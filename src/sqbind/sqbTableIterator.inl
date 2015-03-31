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
# define SQBIND_ASSERT_ITERATOR_VALID(SQBIND_TABLE_INDEX, SQBIND_ITERATOR_INDEX) \
  SQBIND_ASSERT(sq_gettype(m_vm, SQBIND_ITERATOR_INDEX) == OT_NULL || sq_gettype(m_vm, SQBIND_ITERATOR_INDEX) == OT_INTEGER); \
  SQBIND_ASSERT(sq_gettype(m_vm, SQBIND_TABLE_INDEX) == OT_TABLE); \
  sq_push(m_vm, SQBIND_TABLE_INDEX); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_pop(m_vm, 2)
#else
# define SQBIND_ASSERT_ITERATOR_VALID(SQBIND_TABLE_INDEX, SQBIND_ITERATOR_INDEX)
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// TableIterator
//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType TableIterator::GetKeyType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  return sq_gettype(m_vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool TableIterator::IsKeyInstanceOfType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, -2, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline void TableIterator::GetKey(KeyType *key) const
{
  SQBIND_ASSERT(key != nullptr);
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  *key = Get(TypeWrapper<KeyType>(), m_vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType TableIterator::GetValueType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  return sq_gettype(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool TableIterator::IsValueInstanceOfType() const
{
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  SQUserPointer up;
  SQUserPointer typetag = ClassTypeTag<ClassType>::Get();
  SQRESULT result = sq_getinstanceup(m_vm, -1, &up, typetag);
  return SQ_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline void TableIterator::GetValue(ValueType *value) const
{
  SQBIND_ASSERT(value != nullptr);
  SQBIND_ASSERT(m_state == kIterationInProgress);
  SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
  *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
}

} // namespace sqb
