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
/// Push
//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, bool value)
{
  sq_pushbool(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, char value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int8_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint8_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int16_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint16_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int32_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint32_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, float value)
{
  sq_pushfloat(vm, static_cast<SQFloat>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, const SQChar *value)
{
  sq_pushstring(vm, value, -1);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, SQUserPointer value)
{
  sq_pushuserpointer(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, HSQOBJECT value)
{
  sq_pushobject(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
/// Match
//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<bool> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_BOOL;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<char> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<float> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<const SQChar*> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_STRING;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<SQUserPointer> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return sq_gettype(vm, index) == OT_USERPOINTER;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<HSQOBJECT> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  // sq_gettype for invalid indexes just returns junk, as there is no reliable
  // way to check it failed we have to check the stack size.
  //
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
/// Get
//----------------------------------------------------------------------------------------------------------------------
inline bool Get(TypeWrapper<bool> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBool value;
  SQRESULT result = sq_getbool(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value == SQTrue;
}

//----------------------------------------------------------------------------------------------------------------------
inline char Get(TypeWrapper<char> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<char>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int8_t Get(TypeWrapper<int8_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int8_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint8_t Get(TypeWrapper<uint8_t>, HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint8_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int16_t Get(TypeWrapper<int16_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int16_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint16_t Get(TypeWrapper<uint16_t>, HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value = 0;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint16_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline int32_t Get(TypeWrapper<int32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int32_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint32_t Get(TypeWrapper<uint32_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint32_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline float Get(TypeWrapper<float> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQFloat value;
  SQRESULT result = sq_getfloat(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<float>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *Get(TypeWrapper<const SQChar*> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  const SQChar *value;
  SQRESULT result = sq_getstring(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQUserPointer Get(TypeWrapper<SQUserPointer> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQUserPointer value;
  SQRESULT result = sq_getuserpointer(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQOBJECT Get(TypeWrapper<HSQOBJECT> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(index != 0);
  SQBIND_ASSERT(-sq_gettop(vm) <= index);
  SQBIND_ASSERT(index <= sq_gettop(vm));

  HSQOBJECT value;
  // sq_getstackobj always returns SQ_OK so no need to test the result
  //
  sq_getstackobj(vm, index, &value);
  return value;
}

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, int64_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, uint64_t value)
{
  sq_pushinteger(vm, static_cast<SQInteger>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<int64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<uint64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline int64_t Get(TypeWrapper<int64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<int64_t>(value);
}

//----------------------------------------------------------------------------------------------------------------------
inline uint64_t Get(TypeWrapper<uint64_t> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQInteger value;
  SQRESULT result = sq_getinteger(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<uint64_t>(value);
}

#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, double value)
{
  sq_pushfloat(vm, static_cast<SQFloat>(value));
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool Match(TypeWrapper<double> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index));
  return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC);
}

//----------------------------------------------------------------------------------------------------------------------
inline double Get(TypeWrapper<double> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SQFloat value;
  SQRESULT result = sq_getfloat(vm, index, &value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return static_cast<double>(value);
}

#endif // defined(SQUSEDOUBLE)

} // namespace sqb
