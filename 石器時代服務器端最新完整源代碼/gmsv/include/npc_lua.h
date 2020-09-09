#ifndef __NPC_LUA__
#define __NPC_LUA__

#include "npc_lua_interface.h"
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LUA_DATALINE0 0
#define LUA_DATALINE1 2000
#define LUA_DATALINE2 4000
#define LUA_DATALINE3 6000
#define LUA_DATALINE4 8000
#define LUA_DATALINE5 10000
#define LUA_DATALINE6 10100
typedef struct __CREATEENEMY
{
	int EnemyId;
	int BaseLevel;
	int SkillType;
}CREATEENEMY,*PCREATEENEMY;

typedef struct __SCRIPTREGLIB
{
	const char *LibName;				//函數庫名
	luaL_reg *FuncRegList;			//需要注冊的函數庫函數列錶
}SCRIPTREGLIB,*PSCRIPTREGLIB;

typedef struct __SCRIPTREGCLASS
{
	const char *ClassName;			//類型名
	PSCRIPTREGLIB NewLib;				//用於申請類實例的 SCRIPTREGLIB
	luaL_reg *FuncRegList;			//需要注冊的類函數列錶
}SCRIPTREGCLASS,*PSCRIPTREGCLASS;

typedef struct __SCRIPTREGARRAY
{
	const char *ArrayName;			//數組名
	const char **SetMetaTable;	//用於設置數組響應動作
	const char **SetFuncName;		//用於設置數組響應動作的函數名字
	PSCRIPTREGLIB FuncList;			//用於響應對應 SetMetaTable 的處理函數列錶
}SCRIPTREGARRAY,*PSCRIPTREGARRAY;

typedef struct __ARRAY_NTINT
{
	size_t Size;
	int Num[1];
}ARRAY_NTINT,*PARRAY_NTINT;

//創建NPC-返迴NPC唯一索引
int NPC_Lua_Create(const char *_DoFile, const char *_InitFuncName, char *_seek, BOOL _IsFly);

//刪除NPC 傳入NPC唯一索引
int NPC_Lua_Del(int _index);

//創建戰鬥
int NPC_Lua_CreateVsEnemy(lua_State *_NLL, int _CharaIndex, int _NpcIndex, const char *_DoFunc, PCREATEENEMY _CreateEnemy, int _ARLen, int _Flg);

const char *NPC_Lua_SetErrorStr(const char *ErrStr);

//注冊擴展調用接口
int NPC_Lua_RegCallEx(lua_State * _NLL, luaL_Reg *_RegList);
//注冊擴展函數庫接口
int NPC_Lua_RegLibEx(lua_State * _NLL, PSCRIPTREGLIB _RegLib);
//注冊擴展類接口
int NPC_Lua_RegClassEx(lua_State * _NLL, PSCRIPTREGCLASS _RegClass);
//注冊擴展數組接口
int NPC_Lua_RegArrayEx(lua_State * _NLL, PSCRIPTREGARRAY _RegArray);

//擴展類型接口函數
//NTInt
int NPC_Lua_NTInt_New(lua_State *_NLL);
int NPC_Lua_NTInt_Get(lua_State *_NLL);
int NPC_Lua_NTInt_Set(lua_State *_NLL);
int NPC_Lua_NTInt_Len(lua_State *_NLL);

//接口函數
////////////////////////////////////////////////NL/////////////////////////////////////////////////
int NPC_Lua_NL_GetErrorStr(lua_State *_NLL);						//返迴錯誤信息
int NPC_Lua_NL_CreateNpc(lua_State *_NLL);							//創建NPC
int NPC_Lua_NL_CreateSpecialNpc(lua_State *L);
extern int copyChar(lua_State *L);
extern int createPet(lua_State *L);
extern int setCharPet(lua_State *L);
extern int getCharPet(lua_State *L);
extern int ToAroundChar(lua_State *L);
extern int Attack(lua_State *L);
extern int Recovery(lua_State *L);
extern int CreateVsEnemy (lua_State *L);
extern int talkToAllServer(lua_State *L);
extern int dengon(lua_State *L);
extern int RandRandWalk(lua_State *L);

