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
//----------------------------------------------------------------------------------------------------------------------
inline StackHandler::StackHandler(HSQUIRRELVM vm)
: m_vm(vm)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM StackHandler::GetVMPtr() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::GetParamCount() const
{
  return sq_gettop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType StackHandler::GetType(SQInteger index) const
{
  return sq_gettype(m_vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsNumber(SQInteger index) const
{
  return (sq_gettype(m_vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsString(SQInteger index) const
{
  return sq_gettype(m_vm, index) == OT_STRING;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::IsInstance(SQInteger index) const
{
  return sq_gettype(m_vm, index) == OT_INSTANCE;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool StackHandler::IsInstanceOfType(SQInteger index) const
{
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, index, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::GetInteger(SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQFloat StackHandler::GetFloat(SQInteger index)
{
  SQFloat value = static_cast<SQFloat>(0.0);
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename NumberType>
inline NumberType StackHandler::GetNumber(SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<NumberType>(value);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline float StackHandler::GetNumber(SQInteger index)
{
  SQFloat value = 0;
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<float>(value);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline double StackHandler::GetNumber(SQInteger index)
{
  SQFloat value = 0;
  SQRESULT result = sq_getfloat(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<double>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool StackHandler::GetBool(SQInteger index)
{
  SQBool value = SQFalse;
  SQRESULT result = sq_getbool(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value == SQTrue;
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *StackHandler::GetString(SQInteger index)
{
  const SQChar *value = _SC("");
  SQRESULT result = sq_getstring(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserData(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserdata(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserDataAndTypeTag(SQInteger index, SQUserPointer *typetag)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserdata(m_vm, index, &value, typetag);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetUserPointer(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getuserpointer(m_vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetInstance(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getinstanceup(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassType *StackHandler::GetInstance(SQInteger index)
{
  SQUserPointer value = nullptr;
  SQRESULT result = sq_getinstanceup(m_vm, index, &value, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<ClassType *>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer StackHandler::GetInstanceMatchTypeTag(SQInteger index, SQUserPointer typetag)
{
  // it's not a fatal failure if the typetags don't match so don't assert on the result of sq_getinstanceup,
  // only assert if it's not an instance on the stack.
  //
  SQBIND_ASSERT(sq_gettype(m_vm, index) == OT_INSTANCE);

  SQUserPointer value;
  if (SQ_SUCCEEDED(sq_getinstanceup(m_vm, index, &value, typetag)))
  {
    return value;
  }
  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassType *StackHandler::GetInstanceAsType(SQInteger index)
{
  // it's not a fatal failure if the typetags don't match so don't assert on the result of sq_getinstanceup,
  // only assert if it's not an instance on the stack.
  //
  SQBIND_ASSERT(sq_gettype(m_vm, index) == OT_INSTANCE);

  SQUserPointer value;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  if (SQ_SUCCEEDED(sq_getinstanceup(m_vm, index, &value, typetag)))
  {
    return static_cast<ClassType *>(value);
  }
  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamCountError(SQInteger expectedParamCount)
{
  SQInteger paramCount = GetParamCount();
  return ThrowError(
    _SC("wrong number of parameters '%d' ; expected '%d'"),
    paramCount,
    expectedParamCount);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamCountError(SQInteger minParamCount, SQInteger maxParamCount)
{
  SQInteger paramCount = GetParamCount();
  if (paramCount < minParamCount)
  {
    return ThrowError(
      _SC("too few parameters '%d' ; expected at least '%d'"),
      paramCount,
      minParamCount);
  }
  else
  {
    return ThrowError(
      _SC("too many parameters '%d' ; expected at most '%d'"),
      paramCount,
      maxParamCount);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamError(SQInteger index, const SQChar *expectedType)
{
  return ThrowError(
    _SC("parameter %d has an invalid type '%s' ; expected: '%s'"),
    index - 1,
    GetTypeName(index),
    expectedType);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::ThrowParamError(SQInteger index, SQObjectType expectedType)
{
  return ThrowError(
    _SC("parameter %d has an invalid type '%s' ; expected: '%s'"),
    index - 1,
    GetTypeName(index),
    RawTypeToTypeName(expectedType));
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return()
{ 
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(bool value)
{
  sq_pushbool(m_vm, (value ? SQTrue : SQFalse));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQInteger value)
{
  sq_pushinteger(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQFloat value)
{
  sq_pushfloat(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(const SQChar *value, SQInteger length)
{
  sq_pushstring(m_vm, value, length);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(SQUserPointer value)
{
  sq_pushuserpointer(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::Return(HSQOBJECT value)
{
  sq_pushobject(m_vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(ClassType *value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(ClassType &value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(const ClassType *value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline SQInteger StackHandler::Return(const ClassType &value)
{
  return Push<ClassType>(m_vm, value);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
SQInteger StackHandler::Return(const ClassType *value, SQRELEASEHOOK hook)
{
  if (value != nullptr)
  {
    ClassTypeTag<ClassType> *typeinfo = ClassTypeTag<ClassType>::Get();
    HSQOBJECT classObject = typeinfo->GetClassObject(m_vm);
    if (CreateNativeClassInstance(m_vm, classObject, hook))
    {
      sq_setinstanceup(m_vm, -1, const_cast<ClassType *>(value));
      return 1;
    }
    if (hook != nullptr)
    {
      hook(const_cast<ClassType *>(value), sizeof(ClassType));
    }
    return ThrowError(_SC("error returning instance of type '%s'"), TypeInfo<ClassType>().m_typeName);
  }

  sq_pushnull(m_vm);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger StackHandler::SuspendVM()
{
  return sq_suspendvm(m_vm);
}

} // namespace sqb
