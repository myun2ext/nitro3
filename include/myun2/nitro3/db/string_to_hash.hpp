#ifndef __github_com_myun2__nitro__db__string_to_hash_HPP__
#define __github_com_myun2__nitro__db__string_to_hash_HPP__

#include <string.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{

			template <typename _ResultT>
			_ResultT string_to_hash(const void* s, unsigned int length)
			{
				const unsigned char* p = (const unsigned char*)s;
				const unsigned char* tail = p + length;
				_ResultT r = 0;

				for(; p != s; p++) {
					r += *p;
				}
				return r;
			}

			unsigned int string_to_hash(const void* s, unsigned int length) {
				return string_to_hash<unsigned int> (s, length);
			}

			unsigned int string_to_hash(const char* s) {
				return string_to_hash(s, strlen(s));
			}
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_to_hash_HPP__
