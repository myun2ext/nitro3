#include <stdio.h>
#include "myun2/nitro3/pool/pool.hpp"

using myun2::nitro3::pool::file_pool;

typedef unsigned long lt;

int main()
{
	file_pool p("a.db");
	lt i = p.write("abc");
	printf("[%d] %s\n", i, p.read_str(i).c_str());

	p.update(0, "jdk");
	printf("[%d] %s\n", 0, p.read_str(0).c_str());

	return 0;
}
