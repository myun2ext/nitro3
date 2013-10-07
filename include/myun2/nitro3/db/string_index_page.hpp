#ifndef __github_com_myun2__nitro__db__string_index_page_HPP__
#define __github_com_myun2__nitro__db__string_index_page_HPP__

#include "myun2/nitro3/db/string_to_hash.hpp"

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, unsigned int _PageSize=16>
			class string_index_page
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef unsigned int hash_t;
			private:
				_Impl& file;

				unsigned int pages[_PageSize];
				void read_page() {
					pages = file.read<unsigned int [_PageSize]>(0);
				}
			public:
				string_index_page(_Impl& _file) : file(_file) {}

				///////////////////////

				hash_t key_to_index(const char* s){ return string_to_index(s); }

				index_t add(const char* key) {
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_index_page_HPP__
