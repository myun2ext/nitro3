#include <stdio.h>
#include "myun2/nitro3/resource/file.hpp"

//using myun2::nitro3::resource::file;
using myun2::nitro3::file;

int main()
{
	file f("test.dat");
	f.write("aaaa");
	f.write("bbbb");

	return 0;
}
