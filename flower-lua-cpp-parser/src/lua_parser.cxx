module;

#include <lua.hpp>

module lua_parser;

import <string>;
import <format>;
import <iostream>;

using namespace flower;

static constexpr auto can_file_be_read
{
	[](const auto& lua_state, const auto& path)
	{
		return luaL_dofile(lua_state, path) ? false : true;
	}
};	
	
Config::Config(const std::filesystem::path& config_path)
{
	luaL_openlibs(lua_state.get());

	if (can_file_be_read(lua_state.get(), config_path.string().c_str()))
	{
		lua_getglobal(lua_state.get(), "speed");
		lua_getglobal(lua_state.get(), "alive");
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
