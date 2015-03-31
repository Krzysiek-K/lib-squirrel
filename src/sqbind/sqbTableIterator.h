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
#include <sqbind/sqbClassTypeTag.h>
#include <sqbind/sqbSquirrelObject.h>
#include <sqbind/sqbStackUtils.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API TableIterator
{
public:
  TableIterator(HSQUIRRELVM vm, SQInteger tableIndex);
  TableIterator(HSQUIRRELVM vm, HSQOBJECT tableObject);
  TableIterator(const SquirrelObject& tableObject);
  ~TableIterator();

  /// \brief Rewinds the iterator back to the start
  void Reset();

  /// \brief Iterates to the next element of the table, returns false when the iterating is complete.
  bool Next();

  SQObjectType GetKeyType() const;

  template<typename ClassType>
  bool IsKeyInstanceOfType() const;

  template<typename KeyType>
  void GetKey(KeyType *key) const;

  SQObjectType GetValueType() const;

  template<typename ClassType>
  bool IsValueInstanceOfType() const;

  template<typename ValueType>
  void GetValue(ValueType *value) const;

protected:
  /// \brief Enum to describe the current state of the iterator.
  /// \note Enum is in this order so when they are in order in a switch kIterationNotStarted and
  ///   kIterationFinished are next to each other and can share the same code path.
  enum IterationState
  {
    kIterationNotStarted,
    kIterationFinished,
    kIterationInProgress,
  };

  HSQUIRRELVM     m_vm;
  HSQOBJECT       m_object;
  IterationState  m_state;
};

} // namespace sqb

#include <sqbind/sqbTableIterator.inl>
