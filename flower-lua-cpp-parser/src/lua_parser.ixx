export module lua_parser;

import <memory>;
import <lua.hpp>;
import <string_view>;

export namespace flower
{
	constexpr auto can_file_be_read
	{   
		[](auto lua_state, auto path)
		{ 
			if (luaL_loadfile(lua_state, path))
			{
				return false;
			}

			if (lua_pcall(lua_state, 0, LUA_MULTRET, 0))
			{
				return false;
			}

			return true;
		}
	};

	[[nodiscard]] auto load_config(std::string_view path) -> int
	{
		using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;
		const auto lua_state { Lua_state { luaL_newstate(), lua_close } };

		luaL_openlibs(lua_state.get());

		if (can_file_be_read(lua_state.get(), path.data()))
		{
			lua_getglobal(lua_state.get(), "speed");
			return static_cast<int>(lua_tonumber(lua_state.get(), -1));
		}
	}
}