#ifndef __github_com_myun2__nitro__db__hash_table_HPP__
#define __github_com_myun2__nitro__db__hash_table_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _HashKey=unsigned int, typename _HashValue=unsigned int, unsigned int _HashTableLength=2048>
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
				size_t chop(const key_t& hash) const {
					return hash % _HashTableLength;
				}
				entry& at(size_t i) {
					return entries[i];
				}
			public:
				hash_table(_Impl& _file) : file(_file) { reload(); }

				entry& operator[] (const key_t& hash) {
					size_t chopped = chop(hash);
					return at(chopped);
				}

				void reload() {
					file._read(0, entries, sizeof(entries));
				}
				void flush() {
					file._write(0, entries, sizeof(entries));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__hash_table_HPP__
