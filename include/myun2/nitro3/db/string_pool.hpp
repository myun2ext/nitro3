#ifndef __github_com_myun2__nitro__db__string_pool_HPP__
#define __github_com_myun2__nitro__db__string_pool_HPP__

#include <memory.h>

namespace myun2
{
	namespace nitro3
	{
		namespace db
		{
			template <typename _Impl>
			class string_pool
			{
			public:
				typedef typename _Impl::index_t index_t;
				typedef size_t length_t;
			private:
				_Impl& file;

				void write_length(index_t i, length_t length) {
					write(i, length, sizeof(length_t));
				}
				length_t read_length(index_t i) {
					length_t len = 0;
					read(i, len, sizeof(length_t));
					return len;
				}
			public:
				string_pool(_Impl& _file) : file(_file) {}

				index_t add(const void* p, length_t length) {
					index_t i = file.size();
					file._write(i, p, length);
					return i;
				}
				index_t add(const char* s) { return add(s, strlen(s)); }
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
					length_t len = read_length();
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

#endif//__github_com_myun2__nitro__db__string_pool_HPP__
