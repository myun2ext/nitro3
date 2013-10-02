#ifndef __github_com_myun2__nitro__file_pool_HPP__
#define __github_com_myun2__nitro__file_pool_HPP__

#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include "myun2/nitro3/pool/core.hpp"
#include <string.h> // use strlen()
#include <string>
#include <vector>

namespace myun2
{
	namespace nitro3
	{
		namespace pool
		{
			struct file_pool_exception {};

			class file_pool : public base
			{
			public:
				typedef unsigned long length_t;
				typedef long index_t;
			private:
				FILE* fp;
				index_t seek_to_tail(){ fseek(fp, 0, SEEK_END); return ftell(fp); }
				void seek_to(size_t pos){ fseek(fp, pos, SEEK_SET); }
			public:
				file_pool(const char* filename) { open(filename); }
				bool open(const char* filename) {
					if ( _access(filename, F_OK) == 0 )
						fp = fopen(filename, "r+b");
					else
						fp = fopen(filename, "w+b");
					if ( fp == NULL )
						throw file_pool_exception();
				}

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
				index_t update(index_t i, const char* s) { return write(s, strlen(s)); }
				index_t update(index_t i, const void* p, length_t update_length) {
					seek_to(i);
					fwrite(&length, sizeof(length_t), 1, fp);
					if ( update_length == length ) {
						fwrite(p, length, 1, fp);
						return i;
					}
					else
						return -1;
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

#endif//__github_com_myun2__nitro__file_pool_HPP__
