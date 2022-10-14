module;

#include <lua.hpp>
#include <array>
#include <span>
#include <variant>

export module lua_parser;

import helpers;
import <filesystem>;
import <iostream>;

using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;

namespace flower
{
	export class Config
	{
	public:
		explicit Config(const std::filesystem::path&);

		auto print_stack() const -> void;

		auto load_value(auto& value, std::string_view value_name) const
		{
			const auto result = helpers::get_number(lua_state.get(), value_name);

			if (std::holds_alternative<int>(result))
			{
				value = std::get<int>(result);
			}

			else if (std::holds_alternative<float>(result))
			{
				value = std::get<float>(result);
			}

			else if (std::holds_alternative<bool>(result))
			{
				value = std::get<bool>(result);
			}
		}

		auto load_value(std::string& value, std::string_view value_name) const
		{
			lua_getglobal(lua_state.get(), value_name.data());
			value = lua_tostring(lua_state.get(), -1);
		}

		auto load_value(std::vector<int>& vec, std::string_view value_name) const
		{
			lua_getglobal(lua_state.get(), value_name.data());

			if (!lua_istable(lua_state.get(), -1))
			{
				return;
			}

			lua_pushnil(lua_state.get());

			while (lua_next(lua_state.get(), -2))
			{
				vec.emplace_back(static_cast<float>(lua_tonumber(lua_state.get(), -1)));
				lua_pop(lua_state.get(), 1);
			}

			lua_pop(lua_state.get(), 1);
		}

	private:
		const Lua_state lua_state{ luaL_newstate(), lua_close };
	};
}