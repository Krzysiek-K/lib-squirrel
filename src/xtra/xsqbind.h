
#pragma once


#include "xsquirrel.h"
#include "sqbind/SquirrelBind.h"

#include <vector>
#include <string>


namespace sqb {
	template<>
	struct TypeInfo<SqRef>
	{
	  enum
	  {
		kTypeID = kScriptVarTypeObject,
		kTypeSize = sizeof(SqRef),
		kTypeMask = '.',
		kTypeIsInstance = SQFalse,
	  };
	  const SQChar *m_typeName;
	  TypeInfo() : m_typeName(_SC("SqRef")) {}
	};

	template<>
	struct TypeInfo<std::string>
	{
	  enum
	  {
		kTypeID = kScriptVarTypeObject,
		kTypeSize = sizeof(std::string),
		kTypeMask = 's',
		kTypeIsInstance = SQFalse,
	  };
	  const SQChar *m_typeName;
	  TypeInfo() : m_typeName(_SC("string")) {}
	};
}


#define XSQ_REGISTER_FN(fn)		\
	static void __xsq_register_##fn(HSQUIRRELVM vm) {	\
		sq_pushroottable(vm);							\
		sqb::Bind::BindFunction(vm, -1, &fn, #fn);		\
		sq_poptop(vm);									\
	}													\
	static char __xsq_register_trigger_##fn = (__xsq_register::add(__xsq_register_##fn), 0);
