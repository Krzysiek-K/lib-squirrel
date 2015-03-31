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
#include <cstdio>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbAssert.h>
#include <sqbind/sqbTypeInfo.h>
#include <sqbind/sqbTypeTraits.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief For binding classes that have no base class.
//----------------------------------------------------------------------------------------------------------------------
class NoBaseClass { };

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
typedef void (*CopyInstanceFunction)(void *dst, void *src);

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API ClassTypeTagBase
{
public:
  ClassTypeTagBase();
  virtual ~ClassTypeTagBase();

  /// \brief As this class is used as a type tag it will be cast to void pointers and back again, this check
  /// should ensure that other typetags cast from void pointers are not incorrectly used as this.
  bool IsValid() const;

  /// \brief Many types cannot have offset, since "this" is the same for all base classes of
  /// an instance. Detect this, to avoid sum up base offsets all the time.
  bool MayHaveOffset() const;
  /// \brief Gets the offset to this class from the base class pointer.
  ptrdiff_t GetOffsetTo(const ClassTypeTagBase *pbase) const;

  /// \brief Get the script name of the type
  const SQChar *GetTypeName() const;

  /// \brief Sets the release hook for the class.
  /// \note Always use the instance returned by the static Get function to call this func.
  void SetReleaseHook(SQRELEASEHOOK releaseHook);
  /// \brief Get the release hook for this class.
  /// \note Always use the instance returned by the static Get function to call this func.
  SQRELEASEHOOK GetReleaseHook() const;

  /// \brief Stores the class in the vm's registry table.
  void SetClassObject(HSQUIRRELVM vm, HSQOBJECT classObject);
  /// \brief Retrieves the class from the vm's registry table. The returned object handle is not a strong
  /// reference to the class object, make sure to call sq_addref if a strong reference is needed.
  HSQOBJECT GetClassObject(HSQUIRRELVM vm) const;

  /// \brief Checks that a class userdata is exactly equal to a specific size.
  /// \note Class user data is set using sq_setclassudsize or ClassDefBase::SetUserDataSize.
  bool CheckClassUserDataSize(HSQUIRRELVM vm, SQInteger expectedSize) const;

  virtual CopyInstanceFunction GetCopyFunction() const = 0;

protected:
  /// \brief Name of type.
  const SQChar *m_name;
  /// \brief Sets the release hook for the class.
  SQRELEASEHOOK m_releaseHook;
  /// \brief pointer to base class type.
  ClassTypeTagBase *m_baseType;
  /// \brief Adjustment of this pointer between this type and its base class.
  ptrdiff_t m_offset;
  /// \brief Set to 0 for types that cannot possibly have offset.
  mutable int8_t m_mayHaveOffset;

private:
  static const int32_t m_expectedValidityCheck;
  const int32_t m_validityCheck;

  // disable copy construction
  //
  ClassTypeTagBase(const ClassTypeTagBase&);
  const ClassTypeTagBase& operator = (const ClassTypeTagBase&);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief This level handles instance copying in different ways
//----------------------------------------------------------------------------------------------------------------------
template<typename T, bool copyable>
class ClassTypeTagCopyImpl;

//----------------------------------------------------------------------------------------------------------------------
/// \brief Base class to do copying using the assignment operator.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTagCopyImpl<ClassType, true> : public ClassTypeTagBase
{
protected:
  /// \brief this works for types with assignment operator
  static void CopyInstance(ClassType *dst, ClassType *src);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Base class to do copying with memcpy
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTagCopyImpl<ClassType, false> : public ClassTypeTagBase
{
protected:
  /// \brief This will assert if possible or do nothing.
  static void CopyInstance(ClassType *dst, ClassType *src);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to get info about types.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
class ClassTypeTag : public ClassTypeTagCopyImpl<ClassType, traits::IsCopyable<ClassType>::kValue>
{
public:
  typedef ClassTypeTagCopyImpl<ClassType, traits::IsCopyable<ClassType>::kValue> ThisBaseType;

  // helps resolve unqualified names to members of the dependent base class.
  using ThisBaseType::m_baseType;
  using ThisBaseType::m_name;
  using ThisBaseType::m_offset;

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(push)
// nonstandard extension used: override specifier 'override'
#pragma warning(disable: 4481)
#endif

  /// \brief Override from ClassTypeTagBase
  CopyInstanceFunction GetCopyFunction() const SQBIND_OVERRIDE;

#if defined(SQBIND_COMPILER_MSVC)
#pragma warning(pop)
#endif

  /// \brief Sets the base class type for this type.
  /// \note Always use the instance returned by the static Get function to call this func.
  ///   Have to pass a dummy pointer to the class type to help gcc out.
  template<typename BaseClassType>
  void SetBaseClass(BaseClassType *);

  /// \brief Gets an instance of ClassType<T> to save many being created.
  static ClassTypeTag<ClassType> *Get();

protected:
  ClassTypeTag();

private:
  static ClassTypeTag m_instance;

  // copy construction and assignment are disabled
  ClassTypeTag(const ClassTypeTag &rhs);
  const ClassTypeTag &operator = (const ClassTypeTag &rhs);
};

}

#include <sqbind/sqbClassTypeTag.inl>
