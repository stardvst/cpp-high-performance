#include <algorithm>

struct Point
{
	int m_x;
	int m_y;
	~Point() {}
};

auto copy(Point *src, Point *dest)
{
	std::copy(src, src + 64, dest); // compiles to loop
}

struct PointOpt
{
	int m_x;
	int m_y;
	~Point() = default; // or no destructor at all
};

auto copy(PointOpt *src, PointOpt *dest)
{
	std::copy(src, src + 64, dest); // compiles to memmove
}

int main()
{
	return 0;
}