int NPC_Lua_NL_DelNpc(lua_State *_NLL);									//刪除NPC
int NPC_Lua_NL_Mod(lua_State *_NLL);									  //求餘數
int NPC_Lua_NL_GetStringFromIndexWithDelim(lua_State *_NLL);									//使用指定字符分割字符串，並返迴調用者指定index位置的字符串
//int NPC_Lua_NL_ANSI_PlayerLoop(lua_State *_NLL);		    //遍曆所有存在人物，返迴索引號
int NPC_Lua_NL_PetLoopGetNext(lua_State *_NLL);		      //遍曆所有存在寵物，返迴寵物索引號 寫法類似定時器
int NPC_Lua_NL_ItemLoopGetNext(lua_State *_NLL);		    //遍曆所有存在道具，返迴道具索引號 如上
int NPC_Lua_NL_PlayerLoopGetNext(lua_State *_NLL);		  //遍曆所有存在人物，返迴人物索引號 如上
int NPC_Lua_NL_GetConfigLineType(lua_State *_NLL);	  	//返迴0為字符串形。1為SHORT形。2為INT型。3為DOUBLE型。如果不存在該字段，返迴-1.
int NPC_Lua_NL_GetConfigLineVal(lua_State *_NLL);	  	  //總是返迴[字符串]。如果需要轉換為數字，請用tonumber()函數。找不到該字段返迴nil
int NPC_Lua_NL_getGameservername(lua_State *_NLL);
BOOL NPC_Lua_CheckNpcEventFree(lua_State *_NLL);									//檢測對象是否滿足某條件
int NPC_Lua_DoNpcEventAction(lua_State *_NLL);									//執行NPC腳本命令
int NPC_Lua_NL_SetTimer(lua_State *_NLL);	  	          //設定一個計時器，所設的函數將按設定的間隔時間周期調用。
int NPC_Lua_NL_DelTimer(lua_State *_NLL);	  	          //刪除一個計時器。一個計時器被刪除，就不會再被周期調用；
int NPC_Lua_NL_RunSaFuncII(lua_State *_NLL);	  	      //調用一個服務端內定義好的2個INT參數的函數。
int NPC_Lua_NL_RunSaFuncIII(lua_State *_NLL);	  	      //調用一個服務端內定義好的3個INT參數的函數(如ITEM_USE等使用道具後的迴調函數）。
int NPC_Lua_NL_ANSI_PlayerLoop(lua_State *_NLL);		    //遍曆所有存在人物，返迴索引號
int NPC_Lua_NL_ANSI_PetLoop(lua_State *_NLL);		        //遍曆所有存在寵物，返迴索引號
int NPC_Lua_NL_ANSI_ItemLoop(lua_State *_NLL);		      //遍曆所有存在道具，返迴索引號
int NPC_Lua_NL_ClsMk(lua_State *_NLL);
int NPC_Lua_NL_AddCheckNum(lua_State *_NLL);
int NPC_Lua_NL_Mkstring(lua_State *_NLL);
int NPC_Lua_NL_Mkint(lua_State *_NLL);
int NPC_Lua_NL_SendMesg(lua_State *_NLL);
int NPC_Lua_NL_WriteShopData(lua_State *_NLL);
////////////////////////////////////////////////NLG////////////////////////////////////////////////
//功能接口
int NPC_Lua_NLG_UpItem(lua_State *_NLL);
int NPC_Lua_NLG_GiveItemOne(lua_State *_NLL);
int NPC_Lua_NLG_GivePetOne(lua_State *_NLL);
int NPC_Lua_NLG_DelItemByIndex(lua_State *_NLL);	
int NPC_Lua_NLG_FindPet(lua_State *_NLL);								//查找寵物欄空位
int NPC_Lua_NLG_GetMap(lua_State *_NLL);						    //獲得當前位置的建築物
int NPC_Lua_NLG_PetUp(lua_State *_NLL);								  //寵物升級
int NPC_Lua_NLG_AddSk(lua_State *_NLL);								  //給職業技能
int NPC_Lua_NLG_SetZy(lua_State *_NLL);								  //設定職業
int NPC_Lua_Char_GetPlayerMaxNum(lua_State *_NLL);			//獲取最大人數
int NPC_Lua_NLG_GetXY(lua_State *_NLL);							  	//獲取一個地圖的坐標
int NPC_Lua_NLG_WalkJc(lua_State *_NLL);							  //檢查障礙物
int NPC_Lua_NLG_KickPlayer(lua_State *_NLL);				  	//T除指定玩傢
int NPC_Lua_NLG_HealOne(lua_State *_NLL);				  	    //指定一個對象 迴復滿HP 滿MP
int NPC_Lua_NLG_HealAll(lua_State *_NLL);				  	    //指定一個玩傢MP 迴復所有包括寵物HP
int NPC_Lua_NLG_LevelUpTo(lua_State *_NLL);				  	  //提升對象的等級。
int NPC_Lua_NLG_AddExp(lua_State *_NLL);			  	  	  //給與一個對象經驗。
int NPC_Lua_NLG_UpPet(lua_State *_NLL);			  	  	    //更新對象的寵物，用於更新【客戶端】寵物數據，在某些後颱道具屬性被修改的情況下不能把更新數據發送到前颱；
int NPC_Lua_NLG_DelPetByPos(lua_State *_NLL);						//刪除 對像 身上指定欄位的寵物
int NPC_Lua_NLG_DelPetByIndex(lua_State *_NLL);					//刪除 對像 身上指定索引號（非ID）的寵物
int NPC_Lua_NLG_GivePetByIndex(lua_State *_NLL);				//給予一隻指定索引號的寵物給指定 對像， 返迴寵物欄位置
int NPC_Lua_NLG_GiveItemByIndex(lua_State *_NLL);				//給與一個道具index指定玩傢 返迴道具欄位
int NPC_Lua_NLG_WarpToSpecificPoint(lua_State *_NLL);	  //移動NPC 可做團體移動
BOOL NPC_Lua_NLG_UpSkillupPoint(lua_State *_NLL);       //更新人物點數
int NPC_Lua_NLG_StayEncount(lua_State *_NLL);	          //原地

