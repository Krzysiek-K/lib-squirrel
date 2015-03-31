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
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ScopedArrayAccess
{
public:
  ScopedArrayAccess(HSQUIRRELVM vm, HSQOBJECT object);
  ScopedArrayAccess(const SquirrelObject &object);

  ~ScopedArrayAccess();

  /// \brief Return the size of the array.
  SQInteger GetSize() const;

  /// \brief Resize the array to size elements.
  void Resize(SQInteger size);

  /// \brief Clears the contents of the array.
  void Clear();

  /// \brief Get the type of the element at index.
  SQObjectType GetElementType(SQInteger index) const;

  template<typename InstanceType>
  bool IsElementInstanceOfType(SQInteger index) const;

  /// \brief Append a new element to the end of the array.
  template<typename ValueType>
  void AppendElement(ValueType value);

  /// \brief Insert a new element at position index of the array.
  template<typename ValueType>
  void InsertElement(SQInteger index, ValueType value);

  /// \brief Removes an element from the end of the array.
  void PopElement();

  /// \brief Removes an element from the end of the array returning the removed value.
  template<typename ValueType>
  const ValueType &PopElement();

  /// \brief Removes an element from the array at the index given.
  void RemoveElement(SQInteger index);

  /// \brief Get the element at the given index.
  template<typename ValueType>
  const ValueType &GetElement(SQInteger index) const;

  /// \brief Set the element at the given index.
  template<typename ValueType>
  void SetElement(SQInteger index, ValueType value);

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

} // namespace sqb

#include <sqbind/sqbScopedArrayAccess.inl>
