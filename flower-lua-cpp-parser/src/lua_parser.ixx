module;

#include <lua.hpp>

export module lua_parser;

import helpers;
import <filesystem>;
import <variant>;
import <iostream>;

using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;

namespace flower
{
	export class Config final
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

		auto load_values() const
		{
			load_value(speed, "speed");
			load_value(position, "position");
			load_value(alive, "alive");
			load_value(name, "name");
		}

		static inline auto speed = int{};
		static inline auto position = float{};
		static inline auto alive = bool{};
		static inline auto name = std::string{};

	private:
		const Lua_state lua_state{ luaL_newstate(), lua_close };
	};
}