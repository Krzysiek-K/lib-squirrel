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
#include <sqbind/sqbSquirrelVM.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdsystem.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbAssert.h>
#include <sqbind/sqbSquirrelObject.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// SquirrelVM
//----------------------------------------------------------------------------------------------------------------------
bool SquirrelVM::Initialise(InitialisationOptions::Flags flags)
{
  if (m_vm != nullptr)
  {
    // vm is already initialised.
    //
    return false;
  }

  m_vm = sq_open(kInitialStackSize);
  SQBIND_ASSERT(m_vm != nullptr);

  // enable debug line number info for error reporting
  //
  sq_enabledebuginfo(m_vm, SQTrue);

  // setup the compiler and runtime error handlers to use the print function
  //
  sqstd_seterrorhandlers(m_vm);

  // initialise all the standard libs
  //
  if (flags != InitialisationOptions::kRegisterNoStdLibs)
  {
    sq_pushroottable(m_vm);

    if ((flags & InitialisationOptions::kRegisterStdBlobLib) == InitialisationOptions::kRegisterStdBlobLib)
    {
      SQRESULT result = sqstd_register_bloblib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdIOLib) == InitialisationOptions::kRegisterStdIOLib)
    {
      SQRESULT result = sqstd_register_iolib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdMathLib) == InitialisationOptions::kRegisterStdMathLib)
    {
      SQRESULT result = sqstd_register_mathlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdStringLib) == InitialisationOptions::kRegisterStdStringLib)
    {
      SQRESULT result = sqstd_register_stringlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    if ((flags & InitialisationOptions::kRegisterStdSystemLib) == InitialisationOptions::kRegisterStdSystemLib)
    {
      SQRESULT result = sqstd_register_systemlib(m_vm);
      SQBIND_ASSERT_SUCCEEDED(result);
    }

    // pop the root table
    //
    sq_poptop(m_vm);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool SquirrelVM::Shutdown()
{
  if (m_vm == nullptr)
  {
    // vm was never initialised
    //
    return false;
  }

  // shutdown the vm
  //
  sq_close(m_vm);
  m_vm = nullptr;

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::GetRootTable() const
{
  sq_pushroottable(m_vm);
  SquirrelObject object(m_vm, -1);
  sq_poptop(m_vm);
  return object;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::GetConstTable() const
{
  sq_pushconsttable(m_vm);
  SquirrelObject object(m_vm, -1);
  sq_poptop(m_vm);
  return object;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewTable()
{
  sq_newtable(m_vm);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewTable(SQInteger initialCapacity)
{
  sq_newtableex(m_vm, initialCapacity);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CreateNewArray(SQInteger size)
{
  sq_newarray(m_vm, size);
  SquirrelObject result(m_vm, -1);
  sq_poptop(m_vm);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CompileBuffer(
  const SQChar              *buffer,
  const CompilationOptions  &compilationOptions)
{
  SquirrelObject compiledBuffer;

  if (m_vm == nullptr)
  {
    return compiledBuffer;
  }

  if (buffer == nullptr)
  {
    return compiledBuffer;
  }

  size_t bufferLength = scstrlen(buffer);
  if (bufferLength == 0)
  {
    return compiledBuffer;
  }

  // compile the buffer with the given compilation options
  //
  SQRESULT result = sq_compilebuffer(
    m_vm,
    buffer,
    bufferLength,
    compilationOptions.m_sourceName ? compilationOptions.m_sourceName : _SC("CompiledBuffer"),
    compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    compiledBuffer.Reference(m_vm, -1);
    sq_poptop(m_vm);
  }

  return compiledBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
SquirrelObject SquirrelVM::CompileScript(
  const SQChar              *filename,
  const CompilationOptions  &compilationOptions)
{
  SquirrelObject compiledBuffer;

  if (m_vm == nullptr)
  {
    return compiledBuffer;
  }

  if (filename == nullptr)
  {
    return compiledBuffer;
  }

  size_t filenameLength = scstrlen(filename);
  if (filenameLength == 0)
  {
    return compiledBuffer;
  }

  // load and compile the script with the given compilation options
  //
  SQRESULT result = sqstd_loadfile(m_vm, filename, compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    compiledBuffer.Reference(m_vm, -1);
    sq_poptop(m_vm);
  }

  return compiledBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelVM::ExecuteBuffer(
  const SQChar              *buffer,
  const CompilationOptions  &compilationOptions,
  const ExecutionOptions    &executionOptions,
  SquirrelObject            *returnValue)
{
  if (m_vm == nullptr)
  {
    return SQ_ERROR;
  }

  if (buffer == nullptr)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : argument 'buffer' was null."));
  }

  size_t bufferLength = scstrlen(buffer);
  if (bufferLength == 0)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : argument 'buffer' was empty."));
  }

  // compile the buffer with the given compilation options
  //
  SQRESULT result = sq_compilebuffer(
    m_vm,
    buffer,
    bufferLength,
    compilationOptions.m_sourceName ? compilationOptions.m_sourceName : _SC("CompiledBuffer"),
    compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_FAILED(result))
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : compilation of buffer failed."));
  }

  // push the root table
  //
  sq_pushroottable(m_vm);

  // call the compiled buffer with the given execution options
  //
  result = sq_call(
    m_vm,
    1,
    (returnValue != nullptr) ? SQTrue : SQFalse,
    executionOptions.m_raiseError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    if (returnValue != nullptr)
    {
      returnValue->Reference(m_vm, -1);

      // remove the result and the compiled buffer
      //
      sq_pop(m_vm, 2);

      return 1;
    }
    else
    {
      // pop the compiled buffer
      //
      sq_poptop(m_vm);

      return 0;
    }
  }
  else
  {
    // pop the compiled buffer
    //
    sq_poptop(m_vm);

    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteBuffer() : execution of buffer failed."));
  }
}

//----------------------------------------------------------------------------------------------------------------------
SQRESULT SquirrelVM::ExecuteScript(
  const SQChar              *filename,
  const CompilationOptions  &compilationOptions,
  const ExecutionOptions    &executionOptions,
  SquirrelObject            *returnValue)
{
  if (m_vm == nullptr)
  {
    return SQ_ERROR;
  }

  if (filename == nullptr)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : argument 'filename' was null."));
  }

  size_t filenameLength = scstrlen(filename);
  if (filenameLength == 0)
  {
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : argument 'filename' was empty."));
  }

  // load and compile the script with the given compilation options
  //
  SQRESULT result = sqstd_loadfile(m_vm, filename, compilationOptions.m_printError ? SQTrue : SQFalse);

  if (SQ_FAILED(result))
  {
    // pop the root table
    //
    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : loading of 'filename' failed."));
  }

  // push the root table in anticipation of the call
  //
  sq_pushroottable(m_vm);

  // call the compiled script with the given execution options
  //
  result = sq_call(
    m_vm,
    1,
    (returnValue != nullptr) ? SQTrue : SQFalse,
    executionOptions.m_raiseError ? SQTrue : SQFalse);

  if (SQ_SUCCEEDED(result))
  {
    if (returnValue != nullptr)
    {
      returnValue->Reference(m_vm, -1);

      // remove the result and the compiled buffer
      //
      sq_pop(m_vm, 2);

      return 1;
    }
    else
    {
      // pop the compiled buffer
      //
      sq_poptop(m_vm);

      return 0;
    }
  }
  else
  {
    // pop the root table and compiled buffer
    //
    sq_pop(m_vm, 2);

    return sq_throwerror(m_vm, _SC("SquirrelVM::ExecuteScript() : execution of buffer failed."));
  }
}

} // namespace sqb
