module;

#include <lua.hpp>

export module lua_parser;

import <filesystem>;
import <string_view>;
import <optional>;

namespace flower
{
	constexpr auto get_number = []<typename Type>(lua_State* lua_state, std::string_view value_name)
	{
		lua_getglobal(lua_state, value_name.data());

		if (lua_isinteger(lua_state, -1))
		{
			return static_cast<Type>(lua_tointeger(lua_state, -1));
		}

		else if (lua_isboolean(lua_state, -1))
		{
			return static_cast<Type>(lua_toboolean(lua_state, -1));
		}

		else if (lua_isnumber(lua_state, -1))
		{
			return static_cast<Type>(lua_tonumber(lua_state, -1));
		}

		return Type{};
	};

	export class Config final
	{
		using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;

	public:
		explicit Config(const std::filesystem::path&);

		auto print_stack() const -> void;

		[[nodiscard]] auto get_value(std::string_view value_name) const
		{
			return get_number.template operator() <float> (lua_state.get(), value_name);
		}

	private:
		const Lua_state lua_state{ luaL_newstate(), lua_close };
	};
}