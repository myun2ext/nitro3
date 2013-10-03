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
			size_t seek_to_tail(){ fseek(fp, 0, SEEK_END); return ftell(fp); }
			void seek_to(size_t pos){ fseek(fp, pos, SEEK_SET); }
		public:
			file(const char* filename) { open(filename); }
			bool open(const char* filename) {
				if ( _access(filename, F_OK) == 0 )
					fp = fopen(filename, "r+b");
				else
					fp = fopen(filename, "w+b");
				if ( fp == NULL )
					throw file_open_failed();
			}

			///////////////////////

			size_t write(const char* s) { return write(s, strlen(s)); }
			size_t write(const void* p, size_t length) {
				seek_to(i);
				fwrite(p, length, 1, fp);
				return i;
			}

			template <typename T>
			size_t write(const T& v) {
				seek_to(i);
				fwrite(&v, sizeof(v), 1, fp);
				return i;
			}

			///////////////////////

			::std::string read_str(size_t i, size_t length) {
				seek_to(i);
				::std::string s(length, 0);
				fread((char*)s.data(), length, 1, fp);
				return s;
			}

			size_t read(size_t i, void* buf, size_t length) {
				seek_to(i);
				fread(buf, length, 1, fp);
				return s;
			}

			template <typename T>
			T read(size_t i) {
				seek_to(i);
				T v;
				fread(&v, sizeof(T), 1, fp);
				return v;
			}
		};
	}
}

#endif//__github_com_myun2__nitro__resource__file_HPP__
