#ifndef __github_com_myun2__nitro__file_pool_HPP__
#define __github_com_myun2__nitro__file_pool_HPP__

#include "myun2/nitro3/pool/core.hpp"

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
				file_pool(const char* filename) { open(filename); }
				bool open(const char* filename) {
					fp = fopen(filename, "r+wb");
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__file_pool_HPP__
