#include <string.h>
#include "common.h"
#include "char_base.h"
#include "mylua/base.h"
#include "char.h"
#include "item.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lssproto_serv.h"
#ifdef _NEW_ITEM_
extern int CheckCharMaxItem(int charindex);
#endif
#ifdef _ALLBLUES_LUA_1_2   
#include "mylua/mylua.h"
extern MY_Lua MYLua;
static CharBase ItemBaseInt[] = {
	{{"序號"},							ITEM_ID}
	,{{"圖號"},							ITEM_BASEIMAGENUMBER}
	,{{"價值"},							ITEM_COST}
	,{{"類型"},							ITEM_TYPE}
	,{{"使用"},							ITEM_ABLEUSEFIELD}
	,{{"目標"},							ITEM_TARGET}
	,{{"等級"},							ITEM_LEVEL}
	,{{"次數"},							ITEM_DAMAGEBREAK}
	,{{"堆疊"},							ITEM_USEPILENUMS}
	,{{"重疊"},							ITEM_CANBEPILE}
	,{{"需攻"},							ITEM_NEEDSTR}
	,{{"需敏"},							ITEM_NEEDDEX}
	,{{"需轉"},							ITEM_NEEDTRANS}
	,{{"需職業"},						ITEM_NEEDPROFESSION}
#ifdef _TAKE_ITEMDAMAGE
	,{{"最小度"},						ITEM_DAMAGECRUSHE}
	,{{"最大度"},						ITEM_MAXDAMAGECRUSHE}
#endif
	,{{"傷"},								ITEM_OTHERDAMAGE}
	,{{"吸"},								ITEM_OTHERDEFC}
	,{{"套裝"},							ITEM_SUITCODE}
	,{{"最小攻擊"},					ITEM_ATTACKNUM_MIN}
	,{{"最大攻擊"},					ITEM_ATTACKNUM_MAX}
	,{{"攻"},								ITEM_MODIFYATTACK}
	,{{"防"},								ITEM_MODIFYDEFENCE}
	,{{"敏"},								ITEM_MODIFYQUICK}
	,{{"HP"},								ITEM_MODIFYHP}
	,{{"MP"},								ITEM_MODIFYMP}
	,{{"運氣"},							ITEM_MODIFYLUCK}
	,{{"魅力"},							ITEM_MODIFYCHARM}
	,{{"迴避"},							ITEM_MODIFYAVOID}
	,{{"屬性"},							ITEM_MODIFYATTRIB}
	,{{"屬性比例"},					ITEM_MODIFYATTRIBVALUE}
	,{{"精靈"},							ITEM_MAGICID}
	,{{"中精率"},						ITEM_MAGICPROB}
	,{{"精耗MP"},						ITEM_MAGICUSEMP}
	,{{"格檔"},							ITEM_MODIFYARRANGE}
	,{{"次序"},							ITEM_MODIFYSEQUENCE}
	,{{"負重"},							ITEM_ATTACHPILE}
	,{{"命中"},							ITEM_HITRIGHT}
	,{{"忽防"},							ITEM_NEGLECTGUARD}
	,{{"毒耐"},							ITEM_POISON}
	,{{"麻耐"},							ITEM_PARALYSIS}
	,{{"睡耐"},							ITEM_SLEEP}
	,{{"石耐"},							ITEM_STONE}
	,{{"酒耐"},							ITEM_DRUNK}
	,{{"混耐"},							ITEM_CONFUSION}
	,{{"會心"},							ITEM_CRITICAL}
	,{{"動作"},							ITEM_USEACTION}
	,{{"登出消失"},					ITEM_DROPATLOGOUT}
	,{{"丟棄消失"},					ITEM_VANISHATDROP}
	,{{""},									ITEM_ISOVERED}
	,{{"郵寄"},							ITEM_CANPETMAIL}
	,{{"閤成從"},						ITEM_CANMERGEFROM}
	,{{"閤成至"},						ITEM_CANMERGETO}
	,{{"份量0"},						ITEM_INGVALUE0}
	,{{"份量1"},						ITEM_INGVALUE1}
	,{{"份量2"},						ITEM_INGVALUE2}
	,{{"份量3"},						ITEM_INGVALUE3}
	,{{"份量4"},						ITEM_INGVALUE4}
	,{{"顔色"},							ITEM_COLOER}
	,{{"物品等級"},					ITEM_LEAKLEVEL}
#ifdef _ITEM_USE_TIME
	,{{"物品時間"},					ITEM_USETIME}
#endif
}; 

