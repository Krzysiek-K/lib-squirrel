
#ifndef _XSQUIRREL_CPP_DONE
#define _XSQUIRREL_CPP_DONE



#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SQBIND_STATIC
#define SQBIND_STATIC
#endif



#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>
using namespace std;


#include "xsquirrel.h"
#include "sqstdio.h"
#include "sqstdmath.h"
#include "sqstdstring.h"
#include "sqstdblob.h"



// -------------------------------- helper macros --------------------------------


#define __IS_RANGE(x,a,b)		( (x)>=(a) && (x)<=(b) )
#define __IS_ALPHA(x)			( __IS_RANGE((x),'a','z') || __IS_RANGE((x),'A','Z') )
#define __IS_NUM(x)				__IS_RANGE((x),'0','9')
#define __IS_IDENT_START(x)		( __IS_ALPHA(x) || ((x)=='_') )
#define __IS_IDENT_CHAR(x)		( __IS_ALPHA(x) || __IS_NUM(x) || ((x)=='_') )




// -------------------------------- helper functions --------------------------------


static void _parse_white(const char *&s)
{
	while(*s==' ' || *s=='\t' || *s=='\n' || *s=='\r') s++;
}


static bool _parse_ident(const char *&s,string &out)
{
	_parse_white(s);
	if(!__IS_IDENT_START(*s))
	{
		out.clear();
		return false;
	}
	const char *b = s++;
	while(__IS_IDENT_CHAR(*s)) s++;
	out.assign(b,s);
	return true;
}



// -------------------------------- _sq_get/_sq_push template specializations --------------------------------


template<> bool SqVM::_sq_get(std::string &out,int depth)
{
	if(SQ_FAILED(sq_tostring(vm,depth)))
	{
		out.clear();
		return false;
	}
	const char *s=NULL;
	if(SQ_FAILED(sq_getstring(vm,-1,&s)) || !s)
	{
		out.clear();
		sq_remove(vm,-1);
		return false;
	}
	out=s;
	sq_remove(vm,-1);
	return true;
}







// -------------------------------- SqRef --------------------------------


int SqRef::_get_base(const char *name)
{
	if(!handle || !handle->vm)
		return int(0x8000000);
	HSQUIRRELVM vm = handle->vm->vm;
	int top = sq_gettop(vm);
	sq_pushobject(vm,handle->hobj);
	sq_pushstring(vm,name,-1);
	if(SQ_SUCCEEDED(sq_get(vm,-2)))
		return top;
	sq_settop(vm,top);
	return int(0x8000000);
}

int SqRef::_set_base(const char *name)
{
	if(!handle || !handle->vm)
		return int(0x8000000);
	HSQUIRRELVM vm = handle->vm->vm;
	int top = sq_gettop(vm);
	sq_pushobject(vm,handle->hobj);
	sq_pushstring(vm,name,-1);
	return top;
}




// -------------------------------- ObjectHandle --------------------------------


SqVM::ObjectHandle::ObjectHandle(SqVM &_vm) : vm(&_vm), refcount(0)
{
	sq_resetobject(&hobj);

	next = vm->first_free_handle;
	prev = NULL;
	vm->first_free_handle = this;
}

void SqVM::ObjectHandle::Free()
{
	if(vm)
	{
		sq_release(vm->vm,&hobj);

		// just to be sure
		sq_resetobject(&hobj);
		refcount = 0;
	}

	// unbind from the busy list
	if(next)	next->prev = prev;
	if(prev)	prev->next = next;
	else if(vm)	vm->first_busy_handle = next;

	// bind to free list (delete self if VM no longer exists)
	if(!vm)
	{
		delete this;
		return;
	}
	next = vm->first_free_handle;
	prev = NULL;
	vm->first_free_handle = this;
}






// -------------------------------- SqVM --------------------------------


void SqVM::print_callback(HSQUIRRELVM vm, const SQChar *fmt, ...)
{
	std::string out;

	va_list arg;
	
	va_start(arg,fmt);
	int len = vsnprintf(NULL,0,fmt,arg) + 1;
	out.resize(len);
	va_end(arg);
	
	va_start(arg,fmt);
	vsnprintf((char*)out.data(),len,fmt,arg);
	out.resize(len-1);

	va_end(arg);

	xsq_print(out.c_str());
}

