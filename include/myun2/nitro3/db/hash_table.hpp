#ifndef __github_com_myun2__nitro__db__hash_table_HPP__
#define __github_com_myun2__nitro__db__hash_table_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _HashKey, typename _HashValue, unsigned int _HashTableLength=256>
			class hash_table
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef _HashKey key_t;
				typedef _HashValue value_t;
			private:
				_Impl& file;

				struct entry
				{
					key_t key;
					value_t v;
				};
				entry entries[_HashTableLength];

				void read_page() {
					file._read(0, page, sizeof(page));
				}
				void write_page() {
					file._write(0, page, sizeof(page));
				}
				index_t to_hash(const char* s) {
					return string_to_hash(s) % _PageLength;
				}
			public:
				string_index_page(_Impl& _file) : file(_file) {
					read_page();
				}

				index_t add(const char* key) {
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__hash_table_HPP__
