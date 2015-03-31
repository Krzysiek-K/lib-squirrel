
#ifndef _XSQIO_CPP_DONE
#define _XSQIO_CPP_DONE



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



// internal file frapper
typedef void *XSQ_FILE;
struct XSqFile {
	vector<unsigned char> data;
	int fpos;
	bool eof;
	bool error;

	XSqFile() : fpos(0), eof(false), error(false) {}
};


SQFILE sqstd_fopen(const SQChar *filename ,const SQChar *mode)
{
#ifdef SQUNICODE
	#error Unicode not supported
#endif

	bool md_read = false;
	bool md_write = false;
	bool md_append= false;
	bool md_text = false;
	bool md_plus = false;

	while(*mode)
	{
		if(*mode=='r') md_read = true;
		if(*mode=='w') md_write = true;
		if(*mode=='a') md_append = true;
		if(*mode=='t') md_text = true;
		if(*mode=='+') md_plus = true;
		mode++;
	}

	// only pure read supported (with optional text mode)
	if(md_write || md_append || md_plus || !md_read) return NULL;

	XSqFile *f = new XSqFile();
	if(!xsq_getfile(filename,f->data))
	{
		delete f;
		return NULL;
	}

	// text mode read - remove all '\r'
	if(md_text)
	{
		int d = 0;
		for(int i=0;i<(int)f->data.size();i++)
			if(f->data[i]!='\r')
				f->data[d++] = f->data[i];
		f->data.resize(d);
	}

	return (SQFILE*)f;
}

SQInteger sqstd_fread(void* buffer, SQInteger size, SQInteger count, SQFILE fp)
{
	if(!fp) return 0;
	XSqFile *f = (XSqFile*)fp;

	int len = f->data.size() - f->fpos;
	if( len >= size*count )
		len = size*count;
	else
		f->eof = true;

	if(len>0)
	{
		memcpy(buffer,&f->data[f->fpos],len);
		f->fpos += len;
	}

	return len / size;
}

SQInteger sqstd_fwrite(const SQUserPointer buffer, SQInteger size, SQInteger count, SQFILE fp)
{
	return 0;	// TBD: unsupported
}

SQInteger sqstd_fseek(SQFILE fp, SQInteger offset, SQInteger origin)
{
	if(!fp) return 1;
	XSqFile *f = (XSqFile*)fp;
	long int newpos = -1;
	if(origin==SQ_SEEK_SET) newpos = offset;
	if(origin==SQ_SEEK_CUR) newpos = f->fpos + offset;
	if(origin==SQ_SEEK_END) newpos = f->data.size() + offset;
	if(newpos<0 || newpos>(int)f->data.size())
		return 1;
	f->fpos = newpos;
	f->eof = false;
	// ungetc character should be dropped, but none suported
	return 0;
}

SQInteger sqstd_ftell(SQFILE fp)
{
	if(!fp) return -1L;
	return ((XSqFile*)fp)->fpos;
}

SQInteger sqstd_fflush(SQFILE fp)
{
	return 0;	// TBD
}

SQInteger sqstd_fclose(SQFILE fp)
{
	if(!fp) return EOF;
	delete (XSqFile*)fp;
	return 0;
}

SQInteger sqstd_feof(SQFILE fp)
{
	if(!fp) return 0;
	return ((XSqFile*)fp)->eof ? 1 : 0;
}




#endif
