#include <stdio.h>
#include "myun2/nitro3/resource/handle.hpp"

using namespace myun2::nitro3::resource;

void closer(FILE* fp) { fclose(fp); }

int main()
{
	handle<FILE*, closer> h;

	return 0;
}
