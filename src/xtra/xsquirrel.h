
#ifndef _XSQUIRREL_H
#define _XSQUIRREL_H


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif


#include <string.h>
#include <string>
#include <vector>

#if !defined(__clang__)
	#define __has_feature(x)	0
#endif

#if defined(__GNUC__)
	#define SQBIND_BEGIN_MULTILINE_MACRO()	do {
	#define SQBIND_END_MULTILINE_MACRO()	} while(0)
#endif

#define SQBIND_CPP0X_NULLPTR_SUPPORTED	0


#include "squirrel/squirrel.h"


// Implemented on user side
void xsq_print( const char *msg );
void xsq_error( const char *err );
bool xsq_getfile( const char *path, std::vector<unsigned char> &data );
unsigned long long xsq_getfiletime( const char *path );




#define XSQ_STRUCT(name,sqname,st)							\
	struct name {											\
		st													\
		static const char *_name() { return #name; }		\
		static const char *_name_sq() { return sqname; }	\
		static const char *_member_list() { return #st; }	\
	};




// ---------------- register internals ----------------

class __xsq_register {
public:
	static std::vector<void (*)(HSQUIRRELVM)> &regs()
	{
		static std::vector<void (*)(HSQUIRRELVM)> _regs;
		return _regs;
	}

	static void add(void (*fn)(HSQUIRRELVM))
	{
		regs().push_back(fn);
	}
};



class SqRef;




class SqVM {
public:
	SqVM() : vm(NULL), first_free_handle(NULL), first_busy_handle(NULL) {}
	~SqVM() { DeInit(); }

	void Init(int stack_size = 1024);
	void DeInit();

	bool DoFile(const char *path);
	bool DoString(const char *code);

	bool AddFile(const char *path);
	int  CheckFiles();


	template<class T>
	T Get(const char *name)
	{
		T out = T();
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(SQ_SUCCEEDED(sq_get(vm,-2)))
			_sq_get(out);
		sq_settop(vm,top);
		return out;
	}

	template<class T>
	bool Get(const char *name,T &out)
	{
		bool ok = false;
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(SQ_SUCCEEDED(sq_get(vm,-2)))
			ok = _sq_get(out);
		else
			out = out();
		sq_settop(vm,top);
		return ok;
	}

	int			GetInt(const char *name)	{ return Get<int>(name); }
	float		GetFloat(const char *name)	{ return Get<float>(name); }
	std::string	GetString(const char *name)	{ return Get<std::string>(name); }
	SqRef		GetObj(const char *name);


	template<class T>
	bool Set(const char *name,const T v)
	{
		bool ok = false;
		int top = sq_gettop(vm);
		sq_pushroottable(vm);
		sq_pushstring(vm,name,-1);
		if(_sq_push(v)==1 && SQ_SUCCEEDED(sq_newslot(vm,-3,false)))
			ok = true;
		sq_settop(vm,top);
		return ok;
	}

	template<class T> SqRef ToObject(const T v);
	SqRef NewObject();


	//template<class A1>
	//bool Run(const char *fn,A1 a1)
	//{
	//	int top = sq_gettop(vm);
	//	sq_pushroottable(vm);
	//	sq_pushstring(vm,fn,-1);
	//	if(SQ_SUCCEEDED(sq_get(vm,-2)))
	//	{
	//		sq_pushroottable(vm); //push the 'this' (in this case is the global table)
	//		sq_pushinteger(vm,n); 
	//		sq_pushfloat(vm,f);
	//		sq_pushstring(vm,s,-1);
	//		sq_call(vm,4,0,0);
	//	}
	//	sq_settop(vm,top); //restores the original stack size
	//}
#define T		template<
#define C(n)	class T##n
#define FN		bool Run(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { int args=1, top=sq_gettop(vm); bool ok=false; sq_pushroottable(vm); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushroottable(vm);
#define P(n)	args+=_sq_push(a##n);
#define END		ok=SQ_SUCCEEDED(sq_call(vm,args,false,true)); } sq_settop(vm,top); return ok; }
	FN CODE END
	T C(1) > FN A(1) CODE P(1) END
	T C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

#define T		template<class R
#define C(n)	class T##n
#define FN		R RunRet(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { int args=1, top=sq_gettop(vm); sq_pushroottable(vm); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushroottable(vm);
#define P(n)	args+=_sq_push(a##n);
#define END		sq_call(vm,args,true,true); R ret = R(); _sq_get(ret); sq_settop(vm,top); return ret; } sq_settop(vm,top); return R(); }
	T > FN CODE END
	T ,C(1) > FN A(1) CODE P(1) END
	T ,C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T ,C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T ,C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T ,C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

private:
	friend class SqRef;
	friend class ObjectHandle;
	friend SqRef &__xsqbind_sqref_get(SQVM *vm,int index);


	class ObjectHandle {
	public:
		SqVM			*vm;
		int				refcount;
		HSQOBJECT		hobj;
		ObjectHandle	*next;
		ObjectHandle	*prev;

		ObjectHandle(SqVM &_vm);

	private:
		friend class SqVM;
		friend class SqRef;

		void Free();	// called after losing last reference

		ObjectHandle();							// disabled
		ObjectHandle(const ObjectHandle &);		// disabled
		void operator =(const ObjectHandle &);	// disabled
	};

	struct ScriptFile {
		std::string			path;
		unsigned long long	timestamp;
	};

	HSQUIRRELVM				vm;
	ObjectHandle			*first_free_handle;
	ObjectHandle			*first_busy_handle;
	std::vector<ScriptFile>	script_files;



	static void print_callback(HSQUIRRELVM vm, const SQChar *format, ...);
	static void print_error_callback(HSQUIRRELVM vm, const SQChar *format, ...);
	static void print_stack_trace(HSQUIRRELVM vm);
	static int	print_runtime_error(HSQUIRRELVM vm);
	static void print_compile_error(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column);

	bool getstackobj(SqRef &out,int index);

	template<class T>	int _sq_push(T a)					{ return xsq_struct_push(&a,T::_member_list()); }
	template<class T>	bool _sq_get(T &out)				{ return xsq_struct_get(&out,T::_member_list()); }

	int xsq_struct_push(const void *st,const char *members);
	bool xsq_struct_get(void *st,const char *members);


	SqVM(const SqVM &);				// disabled
	void operator =(const SqVM &);	// disabled
};




class SqRef {
public:
	SqRef() : handle(NULL) { }
	SqRef(const SqRef &r) : handle(r.handle) { if(handle) handle->refcount++; }

	void operator =(const SqRef &r)
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = r.handle;
		if(handle) handle->refcount++;
	}

	bool operator ==(const SqRef &r) const	{ return handle==r.handle; }
	bool operator !() const					{ return !handle; }

	void clear_ref()
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = NULL;
	}

	void *GetPointer()
	{
		if(!handle) return NULL;
		if(handle->hobj._type==OT_NULL) return NULL;
		return handle->hobj._unVal.pTable;
	}

	template<class T>
	T Get(const char *name)
	{
		int top = _get_base(name);
		if(top==int(0x8000000))
			return T();
		T out = T();
		handle->vm->_sq_get(out);
		sq_settop(handle->vm->vm,top);
		return out;
	}

	template<class T>
	bool Get(const char *name,T &out)
	{
		int top = _get_base(name);
		if(top==int(0x8000000))
		{
			out = T();
			return false;
		}
		handle->vm->_sq_get(out);
		sq_settop(handle->vm->vm,top);
		return true;
	}

	int			GetInt(const char *name)	{ return Get<int>(name); }
	float		GetFloat(const char *name)	{ return Get<float>(name); }
	std::string	GetString(const char *name)	{ return Get<std::string>(name); }
	SqRef		GetObj(const char *name)	{ return Get<SqRef>(name); }

	template<class T>
	bool Set(const char *name,const T v)
	{
		int top = _set_base(name);
		if(top==int(0x8000000))
			return false;
		bool ok = false;
		if(handle->vm->_sq_push(v)==1 && SQ_SUCCEEDED(sq_newslot(handle->vm->vm,-3,false)))
			ok = true;
		sq_settop(handle->vm->vm,top);
		return ok;
	}

	//template<class A1>
	//bool Run(const char *fn,A1 a1)
	//{
	//	int top = sq_gettop(vm);
	//	sq_pushroottable(vm);
	//	sq_pushstring(vm,fn,-1);
	//	if(SQ_SUCCEEDED(sq_get(vm,-2)))
	//	{
	//		sq_pushroottable(vm); //push the 'this' (in this case is the global table)
	//		sq_pushinteger(vm,n); 
	//		sq_pushfloat(vm,f);
	//		sq_pushstring(vm,s,-1);
	//		sq_call(vm,4,0,0);
	//	}
	//	sq_settop(vm,top); //restores the original stack size
	//}
#define T		template<
#define C(n)	class T##n
#define FN		bool Run(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { if(!handle || !handle->vm) return false;	\
					HSQUIRRELVM vm = handle->vm->vm;			\
					int args=1, top=sq_gettop(vm);				\
					bool ok=false; sq_pushobject(vm,handle->hobj); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushobject(vm,handle->hobj);
#define P(n)	args+=handle->vm->_sq_push(a##n);
#define END		ok=SQ_SUCCEEDED(sq_call(vm,args,false,true)); } sq_settop(vm,top); return ok; }
	FN CODE END
	T C(1) > FN A(1) CODE P(1) END
	T C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	

#define T		template<class R
#define C(n)	class T##n
#define FN		R RunRet(const char *fn
#define A(n)	,const T##n a##n
#define CODE	) { if(!handle || !handle->vm) return R();		\
					HSQUIRRELVM vm = handle->vm->vm;			\
					int args=1, top=sq_gettop(vm);				\
					bool ok=false; sq_pushobject(vm,handle->hobj); sq_pushstring(vm,fn,-1); if(SQ_SUCCEEDED(sq_get(vm,-2))) { sq_pushobject(vm,handle->hobj);
#define P(n)	args+=handle->vm->_sq_push(a##n);
#define END		sq_call(vm,args,true,true); R ret = R(); handle->vm->_sq_get(ret); sq_settop(vm,top); return ret; } sq_settop(vm,top); return R(); }
	T > FN CODE END
	T ,C(1) > FN A(1) CODE P(1) END
	T ,C(1),C(2) > FN A(1) A(2) CODE P(1) P(2) END
	T ,C(1),C(2),C(3) > FN A(1) A(2) A(3) CODE P(1) P(2) P(3) END
	T ,C(1),C(2),C(3),C(4) > FN A(1) A(2) A(3) A(4) CODE P(1) P(2) P(3) P(4) END
	T ,C(1),C(2),C(3),C(4),C(5) > FN A(1) A(2) A(3) A(4) A(5) CODE P(1) P(2) P(3) P(4) P(5) END
#undef T
#undef C
#undef FN	
#undef A
#undef CODE	
#undef P
#undef END	


private:
	friend class SqVM;
	friend int __xsqbind_sqref_push(SQVM *vm,SqRef &ref);

	SqVM::ObjectHandle	*handle;

	int _get_base(const char *name);
	int _set_base(const char *name);

	void set_ref(SqVM::ObjectHandle *h)
	{
		if(handle && !--(handle->refcount))
			handle->Free();
		handle = h;
		if(handle) handle->refcount++;
	}
};



inline SqRef SqVM::GetObj(const char *name) { return Get<SqRef>(name); }

template<class T>
SqRef SqVM::ToObject(const T v)
{
	bool ok = false;
	SqRef ref;
	int top = sq_gettop(vm);
	if(_sq_push(v)==1 && getstackobj(ref,-1))
		ok = true;
	sq_settop(vm,top);
	return ref;
}

inline SqRef SqVM::NewObject()
{
	SqRef ref;
	int top = sq_gettop(vm);
	sq_newtable(vm);
	getstackobj(ref,-1);
	sq_settop(vm,top);
	return ref;
}



template<>	inline		int SqVM::_sq_push(const int a)			{ sq_pushinteger(vm,a);				return 1; }
template<>	inline		int SqVM::_sq_push(const float a)		{ sq_pushfloat(vm,a);				return 1; }
template<>	inline		int SqVM::_sq_push(const char *a)		{ sq_pushstring(vm,a,-1);			return 1; }
template<>	inline		int SqVM::_sq_push(const std::string a)	{ sq_pushstring(vm,a.c_str(),-1);	return 1; }
template<>	inline		int SqVM::_sq_push(std::string *a)		{ sq_pushstring(vm,a->c_str(),-1);	return 1; }
template<>	inline		int SqVM::_sq_push(SqRef a)				{ if(a.handle) sq_pushobject(vm,a.handle->hobj); else sq_pushnull(vm);	return 1; }
template<>	inline		bool SqVM::_sq_get(int &out)			{ if(SQ_FAILED(sq_getinteger(vm,-1,&out)))	{ out=0; return false; } return true; }
template<>	inline		bool SqVM::_sq_get(float &out)			{ if(SQ_FAILED(sq_getfloat(vm,-1,&out)))	{ out=0; return false; } return true; }
template<>	inline		bool SqVM::_sq_get(std::string &out)	{ sq_tostring(vm,-1); sq_remove(vm,-2); const char *s=NULL; if(SQ_FAILED(sq_getstring(vm,-1,&s)) || !s) { out.clear(); return false; } out=s; return true; }
template<>	inline		bool SqVM::_sq_get(SqRef &out)			{ return getstackobj(out,-1); }





#endif
