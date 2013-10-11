#include <stdio.h>
#include "myun2/nitro3/pool/file_pool.hpp"
#include "myun2/nitro3/db/btree_index.hpp"
#include "myun2/nitro3/db/btree/centering_insert.hpp"

using myun2::nitro3::pool::file_pool;
using namespace myun2::nitro3::db;
using namespace myun2::nitro3::db::btree_alg;

int main()
{
	file_pool file = file_pool("btree.idx");
	btree_index<file_pool, centering_insert<> > btree(file);

	//printf("%d\n", btree.find_first_empty() );

	return 0;
}
