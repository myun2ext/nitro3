#ifndef __github_com_myun2__nitro__db__string_to_hash_HPP__
#define __github_com_myun2__nitro__db__string_to_hash_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <unsigned int hash_bits, typename _ResultT=unsigned int>
			_ResultT string_to_hash(const void* s, unsigned int length)
			{
				const unsigned char* p = s;
				const unsigned char* tail = s + length;
				_ResultT r = 0;

				for(; p != s; p++) {
					r += *p;
				}
				return r;
			}
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_to_hash_HPP__
