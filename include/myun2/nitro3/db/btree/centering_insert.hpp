#ifndef __github_com_myun2__nitro__db__btree__centering_insert_HPP__
#define __github_com_myun2__nitro__db__btree__centering_insert_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			namespace btree_
			{
				class centering_insert
				{
				public:
					struct header
					{
						unsigned int entry_start;
						unsigned int entry_end;
					};

					struct entry
					{
						key_t key;
						value_t value;
					};
				};
			}
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree__centering_insert_HPP__
