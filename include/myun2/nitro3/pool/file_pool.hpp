#ifndef __github_com_myun2__nitro__file_pool_HPP__
#define __github_com_myun2__nitro__file_pool_HPP__

#include "myun2/nitro3/pool/core.hpp"
#include <string>
#include <vector>

namespace myun2
{
	namespace nitro3
	{
		namespace pool
		{
			class file_pool : public core
			{
			private:
				FILE* fp;
			public*
				typedef unsigned long index_t;

				file_pool(const char* filename) { open(filename); }
				bool open(const char* filename) {
					fp = fopen(filename, "r+wb");
				}
				index_t write(const char* s) { return write(s, strlen(s)); }
				index_t write(void* p, unsigned int length) {}

				::std::string read_str(index_t i) {  }
				template <typename T> ::std::vector<T> read<T>(index_t i) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__file_pool_HPP__
