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
#include "sqbPrecompiled.h"
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/sqbTableIterator.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
// TableIterator
//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(HSQUIRRELVM vm, SQInteger tableIndex)
: m_vm(vm),
  m_state(kIterationNotStarted)
{
  sq_getstackobj(m_vm, tableIndex, &m_object);
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(HSQUIRRELVM vm, HSQOBJECT tableObject)
: m_vm(vm),
  m_object(tableObject),
  m_state(kIterationNotStarted)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::TableIterator(const SquirrelObject& tableObject)
: m_vm(tableObject.GetVM()),
  m_object(tableObject.GetObject()),
  m_state(kIterationNotStarted)
{
  SQBIND_ASSERT(sq_type(m_object) == OT_TABLE);
  sq_pushobject(m_vm, m_object);
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
TableIterator::~TableIterator()
{
  // clean up the stack
  //
  switch (m_state)
  {
  case kIterationNotStarted:
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    sq_pop(m_vm, 2);
    break;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    sq_pop(m_vm, 4);
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void TableIterator::Reset()
{
  // get rid of the current iterator
  //
  switch (m_state)
  {
  case kIterationNotStarted:
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    sq_poptop(m_vm);
    break;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    sq_pop(m_vm, 3);
    break;
  }

  // setup for first iteration
  //
  m_state = kIterationNotStarted;
  sq_pushnull(m_vm);
}

//----------------------------------------------------------------------------------------------------------------------
bool TableIterator::Next()
{
  // get rid of the current iterator
  //
  switch (m_state)
  {
  case kIterationNotStarted:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    m_state = kIterationInProgress;
    break;
  case kIterationFinished:
    SQBIND_ASSERT_ITERATOR_VALID(-2, -1);
    // early out as we have already finished iterating
    //
    return false;
  case kIterationInProgress:
    SQBIND_ASSERT_ITERATOR_VALID(-4, -3);
    // pop the previous key and value
    //
    sq_pop(m_vm, 2);
    break;
  }

  // iterate to the next slot
  //
  if (SQ_SUCCEEDED(sq_next(m_vm, -2)))
  {
    return true;
  }

  // mark iterator as finished
  //
  m_state = kIterationFinished;

  return false;
}

} // namespace sqb
