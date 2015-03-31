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

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(push)
// disable warning C4127: conditional expression is constant
// type traits kValue used as conditionals
#pragma warning(disable: 4127)
#endif

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
// Specialisation based on if a type is copyable, required to work round template specialisation issues.
// Consider: template<typename X> class A { template<typename Y> class B{}; };
// It is not permitted to specialise class B without also specialising class A so this helper function is needed
// for the default constructors
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyableType>
struct CopyableSpecialisation
{
  template<typename ClassType>
  static SQInteger ClassUserDataConstructor(HSQUIRRELVM vm);

  template<typename ClassType>
  static SQInteger SqMallocConstructor(HSQUIRRELVM vm);
};

} // namespace internal

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline HSQOBJECT ClassDefinitionBase<ClassType, BaseClassType>::GetClassObject() const
{
  return m_classObject;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SetUserDataSize(size_t size)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_setclassudsize(m_vm, -1, size);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SetReleaseHook(SQRELEASEHOOK hook)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
  classTypeTag->SetReleaseHook(hook);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Constructor(
  SQFUNCTION constructor,
  const FunctionOptions& options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeFunction(m_vm, -1, constructor, _SC("constructor"), options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::ClassFunction(
  FuncType function,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindClassFunction<ClassType>(m_vm, -1, function, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeClassFunction(
  HSQMETHOD function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeClassFunction<ClassType>(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Function(
  FuncType function,
  const SQChar *name,
  FunctionOptions options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindFunction(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeFunction(
  SQFUNCTION function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeFunction(m_vm, -1, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename FuncType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::SingletonFunction(
  ClassType *instance,
  FuncType function,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindSingletonFunction(m_vm, -1, instance, function, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::NativeSingletonFunction(
  ClassType *instance,
  HSQMETHOD function,
  const SQChar *name,
  const FunctionOptions &options)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindNativeSingletonFunction(m_vm, -1, instance, function, name, options);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::Variable(
  VariableType ClassType:: *variable,
  const SQChar             *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindInstanceVariable<ClassType>(m_vm, -1, variable, name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::UserPointerVariable(
  VariableType ClassType:: *variable,
  const SQChar             *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sqb::Bind::BindInstanceVariable<ClassType>(m_vm, -1, reinterpret_cast<SQUserPointer ClassType::*>(variable), name);
  sq_poptop(m_vm);
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
template<typename VariableType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::StaticVariable(
  const VariableType &variable,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_pushstring(m_vm, name, -1);
  Push(m_vm, variable);
  sq_newslot(m_vm, -3, SQTrue);
  sq_poptop(m_vm);

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>& ClassDefinitionBase<ClassType, BaseClassType>::EnumEntry(
  SQInteger entry,
  const SQChar *name)
{
  SQBIND_ASSERT(sq_isclass(m_classObject));

  sq_pushobject(m_vm, m_classObject);
  sq_pushstring(m_vm, name, -1);
  sq_pushinteger(m_vm, entry);
  sq_newslot(m_vm, -3, SQTrue);
  sq_poptop(m_vm);

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
ClassDefinitionBase<ClassType, BaseClassType>::ClassDefinitionBase(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: m_vm(vm)
{
  sq_resetobject(&m_classObject);

  if (!sqb::Bind::BindClass<ClassType, BaseClassType>(m_vm, ownerIndex, name))
  {
    return;
  }

  sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
  m_classObject = classTypeTag->GetClassObject(m_vm);
  sq_addref(m_vm, &m_classObject);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinitionBase<ClassType, BaseClassType>::~ClassDefinitionBase()
{
  sq_release(m_vm, &m_classObject);
}

//----------------------------------------------------------------------------------------------------------------------
// ClassUserDataClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger ClassUserDataClassDefinition<ClassType, BaseClassType>::DefaultConstructor(HSQUIRRELVM vm)
{
  typedef internal::CopyableSpecialisation<traits::IsCopyable<ClassType>::kValue> CopyableSpecialisation;
  return CopyableSpecialisation::template ClassUserDataConstructor<ClassType>(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger ClassUserDataClassDefinition<ClassType, BaseClassType>::DefaultReleaseHook(
  SQUserPointer up,
  SQInteger     SQBIND_UNUSED(size))
{
  if (!traits::IsPod<ClassType>::kValue)
  {
    ClassType *instance = static_cast<ClassType *>(up);
    (void)instance; // line below isn't enough to make it think it is referenced.
    instance->~ClassType();
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassUserDataClassDefinition<ClassType, BaseClassType>::ClassUserDataClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
  size_t classUserDataSize = sizeof(ClassType);
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    // need to ensure there is room to align the instance if necessary
    //
    classUserDataSize += traits::IsAligned<ClassType>::kAlignment;
  }
  // needs to be fully qualified to prevent there are no arguments to 'SetUserDataSize' that depend
  // on a template parameter, so a declaration of 'SetUserDataSize' must be available
  //
  ClassDefinitionBase<ClassType, BaseClassType>::SetUserDataSize(classUserDataSize);

  if (!traits::IsPod<ClassType>::kValue)
  {
    sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
    classTypeTag->SetReleaseHook(&DefaultReleaseHook);
  }

  FunctionOptions options;
  if (traits::IsCopyable<ClassType>::kValue)
  {
    options.m_paramCheckCount = -1;
    options.m_typeMaskString = _SC("xx");
    
  }
  else
  {
    options.m_paramCheckCount = 1;
    options.m_typeMaskString = _SC("x");
  }
  ClassDefinitionBase<ClassType, BaseClassType>::Constructor(&DefaultConstructor, options);
}

//----------------------------------------------------------------------------------------------------------------------
// SqMallocClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger SqMallocClassDefinition<ClassType, BaseClassType>::DefaultConstructor(HSQUIRRELVM vm)
{
  typedef internal::CopyableSpecialisation<traits::IsCopyable<ClassType>::kValue> CopyableSpecialisation;
  return CopyableSpecialisation::template SqMallocConstructor<ClassType>(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SQInteger SqMallocClassDefinition<ClassType, BaseClassType>::DefaultReleaseHook(
  SQUserPointer up,
  SQInteger     size)
{
  if (!traits::IsPod<ClassType>::kValue)
  {
    ClassType *instance = static_cast<ClassType *>(up);
    (void)instance; // line below isn't enough to make it think it is referenced.
    instance->~ClassType();
  }

  sq_free(up, size);

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline SqMallocClassDefinition<ClassType, BaseClassType>::SqMallocClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
  // Classes bound with SqMalloc currently do not support alignment
  //
  SQBIND_ASSERT(!traits::IsAligned<ClassType>::kIsAligned);

  if (!traits::IsPod<ClassType>::kValue)
  {
    sqb::ClassTypeTag<ClassType>* classTypeTag = sqb::ClassTypeTag<ClassType>::Get();
    classTypeTag->SetReleaseHook(&DefaultReleaseHook);
  }

  FunctionOptions options;
  if (traits::IsCopyable<ClassType>::kValue)
  {
    options.m_paramCheckCount = -1;
    options.m_typeMaskString = _SC("xx");
  }
  else
  {
    options.m_paramCheckCount = 1;
    options.m_typeMaskString = _SC("x");
  }
  ClassDefinitionBase<ClassType, BaseClassType>::Constructor(&DefaultConstructor, options);
}

//----------------------------------------------------------------------------------------------------------------------
// NoConstructorClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline NoConstructorClassDefinition<ClassType, BaseClassType>::NoConstructorClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassDefinitionBase<ClassType, BaseClassType>(vm, ownerIndex, name)
{
}

//----------------------------------------------------------------------------------------------------------------------
// ClassDefinition
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
inline ClassDefinition<ClassType, BaseClassType>::ClassDefinition(
  HSQUIRRELVM   vm,
  SQInteger     ownerIndex,
  const SQChar *name)
: ClassUserDataClassDefinition<ClassType, BaseClassType>(vm, ownerIndex, name)
{
}

//----------------------------------------------------------------------------------------------------------------------
// internal::CopyableSpecialisation
//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<true>::ClassUserDataConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQUserPointer userPointer;
  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  sq_getinstanceup(vm, 1, &userPointer, nullptr);
  SQBIND_ASSERT_MSG(userPointer != nullptr, "new instance user pointer was null, did you forget to call sq_setclassudsize?");

  // align the instance if required
  //
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
    const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<ClassType>::kAlignment);
    userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
    sq_setinstanceup(vm, 1, userPointer);
  }

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  if (stack.GetParamCount() == 2)
  {
    const ClassType *original = static_cast<const ClassType *>(stack.GetInstanceMatchTypeTag(2, classTypeTag));
    if (original)
    {
      // instance is for inspecting with a debugger
      //
      ClassType *instance = new (userPointer) ClassType(*original);
      (void)instance;

      return 1;
    }

    return stack.ThrowParamError(2, sqb::TypeInfo<ClassType>().m_typeName);
  }

  // instance is for inspecting with a debugger
  //
  ClassType *instance = new (userPointer) ClassType;
  (void)instance;

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<false>::ClassUserDataConstructor(
  HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQUserPointer userPointer;
  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  sq_getinstanceup(vm, 1, &userPointer, nullptr);
  SQBIND_ASSERT_MSG(userPointer != nullptr, "new instance user pointer was null, did you forget to call sq_setclassudsize?");

  // align the instance if required
  //
  if (traits::IsAligned<ClassType>::kIsAligned)
  {
    const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
    const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<ClassType>::kAlignment);
    userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
    sq_setinstanceup(vm, 1, userPointer);
  }

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  // instance is for inspecting with a debugger
  //
  ClassType *instance = new (userPointer) ClassType;
  (void)instance;

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<true>::SqMallocConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  void *memory = sq_malloc(sizeof(ClassType));

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  if (stack.GetParamCount() == 2)
  {
    const ClassType *original = static_cast<const ClassType *>(stack.GetInstanceMatchTypeTag(2, classTypeTag));
    if (original)
    {
      ClassType *instance = new (memory) ClassType(*original);
      sq_setinstanceup(vm, 1, instance);

      return 1;
    }

    // make sure we don't leak memory
    //
    sq_free(memory, sizeof(ClassType));
    sq_setinstanceup(vm, 1, nullptr);
    sq_setreleasehook(vm, 1, nullptr);

    return stack.ThrowParamError(2, sqb::TypeInfo<ClassType>().m_typeName);
  }

  ClassType *instance = new (memory) ClassType;
  sq_setinstanceup(vm, 1, instance);

  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
inline SQInteger internal::CopyableSpecialisation<false>::SqMallocConstructor(HSQUIRRELVM vm)
{
  StackHandler stack(vm);

  ClassTypeTag<ClassType>* classTypeTag = ClassTypeTag<ClassType>::Get();

  SQBIND_ASSERT(sq_gettype(vm, 1) == OT_INSTANCE);
  void *memory = sq_malloc(sizeof(ClassType));

  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  sq_setreleasehook(vm, 1, hook);

  ClassType *instance = new (memory) ClassType;
  sq_setinstanceup(vm, 1, instance);

  return 1;
}

} // namespace sqb

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(pop)
#endif
