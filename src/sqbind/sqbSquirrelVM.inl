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
// CompilationOptions
//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions::CompilationOptions()
: m_sourceName(nullptr),
  m_printError(true)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions &CompilationOptions::SourceName(const SQChar *sourceName)
{
  m_sourceName = sourceName;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline CompilationOptions &CompilationOptions::PrintError(bool printError)
{
  m_printError = printError;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
inline ExecutionOptions::ExecutionOptions()
: m_raiseError(true)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline ExecutionOptions &ExecutionOptions::RaiseError(bool raiseError)
{
  m_raiseError = raiseError;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
// SquirrelVM
//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM()
: m_vm(nullptr)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM(InitialisationOptions::Flags flags)
: m_vm(nullptr)
{
  Initialise(flags);
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::SquirrelVM(HSQUIRRELVM vm)
: m_vm(vm)
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::~SquirrelVM()
{
}

//----------------------------------------------------------------------------------------------------------------------
inline SquirrelVM::operator HSQUIRRELVM () const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelVM::SetVM(HSQUIRRELVM vm)
{
  HSQUIRRELVM result = m_vm;
  m_vm = vm;
  return result;
}

//----------------------------------------------------------------------------------------------------------------------
inline HSQUIRRELVM SquirrelVM::GetVM() const
{
  return m_vm;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelVM::IsInitialised() const
{
  return m_vm != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
inline bool SquirrelVM::SetPrintFunction(SQPRINTFUNCTION printFunction)
{
  if (m_vm)
  {
    sq_setprintfunc(m_vm, printFunction, printFunction);
    return true;
  }

  return false;
}

} // namespace sqb
