import lua_parser;

import <exception>;
import <iostream>;

auto main() -> int
{
	try
	{
		flower::Config config("./config.lua");
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}
