// ---------------- Library -- generated on 14.9.2017  22:24 ----------------



#pragma once

// ******************************** sqrat.h ********************************
//
// Sqrat: Squirrel C++ Binding Utility
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

/*! \mainpage Sqrat Main Page
 *
 * \section intro_sec Introduction
 *
 * Sqrat is a C++ library for Squirrel that facilitates exposing classes and other native functionality to Squirrel scripts. It models the underlying Squirrel API closely to give access to a wider range of functionality than other binding libraries. In addition to the binding library, Sqrat features a threading library and a module import library.
 *
 * \section install_sec Installation
 *
 * Sqrat only contains C++ headers so for installation you just need to copy the files in the include directory to some common header path.
 *
 * \section sec_faq Frequently Asked Questions
 *
 * Q: My application is crashing when I call sq_close. Why is this happening?<br>
 * A: All Sqrat::Object instances and derived type instances must be destroyed before calling sq_close.
 *
 * \section discuss_sec Discussion and User Support
 *
 * Discussion about Sqrat happens at the Squirrel language forum, the Bindings section
 * http://squirrel-lang.org/forums/default.aspx?g=topics&f=4
 *
 * \section bug_sec Bug Reporting
 *
 * Bug reports or feature enhancement requests and patches can be submitted at the SourceForge Sqrat site
 * https://sourceforge.net/p/scrat/sqrat/
 *
 * You're invited to make documentation suggestions for Sqrat. Together, we can make Sqrat as easy to understand as possible!
 */

#if !defined(_SCRAT_MAIN_H_)
#define _SCRAT_MAIN_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
/*
Copyright (c) 2003-2012 Alberto Demichelis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef _SQUIRREL_H_
#define _SQUIRREL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SQUIRREL_API
#define SQUIRREL_API extern
#endif

#if (defined(_WIN64) || defined(_LP64))
#ifndef _SQ64
#define _SQ64
#endif
#endif

#ifdef _SQ64

#ifdef _MSC_VER
typedef __int64 SQInteger;
typedef unsigned __int64 SQUnsignedInteger;
typedef unsigned __int64 SQHash; /*should be the same size of a pointer*/
#else
typedef long long SQInteger;
typedef unsigned long long SQUnsignedInteger;
typedef unsigned long long SQHash; /*should be the same size of a pointer*/
#endif
typedef int SQInt32; 
typedef unsigned int SQUnsignedInteger32;
#else 
typedef int SQInteger;
typedef int SQInt32; /*must be 32 bits(also on 64bits processors)*/
typedef unsigned int SQUnsignedInteger32; /*must be 32 bits(also on 64bits processors)*/
typedef unsigned int SQUnsignedInteger;
typedef unsigned int SQHash; /*should be the same size of a pointer*/
#endif


#ifdef SQUSEDOUBLE
typedef double SQFloat;
#else
typedef float SQFloat;
#endif

#if defined(SQUSEDOUBLE) && !defined(_SQ64) || !defined(SQUSEDOUBLE) && defined(_SQ64)
#ifdef _MSC_VER
typedef __int64 SQRawObjectVal; //must be 64bits
#else
typedef long long SQRawObjectVal; //must be 64bits
#endif
#define SQ_OBJECT_RAWINIT() { _unVal.raw = 0; }
#else
typedef SQUnsignedInteger SQRawObjectVal; //is 32 bits on 32 bits builds and 64 bits otherwise
#define SQ_OBJECT_RAWINIT()
#endif

#ifndef SQ_ALIGNMENT // SQ_ALIGNMENT shall be less than or equal to SQ_MALLOC alignments, and its value shall be power of 2.
#if defined(SQUSEDOUBLE) || defined(_SQ64)
#define SQ_ALIGNMENT 8
#else
#define SQ_ALIGNMENT 4
#endif
#endif

typedef void* SQUserPointer;
typedef SQUnsignedInteger SQBool;
typedef SQInteger SQRESULT;

#define SQTrue	(1)
#define SQFalse	(0)

struct SQVM;
struct SQTable;
struct SQArray;
struct SQString;
struct SQClosure;
struct SQGenerator;
struct SQNativeClosure;
struct SQUserData;
struct SQFunctionProto;
struct SQRefCounted;
struct SQClass;
struct SQInstance;
struct SQDelegable;
struct SQOuter;

#ifdef _UNICODE
#define SQUNICODE
#endif

#ifdef SQUNICODE
#if (defined(_MSC_VER) && _MSC_VER >= 1400) // 1400 = VS8

#if !defined(_NATIVE_WCHAR_T_DEFINED) //this is if the compiler considers wchar_t as native type
#define wchar_t unsigned short
#endif

#else
typedef unsigned short wchar_t;
#endif

typedef wchar_t SQChar;
#define _SC(a) L##a
#define	scstrcmp	wcscmp
#define scsprintf	swprintf
#define scstrlen	wcslen
#define scstrtod	wcstod
#ifdef _SQ64
#define scstrtol	_wcstoi64
#else
#define scstrtol	wcstol
#endif
#define scatoi		_wtoi
#define scstrtoul	wcstoul
#define scvsprintf	vswprintf
#define scstrstr	wcsstr
#define scisspace	iswspace
#define scisdigit	iswdigit
#define scisxdigit	iswxdigit
#define scisalpha	iswalpha
#define sciscntrl	iswcntrl
#define scisalnum	iswalnum
#define scprintf	wprintf
#define MAX_CHAR 0xFFFF
#else
typedef char SQChar;
#define _SC(a) a
#define	scstrcmp	strcmp
#define scsprintf	sprintf
#define scstrlen	strlen
#define scstrtod	strtod
#ifdef _SQ64
#ifdef _MSC_VER
#define scstrtol	_strtoi64
#else
#define scstrtol	strtoll
#endif
#else
#define scstrtol	strtol
#endif
#define scatoi		atoi
#define scstrtoul	strtoul
#define scvsprintf	vsprintf
#define scstrstr	strstr
#define scisspace	isspace
#define scisdigit	isdigit
#define scisxdigit	isxdigit
#define sciscntrl	iscntrl
#define scisalpha	isalpha
#define scisalnum	isalnum
#define scprintf	printf
#define MAX_CHAR 0xFF
#endif

#ifdef _SQ64
#define _PRINT_INT_PREC _SC("ll")
#define _PRINT_INT_FMT _SC("%lld")
#else
#define _PRINT_INT_FMT _SC("%d")
#endif

#define SQUIRREL_VERSION	_SC("Squirrel 3.0.3 stable")
#define SQUIRREL_COPYRIGHT	_SC("Copyright (C) 2003-2012 Alberto Demichelis")
#define SQUIRREL_AUTHOR		_SC("Alberto Demichelis")
#define SQUIRREL_VERSION_NUMBER	303

#define SQ_VMSTATE_IDLE			0
#define SQ_VMSTATE_RUNNING		1
#define SQ_VMSTATE_SUSPENDED	2

#define SQUIRREL_EOB 0
#define SQ_BYTECODE_STREAM_TAG	0xFAFA

#define SQOBJECT_REF_COUNTED	0x08000000
#define SQOBJECT_NUMERIC		0x04000000
#define SQOBJECT_DELEGABLE		0x02000000
#define SQOBJECT_CANBEFALSE		0x01000000

#define SQ_MATCHTYPEMASKSTRING (-99999)

#define _RT_MASK 0x00FFFFFF
#define _RAW_TYPE(type) (type&_RT_MASK)

#define _RT_NULL			0x00000001
#define _RT_INTEGER			0x00000002
#define _RT_FLOAT			0x00000004
#define _RT_BOOL			0x00000008
#define _RT_STRING			0x00000010
#define _RT_TABLE			0x00000020
#define _RT_ARRAY			0x00000040
#define _RT_USERDATA		0x00000080
#define _RT_CLOSURE			0x00000100
#define _RT_NATIVECLOSURE	0x00000200
#define _RT_GENERATOR		0x00000400
#define _RT_USERPOINTER		0x00000800
#define _RT_THREAD			0x00001000
#define _RT_FUNCPROTO		0x00002000
#define _RT_CLASS			0x00004000
#define _RT_INSTANCE		0x00008000
#define _RT_WEAKREF			0x00010000
#define _RT_OUTER			0x00020000

typedef enum tagSQObjectType{
	OT_NULL =			(_RT_NULL|SQOBJECT_CANBEFALSE),
	OT_INTEGER =		(_RT_INTEGER|SQOBJECT_NUMERIC|SQOBJECT_CANBEFALSE),
	OT_FLOAT =			(_RT_FLOAT|SQOBJECT_NUMERIC|SQOBJECT_CANBEFALSE),
	OT_BOOL =			(_RT_BOOL|SQOBJECT_CANBEFALSE),
	OT_STRING =			(_RT_STRING|SQOBJECT_REF_COUNTED),
	OT_TABLE =			(_RT_TABLE|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_ARRAY =			(_RT_ARRAY|SQOBJECT_REF_COUNTED),
	OT_USERDATA =		(_RT_USERDATA|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_CLOSURE =		(_RT_CLOSURE|SQOBJECT_REF_COUNTED),
	OT_NATIVECLOSURE =	(_RT_NATIVECLOSURE|SQOBJECT_REF_COUNTED),
	OT_GENERATOR =		(_RT_GENERATOR|SQOBJECT_REF_COUNTED),
	OT_USERPOINTER =	_RT_USERPOINTER,
	OT_THREAD =			(_RT_THREAD|SQOBJECT_REF_COUNTED) ,
	OT_FUNCPROTO =		(_RT_FUNCPROTO|SQOBJECT_REF_COUNTED), //internal usage only
	OT_CLASS =			(_RT_CLASS|SQOBJECT_REF_COUNTED),
	OT_INSTANCE =		(_RT_INSTANCE|SQOBJECT_REF_COUNTED|SQOBJECT_DELEGABLE),
	OT_WEAKREF =		(_RT_WEAKREF|SQOBJECT_REF_COUNTED),
	OT_OUTER =			(_RT_OUTER|SQOBJECT_REF_COUNTED) //internal usage only
}SQObjectType;

#define ISREFCOUNTED(t) (t&SQOBJECT_REF_COUNTED)


typedef union tagSQObjectValue
{
	struct SQTable *pTable;
	struct SQArray *pArray;
	struct SQClosure *pClosure;
	struct SQOuter *pOuter;
	struct SQGenerator *pGenerator;
	struct SQNativeClosure *pNativeClosure;
	struct SQString *pString;
	struct SQUserData *pUserData;
	SQInteger nInteger;
	SQFloat fFloat;
	SQUserPointer pUserPointer;
	struct SQFunctionProto *pFunctionProto;
	struct SQRefCounted *pRefCounted;
	struct SQDelegable *pDelegable;
	struct SQVM *pThread;
	struct SQClass *pClass;
	struct SQInstance *pInstance;
	struct SQWeakRef *pWeakRef;
	SQRawObjectVal raw;
}SQObjectValue;


typedef struct tagSQObject
{
	SQObjectType _type;
	SQObjectValue _unVal;
}SQObject;

typedef struct  tagSQMemberHandle{
	SQBool _static;
	SQInteger _index;
}SQMemberHandle;

typedef struct tagSQStackInfos{
	const SQChar* funcname;
	const SQChar* source;
	SQInteger line;
}SQStackInfos;

typedef struct SQVM* HSQUIRRELVM;
typedef SQObject HSQOBJECT;
typedef SQMemberHandle HSQMEMBERHANDLE;
typedef SQInteger (*SQFUNCTION)(HSQUIRRELVM);
typedef SQInteger (*SQRELEASEHOOK)(SQUserPointer,SQInteger size);
typedef void (*SQCOMPILERERROR)(HSQUIRRELVM,const SQChar * /*desc*/,const SQChar * /*source*/,SQInteger /*line*/,SQInteger /*column*/);
typedef void (*SQPRINTFUNCTION)(HSQUIRRELVM,const SQChar * ,...);
typedef void (*SQDEBUGHOOK)(HSQUIRRELVM /*v*/, SQInteger /*type*/, const SQChar * /*sourcename*/, SQInteger /*line*/, const SQChar * /*funcname*/);
typedef SQInteger (*SQWRITEFUNC)(SQUserPointer,SQUserPointer,SQInteger);
typedef SQInteger (*SQREADFUNC)(SQUserPointer,SQUserPointer,SQInteger);

typedef SQInteger (*SQLEXREADFUNC)(SQUserPointer);

typedef struct tagSQRegFunction{
	const SQChar *name;
	SQFUNCTION f;
	SQInteger nparamscheck;
	const SQChar *typemask;
}SQRegFunction;

typedef struct tagSQFunctionInfo {
	SQUserPointer funcid;
	const SQChar *name;
	const SQChar *source;
}SQFunctionInfo;

/*vm*/
SQUIRREL_API HSQUIRRELVM sq_open(SQInteger initialstacksize);
SQUIRREL_API HSQUIRRELVM sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize);
SQUIRREL_API void sq_seterrorhandler(HSQUIRRELVM v);
SQUIRREL_API void sq_close(HSQUIRRELVM v);
SQUIRREL_API void sq_setforeignptr(HSQUIRRELVM v,SQUserPointer p);
SQUIRREL_API SQUserPointer sq_getforeignptr(HSQUIRRELVM v);
SQUIRREL_API void sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc,SQPRINTFUNCTION errfunc);
SQUIRREL_API SQPRINTFUNCTION sq_getprintfunc(HSQUIRRELVM v);
SQUIRREL_API SQPRINTFUNCTION sq_geterrorfunc(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_suspendvm(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_wakeupvm(HSQUIRRELVM v,SQBool resumedret,SQBool retval,SQBool raiseerror,SQBool throwerror);
SQUIRREL_API SQInteger sq_getvmstate(HSQUIRRELVM v);
SQUIRREL_API SQInteger sq_getversion();

/*compiler*/
SQUIRREL_API SQRESULT sq_compile(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror);
SQUIRREL_API SQRESULT sq_compilebuffer(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror);
SQUIRREL_API void sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable);
SQUIRREL_API void sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable);
SQUIRREL_API void sq_setcompilererrorhandler(HSQUIRRELVM v,SQCOMPILERERROR f);

