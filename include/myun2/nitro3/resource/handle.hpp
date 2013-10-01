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

					holder* clone() { add_reference(); this; }
					void add_reference() { referenced_count++; }
					void remove_reference() {
						referenced_count--;
						if ( referenced_count == 0 )
							_Releaser x(h);
					}

					static holder* allocate() { return new holder(); }
					static holder* allocate(const T& in_handle) { return new holder(in_handle); }
				};
				mutable holder *p_holder;
				holder* clone() const { p_holder->add_reference(); return p_holder; }
			public:
				handle(){ p_holder = 0; }
				handle(const T& in_handle) { p_holder = new holder(in_handle); }
				handle(const handle& in_handle) { p_holder = in_handle.clone(); }
				virtual ~handle() { if ( p_holder != 0 ) p_holder->remove_reference(); }
			};
		}
	}
}

#endif//__github_com_myun2__nitro3__resource__handle_HPP__