int NPC_Lua_NLG_CheckInFront(lua_State *_NLL);					//用於檢查某個對象是否在某個對象麵前
int NPC_Lua_NLG_CheckObj(lua_State *_NLL);							//檢查某個地圖位置是否有對象存在
int NPC_Lua_NLG_CharLook(lua_State *_NLL);							//設置人物方嚮(發送更新封包)
int NPC_Lua_NLG_CreateBattle(lua_State *_NLL);					//創建戰鬥
int NPC_Lua_NLG_CreateVsEnemyAB (lua_State *L);
int NPC_Lua_NLG_InputCard(lua_State *_NLL);							//創建一個對話框讓玩傢輸入虛擬卡號
int NPC_Lua_NLG_CreateBattlePvP(lua_State *_NLL);

int NPC_Lua_NLG_SearchWatchBattleRandIndex(lua_State *_NLL);

int NPC_Lua_NLG_DelPet(lua_State *_NLL);								//刪除指定玩傢寵物欄一個或多個寵物
int NPC_Lua_NLG_DelHaveIndexPet(lua_State *_NLL);
int NPC_Lua_NLG_DelItem(lua_State *_NLL);								//刪除指定玩傢道具欄一個或多個寵物
int NPC_Lua_NLG_DelItemByPos(lua_State *_NLL);								//刪除指定玩傢道具欄一個或多個寵物
int NPC_Lua_NLG_DischargeParty(lua_State *_NLL);				//解散 團隊

int NPC_Lua_NLG_GivePet(lua_State *_NLL);								//給指定玩傢一個或多個寵物
int NPC_Lua_NLG_GiveOnePet(lua_State *_NLL);								//給指定玩傢一個寵物
int NPC_Lua_NLG_GiveItem(lua_State *_NLL);							//給指定玩傢一個或多個寵物
int NPC_Lua_NLG_GiveOneItem(lua_State *_NLL);							//給指定玩傢一個道具
int NPC_Lua_NLG_GiveRandItem(lua_State *_NLL);
int NPC_Lua_Char_GetOnLinePlayer(lua_State *_NLL);			//獲取當前在綫人數

int NPC_Lua_NLG_ShowWindowTalked(lua_State *_NLL);			//在指定玩傢客戶端顯示指定內容、類型的對話框
int NPC_Lua_NLG_SetAction(lua_State *_NLL);							//設置對象的動作

int NPC_Lua_NLG_TalkToCli(lua_State *_NLL);							//普通說話，可以對全服務器人說
int NPC_Lua_NLG_TalkToFloor(lua_State *_NLL);						//對在某一指定地圖內的玩傢說話

int NPC_Lua_NLG_UpChar(lua_State *_NLL);								//嚮NPC周圍的玩傢發送NPC的數據更新封包
int NPC_Lua_NLG_UpStateBySecond(lua_State *_NLL);				//嚮指定玩傢發送第2類狀態更新封包
int NPC_Lua_NLG_UpStateByThird(lua_State *_NLL);				//嚮指定玩傢發送第3類狀態更新封包
int NPC_Lua_NLG_Update_Party(lua_State *_NLL);					//嚮玩傢所在的團隊成員發送玩傢的狀態更新封包

