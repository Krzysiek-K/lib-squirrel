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
// ClassTypeTagBase functions.
//----------------------------------------------------------------------------------------------------------------------
inline bool ClassTypeTagBase::IsValid() const
{
  return m_validityCheck == m_expectedValidityCheck;
}

//----------------------------------------------------------------------------------------------------------------------
inline const SQChar *ClassTypeTagBase::GetTypeName() const
{
  return m_name;
}

//----------------------------------------------------------------------------------------------------------------------
inline void ClassTypeTagBase::SetReleaseHook(SQRELEASEHOOK releaseHook)
{
  m_releaseHook = releaseHook;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQRELEASEHOOK ClassTypeTagBase::GetReleaseHook() const
{
  return m_releaseHook;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline void ClassTypeTagCopyImpl<ClassType, true>::CopyInstance(ClassType *dst, ClassType *src)
{
  *dst = *src;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline void ClassTypeTagCopyImpl<ClassType, false>::CopyInstance(
  ClassType *SQBIND_UNUSED(dst),
  ClassType *SQBIND_UNUSED(src))
{
  SQBIND_ASSERT_FAIL();
}

//----------------------------------------------------------------------------------------------------------------------
/// ClassTypeTag<ClassType>
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
ClassTypeTag<ClassType> ClassTypeTag<ClassType>::m_instance;

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline CopyInstanceFunction ClassTypeTag<ClassType>::GetCopyFunction() const
{
  return reinterpret_cast<CopyInstanceFunction>(&ThisBaseType::CopyInstance);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
template<typename BaseClassType>
void ClassTypeTag<ClassType>::SetBaseClass(BaseClassType *)
{
  m_baseType = ClassTypeTag<BaseClassType>::Get();

  // get the this pointer as the type ClassType (could be anything instead of this other than nullptr)
  //
  const ClassType *pt = reinterpret_cast<ClassType *>(this);
  // subtract the type pointer from the same pointer cast to the base type
  // the cast to base type offsets the pointer if there is any offset between types BC and T
  // subtracting T* from BC* for the same instance will result in the offset.
  //
  m_offset = reinterpret_cast<const char *>(pt) - reinterpret_cast<const char *>(static_cast<const BaseClassType *>(pt));
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassTypeTag<ClassType> *ClassTypeTag<ClassType>::Get()
{
  return &m_instance;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
inline ClassTypeTag<NoBaseClass> *ClassTypeTag<NoBaseClass>::Get()
{
  return nullptr;
}

// as all ClassTypeTagBase are static instances this destructor is hit after the test coverage scanning has finished
//
SQBIND_TEST_COVERAGE_OFF()
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline ClassTypeTag<ClassType>::ClassTypeTag()
{
  m_name = TypeInfo<ClassType>().m_typeName;
}
SQBIND_TEST_COVERAGE_ON()

} // namespace sqb
