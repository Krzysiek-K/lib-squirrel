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
# define SQBIND_ASSERT_TABLE_SCOPE_VALID() \
  SQBIND_ASSERT(sq_gettype(m_vm, -1) == OT_TABLE); \
  sq_pushobject(m_vm, m_object); \
  SQBIND_ASSERT(sq_cmp(m_vm) == 0); \
  sq_poptop(m_vm)
#else
# define SQBIND_ASSERT_TABLE_SCOPE_VALID()
#endif

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// ScopedTableAccess
//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::ScopedTableAccess(HSQUIRRELVM vm, HSQOBJECT object)
: m_vm(vm),
  m_object(object)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::ScopedTableAccess(const SquirrelObject &object)
: m_vm(object.GetVM()),
  m_object(object.GetObject())
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
}

//----------------------------------------------------------------------------------------------------------------------
inline ScopedTableAccess::~ScopedTableAccess()
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_poptop(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger ScopedTableAccess::GetSize() const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  return sq_getsize(m_vm, -1);
}

//----------------------------------------------------------------------------------------------------------------------
inline void ScopedTableAccess::Clear()
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = sq_clear(m_vm, -1);
  SQBIND_ASSERT_SUCCEEDED(result);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline bool ScopedTableAccess::SlotExists(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline bool ScopedTableAccess::SlotExists(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline bool ScopedTableAccess::RawSlotExists(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
inline bool ScopedTableAccess::RawSlotExists(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    sq_poptop(m_vm);
    return true;
  }
  else
  {
    return false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQObjectType ScopedTableAccess::GetSlotType(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedTableAccess::GetSlotType(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);

  if (SQ_SUCCEEDED(sq_get(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQObjectType ScopedTableAccess::RawGetSlotType(KeyType key) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType ScopedTableAccess::RawGetSlotType(const SQChar *key, SQInteger keyLength) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);

  if (SQ_SUCCEEDED(sq_rawget(m_vm, -2)))
  {
    SQObjectType type = sq_gettype(m_vm, -1);
    sq_poptop(m_vm);
    return type;
  }

  return OT_NULL;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::NewSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::NewSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::NewSlotNewArray(KeyType key, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arraySize);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::NewSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arraySize);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::NewSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::NewSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  return sq_newslot(m_vm, -3, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::DeleteSlot(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_deleteslot(m_vm, -2, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::DeleteSlot(KeyType key, ValueType *value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (value != nullptr)
  {
    result = sq_deleteslot(m_vm, -2, SQTrue);
    if (SQ_SUCCEEDED(result))
    {
      *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
      sq_poptop(m_vm);
    }
  }
  else
  {
    result = sq_deleteslot(m_vm, -2, SQFalse);
  }

  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawDeleteSlot(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_deleteslot(m_vm, -2, SQFalse);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawDeleteSlot(KeyType key, ValueType *value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);

  result = sq_deleteslot(m_vm, -2, SQTrue);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::GetSlot(KeyType key, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_get(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::GetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = sq_get(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawGetSlot(KeyType key, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_rawget(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::RawGetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = sq_rawget(m_vm, -2);
  if (SQ_SUCCEEDED(result))
  {
    *value = Get(TypeWrapper<ValueType>(), m_vm, -1);
    sq_poptop(m_vm);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::SetSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::SetSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::SetSlotNewArray(KeyType key, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arraySize);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::SetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arraySize);
  SQRESULT result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::SetSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::SetSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  SQRESULT result = sq_set(m_vm, -3);
  if (SQ_FAILED(result))
  {
    sq_pop(m_vm, 2);
  }
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType, typename ValueType>
inline SQRESULT ScopedTableAccess::RawSetSlot(KeyType key, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
inline SQRESULT ScopedTableAccess::RawSetSlot(const SQChar *key, SQInteger keyLength, ValueType value)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  SQRESULT result = Push(m_vm, value);
  SQBIND_ASSERT_SUCCEEDED(result);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawSetSlotNewArray(KeyType key, SQInteger arrayLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newarray(m_vm, arrayLength);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::RawSetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arrayLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newarray(m_vm, arrayLength);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename KeyType>
inline SQRESULT ScopedTableAccess::RawSetSlotNewTable(KeyType key)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  SQRESULT result = Push(m_vm, key);
  SQBIND_ASSERT_SUCCEEDED(result);
  sq_newtable(m_vm);
  return sq_rawset(m_vm, -3);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRESULT ScopedTableAccess::RawSetSlotNewTable(const SQChar *key, SQInteger keyLength)
{
  SQBIND_ASSERT_TABLE_SCOPE_VALID();
  sq_pushstring(m_vm, key, keyLength);
  sq_newtable(m_vm);
  return sq_rawset(m_vm, -3);
}

} // namespace sqb
