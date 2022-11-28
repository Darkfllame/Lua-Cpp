#include "LuaCpp.hpp"
#include "lua.hpp"

using namespace Lua54Cpp;

void checkLuaType(int t, int type, const char* message)
{
	if (t != type)
	{
		std::cout << message << std::endl;
		exit(1);
	}
}

#pragma region Misc
Lua::Lua()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}
Lua::Lua(lua_State*L)
{
	(*this).L = L;
}
Lua::~Lua()
{
	lua_close(L);
}

int Lua::DoString(String code)
{
	return luaL_dostring(L, code.c_str());
}
int Lua::DoFile(String filename)
{
	return luaL_dofile(L, filename.c_str());
}

void Lua::CallFunction(String name, Index args[], int numberRes)
{
	int type = lua_getglobal(L, name.c_str());
	checkLuaType(type, LUA_TFUNCTION, "can't call a non-function type");
	for (int i = sizeof(args); i > 0; i--)
	{
		lua_pushvalue(L, args[i]);
	}
	lua_call(L, sizeof(args), numberRes);
}

Index Lua::SetGlobal(Index val, String name)
{
	lua_pushvalue(L, val);
	lua_setglobal(L, name.c_str());

	return lua_absindex(L, val);
}
#pragma endregion

#pragma region ValueManipulation
Index Lua::NewValue(String val)
{
	lua_pushstring(L, val.c_str());
	return lua_absindex(L, -1);
}
Index Lua::NewValue(Number val)
{
	lua_pushnumber(L, val);
	return lua_absindex(L, -1);
}
Index Lua::NewValue(Integer val)
{
	lua_pushinteger(L, val);
	return lua_absindex(L, -1);
}
Index Lua::NewValue(CFunction val)
{
	lua_pushcclosure(L, val, 0);
	return lua_absindex(L, -1);
}
Index Lua::NewValue(UserData val)
{
	lua_pushlightuserdata(L, val);
	return lua_absindex(L, -1);
}
Index Lua::NewValue()
{
	lua_pushnil(L);
	return lua_absindex(L, -1);
}

Index Lua::NewGlobalValue(String val, String name)
{
	Index idx = NewValue(val);
	lua_setglobal(L, name.c_str());
	return idx;
}
Index Lua::NewGlobalValue(Number val, String name)
{
	Index idx = NewValue(val);
	lua_setglobal(L, name.c_str());
	return idx;
}
Index Lua::NewGlobalValue(Integer val, String name)
{
	Index idx = NewValue(val);
	lua_setglobal(L, name.c_str());
	return idx;
}
Index Lua::NewGlobalValue(CFunction val, String name)
{
	Index idx = NewValue(val);
	lua_setglobal(L, name.c_str());
	return idx;
}
Index Lua::NewGlobalValue(UserData val, String name)
{
	Index idx = NewValue(val);
	lua_setglobal(L, name.c_str());
	return idx;
}
Index Lua::NewGlobalValue(String name)
{
	Index idx = NewValue();
	lua_setglobal(L, name.c_str());
	return idx;
}

Index Lua::CopyValue(Index index)
{
	lua_pushvalue(L, index);
	return lua_absindex(L, -1);
}
Index Lua::CopyGlobalValue(String index)
{
	lua_getglobal(L, index.c_str());
	lua_pushvalue(L, -1);
	return lua_absindex(L, -1);
}
Index Lua::CopyValueAsGlobal(Index index, String name)
{
	lua_pushvalue(L, index);
	lua_setglobal(L, name.c_str());
	return lua_absindex(L, -1);
}
Index Lua::CopyGlobalValueAsGlobal(String index, String name)
{
	lua_getglobal(L, index.c_str());
	lua_pushvalue(L, -1);
	lua_setglobal(L, name.c_str());
	return lua_absindex(L, -1);
}
#pragma endregion

#pragma region TableManipulations
Index Lua::CreateTable(Index size)
{
	lua_createtable(L, 0, size);
	return lua_absindex(L, -1);
}
Index Lua::CreateTable()
{
	return CreateTable(0);
}

Index Lua::CreateGlobalTable(Index size, String name)
{
	Index i = CreateTable(size);
	lua_setglobal(L, name.c_str());
	return i;
}
Index Lua::CreateGlobalTable(String name)
{
	Index i = CreateTable();
	lua_setglobal(L, name.c_str());
	return i;
}

