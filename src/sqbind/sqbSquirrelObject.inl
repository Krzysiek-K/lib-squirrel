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
// SquirrelObject
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject()
: m_vm(nullptr)
{
  sq_resetobject(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(HSQUIRRELVM vm, SQInteger index)
{
  m_vm = vm;
  SQRESULT result = sq_getstackobj(vm, index, &m_object);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_addref(m_vm, &m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(HSQUIRRELVM vm, HSQOBJECT object)
{
  m_vm = vm;
  m_object = object;
  sq_addref(vm, &m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::SquirrelObject(const SquirrelObject& rhs)
: m_vm(rhs.m_vm),
  m_object(rhs.m_object)
{
  if (m_vm)
  {
    sq_addref(m_vm, &m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::~SquirrelObject()
{
  // release the object reference
  //
  if (m_vm)
  {
    sq_release(m_vm, &m_object);
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject::operator HSQOBJECT () const
{
  return m_object;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQOBJECT SquirrelObject::GetObject() const
{
  return m_object;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelObject::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType SquirrelObject::GetType() const
{
  return sq_type(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *SquirrelObject::GetTypeName() const
{
  SQObjectType objectType = sq_type(m_object);
  return RawTypeToTypeName(objectType);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsBool() const
{
  return sq_isbool(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsFloat() const
{
  return sq_isfloat(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsInteger() const
{
  return sq_isinteger(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsNull() const
{
  return sq_isnull(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsString() const
{
  return sq_isstring(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::IsTable() const
{
  return sq_istable(m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelObject::AsBool() const
{
  return (sq_objtobool(&m_object) == SQTrue);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQFloat SquirrelObject::AsFloat() const
{
  return sq_objtofloat(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger SquirrelObject::AsInteger() const
{
  return sq_objtointeger(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *SquirrelObject::AsString() const
{
  return sq_objtostring(&m_object);
}

//----------------------------------------------------------------------------------------------------------------------
// TypeInfo<SquirrelObject>
//----------------------------------------------------------------------------------------------------------------------
inline TypeInfo<SquirrelObject>::TypeInfo()
: m_typeName(_SC("object"))
{
}

//----------------------------------------------------------------------------------------------------------------------
// Push
//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT Push(HSQUIRRELVM vm, SquirrelObject value)
{
  sq_pushobject(vm, value);
  return 1;
}

//----------------------------------------------------------------------------------------------------------------------
// Match
//----------------------------------------------------------------------------------------------------------------------
inline bool Match(
  TypeWrapper<SquirrelObject> SQBIND_UNUSED(wrapper),
  HSQUIRRELVM                 SQBIND_UNUSED(vm),
  SQInteger                   SQBIND_UNUSED(index))
{
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
// Get
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelObject Get(TypeWrapper<SquirrelObject> SQBIND_UNUSED(wrapper), HSQUIRRELVM vm, SQInteger index)
{
  SquirrelObject value(vm, index);
  return value;
}

} // namespace sqb
