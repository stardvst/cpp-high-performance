#include <vector>
#include <functional>
#include "timer.h"

auto lambda = [](int v) { return v * 3; };

auto use_lambda()
{
	using T = decltype(lambda);
	auto fs = std::vector<T>(10'000'000, lambda);

	auto res = 1;
	{
		Timer t;
		for (const auto &f : fs)
			res = f(res);
	}
	return res;
}

auto use_std_function()
{
	using T = std::function<int(int)>;
	auto fs = std::vector<T>(10'000'000, T{ lambda });

	auto res = 1;
	{
		Timer t;
		for (const auto &f : fs)
			res = f(res);
	}
	return res;
}

int main()
{
	use_lambda();
	use_std_function();
}
