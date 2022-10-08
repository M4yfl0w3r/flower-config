import lua_parser;

namespace fl = flower;

import <iostream>;

auto main() -> int
{
	fl::Config config{ "./config.lua" };

	config.load_values();

	std::cout << "Speed = " << fl::Config::speed << '\n';
	std::cout << "Position = " << fl::Config::position << '\n';
	std::cout << "Alive = " << std::boolalpha << fl::Config::alive << '\n';
}