int NPC_Lua_NLG_Warp(lua_State *_NLL);									//傳送一個對象
int NPC_Lua_NLG_WalkMove(lua_State *_NLL);							//移動一個對象
int NPC_Lua_NLG_WatchEntry(lua_State *_NLL);						//觀戰
int NPC_Lua_NLG_HealerAllHeal(lua_State *_NLL);         //加血
int NPC_Lua_NLG_GetMaxPlayNum(lua_State *_NLL);					//獲取服務器最大在綫數
int NPC_Lua_NLG_CheckPlayIndex(lua_State *_NLL);				//檢查玩傢索引是否正常
int NPC_Lua_NLG_Save(lua_State *_NLL);
////add by mo
int NPC_Lua_NLG_SetExp(lua_State *_NLL);							//設置服務器經驗倍率
int NPC_Lua_NLG_GetExp(lua_State *_NLL);							//獲取服務器經驗倍率
int NPC_Lua_NLG_SetPetTransRange(lua_State *_NLL);				//設置寵物轉生範圍參數
int NPC_Lua_NLG_GetPetTransRange(lua_State *_NLL);				//獲得寵物轉生範圍參數
///////////////////////////////////////////////Char////////////////////////////////////////////////
//設置數據的接口
int NPC_Lua_Char_ClrEvtEnd(lua_State *_NLL);						//設置清除結束任務標誌
int NPC_Lua_Char_ClrEvtNow(lua_State *_NLL);						//設置清除正在做任務標誌
int NPC_Lua_Char_ClrEvt(lua_State *_NLL);								//設置清除任務標誌
int NPC_Lua_Char_GetAllocPoint(lua_State *_NLL);	      //獲取寵物CharIndex的四維成長
int NPC_Lua_Char_GetDataFromEnemyBase(lua_State *_NLL);	//獲取對應 標誌 的寵物模闆數據（enemybaseX.txt）；
int NPC_Lua_Char_GetPlayerIndex(lua_State *_NLL);       //玩傢索引
int NPC_Lua_Char_FindItemIndex(lua_State *_NLL);				//搜索指定對像身上是否擁有某道具為指定的索引號
int NPC_Lua_Char_FindPetIndex(lua_State *_NLL);		      //搜索指定對像身上是否擁有寵物為指定的索引號
int NPC_Lua_CHAR_CHECKINDEX(lua_State *_NLL);				     //玩傢索引
int NPC_Lua_Char_GetPetSkill(lua_State *_NLL);				  //取得寵物指定技能欄的技能編號
int NPC_Lua_Char_GetPetSkillNo(lua_State *_NLL);	      //獲取Char數據
int NPC_Lua_Char_RidNo(lua_State *_NLL);								//設置清除任務標誌
int NPC_Lua_Char_GetEmptyItemBoxNum(lua_State *_NLL);	  //搜索指定對像身上道具欄空位的數量
int NPC_Lua_Char_GetEmptyPetBoxNum(lua_State *_NLL);	  //搜索指定對像身上寵物欄空位的數量
int NPC_Lua_Char_GetPlayerItemNum(lua_State *_NLL);	    //搜索指定對像身上為某ID的道具的數量
int NPC_Lua_Char_GetPlayerPetNum(lua_State *_NLL);	    //搜索指定對像身上為某ID的寵物的數量
int NPC_ABLua_char_getPlayerMaxNum(lua_State *_NLL);    //玩傢最大人數
int NPC_ABLua_char_getBattleexp(lua_State *_NLL);       //戰鬥經驗倍數
int NPC_Lua_Char_SetPetSkill(lua_State *_NLL);				  //設置寵物指定技能欄的技能編號
int NPC_Lua_Char_SetPetSkillNo(lua_State *_NLL);	
int NPC_Lua_Char_ComplianceParameter(lua_State *_NLL);	//根據對象屬性來重新計算並設置WORK屬性，以達到生效的目的。
int NPC_Lua_Char_HcItemId(lua_State *_NLL);					  	//閤成用到的搜索身上符閤物品。
int NPC_Lua_Char_DelHcItem(lua_State *_NLL);					  //刪除身上某個位置的物品。
int NPC_Lua_Char_GETFM(lua_State *_NLL);					      //獲取傢族氣勢 聲望 資金
int NPC_Lua_Char_FindPetEnemyBaseId(lua_State *_NLL);		//搜索指定對象身上是否擁有寵物EnemyBase文件的對應ID
int NPC_Lua_Char_ITEMID_NAME(lua_State *_NLL);					//獲得指定道具ID的名字
int NPC_Lua_Char_ITEMID_NAME2(lua_State *_NLL);					//獲得指定道具ID的說明
int NPC_Lua_Char_ITEMID_LEVEL(lua_State *_NLL);					//獲得指定道具ID的等級
int NPC_Lua_Char_ITEMID_GOLD(lua_State *_NLL);					//獲得指定道具ID的價格
int NPC_Lua_Char_ITEMID_RANO(lua_State *_NLL);					//獲得指定道具ID的圖形
int NPC_Lua_Char_CharRidNo(lua_State *_NLL);					  //檢查對像是否已經吃瞭某騎寵證；
int NPC_Lua_Char_GetPetOwner(lua_State *_NLL);				  //獲得寵物主人的索引號
int NPC_Lua_Char_GetEnemyBaseIdFromEnemyId(lua_State *_NLL);	//通過enemy.txt上所設置的寵物編號來查找enemybase.txt上所設定的寵物編號。
int NPC_Lua_Char_GetEnemyIdFromEnemyBaseId(lua_State *_NLL);	//通過enemybase.txt上所設置的寵物編號來查找enemy.txt上所設定的寵物編號。
int NPC_Lua_Char_GetIp(lua_State *_NLL);	              //獲取指定對像的IP地址
int NPC_Lua_Char_SetAllocPoint(lua_State *_NLL);	      //設置寵物CharIndex的四維成長
int NPC_Lua_Char_GetMaxPetIndex(lua_State *_NLL);	      //獲取最大寵物索引
int NPC_Lua_Char_GetMaxPlayerIndex(lua_State *_NLL);	  //獲取最大人物索引
int NPC_Lua_Char_SavePetToString(lua_State *_NLL);	    //生成一個描述寵物的字符串。
int NPC_Lua_Char_LoadPetFromString(lua_State *_NLL);	  //根據一個描述寵物的字符串，生成一個寵物。
int NPC_Lua_Char_GetPlayerFromAccAndName(lua_State *_NLL);//根據玩傢的帳號和人物名來尋找玩傢。帳號和人物名留空也可查找。不可都留空
int NPC_Lua_Char_CheckPet(lua_State *_NLL);             //檢查寵物索引是否有效。
int NPC_Lua_Char_CheckPlayer(lua_State *_NLL);          //檢查人物索引是否有效。
int NPC_Lua_Char_CheckItemIndex(lua_State *_NLL);           //檢查道具索引是否有效。
int NPC_Lua_Char_GetfdFromCharaIndex(lua_State *_NLL);

