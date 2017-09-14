
#include <stdio.h>
#include <stdarg.h>
#include <string>

#include <base.h>

#define XSQ_VEC2	base::vec2
#define XSQ_VEC3	base::vec3
#include "xsqbind.h"


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

void bar3(int a,int b,int c)
{
	printf("\nBar3 is %d %d %d\n",a,b,c);
}
XSQ_REGISTER_FN(bar3);


void otest(SqRef o)
{
	printf("otest = (%d,%d)\n",o.GetInt("x"),o.GetInt("y"));
}
XSQ_REGISTER_FN(otest);

SqRef otest2()
{
	SqRef r = vm.NewTable();
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

box_t otest3(box_t box)
{
	swap(box.x,box.y);
	box.name = "Swapped";
	return box;
}
XSQ_REGISTER_FN(otest3);

void otest4(box_t b)
{
	printf("'%s' -> %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);
}
XSQ_REGISTER_FN(otest4);

box_t otest5()
{
	box_t b = { "My box", 51, 52, 53, 54 };
	return b;
}
XSQ_REGISTER_FN(otest5);



string getstr2()
{
	return "foo";
}
XSQ_REGISTER_FN(getstr2);



vec2 vtest2(vec2 v)
{
	printf("vtest2 %.2f %.2f\n",v.x,v.y);
	return v+0.5f;
}
XSQ_REGISTER_FN(vtest2);

vec3 vtest3(vec3 v)
{
	printf("vtest3 %.2f %.2f %.2f\n",v.x,v.y,v.z);
	return v+0.5f;
}
XSQ_REGISTER_FN(vtest3);


vec3 bigtest3(vec3 a,vec3 b,vec3 c)
{
	printf("bigtest 3\n");
	printf("  %.0f %.0f %.0f\n",a.x,a.y,a.z);
	printf("  %.0f %.0f %.0f\n",b.x,b.y,b.z);
	printf("  %.0f %.0f %.0f\n",c.x,c.y,c.z);
	return vec3(10,11,12);
}
XSQ_REGISTER_FN(bigtest3);

vec2 bigtest2(vec2 a,vec2 b,vec2 c)
{
	printf("bigtest 2\n");
	printf("  %.0f %.0f\n",a.x,a.y);
	printf("  %.0f %.0f\n",b.x,b.y);
	printf("  %.0f %.0f\n",c.x,c.y);
	return vec2(7,8);
}
XSQ_REGISTER_FN(bigtest2);

box_t bigtestb(box_t a,box_t b,box_t c)
{
	printf("bigtest box\n");
	printf("  '%s' -> %d %d %d %d\n",a.name.c_str(),a.x,a.y,a.w,a.h);
	printf("  '%s' -> %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);
	printf("  '%s' -> %d %d %d %d\n",c.name.c_str(),c.x,c.y,c.w,c.h);
	box_t box = { "goo", 22, 23, 24, 25 };
	return box;
}
XSQ_REGISTER_FN(bigtestb);

int main(int argc, char **argv)
{
	vm.Init();

    const SQChar *program = "::print(\"Hello World, I'm back!\\n\");";

	printf("%3d: %s\n", __LINE__, vm.DoFile("vector.nut") ? "OK" : "Err" );

	vm.Set("x",8);
	vm.Set("v",vec3(10,11,12));
//	vm.DoString(program);

	printf("%3d: %s\n", __LINE__, vm.DoFile("test3.nut") ? "OK" : "Err" );

	//printf("foo returned %d\n",vm.RunRet<int>("foo",4));
	//printf("%3d: %s\n", __LINE__, vm.Run("foo",3.14f) ? "OK" : "Err" );
	//printf("%3d: %s\n", __LINE__, vm.Run("foo","Hello!") ? "OK" : "Err" );
	//printf("%3d: %s\n", __LINE__, vm.Run("foo",&string("World!")) ? "OK" : "Err" );
	//box_t b = { "A box", 10, 11, 20, 22 };
	//vm.Run("boxer",b);
	//printf("x = %d\n",vm.GetInt("x"));
	//b = vm.RunRet<box_t>("make_box");
	//printf("box = '%s' %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);
	//
	//
	//SqRef o = vm.RunRet<SqRef>("mkobj");
	//SqRef p = vm.RunRet<SqRef>("mkobj");
	//
	//printf("Object has:\n");
	//printf(" a = %s\n",o.GetString("a").c_str());
	//printf(" b = %s\n",o.GetString("b").c_str());
	//
	//printf("---\n");
	//o.Run("foo");
	//o.Run("bar");
	//o.Run("bar");
	//o.Run("bar");
	//p.Run("bar");
	//p.Run("bar");
	//p.Run("bar");
	//p.Run("bar");
	//printf("---\n");
	//
	//o = vm.ToObject("Hello!");
	//p = vm.ToObject(21);
	//vm.Run("test2",o,p);

//	vec3 v = vm.Get<vec3>("vv");
//	printf("%f %f %f\n",v.x,v.y,v.z);

	printf("\n\n\n");
	system("pause");
    return 0;
}
