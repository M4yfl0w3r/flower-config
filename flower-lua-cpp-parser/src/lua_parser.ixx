module;

#include <lua.hpp>

export module lua_parser;

import <filesystem>;

namespace flower
{

	export class Config final
	{
		using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;

	public:
		explicit Config(const std::filesystem::path&);

		auto print_stack() const -> void;

	private:
		const Lua_state lua_state{ luaL_newstate(), lua_close };
	};
}