BOOL NPC_Lua_Char_JoinParty(lua_State *_NLL);           //加入團隊
int NPC_Lua_Char_getFamilyPlayIndex(lua_State *_NLL);   //獲得傢族裏邊人數的索引。

int NPC_Lua_Char_SetEvtEnd(lua_State *_NLL);						//設置任務標誌為結束狀態
int NPC_Lua_Char_SetEvtNow(lua_State *_NLL);						//設置任務標誌為正在做狀態
int NPC_Lua_Char_SetData(lua_State *_NLL);							//設置Char數據
int NPC_Lua_Char_logout(lua_State *_NLL);

int NPC_Lua_Char_getVipPoint(lua_State *_NLL);          //金幣更新
int NPC_Lua_Char_getjfPoint(lua_State *_NLL);           //積分更新
int NPC_Lua_Char_getxjPoint(lua_State *_NLL);           //現金更新
int NPC_Lua_Char_setVipPoint(lua_State *_NLL);          //金幣操作
int NPC_Lua_Char_setjfPoint(lua_State *_NLL);           //積分操作
int NPC_Lua_Char_setxjPoint(lua_State *_NLL);           //現金操作

int NPC_Lua_Char_GetVipPoint(lua_State *_NLL);
int NPC_Lua_Char_SetVipPoint(lua_State *_NLL);
int NPC_Lua_Char_GetAmPoint(lua_State *_NLL);
int NPC_Lua_Char_SetAmPoint(lua_State *_NLL);
int NPC_Lua_Char_GetRmbPoint(lua_State *_NLL);
int NPC_Lua_Char_SetRmbPoint(lua_State *_NLL);

//事件設置的接口
int NPC_Lua_Char_SetWalkPreEvent(lua_State *_NLL);			//設置WalkPre事件響應
int NPC_Lua_Char_SetWalkPostEvent(lua_State *_NLL);			//設置WalkPost事件響應
int NPC_Lua_Char_SetPreOverEvent(lua_State *_NLL);			//設置PreOver事件響應
int NPC_Lua_Char_SetPostOverEvent(lua_State *_NLL);			//設置PostOver事件響應
int NPC_Lua_Char_SetWatchEvent(lua_State *_NLL);				//設置Watch事件響應
int NPC_Lua_Char_SetLoopEvent(lua_State *_NLL);					//設置Loop事件響應
int NPC_Lua_Char_SetTalkedEvent(lua_State *_NLL);				//設置Talked事件響應
int NPC_Lua_Char_SetOFFEvent(lua_State *_NLL);					//設置OFF事件響應
int NPC_Lua_Char_SetLookedEvent(lua_State *_NLL);				//設置Looked事件響應
int NPC_Lua_Char_SetItemPutEvent(lua_State *_NLL);			//設置ItemPut事件響應
int NPC_Lua_Char_SetWindowTalkedEvent(lua_State *_NLL);	//設置WindowTalked事件響應
#ifdef _USER_CHARLOOPS
int NPC_Lua_Char_SetCharLoopsEvent(lua_State *_NLL);		//設置CharLoops事件響應
int NPC_Lua_Char_SetBattleProPertyEvent(lua_State *_NLL);//設置BattleProPerty事件響應
#endif

//獲取數據的接口
int NPC_Lua_Char_IsEventEnd(lua_State *_NLL);						//檢查是否結束的任務標誌
int NPC_Lua_Char_IsEventNow(lua_State *_NLL);						//檢查是否正在做的任務標誌

int NPC_Lua_Char_FindItemId(lua_State *_NLL);						//搜索指定對象身上是否擁有某道具ID
int NPC_Lua_Char_FindPetEnemyId(lua_State *_NLL);				//搜索指定對象身上是否擁有寵物Enemy文件的對應ID

