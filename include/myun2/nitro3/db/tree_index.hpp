#ifndef __github_com_myun2__nitro__db__tree_index_HPP__
#define __github_com_myun2__nitro__db__tree_index_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl>
			class tree_index
			{
			private:
				_Impl _impl;
			public:
				tree_index(const char* filename) : _impl(filename) {}

				///////////////////////

				id_t write(const char* s) { return write(s, strlen(s)); }
				id_t write(const void* p, length_t length) {
					index_t i = _body.write(p, length);
					return _body.write(p, length);
				}

				template <typename T>
				id_t write(const T& v) {
					id_t i = seek_to_tail();
					fwrite(&v, sizeof(v), 1, fp);
					return i;
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

#endif//__github_com_myun2__nitro__db__tree_index_HPP__
