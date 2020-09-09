#include <string.h>
#include "common.h"
#include "version.h"
#include "profession_skill.h"
#include "mylua/base.h"
#include "char.h"
#include "item.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lssproto_serv.h"

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
#ifdef _ALLBLUES_LUA_1_8 
#include "mylua/mylua.h"
extern MY_Lua MYLua;

static CharBase ProfessionSkillBaseInt[] = {
	{{"編號"},							PROFESSION_SKILL_ID}
	,{{"職業"},							PROFESSION_SKILL_PROFESSION_CLASS}
	,{{"目標"},							PROFESSION_SKILL_TARGET}
	,{{"耗費MP"},						PROFESSION_SKILL_COST_MP}
	,{{"旗標"},							PROFESSION_SKILL_USE_FLAG}
	,{{"種類"},							PROFESSION_SKILL_KIND}
	,{{"圖號"},							PROFESSION_SKILL_ICON}
	,{{"攻擊前圖號"},				PROFESSION_SKILL_IMG_1}
	,{{"攻擊圖號"},					PROFESSION_SKILL_IMG_2}
	,{{"金額"},							PROFESSION_SKILL_COST}
	,{{"升級數值"},					PROFESSION_SKILL_FIX_VALUE}
	,{{"必修1"},						PROFESSION_SKILL_LIMIT1}
	,{{"必修熟練度1"},			PROFESSION_SKILL_PERCENT1}
	,{{"必修2"},						PROFESSION_SKILL_LIMIT2}
	,{{"必修熟練度2"},			PROFESSION_SKILL_PERCENT2}
	,{{"必修3"},						PROFESSION_SKILL_LIMIT3}
	,{{"必修熟練度3"},			PROFESSION_SKILL_PERCENT3}
	,{{"必修4"},						PROFESSION_SKILL_LIMIT4}
	,{{"必修熟練度4"},			PROFESSION_SKILL_PERCENT4}
}; 

static CharBase ProfessionSkillBaseChar[] = {
	{{"名稱"},					PROFESSION_SKILL_NAME}
	,{{"注釋"},					PROFESSION_SKILL_TXT}
	,{{"函數"},					PROFESSION_SKILL_FUNCNAME}
	,{{"選項"},					PROFESSION_SKILL_OPTION}
}; 

static int getInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ProfessionSkillBaseInt, arraysizeof(ProfessionSkillBaseInt));

	lua_pushinteger(L, PROFESSION_SKILL_getInt(index, element));
	return 1;
}

static int setInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ProfessionSkillBaseInt, arraysizeof(ProfessionSkillBaseInt));
	const int data = luaL_checkint(L, 3);
	
  if(PROFESSION_SKILL_setInt(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getChar(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ProfessionSkillBaseChar, arraysizeof(ProfessionSkillBaseChar));

	lua_pushstring(L, PROFESSION_SKILL_getChar(index, element));
	return 1;
}

static int setChar(lua_State *L) 
{
	size_t l;
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ProfessionSkillBaseChar, arraysizeof(ProfessionSkillBaseChar));
	char *data = luaL_checklstring(L, 3, &l);
	
  if(PROFESSION_SKILL_setChar(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getProfessionskillArray(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);

	lua_pushinteger(L, PROFESSION_SKILL_getskillArray(index));
	return 1;
}

static const luaL_Reg Professionskilllib[] = {
	{"getInt", 									getInt},
	{"setInt", 									setInt},
	{"getChar", 								getChar},
	{"setChar", 								setChar},
	{"getProfessionskillArray", getProfessionskillArray},
  {NULL, 						NULL}
};

LUALIB_API int luaopen_ProfessionSkill (lua_State *L) {
  luaL_register(L, "Professionskill", Professionskilllib);
  return 1;
}
#endif
#endif

