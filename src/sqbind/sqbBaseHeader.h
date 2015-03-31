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

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_COMPILER_CLANG
/// \def SQBIND_COMPILER_MSVC
/// \def SQBIND_COMPILER_GCC
/// \def SQBIND_COMPILER_VERSION
//----------------------------------------------------------------------------------------------------------------------
#if defined(__clang__)
# define SQBIND_COMPILER_CLANG
# define SQBIND_COMPILER_VERSION (__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__
#elif defined(_MSC_VER)
# define SQBIND_COMPILER_MSVC
# define SQBIND_COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
# define SQBIND_COMPILER_GCC
# define SQBIND_COMPILER_VERSION (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \cond NO_DOXYGEN
#if defined(_MSC_VER) && defined(__clang__)
# undef _HAS_CHAR16_T_LANGUAGE_SUPPORT
# define _HAS_CHAR16_T_LANGUAGE_SUPPORT 0
#endif

#if defined(_MSC_VER)
// visual studio doesn't define std int types.
typedef signed __int8     int8_t;
typedef unsigned __int8   uint8_t;
typedef signed __int16    int16_t;
typedef unsigned __int16  uint16_t;
typedef signed __int32    int32_t;
typedef unsigned __int32  uint32_t;
typedef signed __int64    int64_t;
typedef unsigned __int64  uint64_t;
#else
# include <stdint.h>
# include <stddef.h>
#endif

// enable the use of nullptr for all compilers.
#if !defined(SQBIND_CPP0X_NULLPTR_SUPPORTED)
# if (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# elif (defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION >= 40600))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# elif (defined(SQBIND_COMPILER_CLANG) && __has_feature(cxx_nullptr))
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 1
# else
#  define SQBIND_CPP0X_NULLPTR_SUPPORTED 0
# endif
#endif

#if !SQBIND_CPP0X_NULLPTR_SUPPORTED
# if !defined nullptr
#  define nullptr 0
# endif
#endif
/// \endcond
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_MAJOR_VERSION
/// \brief The major version number of sqbind.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_MAJOR_VERSION 1

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_MINOR_VERSION
/// \brief The minor version number of sqbind.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_MINOR_VERSION 20

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_VERSION_NUMBER
/// \brief The combined version number of sqbind, of the form 1000.
/// The number will be (SQBIND_MAJOR_VERSION * 1000) + SQBIND_MINOR_VERSION
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_VERSION_NUMBER ((SQBIND_MAJOR_VERSION * 1000) + SQBIND_MINOR_VERSION)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_STRINGIFY_INTERNAL
/// \brief Used by SQBIND_STRINGIFY to turn macro values in to strings, never call this directly.
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_STRINGIFY_INTERNAL(SQBIND_VALUE) _SC(#SQBIND_VALUE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_STRINGIFY
/// \brief Converts a value to a string.
/// \code
/// #define NUMBER 1.0
/// // str will be _SC("1.0")
/// //
/// const SQChar* str = SQBIND_STRINGIFY(NUMBER);
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_STRINGIFY(SQBIND_VALUE) SQBIND_STRINGIFY_INTERNAL(SQBIND_VALUE)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_VERSION_STRING
/// \brief The string version number of sqbind of the form sqbind-SQBIND_MAJOR_VERSION.SQBIND_MINOR_VERSION
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_VERSION_STRING _SC("sqbind-") SQBIND_STRINGIFY(SQBIND_MAJOR_VERSION) _SC(".") SQBIND_STRINGIFY(SQBIND_MINOR_VERSION)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_OVERRIDE
/// \brief
/// \code
/// class Base
/// {
/// public:
///   virtual Func();
/// };
///
/// class Derived : public Base
/// {
/// public:
///   SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK();
///   virtual Func() SQBIND_OVERRIDE;
///   SQBIND_END_NONSTANDARD_EXTENSION_BLOCK();
/// };
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_OVERRIDE override
#else
# define SQBIND_OVERRIDE
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK
/// \brief
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK() \
  __pragma(warning(push)) \
  __pragma(warning(disable: 4481))
#else
# define SQBIND_BEGIN_NONSTANDARD_EXTENSION_BLOCK()
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_END_NONSTANDARD_EXTENSION_BLOCK
/// \brief
//----------------------------------------------------------------------------------------------------------------------
#if _MSC_VER >= 1400
# define SQBIND_END_NONSTANDARD_EXTENSION_BLOCK() \
  __pragma(warning(pop))
#else
# define SQBIND_END_NONSTANDARD_EXTENSION_BLOCK()
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_UNUSED
/// \brief Used to mark a function parameter as unused
/// \code
/// void func(int SQBIND_UNUSED(blah))
/// {
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#define SQBIND_UNUSED(X)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TEST_COVERAGE_OFF
/// \brief Disables coverage instrumentation for all code following this call. Only works in coverage builds.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_TEST_COVERAGE_OFF)
# if defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_OFF() __pragma(CoverageScanner(cov-off))
# else // defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_OFF()
# endif // defined(__COVERAGESCANNER__)
#endif // !defined(SQBIND_TEST_COVERAGE_OFF)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_TEST_COVERAGE_ON
/// \brief Pops last coverage instrumentation command resetting it to normal. Only works in coverage builds.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_TEST_COVERAGE_ON)
# if defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_ON() __pragma(CoverageScanner(cov-on))
# else // defined(__COVERAGESCANNER__)
#  define SQBIND_TEST_COVERAGE_ON()
# endif // defined(__COVERAGESCANNER__)
#endif // !defined(SQBIND_TEST_COVERAGE_ON)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_API
/// \brief Used to mark objects for export when compiling sqbind as a dll.
//----------------------------------------------------------------------------------------------------------------------
#ifndef SQBIND_API
# ifdef WIN32
#  ifndef SQBIND_STATIC
#   ifdef SQBIND_EXPORTS
#    define SQBIND_API __declspec(dllexport)
#   else
#    define SQBIND_API __declspec(dllimport)
#   endif
#  else
#   define SQBIND_API
#  endif
# else
#  define SQBIND_API
# endif
#endif
