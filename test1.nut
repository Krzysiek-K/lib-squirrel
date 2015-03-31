
class Foo {
	x = 10
}

Foo.bar <- function()
{
	print("A! "+x+"\n");
	x++
}




local a = Foo();


a.bar();

	

local b = Foo();

a.bar();
b.bar();


function foo(x)
{
	print("Foo is '"+x+"'\n");
	return 13;
}

function boxer(b)
{
	print("Box '"+b.name+"'is "+b.x+" "+b.y+" "+b.w+" "+b.h+"\n");
	return 13;
}

function make_box()
{
	print("Makebox\n");
	return { name="Boxy", x=1, y=2, w=3, h=4 };
}


bar(x);
x <- 5;
