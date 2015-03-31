
#include "sqbind.h"
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




XSQ_STRUCT(box_t,"box",
	string name;
	int x;
	int y;
	int w;
	int h;
);


 
int main(int argc, char **argv)
{
	vm.Init();

    const SQChar *program = "::print(\"Hello World, I'm back!\\n\");";
	vm.Set("x",8);
	vm.DoString(program);
	vm.DoFile("../test1.nut");
	printf("foo returned %d\n",vm.RunRet<int>("foo",4));
	vm.Run("foo",3.14f);
	vm.Run("foo","Hello!");
	vm.Run("foo",&string("World!"));
	box_t b = { "A box", 10, 11, 20, 22 };
	vm.Run("boxer",b);
	printf("x = %d\n",vm.GetInt("x"));
	b = vm.RunRet<box_t>("make_box");
	printf("box = '%s' %d %d %d %d\n",b.name.c_str(),b.x,b.y,b.w,b.h);


	printf("\n\n\n");
	system("pause");
    return 0;
}