/*stack operations*/
SQUIRREL_API void sq_push(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_pop(HSQUIRRELVM v,SQInteger nelemstopop);
SQUIRREL_API void sq_poptop(HSQUIRRELVM v);
SQUIRREL_API void sq_remove(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQInteger sq_gettop(HSQUIRRELVM v);
SQUIRREL_API void sq_settop(HSQUIRRELVM v,SQInteger newtop);
SQUIRREL_API SQRESULT sq_reservestack(HSQUIRRELVM v,SQInteger nsize);
SQUIRREL_API SQInteger sq_cmp(HSQUIRRELVM v);
SQUIRREL_API void sq_move(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx);

/*object creation handling*/
SQUIRREL_API SQUserPointer sq_newuserdata(HSQUIRRELVM v,SQUnsignedInteger size);
SQUIRREL_API void sq_newtable(HSQUIRRELVM v);
SQUIRREL_API void sq_newtableex(HSQUIRRELVM v,SQInteger initialcapacity);
SQUIRREL_API void sq_newarray(HSQUIRRELVM v,SQInteger size);
SQUIRREL_API void sq_newclosure(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars);
SQUIRREL_API SQRESULT sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask);
SQUIRREL_API SQRESULT sq_bindenv(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_pushstring(HSQUIRRELVM v,const SQChar *s,SQInteger len);
SQUIRREL_API void sq_pushfloat(HSQUIRRELVM v,SQFloat f);
SQUIRREL_API void sq_pushinteger(HSQUIRRELVM v,SQInteger n);
SQUIRREL_API void sq_pushbool(HSQUIRRELVM v,SQBool b);
SQUIRREL_API void sq_pushuserpointer(HSQUIRRELVM v,SQUserPointer p);
SQUIRREL_API void sq_pushnull(HSQUIRRELVM v);
SQUIRREL_API SQObjectType sq_gettype(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_typeof(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQInteger sq_getsize(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQHash sq_gethash(HSQUIRRELVM v, SQInteger idx);
SQUIRREL_API SQRESULT sq_getbase(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQBool sq_instanceof(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_tostring(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b);
SQUIRREL_API SQRESULT sq_getstring(HSQUIRRELVM v,SQInteger idx,const SQChar **c);
SQUIRREL_API SQRESULT sq_getinteger(HSQUIRRELVM v,SQInteger idx,SQInteger *i);
SQUIRREL_API SQRESULT sq_getfloat(HSQUIRRELVM v,SQInteger idx,SQFloat *f);
SQUIRREL_API SQRESULT sq_getbool(HSQUIRRELVM v,SQInteger idx,SQBool *b);
SQUIRREL_API SQRESULT sq_getthread(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread);
SQUIRREL_API SQRESULT sq_getuserpointer(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p);
SQUIRREL_API SQRESULT sq_getuserdata(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag);
SQUIRREL_API SQRESULT sq_settypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag);
SQUIRREL_API SQRESULT sq_gettypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag);
SQUIRREL_API void sq_setreleasehook(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook);
SQUIRREL_API SQChar *sq_getscratchpad(HSQUIRRELVM v,SQInteger minsize);
SQUIRREL_API SQRESULT sq_getfunctioninfo(HSQUIRRELVM v,SQInteger level,SQFunctionInfo *fi);
SQUIRREL_API SQRESULT sq_getclosureinfo(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger *nparams,SQUnsignedInteger *nfreevars);
SQUIRREL_API SQRESULT sq_getclosurename(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setnativeclosurename(HSQUIRRELVM v,SQInteger idx,const SQChar *name);
SQUIRREL_API SQRESULT sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p);
SQUIRREL_API SQRESULT sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag);
SQUIRREL_API SQRESULT sq_setclassudsize(HSQUIRRELVM v, SQInteger idx, SQInteger udsize);
SQUIRREL_API SQRESULT sq_newclass(HSQUIRRELVM v,SQBool hasbase);
SQUIRREL_API SQRESULT sq_createinstance(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setattributes(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getattributes(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getclass(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API void sq_weakref(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getdefaultdelegate(HSQUIRRELVM v,SQObjectType t);
SQUIRREL_API SQRESULT sq_getmemberhandle(HSQUIRRELVM v,SQInteger idx,HSQMEMBERHANDLE *handle);
SQUIRREL_API SQRESULT sq_getbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle);
SQUIRREL_API SQRESULT sq_setbyhandle(HSQUIRRELVM v,SQInteger idx,const HSQMEMBERHANDLE *handle);

/*object manipulation*/
SQUIRREL_API void sq_pushroottable(HSQUIRRELVM v);
SQUIRREL_API void sq_pushregistrytable(HSQUIRRELVM v);
SQUIRREL_API void sq_pushconsttable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_setroottable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_setconsttable(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);
SQUIRREL_API SQRESULT sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
SQUIRREL_API SQRESULT sq_set(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_get(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawget(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawset(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_rawdeleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
SQUIRREL_API SQRESULT sq_newmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic);
SQUIRREL_API SQRESULT sq_rawnewmember(HSQUIRRELVM v,SQInteger idx,SQBool bstatic);
SQUIRREL_API SQRESULT sq_arrayappend(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_arraypop(HSQUIRRELVM v,SQInteger idx,SQBool pushval); 
SQUIRREL_API SQRESULT sq_arrayresize(HSQUIRRELVM v,SQInteger idx,SQInteger newsize); 
SQUIRREL_API SQRESULT sq_arrayreverse(HSQUIRRELVM v,SQInteger idx); 
SQUIRREL_API SQRESULT sq_arrayremove(HSQUIRRELVM v,SQInteger idx,SQInteger itemidx);
SQUIRREL_API SQRESULT sq_arrayinsert(HSQUIRRELVM v,SQInteger idx,SQInteger destpos);
SQUIRREL_API SQRESULT sq_setdelegate(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getdelegate(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_clone(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_setfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
SQUIRREL_API SQRESULT sq_next(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_getweakrefval(HSQUIRRELVM v,SQInteger idx);
SQUIRREL_API SQRESULT sq_clear(HSQUIRRELVM v,SQInteger idx);

/*calls*/
SQUIRREL_API SQRESULT sq_call(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror);
SQUIRREL_API SQRESULT sq_resume(HSQUIRRELVM v,SQBool retval,SQBool raiseerror);
SQUIRREL_API const SQChar *sq_getlocal(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx);
SQUIRREL_API SQRESULT sq_getcallee(HSQUIRRELVM v);
SQUIRREL_API const SQChar *sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
SQUIRREL_API SQRESULT sq_throwerror(HSQUIRRELVM v,const SQChar *err);
SQUIRREL_API SQRESULT sq_throwobject(HSQUIRRELVM v);
SQUIRREL_API void sq_reseterror(HSQUIRRELVM v);
SQUIRREL_API void sq_getlasterror(HSQUIRRELVM v);

/*raw object handling*/
SQUIRREL_API SQRESULT sq_getstackobj(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po);
SQUIRREL_API void sq_pushobject(HSQUIRRELVM v,HSQOBJECT obj);
SQUIRREL_API void sq_addref(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API SQBool sq_release(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API SQUnsignedInteger sq_getrefcount(HSQUIRRELVM v,HSQOBJECT *po);
SQUIRREL_API void sq_resetobject(HSQOBJECT *po);
SQUIRREL_API const SQChar *sq_objtostring(const HSQOBJECT *o);
SQUIRREL_API SQBool sq_objtobool(const HSQOBJECT *o);
SQUIRREL_API SQInteger sq_objtointeger(const HSQOBJECT *o);
SQUIRREL_API SQFloat sq_objtofloat(const HSQOBJECT *o);
SQUIRREL_API SQUserPointer sq_objtouserpointer(const HSQOBJECT *o);
SQUIRREL_API SQRESULT sq_getobjtypetag(const HSQOBJECT *o,SQUserPointer * typetag);

/*GC*/
SQUIRREL_API SQInteger sq_collectgarbage(HSQUIRRELVM v);
SQUIRREL_API SQRESULT sq_resurrectunreachable(HSQUIRRELVM v);

/*serialization*/
SQUIRREL_API SQRESULT sq_writeclosure(HSQUIRRELVM vm,SQWRITEFUNC writef,SQUserPointer up);
SQUIRREL_API SQRESULT sq_readclosure(HSQUIRRELVM vm,SQREADFUNC readf,SQUserPointer up);

/*mem allocation*/
SQUIRREL_API void *sq_malloc(SQUnsignedInteger size);
SQUIRREL_API void *sq_realloc(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize);
SQUIRREL_API void sq_free(void *p,SQUnsignedInteger size);

/*debug*/
SQUIRREL_API SQRESULT sq_stackinfos(HSQUIRRELVM v,SQInteger level,SQStackInfos *si);
SQUIRREL_API void sq_setdebughook(HSQUIRRELVM v);
SQUIRREL_API void sq_setnativedebughook(HSQUIRRELVM v,SQDEBUGHOOK hook);

/*UTILITY MACRO*/
#define sq_isnumeric(o) ((o)._type&SQOBJECT_NUMERIC)
#define sq_istable(o) ((o)._type==OT_TABLE)
#define sq_isarray(o) ((o)._type==OT_ARRAY)
#define sq_isfunction(o) ((o)._type==OT_FUNCPROTO)
#define sq_isclosure(o) ((o)._type==OT_CLOSURE)
#define sq_isgenerator(o) ((o)._type==OT_GENERATOR)
#define sq_isnativeclosure(o) ((o)._type==OT_NATIVECLOSURE)
#define sq_isstring(o) ((o)._type==OT_STRING)
#define sq_isinteger(o) ((o)._type==OT_INTEGER)
#define sq_isfloat(o) ((o)._type==OT_FLOAT)
#define sq_isuserpointer(o) ((o)._type==OT_USERPOINTER)
#define sq_isuserdata(o) ((o)._type==OT_USERDATA)
#define sq_isthread(o) ((o)._type==OT_THREAD)
#define sq_isnull(o) ((o)._type==OT_NULL)
#define sq_isclass(o) ((o)._type==OT_CLASS)
#define sq_isinstance(o) ((o)._type==OT_INSTANCE)
#define sq_isbool(o) ((o)._type==OT_BOOL)
#define sq_isweakref(o) ((o)._type==OT_WEAKREF)
#define sq_type(o) ((o)._type)

/* deprecated */
#define sq_createslot(v,n) sq_newslot(v,n,SQFalse)

#define SQ_OK (0)
#define SQ_ERROR (-1)

#define SQ_FAILED(res) (res<0)
#define SQ_SUCCEEDED(res) (res>=0)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQUIRREL_H_*/

// <--- back to sqrat.h

// ---- #include "sqrat/sqratTable.h"
// ---> including sqratTable.h
//
// SqratTable: Table Binding
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_TABLE_H_)
#define _SCRAT_TABLE_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratTable.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
//
// SqratObject: Referenced Squirrel Object Wrapper
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_OBJECT_H_)
#define _SCRAT_OBJECT_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratObject.h
#include <string.h>

// ---- #include "sqratAllocator.h"
// ---> including sqratAllocator.h
//
// SqratAllocator: Custom Class Allocation/Deallocation
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_ALLOCATOR_H_)
#define _SCRAT_ALLOCATOR_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratAllocator.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratAllocator.h
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
//
// SqratTypes: Type Translators
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_TYPES_H_)
#define _SCRAT_TYPES_H_

#ifdef SQUNICODE
#include <cstdlib>
#include <cstring>
#endif

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratTypes.h
#include <string>

// ---- #include "sqratClassType.h"
// ---> including sqratClassType.h
//
// SqratClassType: Type Translators
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//    1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
//    2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
//    3. This notice may not be removed or altered from any source
//    distribution.
//

#if !defined(_SCRAT_CLASSTYPE_H_)
#define _SCRAT_CLASSTYPE_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratClassType.h
#include <typeinfo>

// ---- #include "sqratUtil.h"
// ---> including sqratUtil.h
//
// SqratUtil: Squirrel Utilities
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_UTIL_H_)
#define _SCRAT_UTIL_H_

#include <cassert>
#include <map>
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratUtil.h
#include <string.h>

#if defined(SCRAT_USE_CXX11_OPTIMIZATIONS)
#include <unordered_map>
#endif

namespace Sqrat {

/// @cond DEV

#if defined(SCRAT_USE_CXX11_OPTIMIZATIONS)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Define an unordered map for Sqrat to use based on whether SCRAT_USE_CXX11_OPTIMIZATIONS is defined or not
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class Key, class T>
    struct unordered_map {
        typedef std::unordered_map<Key, T> type;
    };
#else
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Define an unordered map for Sqrat to use based on whether SCRAT_USE_CXX11_OPTIMIZATIONS is defined or not
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class Key, class T>
    struct unordered_map {
        typedef std::map<Key, T> type;
    };
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Define an inline function to avoid MSVC's "conditional expression is constant" warning
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
    template <typename T>
    inline T _c_def(T value) { return value; }
    #define SQRAT_CONST_CONDITION(value) _c_def(value)
#else
    #define SQRAT_CONST_CONDITION(value) value
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(SCRAT_EXPORT)
    #if defined(_WIN32)
        // Windows compilers need a specific keyword for export
        #define SQRAT_API __declspec(dllexport)
    #else
        #if __GNUC__ >= 4
            // GCC 4 has special keywords for showing/hiding symbols,
            // the same keyword is used for both importing and exporting
            #define SQRAT_API __attribute__ ((__visibility__ ("default")))
        #else
            // GCC < 4 has no mechanism to explicitly hide symbols, everything's exported
            #define SQRAT_API

        #endif
    #endif
#elif defined(SCRAT_IMPORT)
    #if defined(_WIN32)
        // Windows compilers need a specific keyword for import
        #define SQRAT_API __declspec(dllimport)
    #else
        #if __GNUC__ >= 4
            // GCC 4 has special keywords for showing/hiding symbols,
            // the same keyword is used for both importing and exporting
            #define SQRAT_API __attribute__ ((__visibility__ ("default")))
        #else
            // GCC < 4 has no mechanism to explicitly hide symbols, everything's exported
            #define SQRAT_API
        #endif
    #endif
#else
    #define SQRAT_API
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Define macros for internal error handling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined (SCRAT_NO_ERROR_CHECKING)
    #define SQCATCH(vm)          if (SQRAT_CONST_CONDITION(false))
    #define SQCATCH_NOEXCEPT(vm) if (SQRAT_CONST_CONDITION(false))
    #define SQCLEAR(vm)
    #define SQRETHROW(vm)
    #define SQTHROW(vm, err)
    #define SQTRY()
    #define SQWHAT(vm)           _SC("")
    #define SQWHAT_NOEXCEPT(vm)  _SC("")
#elif defined (SCRAT_USE_EXCEPTIONS)
    #define SQCATCH(vm)          } catch (const Sqrat::Exception& e)
    #define SQCATCH_NOEXCEPT(vm) if (SQRAT_CONST_CONDITION(false))
    #define SQCLEAR(vm)
    #ifdef _MSC_VER // avoid MSVC's "unreachable code" warning
        #define SQRETHROW(vm)      if (SQRAT_CONST_CONDITION(true)) throw
        #define SQTHROW(vm, err)   if (SQRAT_CONST_CONDITION(true)) throw Sqrat::Exception(err)
    #else
        #define SQRETHROW(vm)      throw
        #define SQTHROW(vm, err)   throw Sqrat::Exception(err)
    #endif
    #define SQTRY()              try {
    #define SQWHAT(vm)           e.Message().c_str()
    #define SQWHAT_NOEXCEPT(vm)  _SC("")
#else
    #define SQCATCH(vm)          if (SQRAT_CONST_CONDITION(false))
    #define SQCATCH_NOEXCEPT(vm) if (Error::Occurred(vm))
    #define SQCLEAR(vm)          Error::Clear(vm)
    #define SQRETHROW(vm)
    #define SQTHROW(vm, err)     Error::Throw(vm, err)
    #define SQTRY()
    #define SQWHAT(vm)           _SC("")
    #define SQWHAT_NOEXCEPT(vm)  Error::Message(vm).c_str()
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Removes unused variable warnings in a way that Doxygen can understand
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SQUNUSED(const T&) {
}

/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a string that is definitely compatible with the version of Squirrel being used (normally this is std::string)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::basic_string<SQChar> string;

/// @cond DEV
#ifdef SQUNICODE
/* from http://stackoverflow.com/questions/15333259/c-stdwstring-to-stdstring-quick-and-dirty-conversion-for-use-as-key-in,
   only works for ASCII chars */
/**
* Convert a std::string into a std::wstring
*/
static std::wstring string_to_wstring(const std::string& str)
{
    return std::wstring(str.begin(), str.end());
}

/**
* Convert a std::wstring into a std::string
*/
static std::string wstring_to_string(const std::wstring& wstr)
{
    return std::string(wstr.begin(), wstr.end());
}

#endif // SQUNICODE

template <class T>
class SharedPtr;

template <class T>
class WeakPtr;

/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class that defines a VM that can be used as a fallback VM in case no other one is given to a piece of code
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DefaultVM {
private:

    static HSQUIRRELVM& staticVm() {
        static HSQUIRRELVM vm;
        return vm;
    }

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the default VM
    ///
    /// \return Default VM
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static HSQUIRRELVM Get() {
        return staticVm();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets the default VM to a given VM
    ///
    /// \param vm New default VM
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void Set(HSQUIRRELVM vm) {
        staticVm() = vm;
    }
};

#if !defined (SCRAT_NO_ERROR_CHECKING) && !defined (SCRAT_USE_EXCEPTIONS)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The class that must be used to deal with errors that Sqrat has
///
/// \remarks
/// When documentation in Sqrat says, "This function MUST have its error handled if it occurred," that
/// means that after the function has been run, you must call Error::Occurred to see if the function
/// ran successfully. If the function did not run successfully, then you MUST either call Error::Clear
/// or Error::Message to clear the error buffer so new ones may occur and Sqrat does not get confused.
///
/// \remarks
/// Any error thrown inside of a bound C++ function will be thrown in the given Squirrel VM and
/// automatically handled.
///
/// \remarks
/// If compiling with SCRAT_USE_EXCEPTIONS defined, Sqrat will throw exceptions instead of using this
/// class to handle errors. This means that functions must be enclosed in try blocks that catch
/// Sqrat::Exception instead of checking for errors with Error::Occurred.
///
/// \remarks
/// If compiling with SCRAT_NO_ERROR_CHECKING defined, Sqrat will run significantly faster,
/// but it will no longer check for errors and the Error class itself will not be defined.
/// In this mode, a Squirrel script may crash the C++ application if errors occur in it.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Error {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Clears the error associated with a given VM
    ///
    /// \param vm Target VM
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void Clear(HSQUIRRELVM vm) {
        sq_pushregistrytable(vm);
        sq_pushstring(vm, "__error", -1);
        sq_rawdeleteslot(vm, -2, false);
        sq_pop(vm, 1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Clears the error associated with a given VM and returns the associated error message
    ///
    /// \param vm Target VM
    ///
    /// \return String containing a nice error message
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static string Message(HSQUIRRELVM vm) {
        sq_pushregistrytable(vm);
        sq_pushstring(vm, "__error", -1);
        if (SQ_SUCCEEDED(sq_rawget(vm, -2))) {
            string** ud;
            sq_getuserdata(vm, -1, (SQUserPointer*)&ud, NULL);
            sq_pop(vm, 1);
            string err = **ud;
            sq_pushstring(vm, "__error", -1);
            sq_rawdeleteslot(vm, -2, false);
            sq_pop(vm, 1);
            return err;
        }
        sq_pushstring(vm, "__error", -1);
        sq_rawdeleteslot(vm, -2, false);
        sq_pop(vm, 1);
        return string(_SC("an unknown error has occurred"));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns whether a Sqrat error has occurred with a given VM
    ///
    /// \param vm Target VM
    ///
    /// \return True if an error has occurred, otherwise false
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool Occurred(HSQUIRRELVM vm) {
        sq_pushregistrytable(vm);
        sq_pushstring(vm, "__error", -1);
        if (SQ_SUCCEEDED(sq_rawget(vm, -2))) {
            sq_pop(vm, 2);
            return true;
        }
        sq_pop(vm, 1);
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Raises an error in a given VM with a given error message
    ///
    /// \param vm  Target VM
    /// \param err A nice error message
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void Throw(HSQUIRRELVM vm, const string& err) {
        sq_pushregistrytable(vm);
        sq_pushstring(vm, "__error", -1);
        if (SQ_FAILED(sq_rawget(vm, -2))) {
            sq_pushstring(vm, "__error", -1);
            string** ud = reinterpret_cast<string**>(sq_newuserdata(vm, sizeof(string*)));
            *ud = new string(err);
            sq_setreleasehook(vm, -1, &error_cleanup_hook);
            sq_rawset(vm, -3);
            sq_pop(vm, 1);
            return;
        }
        sq_pop(vm, 2);
    }

private:

    Error() {}

    static SQInteger error_cleanup_hook(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        string** ud = reinterpret_cast<string**>(ptr);
        delete *ud;
        return 0;
    }
};
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Tells Sqrat whether Squirrel error handling should be used
///
/// \remarks
/// If true, if a runtime error occurs during the execution of a call, the VM will invoke its error handler.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ErrorHandling {
private:

    static bool& errorHandling() {
        static bool eh = true;
        return eh;
    }

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns whether Squirrel error handling is enabled
    ///
    /// \return True if error handling is enabled, otherwise false
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsEnabled() {
        return errorHandling();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Enables or disables Squirrel error handling
    ///
    /// \param enable True to enable, false to disable
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void Enable(bool enable) {
        errorHandling() = enable;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sqrat exception class
///
/// \remarks
/// Used only when SCRAT_USE_EXCEPTIONS is defined (see Sqrat::Error)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Exception {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs an exception
    ///
    /// \param msg A nice error message
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Exception(const string& msg) : message(msg) {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param ex Exception to copy
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Exception(const Exception& ex) : message(ex.message) {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns a string identifying the exception
    ///
    /// \return A nice error message
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const string& Message() const {
        return message;
    }

private:

    string message;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns a string that has been formatted to give a nice type error message (for usage with Class::SquirrelFunc)
///
/// \param vm           VM the error occurred with
/// \param idx          Index on the stack of the argument that had a type error
/// \param expectedType The name of the type that the argument should have been
///
/// \return String containing a nice type error message
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline string FormatTypeError(HSQUIRRELVM vm, SQInteger idx, const string& expectedType) {
    string err = _SC("wrong type (") + expectedType + _SC(" expected");
#if (SQUIRREL_VERSION_NUMBER>= 200) && (SQUIRREL_VERSION_NUMBER < 300) // Squirrel 2.x
    err = err + _SC(")");
#else // Squirrel 3.x
    if (SQ_SUCCEEDED(sq_typeof(vm, idx))) {
        const SQChar* actualType;
        sq_tostring(vm, -1);
        sq_getstring(vm, -1, &actualType);
        sq_pop(vm, 2);
        err = err + _SC(", got ") + actualType + _SC(")");
    } else {
        err = err + _SC(", got unknown)");
    }
#endif
    return err;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns the last error that occurred with a Squirrel VM (not associated with Sqrat errors)
///
/// \param vm Target VM
///
/// \return String containing a nice error message
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline string LastErrorString(HSQUIRRELVM vm) {
    const SQChar* sqErr;
    sq_getlasterror(vm);
    if (sq_gettype(vm, -1) == OT_NULL) {
        sq_pop(vm, 1);
        return string();
    }
    sq_tostring(vm, -1);
    sq_getstring(vm, -1, &sqErr);
    sq_pop(vm, 2);
    return string(sqErr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// A smart pointer that retains shared ownership of an object through a pointer (see std::shared_ptr)
///
/// \tparam T Type of pointer
///
/// \remarks
/// SharedPtr exists to automatically delete an object when all references to it are destroyed.
///
/// \remarks
/// std::shared_ptr was not used because it is a C++11 feature.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class SharedPtr
{
    template <class U>
    friend class SharedPtr;

    template <class U>
    friend class WeakPtr;

private:

    T*            m_Ptr;
    unsigned int* m_RefCount;
    unsigned int* m_RefCountRefCount;

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a new SharedPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SharedPtr() :
    m_Ptr             (NULL),
    m_RefCount        (NULL),
    m_RefCountRefCount(NULL)
    {

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a new SharedPtr from an object allocated with the new operator
    ///
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SharedPtr(T* ptr) :
    m_Ptr             (NULL),
    m_RefCount        (NULL),
    m_RefCountRefCount(NULL)
    {
        Init(ptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a new SharedPtr from an object allocated with the new operator
    ///
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \tparam U Type of pointer (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    SharedPtr(U* ptr) :
    m_Ptr             (NULL),
    m_RefCount        (NULL),
    m_RefCountRefCount(NULL)
    {
        Init(ptr);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy SharedPtr to copy
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SharedPtr(const SharedPtr<T>& copy)
    {
        if (copy.Get() != NULL)
        {
            m_Ptr              = copy.Get();
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCount         += 1;
            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy SharedPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    SharedPtr(const SharedPtr<U>& copy)
    {
        if (copy.Get() != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.Get());
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCount         += 1;
            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy WeakPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    SharedPtr(const WeakPtr<U>& copy)
    {
        if (copy.m_Ptr != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.m_Ptr);
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCount         += 1;
            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructs the owned object if no more SharedPtr link to it
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~SharedPtr()
    {
        Reset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns the SharedPtr
    ///
    /// \param copy SharedPtr to copy
    ///
    /// \return The SharedPtr itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SharedPtr<T>& operator=(const SharedPtr<T>& copy)
    {
        if (this != &copy)
        {
            Reset();

            if (copy.Get() != NULL)
            {
                m_Ptr              = copy.Get();
                m_RefCount         = copy.m_RefCount;
                m_RefCountRefCount = copy.m_RefCountRefCount;

                *m_RefCount         += 1;
                *m_RefCountRefCount += 1;
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns the SharedPtr
    ///
    /// \param copy SharedPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /// \return The SharedPtr itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    SharedPtr<T>& operator=(const SharedPtr<U>& copy)
    {
        Reset();

        if (copy.Get() != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.Get());
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCount         += 1;
            *m_RefCountRefCount += 1;
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up a new object to be managed by the SharedPtr
    ///
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Init(T* ptr)
    {
        Reset();

        m_Ptr = ptr;

        m_RefCount = new unsigned int;
        *m_RefCount = 1;

        m_RefCountRefCount = new unsigned int;
        *m_RefCountRefCount = 1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up a new object to be managed by the SharedPtr
    ///
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    void Init(U* ptr)
    {
        Reset();

        m_Ptr = static_cast<T*>(ptr);

        m_RefCount = new unsigned int;
        *m_RefCount = 1;

        m_RefCountRefCount = new unsigned int;
        *m_RefCountRefCount = 1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Clears the owned object for this SharedPtr and deletes it if no more SharedPtr link to it
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Reset()
    {
        if (m_Ptr != NULL)
        {
            *m_RefCount         -= 1;
            *m_RefCountRefCount -= 1;

            if (*m_RefCount == 0)
            {
                delete m_Ptr;
            }

            if (*m_RefCountRefCount == 0)
            {
                delete m_RefCount;
                delete m_RefCountRefCount;
            }

            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Checks if there is NOT an associated managed object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator!() const
    {
        return m_Ptr == NULL;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another SharedPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool operator ==(const SharedPtr<U>& right) const
    {
        return m_Ptr == right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another SharedPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator ==(const SharedPtr<T>& right) const
    {
        return m_Ptr == right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool friend operator ==(const SharedPtr<T>& left, const U* right)
    {
        return left.m_Ptr == right;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool friend operator ==(const SharedPtr<T>& left, const T* right)
    {
        return left.m_Ptr == right;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool friend operator ==(const U* left, const SharedPtr<T>& right)
    {
        return left == right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool friend operator ==(const T* left, const SharedPtr<T>& right)
    {
        return left == right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another SharedPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool operator !=(const SharedPtr<U>& right) const
    {
        return m_Ptr != right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another SharedPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator !=(const SharedPtr<T>& right) const
    {
        return m_Ptr != right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool friend operator !=(const SharedPtr<T>& left, const U* right)
    {
        return left.m_Ptr != right;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool friend operator !=(const SharedPtr<T>& left, const T* right)
    {
        return left.m_Ptr != right;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename U>
    bool friend operator !=(const U* left, const SharedPtr<T>& right)
    {
        return left != right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Compares with another pointer
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool friend operator !=(const T* left, const SharedPtr<T>& right)
    {
        return left != right.m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dereferences pointer to the managed object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    T& operator*() const
    {
        assert(m_Ptr != NULL); // fails when dereferencing a null SharedPtr
        return *m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dereferences pointer to the managed object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    T* operator->() const
    {
        assert(m_Ptr != NULL); // fails when dereferencing a null SharedPtr
        return m_Ptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the underlying pointer
    ///
    /// \return Pointer to the managed object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    T* Get() const
    {
        return m_Ptr;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// A smart pointer that retains a non-owning ("weak") reference to an object that is managed by SharedPtr (see std::weak_ptr)
///
/// \tparam T Type of pointer
///
/// \remarks
/// WeakPtr exists for when an object that may be deleted at any time needs to be accessed if it exists.
///
/// \remarks
/// std::weak_ptr was not used because it is a C++11 feature.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class WeakPtr
{
    template <class U>
    friend class SharedPtr;

private:

    T*            m_Ptr;
    unsigned int* m_RefCount;
    unsigned int* m_RefCountRefCount;

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a new WeakPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WeakPtr() :
    m_Ptr             (NULL),
    m_RefCount        (NULL),
    m_RefCountRefCount(NULL)
    {

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy WeakPtr to copy
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WeakPtr(const WeakPtr<T>& copy)
    {
        if (copy.m_Ptr != NULL)
        {
            m_Ptr              = copy.m_Ptr;
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy WeakPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    WeakPtr(const WeakPtr<U>& copy)
    {
        if (copy.m_Ptr != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.m_Ptr);
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param copy SharedPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    WeakPtr(const SharedPtr<U>& copy)
    {
        if (copy.Get() != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.Get());
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCountRefCount += 1;
        }
        else
        {
            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructs the WeakPtr but has no influence on the object that was managed
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~WeakPtr()
    {
        Reset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns the WeakPtr
    ///
    /// \param copy WeakPtr to copy
    ///
    /// \return The WeakPtr itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WeakPtr<T>& operator=(const WeakPtr<T>& copy)
    {
        if (this != &copy)
        {
            Reset();

            if (copy.m_Ptr != NULL)
            {
                m_Ptr              = copy.m_Ptr;
                m_RefCount         = copy.m_RefCount;
                m_RefCountRefCount = copy.m_RefCountRefCount;

                *m_RefCountRefCount += 1;
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns the WeakPtr
    ///
    /// \param copy WeakPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /// \return The WeakPtr itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    WeakPtr<T>& operator=(const WeakPtr<U>& copy)
    {
        Reset();

        if (copy.m_Ptr != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.m_Ptr);
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCountRefCount += 1;
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns the WeakPtr
    ///
    /// \param copy SharedPtr to copy
    ///
    /// \tparam U Type of copy (usually doesnt need to be defined explicitly)
    ///
    /// \return The WeakPtr itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class U>
    WeakPtr<T>& operator=(const SharedPtr<U>& copy)
    {
        Reset();

        if (copy.Get() != NULL)
        {
            m_Ptr              = static_cast<T*>(copy.Get());
            m_RefCount         = copy.m_RefCount;
            m_RefCountRefCount = copy.m_RefCountRefCount;

            *m_RefCountRefCount += 1;
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Checks whether the managed object exists
    ///
    /// \return True if the managed object does not exist, false otherwise
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool Expired() const
    {
        return (m_Ptr == NULL || *m_RefCount == 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creates a new SharedPtr that shares ownership of the managed object
    ///
    /// \return A SharedPtr which shares ownership of the managed object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SharedPtr<T> Lock() const
    {
        SharedPtr<T> other;
        if (m_Ptr != NULL)
        {
            other.m_Ptr              = m_Ptr;
            other.m_RefCount         = m_RefCount;
            other.m_RefCountRefCount = m_RefCountRefCount;

            *m_RefCount         += 1;
            *m_RefCountRefCount += 1;
        }
        return other;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Clears the associated object for this WeakPtr
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Reset()
    {
        if (m_Ptr != NULL)
        {
            *m_RefCountRefCount -= 1;

            if (*m_RefCountRefCount == 0)
            {
                delete m_RefCount;
                delete m_RefCountRefCount;
            }

            m_Ptr              = NULL;
            m_RefCount         = NULL;
            m_RefCountRefCount = NULL;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @cond DEV
/// Used internally to get and manipulate the underlying type of variables - retrieved from cppreference.com
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct remove_const                                                {typedef T type;};
template<class T> struct remove_const<const T>                                       {typedef T type;};
template<class T> struct remove_volatile                                             {typedef T type;};
template<class T> struct remove_volatile<volatile T>                                 {typedef T type;};
template<class T> struct remove_cv                                                   {typedef typename remove_volatile<typename remove_const<T>::type>::type type;};
template<class T> struct is_pointer_helper                                           {static const bool value = false;};
template<class T> struct is_pointer_helper<T*>                                       {static const bool value = true;};
template<class T> struct is_pointer_helper<SharedPtr<T> >                            {static const bool value = true;};
template<class T> struct is_pointer_helper<WeakPtr<T> >                              {static const bool value = true;};
template<class T> struct is_pointer : is_pointer_helper<typename remove_cv<T>::type> {};
template<class T> struct is_reference                                                {static const bool value = false;};
template<class T> struct is_reference<T&>                                            {static const bool value = true;};
/// @endcond

}

#endif

// <--- back to sqratClassType.h

namespace Sqrat
{

/// @cond DEV

// The copy function for a class
typedef SQInteger (*COPYFUNC)(HSQUIRRELVM, SQInteger, const void*);

// Every Squirrel class instance made by Sqrat has its type tag set to a AbstractStaticClassData object that is unique per C++ class
struct AbstractStaticClassData {
    AbstractStaticClassData() {}
    virtual ~AbstractStaticClassData() {}
    virtual SQUserPointer Cast(SQUserPointer ptr, SQUserPointer classType) = 0;
    AbstractStaticClassData* baseClass;
    string                   className;
    COPYFUNC                 copyFunc;
};

// StaticClassData keeps track of the nearest base class B and the class associated with itself C in order to cast C++ pointers to the right base class
template<class C, class B>
struct StaticClassData : public AbstractStaticClassData {
    virtual SQUserPointer Cast(SQUserPointer ptr, SQUserPointer classType) {
        if (classType != this) {
            ptr = baseClass->Cast(static_cast<B*>(static_cast<C*>(ptr)), classType);
        }
        return ptr;
    }
};

// Every Squirrel class object created by Sqrat in every VM has its own unique ClassData object stored in the registry table of the VM
template<class C>
struct ClassData {
    HSQOBJECT classObj;
    HSQOBJECT getTable;
    HSQOBJECT setTable;
    SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> instances;
    SharedPtr<AbstractStaticClassData> staticData;
};

// Lookup static class data by type_info rather than a template because C++ cannot export generic templates
class _ClassType_helper {
public:
#if defined(SCRAT_IMPORT)
    static SQRAT_API WeakPtr<AbstractStaticClassData>& _getStaticClassData(const std::type_info* type);
#else
    struct compare_type_info {
        bool operator ()(const std::type_info* left, const std::type_info* right) const {
            return left->before(*right) != 0;
        }
    };
    static SQRAT_API WeakPtr<AbstractStaticClassData>& _getStaticClassData(const std::type_info* type) {
        static std::map<const std::type_info*, WeakPtr<AbstractStaticClassData>, compare_type_info> data;
        return data[type];
    }
#endif
};

// Internal helper class for managing classes
template<class C>
class ClassType {
public:

    static inline ClassData<C>* getClassData(HSQUIRRELVM vm) {
        sq_pushregistrytable(vm);
        sq_pushstring(vm, "__classes", -1);
#ifndef NDEBUG
        SQRESULT r = sq_rawget(vm, -2);
        assert(SQ_SUCCEEDED(r)); // fails if getClassData is called when the data does not exist for the given VM yet (bind the class)
#else
        sq_rawget(vm, -2);
#endif
        sq_pushstring(vm, ClassName().c_str(), -1);
#ifndef NDEBUG
        r = sq_rawget(vm, -2);
        assert(SQ_SUCCEEDED(r)); // fails if getClassData is called when the data does not exist for the given VM yet (bind the class)
#else
        sq_rawget(vm, -2);
#endif
        ClassData<C>** ud;
        sq_getuserdata(vm, -1, (SQUserPointer*)&ud, NULL);
        sq_pop(vm, 3);
        return *ud;
    }

    static WeakPtr<AbstractStaticClassData>& getStaticClassData() {
        return _ClassType_helper::_getStaticClassData(&typeid(C));
    }

    static inline bool hasClassData(HSQUIRRELVM vm) {
        if (!getStaticClassData().Expired()) {
            sq_pushregistrytable(vm);
            sq_pushstring(vm, "__classes", -1);
            if (SQ_SUCCEEDED(sq_rawget(vm, -2))) {
                sq_pushstring(vm, ClassName().c_str(), -1);
                if (SQ_SUCCEEDED(sq_rawget(vm, -2))) {
                    sq_pop(vm, 3);
                    return true;
                }
                sq_pop(vm, 1);
            }
            sq_pop(vm, 1);
        }
        return false;
    }

    static inline AbstractStaticClassData*& BaseClass() {
        assert(getStaticClassData().Expired() == false); // fails because called before a Sqrat::Class for this type exists
        return getStaticClassData().Lock()->baseClass;
    }

    static inline string& ClassName() {
        assert(getStaticClassData().Expired() == false); // fails because called before a Sqrat::Class for this type exists
        return getStaticClassData().Lock()->className;
    }

    static inline COPYFUNC& CopyFunc() {
        assert(getStaticClassData().Expired() == false); // fails because called before a Sqrat::Class for this type exists
        return getStaticClassData().Lock()->copyFunc;
    }

    static SQInteger DeleteInstance(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance;
        return 0;
    }

    static void PushInstance(HSQUIRRELVM vm, C* ptr) {
        if (!ptr) {
            sq_pushnull(vm);
            return;
        }

        ClassData<C>* cd = getClassData(vm);

        typename unordered_map<C*, HSQOBJECT>::type::iterator it = cd->instances->find(ptr);
        if (it != cd->instances->end()) {
            sq_pushobject(vm, it->second);
            return;
        }

        sq_pushobject(vm, cd->classObj);
        sq_createinstance(vm, -1);
        sq_remove(vm, -2);
        sq_setinstanceup(vm, -1, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, -1, &DeleteInstance);
        sq_getstackobj(vm, -1, &((*cd->instances)[ptr]));
    }

    static void PushInstanceCopy(HSQUIRRELVM vm, const C& value) {
        sq_pushobject(vm, getClassData(vm)->classObj);
        sq_createinstance(vm, -1);
        sq_remove(vm, -2);
#ifndef NDEBUG
        SQRESULT result = CopyFunc()(vm, -1, &value);
        assert(SQ_SUCCEEDED(result)); // fails when trying to copy an object defined as non-copyable
#else
        CopyFunc()(vm, -1, &value);
#endif
    }

    static C* GetInstance(HSQUIRRELVM vm, SQInteger idx, bool nullAllowed = false) {
        AbstractStaticClassData* classType = NULL;
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = NULL;
        if (hasClassData(vm)) /* type checking only done if the value has type data else it may be enum */
        {
            if (nullAllowed && sq_gettype(vm, idx) == OT_NULL) {
                return NULL;
            }

            classType = getStaticClassData().Lock().Get();

#if !defined (SCRAT_NO_ERROR_CHECKING)
            if (SQ_FAILED(sq_getinstanceup(vm, idx, (SQUserPointer*)&instance, classType))) {
                SQTHROW(vm, FormatTypeError(vm, idx, ClassName()));
                return NULL;
            }

            if (instance == NULL) {
                SQTHROW(vm, _SC("got unconstructed native class (call base.constructor in the constructor of Squirrel classes that extend native classes)"));
                return NULL;
            }
#else
            sq_getinstanceup(vm, idx, (SQUserPointer*)&instance, 0);
#endif
        }
        else /* value is likely of integral type like enums, cannot return a pointer */
        {
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("unknown")));
            return NULL;
        }
        AbstractStaticClassData* actualType;
        sq_gettypetag(vm, idx, (SQUserPointer*)&actualType);
        if (actualType == NULL) {
            SQInteger top = sq_gettop(vm);
            sq_getclass(vm, idx);
            while (actualType == NULL) {
                sq_getbase(vm, -1);
                sq_gettypetag(vm, -1, (SQUserPointer*)&actualType);
            }
            sq_settop(vm, top);
        }
        if (classType != actualType) {
            return static_cast<C*>(actualType->Cast(instance->first, classType));
        }
        return static_cast<C*>(instance->first);
    }
};

/// @endcond

}

#endif

// <--- back to sqratTypes.h
// ---- #include "sqratUtil.h"
// ---> including sqratUtil.h
// <--- back to sqratTypes.h

namespace Sqrat {

/// @cond DEV

// copied from http://www.experts-exchange.com/Programming/Languages/CPP/A_223-Determing-if-a-C-type-is-convertable-to-another-at-compile-time.html
template <typename T1, typename T2>
struct is_convertible
{
private:
    struct True_ { char x[2]; };
    struct False_ { };

    static True_ helper(T2 const &);
    static False_ helper(...);

    static T1* dummy;

public:
    static bool const YES = (
        sizeof(True_) == sizeof(is_convertible::helper(*dummy))
    );
};

template <typename T, bool b>
struct popAsInt
{
    T value;
    popAsInt(HSQUIRRELVM vm, SQInteger idx)
    {
        SQObjectType value_type = sq_gettype(vm, idx);
        switch(value_type) {
        case OT_BOOL:
            SQBool sqValueb;
            sq_getbool(vm, idx, &sqValueb);
            value = static_cast<T>(sqValueb);
            break;
        case OT_INTEGER:
            SQInteger sqValue;
            sq_getinteger(vm, idx, &sqValue);
            value = static_cast<T>(sqValue);
            break;
        case OT_FLOAT:
            SQFloat sqValuef;
            sq_getfloat(vm, idx, &sqValuef);
			value = static_cast<T>(static_cast<int>(sqValuef));
            break;
        default:
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("integer")));
            value = static_cast<T>(0);
            break;
        }
    }
};

template <typename T>
struct popAsInt<T, false>
{
    T value;  // cannot be initialized because unknown constructor parameters
    popAsInt(HSQUIRRELVM /*vm*/, SQInteger /*idx*/)
    {
        // keep the current error message already set previously, do not touch that here
    }
};

template <typename T>
struct popAsFloat
{
    T value;
    popAsFloat(HSQUIRRELVM vm, SQInteger idx)
    {
        SQObjectType value_type = sq_gettype(vm, idx);
        switch(value_type) {
        case OT_BOOL:
            SQBool sqValueb;
            sq_getbool(vm, idx, &sqValueb);
            value = static_cast<T>(sqValueb);
            break;
        case OT_INTEGER:
            SQInteger sqValue; \
            sq_getinteger(vm, idx, &sqValue);
            value = static_cast<T>(sqValue);
            break;
        case OT_FLOAT:
            SQFloat sqValuef;
            sq_getfloat(vm, idx, &sqValuef);
            value = static_cast<T>(sqValuef);
            break;
        default:
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("float")));
            value = 0;
            break;
        }
    }
};

/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as copies
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/// \remarks
/// This specialization requires T to have a default constructor.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var {

    T value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        SQTRY()
        T* ptr = ClassType<T>::GetInstance(vm, idx);
        if (ptr != NULL) {
            value = *ptr;
#if !defined (SCRAT_NO_ERROR_CHECKING)
        } else if (is_convertible<T, SQInteger>::YES) { /* value is likely of integral type like enums */
            SQCLEAR(vm); // clear the previous error
            value = popAsInt<T, is_convertible<T, SQInteger>::YES>(vm, idx).value;
#endif
        } else {
            // initialize value to avoid warnings
            value = popAsInt<T, is_convertible<T, SQInteger>::YES>(vm, idx).value;
        }
        SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
            SQUNUSED(e); // avoid "unreferenced local variable" warning
#endif
            if (is_convertible<T, SQInteger>::YES) { /* value is likely of integral type like enums */
                value = popAsInt<T, is_convertible<T, SQInteger>::YES>(vm, idx).value;
            } else {
                SQRETHROW(vm);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const T& value) {
        if (ClassType<T>::hasClassData(vm))
            ClassType<T>::PushInstanceCopy(vm, value);
        else /* try integral type */
            pushAsInt<T, is_convertible<T, SQInteger>::YES>().push(vm, value);
    }

private:

    template <class T2, bool b>
    struct pushAsInt {
        void push(HSQUIRRELVM vm, const T2& /*value*/) {
            assert(false); // fails because called before a Sqrat::Class for T exists and T is not convertible to SQInteger
            sq_pushnull(vm);
        }
    };

    template <class T2>
    struct pushAsInt<T2, true> {
        void push(HSQUIRRELVM vm, const T2& value) {
            sq_pushinteger(vm, static_cast<SQInteger>(value));
        }
    };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as references
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<T&> {

    T& value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(*ClassType<T>::GetInstance(vm, idx)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVarR to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, T& value) {
        if (ClassType<T>::hasClassData(vm))
            ClassType<T>::PushInstance(vm, &value);
        else /* try integral type */
            pushAsInt<T, is_convertible<T, SQInteger>::YES>().push(vm, value);
    }

private:

    template <class T2, bool b>
    struct pushAsInt {
        void push(HSQUIRRELVM vm, const T2& /*value*/) {
            assert(false); // fails because called before a Sqrat::Class for T exists and T is not convertible to SQInteger
            sq_pushnull(vm);
        }
    };

    template <class T2>
    struct pushAsInt<T2, true> {
        void push(HSQUIRRELVM vm, const T2& value) {
            sq_pushinteger(vm, static_cast<SQInteger>(value));
        }
    };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as pointers
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<T*> {

    T* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(ClassType<T>::GetInstance(vm, idx, true)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, T* value) {
        ClassType<T>::PushInstance(vm, value);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as pointers to const data
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<T* const> {

    T* const value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(ClassType<T>::GetInstance(vm, idx, true)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, T* const value) {
        ClassType<T>::PushInstance(vm, value);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as const references
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<const T&> {

    const T& value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(*ClassType<T>::GetInstance(vm, idx)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const T& value) {
        ClassType<T>::PushInstanceCopy(vm, value);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as const pointers
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<const T*> {

    const T* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(ClassType<T>::GetInstance(vm, idx, true)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const T* value) {
        ClassType<T>::PushInstance(vm, const_cast<T*>(value));
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push class instances to and from the stack as const pointers to const data
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct Var<const T* const> {

    const T* const value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) : value(ClassType<T>::GetInstance(vm, idx, true)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const T* const value) {
        ClassType<T>::PushInstance(vm, const_cast<T*>(value));
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get (as copies) and push (as references) class instances to and from the stack as a SharedPtr
///
/// \tparam T Type of instance (usually doesnt need to be defined explicitly)
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> void PushVarR(HSQUIRRELVM vm, T& value);
template<class T>
struct Var<SharedPtr<T> > {

    SharedPtr<T> value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as the given type
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        if (sq_gettype(vm, idx) != OT_NULL) {
            Var<T> instance(vm, idx);
            SQCATCH_NOEXCEPT(vm) {
                return;
            }
            value.Init(new T(instance.value));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a class object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const SharedPtr<T>& value) {
        PushVarR(vm, *value);
    }
};

// Integer types
#define SCRAT_INTEGER( type ) \
 template<> \
 struct Var<type> { \
     type value; \
     Var(HSQUIRRELVM vm, SQInteger idx) { \
         value = popAsInt<type, true>(vm, idx).value; \
     } \
     static void push(HSQUIRRELVM vm, const type& value) { \
         sq_pushinteger(vm, static_cast<SQInteger>(value)); \
     } \
 };\
 \
 template<> \
 struct Var<const type&> { \
     type value; \
     Var(HSQUIRRELVM vm, SQInteger idx) { \
         value = popAsInt<type, true>(vm, idx).value; \
     } \
     static void push(HSQUIRRELVM vm, const type& value) { \
         sq_pushinteger(vm, static_cast<SQInteger>(value)); \
     } \
 };

SCRAT_INTEGER(unsigned int)
SCRAT_INTEGER(signed int)
SCRAT_INTEGER(unsigned long)
SCRAT_INTEGER(signed long)
SCRAT_INTEGER(unsigned short)
SCRAT_INTEGER(signed short)
SCRAT_INTEGER(unsigned char)
SCRAT_INTEGER(signed char)
SCRAT_INTEGER(unsigned long long)
SCRAT_INTEGER(signed long long)

#ifdef _MSC_VER
#if defined(__int64)
SCRAT_INTEGER(unsigned __int64)
SCRAT_INTEGER(signed __int64)
#endif
#endif

// Float types
#define SCRAT_FLOAT( type ) \
 template<> \
 struct Var<type> { \
     type value; \
     Var(HSQUIRRELVM vm, SQInteger idx) { \
         value = popAsFloat<type>(vm, idx).value; \
     } \
     static void push(HSQUIRRELVM vm, const type& value) { \
         sq_pushfloat(vm, static_cast<SQFloat>(value)); \
     } \
 }; \
 \
 template<> \
 struct Var<const type&> { \
     type value; \
     Var(HSQUIRRELVM vm, SQInteger idx) { \
         value = popAsFloat<type>(vm, idx).value; \
     } \
     static void push(HSQUIRRELVM vm, const type& value) { \
         sq_pushfloat(vm, static_cast<SQFloat>(value)); \
     } \
 };

SCRAT_FLOAT(float)
SCRAT_FLOAT(double)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push bools to and from the stack
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<bool> {

    bool value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a bool
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        SQBool sqValue;
        sq_tobool(vm, idx, &sqValue);
        value = (sqValue != 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a bool on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const bool& value) {
        sq_pushbool(vm, static_cast<SQBool>(value));
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push const bool references to and from the stack
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const bool&> {

    bool value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a bool
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        SQBool sqValue;
        sq_tobool(vm, idx, &sqValue);
        value = (sqValue != 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a bool on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const bool& value) {
        sq_pushbool(vm, static_cast<SQBool>(value));
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push SQChar arrays to and from the stack (usually is a char array)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<SQChar*> {
private:

    HSQOBJECT obj; /* hold a reference to the object holding value during the Var struct lifetime*/
    HSQUIRRELVM v;

public:

    SQChar* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a character array
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        sq_tostring(vm, idx);
        sq_getstackobj(vm, -1, &obj);
        sq_getstring(vm, -1, (const SQChar**)&value);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
        v = vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~Var()
    {
        if(v && !sq_isnull(obj)) {
            sq_release(v, &obj);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a character array on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    /// \param len   Length of the string (defaults to finding the length by searching for a terminating null-character)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const SQChar* value, SQInteger len = -1) {
        sq_pushstring(vm, value, len);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push const SQChar arrays to and from the stack (usually is a const char array)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const SQChar*> {
private:

    HSQOBJECT obj; /* hold a reference to the object holding value during the Var struct lifetime*/
    HSQUIRRELVM v;

public:

    const SQChar* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a character array
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        sq_tostring(vm, idx);
        sq_getstackobj(vm, -1, &obj);
        sq_getstring(vm, -1, &value);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
        v = vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~Var()
    {
        if(v && !sq_isnull(obj)) {
            sq_release(v, &obj);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a character array on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    /// \param len   Length of the string (defaults to finding the length by searching for a terminating null-character)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const SQChar* value, SQInteger len = -1) {
        sq_pushstring(vm, value, len);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push strings to and from the stack (string is usually std::string)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<string> {

    string value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a string
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        const SQChar* ret;
        sq_tostring(vm, idx);
        sq_getstring(vm, -1, &ret);
        value = string(ret, sq_getsize(vm, -1));
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a string on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const string& value) {
        sq_pushstring(vm, value.c_str(), value.size());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push const string references to and from the stack as copies (strings are always copied)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const string&> {

    string value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a string
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        const SQChar* ret;
        sq_tostring(vm, idx);
        sq_getstring(vm, -1, &ret);
        value = string(ret, sq_getsize(vm, -1));
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a string on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const string& value) {
        sq_pushstring(vm, value.c_str(), value.size());
    }
};

#ifdef SQUNICODE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push std::string to and from the stack when SQChar is not char (must define SQUNICODE)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<std::string> {

    std::string value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a string
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        const SQChar* ret;
        sq_tostring(vm, idx);
        sq_getstring(vm, -1, &ret);
        value = wstring_to_string(string(ret, sq_getsize(vm, -1)));
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a string on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const std::string& value) {
        std::wstring s = string_to_wstring(value);
        sq_pushstring(vm, s.c_str(), s.size());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push const std::string references to and from the stack when SQChar is not char (must define SQUNICODE)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const std::string&> {

    std::string value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a string
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        const SQChar* ret;
        sq_tostring(vm, idx);
        sq_getstring(vm, -1, &ret);
        value = wstring_to_string(string(ret, sq_getsize(vm, -1)));
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a string on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const std::string& value) {
        std::wstring s = string_to_wstring(value);
        sq_pushstring(vm, s.c_str(), s.size());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push SQChar arrays to and from the stack when SQChar is not char (must define SQUNICODE)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<char*> {
private:

    HSQOBJECT obj;/* hold a reference to the object holding value during the Var struct lifetime*/
    HSQUIRRELVM v;

public:

    char* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a character array
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        std::string holder;
        const SQChar *sv;
        sq_tostring(vm, idx);
        sq_getstackobj(vm, -1, &obj);
        sq_getstring(vm, -1, &sv);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
        v = vm;
        holder = wstring_to_string(string(sv));
        value = strdup(holder.c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~Var()
    {
        if(v && !sq_isnull(obj)) {
            sq_release(v, &obj);
            free(value);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a character array on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    /// \param len   Length of the string (defaults to finding the length by searching for a terminating null-character)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const char* value, SQInteger len = -1) {
        sq_pushstring(vm, string_to_wstring(std::string(value)).c_str(), len);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push const SQChar arrays to and from the stack when SQChar is not char (must define SQUNICODE)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const char*> {
private:

    HSQOBJECT obj; /* hold a reference to the object holding value during the Var struct lifetime*/
    HSQUIRRELVM v;

public:

    char* value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a character array
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        std::string holder;
        const SQChar *sv;
        sq_tostring(vm, idx);
        sq_getstackobj(vm, -1, &obj);
        sq_getstring(vm, -1, &sv);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
        v = vm;
        holder = wstring_to_string(string(sv));
        value = strdup(holder.c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~Var()
    {
        if(v && !sq_isnull(obj)) {
            sq_release(v, &obj);
            free(value);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a character array on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    /// \param len   Length of the string (defaults to finding the length by searching for a terminating null-character)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const char* value, SQInteger len = -1) {
        sq_pushstring(vm, string_to_wstring(std::string(value)).c_str(), len);
    }
};
#endif


// Non-referencable type definitions
template<class T> struct is_referencable {static const bool value = true;};

#define SCRAT_MAKE_NONREFERENCABLE( type ) \
 template<> struct is_referencable<type> {static const bool value = false;};

SCRAT_MAKE_NONREFERENCABLE(unsigned int)
SCRAT_MAKE_NONREFERENCABLE(signed int)
SCRAT_MAKE_NONREFERENCABLE(unsigned long)
SCRAT_MAKE_NONREFERENCABLE(signed long)
SCRAT_MAKE_NONREFERENCABLE(unsigned short)
SCRAT_MAKE_NONREFERENCABLE(signed short)
SCRAT_MAKE_NONREFERENCABLE(unsigned char)
SCRAT_MAKE_NONREFERENCABLE(signed char)
SCRAT_MAKE_NONREFERENCABLE(unsigned long long)
SCRAT_MAKE_NONREFERENCABLE(signed long long)
SCRAT_MAKE_NONREFERENCABLE(float)
SCRAT_MAKE_NONREFERENCABLE(double)
SCRAT_MAKE_NONREFERENCABLE(bool)
SCRAT_MAKE_NONREFERENCABLE(string)

#ifdef _MSC_VER
#if defined(__int64)
SCRAT_MAKE_NONREFERENCABLE(unsigned __int64)
SCRAT_MAKE_NONREFERENCABLE(signed __int64)
#endif
#endif

#ifdef SQUNICODE
SCRAT_MAKE_NONREFERENCABLE(std::string)
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pushes a value on to a given VM's stack
///
/// \param vm    VM that the variable will be pushed on to the stack of
/// \param value The actual value being pushed
///
/// \tparam T Type of value (usually doesnt need to be defined explicitly)
///
/// \remarks
/// What this function does is defined by Sqrat::Var template specializations,
/// and thus you can create custom functionality for it by making new template specializations.
/// When making a custom type that is not referencable, you must use SCRAT_MAKE_NONREFERENCABLE( type )
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PushVar(HSQUIRRELVM vm, T* value) {
    Var<T*>::push(vm, value);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pushes a value on to a given VM's stack
///
/// \param vm    VM that the variable will be pushed on to the stack of
/// \param value The actual value being pushed
///
/// \tparam T Type of value (usually doesnt need to be defined explicitly)
///
/// \remarks
/// What this function does is defined by Sqrat::Var template specializations,
/// and thus you can create custom functionality for it by making new template specializations.
/// When making a custom type that is not referencable, you must use SCRAT_MAKE_NONREFERENCABLE( type )
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PushVar(HSQUIRRELVM vm, const T& value) {
    Var<T>::push(vm, value);
}


/// @cond DEV
template<class T, bool b>
struct PushVarR_helper {
    inline static void push(HSQUIRRELVM vm, T value) {
        PushVar<T>(vm, value);
    }
};
template<class T>
struct PushVarR_helper<T, false> {
    inline static void push(HSQUIRRELVM vm, const T& value) {
        PushVar<const T&>(vm, value);
    }
};
/// @endcond


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pushes a reference on to a given VM's stack (some types cannot be referenced and will be copied instead)
///
/// \param vm    VM that the reference will be pushed on to the stack of
/// \param value The actual referenced value being pushed
///
/// \tparam T Type of value (usually doesnt need to be defined explicitly)
///
/// \remarks
/// What this function does is defined by Sqrat::Var template specializations,
/// and thus you can create custom functionality for it by making new template specializations.
/// When making a custom type that is not referencable, you must use SCRAT_MAKE_NONREFERENCABLE( type )
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void PushVarR(HSQUIRRELVM vm, T& value) {
    if (!is_pointer<T>::value && is_referencable<typename remove_cv<T>::type>::value) {
        Var<T&>::push(vm, value);
    } else {
        PushVarR_helper<T, is_pointer<T>::value>::push(vm, value);
    }
}

}

#endif

// <--- back to sqratAllocator.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @cond DEV
/// utility taken from http://stackoverflow.com/questions/2733377/is-there-a-way-to-test-whether-a-c-class-has-a-default-constructor-other-than/2770326#2770326
/// may be obsolete in C++ 11
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
class is_default_constructible {
    template<int x>
    class receive_size{};

    template< class U >
    static int sfinae( receive_size< sizeof U() > * );

    template< class U >
    static char sfinae( ... );

public:
    enum { value = sizeof( sfinae<T>(0) ) == sizeof(int) };
};
/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DefaultAllocator is the allocator to use for Class that can both be constructed and copied
///
/// \tparam C Type of class
///
/// \remarks
/// There is mechanisms defined in this class that allow the Class::Ctor method to work properly (e.g. iNew).
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class DefaultAllocator {

    template <class T, bool b>
    struct NewC
    {
        T* p;
        NewC()
        {
           p = new T();
        }
    };

    template <class T>
    struct NewC<T, false>
    {
        T* p;
        NewC()
        {
           p = 0;
        }
    };

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
        SetInstance(vm, 1, NewC<C, is_default_constructible<C>::value >().p);
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @cond DEV
    /// following iNew functions are used only if constructors are bound via Ctor() in Sqrat::Class (safe to ignore)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger iNew(HSQUIRRELVM vm) {
        return New(vm);
    }

    template <typename A1>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    /// @endcond

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SetInstance(vm, idx, new C(*static_cast<const C*>(value)));
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NoConstructor is the allocator to use for Class that can NOT be constructed or copied
///
/// \tparam C Type of class
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class NoConstructor {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instance));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class (not allowed in this allocator)
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" constructing is not allowed"))).c_str());
#else
        SQUNUSED(vm);
        return 0;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type (not used in this allocator)
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SQUNUSED(vm);
        SQUNUSED(idx);
        SQUNUSED(value);
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" cloning is not allowed"))).c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CopyOnly is the allocator to use for Class that can be copied but not constructed
///
/// \tparam C Type of class
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class CopyOnly {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class (not allowed in this allocator)
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" constructing is not allowed"))).c_str());
#else
        SQUNUSED(vm);
        return 0;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SetInstance(vm, idx, new C(*static_cast<const C*>(value)));
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NoCopy is the allocator to use for Class that can be constructed but not copied
///
/// \tparam C Type of class
///
/// \remarks
/// There is mechanisms defined in this class that allow the Class::Ctor method to work properly (e.g. iNew).
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class NoCopy {

    template <class T, bool b>
    struct NewC
    {
        T* p;
        NewC()
        {
           p = new T();
        }
    };

    template <class T>
    struct NewC<T, false>
    {
        T* p;
        NewC()
        {
           p = 0;
        }
    };

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
        SetInstance(vm, 1, NewC<C, is_default_constructible<C>::value >().p);
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @cond DEV
    /// following iNew functions are used only if constructors are bound via Ctor() in Sqrat::Class (safe to ignore)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger iNew(HSQUIRRELVM vm) {
        return New(vm);
    }

    template <typename A1>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SetInstance(vm, 1, new C(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value
        ));
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    /// @endcond

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type (not used in this allocator)
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SQUNUSED(vm);
        SQUNUSED(idx);
        SQUNUSED(value);
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" cloning is not allowed"))).c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

}

#endif

// <--- back to sqratObject.h
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
// <--- back to sqratObject.h
// ---- #include "sqratOverloadMethods.h"
// ---> including sqratOverloadMethods.h
//
// SqratOverloadMethods: Overload Methods
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SQRAT_OVERLOAD_METHODS_H_)
#define _SQRAT_OVERLOAD_METHODS_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratOverloadMethods.h
// ---- #include <sqstdaux.h>
// ---> including sqstdaux.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTD_AUXLIB_H_
#define _SQSTD_AUXLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

SQUIRREL_API void sqstd_seterrorhandlers(HSQUIRRELVM v);
SQUIRREL_API void sqstd_printcallstack(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _SQSTD_AUXLIB_H_ */

// <--- back to sqratOverloadMethods.h
#include <sstream>
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
// <--- back to sqratOverloadMethods.h
// ---- #include "sqratUtil.h"
// ---> including sqratUtil.h
// <--- back to sqratOverloadMethods.h
// ---- #include "sqratGlobalMethods.h"
// ---> including sqratGlobalMethods.h
//
// SqratGlobalMethods: Global Methods
//

//
// Copyright (c) 2009 Brandon Jones
// Copyirght 2011 Li-Cheng (Andy) Tai
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_GLOBAL_METHODS_H_)
#define _SCRAT_GLOBAL_METHODS_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratGlobalMethods.h
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
// <--- back to sqratGlobalMethods.h

namespace Sqrat {

/// @cond DEV

//
// Squirrel Global Functions
//
template <class R>
class SqGlobal {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)();
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        R ret = (*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 1
    template <class A1, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 1) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 2
    template <class A1, class A2, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        Var<A14> a14(vm, startIdx + 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }
};


//
// reference return specialization
//

template <class R>
class SqGlobal<R&> {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)();
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        R& ret = (*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 1
    template <class A1, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 1) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 2
    template <class A1, class A2, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R& (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        Var<A14> a14(vm, startIdx + 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }
};


//
// void return specialization
//

template <>
class SqGlobal<void> {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)();
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        (*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 1
    template <class A1, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 1) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 2
    template <class A1, class A2, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, SQInteger startIdx, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
        Var<A1> a1(vm, startIdx);
        Var<A2> a2(vm, startIdx + 1);
        Var<A3> a3(vm, startIdx + 2);
        Var<A4> a4(vm, startIdx + 3);
        Var<A5> a5(vm, startIdx + 4);
        Var<A6> a6(vm, startIdx + 5);
        Var<A7> a7(vm, startIdx + 6);
        Var<A8> a8(vm, startIdx + 7);
        Var<A9> a9(vm, startIdx + 8);
        Var<A10> a10(vm, startIdx + 9);
        Var<A11> a11(vm, startIdx + 10);
        Var<A12> a12(vm, startIdx + 11);
        Var<A13> a13(vm, startIdx + 12);
        Var<A14> a14(vm, startIdx + 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value,
            a14.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
};


//
// Global Function Resolvers
//

// Arg Count 0
template <class R>
SQFUNCTION SqGlobalFunc(R (* /*method*/)()) {
    return &SqGlobal<R>::template Func0<false>;
}

// Arg Count 0
template <class R>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)()) {
    return &SqGlobal<R&>::template Func0<false>;
}

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1)) {
    return &SqGlobal<R>::template Func1<A1, 2, false>;
}

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1)) {
    return &SqGlobal<R&>::template Func1<A1, 2, false>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2)) {
    return &SqGlobal<R>::template Func2<A1, A2, 2, false>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2)) {
    return &SqGlobal<R&>::template Func2<A1, A2, 2, false>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R>::template Func3<A1, A2, A3, 2, false>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R&>::template Func3<A1, A2, A3, 2, false>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R>::template Func4<A1, A2, A3, A4, 2, false>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R&>::template Func4<A1, A2, A3, A4, 2, false>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R>::template Func5<A1, A2, A3, A4, A5, 2, false>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R&>::template Func5<A1, A2, A3, A4, A5, 2, false>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R>::template Func6<A1, A2, A3, A4, A5, A6, 2, false>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R&>::template Func6<A1, A2, A3, A4, A5, A6, 2, false>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R>::template Func7<A1, A2, A3, A4, A5, A6, A7, 2, false>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, 2, false>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 2, false>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 2, false>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 2, false>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 2, false>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 2, false>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 2, false>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 2, false>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 2, false>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 2, false>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 2, false>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 2, false>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 2, false>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 2, false>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 2, false>;
}


//
// Member Global Function Resolvers
//

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1)) {
    return &SqGlobal<R>::template Func1<A1, 1, false>;
}

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1)) {
    return &SqGlobal<R&>::template Func1<A1, 1, false>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2)) {
    return &SqGlobal<R>::template Func2<A1, A2, 1, false>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2)) {
    return &SqGlobal<R&>::template Func2<A1, A2, 1, false>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R>::template Func3<A1, A2, A3, 1, false>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R&>::template Func3<A1, A2, A3, 1, false>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R>::template Func4<A1, A2, A3, A4, 1, false>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R&>::template Func4<A1, A2, A3, A4, 1, false>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R>::template Func5<A1, A2, A3, A4, A5, 1, false>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R&>::template Func5<A1, A2, A3, A4, A5, 1, false>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R>::template Func6<A1, A2, A3, A4, A5, A6, 1, false>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R&>::template Func6<A1, A2, A3, A4, A5, A6, 1, false>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R>::template Func7<A1, A2, A3, A4, A5, A6, A7, 1, false>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, 1, false>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 1, false>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 1, false>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 1, false>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 1, false>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 1, false>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 1, false>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 1, false>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 1, false>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 1, false>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 1, false>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 1, false>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 1, false>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 1, false>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 1, false>;
}

/// @endcond

}

#endif

// <--- back to sqratOverloadMethods.h
// ---- #include "sqratMemberMethods.h"
// ---> including sqratMemberMethods.h
//
// SqratMemberMethods: Member Methods
//

//
// Copyright (c) 2009 Brandon Jones
// Copyright 2011 Li-Cheng (Andy) Tai
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_MEMBER_METHODS_H_)
#define _SCRAT_MEMBER_METHODS_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratMemberMethods.h
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
// <--- back to sqratMemberMethods.h

namespace Sqrat {

/// @cond DEV

//
// Squirrel Global Functions
//

template <class C, class R>
class SqMember {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        typedef R (C::*M)();
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        R ret = (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <bool overloaded /*= false*/>
    static SQInteger Func0C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)() const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        R ret = (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 1
    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 2
    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded  /*= false*/ >
    static SQInteger Func10C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/  >
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/>
    static SQInteger Func12C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }
};


//
// reference return specialization
//

template <class C, class R>
class SqMember<C, R&> {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)();
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        R& ret = (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <bool overloaded /*= false*/>
    static SQInteger Func0C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)() const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        R& ret = (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 1
    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 2
    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded  /*= false*/ >
    static SQInteger Func10C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }


    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/  >
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/>
    static SQInteger Func12C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R&(C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef R& (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        R& ret = (ptr->*method)(
                    a1.value,
                    a2.value,
                    a3.value,
                    a4.value,
                    a5.value,
                    a6.value,
                    a7.value,
                    a8.value,
                    a9.value,
                    a10.value,
                    a11.value,
                    a12.value,
                    a13.value,
                    a14.value
                );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }

};


//
// void return specialization
//

template <class C>
class SqMember<C, void> {
public:

    // Arg Count 0
    template <bool overloaded /*= false*/>
    static SQInteger Func0(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)();
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <bool overloaded /*= false*/>
    static SQInteger Func0C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)() const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        (ptr->*method)();
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 1
    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, bool overloaded /*= false*/>
    static SQInteger Func1C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 3) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 2
    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, bool overloaded /*= false*/>
    static SQInteger Func2C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 4) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 3
    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, bool overloaded /*= false*/>
    static SQInteger Func3C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 5) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 4
    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, bool overloaded /*= false*/>
    static SQInteger Func4C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 6) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 5
    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, bool overloaded /*= false*/>
    static SQInteger Func5C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 7) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 6
    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, bool overloaded /*= false*/>
    static SQInteger Func6C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 8) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, bool overloaded /*= false*/>
    static SQInteger Func7C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 9) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, bool overloaded /*= false*/>
    static SQInteger Func8C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 10) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, bool overloaded /*= false*/>
    static SQInteger Func9C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 11) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 10
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded /*= false*/>
    static SQInteger Func10(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, bool overloaded /*= false*/>
    static SQInteger Func10C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 12) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 11
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, bool overloaded /*= false*/>
    static SQInteger Func11C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 13) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 12
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/>
    static SQInteger Func12(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, bool overloaded /*= false*/>
    static SQInteger Func12C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 14) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 13
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, bool overloaded /*= false*/>
    static SQInteger Func13C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 15) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    // Arg Count 14
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value,
            a14.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, bool overloaded /*= false*/>
    static SQInteger Func14C(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != 16) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
        ptr = Var<C*>(vm, 1).value;
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm); // clear the previous error
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
        Var<A1> a1(vm, 2);
        Var<A2> a2(vm, 3);
        Var<A3> a3(vm, 4);
        Var<A4> a4(vm, 5);
        Var<A5> a5(vm, 6);
        Var<A6> a6(vm, 7);
        Var<A7> a7(vm, 8);
        Var<A8> a8(vm, 9);
        Var<A9> a9(vm, 10);
        Var<A10> a10(vm, 11);
        Var<A11> a11(vm, 12);
        Var<A12> a12(vm, 13);
        Var<A13> a13(vm, 14);
        Var<A14> a14(vm, 15);
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        (ptr->*method)(
            a1.value,
            a2.value,
            a3.value,
            a4.value,
            a5.value,
            a6.value,
            a7.value,
            a8.value,
            a9.value,
            a10.value,
            a11.value,
            a12.value,
            a13.value,
            a14.value
        );
        SQCATCH_NOEXCEPT(vm) {
            return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

};


//
// Member Function Resolvers
//

// Arg Count 0
template <class C, class R>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)()) {
    return &SqMember<C, R>::template Func0<false>;
}

template <class C, class R>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)() const) {
    return &SqMember<C, R>::template Func0C<false>;
}

template <class C, class R>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)()) {
    return &SqMember<C, R&>::template Func0<false>;
}

template <class C, class R>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)() const) {
    return &SqMember<C, R&>::template Func0C<false>;
}

// Arg Count 1
template <class C, class R, class A1>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1)) {
    return &SqMember<C, R>::template Func1<A1, false>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1) const) {
    return &SqMember<C, R>::template Func1C<A1, false>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1)) {
    return &SqMember<C, R&>::template Func1<A1, false>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1) const) {
    return &SqMember<C, R&>::template Func1C<A1, false>;
}

// Arg Count 2
template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2)) {
    return &SqMember<C, R>::template Func2<A1, A2, false>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2) const) {
    return &SqMember<C, R>::template Func2C<A1, A2, false>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2)) {
    return &SqMember<C, R&>::template Func2<A1, A2, false>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2) const) {
    return &SqMember<C, R&>::template Func2C<A1, A2, false>;
}

// Arg Count 3
template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3)) {
    return &SqMember<C, R>::template Func3<A1, A2, A3, false>;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3) const) {
    return &SqMember<C, R>::template Func3C<A1, A2, A3, false>;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3)) {
    return &SqMember<C, R&>::template Func3<A1, A2, A3, false>;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3) const) {
    return &SqMember<C, R&>::template Func3C<A1, A2, A3, false>;
}

// Arg Count 4
template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4)) {
    return &SqMember<C, R>::template Func4<A1, A2, A3, A4, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4) const) {
    return &SqMember<C, R>::template Func4C<A1, A2, A3, A4, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4)) {
    return &SqMember<C, R&>::template Func4<A1, A2, A3, A4, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4) const) {
    return &SqMember<C, R&>::template Func4C<A1, A2, A3, A4, false>;
}

// Arg Count 5
template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqMember<C, R>::template Func5<A1, A2, A3, A4, A5, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5) const) {
    return &SqMember<C, R>::template Func5C<A1, A2, A3, A4, A5, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqMember<C, R&>::template Func5<A1, A2, A3, A4, A5, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberFunc(R&(C::* /*method*/)(A1, A2, A3, A4, A5) const) {
    return &SqMember<C, R&>::template Func5C<A1, A2, A3, A4, A5, false>;
}

// Arg Count 6
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqMember<C, R>::template Func6<A1, A2, A3, A4, A5, A6, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const) {
    return &SqMember<C, R>::template Func6C<A1, A2, A3, A4, A5, A6, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqMember<C, R&>::template Func6<A1, A2, A3, A4, A5, A6, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const) {
    return &SqMember<C, R&>::template Func6C<A1, A2, A3, A4, A5, A6, false>;
}

// Arg Count 7
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqMember<C, R>::template Func7<A1, A2, A3, A4, A5, A6, A7, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const) {
    return &SqMember<C, R>::template Func7C<A1, A2, A3, A4, A5, A6, A7, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqMember<C, R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const) {
    return &SqMember<C, R&>::template Func7C<A1, A2, A3, A4, A5, A6, A7, false>;
}

// Arg Count 8
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqMember<C, R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
    return &SqMember<C, R>::template Func8C<A1, A2, A3, A4, A5, A6, A7, A8, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqMember<C, R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
    return &SqMember<C, R&>::template Func8C<A1, A2, A3, A4, A5, A6, A7, A8, false>;
}

// Arg Count 9
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqMember<C, R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
    return &SqMember<C, R>::template Func9C<A1, A2, A3, A4, A5, A6, A7, A8, A9, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberFunc(R&(C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqMember<C, R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
    return &SqMember<C, R&>::template Func9C<A1, A2, A3, A4, A5, A6, A7, A8, A9, false>;
}

// Arg Count 10
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqMember<C, R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const) {
    return &SqMember<C, R>::template Func10C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, false>;
}
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqMember<C, R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const) {
    return &SqMember<C, R&>::template Func10C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, false>;
}

// Arg Count 11
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqMember<C, R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const) {
    return &SqMember<C, R>::template Func11C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, false>;
}
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqMember<C, R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const) {
    return &SqMember<C, R&>::template Func11C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, false>;
}

// Arg Count 12
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqMember<C, R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const) {
    return &SqMember<C, R>::template Func12C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqMember<C, R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const) {
    return &SqMember<C, R&>::template Func12C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, false>;
}

// Arg Count 13
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqMember<C, R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const) {
    return &SqMember<C, R>::template Func13C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqMember<C, R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const) {
    return &SqMember<C, R&>::template Func13C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, false>;
}

// Arg Count 14
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqMember<C, R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const) {
    return &SqMember<C, R>::template Func14C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqMember<C, R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, false>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const) {
    return &SqMember<C, R&>::template Func14C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, false>;
}


//
// Variable Get
//

template <class C, class V>
inline SQInteger sqDefaultGet(HSQUIRRELVM vm) {
    C* ptr;
    SQTRY()
    ptr = Var<C*>(vm, 1).value;
    SQCATCH_NOEXCEPT(vm) {
        SQCLEAR(vm); // clear the previous error
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    typedef V C::*M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    PushVarR(vm, ptr->*member);

    return 1;
}

template <class C, class V>
inline SQInteger sqStaticGet(HSQUIRRELVM vm) {
    typedef V *M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    PushVarR(vm, *member);

    return 1;
}

inline SQInteger sqVarGet(HSQUIRRELVM vm) {
    // Find the get method in the get table
    sq_push(vm, 2);
#if !defined (SCRAT_NO_ERROR_CHECKING)
    if (SQ_FAILED(sq_rawget(vm, -2))) {
#if (SQUIRREL_VERSION_NUMBER>= 200) && (SQUIRREL_VERSION_NUMBER < 300) // Squirrel 2.x
        return sq_throwerror(vm, _SC("member variable not found"));
#else // Squirrel 3.x
        sq_pushnull(vm);
        return sq_throwobject(vm);
#endif
    }
#else
    sq_rawget(vm, -2);
#endif

    // push 'this'
    sq_push(vm, 1);

    // Call the getter
#if !defined (SCRAT_NO_ERROR_CHECKING)
    SQRESULT result = sq_call(vm, 1, true, ErrorHandling::IsEnabled());
    if (SQ_FAILED(result)) {
        return sq_throwerror(vm, LastErrorString(vm).c_str());
    }
#else
    sq_call(vm, 1, true, ErrorHandling::IsEnabled());
#endif

    return 1;
}


//
// Variable Set
//

template <class C, class V>
inline SQInteger sqDefaultSet(HSQUIRRELVM vm) {
    C* ptr;
    SQTRY()
    ptr = Var<C*>(vm, 1).value;
    SQCATCH_NOEXCEPT(vm) {
        SQCLEAR(vm); // clear the previous error
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    typedef V C::*M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    SQTRY()
    if (is_pointer<V>::value || is_reference<V>::value) {
        ptr->*member = Var<V>(vm, 2).value;
    } else {
        ptr->*member = Var<const V&>(vm, 2).value;
    }
    SQCATCH_NOEXCEPT(vm) {
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    return 0;
}

template <class C, class V>
inline SQInteger sqStaticSet(HSQUIRRELVM vm) {
    typedef V *M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    SQTRY()
    if (is_pointer<V>::value || is_reference<V>::value) {
        *member = Var<V>(vm, 2).value;
    } else {
        *member = Var<const V&>(vm, 2).value;
    }
    SQCATCH_NOEXCEPT(vm) {
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    return 0;
}

inline SQInteger sqVarSet(HSQUIRRELVM vm) {
    // Find the set method in the set table
    sq_push(vm, 2);
#if !defined (SCRAT_NO_ERROR_CHECKING)
    if (SQ_FAILED(sq_rawget(vm, -2))) {
#if (SQUIRREL_VERSION_NUMBER>= 200) && (SQUIRREL_VERSION_NUMBER < 300) // Squirrel 2.x
        return sq_throwerror(vm, _SC("member variable not found"));
#else // Squirrel 3.x
        sq_pushnull(vm);
        return sq_throwobject(vm);
#endif
    }
#else
    sq_rawget(vm, -2);
#endif

    // push 'this'
    sq_push(vm, 1);
    sq_push(vm, 3);

    // Call the setter
#if !defined (SCRAT_NO_ERROR_CHECKING)
    SQRESULT result = sq_call(vm, 2, false, ErrorHandling::IsEnabled());
    if (SQ_FAILED(result)) {
        return sq_throwerror(vm, LastErrorString(vm).c_str());
    }
#else
    sq_call(vm, 2, false, ErrorHandling::IsEnabled());
#endif

    return 0;
}

/// @endcond

}

#endif

// <--- back to sqratOverloadMethods.h

namespace Sqrat {

/// @cond DEV

//
// Overload name generator
//

class SqOverloadName {
public:

    static string Get(const SQChar* name, int args) {
        std::basic_stringstream<SQChar> overloadName;
        overloadName << _SC("__overload_") << name << args;

        return overloadName.str();
    }
};


//
// Squirrel Overload Functions
//

template <class R>
class SqOverload {
public:

    static SQInteger Func(HSQUIRRELVM vm) {
        // Get the arg count
        int argCount = sq_gettop(vm) - 2;

        const SQChar* funcName;
        sq_getstring(vm, -1, &funcName); // get the function name (free variable)

        string overloadName = SqOverloadName::Get(funcName, argCount);

        sq_pushstring(vm, overloadName.c_str(), -1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, 1))) { // Lookup the proper overload
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#else
        sq_get(vm, 1);
#endif

        // Push the args again
        for (int i = 1; i <= argCount + 1; ++i) {
            sq_push(vm, i);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, argCount + 1, true, ErrorHandling::IsEnabled());
        if (SQ_FAILED(result)) {
            return sq_throwerror(vm, LastErrorString(vm).c_str());
        }
#else
        sq_call(vm, argCount + 1, true, ErrorHandling::IsEnabled());
#endif

        return 1;
    }
};


//
// void return specialization
//

template <>
class SqOverload<void> {
public:

    static SQInteger Func(HSQUIRRELVM vm) {
        // Get the arg count
        int argCount = sq_gettop(vm) - 2;

        const SQChar* funcName;
        sq_getstring(vm, -1, &funcName); // get the function name (free variable)

        string overloadName = SqOverloadName::Get(funcName, argCount);

        sq_pushstring(vm, overloadName.c_str(), -1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, 1))) { // Lookup the proper overload
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#else
        sq_get(vm, 1);
#endif

        // Push the args again
        for (int i = 1; i <= argCount + 1; ++i) {
            sq_push(vm, i);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, argCount + 1, false, ErrorHandling::IsEnabled());
        if (SQ_FAILED(result)) {
            return sq_throwerror(vm, LastErrorString(vm).c_str());
        }
#else
        sq_call(vm, argCount + 1, false, ErrorHandling::IsEnabled());
#endif

        return 0;
    }
};


//
// Global Overloaded Function Resolvers
//

// Arg Count 0
template <class R>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)()) {
    return &SqGlobal<R>::template Func0<true>;
}

template <class R>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)()) {
    return &SqGlobal<R&>::template Func0<true>;
}

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1)) {
    return &SqGlobal<R>::template Func1<A1, 2, true>;
}

template <class R, class A1>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1)) {
    return &SqGlobal<R&>::template Func1<A1, 2, true>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2)) {
    return &SqGlobal<R>::template Func2<A1, A2, 2, true>;
}

template <class R, class A1, class A2>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2)) {
    return &SqGlobal<R&>::template Func2<A1, A2, 2, true>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R>::template Func3<A1, A2, A3, 2, true>;
}

template <class R, class A1, class A2, class A3>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R&>::template Func3<A1, A2, A3, 2, true>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R>::template Func4<A1, A2, A3, A4, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R&>::template Func4<A1, A2, A3, A4, 2, true>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R>::template Func5<A1, A2, A3, A4, A5, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R&>::template Func5<A1, A2, A3, A4, A5, 2, true>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R>::template Func6<A1, A2, A3, A4, A5, A6, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R&>::template Func6<A1, A2, A3, A4, A5, A6, 2, true>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R>::template Func7<A1, A2, A3, A4, A5, A6, A7, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, 2, true>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 2, true>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 2, true>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 2, true>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 2, true>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 2, true>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 2, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 2, true>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 2, true>;
}
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 2, true>;
}


//
// Member Global Overloaded Function Resolvers
//

// Arg Count 1
template <class R, class A1>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1)) {
    return &SqGlobal<R>::template Func1<A1, 1, true>;
}

template <class R, class A1>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1)) {
    return &SqGlobal<R&>::template Func1<A1, 1, true>;
}

// Arg Count 2
template <class R, class A1, class A2>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2)) {
    return &SqGlobal<R>::template Func2<A1, A2, 1, true>;
}

template <class R, class A1, class A2>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2)) {
    return &SqGlobal<R&>::template Func2<A1, A2, 1, true>;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R>::template Func3<A1, A2, A3, 1, true>;
}

