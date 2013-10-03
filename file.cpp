#include <stdio.h>
#include "myun2/nitro3/resource/file.hpp"
#include "myun2/nitro3/resource/parted.hpp"

//using myun2::nitro3::resource::file;
using myun2::nitro3::file;
using myun2::nitro3::resource::parted;

int main()
{
	parted<file> f(1,3, "test.dat");
	f.write("aaaa");
	f.write("bbbb");
	printf("%s\n", f.read_str(2, 8).c_str());

	return 0;
}
