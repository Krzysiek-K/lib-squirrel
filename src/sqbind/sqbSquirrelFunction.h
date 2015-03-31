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
#include <sqbind/sqbAssert.h>
#include <sqbind/sqbScopedArrayAccess.h>
#include <sqbind/sqbSquirrelObject.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
struct ExecutionOptions;

//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelFunction
{
public:
  SquirrelFunction(HSQUIRRELVM vm);
  SquirrelFunction(HSQUIRRELVM vm, SQInteger index);
  SquirrelFunction(HSQUIRRELVM vm, HSQOBJECT function);
  SquirrelFunction(const SquirrelObject &function);

  /// \brief returns the previously managed vm.
  HSQUIRRELVM SetVM(HSQUIRRELVM vm);
  /// \brief Get the vm.
  HSQUIRRELVM GetVM() const;

  /// \note Setting the function does not affect the environment or arguments array.
  void SetFunction(SQInteger index);
  void SetFunction(HSQOBJECT function);

  /// \brief Set the environment to use when calling this function. By default the
  ///   environment is the root table of the function's vm, you only need to call this
  ///   function if you would like to use a different environment.
  void SetEnvironment(SQInteger index);
  void SetEnvironment(HSQOBJECT environment);

  /// \brief Returns the current number of arguments bound to this function instance.
  SQInteger GetArgumentCount() const;

  /// \brief Clears all currently bound arguments.
  void ClearArguments();

  /// \brief Adds an argument to be passed to the function when called.
  template<typename ArgumentType>
  void AddArgument(ArgumentType argument);

  template<typename ArgumentType>
  void InsertArgument(SQInteger index, ArgumentType argument);

  /// \brief Overwrites an existing function argument. This will assert if you try an overwrite a
  ///   non-existant argument.
  template<typename ArgumentType>
  void OverwriteArgument(SQInteger index, ArgumentType argument);

  /// \brief Remove an existing function argument. This will assert if you try an remove a
  ///   non-existant argument.
  void RemoveArgument(SQInteger index);

  /// \brief Call the function with the chosen environment and arguments, this can be called repeatedly
  ///   without the need to reset the arguments.
  SQRESULT Call();
  SQRESULT Call(const ExecutionOptions &options);

  /// \brief Get the type of the value returned by the function. If the function returned nothing
  ///   this will return OT_NULL.
  SQObjectType GetReturnType() const;

  /// \brief Get the value returned by the last call. This will be replaced every time the function is called.
  template<typename ResultType>
  const ResultType& GetReturnValue() const;

protected:
  SquirrelObject  m_function;
  SquirrelObject  m_environment;
  SquirrelObject  m_arguments;
  SquirrelObject  m_returnValue;
  HSQUIRRELVM     m_vm;
};

} // namespace sqb

#include <sqbind/sqbSquirrelFunction.inl>
