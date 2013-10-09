#ifndef __github_com_myun2__nitro__db__binary_page_HPP__
#define __github_com_myun2__nitro__db__binary_page_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, unsigned int _PageSize=256, typename _KeyType=unsigned int, typename _IndexType=unsigned char>
			class binary_page
			{
			public:
				//typedef typename _Impl::index_t index_t;
				typedef size_t pos_t;
				typedef _IndexType index_t;
				typedef _KeyType key_t;
			private:
				static const size_t head = 0;
				static const size_t null_pos = 0;

				_Impl& file;
				struct Entry
				{
					index_t i;
					key_t key;
					index_t prev, next;

					Entry(index_t i_, key_t key_) : i(i_), key(key_), prev(null_pos), next(null_pos) {}
				};

				Entry page[_PageSize];
				void read_page() {
					memset(page, 0, sizeof(page));
					file._read(0, page, sizeof(page));
				}
				void write_page() {
					file._write(0, page, sizeof(page));
				}

				Entry read(pos_t pos) { return page[pos]; }
				void write(pos_t pos, const Entry &Entry) {page[pos] = entry; }
				void flush() { write_page() }

				index_t find_entry(pos_t pos, const _KeyType &key) {
					Entry e = read(pos);
					if ( e.key == key )
						return pos;
					if ( key < e.key )
						return find_entry(e.prev, key);
					else
						return find_entry(e.next, key);
				}
			public:
				binary_page(_Impl& _file) : file(_file) {
					read_page();
				}

				index_t find(const _KeyType &key) {
					return find_sub(head, key);
				}

				index_t append(const _KeyType &key) {
					//////Entry e(
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__binary_page_HPP__
