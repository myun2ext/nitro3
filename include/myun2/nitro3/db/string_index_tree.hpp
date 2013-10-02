#ifndef __github_com_myun2__nitro__db__string_index_tree_HPP__
#define __github_com_myun2__nitro__db__string_index_tree_HPP__

#include "myun2/nitro3/db/string_to_hash.hpp"
#include "myun2/nitro3/db/page.hpp"

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, typename _Value, unsigned int _PageBits=8>
			class string_index_tree
			{
			public:
				typedef unsigned int index_t;
			private:
				page *root_page;
				_Impl _impl;
				
				void open() {
					root_page = new root_page(_impl);
				}
			public:
				string_index_tree(const char* filename) : _impl(filename) { open(); }

				///////////////////////

				index_t add(const char* key, const &_Value v) { return add(key, strlen(key), v); }
				index_t add(const void* key, unsigned int key_length, const &_Value v) {
					return _impl.write(p, length);
				}

				template <typename T>
				id_t update(id_t i, const T& v) {
					seek_to(i);
					fwrite(&v, sizeof(v), 1, fp);
					return i;
				}

				///////////////////////

				::std::string read_str(id_t i) {
					seek_to(i);
					length_t length;
					fread(&length, sizeof(length_t), 1, fp);
					::std::string s(length, 0);
					fread((char*)s.data(), length, 1, fp);
					return s;
				}

				template <typename T>
				T read(id_t i) {
					seek_to(i);
					T v;
					fread(&v, sizeof(T), 1, fp);
					return v;
				}

				//template <typename T> ::std::vector<T> read_vector(id_t i) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_index_tree_HPP__
