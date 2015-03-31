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
// Bind
//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename BaseClassType>
bool Bind::BindClass(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_TABLE && objectType != OT_CLASS)
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

  sqb::ClassTypeTag<ClassType> *classTypeTag = sqb::ClassTypeTag<ClassType>::Get();

  // sqb::ClassTypeTag::Get will return null for sqb::NoBaseClass, make sure it cannot be bound
  //
  if (classTypeTag == nullptr)
  {
    return false;
  }

  // push this read for binding the class in to a named slot in object
  //
  sq_pushstring(vm, name, nameLength);

  // create a new class and setup up the base class if there was one
  //
  if (SetBaseClass<BaseClassType>::ForClassTypeTag(classTypeTag))
  {
    if (!PushBaseClassType<BaseClassType>(vm))
    {
      sq_poptop(vm);
      return false;
    }

    SQRESULT result = sq_newclass(vm, SQTrue);
    SQBIND_ASSERT_SUCCEEDED(result);
  }
  else
  {
    SQRESULT result = sq_newclass(vm, SQFalse);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  // set the ClassType instance as the type tag for the new class
  //
  {
    SQRESULT result = sq_settypetag(vm, -1, classTypeTag);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  // ensure the class object can be retrieve using ClassType at any point
  //
  HSQOBJECT classObject;
  {
    SQRESULT result = sq_getstackobj(vm, -1, &classObject);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  classTypeTag->SetClassObject(vm, classObject);

  // setup _typeof metamethod
  //
  FunctionOptions options;
  options.ParamCheckCount(1);
  options.TypeMask(_SC("x"));
  {
    bool result = BindNativeFunction(vm, -1, &TypeOf<ClassType>, _SC("_typeof"), options);
    SQBIND_ASSERT(result);
  }

  // add the new class as a named slot in object
  //
  {
    SQRESULT result = sq_newslot(vm, objectIndex, SQTrue);
    SQBIND_ASSERT_SUCCEEDED(result);
  }

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename FunctionType>
bool Bind::BindFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  FunctionType      function,
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

  // create a new squirrel closure using the templated dispatch function with the actual function
  // as a free variable
  //
  sq_pushuserpointer(vm, reinterpret_cast<SQUserPointer*>(function));
  sq_newclosure(vm, &DispatchFunctionCall<FunctionType>, 1);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  sq_pushstring(vm, name, nameLength);
  sq_push(vm, -2);
  result = sq_newslot(vm, objectIndex, options.m_staticType);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename FunctionType>
inline bool Bind::BindClassFunction(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  FunctionType  function,
  const SQChar *name)
{
  if (sq_gettype(vm, objectIndex) != OT_CLASS)
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

  // put the name on the stack first ready for creating the slot later
  //
  sq_pushstring(vm, name, nameLength);

  // push the the function pointer as a free variable to be used by the dispatch function.
  // note: has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;

  sq_newclosure(vm, &DispatchClassFunctionCall<ClassType, FunctionType>, 1);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool Bind::BindNativeClassFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  SQInteger         (ClassType:: *function)(HSQUIRRELVM),
  const SQChar     *name,
  FunctionOptions   options)
{
  typedef SQInteger (ClassType:: *FunctionType)(HSQUIRRELVM);

  if (sq_gettype(vm, objectIndex) != OT_CLASS)
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

  // push the the function pointer as a free variable to be used by the dispatch function.
  // note: has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;

  sq_newclosure(vm, &DispatchNativeClassFunctionCall<ClassType>, options.m_freeVariableCount + 1);

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
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType, typename FunctionType>
inline bool Bind::BindSingletonFunction(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  ClassType    *instance,
  FunctionType  function,
  const SQChar *name)
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

  if (instance == nullptr)
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

  // put the name on the stack first ready for creating the slot later
  //
  sq_pushstring(vm, name, nameLength);

  // push the class instance and the function pointer as free variables to be used by the dispatch function.
  // note: function has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;
  sq_pushuserpointer(vm, reinterpret_cast<SQUserPointer*>(instance));

  sq_newclosure(vm, &DispatchSingletonFunctionCall<ClassType, FunctionType>, 2);

  // set the param check count and typemask for the new function
  //
  SQRESULT result = autogen::ParamCheckHelper::SetParamsCheck(vm, function);
  SQBIND_ASSERT_SUCCEEDED_MSG(result, "check all parameter types have been bound with SQBIND_DECLARE_TYPEINFO macro.");

  // set the name used when debugging
  //
  result = sq_setnativeclosurename(vm, -1, name);
  SQBIND_ASSERT_SUCCEEDED(result);

  // create a named slot for the new function in the owning object
  //
  result = sq_newslot(vm, objectIndex, SQTrue);
  SQBIND_ASSERT_SUCCEEDED(result);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename ClassType>
inline bool Bind::BindNativeSingletonFunction(
  HSQUIRRELVM       vm,
  SQInteger         objectIndex,
  ClassType        *instance,
  SQInteger         (ClassType:: *function)(HSQUIRRELVM),
  const SQChar     *name,
  FunctionOptions   options)
{
  typedef SQInteger (ClassType:: *FunctionType)(HSQUIRRELVM);

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

  if (instance == nullptr)
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

  // push the class instance and the function pointer as free variables to be used by the dispatch function.
  // note: function has to be done as userdata not a userpointer as member functions can sometimes
  //       be bigger than sizeof(void*).
  //
  FunctionType* pointer = (FunctionType*)sq_newuserdata(vm, sizeof(FunctionType));
  *pointer = function;
  sq_pushuserpointer(vm, *reinterpret_cast<SQUserPointer*>(&instance));

  sq_newclosure(vm, &DispatchNativeSingletonFunctionCall<ClassType>, options.m_freeVariableCount + 2);

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
  result = sq_newslot(vm, objectIndex, SQFalse);
  SQBIND_ASSERT_SUCCEEDED(result);

  // remove the first closure from the stack, the pushed copy was removed by sq_newslot.
  //
  sq_poptop(vm);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename VariableType>
inline bool Bind::BindVariable(
  HSQUIRRELVM   vm,
  SQInteger     objectIndex,
  VariableType *variable,
  const SQChar *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS && objectType != OT_TABLE)
  {
    return false;
  }

  if (variable == nullptr)
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

  SQInteger top = sq_gettop(vm);

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    objectIndex = top + objectIndex + 1;
  }

  GetOrCreateObjectReferencesTable(vm, objectIndex, objectType);
  SQBIND_ASSERT(sq_gettype(vm, -1) == OT_TABLE);

  // now create the variable reference in the object references table.
  //
  sq_newtable(vm);

  sq_pushstring(vm, name, -1);
  sq_push(vm, -2);
  sq_rawset(vm, -4);

  ScriptVarType variableType = static_cast<ScriptVarType>(TypeInfo<VariableType>::kTypeID);
  ClassTypeTag<VariableType>* variableClassTypeTag = ClassTypeTag<VariableType>::Get();
  SQInteger flags = ((objectType == OT_CLASS) ? kVariableStatic : kVariableNoFlags);
  bool result = CreateVariableReference(
    vm,
    top + 2,
    variableType,
    reinterpret_cast<SQUserPointer>(variable),
    nullptr,
    variableClassTypeTag,
    flags);

  if (!result)
  {
    sq_pop(vm, 2);
    return false;
  }

  SQInteger referencesTableIndex = top + 1;

  EnsureGetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);
  EnsureSetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);

  // pop the registry table, the object references table and the variable references.
  //
  sq_pop(vm, 2);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename VariableType>
inline bool Bind::BindInstanceVariable(
  HSQUIRRELVM                   vm,
  SQInteger                     objectIndex,
  VariableType InstanceType::  *variable,
  const SQChar                 *name)
{
  SQObjectType objectType = sq_gettype(vm, objectIndex);
  if (objectType != OT_CLASS)
  {
    return false;
  }

  if (variable == nullptr)
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

  SQInteger top = sq_gettop(vm);

  // if the index was relative to the top convert to an absolute index before calls alter the stack.
  //
  if (objectIndex < 0)
  {
    objectIndex = top + objectIndex + 1;
  }

  GetOrCreateObjectReferencesTable(vm, objectIndex, objectType);
  SQBIND_ASSERT(sq_gettype(vm, -1) == OT_TABLE);

  // now create the variable reference in the object references table.
  //
  sq_newtable(vm);

  sq_pushstring(vm, name, -1);
  sq_push(vm, -2);
  sq_rawset(vm, -4);

  // c++ won't let you cast from a member variable pointer to a void * so this struct is used to help
  // cast it. By casting the struct to a void ** and then dereferencing back to void * the variable pointer
  // is effectively cast to a void *. This uses the fact that the CastHelper::variable is the first and
  // only member of the struct so a pointer to the helper will also point to helper::variable.
  //
  struct CastHelper
  {
    VariableType InstanceType:: *variable;
  };
  CastHelper helper;
  helper.variable = variable;
  SQUserPointer offset = *reinterpret_cast<void**>(&helper);

#if defined(_SQ64)
  // 64-bit member variable offsets have the higher 32 bits uninitialised so mask that away
  // ie 0xcccccccc00000000 -> 0x0000000000000000
  //
  offset = reinterpret_cast<SQUserPointer>(reinterpret_cast<ptrdiff_t>(offset) & 0xffffffff);
#endif

  ClassTypeTag<InstanceType>* instanceClassTypeTag = ClassTypeTag<InstanceType>::Get();
  ClassTypeTag<VariableType>* variableClassTypeTag = ClassTypeTag<VariableType>::Get();
  bool result = CreateVariableReference(
    vm,
    top + 2,
    static_cast<ScriptVarType>(TypeInfo<VariableType>::kTypeID),
    offset,
    instanceClassTypeTag,
    variableClassTypeTag,
    kVariableNoFlags);

  if (!result)
  {
    sq_pop(vm, 2);
    return false;
  }

  SQInteger referencesTableIndex = top + 1;

  EnsureGetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);
  EnsureSetMetaMethodBound(vm, objectIndex, objectType, referencesTableIndex);

  // pop the registry table, the object references table and the variable references.
  //
  sq_pop(vm, 2);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename BaseClassType>
template<typename ClassType>
bool Bind::SetBaseClass<BaseClassType>::ForClassTypeTag(sqb::ClassTypeTag<ClassType> *classType)
{
  classType->SetBaseClass(static_cast<BaseClassType *>(nullptr));

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
template<>
template<typename ClassType>
bool Bind::SetBaseClass<NoBaseClass>::ForClassTypeTag(sqb::ClassTypeTag<ClassType> *SQBIND_UNUSED(classType))
{
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename BaseClassType>
inline bool Bind::PushBaseClassType(HSQUIRRELVM vm)
{
  sqb::ClassTypeTag<BaseClassType> *baseClassTypeTag = sqb::ClassTypeTag<BaseClassType>::Get();

  HSQOBJECT baseClassObject = baseClassTypeTag->GetClassObject(vm);
  if (sq_type(baseClassObject) == OT_CLASS)
  {
    sq_pushobject(vm, baseClassObject);
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
void Bind::GetInstanceFromStack(HSQUIRRELVM vm, SQInteger objectIndex, InstanceType **instance)
{
  // get the instance which will be the first parameter in the stack
  //
  SQUserPointer pointer;
  SQRESULT result = sq_getinstanceup(vm, objectIndex, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  // if the instance bound is not of type InstanceType then the pointer may need to be offset
  //
  ClassTypeTagBase *actualTypeTag;
  // this call cannot fail if sq_getinstanceup passed
  //
  sq_gettypetag(vm, objectIndex, reinterpret_cast<SQUserPointer *>(&actualTypeTag));
  SQBIND_ASSERT(actualTypeTag != nullptr);
  SQBIND_ASSERT(actualTypeTag->IsValid());

  // adjust the pointer offset if necessary
  //
  ClassTypeTagBase *expectedTypeTag = ClassTypeTag<InstanceType>::Get();
  if (actualTypeTag != expectedTypeTag && actualTypeTag->MayHaveOffset())
  {
    // instance type is more derived than callee and there may be an offset, adjust pointer
    ptrdiff_t offset = actualTypeTag->GetOffsetTo(expectedTypeTag);
    pointer = static_cast<uint8_t *>(pointer) - offset;
  }

  *instance = static_cast<InstanceType *>(pointer);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename FuncType>
inline SQInteger Bind::DispatchFunctionCall(HSQUIRRELVM vm)
{
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 1);

  FuncType function;
  SQRESULT result = sq_getuserpointer(vm, count, reinterpret_cast<SQUserPointer *>(&function));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(function != nullptr);

  return autogen::Call(function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename FunctionType>
inline SQInteger Bind::DispatchClassFunctionCall(HSQUIRRELVM vm)
{
  // count is also the index of the last free variable of the function
  //
  SQInteger count = sq_gettop(vm);
  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the first parameter in the stack
  //
  InstanceType *instance;
  GetInstanceFromStack(vm, 1, &instance);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  SQRESULT result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return autogen::Call(*instance, function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
inline SQInteger Bind::DispatchNativeClassFunctionCall(HSQUIRRELVM vm)
{
  typedef SQInteger (InstanceType:: *FunctionType)(HSQUIRRELVM);
  // count is also the index of the last free variable of the function
  //
  SQInteger count = sq_gettop(vm);
  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the first parameter in the stack
  //
  InstanceType *instance;
  GetInstanceFromStack(vm, 1, &instance);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  SQRESULT result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return (instance->*(function))(vm);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType, typename FunctionType>
inline SQInteger Bind::DispatchSingletonFunctionCall(HSQUIRRELVM vm)
{
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the second to last free variable on the stack
  //
  InstanceType *instance = nullptr;
  SQRESULT result = sq_getuserpointer(vm, count - 1, reinterpret_cast<SQUserPointer *>(&instance));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(instance != nullptr);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return autogen::Call(*instance, function, vm, 2);
}

//----------------------------------------------------------------------------------------------------------------------
template<typename InstanceType>
inline SQInteger Bind::DispatchNativeSingletonFunctionCall(HSQUIRRELVM vm)
{
  typedef SQInteger (InstanceType:: *FunctionType)(HSQUIRRELVM);
  SQInteger count = sq_gettop(vm);

  SQBIND_ASSERT(count >= 2);

  // get the instance which will be the second to last free variable on the stack
  //
  InstanceType *instance = nullptr;
  SQRESULT result = sq_getuserpointer(vm, count - 1, reinterpret_cast<SQUserPointer *>(&instance));
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(instance != nullptr);

  // get the function which is the last free variable on the stack
  //
  SQUserPointer pointer = nullptr;
  result = sq_getuserdata(vm, count, &pointer, nullptr);
  SQBIND_ASSERT_SUCCEEDED(result);
  SQBIND_ASSERT(pointer != nullptr);

  FunctionType function = *((FunctionType*)pointer);
  return (instance->*(function))(vm);
}

} // namespace sqb
