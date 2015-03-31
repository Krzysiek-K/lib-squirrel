
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include "xsqbind.h"

#include <base.h>

using namespace std;
using namespace base;



void xsq_print( const char *msg )
{
	printf("%s",msg);
}

void xsq_error( const char *err )
{
	printf("ERROR: %s",err);
}

bool xsq_getfile( const char *path, std::vector<unsigned char> &data )
{
	return NFS.GetFileBytes(path,data);
}

unsigned long long xsq_getfiletime( const char *path )
{
	return GetFileTime(path);
}



SqVM vm;

void bar(int test)
{
	printf("Bar is %d\n",test);
}
XSQ_REGISTER_FN(bar);


void otest(SqRef o)
{
	printf("otest = (%d,%d)\n",o.GetInt("x"),o.GetInt("y"));
}
XSQ_REGISTER_FN(otest);

SqRef otest2()
{
	SqRef r = vm.NewObject();
	r.Set("x",13);
	r.Set("y",21);
	return r;
}
XSQ_REGISTER_FN(otest2);



XSQ_STRUCT(box_t,"box",
	string name;
	int x;
	int y;
	int w;
	int h;
);

//box_t otest3(box_t box)
//{
//	swap(box.x,box.y);
//	box.name = "Swapped";
//	return box;
//}
//XSQ_REGISTER_FN(otest3);


string getstr2()
{
	return "foo";
}
XSQ_REGISTER_FN(getstr2);


 
int main(int argc, char **argv)
{
	vm.Init();

    const SQChar *program = "::print(\"Hello World, I'm back!\\n\");";
	vm.Set("x",8);
//	vm.DoString(program);
	printf("%3d: %s\n", __LINE__, vm.DoFile("test2.nut") ? "OK" : "Err" );
	printf("foo returned %d\n",vm.RunRet<int>("foo",4));
	printf("%3d: %s\n", __LINE__, vm.Run("foo",3.14f) ? "OK" : "Err" );
	printf("%3d: %s\n", __LINE__, vm.Run("foo","Hello!") ? "OK" : "Err" );
	printf("%3d: %s\n", __LINE__, vm.Run("foo",&string("World!")) ? "OK" : "Err" );
	box_t b = { "A box", 10, 11, 20, 22 };
	vm.Run("boxer",b);
	printf("x = %d\n",vm.GetInt("x"));
	b = vm.RunRet<box_t>("make_box");
	printf("box = '%s' %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);


	SqRef o = vm.RunRet<SqRef>("mkobj");
	SqRef p = vm.RunRet<SqRef>("mkobj");

	printf("Object has:\n");
	printf(" a = %s\n",o.GetString("a").c_str());
	printf(" b = %s\n",o.GetString("b").c_str());

	printf("---\n");
	o.Run("foo");
	o.Run("bar");
	o.Run("bar");
	o.Run("bar");
	p.Run("bar");
	p.Run("bar");
	p.Run("bar");
	p.Run("bar");
	printf("---\n");

	o = vm.ToObject("Hello!");
	p = vm.ToObject(21);
	vm.Run("test2",o,p);

	printf("\n\n\n");
	system("pause");
    return 0;
}
