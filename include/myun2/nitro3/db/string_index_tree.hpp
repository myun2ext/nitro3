#ifndef __github_com_myun2__nitro__db__string_index_tree_HPP__
#define __github_com_myun2__nitro__db__string_index_tree_HPP__

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
				_Impl _impl;
			public:
				string_index_tree(const char* filename) : _impl(filename) {}

				///////////////////////

				index_t add(const char* key, const &_Value v) { return add(key, strlen(key)); }
				index_t add(const void* key, unsigned int key_length, const &_Value v) {
					return _impl.write(p, length);
				}

				///////////////////////

				/*  safe...?  */
				id_t update(id_t i, const char* s) { return update(i, s, strlen(s)); }
				id_t update(id_t i, const void* p, length_t update_length) {
					seek_to(i);
					length_t length;
					fread(&length, sizeof(length_t), 1, fp);
					if ( update_length == length ) {
						fwrite(p, length, 1, fp);
						return i;
					}
					else
						throw file_pool_update_length_unmatched();
						//return -1;
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
