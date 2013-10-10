#ifndef __github_com_myun2__nitro__db__btree_index_HPP__
#define __github_com_myun2__nitro__db__btree_index_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl>
			class btree_index
			{
			public:
				typedef typename _Impl::index_t index_t;
			private:
				_Impl& file;

				index_t page[_PageLength * _KeyEntries];
				void read_page() {
					file._read(0, page, sizeof(page));
				}
				void write_page() {
					file._write(0, page, sizeof(page));
				}
				index_t key_to_index(const char* s) {
					return string_to_hash(s) % _PageLength;
				}
			public:
				btree_index(_Impl& _file) : file(_file) {
					read_page();
				}

				index_t add(const char* key) {
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree_index_HPP__
