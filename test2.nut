



function tabclass( name, parent, defs )
{
	local root = getroottable();
	local _name = "_"+name;
	if(!root.rawin(_name)) root[_name] <- {}
	root[_name].setdelegate(parent);

	defs.setdelegate( root[_name] );

	root[name] <- function() {
		return clone defs;
	};
}



tabclass( "Foo", null, {
	a = "Hello",
	b = "World",
	x = 10
} );

function _Foo::bar()
{
	print("A! "+x+"\n");
	x++
}

function _Foo::foo()
{
	print("My value of 'a' is "+a+"\n");
}



local a = Foo();

a.x = 30;
a.bar();

	

local b = Foo();

function _Foo::bar()
{
	print("B! "+x+"\n");
	x++
}



a.bar();
b.bar();
b.bar();

a.y <- 5;


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



function mkobj()
{
	return Foo();
}

function test2(a,b)
{
	print("A = "+a+"\n");
	print("B = "+b+"\n");
}

function printobj(o)
{
	foreach(k,v in o)
		print(k+"="+v+" ");
	print("\n");
}

function printobj2(o)
{
	foreach(k,v in o)
		print("'"+k+"' = "+v+"\n");
}


print("---- Test 2 ----\n");
otest( {x=4,y=5} );
obj <- otest2();
printobj(obj);
print("text = " + getstr2() +"\n");

print("\n")
print("\n")
print("---- Test 4/5 ----\n");
otest4( { name="Boxer", x=-1, y=-2, w=-3, h=-4 } );
print("\n")
printobj2( otest5() );
printobj2( otest3( { name="Boxer2", x=-11, y=-12, w=-13, h=-14 } ) );
print("\n")
print("\n")

print( vec2(1,2)+vec2(3,4)+"\n")
print("\n")
