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
//----------------------------------------------------------------------------------------------------------------------
#include <new>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Class for passing around types.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
struct TypeWrapper { };

/// \brief Pushes a value onto the stack, there is no default implementation of the template versions
/// of this function. Specialisations are declared when the \link CLASS_DECLARATION instance binding macros \endlink
/// are used.
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, T *value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, T &value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, const T *value);

/// \overload
template<typename T>
SQRESULT Push(HSQUIRRELVM vm, const T &value);

/// \brief Checks that an object on the stack is of a particular type.
template<typename T>
bool Match(TypeWrapper<T>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<T *>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<T &> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<const T *> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
bool Match(TypeWrapper<const T &> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \brief Gets a typed value from the stack at the index specified. If the value is
/// a reference then it will be invalid when it is removed from the stack.
/// Get should be used in conjunction with Match as no type checking is done.
template<typename T>
T& Get(TypeWrapper<T> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
T *Get(TypeWrapper<T*> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
T &Get(TypeWrapper<T&> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
const T *Get(TypeWrapper<const T *>, HSQUIRRELVM vm, SQInteger index);

/// \overload
template<typename T>
const T &Get(TypeWrapper<const T &>, HSQUIRRELVM vm, SQInteger index);

/// \overload
SQRESULT Push(HSQUIRRELVM vm, bool value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, char value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int8_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint8_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int16_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint16_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, int32_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, uint32_t value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, float value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, const SQChar *value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, SQUserPointer value);
/// \overload
SQRESULT Push(HSQUIRRELVM vm, HSQOBJECT value);

/// \overload
bool Match(TypeWrapper<bool> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<char> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<int32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<uint32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<float> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<const SQChar*> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<SQUserPointer> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool Match(TypeWrapper<HSQOBJECT> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \overload
bool          Get(TypeWrapper<bool> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
char          Get(TypeWrapper<char> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int8_t        Get(TypeWrapper<int8_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint8_t       Get(TypeWrapper<uint8_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int16_t       Get(TypeWrapper<int16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint16_t      Get(TypeWrapper<uint16_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int32_t       Get(TypeWrapper<int32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint32_t      Get(TypeWrapper<uint32_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
float         Get(TypeWrapper<float> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
const SQChar *Get(TypeWrapper<const SQChar *> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
SQUserPointer Get(TypeWrapper<SQUserPointer> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
HSQOBJECT     Get(TypeWrapper<HSQOBJECT> wrapper, HSQUIRRELVM vm, SQInteger index);

#if defined(_SQ64)
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, int64_t value);
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, uint64_t value);
/// \overload
bool      Match(TypeWrapper<int64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
bool      Match(TypeWrapper<uint64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
int64_t   Get(TypeWrapper<int64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
uint64_t  Get(TypeWrapper<uint64_t> wrapper, HSQUIRRELVM vm, SQInteger index);
#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)
/// \overload
SQRESULT  Push(HSQUIRRELVM vm, double value);
/// \overload
bool      Match(TypeWrapper<double> wrapper, HSQUIRRELVM vm, SQInteger index);
/// \overload
double    Get(TypeWrapper<double> wrapper, HSQUIRRELVM vm, SQInteger index);
#endif // defined(SQUSEDOUBLE)

} // namespace sqb

#include <sqbind/sqbStackUtils.inl>
