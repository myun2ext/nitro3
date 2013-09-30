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

					void increment_reference() { referenced_count++; }
					void decrement_reference() {
						referenced_count--;
						if ( referenced_count == 0 )
							_Releaser(h);
					}

					static holder* allocate() { return new T; }
					static holder* allocate(const T& in_handle) { return new T(in_handle); }
				};
				mutable holder *p_holder;
				void increment_reference() const { p_holder->referenced_count++; }
				void decrement_reference() const { p_holder->referenced_count--; }
				holder* holder_clone() const { p_holder->increment_reference(); return p_holder; }
			public:
				handle(){ p_holder = 0; }
				handle(const T& in_handle) { p_holder = holder::allocate(in_handle); }
				handle(const handle& in_handle) { p_holder = in_handle.holder_clone(); }
				virtual ~handle() { if ( p_holder != 0 ) p_holder->decrement_reference(); }
			};
		}
	}
}

#endif//__github_com_myun2__nitro3__resource__handle_HPP__