Index Lua::NewTableValue(Index table, Integer idx, String val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);			// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, Integer idx, Number val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);			// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, Integer idx, Integer val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);			// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, Integer idx, CFunction val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);			// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, Integer idx, UserData val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);			// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, Integer idx)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue();				// create a new value
	lua_seti(L, table, idx);			// set the value to the table

	return table;
}

Index Lua::NewGlobalTableValue(String table, Integer idx, String val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);			// create a new value
	lua_seti(L, -2, idx);				// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, Integer idx, Number val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);			// create a new value
	lua_seti(L, -2, idx);				// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, Integer idx, Integer val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);			// create a new value
	lua_seti(L, -2, idx);				// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, Integer idx, CFunction val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);			// create a new value
	lua_seti(L, -2, idx);				// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, Integer idx, UserData val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);			// create a new value
	lua_seti(L, -2, idx);				// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}

Index Lua::NewTableValue(Index table, String idx, String val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);						// create a new value
	lua_setfield(L, table, idx.c_str());			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, String idx, Number val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);						// create a new value
	lua_setfield(L, table, idx.c_str());			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, String idx, Integer val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);						// create a new value
	lua_setfield(L, table, idx.c_str());			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, String idx, CFunction val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);						// create a new value
	lua_setfield(L, table, idx.c_str());			// set the value to the table

	return table;
}
Index Lua::NewTableValue(Index table, String idx, UserData val)
{
	// check if given table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	Index i = NewValue(val);						// create a new value
	lua_setfield(L, table, idx.c_str());			// set the value to the table

	return table;
}

Index Lua::NewGlobalTableValue(String table, String idx, String val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);				// create a new value
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, String idx, Number val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);				// create a new value
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, String idx, Integer val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);				// create a new value
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, String idx, CFunction val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);				// create a new value
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}
Index Lua::NewGlobalTableValue(String table, String idx, UserData val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	Index i = NewValue(val);				// create a new value
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}

Index Lua::CopyValueToTable(Index table, Integer idx, Index val)
{
	// check if table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	lua_pushvalue(L, val);			// push the value to the stack
	lua_seti(L, -2, idx);			// set the value to the table

	return lua_absindex(L, -1);
}
Index Lua::CopyValueToGlobalTable(String table, Integer idx, Index val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	lua_pushvalue(L, val);			// push the value to the stack
	lua_seti(L, -2, idx);		// set the value to the table

	return lua_absindex(L, -2);
}
Index Lua::CopyValueToTable(Index table, String idx, Index val)
{
	// check if table is a table
	luaL_checktype(L, table, LUA_TTABLE);

	lua_pushvalue(L, val);					// push the value to the stack
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	return table;
}
Index Lua::CopyValueToGlobalTable(String table, String idx, Index val)
{
	// get the type of table and push it on the stack
	int t = lua_getglobal(L, table.c_str());

	// check if table is a table
	checkLuaType(t, LUA_TTABLE, "given index is not a table");

	lua_pushvalue(L, val);					// push the value to the stack
	lua_setfield(L, -2, idx.c_str());		// set the value to the table

	t = lua_absindex(L, -2);

	return t;
}

Index Lua::CopyGlobalValueToTable(Index table, Integer idx, String val)
{
	checkLuaType(lua_type(L, table), LUA_TTABLE, "given #1 argument is not a table");
	lua_getglobal(L, val.c_str());
	lua_seti(L, table, idx);
	return lua_absindex(L, -1);
}
Index Lua::CopyGlobalValueToGlobalTable(String table, Integer idx, String val)
{
	int t = lua_getglobal(L, table.c_str());

	checkLuaType(t, LUA_TTABLE, "given #1 argument is not a table");

	lua_getglobal(L, val.c_str());
	lua_seti(L, -2, idx);

	return lua_absindex(L, -1);
}
Index Lua::CopyGlobalValueToTable(Index table, String idx, String val)
{
	checkLuaType(lua_type(L, table), LUA_TTABLE, "given #1 argument is not a table");
	lua_getglobal(L, val.c_str());
	lua_setfield(L, table, idx.c_str());
	return lua_absindex(L, -1);
}
Index Lua::CopyGlobalValueToGlobalTable(String table, String idx, String val)
{
	int t = lua_getglobal(L, table.c_str());

	checkLuaType(t, LUA_TTABLE, "given #1 argument is not a table");

	lua_getglobal(L, val.c_str());
	lua_setfield(L, -2, idx.c_str());

	return lua_absindex(L, -1);
}
#pragma endregion