template <class R, class A1, class A2, class A3>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3)) {
    return &SqGlobal<R&>::template Func3<A1, A2, A3, 1, true>;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R>::template Func4<A1, A2, A3, A4, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4)) {
    return &SqGlobal<R&>::template Func4<A1, A2, A3, A4, 1, true>;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R>::template Func5<A1, A2, A3, A4, A5, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqGlobal<R&>::template Func5<A1, A2, A3, A4, A5, 1, true>;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R>::template Func6<A1, A2, A3, A4, A5, A6, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqGlobal<R&>::template Func6<A1, A2, A3, A4, A5, A6, 1, true>;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R>::template Func7<A1, A2, A3, A4, A5, A6, A7, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqGlobal<R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, 1, true>;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqGlobal<R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, 1, true>;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqGlobal<R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 1, true>;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqGlobal<R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, 1, true>;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqGlobal<R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, 1, true>;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqGlobal<R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, 1, true>;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqGlobal<R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, 1, true>;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 1, true>;
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqGlobal<R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, 1, true>;
}


//
// Member Overloaded Function Resolvers
//

// Arg Count 0
template <class C, class R>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)()) {
    return &SqMember<C, R>::template Func0<true>;
}

template <class C, class R>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)() const) {
    return &SqMember<C, R>::template Func0C<true>;
}

