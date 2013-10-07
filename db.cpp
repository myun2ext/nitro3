#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/string_index_file.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;

int main()
{
	int hash = string_to_hash("abc");
	printf("%d\n", hash);

	return 0;
}
