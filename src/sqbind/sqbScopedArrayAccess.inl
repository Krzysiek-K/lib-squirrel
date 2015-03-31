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

//----------------------------------------------------------------------------------------------------------------------
// Assert to check that the object is on the top of the stack.
//----------------------------------------------------------------------------------------------------------------------
#if SQBIND_ASSERTS_ENABLED
# define SQBIND_ASSERT_ARRAY_SCOPE_VALID() \
  SQBIND_ASSERT(sq_gettype(m_vm, -1) == OT_ARRAY); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_poptop(m_vm)
#else
# define SQBIND_ASSERT_ARRAY_SCOPE_VALID()
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedArrayAccess
//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::ScopedArrayAccess(HSQUIRRELVM vm, HSQOBJECT object)
: m_vm(vm),
  m_object(object)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_ARRAY);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::ScopedArrayAccess(const SquirrelObject &object)
: m_vm(object.GetVM()),
  m_object(object.GetObject())
{
  SQBIND_ASSERT(sq_type(m_object) == OT_ARRAY);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedArrayAccess::~ScopedArrayAccess()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger ScopedArrayAccess::GetSize() const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  return sq_getsize(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::Resize(SQInteger size)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arrayresize(m_vm, -1, size);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::Clear()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_clear(m_vm, -1);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedArrayAccess::GetElementType(SQInteger index) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, index);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQObjectType type = sq_gettype(m_vm, -1);
  sq_poptop(m_vm);
  return type;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
bool ScopedArrayAccess::IsElementInstanceOfType(SQInteger index) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, index);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);

  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  result = sq_getinstanceup(m_vm, -1, &up, typetag);

  sq_poptop(m_vm);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::AppendElement(ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_arrayappend(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::InsertElement(SQInteger index, ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQBIND_ASSERT(index >= 0);
  SQBIND_ASSERT(index <= sq_getsize(m_vm, -1));
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_arrayinsert(m_vm, -2, index);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::PopElement()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arraypop(m_vm, -2, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline const ValueType &ScopedArrayAccess::PopElement()
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQRESULT result = sq_arraypop(m_vm, -2, SQTrue);
  SQBIND_ASSERT_SUCCEEDED(result);
  const ValueType &value = Get(TypeWrapper<ValueType>(), m_vm, -1);
  sq_poptop(m_vm);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedArrayAccess::RemoveElement(SQInteger index)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  SQBIND_ASSERT(index >= 0);
  SQBIND_ASSERT(index < sq_getsize(m_vm, -1));
  SQRESULT result = sq_arrayremove(m_vm, -1, index);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void ScopedArrayAccess::SetElement(SQInteger key, ValueType value)
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, key);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_rawset(m_vm, -3);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline const ValueType &ScopedArrayAccess::GetElement(SQInteger key) const
{
  SQBIND_ASSERT_ARRAY_SCOPE_VALID();
  sq_pushinteger(m_vm, key);
  SQRESULT result = sq_rawget(m_vm, -2);
  SQBIND_ASSERT_SUCCEEDED(result);
  const ValueType &value = Get(TypeWrapper<ValueType>(), m_vm, -1);
  sq_poptop(m_vm);
  return value;
}

} // namespace sqb
