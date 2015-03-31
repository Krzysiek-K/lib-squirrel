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
#include <sqbind/sqbBind.h>
#include <sqbind/sqbStackHandler.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
const SQInteger Bind::kGetMetaMethodParamCheckCount = 2;
const SQInteger Bind::kSetMetaMethodParamCheckCount = 3;

const SQChar *Bind::kGetMetaMethodTypeMask = _SC("x|t|u s");
const SQChar *Bind::kSetMetaMethodTypeMask = _SC("x|t|u s .");

const SQInteger Bind::kThisObjectStackIndex = 1;

const SQInteger Bind::kNameStackIndex = 2;

const SQInteger Bind::kGetObjectReferencesStackIndex = 3;

const SQInteger Bind::kSetValueStackIndex = 3;
const SQInteger Bind::kSetObjectReferencesStackIndex = 4;

//----------------------------------------------------------------------------------------------------------------------
bool Bind::BindNativeFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  SQFUNCTION        function,
  const SQChar     *name,
  FunctionOptions   options)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (name == nullptr)
  {
    return false;
  }

  size_t nameLength = scstrlen(name);
  if (nameLength == 0)
  {
    return false;
  }

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    SQInteger top = sq_gettop(vm);
    objectIndex = top + objectIndex + 1;
  }

  sq_newclosure(vm, function, options.m_freeVariableCount);

  if (options.m_paramCheckCount != 0 && options.m_typeMaskString != nullptr)
  {
    if (SQ_FAILED(sq_setparamscheck(vm, options.m_paramCheckCount, options.m_typeMaskString)))
    {
      sq_poptop(vm);
      return false;
    }
  }

  // set the name used when debugging
  //
  SQRESULT result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, options.m_staticType);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetOrCreateObjectReferencesTable(HSQUIRRELVM vm, SQInteger objectIndex, SQObjectType objectType)
{
  // get the table that holds all variable references for the object we're binding to from the registry table.
  // the key is the object itself
  //
  sq_pushregistrytable(vm);
  sq_push(vm, objectIndex);

  // if there is no table then create a slot with the object being bound as the key and a new table as the value.
  //
  if (SQ_FAILED(sq_rawget(vm, -2)))
  {
    sq_newtable(vm);

    sq_push(vm, objectIndex);
    sq_push(vm, -2);
    sq_rawset(vm, -4);

    // if object is a class the delegate of the object references table must be the object references table
    // of the base class if there is one otherwise getting a member bound to a base class will fail for instances
    // of a derived class.
    //
    if (objectType == OT_CLASS)
    {
      sq_getbase(vm, objectIndex);

      if (sq_gettype(vm, objectIndex + 3) == OT_CLASS)
      {
        // do this recursively up the inheritance hierarchy
        //
        GetOrCreateObjectReferencesTable(vm, objectIndex + 3, OT_CLASS);
        sq_setdelegate(vm, objectIndex + 2);
      }

      sq_poptop(vm);
    }
  }

  // remove the registry table
  //
  sq_remove(vm, -2);
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetOrCreateObjectDelegate(HSQUIRRELVM vm, SQInteger objectIndex)
{
  // this function is only called by this class so there is no need to do any checking of arguments
  //
  SQRESULT result = sq_getdelegate(vm, objectIndex);
  SQBIND_ASSERT_SUCCEEDED(result);
  if (sq_gettype(vm, -1) == OT_NULL)
  {
    sq_poptop(vm);

    sq_newtable(vm);

    sq_push(vm, -1);
    sq_setdelegate(vm, objectIndex);
  }
}

//----------------------------------------------------------------------------------------------------------------------
bool Bind::CreateVariableReference(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  ScriptVarType   variableType,
  SQUserPointer   offsetOrAddress,
  ClassTypeTagBase  *instanceClassType,
  ClassTypeTagBase  *variableClassType,
  SQInteger       bindFlags)
{
  SQBIND_ASSERT(sq_gettype(vm, variableReferenceIndex) == OT_TABLE);

  // store the script type
  //
  if (variableType == kScriptVarTypeNone)
  {
    return false;
  }
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_pushinteger(vm, variableType);
  sq_rawset(vm, variableReferenceIndex);

  // store the offsetOrAddress
  //
  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_pushuserpointer(vm, offsetOrAddress);
  sq_rawset(vm, variableReferenceIndex);

  // if we're binding to a class instance then store the instance type
  //
  if (instanceClassType != nullptr)
  {
    SQBIND_ASSERT(instanceClassType->IsValid());

    sq_pushinteger(vm, kInstanceClassTypeKey);
    sq_pushuserpointer(vm, instanceClassType);
    sq_rawset(vm, variableReferenceIndex);
  }

  // if the variable being bound is a class then store the class type
  //
  if (variableType == kScriptVarTypeInstance)
  {
    SQBIND_ASSERT(variableClassType != nullptr);
    SQBIND_ASSERT(variableClassType->IsValid());

    sq_pushinteger(vm, kVariableClassTypeKey);
    sq_pushuserpointer(vm, variableClassType);
    sq_rawset(vm, variableReferenceIndex);
  }

  // if there were any flags then store them
  //
  if (bindFlags != kVariableNoFlags)
  {
    sq_pushinteger(vm, kFlagsKey);
    sq_pushinteger(vm, static_cast<SQInteger>(bindFlags));
    sq_rawset(vm, variableReferenceIndex);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::EnsureGetMetaMethodBound(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  SQObjectType  type,
  SQInteger     objectReferencesIndex)
{
  // this function can only be called by other static functions of this class so the parameters
  // and objects in the stack are guaranteed to be correct.
  //
  if (type != OT_CLASS)
  {
    GetOrCreateObjectDelegate(vm, objectIndex);
    objectIndex = -2;
  }

  sq_pushstring(vm, _SC("_get"), 4);
  if (SQ_FAILED(sq_rawget(vm, objectIndex)))
  {
    // there is no _set metamethod so create one
    //
    FunctionOptions options;

    // set up the param checks
    //
    options.ParamCheckCount(kGetMetaMethodParamCheckCount);
    options.TypeMask(kGetMetaMethodTypeMask);

    // push the object references table to be bound as a free variable
    //
    options.FreeVariables(1);
    sq_push(vm, objectReferencesIndex);

    if (type == OT_CLASS)
    {
      BindNativeFunction(vm, objectIndex, &GetInstanceVariableReference, _SC("_get"), options);
    }
    else
    {
      BindNativeFunction(vm, objectIndex, &GetVariableReference, _SC("_get"), options);
    }
  }
  else
  {
    SQBIND_ASSERT(sq_gettype(vm, -1) == OT_NATIVECLOSURE);

    // pop the metamethod
    //
    sq_poptop(vm);
  }

  if (type != OT_CLASS)
  {
    // pop the delegate
    //
    sq_poptop(vm);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::EnsureSetMetaMethodBound(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  SQObjectType  type,
  SQInteger     objectReferencesIndex)
{
  // this function can only be called by other static functions of this class so the parameters
  // and objects in the stack are guaranteed to be correct.
  //
  if (type != OT_CLASS)
  {
    GetOrCreateObjectDelegate(vm, objectIndex);
    objectIndex = -2;
  }

  sq_pushstring(vm, _SC("_set"), 4);
  if (SQ_FAILED(sq_rawget(vm, objectIndex)))
  {
    // there is no _set metamethod so create one
    //
    FunctionOptions options;

    // set up the param checks
    //
    options.ParamCheckCount(kSetMetaMethodParamCheckCount);
    options.TypeMask(kSetMetaMethodTypeMask);

    // push the object references table to be bound as a free variable
    //
    options.FreeVariables(1);
    sq_push(vm, objectReferencesIndex);

    if (type == OT_CLASS)
    {
      BindNativeFunction(vm, objectIndex, &SetInstanceVariableReference, _SC("_set"), options);
    }
    else
    {
      BindNativeFunction(vm, objectIndex, &SetVariableReference, _SC("_set"), options);
    }
  }
  else
  {
    SQBIND_ASSERT(sq_gettype(vm, -1) == OT_NATIVECLOSURE);

    // pop the metamethod
    //
    sq_poptop(vm);
  }

  if (type != OT_CLASS)
  {
    // pop the delegate
    //
    sq_poptop(vm);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetVariableReferenceTypeAndAddress(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  SQInteger      *variableType,
  SQUserPointer  *address)
{
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getinteger(vm, -1, variableType);
  sq_poptop(vm);

  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, address);
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
void Bind::GetVariableClassType(
  HSQUIRRELVM           vm,
  SQInteger             variableReferenceIndex,
  const ClassTypeTagBase **variableClassType)
{
  // get the variable class type from the variable reference table
  //
  sq_pushinteger(vm, kVariableClassTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, (SQUserPointer*)variableClassType);
  sq_poptop(vm);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  if (SQ_FAILED(sq_rawget(vm, kGetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_pushnull(vm);
    return sq_throwobject(vm);
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetVariableReferenceTypeAndAddress(vm, kGetObjectReferencesStackIndex + 1, &variableType, &address);
  return GetVariable(vm, kGetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  if (SQ_FAILED(sq_rawget(vm, kSetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_pushnull(vm);
    return sq_throwobject(vm);
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetVariableReferenceTypeAndAddress(vm, kSetObjectReferencesStackIndex + 1, &variableType, &address);
  return SetVariable(vm, kSetObjectReferencesStackIndex + 1, variableType, address);
}


//----------------------------------------------------------------------------------------------------------------------
void Bind::GetInstanceVariableReferenceTypeAndAddress(
  HSQUIRRELVM     vm,
  SQInteger       variableReferenceIndex,
  SQInteger      *variableType,
  SQUserPointer  *address)
{
  sq_pushinteger(vm, kScriptVarTypeKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getinteger(vm, -1, variableType);
  sq_poptop(vm);

  SQUserPointer offsetOrAddress;
  sq_pushinteger(vm, kOffsetOrAddressKey);
  sq_rawget(vm, variableReferenceIndex);
  sq_getuserpointer(vm, -1, &offsetOrAddress);
  sq_poptop(vm);

  SQInteger flags;
  sq_pushinteger(vm, kFlagsKey);
  if (SQ_SUCCEEDED(sq_rawget(vm, variableReferenceIndex)))
  {
    sq_getinteger(vm, -1, &flags);
    sq_poptop(vm);
  }
  else
  {
    flags = kVariableNoFlags;
  }

  // if the static flag isn't set then offsetOrAddress is an offset from the instance so it must be
  // adjusted to make an absolute address
  //
  if ((flags & kVariableStatic) == kVariableStatic)
  {
    *address = offsetOrAddress;
  }
  else
  {
    // get the bound class type from the variable reference table
    //
    const ClassTypeTagBase *boundInstanceType;
    sq_pushinteger(vm, kInstanceClassTypeKey);
    sq_rawget(vm, variableReferenceIndex);
    sq_getuserpointer(vm, -1, (SQUserPointer*)&boundInstanceType);
    sq_poptop(vm);

    // get the current instance and its class type, don't ask for a typetag match as the typetag
    // matching will be done by GetOffsetTo and there is no point doing it twice.
    //
    SQUserPointer thisInstance;
    sq_getinstanceup(vm, kThisObjectStackIndex, &thisInstance, nullptr);
    SQUserPointer typetag;
    sq_gettypetag(vm, kThisObjectStackIndex, &typetag);

    const ClassTypeTagBase *thisInstanceType = static_cast<const ClassTypeTagBase *>(typetag);

    // adjust for the current type potentially being a derived class type of the bound class type.
    // if the current instance class type is not the same or does not derive from the bound class type
    // this call will assert.
    //
    if (boundInstanceType != typetag && thisInstanceType->MayHaveOffset())
    {
      ptrdiff_t offset = thisInstanceType->GetOffsetTo(boundInstanceType);
      thisInstance = static_cast<uint8_t *>(thisInstance) - offset;
    }

    // finally apply the offset from the instance to the member variable
    //
    *address = static_cast<uint8_t *>(thisInstance) + reinterpret_cast<ptrdiff_t>(offsetOrAddress);
  }
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetInstanceVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  // note that sq_get is used instead of sq_rawget as the variable reference may be in a delegate
  // of the object references table if it is a member of a base class not the most derived class
  //
  if (SQ_FAILED(sq_get(vm, kGetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_reseterror(vm);
    return SQ_ERROR;
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetInstanceVariableReferenceTypeAndAddress(vm, kGetObjectReferencesStackIndex + 1, &variableType, &address);
  return GetVariable(vm, kGetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetInstanceVariableReference(HSQUIRRELVM vm)
{
  // the object references stack index is never popped by this native closure,
  // squirrel cleans up the stack when this call returns
  //
  sq_push(vm, kNameStackIndex);
  // note that sq_get is used instead of sq_rawget as the variable reference may be in a delegate
  // of the object references table if it is a member of a base class not the most derived class
  //
  if (SQ_FAILED(sq_get(vm, kSetObjectReferencesStackIndex)))
  {
    // throwing null indicates no runtime error and a clean failure of 'index not found'.
    //
#if defined(SQUIRREL_VERSION_NUMBER) && (SQUIRREL_VERSION_NUMBER >= 301)
    sq_reseterror(vm);
    return SQ_ERROR;
#else
    sq_reseterror(vm);
    return SQ_ERROR;
#endif // defined(SQUIRREL_VERSION_NUMBER) && SQUIRREL_VERSION_NUMBER >= 301
  }

  SQInteger variableType;
  SQUserPointer address;
  GetInstanceVariableReferenceTypeAndAddress(vm, kSetObjectReferencesStackIndex + 1, &variableType, &address);
  return SetVariable(vm, kSetObjectReferencesStackIndex + 1, variableType, address);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::GetVariable(
  HSQUIRRELVM   vm,
  SQInteger     variableReferenceIndex,
  SQInteger     variableType,
  SQUserPointer address)
{
  StackHandler sh(vm);
  switch (variableType)
  {
  case TypeInfo<bool>::kTypeID:
    {
      const bool *value = static_cast<const bool*>(address);
      return sh.Return(static_cast<bool>(*value));
    }
  case TypeInfo<char>::kTypeID:
    {
      const char *value = static_cast<const char*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int8_t>::kTypeID:
    {
      const int8_t *value = static_cast<const int8_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint8_t>::kTypeID:
    {
      const uint8_t *value = static_cast<const uint8_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int16_t>::kTypeID:
    {
      const int16_t *value = static_cast<const int16_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint16_t>::kTypeID:
    {
      const uint16_t *value = static_cast<const uint16_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<int32_t>::kTypeID:
    {
      const int32_t *value = static_cast<const int32_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint32_t>::kTypeID:
    {
      const uint32_t *value = static_cast<const uint32_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<float>::kTypeID:
    {
      const float *value = static_cast<const float*>(address);
      return sh.Return(static_cast<SQFloat>(*value));
    }
  case TypeInfo<const SQChar *>::kTypeID:
    {
      const SQChar *const *value = static_cast<const SQChar *const *>(address);
      return sh.Return(static_cast<const SQChar*>(*value));
    }
  case TypeInfo<SQUserPointer>::kTypeID:
    {
      SQUserPointer *value = static_cast<SQUserPointer*>(address);
      return sh.Return(*value);
    }
  case kScriptVarTypeInstance:
    {
      const ClassTypeTagBase *variableClassTypeTag = nullptr;
      GetVariableClassType(vm, variableReferenceIndex, &variableClassTypeTag);

      HSQOBJECT variableClassObject = variableClassTypeTag->GetClassObject(vm);
      sq_pushobject(vm, variableClassObject);
      if (SQ_SUCCEEDED(sq_createinstance(vm, -1)))
      {
        // remove variableClassObject from stack
        //
        sq_remove(vm, -2);
        SQUserPointer instance = static_cast<SQUserPointer>(address);
        sq_setinstanceup(vm, -1, instance);
        return 1;
      }
      // remove variableClassObject from stack
      //
      sq_poptop(vm);
      return sh.ThrowError(
        _SC("error getting variable '%s' ; check variable class type '%s' has been bound correctly"),
        sh.GetString(2),
        variableClassTypeTag->GetTypeName());
    }
#if defined(_SQ64)
  case TypeInfo<int64_t>::kTypeID:
    {
      const int64_t *value = static_cast<const int64_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
  case TypeInfo<uint64_t>::kTypeID:
    {
      const uint64_t *value = static_cast<const uint64_t*>(address);
      return sh.Return(static_cast<SQInteger>(*value));
    }
#endif
#if defined(SQUSEDOUBLE)
  case TypeInfo<double>::kTypeID:
    {
      const double *value = static_cast<const double*>(address);
      return sh.Return(static_cast<SQFloat>(*value));
    }
#endif
  default:
    break;
  }

  // annoyingly has to be outside the switch for test coverage instrumentation to work
  //
  return sh.ThrowError(
    _SC("error getting variable '%s' ; unknown variable type id '%d'"),
    sh.GetString(2),
    variableType);
}

//----------------------------------------------------------------------------------------------------------------------
SQInteger Bind::SetVariable(
  HSQUIRRELVM   vm,
  SQInteger     variableReferenceIndex,
  SQInteger     variableType,
  SQUserPointer address)
{
  StackHandler sh(vm);

  SQObjectType expectedType;
  switch (variableType)
  {
  case TypeInfo<bool>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_BOOL)
    {
      SQBool value;
      sq_getbool(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<bool*>(address) = (value == SQTrue) ? true : false;
      sq_pushbool(vm, value);
      return 1;
    }
    expectedType = OT_BOOL;
    break;
  case TypeInfo<char>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<char*>(address) = static_cast<char>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int8_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int8_t*>(address) = static_cast<int8_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint8_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint8_t*>(address) = static_cast<uint8_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int16_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int16_t*>(address) = static_cast<int16_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint16_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint16_t*>(address) = static_cast<uint16_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<int32_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int32_t*>(address) = static_cast<int32_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint32_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint32_t*>(address) = static_cast<uint32_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<float>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_FLOAT)
    {
      SQFloat value;
      sq_getfloat(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<float*>(address) = static_cast<float>(value);
      sq_pushfloat(vm, value);
      return 1;
    }
    expectedType = OT_FLOAT;
    break;
  case TypeInfo<const SQChar *>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_STRING)
    {
      const SQChar *value;
      sq_getstring(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<const SQChar **>(address) = value;
      sq_pushstring(vm, value, -1);

      // get the string references table from the variable reference table
      // if sq_rawget fails then the table doesn't exist yet so create it
      //
      sq_pushinteger(vm, kStringReferencesTableKey);
      if (SQ_FAILED(sq_rawget(vm, variableReferenceIndex)))
      {
        sq_newtable(vm);

        // push the integer and then the new table as sq_rawset will pop the key and value from the stack
        // and we need the new table to be on the stack after the call to sq_rawset.
        //
        sq_pushinteger(vm, kStringReferencesTableKey);
        sq_push(vm, -2);
        sq_rawset(vm, variableReferenceIndex);
      }

      // create a reference to the string with this object as the key so there is always a reference
      // otherwise the string may be cleaned up when it is still required
      //
      sq_push(vm, kThisObjectStackIndex);
      sq_push(vm, -3);
      sq_rawset(vm, -3);

      // remove the string references table
      //
      sq_poptop(vm);

      return 1;
    }
    expectedType = OT_STRING;
    break;
  case TypeInfo<SQUserPointer>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_USERPOINTER)
    {
      SQUserPointer value;
      sq_getuserpointer(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<SQUserPointer *>(address) = value;
      sq_pushuserpointer(vm, value);
      return 1;
    }
    expectedType = OT_USERPOINTER;
    break;
  case kScriptVarTypeInstance:
    {
      const ClassTypeTagBase *variableClassTypeTag = nullptr;
      GetVariableClassType(vm, variableReferenceIndex, &variableClassTypeTag);

      SQUserPointer value;
      if (SQ_SUCCEEDED(sq_getinstanceup(vm, kSetValueStackIndex, &value, (SQUserPointer)variableClassTypeTag)))
      {
        CopyInstanceFunction copyFunction = variableClassTypeTag->GetCopyFunction();
        copyFunction(address, value);

        HSQOBJECT variableClassObject = variableClassTypeTag->GetClassObject(vm);
        sq_pushobject(vm, variableClassObject);
        if (SQ_SUCCEEDED(sq_createinstance(vm, -1)))
        {
          // remove variableClassObject from stack
          //
          sq_remove(vm, -2);
          SQUserPointer instance = static_cast<SQUserPointer>(address);
          sq_setinstanceup(vm, -1, instance);
          return 1;
        }

        // remove variableClassObject from stack
        //
        sq_poptop(vm);
        return sh.ThrowError(
          _SC("error setting variable '%s' ; check variable class type '%s' has been bound correctly"),
          sh.GetString(2),
          variableClassTypeTag->GetTypeName());
      }

      return sh.ThrowError(
        _SC("error setting variable '%s' ; expected '%s' got '%s'"),
        sh.GetString(2),
        variableClassTypeTag->GetTypeName(),
        sh.GetTypeName(3));
    }
    break;
#if defined(_SQ64)
  case TypeInfo<int64_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<int64_t*>(address) = static_cast<int64_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
  case TypeInfo<uint64_t>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_INTEGER)
    {
      SQInteger value;
      sq_getinteger(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<uint64_t*>(address) = static_cast<uint64_t>(value);
      sq_pushinteger(vm, value);
      return 1;
    }
    expectedType = OT_INTEGER;
    break;
#endif // defined(_SQ64)
#if defined(SQUSEDOUBLE)
  case TypeInfo<double>::kTypeID:
    if (sq_gettype(vm, kSetValueStackIndex) == OT_FLOAT)
    {
      SQFloat value;
      sq_getfloat(vm, kSetValueStackIndex, &value);
      *reinterpret_cast<double*>(address) = static_cast<double>(value);
      sq_pushfloat(vm, value);
      return 1;
    }
    expectedType = OT_FLOAT;
    break;
#endif // defined(SQUSEDOUBLE)
  default:
    return sh.ThrowError(
      _SC("error setting variable '%s' ; unknown variable type id '%d'"),
      sh.GetString(2),
      variableType);
  }

  return sh.ThrowError(
    _SC("error setting variable '%s' ; expected '%s' got '%s'"),
    sh.GetString(2),
    RawTypeToTypeName(expectedType),
    sh.GetTypeName(3));
}

}
