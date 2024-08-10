//
// Created by MasterGames on 10/08/2024.
//
#include "LuaUtils.h"

/*
 * Custom print function to redirect Lua print output to Android log
*/
int lua_print(lua_State* L)
{
    std::string message;
    int n = lua_gettop(L); // Number of arguments
    for (int i = 1; i <= n; ++i)
    {
        if (i > 1)
        {
            message += " "; // Separate arguments with space
        }
        message += lua_tostring(L, i); // Concatenate arguments
    }

    LOGI("Lua: %s", message.c_str());
    return 0;
}

/*
 * Function to execute Lua script
*/
void execute_lua_script(lua_State* L, const std::string& script)
{
    lua_pushcfunction(L, lua_print); // Set custom print function
    lua_setglobal(L, "print");

    if (luaL_dostring(L, script.c_str()) != LUA_OK)
    {
        LOGE("Lua error: %s", lua_tostring(L, -1));
    }
}

/*
 * Function to run the Lua script
*/
void run_lua_script(const std::string& script)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Use the script from the header file
    execute_lua_script(L, script);

    lua_close(L);
}