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
				struct holder
				{
					T h;
					unsigned int referenced_count;

					holder(){ referenced_count = 0; }
					holder(const T& in_handle) : h(in_handle) { referenced_count = 0; }

					static *holder allocate() { return new T; }
					static *holder allocate(const T& in_handle) { return new T(in_handle); }
				};
				holder *p_holder;
			public:
				handle(){ p_holder = 0; }
				handle(const T& in_handle) { p_holder = holder::allocate(in_handle); }
				virtual ~handle() {
					if ( p_holder != 0 ) _Releaser(in_handle);
				}
			};
		}
	}
}

#endif//__github_com_myun2__nitro3__resource__handle_HPP__
