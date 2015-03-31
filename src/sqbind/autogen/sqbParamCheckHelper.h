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
#include "sqbind/sqbTypeInfo.h"
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
class ParamCheckHelper
{
public:
  template<typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)());
  template<typename InstanceType, typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)());
  template<typename InstanceType, typename ReturnType>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)() const);
  template<typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0));
  template<typename InstanceType, typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0));
  template<typename InstanceType, typename ReturnType, typename ParameterType0>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const);
  template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9));
  template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
  static SQRESULT SetParamsCheck(HSQUIRRELVM vm, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const);
};

} // namespace autogen

} // namespace sqb

#include "sqbind/autogen/sqbParamCheckHelper.inl"
