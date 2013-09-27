#ifndef __github_com_myun2__nitro3__resource__handle_HPP__
#define __github_com_myun2__nitro3__resource__handle_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace resource
		{
			template <typename T, typename _Releaser>
			class handle
			{
			private:
				T _handle;
			public:
				handle(){}
				handle(const T in_handle) : _handle(in_handle) {}
				virtual ~handle() {
					_Releaser(in_handle);
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro3__resource__handle_HPP__
