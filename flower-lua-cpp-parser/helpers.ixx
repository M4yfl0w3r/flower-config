module;

#include <lua.hpp>

export module helpers;

import <string_view>;
import <variant>;

export namespace flower::helpers
{
	constexpr auto can_file_be_read(const auto& lua_state, const auto& path)
	{
		return luaL_dofile(lua_state, path) ? false : true;
	};

	auto get_number(lua_State* lua_state, std::string_view value_name) -> std::variant<int, float, bool>
	{
		lua_getglobal(lua_state, value_name.data());

		if (lua_isinteger(lua_state, -1))
		{
			return static_cast<int>(lua_tointeger(lua_state, -1));
		}

		else if (lua_isboolean(lua_state, -1))
		{
			return static_cast<bool>(lua_toboolean(lua_state, -1));
		}

		else if (lua_isnumber(lua_state, -1))
		{
			return static_cast<float>(lua_tonumber(lua_state, -1));
		}
			
		return {};
	}

}