int NPC_Lua_Char_GetData(lua_State *_NLL);						//獲取Char數據
int NPC_Lua_Char_GetItemId(lua_State *_NLL);						//獲取指定對象身上指定位置的道具ID
int NPC_Lua_Char_GetPetEnemyId(lua_State *_NLL);				//獲取指定對象身上指定位置的寵物Enemy文件的對應ID
int NPC_Lua_Char_GetItemIndex(lua_State *_NLL);					//獲取指定對象身上指定位置的道具索引
int NPC_Lua_Char_GetPetIndex(lua_State *_NLL);					//獲取指定對象身上指定位置的寵物對象索引
int NPC_Lua_Char_GetTeamIndex(lua_State *_NLL);					//獲取隊員的對象索引
int NPC_Lua_Char_GetPlayerIndexByCdkey(lua_State *_NLL);		//通過帳號查詢人物索引
int NPC_Lua_Char_VipPoint(lua_State *_NLL);
int NPC_Lua_Char_HealAll(lua_State *_NLL);
int NPC_Lua_Char_GetPetSkillId(lua_State *_NLL);
int NPC_Lua_Char_GetPetSkillName(lua_State *_NLL);
int NPC_Lua_Char_GetPetSkillMsg(lua_State *_NLL);
int NPC_Lua_Char_SetPetSkill(lua_State *_NLL);
int NPC_Lua_Char_RandMsg(lua_State *_NLL);
int NPC_Lua_Char_GetBeatitudeNum(lua_State *_NLL);
///////////////////////////////////////////////GAME////////////////////////////////////////////////
int NPC_Lua_Game_FMPOINT_GetData(lua_State *_NLL);           //獲得莊園據點的信息
int NPC_Lua_Game_FMPOINT_ACSetFMPoint(lua_State *_NLL);      //設定傢族據點信息。僅當據點未被占據時有效。
int NPC_Lua_Game_FMPOINT_ACFixFMPoint(lua_State *_NLL);      //修改傢族據點信息，並清空氣勢。一般用於族戰結束。
int NPC_Lua_Game_FMPOINT_ACCleanFMPoint(lua_State *_NLL);    //無條件清除傢族據點。
///////////////////////////////////////////////Item////////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Item_GetData(lua_State *_NLL);							//獲取道具數據
int NPC_Lua_Item_GetDataFromItemSet(lua_State *_NLL);		//獲取ITEMSETX文件的數據
int NPC_Lua_Item_GetValidity(lua_State *_NLL);		      //獲取指定道具的過期時間
int NPC_Lua_Item_GetItemOwner(lua_State *_NLL);		      //獲取指定道具主人的索引
int NPC_Lua_Item_GetMaxItemIndex(lua_State *_NLL);		  //獲取最大道具索引
int NPC_Lua_Item_SaveItemToString(lua_State *_NLL);	    //生成一個描述物品的字符串。
int NPC_Lua_Item_SetValidity(lua_State *_NLL);		      //設置指定道具的過期時間。
int NPC_Lua_Item_LoadItemFromString(lua_State *_NLL);	  //根據一個描述物品的字符串，生成一個物品。

//設置數據的接口
int NPC_Lua_Item_SetData(lua_State *_NLL);							//獲取道具數據

//事件設置的接口
int NPC_Lua_Item_SetPreOverEvent(lua_State *_NLL);			//設置PreOver事件響應
int NPC_Lua_Item_SetPostOverEvent(lua_State *_NLL);			//設置PostOver事件響應
int NPC_Lua_Item_SetWatchEvent(lua_State *_NLL);				//設置Watch事件響應
int NPC_Lua_Item_SetUseEvent(lua_State *_NLL);					//設置Use事件響應
int NPC_Lua_Item_SetAttachEvent(lua_State *_NLL);				//設置Attach事件響應
int NPC_Lua_Item_SetDetachEvent(lua_State *_NLL);				//設置Detach事件響應
int NPC_Lua_Item_SetDropEvent(lua_State *_NLL);					//設置Drop事件響應
int NPC_Lua_Item_SetPickUPEvent(lua_State *_NLL);				//設置PickUP事件響應
#ifdef _Item_ReLifeAct
int NPC_Lua_Item_SetDieReLifeEvent(lua_State *_NLL);		//設置DieReLife事件響應
#endif
///////////////////////////////////////////////BIT///////////////////////////////////////////////
int NPC_Lua_Bit_band(lua_State *_NLL);
int NPC_Lua_Bit_bor(lua_State *_NLL);
int NPC_Lua_Bit_bxor(lua_State *_NLL);
int NPC_Lua_Bit_lshift(lua_State *_NLL);
int NPC_Lua_Bit_rshift(lua_State *_NLL);
///////////////////////////////////////////////Obj////////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Obj_GetType(lua_State *_NLL);								//獲取OBJ的類型
/*
int NPC_Lua_Obj_GetName(lua_State *_NLL);								//獲取OBJ的名稱
int NPC_Lua_Obj_GetDIR(lua_State *_NLL);								//獲取OBJ的方嚮
int NPC_Lua_Obj_GetImageNum(lua_State *_NLL);						//獲取OBJ的形象號
*/
int NPC_Lua_Obj_GetCharType(lua_State *_NLL);						//獲取OBJ對應的Char數據結構的類型
int NPC_Lua_Obj_GetCharIndex(lua_State *_NLL);					//獲取OBJ對應的Char數據結構的索引
int NPC_Lua_Obj_GetX(lua_State *_NLL);									//獲取OBJ的X坐標
int NPC_Lua_Obj_GetY(lua_State *_NLL);									//獲取OBJ的Y坐標
int NPC_Lua_Obj_GetFloor(lua_State *_NLL);							//獲取OBJ所在的地圖編號
//int NPC_Lua_Obj_GetDelTime(lua_State *_NLL);						//獲取OBJ的刪除時間

