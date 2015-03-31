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
// ParamCheckHelper
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)())
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)())
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)() const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 1, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 2, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 3, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 4, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 5, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 6, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 7, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 8, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 9, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 10, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9))
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQRESULT ParamCheckHelper::SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const)
{
  SQChar typemask[] =
  {
    _SC('.'),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType0>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType1>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType2>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType3>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType4>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType5>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType6>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType7>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType8>::kType>::kTypeMask),
    _SC(sqb::TypeInfo<typename sqb::traits::RemoveQualifiers<ParameterType9>::kType>::kTypeMask),
    _SC('\0')
  };

  return sq_setparamscheck(vm, 11, typemask);
}

} // namespace autogen

} // namespace sqb
