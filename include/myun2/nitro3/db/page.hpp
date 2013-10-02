#ifndef __github_com_myun2__nitro__db__page_HPP__
#define __github_com_myun2__nitro__db__page_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _IndexFile, typename _Value, unsigned int _PageBits=8>
			class page
			{
			public:
				typedef unsigned int index_t;
				typedef unsigned int hash_t;
			private:
				_IndexFile& _index;
				unsigned int page_head;

				hash_t key_to_index(const void* key, unsigned int key_length) {
					return *key;
				}
			public:
				page(_IndexFile& index, unsigned int page_head_in) : _index(index), page_head(page_head_in) {}

				///////////////////////

				index_t write(const char* key, const &_Value v) { return write(key, strlen(key), v); }
				index_t write(const void* key, unsigned int key_length, const &_Value v) {
					return _impl.write(page_head_in + key_to_index(key, key_length), v);
				}

				_Value read(const char* key) { return read(key, strlen(key)); }
				_Value read(const void* key, unsigned int key_length) {
					return _impl.read(page_head_in + key_to_index(key, key_length));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__page_HPP__
