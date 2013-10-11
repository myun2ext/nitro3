#ifndef __github_com_myun2__nitro__db__btree_index_HPP__
#define __github_com_myun2__nitro__db__btree_index_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _Algorithm, typename _ValueType=unsigned int, typename _KeyType=unsigned int, unsigned int _PageEntries=1024>
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
					//typedef typename _Algorithm::header header;
					//typedef typename _Algorithm::entry entry;

					struct header
					{
						unsigned int entry_start;
						unsigned int entry_end;
					};

					//typedef typename _Impl::index_t entry;
					struct entry
					{
						key_t key;
						value_t value;
					};
					typedef size_t index_t;
					static const unsigned int max = _PageEntries;
					static const unsigned int entry_max = _PageEntries - (sizeof(header) / sizeof(entry));
					static const index_t null_idx = 0;

					header head;
					entry entries[entry_max];

					entry& at(const index_t& i) { return entries[i]; }
					const entry& at(const index_t& i) const { return entries[i]; }

					entry& find_first() {}
					entry& find_first_empty() {
						for(size_t i=0; i<max; i++) {
							if ( at(i) == null_idx )
								return at(i);
						}
					}
					entry& add(const value_t& v) {
						entry& e = find_first_empty();
						e.value = v;
						return e;
					}
				};
				static const size_t page_size = sizeof(page);

				void init_page(page& p) {
					memset(&p, 0, sizeof(page));
				}
				page create_page() {
					page p;
					init_page(p);
					return p;
				}
				template <typename T>
				void add(page& p, const T& v) {
					
				}

				size_t page_pos(unsigned int page_num) const { return page_num * page_size; }
				page& read_page(page& p, unsigned int page_idx) {
					file._read(page_pos(page_idx), &p, sizeof(page));
					return p;
				}
				page& write_page(page& p, unsigned int page_idx) {
					file._write(page_pos(page_idx), &p, sizeof(page));
					return p;
				}
				bool is_file_none() const { return file.size() == 0; }
				void init() {
					if ( is_file_none() )
						create_first_page();
				}
				void create_first_page() {
					page p = create_page();
					write_page(p, 0);
				}

			public:
				btree_index(_Impl& _file) : file(_file) { init(); }

				void append(const key_t& k) {
					
				}

				void flush() {}
				void save() {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree_index_HPP__