template <class C, class R>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)()) {
    return &SqMember<C, R&>::template Func0<true>;
}
template <class C, class R>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)() const) {
    return &SqMember<C, R&>::template Func0C<true>;
}

// Arg Count 1
template <class C, class R, class A1>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1)) {
    return &SqMember<C, R>::template Func1<A1, true>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1) const) {
    return &SqMember<C, R>::template Func1C<A1, true>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1)) {
    return &SqMember<C, R&>::template Func1<A1, true>;
}

template <class C, class R, class A1>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1) const) {
    return &SqMember<C, R&>::template Func1C<A1, true>;
}

// Arg Count 2
template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2)) {
    return &SqMember<C, R>::template Func2<A1, A2, true>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2) const) {
    return &SqMember<C, R>::template Func2C<A1, A2, true>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2)) {
    return &SqMember<C, R&>::template Func2<A1, A2, true>;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2) const) {
    return &SqMember<C, R&>::template Func2C<A1, A2, true>;
}

// Arg Count 3
template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3)) {
    return &SqMember<C, R>::template Func3<A1, A2, A3, true>;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3) const) {
    return &SqMember<C, R>::template Func3C<A1, A2, A3, true>;
}
template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3)) {
    return &SqMember<C, R&>::template Func3<A1, A2, A3, true>;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3) const) {
    return &SqMember<C, R&>::template Func3C<A1, A2, A3, true>;
}

