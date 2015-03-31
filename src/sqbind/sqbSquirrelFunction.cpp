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
#include <sqbind/sqbSquirrelFunction.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbSquirrelVM.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelFunction
//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm)
: m_vm(vm)
{
  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm, SQInteger index)
: m_vm(vm)
{
#if SQBIND_ASSERTS_ENABLED
  SQObjectType type = sq_gettype(m_vm, index);
  SQBIND_ASSERT(type == OT_CLOSURE || type == OT_NATIVECLOSURE || type == OT_GENERATOR);
#endif
  m_function.Reference(m_vm, index);

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(HSQUIRRELVM vm, HSQOBJECT function)
: m_vm(vm)
{
  SQBIND_ASSERT(sq_type(function) == OT_CLOSURE || sq_type(function) == OT_NATIVECLOSURE || sq_type(function) == OT_GENERATOR);
  m_function.Reference(m_vm, function);

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelFunction::SquirrelFunction(const SquirrelObject &function)
: m_function(function)
{
  SQBIND_ASSERT(m_function.GetType() == OT_CLOSURE || m_function.GetType() == OT_NATIVECLOSURE || m_function.GetType() == OT_GENERATOR);
  m_vm = m_function.GetVM();

  sq_pushroottable(m_vm);
  m_environment.Reference(m_vm, -1);
  sq_poptop(m_vm);

  sq_newarray(m_vm, 0);
  m_arguments.Reference(m_vm, -1);
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetFunction(SQInteger index)
{
#if SQBIND_ASSERTS_ENABLED
  SQObjectType type = sq_gettype(m_vm, index);
  SQBIND_ASSERT(type == OT_CLOSURE || type == OT_NATIVECLOSURE || type == OT_GENERATOR);
#endif
  m_function.Reference(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetFunction(HSQOBJECT function)
{
  SQBIND_ASSERT(sq_type(function) == OT_CLOSURE || sq_type(function) == OT_NATIVECLOSURE || sq_type(function) == OT_GENERATOR);
  m_function.Reference(m_vm, function);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetEnvironment(SQInteger index)
{
  m_environment.Reference(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
void SquirrelFunction::SetEnvironment(HSQOBJECT environment)
{
  m_environment.Reference(m_vm, environment);
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelFunction::Call()
{
  ExecutionOptions options;
  SQRESULT result = Call(options);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelFunction::Call(const ExecutionOptions &options)
{
  // push the function and environment first
  //
  sq_pushobject(m_vm, m_function);
  sq_pushobject(m_vm, m_environment);

  // push the arguments array so we can push all the arguments
  //
  sq_pushobject(m_vm, m_arguments);
  SQInteger argumentCount = sq_getsize(m_vm, -1);
  for (SQInteger i = 0; i != argumentCount; ++i)
  {
    sq_pushinteger(m_vm, i);
    SQRESULT result = sq_rawget(m_vm, -i - 2);
    SQBIND_ASSERT_SUCCEEDED(result);
  }
  // remove the arguments array
  //
  sq_remove(m_vm, -argumentCount - 1);

  SQRESULT result = sq_call(m_vm, argumentCount + 1, SQTrue, options.m_raiseError);
  if (SQ_SUCCEEDED(result))
  {
    m_returnValue.Reference(m_vm, -1);
    // pop the return value
    //
    sq_poptop(m_vm);
  }

  // pop the function
  //
  sq_poptop(m_vm);

  return result;
}

} // namespace sqb
