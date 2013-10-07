#ifndef __github_com_myun2__nitro__db__string_index_page_HPP__
#define __github_com_myun2__nitro__db__string_index_page_HPP__

#include "myun2/nitro3/db/string_to_hash.hpp"

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl>
			class string_index_page
			{
			public:
				typedef unsigned int index_t;
				typedef unsigned int hash_t;
			private:
				_Impl& file;
			public:
				string_index_page(_Impl& _file) : file(_file) {}

				///////////////////////

				index_t write(const char* key, const _Value& v) { return write(key, strlen(key), v); }
				index_t write(const void* key, unsigned int key_length, const _Value& v) {
					return _index.write(page_head + key_to_index(key, key_length), v);
				}

				_Value read(const char* key) { return read(key, strlen(key)); }
				_Value read(const void* key, unsigned int key_length) {
					return _index.read(page_head + key_to_index(key, key_length));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_index_page_HPP__
