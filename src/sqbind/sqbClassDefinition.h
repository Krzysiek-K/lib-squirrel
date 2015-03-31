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
#include <sqbind/sqbBind.h>
#include <sqbind/sqbTypeTraits.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Wrapper class for binding squirrel class. This class cannot be used directly, use
/// sqb#ClassDefinition or sqb#NoConstructorClassDefinition.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
class ClassDefinitionBase
{
public:
  /// \brief typedef for class method with variable arguments.
  typedef SQInteger (ClassType::*HSQMETHOD)(HSQUIRRELVM);

  /// \brief Get the object that defines this class being bound.
  HSQOBJECT GetClassObject() const;

  /// \brief Sets the user data size of the class. When an instance of the class is created
  /// an additional amount of memory of size is also allocated after the instance saving the need
  /// for another allocation. The instance user pointer will point at the start of this additional
  /// memory block. ClassUserDataClassDefinition uses this approach to save the need for an additional allocation
  /// with every instance which SqMallocClassDefinition requires.
  ClassDefinitionBase& SetUserDataSize(size_t size);

  /// \brief Set the release hook for this class, will override any existing release hook.
  /// \note ClassUserDataClassDefinition and SqMallocClassDefinition call this function internally so unless
  /// you need to override the default release hook there is no need to call this.
  ClassDefinitionBase& SetReleaseHook(SQRELEASEHOOK hook);

  /// \brief Set the constructor of this class type. This will override any existing constructor
  /// but leave the current release hook. Useful when a class has a constructor that accepts more
  /// than the arguments the default SqMallocConstructor and ClassUserDataConstructor functions provide.
  /// \code
  /// class Vector2
  /// {
  /// public:
  ///   Vector2();
  ///   Vector2(const Vector2& copy);
  ///   Vector2(float x, float y);
  /// }
  ///
  /// SQInteger Vector2Constructor(HSQUIRRELVM vm);
  ///
  /// // ClassUserDataClassDefinition constructor sets up a default constructor and release hook and then
  /// // the call to Constructor overrides the constructor but leaves the release hook.
  /// sqb::ClassUserDataClassDefinition(vm, "Vector2")
  ///   .Constructor(
  ///     &Vector2Constructor,
  ///     FunctionOptions()
  ///       .ParamCheckCount(-1)
  ///       .TypeMask(_SC("x x|n n"))
  ///     )
  ///   ;
  /// \endcode
  ClassDefinitionBase& Constructor(
    SQFUNCTION constructor,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Bind a class method.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   int Func(int p1, bool p2, float p3);
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).ClassFunction(&MyClass::Func, _SC("function"));
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& ClassFunction(FuncType function, const SQChar *name);

  /// \brief
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   void Func(HSQUIRRELVM vm);
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeClassFunction(&MyClass::Func, _SC("function"));
  /// \endcode
  ClassDefinitionBase& NativeClassFunction(
    HSQMETHOD function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Binds a static class function as a static squirrel function.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   static void Func(int p1, float p2);
  /// }
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).Function(&MyClass::Func, _SC("function"));
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& Function(FuncType function, const SQChar *name, FunctionOptions options = FunctionOptions());

