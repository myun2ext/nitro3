#ifndef __github_com_myun2__nitro__db__btree_index_HPP__
#define __github_com_myun2__nitro__db__btree_index_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, unsigned int _PageEntries>
			class btree_index
			{
			public:
			private:
				_Impl& file;
				struct page
				{
				};
			public:
				btree_index(_Impl& _file) : file(_file) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree_index_HPP__
