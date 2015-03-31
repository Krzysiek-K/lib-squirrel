#pragma once
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
#include <squirrel.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbBaseHeader.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
class SquirrelObject;

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API InitialisationOptions
{
  enum
  {
    kRegisterNoStdLibs    = 0,
    kRegisterStdBlobLib   = 1 << 1,
    kRegisterStdIOLib     = 1 << 2,
    kRegisterStdMathLib   = 1 << 3,
    kRegisterStdStringLib = 1 << 4,
    kRegisterStdSystemLib = 1 << 5,
    kRegisterAllStdLibs   = kRegisterStdBlobLib | kRegisterStdIOLib | kRegisterStdMathLib | kRegisterStdStringLib | kRegisterStdSystemLib,
  };

  typedef uint8_t Flags;
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API CompilationOptions
{
  /// \brief The name associated with the compiled script used to generate more meaningful runtime errors,
  ///   defaults to null.
  const SQChar *m_sourceName;

  /// \brief Should an error be printed if the compilation fails, defaults to true.
  bool m_printError;

  CompilationOptions();

  CompilationOptions &SourceName(const SQChar *sourceName);
  CompilationOptions &PrintError(bool printError);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
struct SQBIND_API ExecutionOptions
{
  /// \brief Should the execution raise an error if it fails, defaults to true.
  bool m_raiseError;

  ExecutionOptions();

  ExecutionOptions &RaiseError(bool raiseError);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelVM
{
public:

  enum
  {
    kInitialStackSize = 1024,
  };

  /// \brief Initialises the vm to null.
  SquirrelVM();
  /// \brief Initialise the vm and register the specified standard libraries, this is the same as calling Initialise.
  SquirrelVM(InitialisationOptions::Flags flags);
  /// \brief Initialise with an external vm, you cannot call Initialise if this was called.
  SquirrelVM(HSQUIRRELVM vm);
  /// \brief This destructor does nothing in case the vm was externally managed, to shutdown a vm
  ///   call Shutdown.
  ~SquirrelVM();

  /// \brief Overload the type cast operator to all this to be passed to native squirrel functions.
  operator HSQUIRRELVM () const;

  /// \brief Set the squirrel vm this manages, returns the previously managed vm.
  HSQUIRRELVM SetVM(HSQUIRRELVM vm);
  /// \brief Get the squirrel vm this is managing.
  HSQUIRRELVM GetVM() const;

  /// \brief Perform some standard initialisation of a squirrel vm. Creates a vm, turns on debugging info,
  ///   sets up the compile and runtime error handlers to use the print function and registers the standard
  ///   libraries.
  bool Initialise(InitialisationOptions::Flags flags = InitialisationOptions::kRegisterAllStdLibs);

  /// \brief Has this instance been successfully initialised.
  bool IsInitialised() const;

  /// \brief Shutdown the vm managed by this class.
  bool Shutdown();

  /// \brief Sets the print and error functions.
  bool SetPrintFunction(SQPRINTFUNCTION printFunction);

  SquirrelObject GetRootTable() const;

  SquirrelObject GetConstTable() const;

  SquirrelObject CreateNewTable();
  SquirrelObject CreateNewTable(SQInteger initialCapacity);
  SquirrelObject CreateNewArray(SQInteger size);


  /// \brief Compile a script buffer.
  SquirrelObject CompileBuffer(
    const SQChar              *buffer,
    const CompilationOptions  &compilationOptions = CompilationOptions());

  /// \brief Compile a script file.
  SquirrelObject CompileScript(
    const SQChar              *filename,
    const CompilationOptions  &compilationOptions = CompilationOptions());

  /// \brief Compile and call a script buffer.
  SQRESULT ExecuteBuffer(
    const SQChar              *buffer,
    const CompilationOptions  &compilationOptions = CompilationOptions(),
    const ExecutionOptions    &executionOptions = ExecutionOptions(),
    SquirrelObject            *returnValue = nullptr);

  /// \brief Compile and call a script file.
  SQRESULT ExecuteScript(
    const SQChar              *filename,
    const CompilationOptions  &compilationOptions = CompilationOptions(),
    const ExecutionOptions    &executionOptions = ExecutionOptions(),
    SquirrelObject            *returnValue = nullptr);

protected:
  HSQUIRRELVM m_vm;
};

} // namespace sqb

#include <sqbind/sqbSquirrelVM.inl>