void SqVM::print_error_callback(HSQUIRRELVM vm, const SQChar *fmt, ...)
{
	std::string out;

	va_list arg;
	
	va_start(arg,fmt);
	int len = vsnprintf(NULL,0,fmt,arg) + 1;
	out.resize(len);
	va_end(arg);
	
	va_start(arg,fmt);
	vsnprintf((char*)out.data(),len,fmt,arg);
	out.resize(len-1);
	va_end(arg);

	xsq_error(out.c_str());
}


void SqVM::print_stack_trace(HSQUIRRELVM vm)
{
    SQStackInfos stack_info;
    SQInteger stack_depth = 1;
 
    print_error_callback(vm,"  Stack Dump:\n");
    while( SQ_SUCCEEDED(sq_stackinfos(vm,stack_depth,&stack_info)) )
	{
        const SQChar *func_name = (stack_info.funcname) ? stack_info.funcname : "???";
        const SQChar *source_file = (stack_info.source) ? stack_info.source : "???";
        print_error_callback(vm,"    %2d: %s (%s:%d)\n", stack_depth, func_name, source_file, stack_info.line);
        stack_depth++;
    }
}
 
int SqVM::print_runtime_error(HSQUIRRELVM vm)
{
    const SQChar* error_message = NULL;
    if(sq_gettop(vm) >= 1)
	{
        if(SQ_SUCCEEDED(sq_getstring(vm,2,&error_message)))
            print_error_callback(vm,"Script runtime error: %s.\n", error_message);
        print_stack_trace(vm);
    }
    return 0;
}
 
void SqVM::print_compile_error(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column)
{
    print_error_callback(vm,"Script compile error: %s:%d:%d : %s.\n", file, line, column, description);
}







void SqVM::Init(int stack_size)
{
	last_stack_size = stack_size;

	DeInit();
	if(vm) sq_close(vm);

    vm = sq_open(stack_size);
	sq_setforeignptr(vm,this);

    sq_setprintfunc(vm, print_callback, print_error_callback);
    sq_setcompilererrorhandler(vm, print_compile_error);
    sq_newclosure(vm, print_runtime_error, 0);
    sq_seterrorhandler(vm);

	sq_pushroottable(vm);		sqstd_register_mathlib(vm);
	sq_pushroottable(vm);		sqstd_register_stringlib(vm);
	sq_pushroottable(vm);		sqstd_register_bloblib(vm);

	for(int i=0;i<(int)__xsq_register::regs().size();i++)
		__xsq_register::regs()[i](vm);
}

void SqVM::DeInit()
{
	// delete free handles
	ObjectHandle *h = first_free_handle;
	while(h)
	{
		ObjectHandle *n = h->next;
		delete h;
		h = n;
	}
	first_free_handle = NULL;

	// unbind busy handles
	h = first_busy_handle;
	while(h)
	{
		h->vm = NULL;
		h = h->next;
	}
	first_busy_handle = NULL;

	// close VM
	if(vm) sq_close(vm);

	script_files.clear();
}

void SqVM::Reset()
{
	vector<ScriptFile> files = script_files;

	Init(last_stack_size);
	for(int i=0;i<(int)files.size();i++)
		AddFile(files[i].path.c_str());
}



bool SqVM::DoFile(const char *path)
{
    sq_pushroottable(vm);
    if(SQ_FAILED(sqstd_dofile(vm, path, 0, 1)))
    {
		sq_pop(vm,1);
		return false;
    }
    sq_pop(vm,1);
	return true;
}

bool SqVM::DoString(const char *code)
{
    if(SQ_FAILED(sq_compilebuffer(vm, code, sizeof(SQChar)*strlen(code), "script", SQTrue)))
        return false;
 
    sq_pushroottable(vm);
    if (SQ_FAILED(sq_call(vm, 1, SQFalse, SQTrue)))
    {
		sq_pop(vm,1);
		return false;
    }
    sq_pop(vm,1);
	return true;
}

bool SqVM::AddFile(const char *path)
{
	ScriptFile sf;
	sf.path = path;
	sf.timestamp = xsq_getfiletime(path);
	for(int i=0;i<(int)script_files.size();i++)
		if(sf.path==script_files[i].path)
		{
			script_files[i].timestamp = sf.timestamp;
			sf.path.clear();
			break;
		}
	if(sf.path.size()>0)
		script_files.push_back(sf);

	return DoFile(path);
}