static CharBase ItemBaseChar[] = {
	{{"名稱"},					ITEM_NAME}
	,{{"顯示名"},				ITEM_SECRETNAME}
	,{{"說明"},					ITEM_EFFECTSTRING}
	,{{"字段"},					ITEM_ARGUMENT}
	,{{"成份名0"},			ITEM_INGNAME0}
	,{{"成份名1"},			ITEM_INGNAME1}
	,{{"成份名2"},			ITEM_INGNAME2}
	,{{"成份名3"},			ITEM_INGNAME3}
	,{{"成份名4"},			ITEM_INGNAME4}
#ifdef _ANGEL_SUMMON
	,{{"精召"},					ITEM_ANGELMISSION}
	,{{"天使"},					ITEM_ANGELINFO}
	,{{"英雄"},					ITEM_HEROINFO}
#endif
	,{{"Unicode"},	ITEM_UNIQUECODE}
	,{{"編碼"},	ITEM_UNIQUECODE}
}; 

static CharBase ItemBaseValue[] = {
	{{"爪"},							ITEM_FIST}
	,{{"斧"},							ITEM_AXE}
	,{{"棍"},							ITEM_CLUB}
	,{{"槍"},							ITEM_SPEAR}
	,{{"弓"},							ITEM_BOW}
	,{{"盾"},							ITEM_SHIELD}
	,{{"盔"},							ITEM_HELM}
	,{{"鎧"},							ITEM_ARMOUR}
	,{{"環"},							ITEM_BRACELET}
	,{{"樂"},							ITEM_MUSIC}
	,{{"項"},							ITEM_NECKLACE}
	,{{"環"},							ITEM_RING}
	,{{"帶"},							ITEM_BELT}
	,{{"耳環"},						ITEM_EARRING}
	,{{"鼻環"},						ITEM_NOSERING}
	,{{"護身符"},					ITEM_AMULET}
	,{{"其它"},						ITEM_OTHER}
	,{{"迴鏇鏢"},					ITEM_BOOMERANG}
	,{{"投擲斧"},					ITEM_BOUNDTHROW}
	,{{"投擲石"},					ITEM_BREAKTHROW}
	,{{"碟"},							ITEM_DISH}
#ifdef _ITEM_INSLAY
	,{{"金屬"},						ITEM_METAL}
	,{{"寶石"},						ITEM_JEWEL}
#endif
#ifdef _ITEM_CHECKWARES
	,{{"貨物"},						ITEM_WARES}
#endif
#ifdef _ITEM_EQUITSPACE
	,{{"腰帶"},						ITEM_WBELT}
	,{{"盾牌"},						ITEM_WSHIELD}
	,{{"鞋子"},						ITEM_WSHOES}
#endif
#ifdef _EQUIT_NEWGLOVE 
	,{{"手套"},						ITEM_WGLOVE}
#endif
#ifdef _ALCHEMIST
	,{{"煉金術"},					ITEM_ALCHEMIST}
#endif
#ifdef _PET_ITEM
	,{{"寵頭"},						ITEM_PET_HEAD}
	,{{"寵牙"},						ITEM_PET_TOOTH}
	,{{"寵爪"},						ITEM_PET_CLAW}
	,{{"寵胸"},						ITEM_PET_BREAST}
	,{{"寵背"},						ITEM_PET_BACK}
	,{{"寵翅"},						ITEM_PET_WING}
	,{{"寵腳"},						ITEM_PET_FEET}
#endif
}; 

static CharBase ItemBaseWorkInt[] = {
	{{"對象"}, 						ITEM_WORKOBJINDEX}
	,{{"玩傢"}, 					ITEM_WORKCHARAINDEX}
}; 

static CharBase ItemBaseEvent[] = {
	{{"未知事件"}, 				ITEM_PREOVERFUNC}
	,{{"郵件事件"}, 			ITEM_POSTOVERFUNC}
	,{{"使用事件"}, 			ITEM_USEFUNC}
	,{{"裝上事件"}, 			ITEM_ATTACHFUNC}
	,{{"卸下事件"}, 			ITEM_DETACHFUNC}
	,{{"丟棄事件"}, 			ITEM_DROPFUNC}
	,{{"檢起事件"}, 			ITEM_PICKUPFUNC}
	,{{"死亡事件"}, 			ITEM_DIERELIFEFUNC}
}; 

static int getInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseInt, arraysizeof(ItemBaseInt));

	lua_pushinteger(L, ITEM_getInt(index, element));
	return 1;
}

