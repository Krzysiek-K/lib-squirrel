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
#include <sqbind/sqbStackHandler.h>
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbClassTypeTag.h>
//----------------------------------------------------------------------------------------------------------------------

#if defined(_MSC_VER)
# if defined(SQUNICODE)
#  define scvscprintf _vscwprintf
#  define scvsnprintf _vsnwprintf_s
# else // defined(SQUNICODE)
#  define scvscprintf _vscprintf
#  define scvsnprintf vsnprintf_s
# endif // defined(SQUNICODE)
#else // defined(_MSC_VER)
# if defined(SQUNICODE)
#  define scvsnprintf vsnwprintf
# else // defined(SQUNICODE)
#  define scvsnprintf vsnprintf
# endif // defined(SQUNICODE)
#endif // defined(_MSC_VER)

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
const SQChar *StackHandler::GetTypeName(SQInteger idx) const
{
  SQObjectType type = sq_gettype(m_vm, idx);

  // if it is an instance bound by this library then use that bound type name
  //
  if (type == OT_INSTANCE)
  {
    SQUserPointer typetag;
    sq_gettypetag(m_vm, idx, &typetag);

    if (typetag != nullptr)
    {
      const ClassTypeTagBase *classTypeTag = static_cast<const ClassTypeTagBase*>(typetag);
      if (classTypeTag->IsValid())
      {
        return classTypeTag->GetTypeName();
      }
    }
  }

  // if the type isn't an instance or the type tag isn't valid then return the raw type.
  //
  return RawTypeToTypeName(type);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger StackHandler::ThrowNull()
{
  sq_reseterror(m_vm);
  return -1;
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger StackHandler::ThrowError(const SQChar *format, ...)
{
  SQBIND_ASSERT(format != nullptr);

#if defined(_MSC_VER)
  va_list vargs;
  va_start(vargs, format);
  int length = scvscprintf(format, vargs) + 1;
  va_end(vargs);

  SQChar *buffer = sq_getscratchpad(m_vm, length);

  va_start(vargs, format);
  scvsnprintf(buffer, length, length - 1, format, vargs);
  va_end(vargs);
#elif defined(__GNUC__) && defined(__STRICT_ANSI__)
  // susceptible to buffer overrun but vsnprintf doesn't exist for ansi c
  //
  const SQInteger increment = 256;
  SQInteger size = ((scstrlen(format) / increment) + 1) * increment;
  SQChar *buffer = sq_getscratchpad(m_vm, size);

  va_list vargs;
  va_start(vargs, format);
  int length = scvsprintf(buffer, format, vargs);
  va_end(vargs);

  SQBIND_ASSERT(length < size);
#else
  const SQInteger increment = 256;
  SQInteger size = ((scstrlen(format) / increment) + 1) * increment;
  SQChar *buffer = sq_getscratchpad(m_vm, size);

  va_list vargs;
  va_start(vargs, format);
  int length = scvsnprintf(buffer, size, format, vargs);
  va_end(vargs);

  if (length >= size)
  {
    buffer = sq_getscratchpad(m_vm, length + 1);

    va_start(vargs, format);
    int length = scvsnprintf(buffer, size, format, vargs);
    va_end(vargs);
  }
#endif

  return sq_throwerror(m_vm, buffer);
}

}