// Arg Count 4
template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4)) {
    return &SqMember<C, R>::template Func4<A1, A2, A3, A4, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4) const) {
    return &SqMember<C, R>::template Func4C<A1, A2, A3, A4, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4)) {
    return &SqMember<C, R&>::template Func4<A1, A2, A3, A4, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4) const) {
    return &SqMember<C, R&>::template Func4C<A1, A2, A3, A4, true>;
}

// Arg Count 5
template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqMember<C, R>::template Func5<A1, A2, A3, A4, A5, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5) const) {
    return &SqMember<C, R>::template Func5C<A1, A2, A3, A4, A5, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5)) {
    return &SqMember<C, R&>::template Func5<A1, A2, A3, A4, A5, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5) const) {
    return &SqMember<C, R&>::template Func5C<A1, A2, A3, A4, A5, true>;
}

// Arg Count 6
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqMember<C, R>::template Func6<A1, A2, A3, A4, A5, A6, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const) {
    return &SqMember<C, R>::template Func6C<A1, A2, A3, A4, A5, A6, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return &SqMember<C, R&>::template Func6<A1, A2, A3, A4, A5, A6, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const) {
    return &SqMember<C, R&>::template Func6C<A1, A2, A3, A4, A5, A6, true>;
}

// Arg Count 7
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqMember<C, R>::template Func7<A1, A2, A3, A4, A5, A6, A7, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const) {
    return &SqMember<C, R>::template Func7C<A1, A2, A3, A4, A5, A6, A7, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return &SqMember<C, R&>::template Func7<A1, A2, A3, A4, A5, A6, A7, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const) {
    return &SqMember<C, R&>::template Func7C<A1, A2, A3, A4, A5, A6, A7, true>;
}

// Arg Count 8
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqMember<C, R>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
    return &SqMember<C, R>::template Func8C<A1, A2, A3, A4, A5, A6, A7, A8, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return &SqMember<C, R&>::template Func8<A1, A2, A3, A4, A5, A6, A7, A8, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
    return &SqMember<C, R&>::template Func8C<A1, A2, A3, A4, A5, A6, A7, A8, true>;
}

// Arg Count 9
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqMember<C, R>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
    return &SqMember<C, R>::template Func9C<A1, A2, A3, A4, A5, A6, A7, A8, A9, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return &SqMember<C, R&>::template Func9<A1, A2, A3, A4, A5, A6, A7, A8, A9, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
    return &SqMember<C, R&>::template Func9C<A1, A2, A3, A4, A5, A6, A7, A8, A9, true>;
}

// Arg Count 10
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqMember<C, R>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const) {
    return &SqMember<C, R>::template Func10C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return &SqMember<C, R&>::template Func10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const) {
    return &SqMember<C, R&>::template Func10C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, true>;
}

// Arg Count 11
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqMember<C, R>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const) {
    return &SqMember<C, R>::template Func11C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return &SqMember<C, R&>::template Func11<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const) {
    return &SqMember<C, R&>::template Func11C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, true>;
}

// Arg Count 12
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqMember<C, R>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const) {
    return &SqMember<C, R>::template Func12C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return &SqMember<C, R&>::template Func12<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const) {
    return &SqMember<C, R&>::template Func12C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, true>;
}

// Arg Count 13
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqMember<C, R>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const) {
    return &SqMember<C, R>::template Func13C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return &SqMember<C, R&>::template Func13<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const) {
    return &SqMember<C, R&>::template Func13C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, true>;
}


// Arg Count 14
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqMember<C, R>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const) {
    return &SqMember<C, R>::template Func14C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, true>;
}
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return &SqMember<C, R&>::template Func14<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, true>;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const) {
    return &SqMember<C, R&>::template Func14C<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, true>;
}


//
// Overload handler resolver
//

template <class R>
inline SQFUNCTION SqOverloadFunc(R (* /*method*/)) {
    return &SqOverload<R>::Func;
}

template <class C, class R>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)) {
    return &SqOverload<R>::Func;
}

template <class C, class R>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)() const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const ) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const ) {
    return &SqOverload<R>::Func;
}


//
// Query argument count
//

// Arg Count 0
template <class R>
inline int SqGetArgCount(R (* /*method*/)()) {
    return 0;
}

// Arg Count 1
template <class R, class A1>
inline int SqGetArgCount(R (* /*method*/)(A1)) {
    return 1;
}

// Arg Count 2
template <class R, class A1, class A2>
inline int SqGetArgCount(R (* /*method*/)(A1, A2)) {
    return 2;
}

// Arg Count 3
template <class R, class A1, class A2, class A3>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3)) {
    return 3;
}

// Arg Count 4
template <class R, class A1, class A2, class A3, class A4>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4)) {
    return 4;
}

// Arg Count 5
template <class R, class A1, class A2, class A3, class A4, class A5>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5)) {
    return 5;
}

// Arg Count 6
template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return 6;
}

// Arg Count 7
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return 7;
}

// Arg Count 8
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return 8;
}

// Arg Count 9
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return 9;
}

// Arg Count 10
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return 10;
}

// Arg Count 11
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return 11;
}

// Arg Count 12
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return 12;
}

// Arg Count 13
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return 13;
}

// Arg Count 14
template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline int SqGetArgCount(R (* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return 14;
}


//
// Query member function argument count
//

// Arg Count 0
template <class C, class R>
inline int SqGetArgCount(R (C::* /*method*/)()) {
    return 0;
}

// Arg Count 1
template <class C, class R, class A1>
inline int SqGetArgCount(R (C::* /*method*/)(A1)) {
    return 1;
}

// Arg Count 2
template <class C, class R, class A1, class A2>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2)) {
    return 2;
}

// Arg Count 3
template <class C, class R, class A1, class A2, class A3>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3)) {
    return 3;
}

// Arg Count 4
template <class C, class R, class A1, class A2, class A3, class A4>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4)) {
    return 4;
}

// Arg Count 5
template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5)) {
    return 5;
}

// Arg Count 6
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6)) {
    return 6;
}

// Arg Count 7
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7)) {
    return 7;
}

// Arg Count 8
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8)) {
    return 8;
}

// Arg Count 9
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
    return 9;
}

// Arg Count 10
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) {
    return 10;
}

// Arg Count 11
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) {
    return 11;
}

// Arg Count 12
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) {
    return 12;
}

// Arg Count 13
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)) {
    return 13;
}

// Arg Count 14
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)) {
    return 14;
}


//
// Query const member function argument count
//

// Arg Count 0
template <class C, class R>
inline int SqGetArgCount(R (C::* /*method*/)() const) {
    return 0;
}

// Arg Count 1
template <class C, class R, class A1>
inline int SqGetArgCount(R (C::* /*method*/)(A1) const) {
    return 1;
}

// Arg Count 2
template <class C, class R, class A1, class A2>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2) const) {
    return 2;
}

// Arg Count 3
template <class C, class R, class A1, class A2, class A3>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3) const) {
    return 3;
}

// Arg Count 4
template <class C, class R, class A1, class A2, class A3, class A4>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4) const) {
    return 4;
}

// Arg Count 5
template <class C, class R, class A1, class A2, class A3, class A4, class A5>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5) const) {
    return 5;
}

// Arg Count 6
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6) const) {
    return 6;
}

// Arg Count 7
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7) const) {
    return 7;
}

// Arg Count 8
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
    return 8;
}

// Arg Count 9
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
    return 9;
}

// Arg Count 10
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const) {
    return 10;
}

// Arg Count 11
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const) {
    return 11;
}

// Arg Count 12
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const) {
    return 12;
}

// Arg Count 13
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13) const) {
    return 13;
}

// Arg Count 14
template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
inline int SqGetArgCount(R (C::* /*method*/)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14) const) {
    return 14;
}

/// @endcond

}

#endif

// <--- back to sqratObject.h
// ---- #include "sqratUtil.h"
// ---> including sqratUtil.h
// <--- back to sqratObject.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The base class for classes that represent Squirrel objects
///
/// \remarks
/// All Object and derived classes MUST be destroyed before calling sq_close or your application will crash when exiting.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Object {
protected:

/// @cond DEV
    HSQUIRRELVM vm;
    HSQOBJECT obj;
    bool release;

    Object(HSQUIRRELVM v, bool releaseOnDestroy = true) : vm(v), release(releaseOnDestroy) {
        sq_resetobject(&obj);
    }
