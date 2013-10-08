#ifndef __github_com_myun2__nitro__db__string_index_page_HPP__
#define __github_com_myun2__nitro__db__string_index_page_HPP__

#include "myun2/nitro3/db/string_to_hash.hpp"
#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, unsigned int _PageLength=256, unsigned int _KeyEntries=4>
			class string_index_page
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef unsigned int hash_t;
			private:
				_Impl& file;

				hash_t page[_PageLength * _KeyEntries];
				void read_page() {
					file._read(0, page, sizeof(page));
				}
				void write_page() {
					file._write(0, page, sizeof(page));
				}

				void init_on_mem_page()
				{
					memset(page, 0, sizeof(page));
				}
			public:
				string_index_page(_Impl& _file) : file(_file) {
					init_on_mem_page();
				}

				///////////////////////

				hash_t key_to_index(const char* s){ return string_to_hash(s) % _PageLength; }

				index_t add(const char* key) {
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_index_page_HPP__
