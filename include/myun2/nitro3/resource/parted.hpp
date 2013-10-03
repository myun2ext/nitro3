#ifndef __github_com_myun2__nitro__resource__parted_HPP__
#define __github_com_myun2__nitro__resource__parted_HPP__

namespace myun2
{
	namespace nitro3
	{
		namespace resource
		{
			template <typename Impl, typename IndexType>
			class parted : public Impl
			{
			private:
				typedef Impl _Base;
				typedef IndexType T;
				const T start;
				const T end;
			public:
				parted(const IndexType &_start, const IndexType &_end) : start(_start), end(_end) {}

				template <typename T>
				parted(const IndexType &_start, const IndexType &_end, const T& v)
					: _Base(v), start(_start), end(_end)  {}

				size_t seek_to_tail(){ _Base::seek_to(end); return end; }
				void seek_to(long pos){ _Base::seek_to(pos); }
			};
		}
	}
}

#endif//__github_com_myun2__nitro__resource__parted_HPP__