  /// \brief Registers a standard SQFUNCTION as a non-static member function of this class.
  /// \note the Static in the name refers to the c++/c function being static not the squirrel
  /// class function.
  /// \code
  /// class MyClass
  /// {
  /// public:
  ///   static int example1(HSQUIRREL vm);
  /// }
  /// int example2(HSQUIRREL vm);
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeFunction(&MyClass::example1, _SC("example1"));
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass")).NativeFunction(&example2, _SC("example2"));
  /// \endcode
  ClassDefinitionBase& NativeFunction(
    SQFUNCTION function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Bind a normal member function of a singleton class as a static function in squirrel.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   void Func();
  /// }
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .SingletonFunction(Singleton::GetInstance(), &Singleton::Func, _SC("Func")
  ///   ;
  /// \endcode
  template<typename FuncType>
  ClassDefinitionBase& SingletonFunction(ClassType *instance, FuncType function, const SQChar *name);

  /// \brief Bind a variable argument member function of a singleton class as a static function in squirrel.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   SQInteger Func(HSQUIRRELVM vm);
  /// }
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .NativeSingletonFunction(Singleton::GetInstance, &Singleton::Func, _SC("Func")
  ///   ;
  /// \endcode
  ClassDefinitionBase& NativeSingletonFunction(
    ClassType *instance,
    HSQMETHOD function,
    const SQChar *name,
    const FunctionOptions &options = FunctionOptions());

  /// \brief Binds a class member variable as a member variable of the squirrel class.
  /// \code
  /// struct Vector2
  /// {
  ///   float x;
  ///   float y;
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<Vector2>(vm, _SC("Vector2"))
  ///   .Variable(&Vector2::x, _SC("x"))
  ///   .Variable(&Vector2::y, _SC("y"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& Variable(VariableType ClassType:: *var, const SQChar *name);

  /// \brief Binds a class member variable as a member variable of type user pointer in the squirrel class.
  /// User pointers cannot be manipulated directly from squirrel but can be passed around and used as a
  /// function argument.
  /// \code
  /// struct Handle
  /// {
  ///   void *m_pointer;
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<Handle>(vm, _SC("Handle"))
  ///   .UserPointerVariable(&Handle::m_pointer, _SC("pointer"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& UserPointerVariable(VariableType ClassType:: *var, const SQChar *name);

  /// \brief Bind a variable as a static member of a class.
  /// Useful in conjunction with SingletonFunc for binding specific instance member variables 
  /// or normal variables. All static variables are const for fundamental squirrel types bound
  /// static variables will have the value at the time of binding.
  /// \code
  /// class Singleton
  /// {
  /// public:
  ///   static Singleton *GetInstance();
  ///   bool m_boolean;
  /// };
  /// static int m_integer;
  ///
  /// sqb::NoConstructorClassDefinition(vm, _SC("Singleton"))
  ///   .StaticVariable(GetInstance()->m_boolean, _SC("boolean"))
  ///   .StaticVariable(m_integer, _SC("integer"))
  ///   ;
  /// \endcode
  template<typename VariableType>
  ClassDefinitionBase& StaticVariable(const VariableType &var, const SQChar *name);

  /// \brief Bind an integer or enum value as a static int member of the class
  /// \code
  /// class Window
  /// {
  /// public:
  ///   enum CreationFlags
  ///   {
  ///     kCreateMaximised = 0,
  ///     kCreateResizable = 1
  ///   };
  ///   // other code
  /// };
  /// int kExternalCreateFlag = 2;
  ///
  /// sqb::ClassDefinition<Window>(vm, name)
  ///   .EnumEntry(Window::kCreateMaximised, _SC("kCreateMaximised"))
  ///   .EnumEntry(Window::kCreateResizable, _SC("kCreateResizable"))
  ///   .EnumEntry(kExternalCreateFlag, _SC("kExternalCreateFlag"))
  ///   ;
  /// \endcode
  ClassDefinitionBase& EnumEntry(SQInteger value, const SQChar *name);

protected:
  HSQUIRRELVM     m_vm;
  HSQOBJECT       m_classObject;

  ClassDefinitionBase(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name);
  ~ClassDefinitionBase();

  /// \cond NO_DOXYGEN
  ClassDefinitionBase(const ClassDefinitionBase& rhs);
  const ClassDefinitionBase& operator = (const ClassDefinitionBase& rhs);
  /// \endcond
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with a default constructor and typeof function. The memory required for new class instances
/// will be allocated using squirrel's class user data functionality so only one allocation will be done for the
/// stack object and the instance itself, this is the most effective way of creating new class instances within
/// squirrel. For types declared with SQBIND_DECLARE_CLASS_POD this also means they need no release hook at all which
/// is also a minor speed up. Use in conjunction with SQBIND_DECLARE_CLASSUD_CLASS or SQBIND_DECLARE_CLASS.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class ClassUserDataClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief The default constructor for classes bound with this method, can be used as a fallback in
  ///   custom constructors.
  static SQInteger DefaultConstructor(HSQUIRRELVM vm);
  /// \brief The default release hook for classes bound with this method.
  /// \note If a class is a pod type then there is no need to ever use a release hook, calling this function
  /// will be a no-op.
  static SQInteger DefaultReleaseHook(SQUserPointer up, SQInteger size);

  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// class MyClass
  /// {
  /// };
  ///
  /// sqb::ClassUserDataClassDefinition<MyClass>(vm, _SC("MyClass"));
  /// \endcode
  ClassUserDataClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with a default constructor and typeof function. The memory required for new class instances
/// will be allocated and deallocated with calls to sq_malloc and sq_free. This will be additional to the allocation
/// squirrel will do internally for the stack object. Even if a class is declared with SQBIND_DECLARE_CLASS_POD a
/// release hook is required to ensure sq_free is called. Use in conjunction with SQBIND_DECLARE_SQMALLOC_CLASS.
/// \note This is really only provided as a reference of how other ClassDefinition types can be implemented, use
/// ClassUserDataClassDefinition instead.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class SqMallocClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief The default constructor for classes bound with this method, can be used as a fallback in
  ///   custom constructors.
  static SQInteger DefaultConstructor(HSQUIRRELVM vm);
  /// \brief The default release hook for classes bound with this method.
  static SQInteger DefaultReleaseHook(SQUserPointer up, SQInteger size);
  
  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// namespace blah
  /// {
  /// class MyClass
  /// {
  /// };
  /// }
  ///
  /// sqb::SqMallocClassDefinition<blah::MyClass>(vm, _SC("ScriptClass"));
  /// \endcode
  SqMallocClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
    
protected:
  template<bool IsCopyableType>
  SQInteger InternalDefaultConstructor(HSQUIRRELVM vm);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Binds a class with the typeof function overloaded. This class can be used if you wish to provide custom
/// methods for allocating/deallocating instance types or for classes that are purely created within c++ code and never
/// squirrel scripts. This can be used to expose singleton classes to script. Use in conjunction with
/// SQBIND_DECLARE_NON_COPYABLE_CLASS or SQBIND_DECLARE_CUSTOM_CLASS.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class NoConstructorClassDefinition : public ClassDefinitionBase<ClassType, BaseClassType>
{
public:
  /// \brief Bind a class to script.
  /// \code
  /// namespace blah
  /// {
  /// class MyClass
  /// {
  /// };
  /// }
  ///
  /// sqb::NoConstructorClassDefinition<blah::MyClass>(vm, _SC("MyClass"));
  /// \endcode
  NoConstructorClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType = NoBaseClass>
class ClassDefinition : public ClassUserDataClassDefinition<ClassType, BaseClassType>
{
public:
  /// \brief Bind a class to script. The parameter name is the name of the class
  /// in script and does not have to be the same as the actual class name.
  /// \code
  /// class MyClass
  /// {
  /// };
  ///
  /// sqb::ClassDefinition<MyClass>(vm, _SC("MyClass"));
  /// \endcode
  ClassDefinition(
    HSQUIRRELVM   vm,
    SQInteger     ownerIndex,
    const SQChar *name);
};

/*Initializing the implicit object parameter 'Type' (a non-const reference) with a non-lvalue*/
/*lint -esym(1793,sqb::ClassDefinitionBase<*,*>)*/
/*Ignoring return value of function*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::Func)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::FuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::GlobalMemberFunc)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::GlobalMemberFuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticFunc)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticFuncVarArgs)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::Var)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::VarAsUserPointer)*/
/*lint -esym(534,sqb::ClassDefinitionBase<*,*>::StaticVar)*/

}

#include <sqbind/sqbClassDefinition.inl>
