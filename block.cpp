#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/blocked_pool.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;

int main()
{
	file_pool f = file_pool("pool.dat");
	blocked_pool<file_pool> b(f);

	//int a = pool.add("aaa");
	//printf("%s\n", pool.read_s(a).c_str());

	return 0;
}
