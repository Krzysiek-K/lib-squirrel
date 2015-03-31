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
#include <sqbind/sqbBaseHeader.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Defines whether a squirrel function is static or not. Only applies to functions within a class.
//----------------------------------------------------------------------------------------------------------------------
enum FunctionStaticType
{
  kNonStaticFunctionType = SQFalse, ///< Non-static function, this applies to all non class functions as they can never
                                    ///  be static.
  kStaticFunctionType = SQTrue,     ///< Static function, this only applies to some class functions.
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief Helper class to set all the optional parameters when binding a new function.
/// \code
/// sqb::Bind::BindFunction(
///   vm,
///   -1,
///   &func,
///   SC("func"),
///   sqb::FunctionOptions()
///     .ParamCheckCount(2)
///     .TypeMask(SC(".."))
///   );
/// \endcode
//----------------------------------------------------------------------------------------------------------------------
class SQBIND_API FunctionOptions
{
public:
  /// \brief The number of free variables the new function has, these must be on the stack when the
  /// call to create function is made. The default value is 0.
  /// \note Free variables are bound the last in the stack first so the last on the stack when binding
  /// will be the first free variable on the stack when accessing them within the function.
  SQUnsignedInteger m_freeVariableCount;

  /// \brief This defines the parameter number check policy. 0 disables checking,
  /// greater than 0 means the number of parameters must exactly match, less
  /// than 0 means the function must be called with at least the absolute
  /// value number of parameters (ie. -3 would be at least 3 parameters
  /// required). The default value is 0.
  SQInteger m_paramCheckCount;

  /// \brief Parameter check type mask string. A null string means no checking.
  /// The default value is a null string.
  const SQChar *m_typeMaskString;

  /// \brief Is the function a static function, only applies to functions added to a
  /// a class object. The default value is kNonStaticFunctionType.
  FunctionStaticType m_staticType;

  FunctionOptions();

  FunctionOptions &FreeVariables(SQUnsignedInteger count);
  FunctionOptions &ParamCheckCount(SQInteger paramCheckCount);
  FunctionOptions &TypeMask(const SQChar *typeMask);
  FunctionOptions &Static(FunctionStaticType staticType);
};

}

#include <sqbind/sqbFunctionOptions.inl>
