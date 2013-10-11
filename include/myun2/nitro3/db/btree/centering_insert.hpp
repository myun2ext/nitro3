#ifndef __github_com_myun2__nitro__db__btree__centering_insert_HPP__
#define __github_com_myun2__nitro__db__btree__centering_insert_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			namespace btree_alg
			{
				template <typename _KeyType=unsigned int, typename _ValueType=unsigned int>
				class centering_insert
				{
				public:
					typedef _KeyType key_t;
					typedef _ValueType value_t;

					struct header
					{
						unsigned int entry_start;
						unsigned int entry_end;
					};

					struct entry
					{
						key_t key;
						value_t value;
					};

				private:
					template <typename _Page>
					struct page_virtual {
						static const unsigned int entry_max = _Page::entry_max;

						_Page& page;
						header& head;
						entry& entries[];
					};

					template <typename _Page>
					void check_and_initial_page(_Page& p) {
						header& head = p.head;
						if ( head.entry_start == 0 )
						{
							head.entry_start = _Page::entry_max / 2;
							head.entry_end = _Page::entry_max / 2;
						}
					}
				public:
					template <typename _Page>
					entry& add(_Page& p, const value_t& v) {
						entry& e = find_first_empty();
						e.value = v;
						return e;
					}
				};
			}
		}
	}
}

#endif//__github_com_myun2__nitro__db__btree__centering_insert_HPP__
