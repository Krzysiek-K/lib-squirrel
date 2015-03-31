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
#include <sqbind/sqbTypeInfo.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief Default function used as _typeof metamethod func of classes bound with #RegisterClassType.
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
SQInteger TypeOf(HSQUIRRELVM vm);

//----------------------------------------------------------------------------------------------------------------------
/// \brief Creates an instance of classObject and set its release hook without invoking the constructor.
/// Resulting instance is left on the top of the stack. The function will fail if classObject is not of
/// type OT_CLASS or the call to sq_createinstance fails. If the call to sq_createinstance fails then
/// the error can be retrieved by getting the last error for the vm.
//----------------------------------------------------------------------------------------------------------------------
SQBIND_API bool CreateNativeClassInstance(HSQUIRRELVM vm, HSQOBJECT classObject, SQRELEASEHOOK hook);

}

#include <sqbind/sqbClassHelpers.inl>
