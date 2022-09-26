import lua_parser;

namespace FL = flower;

auto main() -> int
{
	FL::Config config { "./config.lua" };
	config.print_stack();
}
