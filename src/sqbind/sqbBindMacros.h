#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2012 James Whitworth
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbClassHelpers.h>
#include <sqbind/sqbClassTypeTag.h>
#include <sqbind/sqbStackHandler.h>
#include <sqbind/sqbStackUtils.h>
#include <sqbind/sqbTypeInfo.h>
//----------------------------------------------------------------------------------------------------------------------

/*lint -emacro(19,SQBIND_DECLARE_TYPEINFO)*/
/*lint -emacro(1576,SQBIND_DECLARE_TYPEINFO)*/
/*lint -emacro(1577,SQBIND_DECLARE_TYPEINFO)*/

/*lint -emacro(19,SQBIND_DECLARE_CLASS_BASE)*/
/*lint -emacro(1576,SQBIND_DECLARE_CLASS_BASE)*/
/*lint -emacro(1577,SQBIND_DECLARE_CLASS_BASE)*/

/*lint -emacro(19,SQBIND_DECLARE_CLASS_NAME)*/
/*lint -emacro(1576,SQBIND_DECLARE_CLASS_NAME)*/
/*lint -emacro(1577,SQBIND_DECLARE_CLASS_NAME)*/

/*lint -emacro(19,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/
/*lint -emacro(1576,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/
/*lint -emacro(1577,SQBIND_DECLARE_CUSTOM_CLASS_NAME)*/

/// \defgroup CLASS_DECLARATION Binding types
/// Macros for binding types to script.

