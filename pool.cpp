#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/string_pool.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;

int main()
{
	file_pool f = file_pool("pool.dat");
	string_pool<file_pool> h(f);

	return 0;
}
