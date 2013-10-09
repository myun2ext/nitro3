#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/binary_page.hpp"
#include "myun2/nitro3/db/string_index_page.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;

int main()
{
	file_pool index_file = file_pool("index.db");
	file_pool binary_file = file_pool("binary.db");

	string_index_page<file_pool> index(index_file);
	binary_page<file_pool> binary(binary_file);

	binary.save();

	return 0;
}