int SqVM::CheckFiles()
{
	int n = 0;
	for(int i=0;i<(int)script_files.size();i++)
	{
		ScriptFile &sf = script_files[i];
		unsigned long long t = xsq_getfiletime(sf.path.c_str());
		if(t!=sf.timestamp)
		{
			DoFile(sf.path.c_str());
			sf.timestamp = t;
			n++;
		}
	}
	return n;
}



bool SqVM::getstackobj(SqRef &out,int index)
{
	HSQOBJECT hobj;
	if(SQ_FAILED(sq_getstackobj(vm,index,&hobj)))
	{
		out.clear_ref();
		return false;
	}

	// make sure there is free handle ready
	if(!first_free_handle)
		new ObjectHandle(*this);	// this should add itself to the free list

	// get target ObjectHandle
	ObjectHandle *target = first_free_handle;

	// remove from free list
	first_free_handle = first_free_handle->next;
	if(first_free_handle)
		first_free_handle->prev = NULL;

	// add to busy list
	target->next = first_busy_handle;
	target->prev = NULL;
	if(first_busy_handle)
		first_busy_handle->prev = target;

	// set object
	target->hobj = hobj;
	out.set_ref(target);
	sq_addref(vm,&hobj);

	return true;
}


int SqVM::xsq_struct_push(const void *st,const char *members)
{
	string type, name;

	if(!st || !members)
	{
		sq_pushnull(vm);
		return 1;
	}


	// create table
	sq_newtable(vm);
	
	const char *s = members;
	const char *src = (const char*)st;
	while(1)
	{
		if(!_parse_ident(s,type))
		{
			if(*s) print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		if(!_parse_ident(s,name))
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		sq_pushstring(vm,name.c_str(),-1);
			 if(type=="int"		) { sq_pushinteger(vm,*(int*)src);					src+=sizeof(int);		}
		else if(type=="float"	) { sq_pushfloat(vm,*(float*)src);					src+=sizeof(float);		}
		else if(type=="string"	) { sq_pushstring(vm,((string*)src)->c_str(),-1);	src+=sizeof(string);	}
		else
		{
			print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
			sq_poptop(vm);	// remove name
			break;
		}

		if(!SQ_SUCCEEDED(sq_newslot(vm,-3,false)))
			print_error_callback(vm,"ERROR setting member '%s' in structure: \"%s\"\n",name.c_str(),members);

		_parse_white(s);
		if(*s!=';')
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			break;
		}
		s++;
	}

	return 1;
}


bool SqVM::xsq_struct_get(void *st,const char *members,int depth)
{
	string type, name;

	if(!st || !members)
		return false;


	// gen elments
	int top = sq_gettop(vm);
	if(depth<0) depth = top + depth + 1;
	
	const char *s = members;
	const char *src = (const char*)st;
	while(1)
	{
		if(!_parse_ident(s,type))
		{
			if(*s) print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		if(!_parse_ident(s,name))
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		sq_pushstring(vm,name.c_str(),-1);
		if(SQ_SUCCEEDED(sq_get(vm,depth)))
		{
				 if(type=="int"		) { _sq_get(*(int*)src,-1);			src+=sizeof(int);		}
			else if(type=="float"	) { _sq_get(*(float*)src,-1);		src+=sizeof(float);		}
			else if(type=="string"	) { _sq_get(*(string*)src,-1);		src+=sizeof(string);	}
			else
			{
				print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
				sq_poptop(vm);	// remove value
				return false;
			}
			sq_poptop(vm);	// remove value
		}
		else
		{
				 if(type=="int"		) { *(int*)src = 0;				src+=sizeof(int);		}
			else if(type=="float"	) { *(float*)src = 0;			src+=sizeof(float);		}
			else if(type=="string"	) { ((string*)src)->clear();	src+=sizeof(string);	}
			else
			{
				print_error_callback(vm,"ERROR bad type '%s' in structure: \"%s\"\n",type.c_str(),members);
				return false;
			}
		}


		_parse_white(s);
		if(*s!=';')
		{
			print_error_callback(vm,"ERROR parsing structure: \"%s\"\n   at: %s\n",members,s);
			return false;
		}
		s++;
	}

	return true;
}



#endif
