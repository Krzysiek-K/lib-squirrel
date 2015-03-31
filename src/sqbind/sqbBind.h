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
#include <cstring>
//----------------------------------------------------------------------------------------------------------------------
#include <sqbind/autogen/sqbCall.h>
#include <sqbind/autogen/sqbParamCheckHelper.h>
#include <sqbind/sqbClassHelpers.h>
#include <sqbind/sqbClassTypeTag.h>
#include <sqbind/sqbFunctionOptions.h>
#include <sqbind/sqbTypeInfo.h>
//----------------------------------------------------------------------------------------------------------------------

namespace sqb
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief 
//---------------------------------------------------------------------------------------------------------------------
class SQBIND_API Bind
{
public:

  /// \defgroup Classes Binding classes
  /// Methods for binding classes to squirrel.
  /// @{

  /// \brief Bind a c++ class as a squirrel class.
  ///
  /// \note Binds sqb::TypeOf as "_typeof" metamethod.
  template<typename ClassType, typename BaseClassType>
  static bool BindClass(HSQUIRRELVM vm, SQInteger objectIndex, const SQChar *name);
  /// @}

  /// \defgroup Functions Binding functions
  /// Methods for binding functions to a squirrel table or class object.
  /// @{

  /// \brief Bind a global or static function to the class or table at objectIndex in the stack.
  ///
  /// A simple example of binding a function to the root table: \include BindFunction.cpp
  template<typename FunctionType>
  static bool BindFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    FunctionType      function,
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a global or static native function to the class or table at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or OT_CLASS or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  /// A native function is of the form: \code SQInteger function(HSQUIRRELVM vm); \endcode
  ///
  /// A simple example of binding a native function to the root table: \include BindNativeFunction.cpp
  ///
  /// The options parameter can be used to specify the parameter check type mask and type count, if any
  /// free variables should be bound and if the object at idx is of type OT_CLASS whether the bound function
  /// is static.
  ///
  /// Free variables are bound the last in the stack first so the last on the stack when binding
  /// will be the first free variable on the stack when accessing them within the function.
  ///
  /// A more advanced example of binding a native function with a free variable to the root table: \include BindNativeFunctionWithFreeVariable.cpp
  ///
  /// The type mask and the param check count are passed directly to the squirrel api function sq_setparamscheck
  /// so refer to the squirrel documentation for more information on valid type masks and param check counts.
  ///
  /// Another advanced example of binding a native function with a type checking to the root table: \include BindNativeFunctionWithTypeCheck.cpp
  static bool BindNativeFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    SQFUNCTION        function,
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a class member function to the class at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_CLASS or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  ///
  /// The function will always be bound as non static as an instance is required for a successful call.
  ///
  /// A simple example of binding a function to a class: \include BindClassFunction.cpp
  template<typename ClassType, typename FunctionType>
  static bool BindClassFunction(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    FunctionType  function,
    const SQChar *name);

  /// \brief Bind a native class function to the class at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or if name is
  /// null or zero length. If asserts are disabled then the results are undefined.
  /// A native class function is of the form: \code class Class { SQInteger function(HSQUIRRELVM vm); }; \endcode
  ///
  /// A simple example of binding a native class function to a class: \include BindNativeClassFunction.cpp
  template<typename ClassType>
  static bool BindNativeClassFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    SQInteger         (ClassType:: *function)(HSQUIRRELVM),
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());

  /// \brief Bind a specific instance class member function to the class or table at objectIndex in the stack.
  ///
  /// The call will fail if the object at objectIndex is not of type OT_CLASS or OT_TABLE, if name is
  /// null or zero length or if instance is null.
  ///
  /// The function will always be bound as a static function.
  ///
  /// A simple example of binding a function to the root table: \include BindSingletonFunction.cpp
  template<typename ClassType, typename FunctionType>
  static bool BindSingletonFunction(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    ClassType    *instance,
    FunctionType  function,
    const SQChar *name);

  /// \brief Bind a specific instance native class function to the class or table at objectIndex in the stack.
  ///
  /// The function will assert if the object at objectIndex is not of type OT_TABLE or OT_CLASS, if name is
  /// null or zero length or if instance is null. If asserts are disabled then the results are undefined.
  /// A native singleton function is of the same form as a native class function, the only difference is that this
  /// function binds to a specific class instance:
  /// \code class Singleton { SQInteger function(HSQUIRRELVM vm); }; \endcode
  ///
  /// A simple example of binding a native class function to a class: \include BindNativeSingletonFunction.cpp
  template<typename ClassType>
  static bool BindNativeSingletonFunction(
    HSQUIRRELVM       vm,
    SQInteger         objectIndex,
    ClassType        *instance,
    SQInteger         (ClassType:: *function)(HSQUIRRELVM),
    const SQChar     *name,
    FunctionOptions   options = FunctionOptions());
  /// @}

  /// \defgroup Variables Binding variables
  /// Methods for binding variables to a squirrel table or class object.
  /// @{

  /// \brief Bind a global or static member variable to the object at idx in the stack.
  template<typename VariableType>
  static bool BindVariable(
    HSQUIRRELVM         vm,
    SQInteger           idx,
    VariableType       *variable,
    const SQChar       *name);

  /// \brief Register a class instance member variable to a class.
  template<typename InstanceType, typename VariableType>
  static bool BindInstanceVariable(
    HSQUIRRELVM                   vm,
    SQInteger                     idx,
    VariableType InstanceType::  *variable,
    const SQChar                 *name);
  /// @}

