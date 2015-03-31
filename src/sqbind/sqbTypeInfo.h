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
#include <sqbind/sqbBaseHeader.h>
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_TYPEINFO(TYPE, NAME)
/// \brief Declares the sqb::TypeInfo struct for a type. This is required for binding a type as a variable.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_TYPEINFO(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  struct TypeInfo<TYPE> \
  { \
    enum \
    { \
      kTypeID = kScriptVarTypeInstance, \
      kTypeSize = sizeof(TYPE), \
      kTypeMask = 'x', \
      kTypeIsInstance = SQTrue, \
    }; \
    const SQChar *m_typeName; \
    inline TypeInfo() \
    : m_typeName(_SC(#NAME)) \
    { \
    } \
    inline operator ScriptVarType() const \
    { \
      return static_cast<ScriptVarType>(kTypeID); \
    } \
  }; \
  }

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Converts from a SQObjectType to a string.
/// \code
/// // prints out "string"
/// scprintf(RawTypeToTypeName(OT_STRING));
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *RawTypeToTypeName(SQObjectType type);

//----------------------------------------------------------------------------------------------------------------------
/// \brief List of basic types that are supported.
//----------------------------------------------------------------------------------------------------------------------
enum ScriptVarType
{
  kScriptVarTypeNone = -1,
  kScriptVarTypeBool = 0,
  kScriptVarTypeChar,
  kScriptVarTypeInt8,
  kScriptVarTypeUInt8,
  kScriptVarTypeInt16,
  kScriptVarTypeUInt16,
  kScriptVarTypeInt32,
  kScriptVarTypeUInt32,
  kScriptVarTypeFloat,
  kScriptVarTypeString,
  kScriptVarTypeUserPointer,
  kScriptVarTypeInstance,
  kScriptVarTypeObject,
#if defined(_SQ64)
  kScriptVarTypeInt64,
  kScriptVarTypeUInt64,
#endif // defined(_SQ64)
#if defined(SQUSEDOUBLE)
  kScriptVarTypeDouble,
#endif // defined(SQUSEDOUBLE)
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Template class for gaining info about a bound script type. Specialisation of TypeInfo
/// is done automatically when a type is declared using #SQBIND_DECLARE_TYPEINFO or any of the other
/// macros that call it.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct TypeInfo
{
  enum
  {
    kTypeID = kScriptVarTypeNone,
    kTypeSize = sizeof(T),
    kTypeMask = '?',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
/// \cond NO_DOXYGEN
template<>
struct TypeInfo<bool>
{
  enum
  {
    kTypeID = kScriptVarTypeBool,
    kTypeSize = sizeof(bool),
    kTypeMask = 'b',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<char>
{
  enum
  {
    kTypeID = kScriptVarTypeChar,
    kTypeSize = sizeof(char),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int8_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt8,
    kTypeSize = sizeof(int8_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint8_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt8,
    kTypeSize = sizeof(uint8_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int16_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt16,
    kTypeSize = sizeof(int16_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint16_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt16,
    kTypeSize = sizeof(uint16_t),
    kTypeMask = 'i',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int32_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt32,
    kTypeSize = sizeof(int32_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint32_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt32,
    kTypeSize = sizeof(uint32_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<float>
{
  enum
  {
    kTypeID = kScriptVarTypeFloat,
    kTypeSize = sizeof(float),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<const SQChar*>
{
  enum
  {
    kTypeID = kScriptVarTypeString,
    kTypeSize = sizeof(const SQChar*),
    kTypeMask = 's',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<SQUserPointer>
{
  enum
  {
    kTypeID = kScriptVarTypeUserPointer,
    kTypeSize = sizeof(SQUserPointer),
    kTypeMask = 'p',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<HSQOBJECT>
{
  enum
  {
    kTypeID = kScriptVarTypeObject,
    kTypeSize = sizeof(HSQOBJECT),
    kTypeMask = '.',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<int64_t>
{
  enum
  {
    kTypeID = kScriptVarTypeInt64,
    kTypeSize = sizeof(int64_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<uint64_t>
{
  enum
  {
    kTypeID = kScriptVarTypeUInt64,
    kTypeSize = sizeof(uint64_t),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#endif // defined(_SQ64)

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<double>
{
  enum
  {
    kTypeID = kScriptVarTypeDouble,
    kTypeSize = sizeof(double),
    kTypeMask = 'n',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

#endif // defined(SQUSEDOUBLE)
/// \endcond

} // namespace sqb

#include <sqbind/sqbTypeInfo.inl>
