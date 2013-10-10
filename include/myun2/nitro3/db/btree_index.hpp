#ifndef __github_com_myun2__nitro__db__btree_index_HPP__
#define __github_com_myun2__nitro__db__btree_index_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _KeyType=unsigned int, unsigned int _PageEntries=256>
			class btree_index
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef _KeyType key_t;
			private:
				_Impl& file;
				struct page
				{
					typedef typename _Impl::index_t entry_t;
					typedef size_t index_t;
					static const unsigned int max = _PageEntries;
					static const unsigned int entry_max = _PageEntries;
					static const index_t null_idx = 0;

					entry_t entries[entry_max];

					entry_t& at(const index_t& i) { return entries[i]; }
					const entry_t& at(const index_t& i) const { return entries[i]; }

					entry_t& find_first() {}
					entry_t& find_first_empty() {
						for(size_t i=0; i<max; i++) {
							if ( at(i) == null_idx )
								return at(i);
						}
					}
				};
				void init_page(page& p) {
					memset(&p, 0, sizeof(page));
				}
				template <typename T>
				void add(page& p, const T& v) {
					
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