/// @endcond

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object() : vm(0), release(true) {
        sq_resetobject(&obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param so Object to copy
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object(const Object& so) : vm(so.vm), obj(so.obj), release(so.release) {
        sq_addref(vm, &obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs an Object from a Squirrel object
    ///
    /// \param o Squirrel object
    /// \param v VM that the object will exist in
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object(HSQOBJECT o, HSQUIRRELVM v = DefaultVM::Get()) : vm(v), obj(o), release(true) {
        sq_addref(vm, &obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs an Object from a C++ instance
    ///
    /// \param instance Pointer to a C++ class instance that has been bound already
    /// \param v        VM that the object will exist in
    ///
    /// \tparam T Type of instance
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    Object(T* instance, HSQUIRRELVM v = DefaultVM::Get()) : vm(v), release(true) {
        ClassType<T>::PushInstance(vm, instance);
        sq_getstackobj(vm, -1, &obj);
        sq_addref(vm, &obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~Object() {
        if(release) {
            Release();
            release = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assignment operator
    ///
    /// \param so Object to copy
    ///
    /// \return The Object itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object& operator=(const Object& so) {
        if(release) {
            Release();
        }
        vm = so.vm;
        obj = so.obj;
        release = so.release;
        sq_addref(vm, &GetObject());
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel VM for this Object (reference)
    ///
    /// \return Squirrel VM associated with the Object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQUIRRELVM& GetVM() {
        return vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel VM for this Object (copy)
    ///
    /// \return Squirrel VM associated with the Object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQUIRRELVM GetVM() const {
        return vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the type of the Object as defined by the Squirrel API
    ///
    /// \return SQObjectType for the Object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SQObjectType GetType() const {
        return GetObject()._type;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Checks whether the Object is null
    ///
    /// \return True if the Object currently has a null value, otherwise false
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsNull() const {
        return sq_isnull(GetObject());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel object for this Object (copy)
    ///
    /// \return Squirrel object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual HSQOBJECT GetObject() const {
        return obj;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel object for this Object (reference)
    ///
    /// \return Squirrel object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual HSQOBJECT& GetObject() {
        return obj;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Allows the Object to be inputted directly into places that expect a HSQOBJECT
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    operator HSQOBJECT&() {
        return GetObject();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets the Object to null (removing its references to underlying Squirrel objects)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Release() {
        sq_release(vm, &obj);
        sq_resetobject(&obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value of a slot from the object
    ///
    /// \param slot Name of the slot
    ///
    /// \return An Object representing the value of the slot (can be a null object if nothing was found)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object GetSlot(const SQChar* slot) const {
        HSQOBJECT slotObj;
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, slot, -1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Object(vm); // Return a NULL object
        } else {
            sq_getstackobj(vm, -1, &slotObj);
            Object ret(slotObj, vm); // must addref before the pop!
            sq_pop(vm, 2);
            return ret;
        }
#else
        sq_get(vm, -2);
        sq_getstackobj(vm, -1, &slotObj);
        Object ret(slotObj, vm); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value of an index from the object
    ///
    /// \param index Index of the slot
    ///
    /// \return An Object representing the value of the slot (can be a null object if nothing was found)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object GetSlot(SQInteger index) const {
        HSQOBJECT slotObj;
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Object(vm); // Return a NULL object
        } else {
            sq_getstackobj(vm, -1, &slotObj);
            Object ret(slotObj, vm); // must addref before the pop!
            sq_pop(vm, 2);
            return ret;
        }
#else
        sq_get(vm, -2);
        sq_getstackobj(vm, -1, &slotObj);
        Object ret(slotObj, vm); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Casts the object to a certain C++ type
    ///
    /// \tparam T Type to cast to
    ///
    /// \return A copy of the value of the Object with the given type
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class T>
    T Cast() const {
        sq_pushobject(vm, GetObject());
        T ret = Var<T>(vm, -1).value;
        sq_pop(vm, 1);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Allows Object to be used like C++ arrays with the [] operator
    ///
    /// \param slot The slot key
    ///
    /// \tparam T Type of the slot key (usually doesnt need to be defined explicitly)
    ///
    /// \return An Object representing the value of the slot (can be a null object if nothing was found)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class T>
    inline Object operator[](T slot)
    {
        return GetSlot(slot);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns the size of the Object
    ///
    /// \return Size of Object
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SQInteger GetSize() const {
        sq_pushobject(vm, GetObject());
        SQInteger ret = sq_getsize(vm, -1);
        sq_pop(vm, 1);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Iterator for going over the slots in the object using Object::Next
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct iterator
    {
        /// @cond DEV
        friend class Object;
        /// @endcond

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default constructor (null)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        iterator()
        {
            Index = 0;
            sq_resetobject(&Key);
            sq_resetobject(&Value);
            Key._type = OT_NULL;
            Value._type = OT_NULL;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the string value of the key the iterator is on if possible
        ///
        /// \return String or NULL
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const SQChar* getName() { return sq_objtostring(&Key); }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the Squirrel object for the key the iterator is on
        ///
        /// \return HSQOBJECT representing a key
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        HSQOBJECT getKey() { return Key; }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Gets the Squirrel object for the value the iterator is on
        ///
        /// \return HSQOBJECT representing a value
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        HSQOBJECT getValue() { return Value; }
    private:

        HSQOBJECT Key;
        HSQOBJECT Value;
        SQInteger Index;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Used to go through all the slots in an Object (same limitations as sq_next)
    ///
    /// \param iter An iterator being used for going through the slots
    ///
    /// \return Whether there is a next slot
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool Next(iterator& iter) const
    {
        sq_pushobject(vm,obj);
        sq_pushinteger(vm,iter.Index);
        if(SQ_SUCCEEDED(sq_next(vm,-2)))
        {
            sq_getstackobj(vm,-1,&iter.Value);
            sq_getstackobj(vm,-2,&iter.Key);
            sq_getinteger(vm,-3,&iter.Index);
            sq_pop(vm,4);
            return true;
        }
        else
        {
            sq_pop(vm,2);
            return false;
        }
    }

protected:
/// @cond DEV

    // Bind a function and it's associated Squirrel closure to the object
    inline void BindFunc(const SQChar* name, void* method, size_t methodSize, SQFUNCTION func, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);

        SQUserPointer methodPtr = sq_newuserdata(vm, static_cast<SQUnsignedInteger>(methodSize));
        memcpy(methodPtr, method, methodSize);

        sq_newclosure(vm, func, 1);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }

    inline void BindFunc(const SQInteger index, void* method, size_t methodSize, SQFUNCTION func, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);

        SQUserPointer methodPtr = sq_newuserdata(vm, static_cast<SQUnsignedInteger>(methodSize));
        memcpy(methodPtr, method, methodSize);

        sq_newclosure(vm, func, 1);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }


    // Bind a function and it's associated Squirrel closure to the object
    inline void BindOverload(const SQChar* name, void* method, size_t methodSize, SQFUNCTION func, SQFUNCTION overload, int argCount, bool staticVar = false) {
        string overloadName = SqOverloadName::Get(name, argCount);

        sq_pushobject(vm, GetObject());

        // Bind overload handler
        sq_pushstring(vm, name, -1);
        sq_pushstring(vm, name, -1); // function name is passed as a free variable
        sq_newclosure(vm, overload, 1);
        sq_newslot(vm, -3, staticVar);

        // Bind overloaded function
        sq_pushstring(vm, overloadName.c_str(), -1);
        SQUserPointer methodPtr = sq_newuserdata(vm, static_cast<SQUnsignedInteger>(methodSize));
        memcpy(methodPtr, method, methodSize);
        sq_newclosure(vm, func, 1);
        sq_newslot(vm, -3, staticVar);

        sq_pop(vm,1); // pop table
    }

    // Set the value of a variable on the object. Changes to values set this way are not reciprocated
    template<class V>
    inline void BindValue(const SQChar* name, const V& val, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
        PushVar(vm, val);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }
    template<class V>
    inline void BindValue(const SQInteger index, const V& val, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
        PushVar(vm, val);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }

    // Set the value of an instance on the object. Changes to values set this way are reciprocated back to the source instance
    template<class V>
    inline void BindInstance(const SQChar* name, V* val, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
        PushVar(vm, val);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }
    template<class V>
    inline void BindInstance(const SQInteger index, V* val, bool staticVar = false) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
        PushVar(vm, val);
        sq_newslot(vm, -3, staticVar);
        sq_pop(vm,1); // pop table
    }

/// @endcond
};

/// @cond DEV
template<>
inline void Object::BindValue<int>(const SQChar* name, const int & val, bool staticVar /* = false */) {
    sq_pushobject(vm, GetObject());
    sq_pushstring(vm, name, -1);
    PushVar<int>(vm, val);
    sq_newslot(vm, -3, staticVar);
    sq_pop(vm,1); // pop table
}
/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Object instances to and from the stack as references (Object is always a reference)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Object> {

    Object value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as an Object
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        HSQOBJECT sqValue;
        sq_getstackobj(vm, idx, &sqValue);
        value = Object(sqValue, vm);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put an Object on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const Object& value) {
        sq_pushobject(vm, value.GetObject());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Object instances to and from the stack as references (Object is always a reference)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Object&> : Var<Object> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Object>(vm, idx) {}};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Object instances to and from the stack as references (Object is always a reference)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const Object&> : Var<Object> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Object>(vm, idx) {}};

}

#endif

// <--- back to sqratTable.h
// ---- #include "sqratFunction.h"
// ---> including sqratFunction.h
//
// sqratFunction: Squirrel Function Wrapper
//

//
// Copyright (c) 2009 Brandon Jones
// Copyirght 2011 Li-Cheng (Andy) Tai
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_SQFUNC_H_)
#define _SCRAT_SQFUNC_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratFunction.h
// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratFunction.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a function in Squirrel
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Function  {

    friend class TableBase;
    friend class Table;
    friend class ArrayBase;
    friend struct Var<Function>;

private:

    HSQUIRRELVM vm;
    HSQOBJECT env, obj;

public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function() {
        sq_resetobject(&env);
        sq_resetobject(&obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param sf Function to copy
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function(const Function& sf) : vm(sf.vm), env(sf.env), obj(sf.obj) {
        sq_addref(vm, &env);
        sq_addref(vm, &obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a Function from a slot in an Object
    ///
    /// \param e    Object that potentially contains a Squirrel function in a slot
    /// \param slot Name of the slot to look for the Squirrel function in
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function(const Object& e, const SQChar* slot) : vm(e.GetVM()), env(e.GetObject()) {
        sq_addref(vm, &env);
        Object so = e.GetSlot(slot);
        obj = so.GetObject();
        sq_addref(vm, &obj);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQObjectType value_type = so.GetType();
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE && value_type != OT_CLASS) {
            // Note that classes can also be considered functions in Squirrel
            SQTHROW(vm, _SC("function not found in slot"));
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a Function from two Squirrel objects (one is the environment object and the other is the function object)
    ///
    /// \param v VM that the function will exist in
    /// \param e Squirrel object that should represent the environment of the function
    /// \param o Squirrel object that should already represent a Squirrel function
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function(HSQUIRRELVM v, HSQOBJECT e, HSQOBJECT o) : vm(v), env(e), obj(o) {
        sq_addref(vm, &env);
        sq_addref(vm, &obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~Function() {
        Release();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assignment operator
    ///
    /// \param sf Function to copy
    ///
    /// \return The Function itself
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function& operator=(const Function& sf) {
        Release();
        vm = sf.vm;
        env = sf.env;
        obj = sf.obj;
        sq_addref(vm, &env);
        sq_addref(vm, &obj);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Checks whether the Function is null
    ///
    /// \return True if the Function currently has a null value, otherwise false
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsNull() {
        return sq_isnull(obj);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel environment object for this Function (copy)
    ///
    /// \return Squirrel object representing the Function environment
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQOBJECT GetEnv() const {
        return env;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel environment object for this Function (reference)
    ///
    /// \return Squirrel object representing the Function environment
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQOBJECT& GetEnv() {
        return env;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel function object for this Function (copy)
    ///
    /// \return Squirrel object representing the Function
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQOBJECT GetFunc() const {
        return obj;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel function object for this Function (reference)
    ///
    /// \return Squirrel object representing the Function
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQOBJECT& GetFunc() {
        return obj;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel VM for this Function (copy)
    ///
    /// \return Squirrel VM associated with the Function
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQUIRRELVM GetVM() const {
        return vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel VM for this Function (reference)
    ///
    /// \return Squirrel VM associated with the Function
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HSQUIRRELVM& GetVM() {
        return vm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets the Function to null (removing its references to underlying Squirrel objects)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Release() {
        if(!IsNull()) {
            sq_release(vm, &env);
            sq_release(vm, &obj);
            sq_resetobject(&env);
            sq_resetobject(&obj);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R>
    SharedPtr<R> Evaluate() {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;

        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 1)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }

        SQRESULT result = sq_call(vm, 1, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 1, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1>
    SharedPtr<R> Evaluate(A1 a1) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;

        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 2)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 2, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 2, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2>
    SharedPtr<R> Evaluate(A1 a1, A2 a2) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;

        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 3)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 3, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 3, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 4)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 4, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 4, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 5)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 5, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 5, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 6)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 6, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 6, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)

        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 7)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 7, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 7, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 8)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 8, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 8, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 9)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 9, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 9, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    /// \param a9 Argument 9 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9 Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 10)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 10, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 10, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 11)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 11, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 11, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 12)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 12, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 12, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 13)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 13, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 13, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 14)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);
        PushVar(vm, a13);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 14, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 14, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function and returns its value as a SharedPtr
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    /// \param a14 Argument 14 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A14 Type of argument 14 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam R Type of return value (fails if return value is not of this type)
    ///
    /// \return SharedPtr containing the return value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
    SharedPtr<R> Evaluate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 15)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return SharedPtr<R>();
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);
        PushVar(vm, a13);
        PushVar(vm, a14);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 15, true, ErrorHandling::IsEnabled());

        //handle an error: pop the stack and throw the exception
        if (SQ_FAILED(result)) {
            sq_settop(vm, top);
            SQTHROW(vm, LastErrorString(vm));
            return SharedPtr<R>();
        }
#else
        sq_call(vm, 15, true, ErrorHandling::IsEnabled());
#endif

        SharedPtr<R> ret = Var<SharedPtr<R> >(vm, -1).value;
        sq_settop(vm, top);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Execute() {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 1)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }

        SQRESULT result = sq_call(vm, 1, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 1, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1>
    void Execute(A1 a1) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 2)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 2, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 2, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2>
    void Execute(A1 a1, A2 a2) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 3)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 3, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 3, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3>
    void Execute(A1 a1, A2 a2, A3 a3) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 4)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 4, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 4, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 5)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 5, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 5, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 6)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 6, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 6, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 7)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 7, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 7, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 8)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 8, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 8, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 9)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 9, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 9, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    /// \param a9 Argument 9 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9 Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 10)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 10, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 10, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 11)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 11, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 11, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 12)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 12, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 12, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);


#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 13)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 13, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 13, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 14)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);
        PushVar(vm, a13);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 14, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 14, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    /// \param a14 Argument 14 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A14 Type of argument 14 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
    void Execute(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) {
        SQInteger top = sq_gettop(vm);

        sq_pushobject(vm, obj);
        sq_pushobject(vm, env);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQUnsignedInteger nparams;
        SQUnsignedInteger nfreevars;
        if (SQ_SUCCEEDED(sq_getclosureinfo(vm, -2, &nparams, &nfreevars)) && (nparams != 15)) {
            sq_pop(vm, 2);
            SQTHROW(vm, _SC("wrong number of parameters"));
            return;
        }
#endif

        PushVar(vm, a1);
        PushVar(vm, a2);
        PushVar(vm, a3);
        PushVar(vm, a4);
        PushVar(vm, a5);
        PushVar(vm, a6);
        PushVar(vm, a7);
        PushVar(vm, a8);
        PushVar(vm, a9);
        PushVar(vm, a10);
        PushVar(vm, a11);
        PushVar(vm, a12);
        PushVar(vm, a13);
        PushVar(vm, a14);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, 15, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);

        //handle an error: throw the exception
        if (SQ_FAILED(result)) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_call(vm, 15, false, ErrorHandling::IsEnabled());
        sq_settop(vm, top);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void operator()() {
        Execute();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1>
    void operator()(A1 a1) {
        Execute(a1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2>
    void operator()(A1 a1, A2 a2) {
        Execute(a1, a2);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3>
    void operator()(A1 a1, A2 a2, A3 a3) {
        Execute(a1, a2, a3);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4) {
        Execute(a1, a2, a3, a4);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        Execute(a1, a2, a3, a4, a5);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        Execute(a1, a2, a3, a4, a5, a6);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        Execute(a1, a2, a3, a4, a5, a6, a7);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1 Argument 1 of the Function
    /// \param a2 Argument 2 of the Function
    /// \param a3 Argument 3 of the Function
    /// \param a4 Argument 4 of the Function
    /// \param a5 Argument 5 of the Function
    /// \param a6 Argument 6 of the Function
    /// \param a7 Argument 7 of the Function
    /// \param a8 Argument 8 of the Function
    /// \param a9 Argument 9 of the Function
    ///
    /// \tparam A1 Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2 Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3 Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4 Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5 Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6 Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7 Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8 Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9 Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the Function
    ///
    /// \param a1  Argument 1 of the Function
    /// \param a2  Argument 2 of the Function
    /// \param a3  Argument 3 of the Function
    /// \param a4  Argument 4 of the Function
    /// \param a5  Argument 5 of the Function
    /// \param a6  Argument 6 of the Function
    /// \param a7  Argument 7 of the Function
    /// \param a8  Argument 8 of the Function
    /// \param a9  Argument 9 of the Function
    /// \param a10 Argument 10 of the Function
    /// \param a11 Argument 11 of the Function
    /// \param a12 Argument 12 of the Function
    /// \param a13 Argument 13 of the Function
    /// \param a14 Argument 14 of the Function
    ///
    /// \tparam A1  Type of argument 1 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A2  Type of argument 2 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A3  Type of argument 3 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A4  Type of argument 4 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A5  Type of argument 5 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A6  Type of argument 6 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A7  Type of argument 7 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A8  Type of argument 8 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A9  Type of argument 9 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A10 Type of argument 10 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A11 Type of argument 11 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A12 Type of argument 12 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A13 Type of argument 13 of the Function (usually doesnt need to be defined explicitly)
    /// \tparam A14 Type of argument 14 of the Function (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
    void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) {
        Execute(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Function instances to and from the stack as references (functions are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Function> {

    Function value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a Function
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// Assumes the Function environment is at index 1.
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        HSQOBJECT sqEnv;
        HSQOBJECT sqValue;
        sq_getstackobj(vm, 1, &sqEnv);
        sq_getstackobj(vm, idx, &sqValue);
        value = Function(vm, sqEnv, sqValue);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQObjectType value_type = sq_gettype(vm, idx);
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE) {
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("closure")));
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put a Function on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const Function& value) {
        sq_pushobject(vm, value.GetFunc());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Function instances to and from the stack as references (functions are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Function&> : Var<Function> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Function>(vm, idx) {}};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Function instances to and from the stack as references (functions are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const Function&> : Var<Function> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Function>(vm, idx) {}};

}

#endif

// <--- back to sqratTable.h
// ---- #include "sqratGlobalMethods.h"
// ---> including sqratGlobalMethods.h
// <--- back to sqratTable.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The base class for Table that implements almost all of its functionality
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TableBase : public Object {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /// \param v VM that the table will exist in
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TableBase(HSQUIRRELVM v = DefaultVM::Get()) : Object(v, true) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the TableBase from an Object that already exists
    ///
    /// \param obj An Object that should already represent a Squirrel table
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TableBase(const Object& obj) : Object(obj) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the TableBase from a HSQOBJECT and HSQUIRRELVM that already exist
    ///
    /// \param o Squirrel object that should already represent a Squirrel table
    /// \param v Squirrel VM that contains the Squirrel object given
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TableBase(HSQOBJECT o, HSQUIRRELVM v = DefaultVM::Get()) : Object(o, v) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a Table or Class to the Table (can be used to facilitate namespaces)
    ///
    /// \param name The key in the table being assigned a Table or Class
    /// \param obj  Table or Class that is being placed in the table
    ///
    /// \remarks
    /// Bind cannot be called "inline" like other functions because it introduces order-of-initialization bugs.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind(const SQChar* name, Object& obj) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
        sq_pushobject(vm, obj.GetObject());
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a raw Squirrel closure to the Table
    ///
    /// \param name The key in the table being assigned a function
    /// \param func Squirrel function that is being placed in the Table
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TableBase& SquirrelFunc(const SQChar* name, SQFUNCTION func) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
        sq_newclosure(vm, func, 0);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets a key in the Table to a specific value
    ///
    /// \param name The key in the table being assigned a value
    /// \param val  Value that is being placed in the Table
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    TableBase& SetValue(const SQChar* name, const V& val) {
        BindValue<V>(name, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets an index in the Table to a specific value
    ///
    /// \param index The index in the table being assigned a value
    /// \param val   Value that is being placed in the Table
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    TableBase& SetValue(const SQInteger index, const V& val) {
        BindValue<V>(index, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets a key in the Table to a specific instance (like a reference)
    ///
    /// \param name The key in the table being assigned a value
    /// \param val  Pointer to the instance that is being placed in the Table
    ///
    /// \tparam V Type of instance (usually doesnt need to be defined explicitly)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    TableBase& SetInstance(const SQChar* name, V* val) {
        BindInstance<V>(name, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets an index in the Table to a specific instance (like a reference)
    ///
    /// \param index The index in the table being assigned a value
    /// \param val   Pointer to the instance that is being placed in the Table
    ///
    /// \tparam V Type of instance (usually doesnt need to be defined explicitly)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    TableBase& SetInstance(const SQInteger index, V* val) {
        BindInstance<V>(index, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets a key in the Table to a specific function
    ///
    /// \param name   The key in the table being assigned a value
    /// \param method Function that is being placed in the Table
    ///
    /// \tparam F Type of function (only define this if you need to choose a certain template specialization or overload)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    TableBase& Func(const SQChar* name, F method) {
        BindFunc(name, &method, sizeof(method), SqGlobalFunc(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets a key in the Table to a specific function and allows the key to be overloaded with functions of a different amount of arguments
    ///
    /// \param name   The key in the table being assigned a value
    /// \param method Function that is being placed in the Table
    ///
    /// \tparam F Type of function (only define this if you need to choose a certain template specialization or overload)
    ///
    /// \return The Table itself so the call can be chained
    ///
    /// \remarks
    /// Overloading in Sqrat does not work for functions with the same amount of arguments (just like in Squirrel).
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    TableBase& Overload(const SQChar* name, F method) {
        BindOverload(name, &method, sizeof(method), SqGlobalOverloadedFunc(method), SqOverloadFunc(method), SqGetArgCount(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Checks if the given key exists in the table
    ///
    /// \param name Key to check
    ///
    /// \return True on success, otherwise false
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasKey(const SQChar* name)
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, -1);
        if (SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return false;
        }
        sq_pop(vm, 2);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns the value at a given key
    ///
    /// \param name Key of the element
    ///
    /// \tparam T Type of value (fails if value is not of this type)
    ///
    /// \return SharedPtr containing the value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    SharedPtr<T> GetValue(const SQChar* name)
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, -1);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            SQTHROW(vm, _SC("illegal index"));
            return SharedPtr<T>();
        }
#else
        sq_get(vm, -2);
#endif
        SQTRY()
        Var<SharedPtr<T> > entry(vm, -1);
        SQCATCH_NOEXCEPT(vm) {
            sq_pop(vm, 2);
            return SharedPtr<T>();
        }
        sq_pop(vm, 2);
        return entry.value;
        SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
            SQUNUSED(e); // avoid "unreferenced local variable" warning
#endif
            sq_pop(vm, 2);
            SQRETHROW(vm);
        }
        return SharedPtr<T>(); // avoid "not all control paths return a value" warning
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns the value at a given index
    ///
    /// \param index Index of the element
    ///
    /// \tparam T Type of value (fails if value is not of this type)
    ///
    /// \return SharedPtr containing the value (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    SharedPtr<T> GetValue(int index)
    {
        sq_pushobject(vm, obj);
        sq_pushinteger(vm, index);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            SQTHROW(vm, _SC("illegal index"));
            return SharedPtr<T>();
        }
#else
        sq_get(vm, -2);
#endif
        SQTRY()
        Var<SharedPtr<T> > entry(vm, -1);
        SQCATCH_NOEXCEPT(vm) {
            sq_pop(vm, 2);
            return SharedPtr<T>();
        }
        sq_pop(vm, 2);
        return entry.value;
        SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
            SQUNUSED(e); // avoid "unreferenced local variable" warning
#endif
            sq_pop(vm, 2);
            SQRETHROW(vm);
        }
        return SharedPtr<T>(); // avoid "not all control paths return a value" warning
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets a Function from a key in the Table
    ///
    /// \param name The key in the table that contains the Function
    ///
    /// \return Function found in the Table (null if failed)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function GetFunction(const SQChar* name) {
        HSQOBJECT funcObj;
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Function();
        }
        SQObjectType value_type = sq_gettype(vm, -1);
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE) {
            sq_pop(vm, 2);
            return Function();
        }
#else
        sq_get(vm, -2);
#endif
        sq_getstackobj(vm, -1, &funcObj);
        Function ret(vm, GetObject(), funcObj); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets a Function from an index in the Table
    ///
    /// \param index The index in the table that contains the Function
    ///
    /// \return Function found in the Table (null if failed)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function GetFunction(const SQInteger index) {
        HSQOBJECT funcObj;
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Function();
        }
        SQObjectType value_type = sq_gettype(vm, -1);
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE) {
            sq_pop(vm, 2);
            return Function();
        }
#else
        sq_get(vm, -2);
#endif
        sq_getstackobj(vm, -1, &funcObj);
        Function ret(vm, GetObject(), funcObj); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a table in Squirrel
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Table : public TableBase {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /// \remarks
    /// The Table is invalid until it is given a VM to exist in.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Table() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a Table
    ///
    /// \param v VM to create the Table in
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Table(HSQUIRRELVM v) : TableBase(v) {
        sq_newtable(vm);
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the Table from an Object that already exists
    ///
    /// \param obj An Object that should already represent a Squirrel table
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Table(const Object& obj) : TableBase(obj) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the Table from a HSQOBJECT and HSQUIRRELVM that already exist
    ///
    /// \param o Squirrel object that should already represent a Squirrel table
    /// \param v Squirrel VM that contains the Squirrel object given
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Table(HSQOBJECT o, HSQUIRRELVM v = DefaultVM::Get()) : TableBase(o, v) {
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Table that is a reference to the Squirrel root table for a given VM
/// The Squirrel root table is usually where all globals are stored by the Squirrel language.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RootTable : public TableBase {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a RootTable object to represent the given VM's root table
    ///
    /// \param v VM to get the RootTable for
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    RootTable(HSQUIRRELVM v = DefaultVM::Get()) : TableBase(v) {
        sq_pushroottable(vm);
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(v,1); // pop root table
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Table that is a reference to the Squirrel registry table for a given VM
/// The Squirrel registry table is where non-Squirrel code can store Squirrel objects without worrying about Squirrel code messing with them.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RegistryTable : public TableBase {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a RegistryTable object to represent the given VM's registry table
    ///
    /// \param v VM to get the RegistryTable for
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    RegistryTable(HSQUIRRELVM v = DefaultVM::Get()) : TableBase(v) {
        sq_pushregistrytable(v);
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(v,1); // pop the registry table
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Table instances to and from the stack as references (tables are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Table> {

    Table value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as a Table
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        HSQOBJECT obj;
        sq_resetobject(&obj);
        sq_getstackobj(vm,idx,&obj);
        value = Table(obj, vm);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQObjectType value_type = sq_gettype(vm, idx);
        if (value_type != OT_TABLE) {
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("table")));
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put an Table reference on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const Table& value) {
        HSQOBJECT obj;
        sq_resetobject(&obj);
        obj = value.GetObject();
        sq_pushobject(vm,obj);
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Table instances to and from the stack as references (tables are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Table&> : Var<Table> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Table>(vm, idx) {}};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Table instances to and from the stack as references (tables are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const Table&> : Var<Table> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Table>(vm, idx) {}};

}

#endif

// <--- back to sqrat.h
// ---- #include "sqrat/sqratClass.h"
// ---> including sqratClass.h
//
// SqratClass: Class Binding
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//    1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
//    2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
//    3. This notice may not be removed or altered from any source
//    distribution.
//

#if !defined(_SCRAT_CLASS_H_)
#define _SCRAT_CLASS_H_

#include <typeinfo>
// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratClass.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratClass.h
// ---- #include "sqratClassType.h"
// ---> including sqratClassType.h
// <--- back to sqratClass.h
// ---- #include "sqratMemberMethods.h"
// ---> including sqratMemberMethods.h
// <--- back to sqratClass.h
// ---- #include "sqratAllocator.h"
// ---> including sqratAllocator.h
// <--- back to sqratClass.h
// ---- #include "sqratTypes.h"
// ---> including sqratTypes.h
// <--- back to sqratClass.h

namespace Sqrat
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Facilitates exposing a C++ class with no base class to Squirrel
///
/// \tparam C Class type to expose
/// \tparam A An allocator to use when instantiating and destroying class instances of this type in Squirrel
///
/// \remarks
/// DefaultAllocator is used if no allocator is specified. This should be sufficent for most classes,
/// but if specific behavior is desired, it can be overridden. If the class should not be instantiated from
/// Squirrel the NoConstructor allocator may be used. See NoCopy and CopyOnly too.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class A = DefaultAllocator<C> >
class Class : public Object
{
private:

    static SQInteger cleanup_hook(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        ClassData<C>** ud = reinterpret_cast<ClassData<C>**>(ptr);
        delete *ud;
        return 0;
    }

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs the Class object
    ///
    /// A Class object doesnt do anything on its own.
    /// It must be told what methods and variables it contains.
    /// This is done using Class methods such as Class::Func and Class::Var.
    /// Then the Class must be exposed to Squirrel.
    /// This is usually done by calling TableBase::Bind on a RootTable with the Class.
    ///
    /// \param v           Squirrel virtual machine to create the Class for
    /// \param className   A necessarily unique name for the class that can appear in error messages
    /// \param createClass Should class type data be created? (almost always should be true - don't worry about it)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Class(HSQUIRRELVM v, const string& className, bool createClass = true) : Object(v, false) {
        if (createClass && !ClassType<C>::hasClassData(v)) {
            sq_pushregistrytable(v);
            sq_pushstring(v, "__classes", -1);
            if (SQ_FAILED(sq_rawget(v, -2))) {
                sq_newtable(v);
                sq_pushstring(v, "__classes", -1);
                sq_push(v, -2);
                sq_rawset(v, -4);
            }
            sq_pushstring(v, className.c_str(), -1);
            ClassData<C>** ud = reinterpret_cast<ClassData<C>**>(sq_newuserdata(v, sizeof(ClassData<C>*)));
            *ud = new ClassData<C>;
            sq_setreleasehook(v, -1, &cleanup_hook);
            sq_rawset(v, -3);
            sq_pop(v, 2);

            ClassData<C>* cd = *ud;

            if (ClassType<C>::getStaticClassData().Expired()) {
                cd->staticData.Init(new StaticClassData<C, void>);
                cd->staticData->copyFunc  = &A::Copy;
                cd->staticData->className = string(className);
                cd->staticData->baseClass = NULL;

                ClassType<C>::getStaticClassData() = cd->staticData;
            } else {
                cd->staticData = ClassType<C>::getStaticClassData().Lock();
            }

            HSQOBJECT& classObj = cd->classObj;
            sq_resetobject(&classObj);

            sq_newclass(v, false);
            sq_getstackobj(v, -1, &classObj);
            sq_addref(v, &classObj); // must addref before the pop!
            sq_pop(v, 1);
            InitClass(cd);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel object for this Class (copy)
    ///
    /// \return Squirrel object representing the Squirrel class
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual HSQOBJECT GetObject() const {
        return ClassType<C>::getClassData(vm)->classObj;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets the Squirrel object for this Class (reference)
    ///
    /// \return Squirrel object representing the Squirrel class
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual HSQOBJECT& GetObject() {
        return ClassType<C>::getClassData(vm)->classObj;
    }

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns a static class slot a value
    ///
    /// \param name Name of the static slot
    /// \param val  Value to assign
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// Static values are read-only in Squirrel.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    Class& SetStaticValue(const SQChar* name, const V& val) {
        BindValue<V>(name, val, true);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Assigns a class slot a value
    ///
    /// \param name Name of the slot
    /// \param val  Value to assign
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    Class& SetValue(const SQChar* name, const V& val) {
        BindValue<V>(name, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class variable
    ///
    /// \param name Name of the variable as it will appear in Squirrel
    /// \param var  Variable to bind
    ///
    /// \tparam V Type of variable (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// If V is not a pointer or reference, then it must have a default constructor.
    /// See Sqrat::Class::Prop to work around this requirement
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    Class& Var(const SQChar* name, V C::* var) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);

        // Add the getter
        BindAccessor(name, &var, sizeof(var), &sqDefaultGet<C, V>, cd->getTable);

        // Add the setter
        BindAccessor(name, &var, sizeof(var), &sqDefaultSet<C, V>, cd->setTable);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class variable without a setter
    ///
    /// \param name Name of the variable as it will appear in Squirrel
    /// \param var  Variable to bind
    ///
    /// \tparam V Type of variable (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// If V is not a pointer or reference, then it must have a default constructor.
    /// See Sqrat::Class::Prop to work around this requirement
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    Class& ConstVar(const SQChar* name, V C::* var) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);

        // Add the getter
        BindAccessor(name, &var, sizeof(var), &sqDefaultGet<C, V>, cd->getTable);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Bind a class static variable
    ///
    /// \param name Name of the variable as it will appear in Squirrel
    /// \param var  Variable to bind
    ///
    /// \tparam V Type of variable (usually doesnt need to be defined explicitly)
    ///
    /// \remarks
    /// If V is not a pointer or reference, then it must have a default constructor.
    /// See Sqrat::Class::Prop to work around this requirement
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    Class& StaticVar(const SQChar* name, V* var) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);

        // Add the getter
        BindAccessor(name, &var, sizeof(var), &sqStaticGet<C, V>, cd->getTable);

        // Add the setter
        BindAccessor(name, &var, sizeof(var), &sqStaticSet<C, V>, cd->setTable);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class property
    ///
    /// \param name      Name of the variable as it will appear in Squirrel
    /// \param getMethod Getter for the variable
    /// \param setMethod Setter for the variable
    ///
    /// \tparam F1 Type of get function (usually doesnt need to be defined explicitly)
    /// \tparam F2 Type of set function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// This method binds setter and getter functions in C++ to Squirrel as if they are a class variable.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F1, class F2>
    Class& Prop(const SQChar* name, F1 getMethod, F2 setMethod) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);

        if(getMethod != NULL) {
            // Add the getter
            BindAccessor(name, &getMethod, sizeof(getMethod), SqMemberOverloadedFunc(getMethod), cd->getTable);
        }

        if(setMethod != NULL) {
            // Add the setter
            BindAccessor(name, &setMethod, sizeof(setMethod), SqMemberOverloadedFunc(setMethod), cd->setTable);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class property (using global functions instead of member functions)
    ///
    /// \param name      Name of the variable as it will appear in Squirrel
    /// \param getMethod Getter for the variable
    /// \param setMethod Setter for the variable
    ///
    /// \tparam F1 Type of get function (usually doesnt need to be defined explicitly)
    /// \tparam F2 Type of set function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// This method binds setter and getter functions in C++ to Squirrel as if they are a class variable.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F1, class F2>
    Class& GlobalProp(const SQChar* name, F1 getMethod, F2 setMethod) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);

        if(getMethod != NULL) {
            // Add the getter
            BindAccessor(name, &getMethod, sizeof(getMethod), SqMemberGlobalOverloadedFunc(getMethod), cd->getTable);
        }

        if(setMethod != NULL) {
            // Add the setter
            BindAccessor(name, &setMethod, sizeof(setMethod), SqMemberGlobalOverloadedFunc(setMethod), cd->setTable);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a read-only class property
    ///
    /// \param name      Name of the variable as it will appear in Squirrel
    /// \param getMethod Getter for the variable
    ///
    /// \tparam F Type of get function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// This method binds a getter function in C++ to Squirrel as if it is a class variable.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& Prop(const SQChar* name, F getMethod) {
        // Add the getter
        BindAccessor(name, &getMethod, sizeof(getMethod), SqMemberOverloadedFunc(getMethod), ClassType<C>::getClassData(vm)->getTable);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a read-only class property (using a global function instead of a member function)
    ///
    /// \param name      Name of the variable as it will appear in Squirrel
    /// \param getMethod Getter for the variable
    ///
    /// \tparam F Type of get function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// This method binds a getter function in C++ to Squirrel as if it is a class variable.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& GlobalProp(const SQChar* name, F getMethod) {
        // Add the getter
        BindAccessor(name, &getMethod, sizeof(getMethod), SqMemberGlobalOverloadedFunc(getMethod), ClassType<C>::getClassData(vm)->getTable);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class function
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& Func(const SQChar* name, F method) {
        BindFunc(name, &method, sizeof(method), SqMemberFunc(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a class function with overloading enabled
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// Overloading in this context means to allow the function name to be used with functions
    /// of a different number of arguments. This definition differs from others (e.g. C++'s).
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& Overload(const SQChar* name, F method) {
        BindOverload(name, &method, sizeof(method), SqMemberOverloadedFunc(method), SqOverloadFunc(method), SqGetArgCount(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a global function as a class function
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& GlobalFunc(const SQChar* name, F method) {
        BindFunc(name, &method, sizeof(method), SqMemberGlobalFunc(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a static class function
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& StaticFunc(const SQChar* name, F method) {
        BindFunc(name, &method, sizeof(method), SqGlobalFunc(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a global function as a class function with overloading enabled
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// Overloading in this context means to allow the function name to be used with functions
    /// of a different number of arguments. This definition differs from others (e.g. C++'s).
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& GlobalOverload(const SQChar* name, F method) {
        BindOverload(name, &method, sizeof(method), SqMemberGlobalOverloadedFunc(method), SqOverloadFunc(method), SqGetArgCount(method) - 1);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a static class function with overloading enabled
    ///
    /// \param name   Name of the function as it will appear in Squirrel
    /// \param method Function to bind
    ///
    /// \tparam F Type of function (usually doesnt need to be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// Overloading in this context means to allow the function name to be used with functions
    /// of a different number of arguments. This definition differs from others (e.g. C++'s).
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    Class& StaticOverload(const SQChar* name, F method) {
        BindOverload(name, &method, sizeof(method), SqGlobalOverloadedFunc(method), SqOverloadFunc(method), SqGetArgCount(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a Squirrel function as defined by the Squirrel documentation as a class function
    ///
    /// \param name Name of the function as it will appear in Squirrel
    /// \param func Function to bind
    ///
    /// \return The Class itself so the call can be chained
    ///
    /// \remarks
    /// Inside of the function, the class instance the function was called with will be at index 1 on the
    /// stack and all arguments will be after that index in the order they were given to the function.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Class& SquirrelFunc(const SQChar* name, SQFUNCTION func) {
        sq_pushobject(vm, ClassType<C>::getClassData(vm)->classObj);
        sq_pushstring(vm, name, -1);
        sq_newclosure(vm, func, 0);
        sq_newslot(vm, -3, false);
        sq_pop(vm, 1); // pop table

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets a Function from a name in the Class
    ///
    /// \param name The name in the class that contains the Function
    ///
    /// \return Function found in the Class (null if failed)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function GetFunction(const SQChar* name) {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        HSQOBJECT funcObj;
        sq_pushobject(vm, cd->classObj);
        sq_pushstring(vm, name, -1);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Function();
        }
        SQObjectType value_type = sq_gettype(vm, -1);
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE) {
            sq_pop(vm, 2);
            return Function();
        }
#else
        sq_get(vm, -2);
#endif
        sq_getstackobj(vm, -1, &funcObj);
        Function ret(vm, cd->classObj, funcObj); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
    }

protected:

/// @cond DEV

    static SQInteger ClassWeakref(HSQUIRRELVM vm) {
        sq_weakref(vm, -1);
        return 1;
    }

    static SQInteger ClassTypeof(HSQUIRRELVM vm) {
        sq_pushstring(vm, ClassType<C>::ClassName().c_str(), -1);
        return 1;
    }

    static SQInteger ClassCloned(HSQUIRRELVM vm) {
        SQTRY()
        Sqrat::Var<const C*> other(vm, 2);
        SQCATCH_NOEXCEPT(vm) {
            SQCLEAR(vm);
            return SQ_ERROR;
        }
#if !defined (SCRAT_NO_ERROR_CHECKING)
        return ClassType<C>::CopyFunc()(vm, 1, other.value);
#else
        ClassType<C>::CopyFunc()(vm, 1, other.value);
        return 0;
#endif
        SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
            SQUNUSED(e); // this is to avoid a warning in MSVC
#endif
            return SQ_ERROR;
        }
    }

    // Initialize the required data structure for the class
    void InitClass(ClassData<C>* cd) {
        cd->instances.Init(new typename unordered_map<C*, HSQOBJECT>::type);

        // push the class
        sq_pushobject(vm, cd->classObj);

        // set the typetag of the class
        sq_settypetag(vm, -1, cd->staticData.Get());

        // add the default constructor
        sq_pushstring(vm, _SC("constructor"), -1);
        sq_newclosure(vm, &A::New, 0);
        sq_newslot(vm, -3, false);

        // add the set table (static)
        HSQOBJECT& setTable = cd->setTable;
        sq_resetobject(&setTable);
        sq_pushstring(vm, _SC("__setTable"), -1);
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &setTable);
        sq_addref(vm, &setTable);
        sq_newslot(vm, -3, true);

        // add the get table (static)
        HSQOBJECT& getTable = cd->getTable;
        sq_resetobject(&getTable);
        sq_pushstring(vm, _SC("__getTable"), -1);
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &getTable);
        sq_addref(vm, &getTable);
        sq_newslot(vm, -3, true);

        // override _set
        sq_pushstring(vm, _SC("_set"), -1);
        sq_pushobject(vm, setTable); // Push the set table as a free variable
        sq_newclosure(vm, &sqVarSet, 1);
        sq_newslot(vm, -3, false);

        // override _get
        sq_pushstring(vm, _SC("_get"), -1);
        sq_pushobject(vm, getTable); // Push the get table as a free variable
        sq_newclosure(vm, &sqVarGet, 1);
        sq_newslot(vm, -3, false);

        // add weakref (apparently not provided by default)
        sq_pushstring(vm, _SC("weakref"), -1);
        sq_newclosure(vm, &Class::ClassWeakref, 0);
        sq_newslot(vm, -3, false);

        // add _typeof
        sq_pushstring(vm, _SC("_typeof"), -1);
        sq_newclosure(vm, &Class::ClassTypeof, 0);
        sq_newslot(vm, -3, false);

        // add _cloned
        sq_pushstring(vm, _SC("_cloned"), -1);
        sq_newclosure(vm, &Class::ClassCloned, 0);
        sq_newslot(vm, -3, false);

        // pop the class
        sq_pop(vm, 1);
    }

    // Helper function used to bind getters and setters
    inline void BindAccessor(const SQChar* name, void* var, size_t varSize, SQFUNCTION func, HSQOBJECT table) {
        // Push the get or set table
        sq_pushobject(vm, table);
        sq_pushstring(vm, name, -1);

        // Push the variable offset as a free variable
        SQUserPointer varPtr = sq_newuserdata(vm, static_cast<SQUnsignedInteger>(varSize));
        memcpy(varPtr, var, varSize);

        // Create the accessor function
        sq_newclosure(vm, func, 1);

        // Add the accessor to the table
        sq_newslot(vm, -3, false);

        // Pop get/set table
        sq_pop(vm, 1);
    }

    // constructor binding
    Class& BindConstructor(SQFUNCTION method, SQInteger nParams, const SQChar *name = 0) {
        SQFUNCTION overload = SqOverloadFunc(method);
        bool alternative_global = false;
        if (name == 0)
            name = _SC("constructor");
        else alternative_global = true;
        string overloadName = SqOverloadName::Get(name, nParams);

        if (!alternative_global )
        {
            // push the class
            sq_pushobject(vm, ClassType<C>::getClassData(vm)->classObj);
        }
        else
        {
            // the containing environment is the root table??
            sq_pushroottable(vm);
        }

        // Bind overload handler
        sq_pushstring(vm, name, -1);
        sq_pushstring(vm, name, -1); // function name is passed as a free variable
        sq_newclosure(vm, overload, 1);
        sq_newslot(vm, -3, false);

        // Bind overloaded allocator function
        sq_pushstring(vm, overloadName.c_str(), -1);
        sq_newclosure(vm, method, 0);
        sq_setparamscheck(vm,nParams + 1,NULL);
        sq_newslot(vm, -3, false);
        sq_pop(vm, 1);
        return *this;
    }

/// @endcond

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with no arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::iNew, 0, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 1 argument (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1>, 1, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 2 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2>, 2, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 3 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3>, 3, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 4 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4>, 4, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 5 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    /// \tparam A5 Type of argument 5 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4, class A5>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4, A5>, 5, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 6 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    /// \tparam A5 Type of argument 5 of the constructor (must be defined explicitly)
    /// \tparam A6 Type of argument 6 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4, A5, A6>, 6, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 7 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    /// \tparam A5 Type of argument 5 of the constructor (must be defined explicitly)
    /// \tparam A6 Type of argument 6 of the constructor (must be defined explicitly)
    /// \tparam A7 Type of argument 7 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4, A5, A6, A7>, 7, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 8 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    /// \tparam A5 Type of argument 5 of the constructor (must be defined explicitly)
    /// \tparam A6 Type of argument 6 of the constructor (must be defined explicitly)
    /// \tparam A7 Type of argument 7 of the constructor (must be defined explicitly)
    /// \tparam A8 Type of argument 8 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4, A5, A6, A7, A8>, 8, name);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constructor with 9 arguments (there can only be one constructor of this many arguments for a given name)
    ///
    /// \param name Name of the constructor as it will appear in Squirrel (default value creates a traditional constructor)
    ///
    /// \tparam A1 Type of argument 1 of the constructor (must be defined explicitly)
    /// \tparam A2 Type of argument 2 of the constructor (must be defined explicitly)
    /// \tparam A3 Type of argument 3 of the constructor (must be defined explicitly)
    /// \tparam A4 Type of argument 4 of the constructor (must be defined explicitly)
    /// \tparam A5 Type of argument 5 of the constructor (must be defined explicitly)
    /// \tparam A6 Type of argument 6 of the constructor (must be defined explicitly)
    /// \tparam A7 Type of argument 7 of the constructor (must be defined explicitly)
    /// \tparam A8 Type of argument 8 of the constructor (must be defined explicitly)
    /// \tparam A9 Type of argument 9 of the constructor (must be defined explicitly)
    ///
    /// \return The Class itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    Class& Ctor(const SQChar *name = 0) {
        return BindConstructor(A::template iNew<A1, A2, A3, A4, A5, A6, A7, A8, A9>, 9, name);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Facilitates exposing a C++ class with a base class to Squirrel
///
/// \tparam C Class type to expose
/// \tparam B Base class type (must already be bound)
/// \tparam A An allocator to use when instantiating and destroying class instances of this type in Squirrel
///
/// \remarks
/// Classes in Squirrel are single-inheritance only, and as such Sqrat only allows for single inheritance as well.
///
/// \remarks
/// DefaultAllocator is used if no allocator is specified. This should be sufficent for most classes,
/// but if specific behavior is desired, it can be overridden. If the class should not be instantiated from
/// Squirrel the NoConstructor allocator may be used. See NoCopy and CopyOnly too.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class B, class A = DefaultAllocator<C> >
class DerivedClass : public Class<C, A>
{
private:

    static SQInteger cleanup_hook(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        ClassData<C>** ud = reinterpret_cast<ClassData<C>**>(ptr);
        delete *ud;
        return 0;
    }

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs the DerivedClass object
    ///
    /// A DerivedClass object doesnt do anything on its own.
    /// It must be told what methods and variables it contains.
    /// This is done using Class methods such as Class::Func and Class::Var.
    /// Then the DerivedClass must be exposed to Squirrel.
    /// This is usually done by calling TableBase::Bind on a RootTable with the DerivedClass.
    ///
    /// \param v         Squirrel virtual machine to create the DerivedClass for
    /// \param className A necessarily unique name for the class that can appear in error messages
    ///
    /// \remarks
    /// You MUST bind the base class fully before constructing a derived class.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DerivedClass(HSQUIRRELVM v, const string& className) : Class<C, A>(v, string(), false) {
        if (!ClassType<C>::hasClassData(v)) {
            sq_pushregistrytable(v);
            sq_pushstring(v, "__classes", -1);
            if (SQ_FAILED(sq_rawget(v, -2))) {
                sq_newtable(v);
                sq_pushstring(v, "__classes", -1);
                sq_push(v, -2);
                sq_rawset(v, -4);
            }
            sq_pushstring(v, className.c_str(), -1);
            ClassData<C>** ud = reinterpret_cast<ClassData<C>**>(sq_newuserdata(v, sizeof(ClassData<C>*)));
            *ud = new ClassData<C>;
            sq_setreleasehook(v, -1, &cleanup_hook);
            sq_rawset(v, -3);
            sq_pop(v, 2);

            ClassData<B>* bd = ClassType<B>::getClassData(v);
            ClassData<C>* cd = *ud;

            if (ClassType<C>::getStaticClassData().Expired()) {
                cd->staticData.Init(new StaticClassData<C, B>);
                cd->staticData->copyFunc  = &A::Copy;
                cd->staticData->className = string(className);
                cd->staticData->baseClass = bd->staticData.Get();

                ClassType<C>::getStaticClassData() = cd->staticData;
            } else {
                cd->staticData = ClassType<C>::getStaticClassData().Lock();
            }

            HSQOBJECT& classObj = cd->classObj;
            sq_resetobject(&classObj);

            sq_pushobject(v, bd->classObj);
            sq_newclass(v, true);
            sq_getstackobj(v, -1, &classObj);
            sq_addref(v, &classObj); // must addref before the pop!
            sq_pop(v, 1);
            InitDerivedClass(v, cd, bd);
        }
    }

protected:

/// @cond DEV

    void InitDerivedClass(HSQUIRRELVM vm, ClassData<C>* cd, ClassData<B>* bd) {
        cd->instances.Init(new typename unordered_map<C*, HSQOBJECT>::type);

        // push the class
        sq_pushobject(vm, cd->classObj);

        // set the typetag of the class
        sq_settypetag(vm, -1, cd->staticData.Get());

        // add the default constructor
        sq_pushstring(vm, _SC("constructor"), -1);
        sq_newclosure(vm, &A::New, 0);
        sq_newslot(vm, -3, false);

        // clone the base classes set table (static)
        HSQOBJECT& setTable = cd->setTable;
        sq_resetobject(&setTable);
        sq_pushobject(vm, bd->setTable);
        sq_pushstring(vm, _SC("__setTable"), -1);
        sq_clone(vm, -2);
        sq_remove(vm, -3);
        sq_getstackobj(vm, -1, &setTable);
        sq_addref(vm, &setTable);
        sq_newslot(vm, -3, true);

        // clone the base classes get table (static)
        HSQOBJECT& getTable = cd->getTable;
        sq_resetobject(&getTable);
        sq_pushobject(vm, bd->getTable);
        sq_pushstring(vm, _SC("__getTable"), -1);
        sq_clone(vm, -2);
        sq_remove(vm, -3);
        sq_getstackobj(vm, -1, &getTable);
        sq_addref(vm, &getTable);
        sq_newslot(vm, -3, true);

        // override _set
        sq_pushstring(vm, _SC("_set"), -1);
        sq_pushobject(vm, setTable); // Push the set table as a free variable
        sq_newclosure(vm, sqVarSet, 1);
        sq_newslot(vm, -3, false);

        // override _get
        sq_pushstring(vm, _SC("_get"), -1);
        sq_pushobject(vm, getTable); // Push the get table as a free variable
        sq_newclosure(vm, sqVarGet, 1);
        sq_newslot(vm, -3, false);

        // add weakref (apparently not provided by default)
        sq_pushstring(vm, _SC("weakref"), -1);
        sq_newclosure(vm, &Class<C, A>::ClassWeakref, 0);
        sq_newslot(vm, -3, false);

        // add _typeof
        sq_pushstring(vm, _SC("_typeof"), -1);
        sq_newclosure(vm, &Class<C, A>::ClassTypeof, 0);
        sq_newslot(vm, -3, false);

        // add _cloned
        sq_pushstring(vm, _SC("_cloned"), -1);
        sq_newclosure(vm, &Class<C, A>::ClassCloned, 0);
        sq_newslot(vm, -3, false);

        // pop the class
        sq_pop(vm, 1);
    }

/// @endcond

};

}

#endif

// <--- back to sqrat.h
// ---- #include "sqrat/sqratFunction.h"
// ---> including sqratFunction.h
// <--- back to sqrat.h
// ---- #include "sqrat/sqratConst.h"
// ---> including sqratConst.h
//
// SqratConst: Constant and Enumeration Binding
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_CONST_H_)
#define _SCRAT_CONST_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratConst.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratConst.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Facilitates exposing a C++ enumeration to Squirrel
///
/// \remarks
/// The Enumeration class only facilitates binding C++ enumerations that contain only integers,
/// floats, and strings because the Squirrel constant table can only contain these types of
/// values. Other types of enumerations can be bound using Class::SetStaticValue instead.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Enumeration : public Object {
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs the Enumeration object
    ///
    /// An Enumeration object doesnt do anything on its own.
    /// It must be told what constant values it contains.
    /// This is done using Enumeration::Const.
    /// Then the Enumeration must be exposed to Squirrel.
    /// This is done by calling ConstTable::Enum with the Enumeration.
    ///
    /// \param v           Squirrel virtual machine to create the Enumeration for
    /// \param createTable Whether the underlying table that values are bound to is created by the constructor
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Enumeration(HSQUIRRELVM v = DefaultVM::Get(), bool createTable = true) : Object(v, false) {
        if(createTable) {
            sq_newtable(vm);
            sq_getstackobj(vm,-1,&obj);
            sq_addref(vm, &obj);
            sq_pop(vm,1);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds an enumeration value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The Enumeration itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Enumeration& Const(const SQChar* name, const int val) {
        BindValue<int>(name, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds an enumeration value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The Enumeration itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Enumeration& Const(const SQChar* name, const float val) {
        BindValue<float>(name, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds an enumeration value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The Enumeration itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Enumeration& Const(const SQChar* name, const SQChar* val) {
        BindValue<const SQChar*>(name, val, false);
        return *this;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Facilitates exposing a C++ constant to Squirrel
///
/// \remarks
/// The ConstTable class only facilitates binding C++ constants that are integers,
/// floats, and strings because the Squirrel constant table can only contain these types of
/// values. Other types of constants can be bound using Class::SetStaticValue instead.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConstTable : public Enumeration {
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs a ConstTable object to represent the given VM's const table
    ///
    /// \param v VM to get the ConstTable for
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ConstTable(HSQUIRRELVM v = DefaultVM::Get()) : Enumeration(v, false) {
        sq_pushconsttable(vm);
        sq_getstackobj(vm,-1, &obj);
        sq_pop(v,1); // No addref needed, since the consttable is always around
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constant value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The ConstTable itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ConstTable& Const(const SQChar* name, const int val) {
        Enumeration::Const(name, val);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constant value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The ConstTable itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ConstTable& Const(const SQChar* name, const float val) {
        Enumeration::Const(name, val);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a constant value
    ///
    /// \param name Name of the value as it will appear in Squirrel
    /// \param val  Value to bind
    ///
    /// \return The ConstTable itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ConstTable& Const(const SQChar* name, const SQChar* val) {
        Enumeration::Const(name, val);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds an Enumeration to the ConstTable
    ///
    /// \param name Name of the enumeration as it will appear in Squirrel
    /// \param en   Enumeration to bind
    ///
    /// \return The ConstTable itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ConstTable& Enum(const SQChar* name, Enumeration& en) {
        sq_pushobject(vm, GetObject());
        sq_pushstring(vm, name, -1);
        sq_pushobject(vm, en.GetObject());
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
        return *this;
    }
};

}

#endif

// <--- back to sqrat.h
// ---- #include "sqrat/sqratUtil.h"
// ---> including sqratUtil.h
// <--- back to sqrat.h
// ---- #include "sqrat/sqratScript.h"
// ---> including sqratScript.h
//
// SqratScript: Script Compilation and Execution
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_SCRIPT_H_)
#define _SCRAT_SCRIPT_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratScript.h
// ---- #include <sqstdio.h>
// ---> including sqstdio.h
/*	see copyright notice in squirrel.h */
#ifndef _SQSTDIO_H_
#define _SQSTDIO_H_

#ifdef __cplusplus

#define SQSTD_STREAM_TYPE_TAG 0x80000000

struct SQStream {
	virtual SQInteger Read(void *buffer, SQInteger size) = 0;
	virtual SQInteger Write(void *buffer, SQInteger size) = 0;
	virtual SQInteger Flush() = 0;
	virtual SQInteger Tell() = 0;
	virtual SQInteger Len() = 0;
	virtual SQInteger Seek(SQInteger offset, SQInteger origin) = 0;
	virtual bool IsValid() = 0;
	virtual bool EOS() = 0;
};

extern "C" {
#endif

#define SQ_SEEK_CUR 0
#define SQ_SEEK_END 1
#define SQ_SEEK_SET 2

typedef void* SQFILE;

SQUIRREL_API SQFILE sqstd_fopen(const SQChar *,const SQChar *);
SQUIRREL_API SQInteger sqstd_fread(SQUserPointer, SQInteger, SQInteger, SQFILE);
SQUIRREL_API SQInteger sqstd_fwrite(const SQUserPointer, SQInteger, SQInteger, SQFILE);
SQUIRREL_API SQInteger sqstd_fseek(SQFILE , SQInteger , SQInteger);
SQUIRREL_API SQInteger sqstd_ftell(SQFILE);
SQUIRREL_API SQInteger sqstd_fflush(SQFILE);
SQUIRREL_API SQInteger sqstd_fclose(SQFILE);
SQUIRREL_API SQInteger sqstd_feof(SQFILE);

SQUIRREL_API SQRESULT sqstd_createfile(HSQUIRRELVM v, SQFILE file,SQBool own);
SQUIRREL_API SQRESULT sqstd_getfile(HSQUIRRELVM v, SQInteger idx, SQFILE *file);

//compiler helpers
SQUIRREL_API SQRESULT sqstd_loadfile(HSQUIRRELVM v,const SQChar *filename,SQBool printerror);
SQUIRREL_API SQRESULT sqstd_dofile(HSQUIRRELVM v,const SQChar *filename,SQBool retval,SQBool printerror);
SQUIRREL_API SQRESULT sqstd_writeclosuretofile(HSQUIRRELVM v,const SQChar *filename);

SQUIRREL_API SQRESULT sqstd_register_iolib(HSQUIRRELVM v);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQSTDIO_H_*/


// <--- back to sqratScript.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratScript.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class for managing Squirrel scripts
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Script : public Object {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor
    ///
    /// \param v VM that the Script will be associated with
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Script(HSQUIRRELVM v = DefaultVM::Get()) : Object(v, true) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up the Script using a string containing a Squirrel script
    ///
    /// \param script String containing a file path to a Squirrel script
    /// \param name   Optional string containing the script's name (for errors)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void CompileString(const string& script, const string& name = _SC("")) {
        if(!sq_isnull(obj)) {
            sq_release(vm, &obj);
            sq_resetobject(&obj);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_compilebuffer(vm, script.c_str(), static_cast<SQInteger>(script.size() /** sizeof(SQChar)*/), name.c_str(), true))) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sq_compilebuffer(vm, script.c_str(), static_cast<SQInteger>(script.size() /** sizeof(SQChar)*/), name.c_str(), true);
#endif
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm, 1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up the Script using a string containing a Squirrel script
    ///
    /// \param script String containing a file path to a Squirrel script
    /// \param errMsg String that is filled with any errors that may occur
    /// \param name   Optional string containing the script's name (for errors)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool CompileString(const string& script, string& errMsg, const string& name = _SC("")) {
        if(!sq_isnull(obj)) {
            sq_release(vm, &obj);
            sq_resetobject(&obj);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_compilebuffer(vm, script.c_str(), static_cast<SQInteger>(script.size() /** sizeof(SQChar)*/), name.c_str(), true))) {
            errMsg = LastErrorString(vm);
            return false;
        }
#else
        sq_compilebuffer(vm, script.c_str(), static_cast<SQInteger>(script.size() /** sizeof(SQChar)*/), name.c_str(), true);
#endif
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm, 1);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up the Script using a file containing a Squirrel script
    ///
    /// \param path File path containing a Squirrel script
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void CompileFile(const string& path) {
        if(!sq_isnull(obj)) {
            sq_release(vm, &obj);
            sq_resetobject(&obj);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sqstd_loadfile(vm, path.c_str(), true))) {
            SQTHROW(vm, LastErrorString(vm));
            return;
        }
#else
        sqstd_loadfile(vm, path.c_str(), true);
#endif
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm, 1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets up the Script using a file containing a Squirrel script
    ///
    /// \param path   File path containing a Squirrel script
    /// \param errMsg String that is filled with any errors that may occur
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool CompileFile(const string& path, string& errMsg) {
        if(!sq_isnull(obj)) {
            sq_release(vm, &obj);
            sq_resetobject(&obj);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sqstd_loadfile(vm, path.c_str(), true))) {
            errMsg = LastErrorString(vm);
            return false;
        }
#else
        sqstd_loadfile(vm, path.c_str(), true);
#endif
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm, 1);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the script
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Run() {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(!sq_isnull(obj)) {
            SQRESULT result;
            SQInteger top = sq_gettop(vm);
            sq_pushobject(vm, obj);
            sq_pushroottable(vm);
            result = sq_call(vm, 1, false, true);
            sq_settop(vm, top);
            if(SQ_FAILED(result)) {
                SQTHROW(vm, LastErrorString(vm));
                return;
            }
        }
#else
        SQInteger top = sq_gettop(vm);
        sq_pushobject(vm, obj);
        sq_pushroottable(vm);
        sq_call(vm, 1, false, true);
        sq_settop(vm, top);
#endif
    }

#if !defined (SCRAT_NO_ERROR_CHECKING)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Runs the script
    ///
    /// \param errMsg String that is filled with any errors that may occur
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool Run(string& errMsg) {
        if(!sq_isnull(obj)) {
            SQRESULT result;
            SQInteger top = sq_gettop(vm);
            sq_pushobject(vm, obj);
            sq_pushroottable(vm);
            result = sq_call(vm, 1, false, true);
            sq_settop(vm, top);
            if(SQ_FAILED(result)) {
                errMsg = LastErrorString(vm);
                return false;
            }
            return true;
        }
        return false;
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Writes the byte code of the Script to a file
    ///
    /// \param path File path to write to
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void WriteCompiledFile(const string& path) {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(!sq_isnull(obj)) {
            sq_pushobject(vm, obj);
            sqstd_writeclosuretofile(vm, path.c_str());
        }
#else
        sq_pushobject(vm, obj);
        sqstd_writeclosuretofile(vm, path.c_str());
#endif
        sq_pop(vm, 1); // needed?
    }
};

}

#endif

// <--- back to sqrat.h
// ---- #include "sqrat/sqratArray.h"
// ---> including sqratArray.h
//
// SqratArray: Array Binding
//

//
// Copyright 2011 Alston Chen
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SCRAT_ARRAY_H_)
#define _SCRAT_ARRAY_H_

// ---- #include <squirrel.h>
// ---> including squirrel.h
// <--- back to sqratArray.h
#include <string.h>

// ---- #include "sqratObject.h"
// ---> including sqratObject.h
// <--- back to sqratArray.h
// ---- #include "sqratFunction.h"
// ---> including sqratFunction.h
// <--- back to sqratArray.h
// ---- #include "sqratGlobalMethods.h"
// ---> including sqratGlobalMethods.h
// <--- back to sqratArray.h

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The base class for Array that implements almost all of its functionality
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ArrayBase : public Object {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /// \param v VM that the array will exist in
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase(HSQUIRRELVM v = DefaultVM::Get()) : Object(v, true) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the ArrayBase from an Object that already exists
    ///
    /// \param obj An Object that should already represent a Squirrel array
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase(const Object& obj) : Object(obj) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the ArrayBase from a HSQOBJECT and HSQUIRRELVM that already exist
    ///
    /// \param o Squirrel object that should already represent a Squirrel array
    /// \param v Squirrel VM that contains the Squirrel object given
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase(HSQOBJECT o, HSQUIRRELVM v = DefaultVM::Get()) : Object(o, v) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a Table or Class to the Array (can be used to facilitate namespaces)
    ///
    /// \param index The index in the array being assigned a Table or Class
    /// \param obj   Table or Class that is being placed in the Array
    ///
    /// \remarks
    /// Bind cannot be called "inline" like other functions because it introduces order-of-initialization bugs.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind(const SQInteger index, Object& obj) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
        sq_pushobject(vm, obj.GetObject());
        sq_set(vm, -3);
        sq_pop(vm,1); // pop array
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Binds a raw Squirrel closure to the Array
    ///
    /// \param index The index in the array being assigned a function
    /// \param func  Squirrel function that is being placed in the Array
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase& SquirrelFunc(const SQInteger index, SQFUNCTION func) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
        sq_newclosure(vm, func, 0);
        sq_set(vm, -3);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets an index in the Array to a specific value
    ///
    /// \param index The index in the array being assigned a value
    /// \param val   Value that is being placed in the Array
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& SetValue(const SQInteger index, const V& val) {
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
        PushVar(vm, val);
        sq_set(vm, -3);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets an index in the Array to a specific instance (like a reference)
    ///
    /// \param index The index in the array being assigned a value
    /// \param val   Pointer to the instance that is being placed in the Array
    ///
    /// \tparam V Type of instance (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& SetInstance(const SQInteger index, V* val) {
        BindInstance<V>(index, val, false);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Sets an index in the Array to a specific function
    ///
    /// \param index  The index in the array being assigned a value
    /// \param method Function that is being placed in the Array
    ///
    /// \tparam F Type of function (only define this if you need to choose a certain template specialization or overload)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class F>
    ArrayBase& Func(const SQInteger index, F method) {
        BindFunc(index, &method, sizeof(method), SqGlobalFunc(method));
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns the element at a given index
    ///
    /// \param index Index of the element
    ///
    /// \tparam T Type of element (fails if element is not of this type)
    ///
    /// \return SharedPtr containing the element (or null if failed)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    SharedPtr<T> GetValue(int index)
    {
        sq_pushobject(vm, obj);
        sq_pushinteger(vm, index);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            SQTHROW(vm, _SC("illegal index"));
            return SharedPtr<T>();
        }
#else
        sq_get(vm, -2);
#endif
        SQTRY()
        Var<SharedPtr<T> > element(vm, -1);
        SQCATCH_NOEXCEPT(vm) {
            sq_pop(vm, 2);
            return SharedPtr<T>();
        }
        sq_pop(vm, 2);
        return element.value;
        SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
            SQUNUSED(e); // avoid "unreferenced local variable" warning
#endif
            sq_pop(vm, 2);
            SQRETHROW(vm);
        }
        return SharedPtr<T>(); // avoid "not all control paths return a value" warning
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gets a Function from an index in the Array
    ///
    /// \param index The index in the array that contains the Function
    ///
    /// \return Function found in the Array (null if failed)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Function GetFunction(const SQInteger index) {
        HSQOBJECT funcObj;
        sq_pushobject(vm, GetObject());
        sq_pushinteger(vm, index);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if(SQ_FAILED(sq_get(vm, -2))) {
            sq_pop(vm, 1);
            return Function();
        }
        SQObjectType value_type = sq_gettype(vm, -1);
        if (value_type != OT_CLOSURE && value_type != OT_NATIVECLOSURE) {
            sq_pop(vm, 2);
            return Function();
        }
#else
        sq_get(vm, -2);
#endif
        sq_getstackobj(vm, -1, &funcObj);
        Function ret(vm, GetObject(), funcObj); // must addref before the pop!
        sq_pop(vm, 2);
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Fills a C array with the elements of the Array
    ///
    /// \param array C array to be filled
    /// \param size  The amount of elements to fill the C array with
    ///
    /// \tparam T Type of elements (fails if any elements in Array are not of this type)
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void GetArray(T* array, int size)
    {
        HSQOBJECT value = GetObject();
        sq_pushobject(vm, value);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (size > sq_getsize(vm, -1)) {
            sq_pop(vm, 1);
            SQTHROW(vm, _SC("array buffer size too big"));
            return;
        }
#endif
        sq_pushnull(vm);
        SQInteger i;
        while (SQ_SUCCEEDED(sq_next(vm, -2))) {
            sq_getinteger(vm, -2, &i);
            if (i >= size) break;
            SQTRY()
            Var<const T&> element(vm, -1);
            SQCATCH_NOEXCEPT(vm) {
                sq_pop(vm, 4);
                return;
            }
            sq_pop(vm, 2);
            array[i] = element.value;
            SQCATCH(vm) {
#if defined (SCRAT_USE_EXCEPTIONS)
                SQUNUSED(e); // avoid "unreferenced local variable" warning
#endif
                sq_pop(vm, 4);
                SQRETHROW(vm);
            }
        }
        sq_pop(vm, 2); // pops the null iterator and the array object
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Appends a value to the end of the Array
    ///
    /// \param val Value that is being placed in the Array
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& Append(const V& val) {
        sq_pushobject(vm, GetObject());
        PushVar(vm, val);
        sq_arrayappend(vm, -2);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Appends an instance to the end of the Array (like a reference)
    ///
    /// \param val Pointer to the instance that is being placed in the Array
    ///
    /// \tparam V Type of instance (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& Append(V* val) {
        sq_pushobject(vm, GetObject());
        PushVar(vm, val);
        sq_arrayappend(vm, -2);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Inserts a value in a position in the Array
    ///
    /// \param destpos Index to put the new value in
    /// \param val     Value that is being placed in the Array
    ///
    /// \tparam V Type of value (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& Insert(const SQInteger destpos, const V& val) {
        sq_pushobject(vm, GetObject());
        PushVar(vm, val);
        sq_arrayinsert(vm, -2, destpos);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Inserts an instance in a position in the Array (like a reference)
    ///
    /// \param destpos Index to put the new value in
    /// \param val     Pointer to the instance that is being placed in the Array
    ///
    /// \tparam V Type of instance (usually doesnt need to be defined explicitly)
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class V>
    ArrayBase& Insert(const SQInteger destpos, V* val) {
        sq_pushobject(vm, GetObject());
        PushVar(vm, val);
        sq_arrayinsert(vm, -2, destpos);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Removes the last element from the Array
    ///
    /// \return Object for the element that was removed (null if failed)
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Object Pop() {
        HSQOBJECT slotObj;
        sq_pushobject(vm, GetObject());
        if(SQ_FAILED(sq_arraypop(vm, -1, true))) {
            sq_pop(vm, 1);
            return Object(); // Return a NULL object
        } else {
            sq_getstackobj(vm, -1, &slotObj);
            Object ret(slotObj, vm);
            sq_pop(vm, 2);
            return ret;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Removes an element at a specific index from the Array
    ///
    /// \param itemidx Index of the element being removed
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase& Remove(const SQInteger itemidx) {
        sq_pushobject(vm, GetObject());
        sq_arrayremove(vm, -1, itemidx);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Resizes the Array
    ///
    /// \param newsize Desired size of the Array in number of elements
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase& Resize(const SQInteger newsize) {
        sq_pushobject(vm, GetObject());
        sq_arrayresize(vm, -1, newsize);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Reverses the elements of the array in place
    ///
    /// \return The Array itself so the call can be chained
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBase& Reverse() {
        sq_pushobject(vm, GetObject());
        sq_arrayreverse(vm, -1);
        sq_pop(vm,1); // pop array
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns the length of the Array
    ///
    /// \return Length in number of elements
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SQInteger Length() const
    {
        sq_pushobject(vm, obj);
        SQInteger r = sq_getsize(vm, -1);
        sq_pop(vm, 1);
        return r;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an array in Squirrel
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Array : public ArrayBase {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Default constructor (null)
    ///
    /// \remarks
    /// The Array is invalid until it is given a VM to exist in.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Array() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Constructs an Array
    ///
    /// \param v    VM to create the Array in
    /// \param size An optional size hint
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Array(HSQUIRRELVM v, const SQInteger size = 0) : ArrayBase(v) {
        sq_newarray(vm, size);
        sq_getstackobj(vm,-1,&obj);
        sq_addref(vm, &obj);
        sq_pop(vm,1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the Array from an Object that already exists
    ///
    /// \param obj An Object that should already represent a Squirrel array
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Array(const Object& obj) : ArrayBase(obj) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Construct the Array from a HSQOBJECT and HSQUIRRELVM that already exist
    ///
    /// \param o Squirrel object that should already represent a Squirrel array
    /// \param v Squirrel VM that contains the Squirrel object given
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Array(HSQOBJECT o, HSQUIRRELVM v = DefaultVM::Get()) : ArrayBase(o, v) {
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Array instances to and from the stack as references (arrays are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Array> {

    Array value; ///< The actual value of get operations

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Attempts to get the value off the stack at idx as an Array
    ///
    /// \param vm  Target VM
    /// \param idx Index trying to be read
    ///
    /// \remarks
    /// This function MUST have its Error handled if it occurred.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Var(HSQUIRRELVM vm, SQInteger idx) {
        HSQOBJECT obj;
        sq_resetobject(&obj);
        sq_getstackobj(vm,idx,&obj);
        value = Array(obj, vm);
#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQObjectType value_type = sq_gettype(vm, idx);
        if (value_type != OT_ARRAY) {
            SQTHROW(vm, FormatTypeError(vm, idx, _SC("array")));
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat::PushVar to put an Array reference on the stack
    ///
    /// \param vm    Target VM
    /// \param value Value to push on to the VM's stack
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void push(HSQUIRRELVM vm, const Array& value) {
        HSQOBJECT obj;
        sq_resetobject(&obj);
        obj = value.GetObject();
        sq_pushobject(vm,obj);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Array instances to and from the stack as references (arrays are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<Array&> : Var<Array> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Array>(vm, idx) {}};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to get and push Array instances to and from the stack as references (arrays are always references in Squirrel)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
struct Var<const Array&> : Var<Array> {Var(HSQUIRRELVM vm, SQInteger idx) : Var<Array>(vm, idx) {}};

}

#endif

// <--- back to sqrat.h

#endif

