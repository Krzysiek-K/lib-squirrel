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
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType>
inline SQInteger Call(ReturnType (*function)(), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)() const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0>
inline SQInteger Call(ReturnType (*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(ReturnType (*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9), HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

//----------------------------------------------------------------------------------------------------------------------
// Call
//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename ReturnType, typename ParameterType0, typename ParameterType1, typename ParameterType2, typename ParameterType3, typename ParameterType4, typename ParameterType5, typename ParameterType6, typename ParameterType7, typename ParameterType8, typename ParameterType9>
inline SQInteger Call(const InstanceType &instance, ReturnType (InstanceType::*function)(ParameterType0, ParameterType1, ParameterType2, ParameterType3, ParameterType4, ParameterType5, ParameterType6, ParameterType7, ParameterType8, ParameterType9) const, HSQUIRRELVM vm, SQInteger index)
{
  return autogen::ReturnSpecialisation<ReturnType>::Call(instance, function, vm, index);
}

} // namespace autogen

} // namespace sqb
