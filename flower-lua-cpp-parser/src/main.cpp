import lua_parser;

namespace FL = flower;

#include <iostream>
#include <string_view>

auto main() -> int
{
	FL::Config config{ "./config.lua" };

	std::cout << config.get_value("speed");
}
