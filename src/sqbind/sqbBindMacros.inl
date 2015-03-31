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

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
// BaseClassStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<true>::Push(HSQUIRRELVM vm, InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
    if (CreateNativeClassInstance(vm, classObject, hook))
    {
      sq_setinstanceup(vm, -1, value);
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }
  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    if (CreateNativeClassInstance(vm, classObject, nullptr))
    {
      sq_setinstanceup(vm, -1, value);
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<true>::Push(HSQUIRRELVM vm, const InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
    if (CreateNativeClassInstance(vm, classObject, hook))
    {
      sq_setinstanceup(vm, -1, const_cast<InstanceType *>(value));
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT BaseClassStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType *value)
{
  if (value != nullptr)
  {
    const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
    HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
    SQBIND_ASSERT(sq_isclass(classObject));
    if (CreateNativeClassInstance(vm, classObject, nullptr))
    {
      sq_setinstanceup(vm, -1, const_cast<InstanceType *>(value));
      return 1;
    }

    sqb::StackHandler sh(vm);
    return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
  }

  sq_pushnull(vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
// ClassUserDataStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQBIND_ASSERT(classTypeTag->CheckClassUserDataSize(vm, sizeof(InstanceType)));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    SQUserPointer userPointer;
    sq_getinstanceup(vm, -1, &userPointer, 0);

    // align the instance if required
    //
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif
    if (traits::IsAligned<InstanceType>::kIsAligned)
    {
      const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
      const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<InstanceType>::kAlignment);
      userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
      sq_setinstanceup(vm, 1, userPointer);
    }
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(pop)
#endif

    new (userPointer) InstanceType(value);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, const InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQBIND_ASSERT(classTypeTag->CheckClassUserDataSize(vm, sizeof(InstanceType)));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    SQUserPointer userPointer;
    sq_getinstanceup(vm, -1, &userPointer, 0);

    // align the instance if required
    //
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif
    if (traits::IsAligned<InstanceType>::kIsAligned)
    {
      const ptrdiff_t pointer = reinterpret_cast<ptrdiff_t>(userPointer);
      const ptrdiff_t alignment = static_cast<ptrdiff_t>(traits::IsAligned<InstanceType>::kAlignment);
      userPointer = reinterpret_cast<SQUserPointer>((pointer + (alignment - 1)) & ~(alignment - 1));
      sq_setinstanceup(vm, 1, userPointer);
    }
#if defined(SQBIND_COMPILER_MSVC)
# pragma warning(pop)
#endif

    new (userPointer) InstanceType(value);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ClassUserDataStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
// SqMallocStackHelper
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    void *memory = sq_malloc(sizeof(InstanceType));
    new (memory) InstanceType(value);
    sq_setinstanceup(vm, -1, memory);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<false>::Push(HSQUIRRELVM vm, InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<IsCopyable>::Push(HSQUIRRELVM vm, const InstanceType &value)
{
  const ClassTypeTag<InstanceType> *classTypeTag = ClassTypeTag<InstanceType>::Get();
  HSQOBJECT classObject = classTypeTag->GetClassObject(vm);
  SQBIND_ASSERT(sq_isclass(classObject));
  SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
  if (CreateNativeClassInstance(vm, classObject, hook))
  {
    void *memory = sq_malloc(sizeof(InstanceType));
    new (memory) InstanceType(value);
    sq_setinstanceup(vm, -1, memory);
    return 1;
  }

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("failed creating native class instance of type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT SqMallocStackHelper<false>::Push(HSQUIRRELVM vm, const InstanceType &SQBIND_UNUSED(value))
{
  SQBIND_ASSERT_FAIL();

  sqb::StackHandler sh(vm);
  return sh.ThrowError(_SC("cannot push copy of non copyable type '%s'"), TypeInfo<InstanceType>().m_typeName);
}

} // namespace internal

} // namespace sqb
