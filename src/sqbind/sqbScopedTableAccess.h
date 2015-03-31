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
#include <squirrel.h>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbAssert.h>
#include <sqbind/sqbSquirrelObject.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ScopedTableAccess
{
public:
  ScopedTableAccess(HSQUIRRELVM vm, HSQOBJECT object);
  ScopedTableAccess(const SquirrelObject &object);

  ~ScopedTableAccess();

  /// \brief Return the size of the array.
  SQInteger GetSize() const;

  /// \brief Clears the contents of the array.
  void Clear();

  template<typename KeyType>
  bool SlotExists(KeyType key) const;
  bool SlotExists(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  bool RawSlotExists(KeyType key) const;
  bool RawSlotExists(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  SQObjectType GetSlotType(KeyType key) const;
  SQObjectType GetSlotType(const SQChar *key, SQInteger keyLength) const;

  template<typename KeyType>
  SQObjectType RawGetSlotType(KeyType key) const;
  SQObjectType RawGetSlotType(const SQChar *key, SQInteger keyLength) const;

  /// \brief .
  template<typename KeyType, typename ValueType>
  SQRESULT NewSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT NewSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  template<typename KeyType>
  SQRESULT NewSlotNewArray(KeyType key, SQInteger arraySize);
  SQRESULT NewSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize);

  template<typename KeyType>
  SQRESULT NewSlotNewTable(KeyType key);
  SQRESULT NewSlotNewTable(const SQChar *key, SQInteger keyLength);

  /// \brief .
  template<typename KeyType>
  SQRESULT DeleteSlot(KeyType key);
  template<typename KeyType, typename ValueType>
  SQRESULT DeleteSlot(KeyType key, ValueType *value = nullptr);

  /// \brief .
  template<typename KeyType>
  SQRESULT RawDeleteSlot(KeyType key);
  template<typename KeyType, typename ValueType>
  SQRESULT RawDeleteSlot(KeyType key, ValueType *value);

  /// \brief Get the value at the given index, this will invoke the tables delegate if there is one.
  template<typename KeyType, typename ValueType>
  SQRESULT GetSlot(KeyType key, ValueType *value) const;
  template<typename ValueType>
  SQRESULT GetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const;

  /// \brief Get the value at the given index.
  template<typename KeyType, typename ValueType>
  SQRESULT RawGetSlot(KeyType key, ValueType *value) const;
  template<typename ValueType>
  SQRESULT RawGetSlot(const SQChar *key, SQInteger keyLength, ValueType *value) const;

  /// \brief Set the value at the given index, this will invoke the tables delegate if there is one.
  ///   If the slot does not exist then this call will fail.
  template<typename KeyType, typename ValueType>
  SQRESULT SetSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT SetSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  template<typename KeyType>
  SQRESULT SetSlotNewArray(KeyType key, SQInteger arraySize);
  SQRESULT SetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arraySize);

  template<typename KeyType>
  SQRESULT SetSlotNewTable(KeyType key);
  SQRESULT SetSlotNewTable(const SQChar *key, SQInteger keyLength);

  /// \brief Set the value at the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType, typename ValueType>
  SQRESULT RawSetSlot(KeyType key, ValueType value);
  template<typename ValueType>
  SQRESULT RawSetSlot(const SQChar *key, SQInteger keyLength, ValueType value);

  /// \brief Creates a new table for the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType>
  SQRESULT RawSetSlotNewArray(KeyType key, SQInteger arrayLength);
  SQRESULT RawSetSlotNewArray(const SQChar *key, SQInteger keyLength, SQInteger arrayLength);

  /// \brief Creates a new table for the given index, this bypasses invoking the table delegate.
  ///   If the slot doesn't exist it will be created.
  template<typename KeyType>
  SQRESULT RawSetSlotNewTable(KeyType key);
  SQRESULT RawSetSlotNewTable(const SQChar *key, SQInteger keyLength);

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

} // namespace sqb

#include <sqbind/sqbScopedTableAccess.inl>
