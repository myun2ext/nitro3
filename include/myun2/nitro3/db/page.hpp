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
			private:
				_IndexFile& _index;
			public:
				page(_IndexFile& index) : _index(index) {}

				///////////////////////

				index_t add(const char* key, const &_Value v) { return add(key, strlen(key), v); }
				index_t add(const void* key, unsigned int key_length, const &_Value v) {
					return _impl.write(p, length);
				}

				template <typename T>
				id_t update(id_t i, const T& v) {
					seek_to(i);
					fwrite(&v, sizeof(v), 1, fp);
					return i;
				}

				///////////////////////

				::std::string read_str(id_t i) {
					seek_to(i);
					length_t length;
					fread(&length, sizeof(length_t), 1, fp);
					::std::string s(length, 0);
					fread((char*)s.data(), length, 1, fp);
					return s;
				}

				template <typename T>
				T read(id_t i) {
					seek_to(i);
					T v;
					fread(&v, sizeof(T), 1, fp);
					return v;
				}

				//template <typename T> ::std::vector<T> read_vector(id_t i) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__page_HPP__