int NPC_Lua_Obj_SetType(lua_State *_NLL);								//獲取OBJ的類型
/*
int NPC_Lua_Obj_SetName(lua_State *_NLL);								//獲取OBJ的名稱
int NPC_Lua_Obj_SetDIR(lua_State *_NLL);								//獲取OBJ的方嚮
int NPC_Lua_Obj_SetImageNum(lua_State *_NLL);						//獲取OBJ的形象號
*/
int NPC_Lua_Obj_SetCharType(lua_State *_NLL);						//獲取OBJ對應的Char數據結構的類型
int NPC_Lua_Obj_SetX(lua_State *_NLL);									//獲取OBJ的X坐標
int NPC_Lua_Obj_SetY(lua_State *_NLL);									//獲取OBJ的Y坐標
int NPC_Lua_Obj_SetFloor(lua_State *_NLL);							//獲取OBJ所在的地圖編號
//int NPC_Lua_Obj_SetDelTime(lua_State *_NLL);						//獲取OBJ的刪除時間

//////////////////////////////////////////////Battle///////////////////////////////////////////////
//獲取數據的接口
int NPC_Lua_Battle_GetPlayIndex(lua_State *_NLL);				//獲取戰鬥中的玩傢索引
int NPC_Lua_Battle_GetData(lua_State *_NLL);				    //獲取戰鬥數據
int NPC_Lua_Battle_SetData(lua_State *_NLL);				    //設置戰鬥數據
int NPC_Lua_Battle_IndexToNo(lua_State *_NLL);				  //通過對象索引獲取所在的戰場編號
int NPC_Lua_Battle_NoToIndex(lua_State *_NLL);				  //通過戰場編號獲取他的索引
int NPC_Lua_Battle_CheckIndex(lua_State *_NLL);				  //檢查戰鬥索引是否有效。
//設置數據的接口
int NPC_Lua_Battle_SetNORisk(lua_State *_NLL);					//設置是否開啓無風險模式
int NPC_Lua_Battle_SetMod(lua_State *_NLL);							//設置戰鬥模式標誌
int NPC_Lua_Battle_SetType(lua_State *_NLL);						//設置戰鬥類型
int NPC_Lua_Battle_Exit(lua_State *_NLL);				        //退齣戰鬥
//事件設置的接口
int NPC_Lua_Battle_SetWinEvent(lua_State *_NLL);				//設置Win事件響應
int NPC_Lua_Battle_SetEndEvent(lua_State *_NLL);				//設置Win事件響應
///////////////////////////////////////////////Other///////////////////////////////////////////////
int NPC_Lua_GetFuncPoint(lua_State *_NLL);							//獲取函數指針

