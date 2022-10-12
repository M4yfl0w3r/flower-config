module;

#include <lua.hpp>
#include <string>
#include <format>
#include <iostream>

module lua_parser;

import helpers;

using namespace flower;
	
Config::Config(const std::filesystem::path& config_path)
{
	luaL_openlibs(lua_state.get());

	if (!helpers::can_file_be_read(lua_state.get(), config_path.string().c_str()))
	{
		lua_close(lua_state.get());
	}
}

auto Config::print_stack() const -> void
{
	const auto top = lua_gettop(lua_state.get());

	for (auto ix = 1u; ix <= top; ++ix)
	{
		switch (lua_type(lua_state.get(), ix))
		{
		case LUA_TBOOLEAN:
			std::cout << std::format("{}\n ", lua_toboolean(lua_state.get(), ix) ? "true" : "false");
			break;

		case LUA_TNUMBER:
			std::cout << std::format("{}\n", lua_tonumber(lua_state.get(), ix));
			break;

		case LUA_TSTRING:
			std::cout << std::format("{}\n", lua_tostring(lua_state.get(), ix));
			break;
		}
	}
}
