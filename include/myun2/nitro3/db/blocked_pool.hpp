#ifndef __github_com_myun2__nitro__db__blocked_pool_HPP__
#define __github_com_myun2__nitro__db__blocked_pool_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			//	_IsSquaringUp = false is Incremental Up

			template <typename _Impl, unsigned int _MinimumEntry=8, unsigned int _RecordsInPage=512, bool _IsSquaringUp=true>
			class blocked_pool
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef size_t length_t;
			private:
				_Impl& file;

				struct header_block
				{
					unsigned int type;
					unsigned char __reserved[16 - sizeof(unsigned int)];

					unsigned int page_count;
					unsigned char __reserved[1024 * 16 - sizeof(unsigned int) - 16];
				};
				struct chunck_header
				{
					unsigned int used;
					unsigned char __reserved[16 - sizeof(unsigned int)];
				};
				header_block header;

				void write_length(index_t i, length_t length) {
					update(i, &length, sizeof(length_t));
				}
				length_t read_length(index_t i) {
					length_t len = 0;
					read(i, &len, sizeof(length_t));
					return len;
				}

				//////////

				void reload() {
					file._read(0, &header, sizeof(header));
				}

				void init_file() {
					memset(&header, 0, sizeof(header));
				}
				void init() {
					if ( file.size() == 0 )
						init_file();
					else
						reload();
				}
			public:
				blocked_pool(_Impl& _file) : file(_file) { init(); }

				index_t add(const void* p, length_t length) {
					index_t i = file.size();
					file._write(i, p, length);
					return i;
				}
				index_t add(const char* s) {
					size_t i = file.size();
					size_t len = strlen(s);
					write_length(i, len);
					add(s, len);
					return i;
				}
				template <typename T> index_t add(const T& v) { return add(&v, sizeof(v)); }

				////////////

				index_t update(index_t i, const void* p, length_t length) {
					file._write(i, p, length);
					return i;
				}
				index_t update(index_t i, const char* s) { return update(i, s, strlen(s)); }
				template <typename T> index_t update(index_t i, const T& v) { return update(i, &v, sizeof(v)); }

				////////////

				void read(index_t i, void* p, length_t length) {
					file._read(i, p, length);
				}

				::std::string read_s(index_t i) {
					length_t len = read_length(i);
					::std::string s(len, 0);
					read(i + sizeof(length_t), (char*)s.data(), len);
					return s;
				}
				template <typename T> T read(index_t i) {
					T v;
					read(i, &v, sizeof(T));
					return v;
				}
			};

			//////////////////////////////////////

			//	Is Incremental Up
			template <typename _Impl, unsigned int _MinimumEntry=8, unsigned int _RecordsInPage=128>
			class blocked_pool<_Impl,_MinimumEntry,_RecordsInPage,false>
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef size_t length_t;
			private:
				_Impl& file;

				struct chunck_header
				{
					unsigned int used_count;
				};
			public:
				blocked_pool(_Impl& _file) : file(_file) {}

				index_t add(const void* p, length_t length) {
					index_t i = file.size();
					file._write(i, p, length);
					return i;
				}
				index_t add(const char* s) {
					size_t i = file.size();
					size_t len = strlen(s);
					write_length(i, len);
					add(s, len);
					return i;
				}
				template <typename T> index_t add(const T& v) { return add(&v, sizeof(v)); }

				////////////

				index_t update(index_t i, const void* p, length_t length) {
					file._write(i, p, length);
					return i;
				}
				index_t update(index_t i, const char* s) { return update(i, s, strlen(s)); }
				template <typename T> index_t update(index_t i, const T& v) { return update(i, &v, sizeof(v)); }

				////////////

				void read(index_t i, void* p, length_t length) {
					file._read(i, p, length);
				}

				::std::string read_s(index_t i) {
					length_t len = read_length(i);
					::std::string s(len, 0);
					read(i + sizeof(length_t), (char*)s.data(), len);
					return s;
				}
				template <typename T> T read(index_t i) {
					T v;
					read(i, &v, sizeof(T));
					return v;
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__blocked_pool_HPP__