/// @{

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_BASE(TYPE, NAME)
/// \brief Declares the Match and Get function specialisations for a class type so functions with TYPE as
/// arguments or returning TYPE can be automatically bound to script. Does not define any Push specialisations.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_BASE(TYPE, NAME) \
  SQBIND_DECLARE_TYPEINFO(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return ((sq_gettype(vm, idx) == OT_NULL) || (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK)); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<const TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return ((sq_gettype(vm, idx) == OT_NULL) || (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK)); \
  } \
  template<> \
  inline bool Match<TYPE>(TypeWrapper<const TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (idx < 0 ? -idx : idx)); \
    SQUserPointer up; \
    return (sq_getinstanceup(vm, idx, &up, ClassTypeTag<TYPE>::Get()) == SQ_OK); \
  } \
  template<> \
  inline TYPE &Get<TYPE>(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline TYPE *Get<TYPE>(TypeWrapper<TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    if (sq_gettype(vm, idx) == OT_NULL) \
    { \
      return 0; \
    } \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline TYPE &Get<TYPE>(TypeWrapper<TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<TYPE *>(up); \
  } \
  template<> \
  inline const TYPE *Get<TYPE>(TypeWrapper<const TYPE *>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    if (sq_gettype(vm, idx) == OT_NULL) \
    { \
      return 0; \
    } \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return reinterpret_cast<const TYPE *>(up); \
  } \
  template<> \
  inline const TYPE &Get<TYPE>(TypeWrapper<const TYPE &>, HSQUIRRELVM vm, SQInteger idx) \
  { \
    SQUserPointer up; \
    SQBIND_ASSERT(Match<TYPE>(TypeWrapper<TYPE *>(), vm, idx)); \
    sq_getinstanceup(vm, idx, &up, nullptr); \
    return *reinterpret_cast<const TYPE *>(up); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and also defines two specialisations of Push for TYPE* and const TYPE* types.
/// These will be bound with no release hook as they are pointers and so have been created somewhere externally.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value) \
  { \
    return internal::BaseClassStackHelper<false>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value) \
  { \
    return internal::BaseClassStackHelper<false>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with ClassUserDataClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value) \
  { \
    return internal::ClassUserDataStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value) \
  { \
    return internal::ClassUserDataStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with SqMallocClassDefinition.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value) \
  { \
    return internal::SqMallocStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value) \
  { \
    return internal::SqMallocStackHelper<traits::IsCopyable<TYPE>::kValue>::Push<TYPE>(vm, value); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and defines all Push overloads. Pushing references types will fail,
///   pushing pointer types will be the same as the base type but with the release hook set.
/// Should be used if a class is bound with NonCopyableClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, NAME) \
  SQBIND_TYPE_NON_COPYABLE(TYPE); \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value) \
  { \
  return internal::BaseClassStackHelper<true>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value) \
  { \
  return internal::BaseClassStackHelper<true>::Push<TYPE>(vm, value); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE2 and defines the remaining Push overloads for Type& and const Type&.
/// Should be used if a class is bound with NonCopyableClassDef.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, NAME) \
  SQBIND_TYPE_NON_COPYABLE(TYPE); \
  SQBIND_DECLARE_CLASS_BASE2(TYPE, NAME); \
  namespace sqb \
  { \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  template<> \
  inline SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &SQBIND_UNUSED(value)) \
  { \
    SQBIND_ASSERT_FAIL(); \
    return sq_throwerror(vm, "cannot push copy of non copyable type"); \
  } \
  }

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, NAME)
/// \brief Calls SQBIND_DECLARE_CLASS_BASE and only declares all Push overloads Type. A custom implementation for
/// all four overloads must be defined elsewhere within the program.
/// Should be used if a class is bound using a custom method.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASS_BASE(TYPE, NAME) \
  namespace sqb \
  { \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE *value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, TYPE &value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE *value); \
  template<> \
  SQRESULT Push<TYPE>(HSQUIRRELVM vm, const TYPE &value); \
  }


//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASSUD_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_CLASSUD_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASSUD_CLASS(TYPE) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_SQMALLOC_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_SQMALLOC_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_SQMALLOC_CLASS(TYPE) \
  SQBIND_DECLARE_SQMALLOC_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS_NAME(TYPE, NAME)
/// \brief Calls the recommended method of declaring a named class type. Currently SQBIND_DECLARE_CLASSUD_CLASS_NAME
/// though this is subject to change.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS_NAME(TYPE, NAME) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, NAME)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CLASS(TYPE)
/// \brief Calls the recommended method of declaring a class type. Currently SQBIND_DECLARE_CLASSUD_CLASS
/// though this is subject to change.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CLASS(TYPE) \
  SQBIND_DECLARE_CLASSUD_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_AUTO_RELEASE_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_AUTO_RELEASE_CLASS(TYPE) \
  SQBIND_DECLARE_AUTO_RELEASE_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_NON_COPYABLE_CLASS(TYPE)
/// \brief Calls SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME with TYPE as the name of the class.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_NON_COPYABLE_CLASS(TYPE) \
  SQBIND_DECLARE_NON_COPYABLE_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_CUSTOM_CLASS(TYPE)
/// \brief Declare a type without specialising sqb#Push, the types name will be TYPE.
/// \note sqb#Push must be manually defined elsewhere.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_CUSTOM_CLASS(TYPE) \
  SQBIND_DECLARE_CUSTOM_CLASS_NAME(TYPE, TYPE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_DECLARE_ENUM(TYPE)
/// \brief Declares an enum type by providing specialisations to sqb#Push, sqb#Match and sqb#Get.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_DECLARE_ENUM(TYPE) \
  namespace sqb \
  { \
  template<> \
  struct TypeInfo<TYPE> \
  { \
    enum \
    { \
      kTypeID = kScriptVarTypeInt32, \
      kTypeSize = sizeof(TYPE), \
      kTypeMask = 'n', \
      kTypeIsInstance = SQFalse, \
    }; \
    const SQChar *m_typeName; \
    inline TypeInfo() \
    : m_typeName(_SC("integer")) \
    { \
    } \
    inline operator ScriptVarType() const \
    { \
      return static_cast<ScriptVarType>(kTypeID); \
    } \
  }; \
  inline SQRESULT Push(HSQUIRRELVM vm, TYPE value) \
  { \
    sq_pushinteger(vm, static_cast<SQInteger>(value)); \
    return 1; \
  } \
  inline bool Match(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger index) \
  { \
    SQBIND_ASSERT(sq_gettop(vm) >= (index < 0 ? -index : index)); \
    return ((sq_gettype(vm, index) & SQOBJECT_NUMERIC) == SQOBJECT_NUMERIC); \
  } \
  inline TYPE Get(TypeWrapper<TYPE>, HSQUIRRELVM vm, SQInteger index) \
  { \
    SQInteger value = 0; \
    SQRESULT result = sq_getinteger(vm, index, &value); \
    SQBIND_ASSERT_SUCCEEDED(result); \
    return static_cast<TYPE>(value); \
  } \
  }

/// @}

/// \internal

namespace sqb
{
namespace internal
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool RequiresReleaseHook>
struct BaseClassStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType *value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType *value);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
struct ClassUserDataStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType &value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType &value);
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief
//----------------------------------------------------------------------------------------------------------------------
template<bool IsCopyable>
struct SqMallocStackHelper
{
  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, InstanceType &value);

  template<typename InstanceType>
  static SQRESULT Push(HSQUIRRELVM vm, const InstanceType &value);
};

} // namespace internal

} // namespace sqb

/// \endinternal

#include <sqbind/sqbBindMacros.inl>
