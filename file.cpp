#include <stdio.h>
#include "myun2/nitro3/resource/file.hpp"
#include "myun2/nitro3/resource/parted.hpp"

//using myun2::nitro3::resource::file;
using myun2::nitro3::file;
using namespace myun2::nitro3::resource;

int main()
{
	try {
		parted<file> f(1,3, "test.dat");
		f.write("aaaa");
		f.write("bbbb");
		printf("%s\n", f.read_str(2, 8).c_str());
	}
	catch(const parted_write_over_limit_exception& e)
	{
		printf("catched parted_write_over_limit_exception [%d + %d > %d]\n", e.pos, e.length, e.end);
	}

	return 0;
}
