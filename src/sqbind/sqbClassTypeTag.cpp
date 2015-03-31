//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include "sqbPrecompiled.h"
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbClassTypeTag.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ClassTypeTagBase functions
//----------------------------------------------------------------------------------------------------------------------
const int32_t ClassTypeTagBase::m_expectedValidityCheck = 0x0B57AC1E;

// as all ClassTypeTagBase are static instances this destructor is hit after the test coverage scanning has finished
//
SQBIND_TEST_COVERAGE_OFF()
//----------------------------------------------------------------------------------------------------------------------
ClassTypeTagBase::ClassTypeTagBase()
: m_name(_SC("")),
  m_releaseHook(nullptr),
  m_baseType(nullptr),
  m_offset(0),
  m_mayHaveOffset(-1),
  m_validityCheck(m_expectedValidityCheck)
{
}

//----------------------------------------------------------------------------------------------------------------------
ClassTypeTagBase::~ClassTypeTagBase()
{
}
SQBIND_TEST_COVERAGE_ON()

//----------------------------------------------------------------------------------------------------------------------
void ClassTypeTagBase::SetClassObject(HSQUIRRELVM vm, HSQOBJECT classObject)
{
  // add classObject to the registry table with this userpointer as the key
  // so classObject can easily be retrieved when creating instances.
  sq_pushregistrytable(vm);

  // push the key
  SQUserPointer key = static_cast<SQUserPointer>(this);
  sq_pushuserpointer(vm, key);
  // push the class object
  sq_pushobject(vm, classObject);
  // add it to the registry table
  sq_rawset(vm, -3);

  // pop the registry table
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
HSQOBJECT ClassTypeTagBase::GetClassObject(HSQUIRRELVM vm) const
{
  sq_pushregistrytable(vm);

  SQUserPointer key = static_cast<SQUserPointer>(const_cast<ClassTypeTagBase*>(this));
  sq_pushuserpointer(vm, key);

  HSQOBJECT classObject;
  if (SQ_SUCCEEDED(sq_rawget(vm, -2)))
  {
    sq_getstackobj(vm, -1, &classObject);
    // pop the class
    sq_poptop(vm);
  }
  else
  {
    sq_resetobject(&classObject);
  }

  // pop the registry table
  //
  sq_poptop(vm);

  return classObject;
}

//----------------------------------------------------------------------------------------------------------------------
bool ClassTypeTagBase::CheckClassUserDataSize(HSQUIRRELVM vm, SQInteger expectedSize) const
{
  // retrieve the class object from the registry table
  //
  sq_pushregistrytable(vm);

  SQUserPointer key = static_cast<SQUserPointer>(const_cast<ClassTypeTagBase*>(this));
  sq_pushuserpointer(vm, key);

  SQInteger udsize = -1;
  if (SQ_SUCCEEDED(sq_rawget(vm, -2)))
  {
    udsize = sq_getsize(vm, -1);
    SQBIND_ASSERT(udsize != -1);

    // pop the class
    //
    sq_poptop(vm);
  }

  // pop the registry table, sq_rawget always pops the key from the stack regardless of success/failure.
  //
  sq_poptop(vm);

  return udsize >= expectedSize;
}

//----------------------------------------------------------------------------------------------------------------------
bool ClassTypeTagBase::MayHaveOffset() const
{
  if (m_mayHaveOffset < 0)
  {
    // if m_mayHaveOffset is less than 0 then it needs initialising
    //
    if (m_offset != 0)
    {
      // if this type has an offset then there definitely is an offset
      //
      m_mayHaveOffset = 1;
    }
    else
    {
      // if this type has no offset recurse up the hierarchy to the base checking for an offset
      //
      m_mayHaveOffset = 0;

      ClassTypeTagBase *current = m_baseType;
      while (current != nullptr)
      {
        if (current->m_offset != 0)
        {
          // a base class of this type had an offset to there might be an offset
          //
          m_mayHaveOffset = 1;
          break;
        }

        current = current->m_baseType;
      }
    }
  }

  return (m_mayHaveOffset != 0);
}

//----------------------------------------------------------------------------------------------------------------------
ptrdiff_t ClassTypeTagBase::GetOffsetTo(const ClassTypeTagBase *pbase) const
{
  // if this fails then pbase is invalid
  //
  SQBIND_ASSERT(pbase != nullptr);

  // accumulate the offset(s) until we hit pbase
  //
  ptrdiff_t offset = 0;

  const ClassTypeTagBase *current = this;
  while (current != nullptr && current != pbase)
  {
    offset += current->m_offset;
    current = current->m_baseType;
  }

  // if this fails then it doesn't derive from pbase.
  //
  SQBIND_ASSERT(current == pbase);

  return offset;
}

}
