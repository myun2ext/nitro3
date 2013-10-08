#ifndef __github_com_myun2__nitro__db__binary_page_HPP__
#define __github_com_myun2__nitro__db__binary_page_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl, unsigned int _PageSize=256, typename _KeyType=unsigned char>
			class binary_page
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef _KeyType key_t;
			private:
				_Impl& file;

				unsigned int pages[_PageSize];
				void read_page() {
					file._read(0, pages, sizeof(pages));
				}
				void write_page() {
					file._write(0, pages, sizeof(pages));
				}
			public:
				binary_page(_Impl& _file) : file(_file) {
					read_page();
				}

				///////////////////////

				hash_t key_to_index(const char* s){ return string_to_hash(s); }

				index_t add(const char* key) {
					file.write(key_to_index(key));
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__binary_page_HPP__
