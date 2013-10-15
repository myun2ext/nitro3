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
			private:
				_Impl& file;
			public:
				string_pool(_Impl& _file) : file(_file) {}
			};
		}
	}
}

#endif//__github_com_myun2__nitro__db__string_pool_HPP__
