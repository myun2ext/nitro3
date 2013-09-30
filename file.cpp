#include <stdio.h>
#include "myun2/nitro3/resource/handle.hpp"

using namespace myun2::nitro3::resource;

struct closer{ closer(FILE* fp) { fclose(fp); } };
//struct closer{ void operator()(FILE* fp) const { fclose(fp); } };

int main()
{
	handle<FILE*, closer> h;

	return 0;
}
