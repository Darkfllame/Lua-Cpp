#include "LuaCpp.hpp"

using namespace Lua54Cpp;

static void loadLib();

Lua* lua = NULL;

int main(int argc, const char** argv)
{
	if (argc < 2) 
	{
		std::cout << "no file given" << std::endl;
		return 0;
	}

	lua = new Lua();

	loadLib();
	lua->DoFile(argv[1]);

	delete lua;
	return 0;
}

static void loadLib()
{
	
}