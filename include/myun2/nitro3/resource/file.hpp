#ifndef __github_com_myun2__nitro__resource__file_HPP__
#define __github_com_myun2__nitro__resource__file_HPP__

#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h> // use strlen()
#include <string>
#include <vector>

namespace myun2
{
	namespace nitro3
	{
		struct file_open_failed {};

		class file
		{
		private:
			FILE* fp;
		public:
			file() : fp(NULL) {}
			file(const char* filename) { open(filename); }
			bool open(const char* filename) {
				if ( _access(filename, F_OK) == 0 ){
					fp = fopen(filename, "r+b");
					seek_to_tail();
				}
				else
					fp = fopen(filename, "w+b");
				if ( fp == NULL )
					throw file_open_failed();
			}

			size_t seek_to_tail(){ fseek(fp, 0, SEEK_END); return ftell(fp); }
			void seek_to(long pos){ fseek(fp, pos, SEEK_SET); }

			///////////////////////

			size_t write(const char* s) { return write(s, strlen(s)); }
			size_t write(const void* p, size_t length) {
				return fwrite(p, length, 1, fp);
			}

			template <typename T>
			size_t write(const T& v) {
				return fwrite(&v, sizeof(v), 1, fp);
			}

			////

			size_t write(long i, const char* s) { return write(i, s, strlen(s)); }
			size_t write(long i, const void* p, size_t length) {
				seek_to(i);
				return write(p, length);
			}

			template <typename T>
			size_t write(long i, const T& v) {
				seek_to(i);
				return write(v);
			}

			///////////////////////

			::std::string read_str(long i, size_t length) {
				seek_to(i);
				::std::string s(length, 0);
				fread((char*)s.data(), length, 1, fp);
				return s;
			}

			size_t read(long i, void* buf, size_t length) {
				seek_to(i);
				return fread(buf, length, 1, fp);
			}

			template <typename T>
			T read(long i) {
				seek_to(i);
				T v;
				fread(&v, sizeof(T), 1, fp);
				return v;
			}
		};
	}
}

#endif//__github_com_myun2__nitro__resource__file_HPP__
