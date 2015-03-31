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
#include <cassert>
#include <cstdlib>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbBaseHeader.h>
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERTS_ENABLED
/// \brief Define this to enable asserts, by default it is defined if _DEBUG is enabled.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERTS_ENABLED)
# if defined(_DEBUG)
#  define SQBIND_ASSERTS_ENABLED 1
# else
#  define SQBIND_ASSERTS_ENABLED 0
# endif // defined(_DEBUG)
#endif // !defined(SQBIND_ASSERTS_ENABLED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BREAK()
/// \brief Use this to break program execution
/// \code
/// int i = 0;
/// SQBIND_BREAK(); // program execution will halt here
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_BREAK)
# if defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1300)
#  define SQBIND_BREAK() __debugbreak()
# elif defined(SQBIND_COMPILER_GCC)
#  define SQBIND_BREAK() __builtin_trap()
# else
#  define SQBIND_BREAK() assert(false)
# endif // defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1300)
#endif // !defined(SQBIND_BREAK)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_EXIT(RETURN_CODE)
/// \brief Use this to exit program execution
/// \code
/// int i = 0;
/// SQBIND_EXIT(10); // program will exit returning 10 here
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_EXIT)
# define SQBIND_EXIT(__SQBIND_RETURN_CODE__) exit(__SQBIND_RETURN_CODE__)
#endif

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_BEGIN_MULTILINE_MACRO
/// \brief Helper function for wrapping multi line macros in a do while loop
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_BEGIN_MULTILINE_MACRO)
# if defined(SQBIND_COMPILER_MSVC)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  __pragma(warning(push)) \
  __pragma(warning(disable:4127)) \
  do \
  {
# elif defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION > 40400)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  _Pragma("GCC diagnostic push") \
  _Pragma("GCC diagnostic ignored \"-Wno-unused-values\"") \
  do \
  {
# else // defined(SQBIND_COMPILER_MSVC)
# define SQBIND_BEGIN_MULTILINE_MACRO() \
  do \
  {
# endif // defined(SQBIND_COMPILER_MSVC)
#endif // !defined(SQBIND_BEGIN_MULTILINE_MACRO)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_END_MULTILINE_MACRO
/// \brief Helper function for wrapping multi line macros in a do while loop, required to stop msvc warnings
/// about constant conditionals (warning C4127).
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_END_MULTILINE_MACRO)
# if defined(SQBIND_COMPILER_MSVC)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0) \
  __pragma(warning(pop))
# elif defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION > 40400)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0) \
  _Pragma("GCC diagnostic pop")
# else // defined(defined(SQBIND_COMPILER_MSVC)
# define SQBIND_END_MULTILINE_MACRO() \
  } while(0)
# endif // defined(SQBIND_COMPILER_MSVC)
#endif // !defined(SQBIND_END_MULTILINE_MACRO)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_INTERNAL
/// \brief For internal use by other assert macros only, do not call this directly.
/// If SQBIND_ASSERTS_ENABLED is not defined this macro results in a no-op but still references the condition so there
/// are no unreferenced variable compiler errors or warnings in release code. 
/// \code
/// int result = func();
/// SQBIND_ASSERT(result); // result would be unreferenced without the sizeof code
/// \endcode
/// \note This assert is based on the article Stupid C++ Tricks: Adventures in Assert found
/// http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_INTERNAL)
# if SQBIND_ASSERTS_ENABLED != 0
#  define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
    sqb::AssertFailOp _fail_op = sqb::kAssertFailContinue; \
    if (!(__SQBIND_ASSERT_CONDITION__)) \
    { \
      _fail_op = sqb::AssertionFailure(__FILE__, __LINE__, __SQBIND_ASSERT_MESSAGE__); \
    } \
    switch (_fail_op) \
    { \
    default: \
    case sqb::kAssertFailHalt: \
      SQBIND_BREAK(); \
      break; \
    case sqb::kAssertFailExit: \
      SQBIND_EXIT(-1); \
    case sqb::kAssertFailContinue: \
      break; \
    } \
  SQBIND_END_MULTILINE_MACRO()
# else // SQBIND_ASSERTS_ENABLED != 0
// visual studio 2010 no longer treats sizeof as referencing a variable so we have to rely
// on if (false) and the optimiser taking care of the rest.
// same is true for gcc 4.4
// C4127 is conditional expression is constant warning.
#  if (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600)) || (defined(SQBIND_COMPILER_GCC) && (SQBIND_COMPILER_VERSION < 40500))
#   define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_TEST_COVERAGE_OFF(); \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
  if (false) \
  { \
    (void)(__SQBIND_ASSERT_CONDITION__); \
  } \
  SQBIND_END_MULTILINE_MACRO(); \
  SQBIND_TEST_COVERAGE_ON()
#  else // (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
#   define SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_TEST_COVERAGE_OFF(); \
  SQBIND_BEGIN_MULTILINE_MACRO(); \
    sizeof(__SQBIND_ASSERT_CONDITION__); \
  SQBIND_END_MULTILINE_MACRO(); \
  SQBIND_TEST_COVERAGE_ON()
#  endif // (defined(SQBIND_COMPILER_MSVC) && (SQBIND_COMPILER_VERSION >= 1600))
# endif // SQBIND_ASSERTS_ENABLED != 0
#endif // !defined(SQBIND_ASSERT_INTERNAL)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT(ASSERT_CONDITION)
/// \brief Use this to assert a condition is true. If asserts are enabled and SQBIND_ASSERT has not been
/// overridden externally when the condition is false this will call sqb::AssertionFailure. Depending on the
/// return value of sqb::AssertionFailure program execution can either halt, exit or continue as normal. By
/// default it will halt, to change the behaviour set the assert handler by calling sqb::SetAssertionFailureFunction
/// to something other than sqb::AssertionFailureFunctionDefault.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT)
# define SQBIND_ASSERT(__SQBIND_ASSERT_CONDITION__) \
  SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, "SQBIND_ASSERT(" #__SQBIND_ASSERT_CONDITION__ ")")
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_MSG
/// \brief Assert a condition is true also logging a message on failure.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_MSG)
# define SQBIND_ASSERT_MSG(__SQBIND_ASSERT_CONDITION__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(__SQBIND_ASSERT_CONDITION__, "SQBIND_ASSERT(" #__SQBIND_ASSERT_CONDITION__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAIL()
/// \brief Always does the current assert fail operation. Use this for always halting program execution or to make sure
/// certain code paths are never called.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAIL)
# define SQBIND_ASSERT_FAIL() \
  SQBIND_ASSERT_INTERNAL(false, "SQBIND_ASSERT_FAIL()")
#endif // !defined(SQBIND_ASSERT_FAIL)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAIL_MSG
/// \brief Perform the current assert fail op logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAIL_MSG)
# define SQBIND_ASSERT_FAIL_MSG(__SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(false, "SQBIND_ASSERT_FAIL_MSG() : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_SUCCEEDED
/// \brief Shorter and neater way of writing #SQBIND_ASSERT(SQ_SUCCEEDED(sqresult));
/// Never call a function that returns an SQRESULT inside this macro as it will not be called in release code.
/// \code
/// SQBIND_ASSERT_SUCCEEDED(sq_getinteger(vm, index, &value)); // NEVER DO THIS
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_SUCCEEDED)
# define SQBIND_ASSERT_SUCCEEDED(__SQ_RESULT__) \
  SQBIND_ASSERT_INTERNAL(SQ_SUCCEEDED(__SQ_RESULT__), "SQBIND_ASSERT_SUCCEEDED(" #__SQ_RESULT__ ")")
#endif // !defined(SQBIND_ASSERT_SUCCEEDED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_SUCCEEDED_MSG
/// \brief Assert that an SQRESULT was successful logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_SUCCEEDED_MSG)
# define SQBIND_ASSERT_SUCCEEDED_MSG(__SQ_RESULT__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(SQ_SUCCEEDED(__SQ_RESULT__), "SQBIND_ASSERT_SUCCEEDED(" #__SQ_RESULT__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT_SUCCEEDED_MSG)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAILED
/// \brief Shorter and neater way of writing #SQBIND_ASSERT(SQ_FAILED(sqresult));
/// Never call a function that returns an SQRESULT inside this macro as it will not be called in release code.
/// \code
/// SQBIND_ASSERT_FAILED(sq_getinteger(vm, index, &value)); // NEVER DO THIS
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAILED)
# define SQBIND_ASSERT_FAILED(__SQ_RESULT__) \
  SQBIND_ASSERT_INTERNAL(SQ_FAILED(__SQ_RESULT__), "SQBIND_ASSERT_FAILED(" #__SQ_RESULT__ ")")
#endif // !defined(SQBIND_ASSERT_FAILED)

//----------------------------------------------------------------------------------------------------------------------
/// \def SQBIND_ASSERT_FAILED_MSG
/// \brief Assert that an SQRESULT was unsuccessful logging an additional message.
//----------------------------------------------------------------------------------------------------------------------
#if !defined(SQBIND_ASSERT_FAILED_MSG)
# define SQBIND_ASSERT_FAILED_MSG(__SQ_RESULT__, __SQBIND_ASSERT_MESSAGE__) \
  SQBIND_ASSERT_INTERNAL(SQ_FAILED(__SQ_RESULT__), "SQBIND_ASSERT_FAILED(" #__SQ_RESULT__ ") : " __SQBIND_ASSERT_MESSAGE__)
#endif // !defined(SQBIND_ASSERT_FAILED_MSG)

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
enum AssertFailOp
{
  kAssertFailHalt,      ///< Assertion failure will halt execution.
  kAssertFailExit,      ///< Assertion failure will exit the program.
  kAssertFailContinue,  ///< Assertion failure will let the program execution continue.
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief The function signature for custom assert handler functions. Custom assert handler functions must match
/// this signature.
//----------------------------------------------------------------------------------------------------------------------
typedef AssertFailOp (*AssertFailHandlerFunction)(const char *file, size_t line, const char *message, void *userdata);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Get the current assertion failure function.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API void GetAssertionFailureFunction(AssertFailHandlerFunction *handler, void **userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Set the current assert handler function. By default this is set to sqb::AssertionFailureFunctionDefault
/// with a null user data.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API void SetAssertionFailureFunction(AssertFailHandlerFunction handler, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This function internally calls the current assert handler function and returns the desired fail operation.
/// If the current assert handler is null or SQBIND_ASSERTS_ENABLED is false then this will return kAssertFailContinue.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailure(const char *file, size_t line, const char *message);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which prints the file line and assert condition to stderr and
/// returns sqb::kAssertFailHalt.
/// \code
/// void EnableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionBreak, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionBreak(const char *file, size_t line, const char *message, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which prints the file line and assert condition to stderr and
/// returns sqb::kAssertFailExit.
/// \code
/// void EnableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionExit, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionExit(const char *file, size_t line, const char *message, void *userData);

//----------------------------------------------------------------------------------------------------------------------
/// \brief This assertion failure handler which always returns sqb::kAssertFailContinue.
/// To make sure asserts have no affect then define SQBIND_ASSERTS_ENABLED 0. This should only be used to temporarily
/// disable asserts while running.
/// \code
/// void DisableAsserts()
/// {
///   sqb::SetAssertionFailureFunction(&sqb::AssertionFailureFunctionContinue, nullptr);
/// }
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API AssertFailOp AssertionFailureFunctionContinue(const char *file, size_t line, const char *message, void *userData);

} // namespace sqb
