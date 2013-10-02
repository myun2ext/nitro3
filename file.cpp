#include <stdio.h>
#include "myun2/nitro3/pool/pool.hpp"

using myun2::nitro3::pool::file_pool;

typedef unsigned long lt;

int main()
{
	file_pool p("a.db");
	lt i = p.write("aaa");
	printf("[%d] %s\n", i, p.read_str(i).c_str());

	return 0;
}
