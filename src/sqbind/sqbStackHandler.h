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
#include <sqbind/sqbAssert.h>
#include <sqbind/sqbClassHelpers.h>
#include <sqbind/sqbClassTypeTag.h>
#include <sqbind/sqbStackUtils.h>
#include <sqbind/sqbTypeInfo.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
/// Wraps common functionality for handling the squirrel stack passed into a native closure.
//----------------------------------------------------------------------------------------------------------------------
class StackHandler
{
public:
  /// \brief Initialises the stack handler with a \link #HSQUIRRELVM vm\endlink.
  StackHandler(HSQUIRRELVM vm);

  /// \brief Gets the virtual machine the stack belongs to.
  HSQUIRRELVM GetVMPtr() const;

  /// \brief Gets the number of arguments on the stack.
  SQInteger GetParamCount() const;

  /// \brief Gets the type of the object at the specified index.
  SQObjectType GetType(SQInteger index) const;

  /// \brief Gets the type name of the object at the specified index.
  /// Will generate the same result as calling typeof(obj) in squirrel.
  const SQChar *GetTypeName(SQInteger index) const;

  /// \brief Same as GetType(index) == OT_INTEGER || GetType(index) == OT_FLOAT
  bool IsNumber(SQInteger index) const;

  /// \brief Convenience function same as calling GetType(index) == OT_STRING.
  bool IsString(SQInteger index) const;

  /// \brief Convenience function same as calling GetType(index) == OT_INSTANCE.
  bool IsInstance(SQInteger index) const;

  /// \brief Checks if the object at stack index index is an instance of a particular bound class type.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// ...
  /// if (stack.IsInstanceOfType<MyClass>(1))
  /// {
  ///   MyClass *ptr = stack.GetInstance<MyClass>();
  /// }
  /// \endcode
  template<typename ClassType>
  bool IsInstanceOfType(SQInteger index) const;

  /// \brief Gets an integer from the stack at the specified index. If the object at that index
  /// is not an integer then 0 is returned.
  SQInteger GetInteger(SQInteger index);
  /// \brief Gets a float from the stack at the specified index. If the object at that index is
  /// not a float then 0.0f is returned.
  SQFloat GetFloat(SQInteger index);
  /// \brief Gets a number from the stack. If the object at that index is not a number then 0 is returned.
  /// \code
  /// sqb::StackHandler sh(vm);
  /// float value = sh.GetNumber<float>(1);
  /// \endcode
  template<typename NumberType>
  NumberType GetNumber(SQInteger index);

  /// \brief Gets a boolean from the stack at the specified index. If the object at that index
  /// is not a boolean then the function returns false.
  bool GetBool(SQInteger index);

  /// \brief Gets a string from the stack at the specified index. If the object at that index is
  /// not a string then null is returned.
  const SQChar *GetString(SQInteger index);

  /// \brief Gets a user data from the stack at the specified index.
  SQUserPointer GetUserData(SQInteger index);
  /// \brief Gets a user data from the stack at the specified index also returning an optional typetag.
  SQUserPointer GetUserDataAndTypeTag(SQInteger index, SQUserPointer *typetag);

  /// \brief Gets a user pointer from the stack at the specified index.
  SQUserPointer GetUserPointer(SQInteger index);

  /// \brief Gets an instance user pointer from the stack without checking the typetag.
  SQUserPointer GetInstance(SQInteger index);
  /// \brief Gets an instance of a class from the stack without checking it's type. Use in conjunction
  /// with IsInstanceOfType.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// if (!stack.IsInstanceOfType<MyClass>(1))
  /// {
  ///   return stack.ThrowParamError(1, sqb::TypeInfo<MyClass>().m_typeName);
  /// }
  /// MyClass *_this = stack.GetInstance<MyClass>();
  /// \endcode
  /// \note MyClass must already be bound using SQBIND_DECLARE_CLASS(MyClass); and sqb::ClassDef<MyClass>.
  template<typename ClassType>
  ClassType* GetInstance(SQInteger index);
  /// \brief Gets an instance user pointer from the stack at the specified index checking the typetag, null
  /// typetag means no type check.
  SQUserPointer GetInstanceMatchTypeTag(SQInteger index, SQUserPointer typetag);
  /// \brief Gets a class instance from the stack using ClassType<T>::Get() as the typetag check.
  /// If the object at index is not an instance or does not have the correct typetag then it will
  /// return null otherwise it will return a pointer to the class instance.
  /// \code
  /// sqb::StackHandler stack(vm);
  /// MyClass* instance = stack.GetInstanceAsType<MyClass>(1);
  /// if (instance == nullptr)
  /// {
  ///   return stack.ThrowParamError(1, sqb::TypeInfo<MyClass>().m_typeName);
  /// }
  /// \endcode
  /// \note MyClass must already be bound using SQBIND_DECLARE_CLASS(MyClass); and sqb::ClassDef<MyClass>.
  template<typename ClassType>
  ClassType* GetInstanceAsType(SQInteger index);

