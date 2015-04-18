
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


	// ---- vec2 ----
#ifdef XSQ_VEC2
	template<> struct TypeInfo<XSQ_VEC2>
	{
		enum
		{
			kTypeID = kScriptVarTypeInstance,
			kTypeSize = sizeof(XSQ_VEC2),
			kTypeMask = 'x',
			kTypeIsInstance = SQTrue,
		};
		const SQChar *m_typeName;
		inline TypeInfo() : m_typeName(_SC("vec2"))
		{
		}
		inline operator ScriptVarType() const
		{
			return static_cast<ScriptVarType>(kTypeID);
		}
	}; \
	template<> inline bool Match<XSQ_VEC2>(TypeWrapper<XSQ_VEC2>, HSQUIRRELVM vm, SQInteger idx)					{ return true; }
	template<> inline bool Match<XSQ_VEC2 &>(TypeWrapper<XSQ_VEC2 &>, HSQUIRRELVM vm, SQInteger idx)				{ return true; }
	template<> inline bool Match<const XSQ_VEC2 &>(TypeWrapper<const XSQ_VEC2 &>, HSQUIRRELVM vm, SQInteger idx)	{ return true; }
	template<> inline XSQ_VEC2 &Get<XSQ_VEC2>(TypeWrapper<XSQ_VEC2>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		static XSQ_VEC2 value;
		value = XSQ_VEC2(0,0);
		sqvm._sq_get(value,idx);
		return value;
	}
	template<> inline SQRESULT Push<XSQ_VEC2>(HSQUIRRELVM vm, XSQ_VEC2 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
	template<> inline SQRESULT Push<XSQ_VEC2>(HSQUIRRELVM vm, const XSQ_VEC2 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
#endif

	// ---- vec3 ----
#ifdef XSQ_VEC3
	template<> struct TypeInfo<XSQ_VEC3>
	{
		enum
		{
			kTypeID = kScriptVarTypeInstance,
			kTypeSize = sizeof(XSQ_VEC3),
			kTypeMask = 'x',
			kTypeIsInstance = SQTrue,
		};
		const SQChar *m_typeName;
		inline TypeInfo() : m_typeName(_SC("vec3"))
		{
		}
		inline operator ScriptVarType() const
		{
			return static_cast<ScriptVarType>(kTypeID);
		}
	}; \
	template<> inline bool Match<XSQ_VEC3>(TypeWrapper<XSQ_VEC3>, HSQUIRRELVM vm, SQInteger idx)					{ return true; }
	template<> inline bool Match<XSQ_VEC3 &>(TypeWrapper<XSQ_VEC3 &>, HSQUIRRELVM vm, SQInteger idx)				{ return true; }
	template<> inline bool Match<const XSQ_VEC3 &>(TypeWrapper<const XSQ_VEC3 &>, HSQUIRRELVM vm, SQInteger idx)	{ return true; }
	template<> inline XSQ_VEC3 &Get<XSQ_VEC3>(TypeWrapper<XSQ_VEC3>, HSQUIRRELVM vm, SQInteger idx)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		static XSQ_VEC3 value;
		value = XSQ_VEC3(0,0,0);
		sqvm._sq_get(value,idx);
		return value;
	}
	template<> inline SQRESULT Push<XSQ_VEC3>(HSQUIRRELVM vm, XSQ_VEC3 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
	template<> inline SQRESULT Push<XSQ_VEC3>(HSQUIRRELVM vm, const XSQ_VEC3 &value)
	{
		SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
		return sqvm._sq_push(value);
	}
#endif
}


#define XSQ_REGISTER_FN(fn)		\
	static void __xsq_register_##fn(HSQUIRRELVM vm) {	\
		sq_pushroottable(vm);							\
		sqb::Bind::BindFunction(vm, -1, &fn, #fn);		\
		sq_poptop(vm);									\
	}													\
	static char __xsq_register_trigger_##fn = (__xsq_register::add(__xsq_register_##fn), 0);