static int setInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseInt, arraysizeof(ItemBaseInt));
	const int data = luaL_checkint(L, 3);
	
  if(ITEM_setInt(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getChar(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseChar, arraysizeof(ItemBaseChar));

	lua_pushstring(L, ITEM_getChar(index, element));
	return 1;
}

static int setChar(lua_State *L) 
{
	size_t l;
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseChar, arraysizeof(ItemBaseChar));
	char *data = luaL_checklstring(L, 3, &l);
	
  if(ITEM_setChar(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getWorkInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseWorkInt, arraysizeof(ItemBaseWorkInt));

	lua_pushinteger(L, ITEM_getWorkInt(index, element));
	return 1;
}

static int setWorkInt(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int element = getCharBaseValue(L, 2, ItemBaseWorkInt, arraysizeof(ItemBaseWorkInt));
	const int data = luaL_checkint(L, 3);
	
  if(ITEM_setWorkInt(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getNameFromNumber(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	
	lua_pushstring(L, ITEM_getNameFromNumber(id));
	
	return 1;
}

static int getArgumentString(lua_State *L)
{
	const int id = luaL_checkint(L, 1);

	lua_pushstring(L, ITEM_getArgumentString(id));

	return 1;
}

static int getcostFromITEMtabl(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	
	lua_pushinteger(L, ITEM_getcostFromITEMtabl(id));
	
	return 1;
}

static int getlevelFromITEMtabl(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	
	lua_pushinteger(L, ITEM_getlevelFromITEMtabl(id));
	
	return 1;
}

static int getgraNoFromITEMtabl(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	
	lua_pushinteger(L, ITEM_getgraNoFromITEMtabl(id));
	
	return 1;
}

static int getItemInfoFromNumber(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	
	lua_pushstring(L, ITEM_getItemInfoFromNumber(id));
	
	return 1;
}

static int setFunctionPointer(lua_State *L) 
{
	size_t l;
	const int index = luaL_checkint(L, 1);
  const int functype = getCharBaseValue(L, 2, ItemBaseEvent, arraysizeof(ItemBaseEvent));
  char *luafuncname=luaL_checklstring(L, 3, &l);

	return ITEM_setLUAFunction( index, functype, luafuncname );
}

static int addLUAListFunction(lua_State *L) 
{
	size_t l;
	char *luafuncname=luaL_checklstring(L, 1, &l);
  char *luafunctable=luaL_checklstring(L, 2, &l);
	char *luafunctablepath=luaL_checklstring(L, 3, &l);

	if(strlen(luafunctablepath) > 0){
		MY_Lua *mylua = &MYLua;
	  while(mylua->next != NULL){
	  	if(strcmp(mylua->luapath, luafunctablepath) == 0){
	  		return ITEM_addLUAListFunction( mylua->lua, luafuncname, luafunctable);
	  	}
	  	mylua = mylua->next;
	  }
	}else{
		return ITEM_addLUAListFunction(  L, luafuncname, luafunctable );
	}
	return 1;
}

static int UpdataItemOne(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int itemindex = luaL_checkint(L, 2);

	int i;
	for( i = 0; i < CheckCharMaxItem(charaindex) ; i++ ){
		if(itemindex == CHAR_getItemIndex( charaindex , i )){
			CHAR_sendItemDataOne( charaindex, i);
			break;
		}
	}

	return 1;
}

static int UpdataHaveItemOne(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int haveitemindex = luaL_checkint(L, 2);

	CHAR_sendItemDataOne( charaindex, haveitemindex);

	return 1;
}

static const luaL_Reg itemlib[] = {
	{"getInt", 									getInt},
	{"setInt", 									setInt},
	{"getChar", 								getChar},
	{"setChar", 								setChar},
	{"getWorkInt", 							getWorkInt},
	{"setWorkInt", 							setWorkInt},
	{"setFunctionPointer", 			setFunctionPointer},
	{"addLUAListFunction", 			addLUAListFunction},
	{"getNameFromNumber", 			getNameFromNumber},
	{"getArgumentString", 			getArgumentString},
	{"getcostFromITEMtabl", 		getcostFromITEMtabl},
	{"getlevelFromITEMtabl", 		getlevelFromITEMtabl},
	{"getgraNoFromITEMtabl", 		getgraNoFromITEMtabl},
	{"getItemInfoFromNumber", 	getItemInfoFromNumber},
	{"UpdataItemOne", 					UpdataItemOne},
	{"UpdataHaveItemOne", 			UpdataHaveItemOne},
  {NULL, 						NULL}
};

LUALIB_API int luaopen_Item (lua_State *L) {
  luaL_register(L, "item", itemlib);
  return 1;
}

#endif

