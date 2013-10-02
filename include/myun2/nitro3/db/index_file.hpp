#ifndef __github_com_myun2__nitro__db__index_file_HPP__
#define __github_com_myun2__nitro__db__index_file_HPP__

#include "myun2/nitro3/pool/pool_file.hpp"

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _FileImpl>
			class index_file
			{
			private:
				_FileImpl _impl;
			public:
				index_file(const char* filename) : _impl(filename) {}

				///////////////////////

				index_t write(const char* s) { return write(s, strlen(s)); }
				index_t write(const void* p, length_t length) {
					index_t i = seek_to_tail();
					fwrite(&length, sizeof(length_t), 1, fp);
					fwrite(p, length, 1, fp);
					return i;
				}

				template <typename T>
				index_t write(const T& v) {
					index_t i = seek_to_tail();
					fwrite(&v, sizeof(v), 1, fp);
					return i;
				}

				///////////////////////

				/*  safe...?  */
				index_t update(index_t i, const char* s) { return update(i, s, strlen(s)); }
				index_t update(index_t i, const void* p, length_t update_length) {
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
				index_t update(index_t i, const T& v) {
					seek_to(i);
					fwrite(&v, sizeof(v), 1, fp);
					return i;
				}

				///////////////////////

				::std::string read_str(index_t i) {
					seek_to(i);
					length_t length;
					fread(&length, sizeof(length_t), 1, fp);
					::std::string s(length, 0);
					fread((char*)s.data(), length, 1, fp);
					return s;
				}

				template <typename T>
				T read(index_t i) {
					seek_to(i);
					T v;
					fread(&v, sizeof(T), 1, fp);
					return v;
				}

				//template <typename T> ::std::vector<T> read_vector(index_t i) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__index_file_HPP__
