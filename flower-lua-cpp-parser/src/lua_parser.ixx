export module lua_parser;

import <memory>;
import <lua.hpp>;
import <filesystem>;
import <string_view>;

namespace flower
{
	static constexpr auto can_file_be_read
	{
		[](auto lua_state, auto path)
		{
			return luaL_dofile(lua_state, path) ? false : true;
		}
	};

	export class Config final
	{
		using Lua_state = std::unique_ptr<lua_State, decltype(lua_close)*>;

	public:
		explicit Config(const std::filesystem::path& config_path)
		{
			luaL_openlibs(lua_state.get());
	
			if (!can_file_be_read(lua_state.get(), config_path.string().c_str()))
			{
				throw std::runtime_error("Could not open config file");
			}
		}

		

	private:
		const Lua_state lua_state{ luaL_newstate(), lua_close };
	};
}