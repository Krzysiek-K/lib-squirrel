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
#include <sqbind/sqbStackUtils.h>
#include <sqbind/sqbTypeInfo.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API SquirrelObject
{
public:
  static SquirrelObject kNullObject;

  SquirrelObject();
  SquirrelObject(HSQUIRRELVM vm, SQInteger index);
  SquirrelObject(HSQUIRRELVM vm, HSQOBJECT object);
  SquirrelObject(const SquirrelObject& rhs);

  ~SquirrelObject();

  operator HSQOBJECT () const;

  const SquirrelObject &operator = (const SquirrelObject &rhs);

  HSQOBJECT GetObject() const;
  HSQUIRRELVM GetVM() const;

  void Reference(HSQUIRRELVM vm, SQInteger index);
  void Reference(HSQUIRRELVM vm, HSQOBJECT object);
  void Reference(const SquirrelObject &object);
  void Release();

  SQObjectType GetType() const;
  const SQChar *GetTypeName() const;

  bool IsBool() const;
  bool IsFloat() const;
  bool IsInteger() const;
  bool IsNull() const;
  bool IsString() const;
  bool IsTable() const;

  bool          AsBool() const;
  SQFloat       AsFloat() const;
  SQInteger     AsInteger() const;
  const SQChar *AsString() const;

protected:
  HSQUIRRELVM m_vm;
  HSQOBJECT   m_object;
};

//----------------------------------------------------------------------------------------------------------------------
template<>
struct TypeInfo<SquirrelObject>
{
  enum
  {
    kTypeID = kScriptVarTypeObject,
    kTypeSize = sizeof(SquirrelObject),
    kTypeMask = '.',
    kTypeIsInstance = SQFalse,
  };

  const SQChar *m_typeName;

  TypeInfo();
};

/// \brief Overload of Push stack utility function for SquirrelObject.
SQRESULT Push(HSQUIRRELVM vm, SquirrelObject value);

/// \brief Overload of Match stack utility function for SquirrelObject.
bool Match(TypeWrapper<SquirrelObject> wrapper, HSQUIRRELVM vm, SQInteger index);

/// \brief Overload of Get stack utility function for SquirrelObject.
SquirrelObject Get(TypeWrapper<SquirrelObject> wrapper, HSQUIRRELVM vm, SQInteger index);

} // namespace sqb

#include <sqbind/sqbSquirrelObject.inl>