//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////MAP////////////////////////////////////////////////
int NPC_Lua_Map_CheckCoordinates(lua_State *_NLL);         //檢測某點是否在地圖範圍內。
int NPC_Lua_Map_GetExitFloorXY(lua_State *_NLL);           //檢測地圖是否支持登齣
int NPC_Lua_Map_GetfloorX(lua_State *_NLL);                //獲取地圖X長度
int NPC_Lua_Map_GetfloorY(lua_State *_NLL);                 //獲取地圖Y長度
int NPC_Lua_Map_GetTileAndObjId(lua_State *_NLL);           //獲取地圖某點的地闆和裝飾層
int NPC_Lua_Map_SetTileAndObjId(lua_State *_NLL);           //設置地圖某點的地闆和裝飾層
int NPC_Lua_Map_GetWalkAbleFromPoint(lua_State *_NLL);      //獲取某點是否可以行走
int NPC_Lua_Map_GetImageData(lua_State *_NLL);              //獲取圖片數據
int NPC_Lua_Map_SetImageData(lua_State *_NLL);              //設置圖片數據
int NPC_Lua_Map_GetTopObj(lua_State *_NLL);                 //用來獲取地圖某點上對象
int NPC_Lua_Map_GetNextObj(lua_State *_NLL);                //獲取下一個對象索引
int NPC_Lua_Map_CheckImageIndex(lua_State *_NLL);           //檢測某地圖號圖片是否存在
int NPC_Lua_Map_CheckIndex(lua_State *_NLL);                //檢測某地圖號地圖是否存在
int NPC_Lua_Map_MakeNewMap(lua_State *_NLL);                //製造一個新的地圖 並返迴地圖的ID
int NPC_Lua_Map_DelNewMap(lua_State *_NLL);                 //刪除一個副本地圖
int NPC_Lua_Map_SetExWarp(lua_State *_NLL);                 //設置人物登齣後地圖的傳送點
int NPC_Lua_Map_SetMapPoint(lua_State *_NLL);               //添加地圖傳送點
int NPC_Lua_Map_DelMapPoint(lua_State *_NLL);               //刪除地圖傳送點
int NPC_Lua_Map_getFloorName(lua_State *_NLL);               //獲得地圖名
int NPC_Lua_Map_Upmap(lua_State *_NLL);                      //更新地圖
///////////////////////////////////////////////MAP////////////////////////////////////////////////
///////////////////////////////////////////////Spell////////////////////////////////////////////////
int NPC_Lua_Spell_PETSKILL_GetData(lua_State *_NLL);    //獲取寵物技能ID
int NPC_Lua_Spell_PROFESSION_GetData(lua_State *_NLL);  //獲取職業技能ID
int NPC_Lua_Spell_MAGIC_GetData(lua_State *_NLL);       //獲取精靈技能ID
int NPC_Lua_Spell_PETSKILL_SetData(lua_State *_NLL);    //設置對應ID的技能數據；
int NPC_Lua_Spell_PROFESSION_SetData(lua_State *_NLL);  //設置對應ID的技能數據；
int NPC_Lua_Spell_MAGIC_SetData(lua_State *_NLL);       //設置對應ID的技能數據；
///////////////////////////////////////////////Spell////////////////////////////////////////////////
///////////////////////////////////////////////SQL/////////////////////////////////////////////////
int NPC_Lua_SQL_Push(lua_State *_NLL);						//用於推送MySQL指令
int NPC_Lua_SQL_PushPop(lua_State *_NLL);			//用於推送MySQL指令並設置響應函數
int NPC_Lua_SQL_PushPopAdv(lua_State *_NLL);            //嚮SAAC發齣一個SQL查詢請求，並指定當SAAC返迴處理結果時對結果進行處理的迴調函數,該函數將返迴第一行結果，並釋放結果集。
int NPC_Lua_SQL_QueryFirstRow(lua_State *_NLL);         //迴調函數,該函數將返迴第一行結果，並釋放結果集。
int NPC_Lua_SQL_FetchRow(lua_State *_NLL);              //下一條結果
int NPC_Lua_SQL_FreeResult(lua_State *_NLL);            //釋放結果集
///////////////////////////////////////////////SQL///////////////////////////////////////////////
#define LRet(r) \
{ \
	NPC_Lua_SetErrorStr(NULL); \
	return r; \
}

#define LRetErr(c,r) \
{ \
	NPC_Lua_SetErrorStr(c); \
	return r; \
}

//////////////////////////////////////////////////////////////////////
//返迴一個nil
#define LRetNull(L) \
{ \
	lua_pushnil(L); \
	LRet(1); \
}

//返迴一個BOOL給LUA引擎
#define LRetBool(L, b) \
{ \
	lua_pushboolean(L, b); \
	LRet(1); \
}

//返迴一個int給LUA引擎
#define LRetInt(L, i) \
{ \
	lua_pushinteger(L, i); \
	LRet(1); \
}

#define LRetMsg(L, c) \
{ \
	lua_pushstring(L, c); \
	LRet(1); \
}
////////////////////////////////////////////////////////////////////
//設置一個錯誤狀態和一個錯信息
#define LRetErrInt(L, i, c) \
{ \
	lua_pushinteger(L, i); \
	LRetErr(c,1); \
}

//返迴一個字符串給LUA引擎
#define LRetErrNull(L, c) \
{ \
	lua_pushnil(L); \
	LRetErr(c,1); \
}

//返迴一個字符串給LUA引擎
#define LRetErrMsg(L, c) \
{ \
	lua_pushstring(L, c); \
	LRetErr(c,1); \
}

//用於檢查參數是否足夠
#define CheckEx(L, n) \
{	\
	if(lua_gettop(L) != n) \
	{ \
		luaL_argerror(L, 1, "參數數量錯誤"); \
	} \
}

#define CheckEx2(L, t, n) \
{	\
	if(lua_gettop(L) < (t) || lua_gettop(L) > n) \
	{ \
		luaL_argerror(L, 1, "參數數量錯誤"); \
	} \
}

#define CheckIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "對象索引不能為nil"); \
	} \
}

#define CheckBattleIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "戰鬥索引不能為nil"); \
	} \
}

#define CheckItemIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "道具索引不能為nil"); \
	} \
}

#define CheckObjIndexNull(L, n) \
{ \
	if(lua_isnil((L), (n))) \
	{ \
		luaL_argerror((L), 1, "物件索引不能為nil"); \
	} \
}

#define LRetArray(L, Array, num) \
{ \
	Lua_ReturnArray(L, Array, num); \
	LRet(1); \
}

#ifdef _LUA_Debug
int pcall_callback_err_fun(lua_State* L,const char *_InitFuncName); //調試LUA腳本齣錯信息
#endif

#endif //#ifndef __NPC_LUA__
