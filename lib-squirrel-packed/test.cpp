
#include <base.h>

#define XSQ_VEC2	base::vec2
#define XSQ_VEC3	base::vec3
#include "sqbind.h"

#include "sqrat.h"


using namespace std;
using namespace base;
using namespace Sqrat;



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




XSQ_STRUCT(box_t,"box",
	std::string name;
	int x;
	int y;
	int w;
	int h;
);


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


void myFunc() { printf("MyFunc\n"); }

class MyClass {
public:
	MyClass() { printf("+MyClass\n"); }
	~MyClass() { printf("-MyClass\n"); }
	void Foo() { printf("Foo: bar = %d\n",bar); }
	int bar;
};

void BindRat()
{
	Table myTable(vm());
	myTable.Func("MyFunc", &myFunc);

	Class<MyClass> myClass(vm(),"MyClass");
	myClass.Func("Foo", &MyClass::Foo);
	myClass.Var("bar", &MyClass::bar);

	RootTable(vm()).Bind("MyTable", myTable);
	RootTable(vm()).Bind("MyClass", myClass);
}


int main(int argc, char **argv)
{
	vm.Init();

	BindRat();
	vm.DoFile("rattest.nut");

/*
    const SQChar *program = "print(\"Hello World, I'm back!\\n\");";
	vm.Set("x",8);
	vm.DoString(program);
	vm.DoFile("../vector.nut");
	vm.DoFile("../test3.nut");
	printf("foo returned %d\n",vm.RunRet<int>("foo",4));
	vm.Run("foo",3.14f);
	vm.Run("foo","Hello!");
	vm.Run("foo",&string("World!"));
	box_t b = { "A box", 10, 11, 20, 22 };
	vm.Run("boxer",b);
	printf("x = %d\n",vm.GetInt("x"));
	b = vm.RunRet<box_t>("make_box","hello",vec2(31,32),vec2(33,34));
	printf("box = '%s' %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);
*/

	printf("\n\n\n");
	system("pause");
    return 0;
}
