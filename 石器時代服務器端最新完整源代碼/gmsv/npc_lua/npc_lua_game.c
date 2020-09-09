#include "npc_lua.h"
#include "util.h"
#include "char.h"
#include "char_base.h"
#include "char_data.h"
#include "anim_tbl.h"
#include "object.h"
#include "battle.h"
#include "npcutil.h"
#include "item.h"
#include "readmap.h"
#include "saacproto_cli.h"
#include "family.h"

int NPC_Lua_Game_FMPOINT_GetData(lua_State *_NLL)
{
	CheckEx(_NLL, 2);
	CheckIndexNull(_NLL, 1);
	int GA_Index = (int)lua_tointeger(_NLL, 1);
	int GA_Flg = (int)lua_tointeger(_NLL, 2);

	if(GA_Flg >= 0)
	{
		if(GA_Flg < LUA_DATALINE1)
		{
			GA_Flg -= LUA_DATALINE0;
			char *GA_RetInt = FM_getManorData(GA_Index, GA_Flg);
			LRetInt(_NLL, atoi(GA_RetInt));
		}else if(GA_Flg < LUA_DATALINE2)
		{
			GA_Flg -= LUA_DATALINE1;
			char *GA_RetPoint = FM_getManorData(GA_Index, GA_Flg);
			LRetMsg(_NLL, GA_RetPoint);
		}else
		{
			LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
		}
	}
	LRetErrNull(_NLL, "傳入的標誌是錯誤的。");
}

int NPC_Lua_Game_FMPOINT_ACSetFMPoint(lua_State *_NLL)
{
	CheckEx(_NLL, 5);
	CheckIndexNull(_NLL, 1);
	int leaderindex = (int)lua_tointeger(_NLL, 1);
	int fmpointindex = (int)lua_tointeger(_NLL, 2);
	int map = (int)lua_tointeger(_NLL, 3);
	int x = (int)lua_tointeger(_NLL, 4);
	int y = (int)lua_tointeger(_NLL, 5);
	if(!CHAR_CHECKINDEX(leaderindex))
	{
		LRetErrInt(_NLL, -1, "傳入的索引是無效的。");
	}
	if (fmpointindex < 0 || fmpointindex > 9) 
	{
		LRetErrInt(_NLL, -1, "傳入的莊園編號是無效的。");
	}
	int fd = getfdFromCharaIndex( leaderindex ); 
	if( fd == -1 ){
		LRetErrInt(_NLL, -2, "該玩傢可能已經下綫！");
	}
	char *tmpbuf = "";
  sprintf(tmpbuf, "%d|%d|%d|%d|%d|",leaderindex,fmpointindex,map,x,y);
	FAMILY_SetPoint(fd,leaderindex,tmpbuf);
	LRetInt(_NLL, 0);
}

int NPC_Lua_Game_FMPOINT_ACFixFMPoint(lua_State *_NLL)
{
	CheckEx(_NLL, 3);
	CheckIndexNull(_NLL, 1);
	int winindex = (int)lua_tointeger(_NLL, 1);
	int loseindex = (int)lua_tointeger(_NLL, 2);
	int id = (int)lua_tointeger(_NLL, 3);
	if(!CHAR_CHECKINDEX(winindex) || !CHAR_CHECKINDEX(loseindex))
	{
	  LRetErrNull(_NLL, "傳入的索引是無效的。");
	}
	if (id < 0 || id > 9) 
	{
	  LRetErrNull(_NLL, "傳入的莊園編號是無效的。");
	}
if(CHAR_getInt( winindex, CHAR_FMLEADERFLAG ) != FMMEMBER_LEADER)//不是族長
	{
	  LRetErrNull(_NLL, "傳入的索引對象並不是族長");
	}
if(CHAR_getInt( loseindex, CHAR_FMLEADERFLAG ) != FMMEMBER_LEADER)//不是族長
  {
		LRetErrNull(_NLL, "傳入的索引對象並不是族長");
  }
	saacproto_ACFixFMPoint_send(acfd,	CHAR_getChar(winindex,CHAR_FMNAME),CHAR_getInt(winindex,CHAR_FMINDEX) + 1,CHAR_getInt(winindex,CHAR_FMINDEX),
	CHAR_getChar(loseindex,CHAR_FMNAME),CHAR_getInt(loseindex,CHAR_FMINDEX) + 1,CHAR_getInt(loseindex,CHAR_FMINDEX),id);
	LRetInt(_NLL, 0);
}
/*
int NPC_Lua_Game_FMPOINT_ACCleanFMPoint(lua_State *_NLL)
{
	CheckEx(_NLL, 1);
	CheckIndexNull(_NLL, 1);
	int id = (int)lua_tointeger(_NLL, 1);
	if (id < 0 || id > 9)
	{
	  LRetErrNull(_NLL, "傳入的莊園編號是無效的。");
	}
	saacproto_ACDelFmPoint_send(acfd,id);
	LRetInt(_NLL, 0);
}
*/

