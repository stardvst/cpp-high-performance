#include <initializer_list>
#include <vector>
#include <string>
#include <iostream>

class Menu
{
public:
	explicit Menu(const std::initializer_list<std::string> &items)
		: m_items(items)
	{
	}

	auto select(int i)
	{
		m_selected = i;
	}

	auto get_selected() const
	{
		std::cout << m_selected; // <---
		return m_selected != -1 ? m_items[m_selected] : std::string();
	}

private:
	int m_selected = -1;
	std::vector<std::string> m_items;
};

class MenuFixed
{
public:
	explicit MenuFixed(const std::initializer_list<std::string> &items)
		: m_items(items)
	{
	}

	MenuFixed(MenuFixed &&other) noexcept
	{
		std::swap(m_items, other.m_items);
		std::swap(m_selected, other.m_selected);
	}

	auto &operator=(MenuFixed &&other) noexcept
	{
		std::swap(m_items, other.m_items);
		std::swap(m_selected, other.m_selected);
		return *this;
	}

	auto select(int i)
	{
		m_selected = i;
	}

	auto get_selected() const
	{
		std::cout << m_selected; // <---
		return m_selected != -1 ? m_items[m_selected] : std::string();
	}

private:
	int m_selected = -1;
	std::vector<std::string> m_items;
};

int main()
{
	auto a = Menu{ "New", "Open", "Close", "Save" };
	a.select(2);
	auto b = std::move(a);
	auto selected = a.get_selected(); // crash, selected index is copied instead of move, and it has value of 2

	auto af = MenuFixed{ "New", "Open", "Close", "Save" };
	af.select(2);
	auto bf = std::move(af);
	auto selectedf = af.get_selected(); // crash, selected index is copied instead of move, and it has value of 2
}
