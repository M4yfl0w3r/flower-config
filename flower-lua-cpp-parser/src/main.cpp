import lua_parser;

import <iostream>;

auto main() -> int
{
	auto config_speed { flower::load_config(std::string_view{ "./config.lua" }) };
	std::cout << "speed = " << config_speed<< '\n';
}
