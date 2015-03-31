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
inline const SQChar *RawTypeToTypeName(SQObjectType type)
{
  switch(_RAW_TYPE(type))
  {
  case _RT_NULL:
    return _SC("null");
  case _RT_INTEGER:
    return _SC("integer");
  case _RT_FLOAT:
    return _SC("float");
  case _RT_BOOL:
    return _SC("bool");
  case _RT_STRING:
    return _SC("string");
  case _RT_TABLE:
    return _SC("table");
  case _RT_ARRAY:
    return _SC("array");
  case _RT_GENERATOR:
    return _SC("generator");
  case _RT_CLOSURE:
  case _RT_NATIVECLOSURE:
    return _SC("function");
  case _RT_USERDATA:
  case _RT_USERPOINTER:
    return _SC("userdata");
  case _RT_THREAD:
    return _SC("thread");
  case _RT_CLASS:
    return _SC("class");
  case _RT_INSTANCE:
    return _SC("instance");
  case _RT_WEAKREF:
    return _SC("weakref");
  default:
    break;
  }
  return _SC("");
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<bool>
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
inline TypeInfo<T>::TypeInfo()
: m_typeName(_SC(""))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<bool>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<bool>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_BOOL))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<char>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<char>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int8_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int8_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint8_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint8_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int16_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int16_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint16_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint16_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int32_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int32_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint32_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint32_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<float>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<float>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_FLOAT))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<const SQChar*>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<const SQChar*>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_STRING))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<SQUserPointer>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<SQUserPointer>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_USERPOINTER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<HSQOBJECT>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<HSQOBJECT>::TypeInfo()
: m_typeName(_SC("object"))
{
}

#if defined(_SQ64)

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<int64_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<int64_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<uint64_t>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<uint64_t>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_INTEGER))
{
}

#endif

#if defined(SQUSEDOUBLE)

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<double>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<double>::TypeInfo()
: m_typeName(RawTypeToTypeName(OT_FLOAT))
{
}

#endif

} // namespace sqb
