
#ifndef _XSQBIND_CPP_DONE
#define _XSQBIND_CPP_DONE



#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif

#include "xsqbind.h"







SqRef &__xsqbind_sqref_get(SQVM *vm,int index)
{
	SqVM &sqvm = *(SqVM*)sq_getforeignptr(vm);
	static SqRef r;
	r = SqRef();
	sqvm.getstackobj(r,index);
	return r;
}

int __xsqbind_sqref_push(SQVM *vm,SqRef &ref)
{
	if(!ref.handle || !ref.handle->vm)
		return 0;	// return null
	sq_pushobject(vm,ref.handle->hobj);
	return 1;
}



namespace sqb {
	template<>
	SqRef &Get<SqRef>(sqb::TypeWrapper<SqRef>,SQVM *vm,SQInteger index)
	{
		return __xsqbind_sqref_get(vm,index);
	}

	template<>
	bool Match<SqRef>(sqb::TypeWrapper<SqRef>,SQVM *vm,SQInteger index)
	{
		HSQOBJECT hobj;
		if(SQ_FAILED(sq_getstackobj(vm,index,&hobj)))
			return false;
		return sq_istable(hobj) || sq_isarray(hobj) || sq_isinstance(hobj) || sq_isclass(hobj);
	}

	template<>
	SQInteger Push<SqRef>(SQVM *vm,SqRef &ref)
	{
		return __xsqbind_sqref_push(vm,ref);
	}

	//template<>
	//int Push<std::string> (struct SQVM *vm,std::string &s)
	//{
	//	sq_pushstring(vm,s.c_str(),s.size());
	//	return SQ_OK;
	//}


	bool Match(TypeWrapper<const std::string>,HSQUIRRELVM v,int idx) {
		return sq_gettype(v,idx) == OT_STRING;
	}

	std::string Get(TypeWrapper<const std::string>,HSQUIRRELVM v,int idx)
	{
		const SQChar * s;
		sq_getstring(v,idx,&s);
		return std::string(s);

	}

	template<>
	SQInteger Push<std::string>(HSQUIRRELVM v,std::string &value) { sq_pushstring(v,value.c_str(),-1); return 1; }
}



#endif
