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
				static const size_t head = sizeof(_IndexType);
				static const _KeyType null_key = 0;
				static const size_t null_idx = 0;

				_Impl& file;
				struct Entry
				{
					index_t i;
					index_t prev, next;
					key_t key;

					//Entry() : i(null_idx), key(null_key), prev(null_idx), next(null_idx) {}
					Entry(){}
					Entry(index_t i_, key_t key_) : i(i_), key(key_), prev(null_idx), next(null_idx) {}

					bool is_none() const { return i == null_idx; }
					bool is_key_none() const { return key == null_key; }
				};

				Entry page[_PageSize];
				void read_page() {
					memset(page, 0, sizeof(page));
					file._read(0, page, sizeof(page));
				}
				void write_page() {
					file._write(0, page, sizeof(page));
				}

				const Entry& read(pos_t pos) const { return page[pos]; }
				Entry& read(pos_t pos) { return page[pos]; }
				void write(pos_t pos, const Entry &entry) { page[pos] = entry; }
public:
				//index_t find_entry(pos_t pos, const _KeyType &key) {
				const Entry& find_entry(const _KeyType &key, pos_t pos=head) {
					Entry& e = read(pos);
					if ( e.i == null_idx )
						return e;
					if ( e.key == key )
						return e;
					if ( key < e.key )
						return find_entry(key, e.prev);
					else
						return find_entry(key, e.next);
				}
			public:
				binary_page(_Impl& _file) : file(_file) {
					read_page();
				}

				index_t find(const _KeyType &key) {
					return find_entry(key).i;
				}

				index_t append(const _KeyType &key) {
					Entry& e = find_entry(key);
					if ( e.is_none() ) {
						e.key = key;
						save();
						
					}
					//file.write(key_to_index(key));
				}

				void save() { write_page(); }
				void flush() { write_page(); }
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__binary_page_HPP__
