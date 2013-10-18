#ifndef __github_com_myun2__nitro__db__simple__simple_db_HPP__
#define __github_com_myun2__nitro__db__simple__simple_db_HPP__

#include "myun2/nitro3/pool/file_pool.hpp"

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl = myun2::nitro3::pool::file_pool>
			class simple_db_
			{
			};
			typedef simple_db_<> simple_db;
		}
	}
}

#endif//__github_com_myun2__nitro__db__simple__simple_db_HPP__
