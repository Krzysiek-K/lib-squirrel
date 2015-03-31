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

/// \defgroup typetraits Class type traits
//@{

namespace sqb
{
namespace traits
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief This helper struct defines whether a class is a pod type. When an instance of a bound pod class is
/// released there is no need to call its destructor. For classes bound using ClassUserDataClassDef this means
/// there is no need for a release hook at all. For classes bound using SqMallocClassDef there is only a need
/// to call sq_free. There is no way to automatically check if a class is a pod type so classes must be declared
/// as such using DECLARE_TYPE_POD.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsPod { enum { kValue = false }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to query whether a type is copyable. To make a type non-copyable specialise this class
/// or use the macros #SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME or #SQBIND_DECLARE_NON_COPYABLE_CLASS.
/// Copyable types will use the assignment operator to copy them, non-copyable types by default will use
/// memcpy and sizeof(T). To change the copy operation of a type specialise ClassTypeCopyImpl before
/// declaring the type.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsCopyable { enum { kValue = true }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief This helper struct defines whether a class is aligned or not.
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
struct IsAligned { enum { kIsAligned = false, kAlignment = 4, }; };

//----------------------------------------------------------------------------------------------------------------------
/// \brief Used to remove const, pointer and reference qualifiers from a given type. Used when querying
/// information about a type with TypeInfo and other traits classes.
//----------------------------------------------------------------------------------------------------------------------
template<typename Type>
struct RemoveQualifiers { typedef Type kType; };

} // namespace traits

} // namespace sqb

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_POD(TYPE)
/// \brief Informs sqbind a class is a pod type, this means the binding code can optimise the class by simplifying
/// or in some cases removing each instances release hook. This does not affect the behaviour of Push so if the release
/// hook is set manually using ClassType::SetReleaseHook it will still be set for each instance of classes created with
/// Push(const MyClass&).
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_POD(TYPE) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsPod<TYPE> { enum { kValue = true }; }; \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_NON_COPYABLE(TYPE)
/// \brief 
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_NON_COPYABLE(TYPE) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsCopyable<TYPE> { enum { kValue = false }; }; \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TYPE_ALIGNED(TYPE, ALIGNMENT)
/// \brief Declares a class type to be aligned.
/// \note Alignment currently only works with classes declared with SQBIND_DECLARE_CLASS and ClassDefinition or
///   SQBIND_DECLARE_CLASSUD_CLASS and ClassUserDataClassDefinition. Instances bound with the other macros/class
///   definitions will not be aligned.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_TYPE_ALIGNED(TYPE, ALIGNMENT) \
  namespace sqb \
  { \
  namespace traits \
  { \
  template<> \
  struct IsAligned<TYPE> { enum { kIsAligned = true, kAlignment = ALIGNMENT, }; }; \
  } \
  }

//@}

#include <sqbind/sqbTypeTraits.inl>
