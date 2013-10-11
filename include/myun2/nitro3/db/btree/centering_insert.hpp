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
					typedef unsigned int entry_index_t, entry_idx_t;
					static const entry_index_t null_entry_index = 0;

					template <typename _Page>
					struct page_virtual {
						static const entry_index_t entry_max = _Page::entry_max;

						_Page& page;
						header& head;
						entry& entries[];
					};

					entry_index_t center_index() const { _Page::entry_max / 2; }
					template <typename _Page>
					entry& center(_Page& p) { return p.at(center_index()); }

					template <typename _Page>
					bool first_append(_Page& p, const value_t& v) {
						header& head = p.head;
						if ( head.entry_start == null_entry_index )
						{
							head.entry_start = center_index();
							head.entry_end = head.entry_start;
							p.at(head.entry_start) = v;
							return true;
						}
						return false;
					}
				public:
					template <typename _Page>
					//entry& add(_Page& p, const value_t& v) {
					entry& add(_Page& p, const key_t& key, const value_t& v) {
						if first_append(p, v) return center(p);

						entry& pv = center(p);
						if ( pv.key = key )
							throw duplicate_key_exception(pv);

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
