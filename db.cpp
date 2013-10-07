#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/string_index_page.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;

int main()
{
	int hash = string_to_hash("a");
	printf("%d\n", hash);
	hash = string_to_hash("aabc");
	printf("%d\n", hash);
	hash = string_to_hash("334");
	printf("%d\n", hash);
	hash = string_to_hash("test.example.aabd");
	printf("%08X\n", hash);

	return 0;
}
