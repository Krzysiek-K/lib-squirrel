
function printobj(o)
{
	print("object '"+o+"'\n")
	foreach(k,v in o)
		print("\t'"+k+"' = "+v+"\n");
}

function make_box(name,bmin,size)
{
	return { name=name, x=bmin.x, y=bmin.y, w=size.x, h=size.y };
}


box1 <- { name="foo", x=10, y=11, w=12, h=13 }
box2 <- { name="bar", x=14, y=15, w=16, h=17 }
box3 <- { name="moo", x=18, y=19, w=20, h=21 }


print("\n")
print("\n")

print( bigtest3( vec3(1,2,3), vec3(4,5,6), vec3(7,8,9) ) )
print("\n")

bar3( 11, 12, 13 );

//print("\n")
//print("\n")
//
//print( bigtest2( vec2(1,2), vec2(3,4), vec2(5,6) ) )
//
//print("\n")
//print("\n")
//
//printobj( bigtestb( box1, box2, box3 ) )
//
//print("\n")
//print("\n")
//
//
//vv <- vec3(10,20,30)
