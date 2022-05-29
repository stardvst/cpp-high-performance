#include <experimental/propagate_const>

class Foo
{
public:
	explicit Foo(int *ptr) : m_ptr{ ptr } {}

	auto set_ptr_val(int v) const
	{
		*m_ptr = v;
	}

private:
	int *m_ptr{};
};

class Bar
{
public:
	explicit Bar(int *ptr) : m_ptr{ ptr } {}

	// none of below code will compile, because const is propagated

	// auto set_ptr(int *ptr) const
	// {
	// 	m_ptr = ptr;
	// }

	// auto set_val(int v) const
	// {
	// 	m_val = v;
	// }

	// auto set_ptr_val(int v) const
	// {
	// 	*m_ptr = v;
	// }

private:
	std::experimental::propagate_const<int *> m_ptr = nullptr;
	int m_val{};
};

int main()
{
	auto i = 0;
	const auto foo = Foo{ &i };
	foo.set_ptr_val(42);
}
