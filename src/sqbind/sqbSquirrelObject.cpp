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
#include <sqbind/sqbSquirrelObject.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelObject
//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelObject::kNullObject;

//----------------------------------------------------------------------------------------------------------------------
const SquirrelObject &SquirrelObject::operator = (const SquirrelObject &rhs)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the other object
  //
  if (rhs.m_vm)
  {
    m_vm = rhs.m_vm;
    m_object = rhs.m_object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(HSQUIRRELVM vm, SQInteger index)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the object on the stack
  //
  if (vm)
  {
    SQRESULT result = sq_getstackobj(vm, index, &m_object);
    SQBIND_ASSERT_SUCCEEDED(result);
    m_vm = vm;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(HSQUIRRELVM vm, HSQOBJECT object)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the new object
  //
  if (vm)
  {
    m_vm = vm;
    m_object = object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Reference(const SquirrelObject &object)
{
  // release the current object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }

  // reference the other object
  //
  if (object.m_vm)
  {
    m_vm = object.m_vm;
    m_object = object.m_object;
    sq_addref(m_vm, &m_object);
  }
  else
  {
    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelObject::Release()
{
  if (m_vm)
  {
    sq_release(m_vm, &m_object);

    m_vm = nullptr;
    sq_resetobject(&m_object);
  }
}

} // namespace sqb