  /// \brief Throws a null squirrel exception. This indicates that a set/get metamethod index was not found
  /// allowing squirrel to differentiate between this and a runtime error.
  SQInteger ThrowNull();

  /// \brief Throws a squirrel exception. Must be the returned by the native closure.
  /// \code
  /// StackHandler stack(vm);
  /// return stack.ThrowError(_SC("error message"));
  /// \endcode
  SQInteger ThrowError(const SQChar *format, ...);

  /// \brief Throws a squirrel exception with an error message specific for a call with the wrong
  /// number of parameters.
  SQInteger ThrowParamCountError(SQInteger expectedParamCount);

  /// \brief Throws a squirrel exception with an error message specific for a call with the wrong
  /// number of parameters.
  SQInteger ThrowParamCountError(SQInteger minParamCount, SQInteger maxParamCount);

  /// \brief Throws a squirrel exception with an error message specific for wrong parameter arguments.
  /// \code
  /// // squirrel code
  /// testfunc("blah")
  ///
  /// // c++ code inside testfunc
  /// StackHandler stack(vm);
  /// return stack.ThrowParamError(2, _SC("integer"));
  /// \endcode
  /// Generates the error message "parameter 1 has an invalid type 'string' ; expected: 'integer'".
  /// \note index is the index on the stack not the parameter argument number so a stack index of 2 would be
  /// the first parameter to the function. Stack index 1 is the hidden parameter 0 passed to all functions.
  SQInteger ThrowParamError(SQInteger index, const SQChar *expectedType);

  /// \brief Throws a squirrel exception with an error message specific for wrong parameter arguments.
  /// \code
  /// // squirrel code
  /// testfunc("blah")
  ///
  /// // c++ code inside testfunc
  /// StackHandler stack(vm);
  /// return stack.ThrowParamError(2, OT_INTEGER);
  /// \endcode
  /// Generates the error message "parameter 1 has an invalid type 'string' ; expected: 'integer'".
  /// \note index is the index on the stack not the parameter argument number so a stack index of 2 would be
  /// the first parameter to the function. Stack index 1 is the hidden parameter 0 passed to all functions.
  SQInteger ThrowParamError(SQInteger index, SQObjectType expectedType);

  /// \brief Used to returns nothing from a native closure, must be returned by the native closure.
  /// \return The number of arguments the closure returns.
  /// \code
  /// StackHandler sa(vm);
  ///   ...
  /// return sa.Return();
  /// \endcode
  SQInteger Return();
  /// \overload
  /// Makes the native closure return a bool.
  SQInteger Return(bool b);
  /// \overload
  /// Makes the native closure return an integer.
  SQInteger Return(SQInteger i);
  /// \overload
  /// Makes the native closure return a float.
  SQInteger Return(SQFloat f);
  /// \overload
  /// Makes the native closure return a string
  SQInteger Return(const SQChar *s, SQInteger length = -1);
  /// \overload
  /// Makes the native closure return a user pointer
  SQInteger Return(SQUserPointer p);
  /// \overload
  /// Makes the native closure return a HSQOBJECT.
  SQInteger Return(HSQOBJECT object);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(ClassType *instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(ClassType &instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(const ClassType *instance);
  /// \overload
  /// Returns a bound class instance from a closure.
  template<typename ClassType>
  SQInteger Return(const ClassType &instance);

  /// \overload
  /// In some cases can be quicker than the other templated return functions as it removes
  /// the need for an extra copy constructor and also removes some extra function calls.
  /// \code
  /// MyClass func();
  ///
  /// SQInteger sqfunc_standard(HSQUIRRELVM vm)
  /// {
  ///   return stack.Return(func());
  /// }
  ///
  /// SQInteger sqfunc_fast(HSQUIRRELVM vm)
  /// {
  ///   void *memory = sq_malloc(sizeof(MyClass));
  ///   MyClass *copy = new (memory) MyClass(func());
  ///   return stack.Return(copy, &sqb::DefaultReleaseHook<sqb::IsPodType<MyClass>::kValue>::SqFree<MyClass>);
  /// }
  /// \endcode
  template<typename ClassType>
  SQInteger Return(const ClassType *instance, SQRELEASEHOOK hook);

  /// \brief Suspends the execution of the vm must be returned by a c function.
  SQInteger SuspendVM();

private:
/// \cond NO_DOXYGEN
  HSQUIRRELVM m_vm;

  // disabled constructors and assignment operators
  StackHandler();
  StackHandler(const StackHandler &rhs);
  const StackHandler &operator = (const StackHandler &rhs);
/// \endcond
};

}

#include <sqbind/sqbStackHandler.inl>
