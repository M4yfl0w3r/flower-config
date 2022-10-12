import lua_parser;

namespace fl = flower;

import <iostream>;

auto main() -> int
{
	fl::Config config { "./config.lua" };

	config.load_values();

	std::cout << std::format("Speed = {}\n", fl::Config::speed);
	std::cout << std::format("Position = {}\n", fl::Config::position);
	std::cout << std::boolalpha << std::format("Alive = {}\n", fl::Config::alive);
	std::cout << std::format("Name = {}\n\n", fl::Config::name);
	std::cout << std::format("{}\n", fl::Config::fragShader);

}
