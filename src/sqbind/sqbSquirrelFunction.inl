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
// SquirrelFunction
//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelFunction::SetVM(HSQUIRRELVM vm)
{
  HSQUIRRELVM result = m_vm;
  m_vm = vm;
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelFunction::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline SQInteger SquirrelFunction::GetArgumentCount() const
{
  ScopedArrayAccess access(m_arguments);
  return access.GetSize();
}

//----------------------------------------------------------------------------------------------------------------------
inline void SquirrelFunction::ClearArguments()
{
  ScopedArrayAccess access(m_arguments);
  access.Clear();
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::AddArgument(ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.AppendElement(argument);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::InsertArgument(SQInteger index, ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.InsertElement(index, argument);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ArgumentType>
inline void SquirrelFunction::OverwriteArgument(SQInteger index, ArgumentType argument)
{
  ScopedArrayAccess access(m_arguments);
  access.SetElement(index, argument);
}

//----------------------------------------------------------------------------------------------------------------------
inline void SquirrelFunction::RemoveArgument(SQInteger index)
{
  ScopedArrayAccess access(m_arguments);
  access.RemoveElement(index);
}

//----------------------------------------------------------------------------------------------------------------------
inline SQObjectType SquirrelFunction::GetReturnType() const
{
  return m_returnValue.GetType();
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ResultType>
inline const ResultType& SquirrelFunction::GetReturnValue() const
{
  sq_pushobject(m_vm, m_returnValue);
  const ResultType& returnValue = Get(TypeWrapper<ResultType>(), m_vm, -1);
  sq_poptop(m_vm);
  return returnValue;
}

} // namespace sqb
