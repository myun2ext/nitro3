#ifndef __github_com_myun2__nitro__db__btree_index_HPP__
#define __github_com_myun2__nitro__db__btree_index_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _ValueType=unsigned int, typename _KeyType=unsigned int, unsigned int _PageEntries=256>
			class btree_index
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef _ValueType value_t;
				typedef _KeyType key_t;
			private:
				_Impl& file;
				struct page
				{
					//typedef typename _Impl::index_t entry;
					struct Entry
					{
						key_t key;
						value_t value;
					};
					//typedef typename _Impl::index_t Entry;
					typedef size_t index_t;
					static const unsigned int max = _PageEntries;
					static const unsigned int entry_max = _PageEntries;
					static const index_t null_idx = 0;

					Entry entries[entry_max];

					Entry& at(const index_t& i) { return entries[i]; }
					const Entry& at(const index_t& i) const { return entries[i]; }

					Entry& find_first() {}
					Entry& find_first_empty() {
						for(size_t i=0; i<max; i++) {
							if ( at(i) == null_idx )
								return at(i);
						}
					}

					Entry& add(page& p, const value_t& v) {
						Entry& e = find_first_empty();
						e.value = v;
						return e;
					}
				};
				static const size_t page_size = sizeof(page);

				void init_page(page& p) {
					memset(&p, 0, sizeof(page));
				}
				template <typename T>
				void add(page& p, const T& v) {
					
				}

				size_t page_pos(unsigned int page_num) const { return page_num * page_size; }
				page& read_page(page& p, unsigned int page_num) {
					file._read(page_pos(page_num), &p, sizeof(page));
					return p;
				}
				void write_page() {
					file._write(page_pos(page_num), &p, sizeof(page));
					return p;
				}

			public:
				btree_index(_Impl& _file) : file(_file) {}

				void append(const key_t& k) {
					
				}

				void flush() {}
				void save() {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree_index_HPP__
