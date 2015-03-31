#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// THIS FILE IS AUTO GENERATED DO NOT EDIT.
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
namespace autogen
{
//----------------------------------------------------------------------------------------------------------------------
// ReturnSpecialisation<ReturnType>
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = function();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(), HSQUIRRELVM, SQInteger)
{
  function();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = (instance.*function)();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(), HSQUIRRELVM, SQInteger)
{
  (instance.*function)();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger)
{
  ReturnType result = (instance.*function)();

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)() const, HSQUIRRELVM, SQInteger)
{
  (instance.*function)();

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(void (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  function(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<ReturnType>::Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  ReturnType result = (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return sqb::Push(vm, result);
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename InstanceType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ReturnSpecialisation<void>::Call(const InstanceType &instance, void (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  if (!sqb::Match(sqb::TypeWrapper<ParameterType0>(), vm, index + 0))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 0, sqb::TypeInfo<ParameterType0>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType1>(), vm, index + 1))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 1, sqb::TypeInfo<ParameterType1>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType2>(), vm, index + 2))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 2, sqb::TypeInfo<ParameterType2>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType3>(), vm, index + 3))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 3, sqb::TypeInfo<ParameterType3>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType4>(), vm, index + 4))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 4, sqb::TypeInfo<ParameterType4>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType5>(), vm, index + 5))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 5, sqb::TypeInfo<ParameterType5>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType6>(), vm, index + 6))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 6, sqb::TypeInfo<ParameterType6>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType7>(), vm, index + 7))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 7, sqb::TypeInfo<ParameterType7>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType8>(), vm, index + 8))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 8, sqb::TypeInfo<ParameterType8>().m_typeName);
  }

  if (!sqb::Match(sqb::TypeWrapper<ParameterType9>(), vm, index + 9))
  {
    sqb::StackHandler sh(vm);
    return sh.ThrowParamError(index + 9, sqb::TypeInfo<ParameterType9>().m_typeName);
  }

  (instance.*function)(
    sqb::Get(sqb::TypeWrapper<ParameterType0>(), vm, index + 0),
    sqb::Get(sqb::TypeWrapper<ParameterType1>(), vm, index + 1),
    sqb::Get(sqb::TypeWrapper<ParameterType2>(), vm, index + 2),
    sqb::Get(sqb::TypeWrapper<ParameterType3>(), vm, index + 3),
    sqb::Get(sqb::TypeWrapper<ParameterType4>(), vm, index + 4),
    sqb::Get(sqb::TypeWrapper<ParameterType5>(), vm, index + 5),
    sqb::Get(sqb::TypeWrapper<ParameterType6>(), vm, index + 6),
    sqb::Get(sqb::TypeWrapper<ParameterType7>(), vm, index + 7),
    sqb::Get(sqb::TypeWrapper<ParameterType8>(), vm, index + 8),
    sqb::Get(sqb::TypeWrapper<ParameterType9>(), vm, index + 9)
    );

  return 0;
}

} // namespace autogen

} // namespace sqb