private:

  /// \brief This enum contains the keys for every element contained within the variable reference table.
  ///
  /// Each bound variable has a variable reference table within the vm registry table that contains all the
  /// information about the variable required to set and get it via squirrel.
  enum VariableReferenceTableKeys
  {
    kScriptVarTypeKey = 0,     ///< The script type of the bound variable, can be any of ScriptVarType.
    kOffsetOrAddressKey,       ///< The address of the variable or the offset of the variable from its owning
                               ///  class instance.
    kInstanceClassTypeKey,     ///< The type of the bound variables owning instance if any.
    kVariableClassTypeKey,     ///< The class type of the bound variable if its ScriptVarType is of type
                               ///  kScriptVarTypeInstance.
    kFlagsKey,                 ///< The additional VariableFlags set when the variable was bound. Can be any
                               ///  combination of VariableFlags.
    kStringReferencesTableKey, ///< The string references table holds a strong reference to bound string variables
                               ///  so if they have been set via squirrel but all other references to the string have
                               ///  been destroyed, the string is not cleared until the bound variable is no longer
                               ///  referencing the string also.
  };

  enum VariableFlags
  {
    kVariableNoFlags  = 0,      ///< A default bound variable.
    kVariableStatic   = 1 << 0, ///< The variable is static, only used when binding to a class object.
  };

  /// \brief The number of variables expected when calling the _get metamethod.
  static const SQInteger kGetMetaMethodParamCheckCount;
  /// \brief The number of variables expected when calling the _set metamethod.
  static const SQInteger kSetMetaMethodParamCheckCount;

  /// \brief The typemask of variables expected when calling the _get metamethod.
  static const SQChar *kGetMetaMethodTypeMask;
  /// \brief The typemask of variables expected when calling the _set metamethod.
  static const SQChar *kSetMetaMethodTypeMask;

  /// \brief The index of the owning object in the stack when calling the _set or _get metamethod.
  static const SQInteger kThisObjectStackIndex;

  /// \brief The index of the variable name in the stack when calling _set or _get metamethods.
  static const SQInteger kNameStackIndex;

  /// \brief The index of the object references table in the stack when calling the _get metamethod.
  static const SQInteger kGetObjectReferencesStackIndex;

  /// \brief The index of the new object value in the stack when calling the _set metamethod.
  static const SQInteger kSetValueStackIndex;
  /// \brief The index of the object references table in the stack when calling the _set metamethod.
  static const SQInteger kSetObjectReferencesStackIndex;

  /// \brief Helper class, provides specialisation when BaseClassType is NoBaseClass.
  template<typename BaseClassType>
  class SetBaseClass
  {
  public:
    template<typename ClassType>
    static bool ForClassTypeTag(sqb::ClassTypeTag<ClassType> *classType);
  };

  /// \brief
  template<typename BaseClassType>
  static bool PushBaseClassType(HSQUIRRELVM vm);

  /// \brief
  template<typename InstanceType>
  static void GetInstanceFromStack(HSQUIRRELVM vm, SQInteger idx, InstanceType **instance);

  /// \brief Used to dispatch a native squirrel call to a call to a global or static c++ function call.
  template<typename FunctionType>
  static SQInteger DispatchFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType, typename FunctionType>
  static SQInteger DispatchClassFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType>
  static SQInteger DispatchNativeClassFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename ClassType, typename FunctionType>
  static SQInteger DispatchSingletonFunctionCall(HSQUIRRELVM vm);

  /// \brief
  template<typename InstanceType>
  static SQInteger DispatchNativeSingletonFunctionCall(HSQUIRRELVM vm);

  /// \brief Gets the object references table for an object at objectIndex in vm's stack. objectType
  /// should be of type OT_TABLE or OT_CLASS. If the object references table does not exist it is created.
  ///
  /// The object references table is stored per table/class object and holds all the information
  /// about every bound variable type. Each bound variable will have a variable reference table in the
  /// object references table.
  /// \note A derived class' object references table will have its base class' object references table as its
  /// delegate. This ensures that getting the variable reference table for a base member from the derived class
  /// will still succeed.
  static void GetOrCreateObjectReferencesTable(HSQUIRRELVM vm, SQInteger objectIndex, SQObjectType objectType);
  /// \brief Gets the delegate of a table or userdata creating it if necessary.
  /// \note Assumes the object at idx is a table or userdata and that idx is an absolute index.
  static void GetOrCreateObjectDelegate(HSQUIRRELVM vm, SQInteger objectIndex);

  /// \brief Fills in a table at variableReferenceIndex in vm's stack with all the information needed to bind
  /// a variable.
  static bool CreateVariableReference(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    ScriptVarType   variableType,
    SQUserPointer   offsetOrAddress,
    ClassTypeTagBase  *instanceClassType,
    ClassTypeTagBase  *variableClassType,
    SQInteger       bindFlags);

  /// \brief Makes sure that the required _get metamethod is bound for the object at objectIndex in vm's stack.
  static void EnsureGetMetaMethodBound(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    SQObjectType  objectType,
    SQInteger     objectReferencesIndex);
  /// \brief Makes sure that the required _set metamethod is bound for the object at objectIndex in vm's stack.
  static void EnsureSetMetaMethodBound(
    HSQUIRRELVM   vm,
    SQInteger     objectIndex,
    SQObjectType  objectType,
    SQInteger     objectReferencesIndex);

  /// \brief Retrieves the type and absolute address of a bound variable using the variable reference table at
  /// variableReferenceIndex in vm's stack.
  /// \note This should only be used for global variables bound to tables.
  static void GetVariableReferenceTypeAndAddress(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    SQInteger      *variableType,
    SQUserPointer  *address);

  /// \brief Gets the class type of a bound variable using the variable reference table at variableReferenceIndex
  /// in vm's stack.
  static void GetVariableClassType(
    HSQUIRRELVM           vm,
    SQInteger             variableReferenceIndex,
    const ClassTypeTagBase **variableClassType);

  static void GetVariableStringReferencesTable(
    HSQUIRRELVM vm,
    SQInteger   variableReferenceIndex);

  /// \brief The _get metamethod when binding variables to tables or userdata.
  static SQInteger GetVariableReference(HSQUIRRELVM vm);
  /// \brief The _set metamethod when binding variables to tables or userdata.
  static SQInteger SetVariableReference(HSQUIRRELVM vm);

  /// \brief Retrieves the type and offset or address of a bound variable using the variable reference table at
  /// variableReferenceIndex in vm's stack. If the variable is non-static and the owning object is a class
  /// instance then the offset in the variable reference table will be combined with the address of the instance
  /// user pointer to get the absolute address of the value being set/got.
  static void GetInstanceVariableReferenceTypeAndAddress(
    HSQUIRRELVM     vm,
    SQInteger       variableReferenceIndex,
    SQInteger      *variableType,
    SQUserPointer  *address);

  /// \brief The _get metamethod when binding variables to classes.
  static SQInteger GetInstanceVariableReference(HSQUIRRELVM vm);
  /// \brief The _set metamethod when binding variables to classes.
  static SQInteger SetInstanceVariableReference(HSQUIRRELVM vm);

  /// \brief Gets the value of the bound variable at address pushing it in the stack.
  /// \note The return value must be the value returned by the bound native _get metamethod function.
  static SQInteger GetVariable(
    HSQUIRRELVM   vm,
    SQInteger     variableReferenceIndex,
    SQInteger     variableType,
    SQUserPointer address);

  /// \brief Sets the value of the bound variable at address.
  /// \note The return value must be the value returned by the bound native _set metamethod function.
  static SQInteger SetVariable(
    HSQUIRRELVM   vm,
    SQInteger     variableReferenceIndex,
    SQInteger     variableType,
    SQUserPointer address);
};

} // namespace sqb

#include <sqbind/sqbBind.inl>
