#include <iostream>
#include <string>

typedef std::string String;

// re-define the lua_State type because of the CFunctions
typedef struct lua_State lua_State;

#ifndef _LUACPPHPP
#define _LUACPPHPP

#define returnValues(indexs)for(int i=sizeof(indexs);i<=0;i--){lua_pushvalue(L,*indexs[i]);}return sizeof(indexs);}

namespace Lua54Cpp
{
	#pragma region types
	typedef int (CFunction)(lua_State*L);
	typedef long long Integer;
	typedef ptrdiff_t KContext;
	typedef int (*KFunction) (lua_State* L, int status, KContext ctx);
	typedef double Number;
	typedef void* UserData;
	typedef unsigned int Index;

	#define CFunction(name) static int name(Lua*lua)
	#define toLuaCfunc(func) static int func(lua_State* L){return func(new Lua(L));}
	#pragma endregion

	class Lua
	{
		lua_State* L;
		public:
			#pragma region misc
			// constructor
			Lua();
			Lua(lua_State*L);

			// deconstructor
			~Lua();

			// execute a string of lua code
			// \/returns 1 if all ok or an int from 1 to 5
			int DoString(String code);

			// execute a file of lua code
			// \/returns 1 if all ok or an int from 1 to 5
			int DoFile(String filename);

			// call a function by it's name with given arguments
			void CallFunction(String name, Index args[], int numberRes);

			Index SetGlobal(Index val, String name);
			#pragma endregion

			#pragma region ValueManipulation
			// create a value
			// \/returns its index in the stack 
			Index NewValue(String val);
			// create a value
			// \/returns its index in the stack 
			Index NewValue(Number val);
			// create a value
			// \/returns its index in the stack 
			Index NewValue(Integer val);
			// create a value
			// \/returns its index in the stack 
			Index NewValue(CFunction val);
			// create a value
			// \/returns its index in the stack 
			Index NewValue(UserData val);
			// create a value
			// \/returns its index in the stack 
			Index NewValue();

			// create a global value with a name
			// \/returns its index in the stack 
			Index NewGlobalValue(String val, String name);
			// create a global value with a name
			// \/returns its index in the stack 
			Index NewGlobalValue(Number val, String name);
			// create a global value with a name
			// \/returns its index in the stack 
			Index NewGlobalValue(Integer val, String name);
			// create a global value with a name
			// \/returns its index in the stack 
			Index NewGlobalValue(CFunction val, String name);
			// create a global value with a name
			// \/returns its index in the stack 
			Index NewGlobalValue(UserData val, String name);
			// create a value
			// \/returns its index in the stack 
			Index NewGlobalValue(String name);

			// copy the value at given index
			// \/return its index in the stack
			Index CopyValue(Index index);
			// copy the value with given name
			// \/return its index in the stack
			Index CopyGlobalValue(String index);
			// copy the value at given index with given name
			// \/return its index in the stack
			Index CopyValueAsGlobal(Index index, String name);
			// copy the value with given name with a new name
			// \/return its index in the stack
			Index CopyGlobalValueAsGlobal(String index, String name);
			#pragma endregion

			#pragma region TableManipulation
			// create a table with a pre-defined size
			// (use this if you know how many items will be in the table (performances))
			// \/returns the index of the table
			Index CreateTable(Index size);
			// create a table with a non-defined size
			// (use this if you know don't know how many items will be in the table)
			// \/returns the index of the table
			Index CreateTable();

			// create a global table with a pre-defined size and a name
			// (use this if you know how many items will be in the table (performances))
			// \/returns the index of the table
			Index CreateGlobalTable(Index size, String name);
			// create a global table with a non-defined size and a name
			// (use this if you know don't know how many items will be in the table)
			// \/returns the index of the table
			Index CreateGlobalTable(String name);

			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx, String val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx, Number val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx, Integer val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx, CFunction val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx, UserData val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, Integer idx);

			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, Integer idx, String val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, Integer idx, Number val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, Integer idx, Integer val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, Integer idx, CFunction val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, Integer idx, UserData val);

			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, String idx, String val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, String idx, Number val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, String idx, Integer val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, String idx, CFunction val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewTableValue(Index table, String idx, UserData val);

			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, String idx, String val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, String idx, Number val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, String idx, Integer val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, String idx, CFunction val);
			// create a new value in the given table at given index with given value
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index NewGlobalTableValue(String table, String idx, UserData val);

			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyValueToTable(Index table, Integer idx, Index val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyValueToGlobalTable(String table, Integer idx, Index val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyValueToTable(Index table, String idx, Index val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyValueToGlobalTable(String table, String idx, Index val);

			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyGlobalValueToTable(Index table, Integer idx, String val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyGlobalValueToGlobalTable(String table, Integer idx, String val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyGlobalValueToTable(Index table, String idx, String val);
			// add a already created value to the given table at given index
			// equivalent to table[idx] = val
			// \returns the index of the value
			Index CopyGlobalValueToGlobalTable(String table, String idx, String val);
			#pragma endregion
	};
}
#endif