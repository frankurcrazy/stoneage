#include <string.h>
#include "char.h"
#include "battle.h"
#include "object.h"
#include "char_base.h"
#include "enemy.h"
#include "mylua/base.h"
#include "npcutil.h"
#include "readmap.h"
#include "log.h"
#include "pet.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "longzoro/version.h"
#include "handletime.h"
#include "item_event.h"
#include "lssproto_serv.h"
#include "shop.h"
#ifdef _ALLBLUES_LUA   
#include "mylua/mylua.h"
extern MY_Lua MYLua;
static CharBase CharBaseWorkInt[] = {
	{{"對象"}, 						CHAR_WORKOBJINDEX}
#ifdef _FONT_SIZE
	,{{"字號"}, 					CHAR_WORKFONTSIZE}
#endif
	,{{"戰鬥"}, 					CHAR_WORKBATTLEMODE}
	,{{"組隊"}, 					CHAR_WORKPARTYMODE}
	,{{"戰鬥索引"}, 			CHAR_WORKBATTLEINDEX}
	,{{"戰鬥接口1"}, 			CHAR_WORKBATTLECOM1}
	,{{"戰鬥接口2"}, 			CHAR_WORKBATTLECOM2}
	,{{"NPC臨時1"}, 			CHAR_NPCWORKINT1}
  ,{{"NPC臨時2"}, 			CHAR_NPCWORKINT2}
  ,{{"NPC臨時3"}, 			CHAR_NPCWORKINT3}
  ,{{"NPC臨時4"}, 			CHAR_NPCWORKINT4}
  ,{{"NPC臨時5"}, 			CHAR_NPCWORKINT5}
  ,{{"NPC臨時6"},				CHAR_NPCWORKINT6}
  ,{{"NPC臨時7"},				CHAR_NPCWORKINT7}
  ,{{"NPC臨時8"},				CHAR_NPCWORKINT8}
  ,{{"NPC臨時9"},				CHAR_NPCWORKINT9}
  ,{{"NPC臨時10"},			CHAR_NPCWORKINT10}
  ,{{"NPC臨時11"},			CHAR_NPCWORKINT11}
	,{{"NPC臨時12"},			CHAR_NPCWORKINT12}
	,{{"NPC臨時13"},			CHAR_NPCWORKINT13}
	,{{"撿起模式"},				CHAR_WORKPETFOLLOWMODE}
  ,{{"隊員1"},					CHAR_WORKPARTYINDEX1}
  ,{{"隊員2"},					CHAR_WORKPARTYINDEX2}
  ,{{"隊員3"},					CHAR_WORKPARTYINDEX3}
	,{{"隊員4"},					CHAR_WORKPARTYINDEX4}
	,{{"隊員5"},					CHAR_WORKPARTYINDEX5}
	,{{"最大HP"},					CHAR_WORKMAXHP}
	,{{"最大MP"},					CHAR_WORKMAXMP}
	,{{"攻擊力"},					CHAR_WORKATTACKPOWER}
	,{{"防禦力"},					CHAR_WORKDEFENCEPOWER}
	,{{"敏捷力"},					CHAR_WORKQUICK}
	,{{"修正體力"},				CHAR_WORKFIXVITAL}
	,{{"修正腕力"},				CHAR_WORKFIXSTR}
	,{{"修正耐力"},				CHAR_WORKFIXTOUGH}
	,{{"修正速度"},				CHAR_WORKFIXDEX}
	,{{"家族地圖"},				CHAR_WORKFMFLOOR}
	,{{"攻擊"},						CHAR_WORKATTACKPOWER}
	,{{"防禦"},						CHAR_WORKDEFENCEPOWER}
	,{{"敏捷"},						CHAR_WORKQUICK}
	,{{"逃跑"},						CHAR_WORKDBATTLEESCAPE}
	,{{"經驗時間"},				CHAR_WORKITEM_ADDEXPTIME}
	,{{"經驗加成"},				CHAR_WORKITEM_ADDEXP}
#ifdef _OFFLINE_SYSTEM
	,{{"離綫"}, 					CHAR_WORK_OFFLINE}
#endif
	,{{"獲得經驗"},				CHAR_WORKGETEXP}
#ifdef _AUTO_PK
	,{{"自動PK點"},				CHAR_WORK_AUTOPK}
	,{{"自動PK死亡"},			CHAR_WORK_AUTOPK_DEAD}
#endif
#ifdef _SPECIAL_COUNTER
	,{{"計數器"}, 				CHAR_WORK_COUNTER}
#endif
#ifdef _SPECIAL_TIMER
	,{{"計時器"}, 				CHAR_WORK_TIMER}
#endif
#ifdef _STREET_VENDOR	
	,{{"擺攤"}, 					CHAR_WORKSTREETVENDOR}
#endif
#ifdef _RECORD_IP	
	,{{"IP"}, 						CHAR_WORK_RECORD_IP}
#endif
#ifdef _ONLINE_TIME
	,{{"登陸時間"}, 			CHAR_WORK_LOGIN_TIME}
#endif
#ifdef _NEWCLISETSERVID
	,{{"服務器ID"}, 			CHAR_WORK_SERVID}
#endif
	//,{{"PK時間"}, 			CHAR_WORKDBATTLETIME}
#ifdef _MIND_ICON
	,{{"心思"},					CHAR_MIND_NUM}
#endif
#ifdef _PLAYER_EFFECT
	,{{"人物效果"},			CHAR_PLAYER_EFFECT}
#endif
#ifdef _MO_PLAYER_EFFECT
	,{{"優先效果"},			CHAR_PLAYER_EFFECT_PRIORITY}
	,{{"戰寵特效"},			CHAR_PLAYER_EFFECT_PET}
	,{{"裝備特效"},			CHAR_PLAYER_EFFECT_ITEM}
#endif
#ifdef FAMILY_MANOR_
	,{{"莊園特效"},			CHAR_PLAYER_EFFECT_MANOR}
#endif
#ifdef _SINGLE_ONLINE
	,{{"單號在線"},			CHAR_WORK_SINGLE_ONLINE}
#endif
	,{{"主人索引"},			CHAR_WORKPLAYERINDEX}
#ifdef _NPC_EVENT_NOTICE
	,{{"NOTICE"}, 				CHAR_WORK_NOTICE}
#endif
#ifdef _MO_LUA_RESIST
	,{{"毒抗性"},			CHAR_WORKMODPOISON}
	,{{"麻抗性"},			CHAR_WORKMODPARALYSIS}
	,{{"睡抗性"},			CHAR_WORKMODSLEEP}
	,{{"石抗性"},			CHAR_WORKMODSTONE}
	,{{"酒抗性"},			CHAR_WORKMODDRUNK}
	,{{"混抗性"},			CHAR_WORKMODCONFUSION}
	,{{"虛抗性"},			CHAR_WORKMODWEAKEN}
	,{{"劇抗性"},			CHAR_WORKMODDEEPPOISON}
	,{{"障抗性"},			CHAR_WORKMODBARRIER}
	,{{"默抗性"},			CHAR_WORKMODNOCAST}

	,{{"毒抗附加"},			CHAR_WORK_RESIST_POISON}
	,{{"麻抗附加"},			CHAR_WORK_RESIST_PARALYSIS}
	,{{"睡抗附加"},			CHAR_WORK_RESIST_SLEEP}
	,{{"石抗附加"},			CHAR_WORK_RESIST_STONE}
	,{{"酒抗附加"},			CHAR_WORK_RESIST_DRUNK}
	,{{"混抗附加"},			CHAR_WORK_RESIST_CONFUSION}
	,{{"虛抗附加"},			CHAR_WORK_RESIST_WEAKEN}
	,{{"劇抗附加"},			CHAR_WORK_RESIST_DEEPPOISON}
	,{{"障抗附加"},			CHAR_WORK_RESIST_BARRIER}
	,{{"默抗附加"},			CHAR_WORK_RESIST_NOCAST}
#endif
};

static CharBase CharBaseWorkChar[] = {
	{{"NPC臨時1"}, 				CHAR_NPCWORKCHAR1}
  ,{{"NPC臨時2"}, 			CHAR_NPCWORKCHAR2}
  ,{{"NPC臨時3"}, 			CHAR_NPCWORKCHAR3}
  ,{{"NPC臨時4"}, 			CHAR_NPCWORKCHAR4}
  ,{{"NPC臨時5"}, 			CHAR_NPCWORKCHAR5}
  ,{{"NPC臨時6"},				CHAR_NPCWORKCHAR6}
#ifdef _STREET_VENDOR	
	,{{"擺攤"}, 						CHAR_STREETVENDOR_NAME}
#endif
#ifdef _NEWCLISETMAC	
	,{{"MAC"}, 						CHAR_WORK_MAC}
#endif
};

static CharBase CharBaseValue[] = {
	{{"北"}, 					0}
	,{{"東北"}, 			1}
	,{{"東"}, 				2}
	,{{"東南"}, 			3}
	,{{"南"}, 				4}
	,{{"西南"}, 			5}
	,{{"西"}, 				6}
	,{{"西北"}, 			7}
	,{{"無類型"}, 		CHAR_TYPENONE}
	,{{"玩傢"}, 			CHAR_TYPEPLAYER}
	,{{"敵人"}, 			CHAR_TYPEENEMY}
	,{{"寵物"}, 			CHAR_TYPEPET}
#ifdef _ALLBLUES_LUA 
	,{{"LUA"}, 			CHAR_TYPELUANPC}
#endif
#ifdef _PLAYER_NPC 
	,{{"幫托"}, 			CHAR_TYPEPLAYERNPC}
	,{{"幫寵"}, 			CHAR_TYPEPLAYERPETNPC}
#endif
};

static CharBase CharBaseWorkValue[] = {
	{{"無"}, 									CHAR_PARTY_NONE}
	,{{"隊長"}, 							CHAR_PARTY_LEADER}
	,{{"隊員"}, 							CHAR_PARTY_CLIENT}
	,{{"無戰鬥"}, 						BATTLE_CHARMODE_NONE}
	,{{"戰鬥初始化"}, 				BATTLE_CHARMODE_INIT}
	,{{"等待戰鬥"}, 					BATTLE_CHARMODE_C_WAIT}
	,{{"確認戰鬥"}, 					BATTLE_CHARMODE_C_OK}
	,{{"幫助戰鬥"}, 					BATTLE_CHARMODE_RESCUE}
	,{{"結束戰鬥"}, 					BATTLE_CHARMODE_FINAL}
	,{{"觀戰初始化"}, 				BATTLE_CHARMODE_WATCHINIT}
	,{{"沒有家族"}, 					FMMEMBER_NONE}
  ,{{"申請入族"}, 					FMMEMBER_APPLY}
  ,{{"族長"}, 							FMMEMBER_LEADER}
  ,{{"成員"}, 							FMMEMBER_MEMBER}
  ,{{"長老"}, 							FMMEMBER_ELDER}
};

static CharBase CharBaseInt[] = {
	{{"圖像號"}, 			CHAR_BASEIMAGENUMBER}
	,{{"原圖像號"}, 	CHAR_BASEBASEIMAGENUMBER}
	,{{"頭像號"},			CHAR_FACEIMAGENUMBER}
	,{{"存檔"},				CHAR_SAVEINDEXNUMBER}
	,{{"地圖號"},			CHAR_FLOOR}
	,{{"坐標X"}, 			CHAR_X}
	,{{"坐標Y"}, 			CHAR_Y}
	,{{"方嚮"}, 			CHAR_DIR}
	,{{"等級"}, 			CHAR_LV}
	,{{"石幣"}, 			CHAR_GOLD}
	,{{"HP"}, 				CHAR_HP}
	,{{"MP"}, 				CHAR_MP}
	,{{"最大MP"}, 		CHAR_MAXMP}
	,{{"體力"}, 			CHAR_VITAL}
	,{{"腕力"}, 			CHAR_STR}
	,{{"耐力"},				CHAR_TOUGH}
	,{{"速度"},				CHAR_DEX}
	,{{"地"},					CHAR_EARTHAT}
	,{{"水"},					CHAR_WATERAT}
	,{{"火"}, 				CHAR_FIREAT}
	,{{"風"}, 				CHAR_WINDAT}
	,{{"戰寵"}, 			CHAR_DEFAULTPET}
	,{{"魅力"}, 			CHAR_CHARM}
	,{{"運氣"}, 			CHAR_LUCK}
	,{{"死亡次數"}, 	CHAR_DEADCOUNT}
	,{{"走路步數"}, 	CHAR_WALKCOUNT}
	,{{"說話次數"}, 	CHAR_TALKCOUNT}
	,{{"損壞次數"}, 	CHAR_DAMAGECOUNT}
	,{{"給寵次數"}, 	CHAR_GETPETCOUNT}
	,{{"殺寵次數"}, 	CHAR_KILLPETCOUNT}
	,{{"死寵次數"}, 	CHAR_DEADPETCOUNT}
	,{{"發郵件數"}, 	CHAR_SENDMAILCOUNT}
	,{{"閤成次數"}, 	CHAR_MERGEITEMCOUNT}
	,{{"PK次數"}, 		CHAR_DUELBATTLECOUNT}
	,{{"PK贏數"},			CHAR_DUELWINCOUNT}
	,{{"PK敗數"}, 		CHAR_DUELLOSECOUNT}
	,{{"PK連勝"}, 		CHAR_DUELSTWINCOUNT}
	,{{"PK連敗"}, 		CHAR_DUELSTLOSECOUNT}
	,{{"PK最高連勝"},	CHAR_DUELMAXSTWINCOUNT}
	,{{"類型"}, 			CHAR_WHICHTYPE}
	,{{"循環事件時間"},   CHAR_LOOPINTERVALAB}
#ifdef _NEWOPEN_MAXEXP
	,{{"總經驗"}, 		CHAR_OLDEXP}
#endif
	,{{"當前經驗"}, 	CHAR_EXP}
	,{{"技能點"}, 		CHAR_SKILLUPPOINT}
	,{{"升級點"}, 		CHAR_LEVELUPPOINT}
	,{{"DP"}, 				CHAR_DUELPOINT}
	,{{"經驗"}, 			CHAR_EXP}
	,{{"出生地"}, 		CHAR_LASTTALKELDER}
	,{{"轉數"}, 			CHAR_TRANSMIGRATION}
	,{{"禁言"}, 			CHAR_SILENT}
	,{{"家族索引"}, 	CHAR_FMINDEX}
	,{{"家族地位"}, 	CHAR_FMLEADERFLAG}
	,{{"家族類型"}, 	CHAR_FMSPRITE}
#ifdef _NEW_RIDEPETS
	,{{"證書騎寵"}, 	CHAR_LOWRIDEPETS}
#endif
#ifdef _RIDE_CF
	,{{"證書騎寵1"}, 	CHAR_LOWRIDEPETS1}
#ifdef _ADD_RIDE_CF		
	,{{"證書騎寵2"}, 	CHAR_LOWRIDEPETS2}
#endif
#endif
	,{{"個人銀行"}, 	CHAR_BANKGOLD}
	,{{"騎寵"}, 			CHAR_RIDEPET}
	,{{"暴擊"}, 			CHAR_CRITIAL}
	,{{"反擊"}, 			CHAR_COUNTER}
	,{{"下綫時間"}, 	CHAR_LASTLEAVETIME}
#ifdef _GAMBLE_BANK
//	,{{"賭場銀行"}, 	CHAR_RIDEPET}
#endif
#ifdef _DROPSTAKENEW
	,{{"賭場積分"}, 	CHAR_GAMBLENUM}
#endif
#ifdef _TRUMP_EQUIPMENT
	,{{"法寶人物特效"},			CHAR_TRUMP_EFFECT}
#endif
#ifdef _PERSONAL_FAME	// Arminius 8.30: 家族個人聲望
	,{{"聲望"}, 			CHAR_FAME}
#endif
#ifdef _ATTACK_EFFECT
	,{{"攻擊特效"},			CHAR_ATTACK_EFFECT}
#endif
#ifdef _ATTACK_MAGIC
	,{{"地魔法熟練度"}, 			CHAR_EARTH_EXP}
	,{{"水魔法熟練度"}, 			CHAR_WATER_EXP}
	,{{"火魔法熟練度"}, 			CHAR_FIRE_EXP}
	,{{"風魔法熟練度"}, 			CHAR_WIND_EXP}
	,{{"地魔法抗性"}, 				CHAR_EARTH_RESIST}
	,{{"水魔法抗性"}, 				CHAR_WATER_RESIST}
	,{{"火魔法抗性"}, 				CHAR_FIRE_RESIST}
	,{{"風魔法抗性"}, 				CHAR_WIND_RESIST}
	,{{"地魔法熟練度經驗"}, 	CHAR_EARTH_ATTMAGIC_EXP}
	,{{"水魔法熟練度經驗"}, 	CHAR_WATER_ATTMAGIC_EXP}
	,{{"火魔法熟練度經驗"}, 	CHAR_FIRE_ATTMAGIC_EXP}
	,{{"風魔法熟練度經驗"}, 	CHAR_WIND_ATTMAGIC_EXP}
	,{{"地魔法抗性經驗值"}, 	CHAR_EARTH_DEFMAGIC_EXP}
	,{{"水魔法抗性經驗值"}, 	CHAR_WATER_DEFMAGIC_EXP}
	,{{"火魔法抗性經驗值"}, 	CHAR_FIRE_DEFMAGIC_EXP}
	,{{"風魔法抗性經驗值"}, 	CHAR_WIND_DEFMAGIC_EXP}
#endif
#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	,{{"職業彆"}, 	PROFESSION_CLASS}
	,{{"職業等級"}, 	PROFESSION_LEVEL}
	,{{"技能點數"}, 	PROFESSION_SKILL_POINT}
	,{{"增加堆疊"}, 	ATTACHPILE}
	,{{"火熟練度"}, 	PROFESSION_FIRE_P}
	,{{"冰熟練度"}, 	PROFESSION_ICE_P}
	,{{"雷熟練度"}, 	PROFESSION_THUNDER_P}
	,{{"火抗性"}, 	PROFESSION_FIRE_R}
	,{{"冰抗性"}, 	PROFESSION_ICE_R}
	,{{"雷抗性"}, 	PROFESSION_THUNDER_R}
#endif
#ifdef _NEW_MANOR_LAW
	,{{"氣勢"}, 		CHAR_MOMENTUM}
#endif
#ifdef _VIP_SERVER
	,{{"積分"}, 		CHAR_AMPOINT}
#endif
#ifdef _VIP_RIDE
	,{{"會員"}, 			CHAR_VIPRIDE}
	,{{"會員有效期"}, CHAR_VIPTIME}
#endif
#ifdef _ITEM_PET_LOCKED
	,{{"安全鎖"}, 		CHAR_LOCKED}
#endif
#ifdef _ONLINE_SHOP
	,{{"貝幣"}, 			CHAR_BJ}
#endif
	,{{"模式AI"}, 	CHAR_MODAI}
	,{{"可變AI"}, 	CHAR_VARIABLEAI}
	,{{"寵技位"}, 	CHAR_SLOT}
	,{{"寵ID"}, 		CHAR_PETID}
	,{{"怪ID"}, 		CHAR_PETENEMYID}
	,{{"守護獸"}, 	CHAR_PETFAMILY}
	,{{"能力值"}, 	CHAR_ALLOCPOINT}
	,{{"成長區間"}, CHAR_PETRANK}
	,{{"限製等級"}, CHAR_LIMITLEVEL}
#ifdef _PET_BEATITUDE
	,{{"提升值"}, 	CHAR_BEATITUDE}
#endif
#ifdef _CAMEO_MONEY
	,{{"貝殼"}, 		CHAR_CAMEO}
#endif
#ifdef _MISSION_TRAIN
	,{{"任務鏈"}, 	CHAR_MISSIONTRAIN_NUM}
	,{{"任務鏈時間"}, 	CHAR_MISSIONTRAIN_TIME}
#endif
#ifdef _PET_EVOLVE
	,{{"進化"}, 		CHAR_EVOLVE}
#endif
#ifdef _ONLINE_TIME
	,{{"在線時間"}, 		CHAR_ONLINE_TIME}
#endif

#ifdef _FLOOR_DIFI_FIELD
	,{{"樓層時間"}, 		CHAR_FLOORDIFI_TIME}
#endif
#ifdef _ACTIVE_GAME
	,{{"活力"}, 		CHAR_ACTIVE}
#endif
#ifdef _SUPER
	,{{"極品"}, 		CHAR_SUPER}
#endif
#ifdef _ALLDOMAN
	,{{"英雄稱號"}, 		CHAR_HEROFLOOR}
#endif

#ifdef _PLAYER_TITLE
	,{{"稱號等級"}, 		CHAR_TITLE_LV}
	,{{"稱號時間"}, 		CHAR_TITLE_TIME}
#endif
#ifdef _MISSION_TIME
	,{{"任務計時"}, 		CHAR_MISSION_TIME}
#endif
#ifdef _PETCOM_
	,{{"初體力"}, 		CHAR_YHP}
	,{{"初攻擊"}, 		CHAR_YATK}
	,{{"初防禦"}, 		CHAR_YDEF}
	,{{"初速度"}, 		CHAR_YQUICK}
	,{{"初等級"}, 		CHAR_YLV}
#endif
#ifdef _PET_FUSION
	,{{"融合寵"}, 		CHAR_FUSIONBEIT}
	,{{"融合蛋"}, 		CHAR_FUSIONRAISE}
#endif
#ifdef _REGISTRATION_TIME
	,{{"簽到時間"}, 		CHAR_REGISTRATION_TIME}
	,{{"簽到次數"}, 		CHAR_REGISTRATION_COUNT}
	,{{"簽到在線時間"}, CHAR_REGISTRATION_ONLINE_TIME}
#endif
#ifdef _SPECIAL_COUNTER 
	,{{"計數器"}, 		CHAR_SPCOUNTER}
#endif
#ifdef _SPECIAL_TIMER 
	,{{"計時器"}, 		CHAR_SPTIMER}
#endif
#ifdef _OFFLINE_TIME 
	,{{"離綫時間"}, 	CHAR_OFFLINE_TIME}
#endif
#ifdef _FAME_REG_TIME
	,{{"家族簽到時間"}, 	CHAR_FAME_REG_TIME}
#endif
#ifdef _PET_VALIDITY
	,{{"寵物有效期"},		CHAR_PETVALIDITY}
#endif
#ifdef _TENSE_FIELD
	,{{"限時字段"},		CHAR_TENSE_FIELD}
#endif
#ifdef _FM_JOINLIMIT
	,{{"退族時間"},		CHAR_FMTIMELIMIT}
#endif
#ifdef _NEW_ITEM_
	,{{"道具欄狀態"},		CHAR_NEWITEMFLG}
#endif
#ifdef _MO_PLAYER_EFFECT
	,{{"默認特效"},		CHAR_PLAYER_EFFECT_DEFAULT}
#endif
#ifdef _PETCOM_
	,{{"預測血量"},		CHAR_YHP}
	,{{"預測攻擊"},		CHAR_YATK}
	,{{"預測防禦"},		CHAR_YDEF}
	,{{"預測敏捷"},		CHAR_YQUICK}
	,{{"預測等級"},		CHAR_YLV}
#endif
#ifdef _MO_NO_WALK
	,{{"禁足"},		CHAR_NO_WALK}
#endif
#ifdef _NEW_TITLE
	,{{"默認稱號"},		CHAR_TITLE_DEFAULT}
	,{{"稱號狀態1"},		CHAR_TITLE1}
	,{{"稱號狀態2"},		CHAR_TITLE2}
	,{{"稱號狀態3"},		CHAR_TITLE3}
#endif
#ifdef _TRUMP_EQUIPMENT
	,{{"法寶狀態"},		CHAR_TRUMPFLG}
#endif
#ifdef _CHAR_TITLE_STR_
	,{{"文字稱號"},		CHAR_TITLE_}
#endif
};

static CharBase CharBaseChar[] = {
	{{"名字"}, 				CHAR_NAME}
	,{{"昵稱"}, 			CHAR_OWNTITLE}
	,{{"主人"},				CHAR_USERPETNAME}
	,{{"賬號"}, 			CHAR_CDKEY}
	,{{"家族"}, 			CHAR_FMNAME}
#ifdef _TEACHER_SYSTEM
	,{{"導師帳號"}, 	CHAR_TEACHER_ID}
	,{{"導師名字"}, 	CHAR_TEACHER_NAME}
#endif
#ifdef _ITEM_SETLOVER
	,{{"愛人賬號"}, 	CHAR_LOVERID}
	,{{"愛人名字"},		CHAR_LOVERNAME}
#endif
#ifdef _NEW_NAME
	,{{"稱號"},				CHAR_NEWNAME}
#endif
#ifdef _LOTTERY_SYSTEM
	,{{"彩票"},				CHAR_LOTTERY_VALUE}
#endif
	,{{"主人賬號"},		CHAR_OWNERCDKEY}
	,{{"主人名字"},		CHAR_OWNERCHARANAME}

#ifdef _POWER_UP
	,{{"能力提升"},		CHAR_POWER_UP}
#endif
#ifdef _VISUAL_BEATITUDE
	,{{"祝福狀態"},		CHAR_VB}
#endif
	,{{"Unicode"},		CHAR_UNIQUECODE}
};
		

static CharBase CharBaseEvent[] = {
	{{"初始化事件"}, 		CHAR_INITFUNC}
	//,{{"行走事件"}, 		CHAR_WALKPREFUNC}
	//,{{"行走後事件"},		CHAR_WALKPOSTFUNC}
	//,{{"未知事件"}, 		CHAR_PREOVERFUNC}
	//,{{"未知事件"}, 		CHAR_POSTOVERFUNC}
	//,{{"觀看事件"}, 		CHAR_WATCHFUNC}
	,{{"循環事件"}, 		CHAR_LOOPFUNC}
	//,{{"死亡事件"}, 		CHAR_DYINGFUNC}
	,{{"對話事件"},			CHAR_TALKEDFUNC}
	//,{{"攻擊事件"},			CHAR_PREATTACKEDFUNC}
	//,{{"攻擊後事件"}, 	CHAR_POSTATTACKEDFUNC}
	//,{{"離開事件"}, 		CHAR_OFFFUNC}
	//,{{"看事件"}, 			CHAR_LOOKEDFUNC}
	//,{{"丟棄事件"},			CHAR_ITEMPUTFUNC}
	//,{{"特殊對話事件"}, CHAR_SPECIALTALKEDFUNC}
	,{{"窗口事件"}, 		CHAR_WINDOWTALKEDFUNC}
#ifdef _USER_CHARLOOPS
	//,{{"循環事件1"}, 		CHAR_LOOPFUNCTEMP1}
	//,{{"循環事件2"}, 		CHAR_LOOPFUNCTEMP2}
	//,{{"未知事件"}, 		CHAR_BATTLEPROPERTY}
#endif
	,{{"重疊事件"}, 		CHAR_OVERLAPEDFUNC}
	,{{"戰後事件"}, 		CHAR_BATTLEOVERDFUNC}
#ifdef _ALLBLUES_LUA_1_4
	,{{"登出事件"}, 		CHAR_LOGINOUTFUNC}
#endif
#ifdef _ALLBLUES_LUA_1_9
	,{{"戰鬥設置事件"}, CHAR_BATTLESETFUNC}
#endif
}; 
	
static CharBase CharBaseColor[] = {
	{{"白色"}, 			CHAR_COLORWHITE}
	,{{"青色"}, 		CHAR_COLORCYAN}
	,{{"紫色"},			CHAR_COLORPURPLE}
	,{{"藍色"}, 		CHAR_COLORBLUE}
	,{{"黃色"}, 		CHAR_COLORYELLOW}
	,{{"綠色"}, 		CHAR_COLORGREEN}
	,{{"紅色"}, 		CHAR_COLORRED}
	,{{"灰白色"}, 	CHAR_COLORGRAY}
	,{{"灰藍色"}, 	CHAR_COLORBLUE2}
	,{{"灰綠色"}, 	CHAR_COLORGREEN2}
}; 

static CharBase CharBaseUpdata[] = {
	{{"HP"},						CHAR_P_STRING_HP}
	,{{"MAXHP"},				CHAR_P_STRING_MAXHP}
	,{{"MP"},						CHAR_P_STRING_MP}
	,{{"MAXMP"},				CHAR_P_STRING_MAXMP}
	,{{"體力"},					CHAR_P_STRING_VITAL}
	,{{"腕力"},					CHAR_P_STRING_STR}
	,{{"耐力"},					CHAR_P_STRING_TOUGH}
	,{{"速度"},					CHAR_P_STRING_DEX}
	,{{"經驗"},					CHAR_P_STRING_EXP}
	,{{"下一級經驗"},		CHAR_P_STRING_NEXTEXP}
	,{{"等級"},					CHAR_P_STRING_LV}
	,{{"攻擊力"},				CHAR_P_STRING_ATK}
	,{{"防禦力"},				CHAR_P_STRING_DEF}
	,{{"敏捷力"},				CHAR_P_STRING_QUICK}
	,{{"魅力"},					CHAR_P_STRING_CHARM}
	,{{"運氣"},					CHAR_P_STRING_LUCK}
	,{{"地"},						CHAR_P_STRING_EARTH}
	,{{"水"},						CHAR_P_STRING_WATER}
	,{{"火"},						CHAR_P_STRING_FIRE}
	,{{"風"},						CHAR_P_STRING_WIND}
	,{{"石幣"},					CHAR_P_STRING_GOLD}
	,{{"標題"},					CHAR_P_STRING_TITLE}
	,{{"DP"},						CHAR_P_STRING_DUELPOINT}
	,{{"轉數"},					CHAR_P_STRING_TRANSMIGRATION}
	,{{"名字"},					CHAR_P_STRING_NAME}
	,{{"昵稱"},					CHAR_P_STRING_OWNTITLE}
	,{{"騎寵"},					CHAR_P_STRING_RIDEPET}
	,{{"學騎"},					CHAR_P_STRING_LEARNRIDE}
	,{{"圖像"},					CHAR_P_STRING_BASEBASEIMAGENUMBER}
	,{{"天行者"},				CHAR_P_STRING_SKYWALKER}
	,{{"調試模式"},			CHAR_P_STRING_DEBUGMODE}
}; 

static CharBase CharBaseFlg[] = {
	{{"可見"}, 						CHAR_ISVISIBLE}
	,{{"透明"},       		CHAR_ISTRANSPARENT}
  ,{{"飛行"},       		CHAR_ISFLYING}
  ,{{"死亡"},       		CHAR_ISDIE}
  ,{{"組隊"},       		CHAR_ISPARTY}
  ,{{"決鬥"},       		CHAR_ISDUEL}
  ,{{"名片"},       		CHAR_ISTRADECARD}
  ,{{"交易"},       		CHAR_ISTRADE}
#ifdef _CHANNEL_MODIFY
  ,{{"密語頻道"},       CHAR_ISTELL}
  ,{{"家族頻道"},       CHAR_ISFM}
  ,{{"職業頻道"},       CHAR_ISOCC}
  ,{{"對話儲存"},       CHAR_ISSAVE}
  ,{{"聊天室"},       	CHAR_ISCHAT}
#ifdef _CHATROOMPROTOCOL
#ifdef _THE_WORLD_SEND
  ,{{"世界頻道"},       CHAR_ISWORLD}
#endif
#ifdef _ONLINE_TALK_IP
  ,{{"舉報頻道"},       CHAR_ISTALKIP}
#endif
#endif
#endif
	 ,{{"AI模式"},       CHAR_AI_MOD}
};

static CharBase CharBaseAction[] = {
	{{"站立"},					CHAR_ACTSTAND}
	,{{"走動"},					CHAR_ACTWALK}
	,{{"攻擊"},					CHAR_ACTATTACK}
	,{{"投擲"},					CHAR_ACTTHROW}
	,{{"受傷"},					CHAR_ACTDAMAGE}
	,{{"死亡"},					CHAR_ACTDEAD}
	,{{"魔法"},					CHAR_ACTMAGIC}
	,{{"道具"},					CHAR_ACTITEM}
	,{{"效果"},					CHAR_ACTEFFECT}
	,{{"下"},						CHAR_ACTDOWN}
	,{{"坐"},						CHAR_ACTSIT}
	,{{"揮手"},					CHAR_ACTHAND}
	,{{"高興"},					CHAR_ACTPLEASURE}
	,{{"發怒"},					CHAR_ACTANGRY}
	,{{"悲哀"},					CHAR_ACTSAD}
	,{{"防守"},					CHAR_ACTGUARD}
	,{{"走路"},					CHAR_ACTACTIONWALK}
	,{{"點頭"},					CHAR_ACTNOD}
	,{{"站立"},					CHAR_ACTACTIONSTAND}
	,{{"戰鬥"},					CHAR_ACTBATTLE}
	,{{"帶隊"},					CHAR_ACTLEADER}
	,{{"觀戰"},					CHAR_ACTBATTLEWATCH}
	,{{"未知"},					CHAR_ACTPOPUPNAME}
	,{{"鏇轉"},					CHAR_ACTTURN}
	,{{"變形"},					CHAR_ACTWARP}
	,{{"交易"},					CHAR_ACTTRADE}
#ifdef _ANGEL_SUMMON
	,{{"天使"},					CHAR_ACTANGEL}
#endif

#ifdef _MIND_ICON
	,{{"心思"},					CHAR_MIND}
#endif
#ifdef _STREET_VENDOR
	,{{"打開攤灘"},			CHAR_STREETVENDOR_OPEN}
	,{{"關閉攤灘"},			CHAR_STREETVENDOR_CLOSE}
#endif
};


static int getCharNum (lua_State *L) 
{
	lua_pushinteger(L, CHAR_getCharNum());

  return 1;
}

static int getPlayerMaxNum (lua_State *L) 
{
	lua_pushinteger(L, CHAR_getPlayerMaxNum());

  return 1;
}

static int getPetMaxNum (lua_State *L) 
{
	lua_pushinteger(L, CHAR_getPetMaxNum());

  return 1;
}

static int getOthersMaxNum (lua_State *L) 
{
	lua_pushinteger(L, CHAR_getOthersMaxNum());

  return 1;
}


static int check (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
	lua_pushinteger(L, CHAR_CHECKINDEX(index));

  return 1;
}

static int setFlg (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseFlg, arraysizeof(CharBaseFlg));
  const int data = luaL_checkint(L, 3);
  if(CHAR_setFlg(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getFlg (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseFlg, arraysizeof(CharBaseFlg));
  
	lua_pushinteger(L, CHAR_getFlg(index, element));
  return 1;
}

static int setWorkChar (lua_State *L) 
{
	size_t l;
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseWorkChar, arraysizeof(CharBaseWorkChar));
  char *data = luaL_checklstring(L, 3, &l);
  if(CHAR_setWorkChar(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getWorkChar (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseWorkChar, arraysizeof(CharBaseWorkChar));
  lua_pushstring(L, CHAR_getWorkChar(index, element));
  return 1;
}


static int setWorkInt (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseWorkInt, arraysizeof(CharBaseWorkInt));
  const int data = getCharBaseValue(L, 3, CharBaseWorkValue, arraysizeof(CharBaseWorkValue));
  if(CHAR_setWorkInt(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getWorkInt (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseWorkInt, arraysizeof(CharBaseWorkInt));
  lua_pushinteger(L, CHAR_getWorkInt(index, element));
  return 1;
}

static int setChar (lua_State *L) 
{
  size_t l;
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseChar, arraysizeof(CharBaseChar));
  char *data = luaL_checklstring(L, 3, &l);
  if(CHAR_setChar(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getChar (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseChar, arraysizeof(CharBaseChar));
  lua_pushstring(L, CHAR_getChar(index, element));
  return 1;
}

static int setInt (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseInt, arraysizeof(CharBaseInt));
  const int data = getCharBaseValue(L, 3, CharBaseValue, arraysizeof(CharBaseValue));
  if(CHAR_setInt(index, element, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int getInt (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int element = getCharBaseValue(L, 2, CharBaseInt, arraysizeof(CharBaseInt));
  lua_pushinteger(L, CHAR_getInt(index, element));
  return 1;
}

static int setFunctionPointer(lua_State *L) 
{
	size_t l;
	const int index = luaL_checkint(L, 1);
  const int functype = getCharBaseValue(L, 2, CharBaseEvent, arraysizeof(CharBaseEvent));
  char *luafunctable=luaL_checklstring(L, 3, &l);
	char *luafunctablepath=luaL_checklstring(L, 4, &l);
	if(strlen(luafunctablepath) > 0){
		MY_Lua *mylua = &MYLua;
	  while(mylua->next != NULL){
	  	if(strcmp(mylua->luapath, luafunctablepath) == 0){
				return CHAR_setLUAFunction( index, functype, mylua->lua, luafunctable );
	  	}
	  	mylua = mylua->next;
	  }
	}else{
		return CHAR_setLUAFunction( index, functype, L, luafunctable );
	}
	return 1;
}

static int delFunctionPointer(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
  const int functype = getCharBaseValue(L, 2, CharBaseEvent, arraysizeof(CharBaseEvent));

	return CHAR_delLUAFunction( index, functype );
}

static int TalkToCli(lua_State *L) 
{
	size_t l;
	const int talkedcharaindex = luaL_checkint(L, 1);
	const int talkcharaindex = luaL_checkint(L, 2);
	char *message=luaL_checklstring(L, 3, &l);
	const int color = getCharBaseValue(L, 4, CharBaseColor, arraysizeof(CharBaseColor));
	CHAR_talkToCli(talkedcharaindex, talkcharaindex, message, color);
	return 1;
}

static int TalkToRound(lua_State *L) 
{
	size_t l;
	const int talkedcharaindex = luaL_checkint(L, 1);
	char *message=luaL_checklstring(L, 2, &l);
	const int color = getCharBaseValue(L, 3, CharBaseColor, arraysizeof(CharBaseColor));

	int fl = CHAR_getInt( talkedcharaindex, CHAR_FLOOR) ;
	int x  = CHAR_getInt( talkedcharaindex, CHAR_X) ;
	int y  = CHAR_getInt( talkedcharaindex, CHAR_Y) ;
	
	int i,j;

	int range = 8;
	
	for( i=x-range ; i<=x+range ; i++ ){
		for( j=y-range ; j<=y+range ; j++ ){
			OBJECT  object;
			for( object = MAP_getTopObj( fl,i,j ) ; object ; object = NEXT_OBJECT(object) ){
				int objindex = GET_OBJINDEX(object);
				int	toindex = OBJECT_getIndex( objindex);
				if( OBJECT_getType(objindex) == OBJTYPE_CHARA && toindex != talkedcharaindex ){
					if( CHAR_getInt(toindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER){
						typedef void (*TALKF)(int,int,char*,int,int);
						TALKF   talkedfunc=NULL;
						talkedfunc = (TALKF)CHAR_getFunctionPointer( toindex, CHAR_TALKEDFUNC);
						if( talkedfunc ) {
							talkedfunc(toindex, talkedcharaindex, message, color, -1);
						}
					}
				}
			}
		}
	}

	return 1;
}

static int WalkPoint(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	if( CHAR_getWorkInt( index, CHAR_WORKBATTLEMODE ) != BATTLE_CHARMODE_NONE ) return 0;
	
	const int x = luaL_checkint(L, 2);
	const int y = luaL_checkint(L, 3);

	POINT	start, end;
	
	start.x = CHAR_getInt( index, CHAR_X);
	start.y = CHAR_getInt( index, CHAR_Y);
	
	end.x = x;
	end.y = y;

	int pos = NPC_Util_getDirFromTwoPoint( &start, &end);
	if( pos != - 1 ) {
		CHAR_walk( index, pos, 0);
	}
	return 1;
}

static int Walk(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	if( CHAR_getWorkInt( index, CHAR_WORKBATTLEMODE ) != BATTLE_CHARMODE_NONE ) return 0;
	
	const int dir = luaL_checkint(L, 2);
	const int step = luaL_checkint(L, 3);

	POINT	start, end;
	
	start.x = CHAR_getInt( index, CHAR_X);
	start.y = CHAR_getInt( index, CHAR_Y);
	
	end.x = start.x;
	end.y = start.y;
	switch(dir){
		case 0:
		{
			end.x = start.x - step;
			break;
		}
		case 1:
		{
			end.x = start.x + step;
			end.y = start.y - step;
			break;
		}
		case 2:
		{
			end.x = start.x + step;
			break;
		}
		case 3:
		{
			end.x = start.x + step;
			end.y = start.y + step;
			
			break;
		}
		case 4:
		{
			end.y = start.y + step;
			break;
		}
		case 5:
		{
			end.x = start.x - step;
			end.y = start.y + step;
			break;
		}
		case 6:
		{
			end.y = start.y - step;
			break;
		}
		case 7:
		{
			end.x = start.x - step;
			end.y = start.y - step;
			break;
		}
	}

	int pos = NPC_Util_getDirFromTwoPoint( &start, &end);
	if( dir != - 1 ) {
		CHAR_walk( index, pos, 0);
	}
	return 1;
}

static int BoundRandWalk(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	if( CHAR_getWorkInt( index, CHAR_WORKBATTLEMODE ) != BATTLE_CHARMODE_NONE ) return 0;
	
	const int minX = min(luaL_checkint(L, 2), luaL_checkint(L, 4));
	const int minY = min(luaL_checkint(L, 3), luaL_checkint(L, 5));
	const int maxX = max(luaL_checkint(L, 2), luaL_checkint(L, 4));
	const int maxY = max(luaL_checkint(L, 3), luaL_checkint(L, 5));
	
	POINT	start, end;
	int stepX = (rand() % 10) - 5;
	int stepY = (rand() % 10) - 5;
	
	start.x = CHAR_getInt( index, CHAR_X);
	start.y = CHAR_getInt( index, CHAR_Y);
	
	end.x = start.x + stepX;
	if(end.x>maxX)end.x=maxX;
	else if(end.x<minX)end.x=minX;
		
	end.y = start.y + stepY;
	if(end.y>maxY)end.y=maxY;
	else if(end.y<minY)end.y=minY;

	int dir = NPC_Util_getDirFromTwoPoint( &start, &end);

	if( dir != - 1 ) {
		CHAR_walk( index, dir, 0);
	}
	return 1;
}

 int RandRandWalk(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
	if( CHAR_getWorkInt( index, CHAR_WORKBATTLEMODE ) != BATTLE_CHARMODE_NONE ) return 0;

	POINT	start, end;
	int stepX = (rand() % 8) - 4;
	int stepY = (rand() % 8) - 4;
	
	start.x = CHAR_getInt( index, CHAR_X);
	start.y = CHAR_getInt( index, CHAR_Y);
	
	end.x = start.x + stepX;
	end.y = start.y + stepY;

	

	int dir = NPC_Util_getDirFromTwoPoint( &start, &end);
	if( dir != - 1 ) {
		CHAR_walk( index, dir, 0);
	}
	return 1;
}

 int ToAroundChar(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
	int objindex = CHAR_getWorkInt( index,CHAR_WORKOBJINDEX );
	CHAR_sendCToArroundCharacter( objindex);
	return 1;
}

static int talkToFloor(lua_State *L) 
{
	size_t l;
	const int floor = luaL_checkint(L, 1);
	const int talkindex = luaL_checkint(L, 2);
	char *message=luaL_checklstring(L, 3, &l);
	const int color = getCharBaseValue(L, 4, CharBaseColor, arraysizeof(CharBaseColor));
	CHAR_talkToFloor(floor, talkindex, message, color);
	return 1;
}

static int talkToParty(lua_State *L) 
{
	size_t l;
	const int talkedcharaindex = luaL_checkint(L, 1);
	const int talkcharaindex = luaL_checkint(L, 2);
	char *message=luaL_checklstring(L, 3, &l);
	const int color = getCharBaseValue(L, 4, CharBaseColor, arraysizeof(CharBaseColor));
	CHAR_talkToCliAndParty(talkedcharaindex, talkcharaindex, message, color);
	return 1;
}

static int talkToServer(lua_State *L) 
{
	size_t l;
	const int talkcharaindex = luaL_checkint(L, 1);
	char *message=luaL_checklstring(L, 2, &l);
	const int color = getCharBaseValue(L, 3, CharBaseColor, arraysizeof(CharBaseColor));
	
	CHAR_talkToAll( talkcharaindex, message, color);
	return 1;
}

#ifdef _MO_LUA_TALK_EX
static int talkToServerEx(lua_State *L)
{
	size_t l;
	const int talkcharaindex = luaL_checkint(L, 1);
	char *message=luaL_checklstring(L, 2, &l);
	const int color = getCharBaseValue(L, 3, CharBaseColor, arraysizeof(CharBaseColor));
	const int fontsize = luaL_checkint(L, 4);
	int i = 0;
	int playernum = CHAR_getPlayerMaxNum();
	for (i = 0; i < playernum; i++){
		if (CHAR_getCharUse(i) == FALSE) continue;
	  if ( !CHAR_CHECKINDEX( i ) )
	    continue;
			CHAR_talkToCliExt(i, talkcharaindex, message, color, fontsize);
	}

	return 1;
}

#endif
#ifdef _ALLBLUES_LUA_1_1
static int WarpToSpecificPoint(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int floor = luaL_checkint(L, 2);
	const int x = luaL_checkint(L, 3);
	const int y = luaL_checkint(L, 4);

	CHAR_warpToSpecificPoint( charaindex, floor, x, y );
	return 1;
}
static int MapAllWarp(lua_State *L) 
{
	const int oldfloor = luaL_checkint(L, 1);
	const int newfloor = luaL_checkint(L, 2);
	const int x = luaL_checkint(L, 3);
	const int y = luaL_checkint(L, 4);

	int     i;
  int     playernum = CHAR_getPlayerMaxNum();

  for( i = 0 ; i < playernum ; i++) {
    if( CHAR_getCharUse(i) == FALSE )continue;
    if( CHAR_getInt(i, CHAR_FLOOR) != oldfloor )continue;
		CHAR_warpToSpecificPoint( i, newfloor, x, y );
	}
	return 1;
}
#endif


#ifdef _ALLBLUES_LUA_1_3
 int createPet(lua_State *L)
{
	const int enemyid = luaL_checkint(L, 1);
	const int UpLevel = luaL_checkint(L, 2);
	
	int i;
	for( i = 0; i < ENEMY_getEnemyNum(); i ++ ) {
		if( ENEMY_getInt( i, ENEMY_ID) == enemyid) {
			break;
		}
	}
	if( i == ENEMY_getEnemyNum() ){
		lua_pushinteger(L, -1);
		return 1;
	}
	
	int petindex = ENEMY_createPet( i, -1, -1, -1, -1 );

	for( i = 0; i < UpLevel; i ++ ){
		CHAR_PetLevelUp( petindex );
		CHAR_PetAddVariableAi( petindex, AI_FIX_PETLEVELUP );
	}
	CHAR_setInt( petindex, CHAR_LV, CHAR_getInt( petindex, CHAR_LV) + UpLevel );
	CHAR_complianceParameter( petindex );
	CHAR_setInt( petindex, CHAR_HP, CHAR_getWorkInt( petindex, CHAR_WORKMAXHP ));
	
	CHAR_LoginBesideSetWorkInt( petindex, -1 );
	lua_pushinteger(L, petindex);
	
	return 1;
}

 int setCharPet(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
	const int petindex = luaL_checkint(L, 2);
	
	int havepetelement = CHAR_getCharPetElement( index);
  if( havepetelement > -1 ){
  	CHAR_setCharPet( index, havepetelement, petindex);
  	CHAR_setWorkInt( petindex, CHAR_WORKPLAYERINDEX, index);
  }
	
	lua_pushinteger(L, havepetelement);
	
	return 1;
}

 int getCharPet(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
	const int havepetid = luaL_checkint(L, 2);

	lua_pushinteger(L, CHAR_getCharPet( index, havepetid));
	
	return 1;
}

static int setCharPoolPet(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int petindex = luaL_checkint(L, 2);
	
	int havepetelement = CHAR_getCharPoolPetElement( index);
  if( havepetelement > -1 ){
  	CHAR_setCharPoolPet( index, havepetelement, petindex);
  	CHAR_setWorkInt( petindex, CHAR_WORKPLAYERINDEX, index);
  }
	
	lua_pushinteger(L, havepetelement);
	
	return 1;
}

static int getCharPoolPet(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int havepetid = luaL_checkint(L, 2);

	lua_pushinteger(L, CHAR_getCharPoolPet( index, havepetid));
	
	return 1;
}

static int AB_WriteShopData(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	size_t l;
  	const char *data = luaL_checklstring(L, 2, &l);
	WriteShopData(data,index);
	return 1;
}

static int setDepotPetIndex(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int petindex = luaL_checkint(L, 2);
	
	int havepetelement = CHAR_getCharPoolPetElement( index);
  if( havepetelement > -1 ){
  	CHAR_setDepotPetIndex( index, havepetelement, petindex);
  	CHAR_setWorkInt( petindex, CHAR_WORKPLAYERINDEX, index);
  }
	
	lua_pushinteger(L, havepetelement);
	
	return 1;
}

static int getDepotPetIndex(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int havepetid = luaL_checkint(L, 2);

	lua_pushinteger(L, CHAR_getDepotPetIndex( index, havepetid));
	
	return 1;
}

static int DelItem(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int itemindex = luaL_checkint(L, 2);
	
	CHAR_DelItem( charaindex, itemindex);

	return 1;
}

static int getFd(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);

	lua_pushinteger(L, getfdFromCharaIndex(charaindex));
	return 1;
}

static int Updata(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int indextable = getCharBaseValue(L, 2, CharBaseUpdata, arraysizeof(CharBaseUpdata));

	CHAR_send_P_StatusString( charaindex , indextable);
	return 1;
}

static int Additem(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int itemid = luaL_checkint(L, 2);
	int itemindex = -1;
	int emptyitemindexinchara = CHAR_findEmptyItemBox( charaindex );
	
	if( emptyitemindexinchara >= 0 ){
		itemindex = ITEM_makeItemAndRegist( itemid );
		
		if( itemindex > -1 ){
	  	CHAR_setItemIndex( charaindex, emptyitemindexinchara, itemindex );
	  	ITEM_setWorkInt(itemindex, ITEM_WORKOBJINDEX, -1);
	  	ITEM_setWorkInt(itemindex, ITEM_WORKCHARAINDEX, charaindex);
	  	CHAR_sendItemDataOne( charaindex, emptyitemindexinchara);
			LogItem(
				CHAR_getChar( charaindex, CHAR_NAME ),
				CHAR_getChar( charaindex, CHAR_CDKEY ),
#ifdef _add_item_log_name  // WON ADD 在item的log中增加item名稱
				itemindex,
#else
				atoi( message),
#endif
				"AddItem(製作道具LUA)",
		      CHAR_getInt( charaindex,CHAR_FLOOR),
					CHAR_getInt( charaindex,CHAR_X ),
		      CHAR_getInt( charaindex,CHAR_Y ),
		      ITEM_getChar( itemindex, ITEM_UNIQUECODE),
					ITEM_getChar( itemindex, ITEM_NAME),
					ITEM_getInt( itemindex, ITEM_ID)
		
			);
		}
	}
	lua_pushinteger(L, itemindex);
	return 1;
}
#ifdef _NEW_ITEM_
extern int CheckCharMaxItem(int charindex);
#endif
static int Finditem(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int itemid = luaL_checkint(L, 2);
	int i;
	int itemindex=-1;
	int id;
	for( i=CHAR_STARTITEMARRAY;i<CheckCharMaxItem(charaindex);i++ ){
		itemindex = CHAR_getItemIndex( charaindex , i );
		if( ITEM_CHECKINDEX( itemindex) )	{
			id=ITEM_getInt(itemindex ,ITEM_ID );
			if(id == itemid){
				lua_pushinteger(L, itemindex);
				return 1;
			}
		}
	}
	lua_pushinteger(L, -1);
	return 1;
}

static int AddPet(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int enemyid = luaL_checkint(L, 2);
	const int UpLevel = luaL_checkint(L, 3);
	
	int i, havepetelement;
	for( i = 0; i < ENEMY_getEnemyNum(); i ++ ) {
		if( ENEMY_getInt( i, ENEMY_ID) == enemyid) {
			break;
		}
	}
	if( i == ENEMY_getEnemyNum() ){
		lua_pushinteger(L, -1);
		return 1;
	}
	
	for( havepetelement = 0; havepetelement < CHAR_MAXPETHAVE; havepetelement ++ ){
		int petindex = CHAR_getCharPet(index, havepetelement);
		if( !CHAR_CHECKINDEX(petindex))break;
	}
	
	if( havepetelement == CHAR_MAXPETHAVE ){
		lua_pushinteger(L, -1);
		return 1;
	}

	int petindex = ENEMY_createPet( i, -1, -1, -1, -1 );
	if( !CHAR_CHECKINDEX(petindex)){
		lua_pushinteger(L, -1);
		return 1;
	}
		
	for( i = CHAR_getInt( petindex, CHAR_LV ); i < UpLevel; i ++ ){
		CHAR_PetLevelUp( petindex );
		CHAR_PetAddVariableAi( petindex, AI_FIX_PETLEVELUP );
		CHAR_setInt( petindex, CHAR_LV, CHAR_getInt( petindex, CHAR_LV) + 1 );
	}
	
	CHAR_setCharPet( index, havepetelement, petindex);
	
	CHAR_setWorkInt( petindex, CHAR_WORKPLAYERINDEX, index);
	
	char token[64];
	CHAR_setInt(petindex,CHAR_VARIABLEAI,10000);
	CHAR_complianceParameter( petindex );
	CHAR_setInt( petindex, CHAR_HP, CHAR_getWorkInt( petindex, CHAR_WORKMAXHP ));

	snprintf( token, sizeof( token ), "K%d", havepetelement );
	CHAR_sendStatusString( index, token );
	snprintf( token, sizeof( token ), "W%d", havepetelement );
	CHAR_sendStatusString( index, token );
	
	LogPet(
			CHAR_getChar( index, CHAR_NAME ),
			CHAR_getChar( index, CHAR_CDKEY ),
			CHAR_getChar( petindex, CHAR_NAME),
			CHAR_getInt( petindex, CHAR_LV),
			"來至LUA的char.AddPet",
			CHAR_getInt( index,CHAR_FLOOR),
			CHAR_getInt( index,CHAR_X ),
			CHAR_getInt( index,CHAR_Y ),
			CHAR_getChar( petindex, CHAR_UNIQUECODE)   // shan 2001/12/14
	);
	
	lua_pushinteger(L, petindex);
	
	return 1;
}

static int AddPetCf(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int enemyid = luaL_checkint(L, 2);
	const int UpLevel = luaL_checkint(L, 3);
	const int trn = luaL_checkint(L, 4);
	const int vital = luaL_checkint(L, 5);
	const int str = luaL_checkint(L, 6);
	const int tgh = luaL_checkint(L, 7);
	const int dex = luaL_checkint(L, 8);
	
	int i, havepetelement;
	for( i = 0; i < ENEMY_getEnemyNum(); i ++ ) {
		if( ENEMY_getInt( i, ENEMY_ID) == enemyid) {
			break;
		}
	}
	if( i == ENEMY_getEnemyNum() ){
		lua_pushinteger(L, -1);
		return 1;
	}
	
	for( havepetelement = 0; havepetelement < CHAR_MAXPETHAVE; havepetelement ++ ){
		int petindex = CHAR_getCharPet(index, havepetelement);
		if( !CHAR_CHECKINDEX(petindex))break;
	}
	
	if( havepetelement == CHAR_MAXPETHAVE ){
		lua_pushinteger(L, -1);
		return 1;
	}

	int petindex = ENEMY_createPet( i, vital, str, tgh, dex );
	if( !CHAR_CHECKINDEX(petindex)){
		lua_pushinteger(L, -1);
		return 1;
	}

	for( i = CHAR_getInt( petindex, CHAR_LV ); i < UpLevel; i ++ ){
		CHAR_PetLevelUp( petindex );
		CHAR_PetAddVariableAi( petindex, AI_FIX_PETLEVELUP );
		CHAR_setInt( petindex, CHAR_LV, CHAR_getInt( petindex, CHAR_LV) + 1 );
		
	}
	CHAR_setInt( petindex, CHAR_TRANSMIGRATION, trn );
	
	CHAR_setCharPet( index, havepetelement, petindex);
		
//	CHAR_setChar( petindex, CHAR_OWNERCDKEY, CHAR_getChar( index, CHAR_CDKEY));
//	CHAR_setChar( petindex, CHAR_OWNERCHARANAME, CHAR_getChar( index, CHAR_NAME));
		
	CHAR_setWorkInt( petindex, CHAR_WORKPLAYERINDEX, index);
		
	char token[64];

	CHAR_setInt(petindex,CHAR_VARIABLEAI,10000);
	CHAR_complianceParameter( petindex );
	
	CHAR_setInt( petindex, CHAR_HP, CHAR_getWorkInt( petindex, CHAR_WORKMAXHP ));
	
	snprintf( token, sizeof( token ), "K%d", havepetelement );
	CHAR_sendStatusString( index, token );
	snprintf( token, sizeof( token ), "W%d", havepetelement );
	CHAR_sendStatusString( index, token );
	
	LogPet(
			CHAR_getChar( index, CHAR_NAME ),
			CHAR_getChar( index, CHAR_CDKEY ),
			CHAR_getChar( petindex, CHAR_NAME),
			CHAR_getInt( petindex, CHAR_LV),
			"來至LUA的char.AddPetCf",
			CHAR_getInt( index,CHAR_FLOOR),
			CHAR_getInt( index,CHAR_X ),
			CHAR_getInt( index,CHAR_Y ),
			CHAR_getChar( petindex, CHAR_UNIQUECODE)   // shan 2001/12/14
	);
	
	lua_pushinteger(L, petindex);
	
	return 1;
}

#ifdef _PLAYER_NPC
static int setPlayerNpc(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int petindex = luaL_checkint(L, 2);
	int i;
	for( i = 1; i < getPartyNum(charaindex); i ++ ) {
		if( CHAR_getWorkInt( charaindex, i + CHAR_WORKPARTYINDEX1) == -1 ) {
			break;
		}
	}
	if(i == getPartyNum(charaindex)){
		CHAR_endCharOneArray( petindex );
	}else{
		if(CHAR_CHECKINDEX(petindex) == TRUE){
			Object object;
			int objindex;
		
			CHAR_setInt(petindex, CHAR_FLOOR, CHAR_getInt(charaindex, CHAR_FLOOR));
			CHAR_setInt(petindex, CHAR_X, CHAR_getInt(charaindex, CHAR_X));
			CHAR_setInt(petindex, CHAR_Y, CHAR_getInt(charaindex, CHAR_Y));
					
			object.type = OBJTYPE_CHARA;
			object.index = petindex;
			object.x =CHAR_getInt(petindex, CHAR_X);
			object.y = CHAR_getInt(petindex, CHAR_Y);
			object.floor = CHAR_getInt(petindex, CHAR_FLOOR);
			
			objindex = initObjectOne( &object );
			
			if( objindex == -1 ) {
			   CHAR_endCharOneArray( petindex );
			} else {
				CHAR_setWorkInt( petindex,CHAR_WORKOBJINDEX, objindex );
				if(CHAR_JoinParty_Main(petindex, charaindex) == FALSE){
					CHAR_CharaDelete( petindex );
					return 1;
				}
			  
			  CHAR_sendCToArroundCharacter( objindex);
			}
		}
	}
	return 1;
}
#endif
#endif
#ifdef _PETSKILL_SHOP_LUA   
static int FreePetSkill(lua_State *L) 
{
	const int petindex = luaL_checkint(L, 1);
	const int petskill = luaL_checkint(L, 2);
	
	int i;
	for( i=0; i < CHAR_MAXPETSKILLHAVE; i++)	{
		if( petskill == CHAR_getPetSkill( petindex, i) )	{
			lua_pushinteger(L, 1);
			return 1;
		}
	}
	lua_pushinteger(L, 0);
	return 1;
}
#endif

static int Coordinate(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	if( CHAR_getWorkInt( index, CHAR_WORKBATTLEMODE ) != BATTLE_CHARMODE_NONE ) return 0;
	
	const int X = luaL_checkint(L, 2);
	const int Y = luaL_checkint(L, 3);
	
	POINT	start, end;

	start.x = CHAR_getInt( index, CHAR_X);
	start.y = CHAR_getInt( index, CHAR_Y);
	
	end.x = X;
	end.y = Y;

	int dir = NPC_Util_getDirFromTwoPoint( &start, &end);

	if( dir != - 1 ) {
		CHAR_walk( index, dir, 0);
	}
	return 1;
}

static int setPetSkill(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int havepetskillindex = luaL_checkint(L, 2);
	const int skillID = luaL_checkint(L, 3);
	
	CHAR_setPetSkill( index, havepetskillindex, skillID);
	
	return 1;
}

static int getPetSkill(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	const int havepetskillindex = luaL_checkint(L, 2);
	
	lua_pushinteger(L, CHAR_getPetSkill( index, havepetskillindex));

	return 1;
}


static int PetLevelUp(lua_State *L) 
{
	const int index = luaL_checkint(L, 1);
	
	CHAR_PetLevelUp( index );
	
	return 1;
}

static int JoinParty(lua_State *L) 
{
	const int index1 = luaL_checkint(L, 1);
	const int index2 = luaL_checkint(L, 2);
	int TM_Top = lua_gettop(L);
	if(TM_Top==2) CHAR_JoinParty_Main(index2, index1);
	else{
		const int flg = luaL_checkint(L, 3);
		CHAR_JoinParty_Main_New(index2, index1,flg);
	}
	return 1;
}

#ifdef _ALLBLUES_LUA_1_4
static int getRightTo8(lua_State *L)
{
	const int value = luaL_checkint(L, 1);
	const int flg = luaL_checkint(L, 2);
	
	lua_pushinteger(L, (value >> (4 - flg) * 8) & 0xFF);

	return 1;
}

static int getLiftTo8(lua_State *L)
{
	const int value = luaL_checkint(L, 1);
	const int flg = luaL_checkint(L, 2);
	
	lua_pushinteger(L, (value << (4 - flg) * 8));

	return 1;
}

static int complianceParameter(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
	
	CHAR_complianceParameter(index);

	return 1;
}


static int sendStatusString(lua_State *L)
{
	size_t l;
	const int index = luaL_checkint(L, 1);
  char *data=luaL_checklstring(L, 2, &l);

	CHAR_sendStatusString( index, data );

	return 1;
}

static int sendBattleEffect(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
  const int val = luaL_checkint(L, 2);

	CHAR_sendBattleEffect( index, val );

	return 1;
}

static int sendWatchEvent(lua_State *L)
{
	const int objindex = luaL_checkint(L, 1);
	const int action = getCharBaseValue(L, 2, CharBaseAction, arraysizeof(CharBaseAction));
	const int flg = luaL_checkint(L, 3);

	luaL_checktype(L, 4, LUA_TTABLE);
	int n = luaL_getn(L, 4);
	int *opt =  (int *) malloc(n * sizeof(int));
	int i;

	for(i = 0; i < n; i++){
		opt[i] = getArrayInt(L, i);
	}

	CHAR_sendWatchEvent( objindex,	action, opt, n, flg);

	return 1;
}

static int dropPetAbsolute(lua_State *L)
{
	const int index = luaL_checkint(L, 1);
  const int fl = luaL_checkint(L, 2);
  const int fx = luaL_checkint(L, 3);
  const int fy = luaL_checkint(L, 4);
  const int dir = luaL_checkint(L, 5);
  const int val = luaL_checkint(L, 6);
	int dirx[9],diry[9];
	int floor, x, y, i;

	for( i  = 0 ; i < 7 ; i  ++ ){
	    dirx[i+2] = CHAR_getDX(dir + i+1);
	    diry[i+2] = CHAR_getDY(dir + i+1);
	}
	dirx[0] = CHAR_getDX(dir);
	diry[0] = CHAR_getDY(dir);
	dirx[1] = 0;
	diry[1] = 0;
	floor = fl;
	for( i = 0 ; i < 9 ; i ++ ){
	    int x=fx+dirx[i];
	    int y=fy+diry[i];
	    if( PET_isPutPoint( floor, x, y ) == TRUE ) {
	        break;
	    }
	}
	if( i == 9 ) i = 1;
	x = fx+dirx[i];
	y = fy+diry[i];

	int objindex = PET_dropPetAbsolute( index, floor, x, y, val );

	if( objindex == -1 ){
		return 1;
	}

	CHAR_setWorkInt( index, CHAR_WORKOBJINDEX, objindex );
	CHAR_setInt( index, CHAR_FLOOR, floor);
	CHAR_setInt( index, CHAR_X, x);
	CHAR_setInt( index, CHAR_Y, y);
	CHAR_setInt( index, CHAR_PUTPETTIME, NowTime.tv_sec);

	CHAR_sendCToArroundCharacter( objindex);

	return 1;
}

static int AllWarpToSpecificPoint(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int floor = luaL_checkint(L, 2);
	const int x = luaL_checkint(L, 3);
	const int y = luaL_checkint(L, 4);

	if( CHAR_getWorkInt( charaindex, CHAR_WORKPARTYMODE ) == CHAR_PARTY_LEADER ){
		int i;
		for( i = 0; i <  getPartyNum(charaindex); i ++ ){
			int subindex = CHAR_getWorkInt( charaindex, CHAR_WORKPARTYINDEX1+i );
			if( CHAR_CHECKINDEX( subindex ) == FALSE ) continue;
			CHAR_warpToSpecificPoint( subindex, floor, x, y );
			ITEM_WarpDelErrorItem( subindex );
		}
	}else if( CHAR_getWorkInt( charaindex, CHAR_WORKPARTYMODE ) == CHAR_PARTY_CLIENT ){
		CHAR_talkToCli(charaindex, -1, "隊員無法使用。", CHAR_COLORYELLOW);
		return FALSE;
	}else if( CHAR_getWorkInt( charaindex, CHAR_WORKPARTYMODE ) == CHAR_PARTY_NONE ){
		ITEM_WarpDelErrorItem( charaindex );
		CHAR_warpToSpecificPoint( charaindex, floor, x, y );
	}


	return 1;
}

static int Findpet(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int petid = luaL_checkint(L, 2);
	const int lv = luaL_checkint(L, 3);
	int i;
	
	for( i = 0; i < CHAR_MAXPETHAVE; i ++ ){
		int petindex = CHAR_getCharPet( charaindex, i );
		if(!CHAR_CHECKINDEX( petindex))continue;
		if( CHAR_getInt(petindex, CHAR_PETID) == petid ){
			if(lv > 0){
				if( CHAR_getInt(petindex, CHAR_LV) != lv){
					continue;
				}
			}
			lua_pushinteger(L, petindex);
			return 1;
		}
	}

	lua_pushinteger(L, -1);
	return 1;
}

static int FindPetFormMatemo(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int metamo = luaL_checkint(L, 2);
	const int lv = luaL_checkint(L, 3);
	int i;
	
	for( i = 0; i < CHAR_MAXPETHAVE; i ++ ){
		int petindex = CHAR_getCharPet( charaindex, i );
		if(!CHAR_CHECKINDEX( petindex))continue;
		if( CHAR_getInt(petindex, CHAR_BASEBASEIMAGENUMBER) == metamo ){
			if(lv > 0){
				if( CHAR_getInt(petindex, CHAR_LV) != lv){
					continue;
				}
			}
			lua_pushinteger(L, petindex);
			return 1;
		}
	}

	lua_pushinteger(L, -1);
	return 1;
}

static int FindPetFormEnemyTempID(lua_State *L) 
{
	size_t l;
	const int charaindex = luaL_checkint(L, 1);
	char *data=luaL_checklstring(L, 2, &l);
	char token[64];
	int enemytempid = -1, lv = 0;
	int i;
	
	if(getStringFromIndexWithDelim(data, "-", 1, token, sizeof(token)) == TRUE){
		lv = atoi(token);
	}else{
		lua_pushinteger(L, -1);
	}
	
	if(getStringFromIndexWithDelim(data, "-", 2, token, sizeof(token)) == TRUE){
		enemytempid = atoi(token);
	}else{
		lua_pushinteger(L, -1);
	}

	for( i = 0; i < CHAR_MAXPETHAVE; i ++ ){
		int petindex = CHAR_getCharPet( charaindex, i );
		if(!CHAR_CHECKINDEX( petindex))continue;

		if( CHAR_getInt( petindex, CHAR_PETID) == enemytempid ){
			if(lv > 0){
				if( CHAR_getInt(petindex, CHAR_LV) != lv){
					continue;
				}
			}
			lua_pushinteger(L, petindex);
			return 1;
		}
	}

	lua_pushinteger(L, -1);
	return 1;
}

static int CharaDeleteHavePet(lua_State *L)
{
	const int charaindex = luaL_checkint(L, 1);
	CHAR_CharaDeleteHavePet( charaindex);
	return 1;
}


static int DelPet(lua_State *L)
{
	const int charaindex = luaL_checkint(L, 1);
	const int petindex = luaL_checkint(L, 2);
	int i;
	char category[12];

	for( i = 0; i < CHAR_MAXPETHAVE; i ++ ){
		if( petindex == CHAR_getCharPet( charaindex, i ) ){
			if( CHAR_getInt( charaindex, CHAR_RIDEPET) == i ) {
				CHAR_setInt( charaindex, CHAR_RIDEPET, -1);
				CHAR_send_P_StatusString( charaindex, CHAR_P_STRING_RIDEPET );
				CHAR_complianceParameter( charaindex );
				CHAR_sendCToArroundCharacter( CHAR_getWorkInt( charaindex , CHAR_WORKOBJINDEX ));
			}
	    LogPet( CHAR_getChar( charaindex, CHAR_NAME ), // 平乓仿
		                CHAR_getChar( charaindex, CHAR_CDKEY ),
		                CHAR_getChar( petindex, CHAR_NAME),
		                CHAR_getInt( petindex, CHAR_LV),
		                "EvnetDell(LUA任務刪除)",
		                CHAR_getInt( charaindex,CHAR_FLOOR),
		                CHAR_getInt( charaindex,CHAR_X ),
		                CHAR_getInt( charaindex,CHAR_Y ),
		                CHAR_getChar( petindex, CHAR_UNIQUECODE)   // shan 2001/12/14
	    );

			CHAR_endCharOneArray( petindex );
			CHAR_setCharPet( charaindex, i, -1);
			snprintf( category, sizeof( category), "K%d",i);
			CHAR_sendStatusString( charaindex, category );
			break;
		}
	}
	return 1;
}

#endif



#ifdef _ALLBLUES_LUA_1_7
static int findEmptyItemBox(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);

	lua_pushinteger(L, CHAR_findEmptyItemBox(charaindex));
	return 1;
}

static int findEmptyPetBox(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	int num = 0;
	int i;
	for( i = 0; i < CHAR_MAXPETHAVE; i ++ ){
		int petindex = CHAR_getCharPet( charaindex, i );
		if(!CHAR_CHECKINDEX(petindex)){
			num ++ ;
		}
	}
	lua_pushinteger(L, num);
	return 1;
}

static int dropPetFollow(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int havepetindex = luaL_checkint(L, 2);
	char szPet[128];
    int dirx[9],diry[9];
    int i;
    int objindex=-1;
    int floor,x,y;
    int petindex;

	if( CHAR_getWorkInt( charaindex, CHAR_WORKBATTLEMODE)
		!= BATTLE_CHARMODE_NONE) return FALSE;
    petindex = CHAR_getCharPet(charaindex,havepetindex);
    if( petindex == -1  ) return FALSE;
    if( !CHAR_CHECKINDEX( charaindex ) )return FALSE;
    if( CHAR_CHECKINDEX( petindex) == FALSE ) return FALSE;

	if (CHAR_getInt(petindex, CHAR_PETFAMILY) == 1){
     	CHAR_talkToCli(charaindex, -1, "家族守護獸無法丟出！", CHAR_COLORYELLOW);
    	return	FALSE;  
  }
  if (CHAR_getInt(charaindex, CHAR_RIDEPET) == havepetindex){
  	CHAR_talkToCli(charaindex, -1, "騎乘中的寵物無法跟隨！", CHAR_COLORYELLOW);
  	return	FALSE;
  }

	for( i  = 0 ; i < 7 ; i  ++ ){
	    dirx[i+2] = CHAR_getDX(CHAR_getInt(charaindex,CHAR_DIR) + i+1);
	    diry[i+2] = CHAR_getDY(CHAR_getInt(charaindex,CHAR_DIR) + i+1);
	}
	dirx[0] = CHAR_getDX(CHAR_getInt(charaindex,CHAR_DIR));
	diry[0] = CHAR_getDY(CHAR_getInt(charaindex,CHAR_DIR));
	dirx[1] = 0;
	diry[1] = 0;

	floor = CHAR_getInt( charaindex,CHAR_FLOOR );
	for( i = 0 ; i < 9 ; i ++ ){
	    int x=CHAR_getInt(charaindex,CHAR_X)+dirx[i];
	    int y=CHAR_getInt(charaindex,CHAR_Y)+diry[i];
	    if( PET_isPutPoint( floor, x, y ) == TRUE ) {
	        break;
	    }
	}
	if( i == 9 ) i = 1;

	x=CHAR_getInt(charaindex,CHAR_X)+dirx[i];
	y=CHAR_getInt(charaindex,CHAR_Y)+diry[i];

  objindex = PET_dropPetAbsolute( petindex,floor,x,y, FALSE );
  if( objindex == -1 ) return FALSE;
  
  CHAR_setWorkInt( petindex,CHAR_WORKOBJINDEX,objindex );
  CHAR_setCharPet( charaindex, havepetindex, -1);
	CHAR_setInt( petindex, CHAR_FLOOR, floor);
	CHAR_setInt( petindex, CHAR_X, x);
	CHAR_setInt( petindex, CHAR_Y, y);
	CHAR_setInt( petindex, CHAR_PUTPETTIME, NowTime.tv_sec);
	if( havepetindex == CHAR_getInt( charaindex, CHAR_DEFAULTPET)) {
		int	fd;
		CHAR_setInt( charaindex, CHAR_DEFAULTPET, -1);
	    fd = getfdFromCharaIndex( charaindex);
		lssproto_KS_send( fd, havepetindex, 0);

	}
	CHAR_sendCToArroundCharacter( objindex);
  if( CHAR_getInt( charaindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER){
#ifdef _PET_ITEM
		CHAR_sendPetItemData( charaindex, havepetindex);
#endif		
		snprintf( szPet, sizeof( szPet ), "K%d", havepetindex );
		CHAR_sendStatusString( charaindex, szPet );
  }

	CHAR_setWorkInt( charaindex, CHAR_WORKPETFOLLOW, petindex);
	CHAR_setWorkInt( petindex, CHAR_WORKPETFOLLOWMODE, CHAR_PETFOLLOW_NOW);
	CHAR_setWorkInt( petindex, CHAR_WORKPETFOLLOWCOUNT, 0);
	CHAR_setInt( petindex, CHAR_PUTPETTIME, (int)(NowTime.tv_sec));
	CHAR_setInt( petindex, CHAR_WORKPLAYERINDEX, charaindex);
	LogPet(
		CHAR_getChar( charaindex, CHAR_NAME ),
		CHAR_getChar( charaindex, CHAR_CDKEY ),
		CHAR_getChar( petindex, CHAR_NAME),
		CHAR_getInt( petindex, CHAR_LV),
		"Follow(lua溜寵)",
		CHAR_getInt( charaindex,CHAR_FLOOR),
		CHAR_getInt( charaindex,CHAR_X ),
		CHAR_getInt( charaindex,CHAR_Y ),
		CHAR_getChar( petindex, CHAR_UNIQUECODE)
	);
    return 1;
}

static int getItemIndex(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int haveitemindex = luaL_checkint(L, 2);
	
	lua_pushinteger(L, CHAR_getItemIndex( charaindex, haveitemindex ));
	return 1;
	
}

static int charSaveFromConnect(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	if( CHAR_getCharUse(charaindex) != FALSE ){
		CHAR_charSaveFromConnect( charaindex, FALSE );
   }
	return 1;
}

#ifdef _RECORD_IP
static int userip(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);

	unsigned long ip;
	int a,b,c,d;
	char strIP[32];
	
  ip = CHAR_getWorkInt(charaindex, CHAR_WORK_RECORD_IP);
  
  a=(ip % 0x100); ip=ip / 0x100;
  b=(ip % 0x100); ip=ip / 0x100;
  c=(ip % 0x100); ip=ip / 0x100;
  d=(ip % 0x100);
  
	sprintf(strIP, "%d.%d.%d.%d", a, b, c, d);

	lua_pushstring(L, strIP);
	return 1;
}
#endif

static int DischargeParty(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int flg = luaL_checkint(L, 2);
	CHAR_DischargeParty_New(charaindex, flg);
	return 1;
}


static int Skillupsend(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	
	CHAR_Skillupsend(charaindex);
	return 1;
}
#endif

#ifdef _ALLBLUES_LUA_1_9
static int logou(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	
	CHAR_logout(charaindex, TRUE);
	return 1;
}
 int copyChar(lua_State *L)
{
	const int fromindex = luaL_checkint(L, 1);
	const int toindex = luaL_checkint(L, 2);

	if( !CHAR_CHECKINDEX( fromindex) )return 1;
	if( !CHAR_CHECKINDEX( toindex) )return 1;

	CHAR_setInt(toindex, CHAR_BASEIMAGENUMBER, CHAR_getInt(fromindex, CHAR_BASEIMAGENUMBER));
	CHAR_setInt(toindex, CHAR_BASEBASEIMAGENUMBER, CHAR_getInt(fromindex, CHAR_BASEBASEIMAGENUMBER));
	CHAR_setInt(toindex, CHAR_TRANSMIGRATION, CHAR_getInt(fromindex, CHAR_TRANSMIGRATION));
	CHAR_setInt(toindex, CHAR_LV, CHAR_getInt(fromindex, CHAR_LV));
	CHAR_setInt(toindex, CHAR_HP, CHAR_getInt(fromindex, CHAR_HP));
	CHAR_setInt(toindex, CHAR_MP, CHAR_getInt(fromindex, CHAR_MP));
	CHAR_setInt(toindex, CHAR_MAXMP, CHAR_getInt(fromindex, CHAR_MAXMP));
	CHAR_setInt(toindex, CHAR_VITAL, CHAR_getInt(fromindex, CHAR_VITAL));
	CHAR_setInt(toindex, CHAR_STR, CHAR_getInt(fromindex, CHAR_STR));
	CHAR_setInt(toindex, CHAR_TOUGH, CHAR_getInt(fromindex, CHAR_TOUGH));
	CHAR_setInt(toindex, CHAR_DEX, CHAR_getInt(fromindex, CHAR_DEX));
	CHAR_setInt(toindex, CHAR_ALLOCPOINT, CHAR_getInt(fromindex, CHAR_ALLOCPOINT));
	CHAR_setInt(toindex, CHAR_PETRANK, CHAR_getInt(fromindex, CHAR_PETRANK));
	CHAR_setInt(toindex, CHAR_LIMITLEVEL, CHAR_getInt(fromindex, CHAR_LIMITLEVEL));
	CHAR_setChar(toindex, CHAR_NAME, CHAR_getChar(fromindex, CHAR_NAME));
	CHAR_setChar(toindex, CHAR_OWNTITLE, CHAR_getChar(fromindex, CHAR_OWNTITLE));

	CHAR_complianceParameter(toindex);
	
	return 1;
}

 int talkToAllServer(lua_State *L)
{
	size_t l;
	char *message=luaL_checklstring(L, 1, &l);
	saacproto_AllServSend_send(message);
	return 1;
}

#endif

static int earnFame(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int num = luaL_checkint(L, 2);
	CHAR_earnFame(charaindex, num);
	return 1;
}

static int Encounter(lua_State *L)
{
	const int charaindex = luaL_checkint(L, 1);
	if(CHAR_CHECKINDEX(charaindex) == FALSE) return 0;
	int fd=CHAR_getWorkInt( charaindex, CHAR_WORKFD);
	setStayEncount(fd);
#ifdef _USER_CHARLOOPS
	{
		Char 	*ch;
		ch  = CHAR_getCharPointer( charaindex);
		if( ch == NULL ) return 0;
		strcpysafe( ch->charfunctable[CHAR_LOOPFUNCTEMP1].string,
			sizeof( ch->charfunctable[CHAR_LOOPFUNCTEMP1]), "CHAR_BattleStayLoop");//戰鬥
		CHAR_setInt( charaindex, CHAR_LOOPINTERVAL, 2500);
		CHAR_constructFunctable( charaindex);
	}
#endif
}


static int ClearEncounter(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	if(CHAR_CHECKINDEX(charaindex) == FALSE) return 0;
	int fd=CHAR_getWorkInt( charaindex, CHAR_WORKFD);
	clearStayEncount(fd);
	return 1;
}



static int getDX(lua_State *L) 
{
	size_t l;
	char *diy=luaL_checklstring(L, 1, &l);
	
	lua_pushinteger(L, CHAR_getDX(diy));
	return 1;
}

static int getDY(lua_State *L) 
{
	size_t l;
	char *dir=luaL_checklstring(L, 1, &l);
	
	lua_pushinteger(L, CHAR_getDY(dir));
	return 1;
}

static int sendAction(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	const int actionno = luaL_checkint(L, 2);
	const int flg = luaL_checkint(L, 3);
	CHAR_sendAction( charaindex, actionno, flg);
	return 1;
}
#ifdef _NEW_ITEM_
extern int CheckCharMaxItem(int charindex);
#endif

static int GetEmptyItemBoxNum(lua_State *_NLL) 
{
	const int TM_CharIndex = luaL_checkint(_NLL, 1);

	if(!CHAR_CHECKINDEX(TM_CharIndex))
	{
		lua_pushinteger(_NLL, -1);
		return 0;
	}

	int i = CHAR_EQUIPPLACENUM ;
	int EmptyNum = 0;
#ifdef _NEW_ITEM_
	int itemMax = CheckCharMaxItem(TM_CharIndex);
	for( ; i <itemMax; i++){
#else
		for( ; i <CHAR_MAXITEMHAVE; i++){
#endif
		if( CHAR_getItemIndex( TM_CharIndex,i) == -1 ) EmptyNum++;
	}
	lua_pushinteger(_NLL, EmptyNum);
}


static int GetOldLevelExp(lua_State *L) 
{
	const int level = luaL_checkint(L, 1);
	lua_pushinteger(L, CHAR_GetOldLevelExp( level ));
	return 1;
}

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
static int getCharSkill (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int sindex = luaL_checkint(L, 2);
  lua_pushinteger(L, CHAR_getCharSkill(index, sindex));
  return 1;
}


static int setCharSkill (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int sindex = luaL_checkint(L, 2);
  const int data = luaL_checkint(L, 3);
  if(CHAR_setCharSkill(index, sindex, data) == -1){
  	return 0;
  }else{
  	return 1;
  }
}

static int DelSProfeesionSkill (lua_State *L) 
{
  const int index = luaL_checkint(L, 1);
  const int sindex = luaL_checkint(L, 2);
  CHAR_HaveSkill *pSkil;
  pSkil = CHAR_getCharHaveSkill( index, sindex );
	SKILL_makeSkillData( &pSkil->skill, 0, 0 );	
	pSkil->use = 0;
}

#endif


static int UpCahrData(lua_State *L) 
{
	const int charaindex = luaL_checkint(L, 1);
	size_t l;
  	const char *data = luaL_checklstring(L, 2, &l);
	CHAR_sendStatusString(charaindex,data);
	return 1;
}
#ifdef _NEW_TITLE
static int getCharNewTitleMode(lua_State *L){
	const int charaindex = luaL_checkint(L, 1);
	const int id = luaL_checkint(L, 2);
	if (id < 32){
		if (CHAR_getInt(charaindex,CHAR_TITLE1)&(1<<id)) {
			lua_pushinteger(L, 1);
			return 1;
		}
	}
	else if (id >=32 && id < 64) {
		if (CHAR_getInt(charaindex,CHAR_TITLE2)&(1<<(id-32))) {
			lua_pushinteger(L, 1);
			return 1;
		}
	}
	else if (id >=64 && id < 96){
		if (CHAR_getInt(charaindex,CHAR_TITLE3)&(1<<(id-64))) {
			lua_pushinteger(L, 1);
			return 1;
		}
	}
	lua_pushinteger(L, -1);
	return 1;
}

static int setCharNewTitleMode(lua_State *L){
	const int charaindex = luaL_checkint(L, 1);
	const int id = luaL_checkint(L, 2);
	if (id < 32){
		CHAR_setInt(charaindex,CHAR_TITLE1,CHAR_getInt(charaindex,CHAR_TITLE1)|(1<<id));
	}
	else if (id >=32 && id < 64) {
		CHAR_setInt(charaindex,CHAR_TITLE2,CHAR_getInt(charaindex,CHAR_TITLE2)|(1<<(id-32)));
	}
	else if (id >=64 && id < 96){
		CHAR_setInt(charaindex,CHAR_TITLE3,CHAR_getInt(charaindex,CHAR_TITLE3)|(1<<(id-64)));
	}
	return 1;
}

static int clrCharNewTitleMode(lua_State *L){
	const int charaindex = luaL_checkint(L, 1);
	const int id = luaL_checkint(L, 2);
	if (id < 32){
		CHAR_setInt(charaindex,CHAR_TITLE1,CHAR_getInt(charaindex,CHAR_TITLE1)& ~(1<<id));
	}
	else if (id >=32 && id < 64) {
		CHAR_setInt(charaindex,CHAR_TITLE2,CHAR_getInt(charaindex,CHAR_TITLE2)& ~(1<<(id-32)));
	}
	else if (id >=64 && id < 96){
		CHAR_setInt(charaindex,CHAR_TITLE3,CHAR_getInt(charaindex,CHAR_TITLE3)& ~(1<<(id-64)));
	}
	return 1;
}
#endif

static int lua_getMyMaxPilenum(lua_State *L) 
{
	int charaindex=luaL_checkint(L, 1);
	lua_pushinteger(L, CHAR_getMyMaxPilenum(charaindex));
	return 1;
}

static int PileItemFromItemBoxToItemBox(lua_State *L) 
{
	int charaindex=luaL_checkint(L, 1);
	int from=luaL_checkint(L, 2);
	int to=luaL_checkint(L, 3);
	lua_pushinteger(L, CHAR_PileItemFromItemBoxToItemBox(charaindex,from,to));
	return 1;
}

static int CheckUserItem(lua_State *L)
{
	int charaindex=luaL_checkint(L, 1);
	CHAR_CheckUserItem(charaindex);
	return 1;
}

extern int NPC_Lua_NLG_UpChar(lua_State *_NLL);
static const luaL_Reg charlib[] = {
	{"PileItemFromItemBoxToItemBox", PileItemFromItemBoxToItemBox},
	{"getMyMaxPilenum", lua_getMyMaxPilenum},
	{"upchar", 						NPC_Lua_NLG_UpChar},
	{"getCharNum", 						getCharNum},
	{"UpCahrData", 						UpCahrData},
	{"getPlayerMaxNum", 			getPlayerMaxNum},
	{"getPetMaxNum", 					getPetMaxNum},
	{"getOthersMaxNum", 			getOthersMaxNum},
	{"check", 								check},
	{"setWorkChar", 					setWorkChar},
	{"getWorkChar", 					getWorkChar},
	{"setWorkInt", 						setWorkInt},
	{"getWorkInt", 						getWorkInt},
	{"setChar", 							setChar},
  {"getChar", 							getChar},
  {"setInt", 								setInt},
  {"getInt", 								getInt},
  {"setFlg", 								setFlg},
  {"getFlg", 								getFlg},
  {"setFunctionPointer", 		setFunctionPointer},
  {"delFunctionPointer", 		delFunctionPointer},
  {"TalkToCli", 						TalkToCli},
  {"TalkToRound", 					TalkToRound},
  {"talkToFloor", 					talkToFloor},
  {"talkToParty", 					talkToParty},
  {"talkToServer", 					talkToServer},
#ifdef _MO_LUA_TALK_EX
  {"talkToServerEx", 					talkToServerEx},
#endif
  {"BoundRandWalk", 				BoundRandWalk},
  {"ToAroundChar", 					ToAroundChar},
#ifdef _ALLBLUES_LUA_1_1
  {"Walk", 									Walk},
  {"WalkPoint", 						WalkPoint},
  {"WarpToSpecificPoint", 	WarpToSpecificPoint},
  {"MapAllWarp", 						MapAllWarp},
  {"RandRandWalk", 					RandRandWalk},
#endif
#ifdef _ALLBLUES_LUA_1_3
	{"createPet", 						createPet},
	{"setCharPet", 						setCharPet},
	{"getCharPet", 						getCharPet},
	{"setCharPoolPet", 				setCharPoolPet},
	{"getCharPoolPet", 				getCharPoolPet},	
	{"setDepotPetIndex", 			setDepotPetIndex},
	{"getDepotPetIndex", 			getDepotPetIndex},		
	{"DelItem", 							DelItem},	
	{"getFd", 								getFd},
	{"Updata", 								Updata},
	{"Additem", 							Additem},
	{"AddPet", 								AddPet},
	{"Finditem", 							Finditem},
#ifdef _PLAYER_NPC
  {"setPlayerNpc", 					setPlayerNpc},
#endif
  {"Coordinate", 						Coordinate}, 
  {"setPetSkill", 					setPetSkill}, 
  {"getPetSkill", 					getPetSkill}, 
  {"PetLevelUp", 						PetLevelUp}, 
  {"JoinParty", 						JoinParty}, 
#endif
#ifdef _ALLBLUES_LUA_1_4
  {"getLiftTo8", 						getLiftTo8},
  {"getRightTo8", 					getRightTo8},
  {"complianceParameter", 	complianceParameter},
  {"sendStatusString", 			sendStatusString},
  {"sendBattleEffect", 			sendBattleEffect},
  {"dropPetAbsolute", 			dropPetAbsolute},
  {"AddPetCf", 							AddPetCf},
  {"sendWatchEvent", 				sendWatchEvent},
  {"AllWarpToSpecificPoint",AllWarpToSpecificPoint},
  {"Findpet",								Findpet},
  {"DelPet",								DelPet},
  {"CharaDeleteHavePet",								CharaDeleteHavePet},
  {"FindPetFormEnemyTempID",FindPetFormEnemyTempID},
  {"FindPetFormMatemo",			FindPetFormMatemo},
#endif
#ifdef _PETSKILL_SHOP_LUA   
  {"FreePetSkill", 					FreePetSkill},
#endif
#ifdef _ALLBLUES_LUA_1_7
  {"findEmptyPetBox", 			findEmptyPetBox},
  {"findEmptyItemBox", 			findEmptyItemBox},
  {"dropPetFollow", 				dropPetFollow},
  {"getItemIndex", 					getItemIndex},
  {"charSaveFromConnect", 	charSaveFromConnect},
  {"DischargeParty", 				DischargeParty},
  {"Skillupsend", 					Skillupsend},
#ifdef _RECORD_IP
  {"userip", 								userip},
#endif
#endif
#ifdef _ALLBLUES_LUA_1_9
	{"logou", 								logou},
	{"copyChar", 							copyChar},
	{"talkToAllServer", 			talkToAllServer},	
#endif
	{"earnFame", 							earnFame},
	{"Encounter", 						Encounter},
	{"getDX", 								getDX},
	{"getDY", 								getDY},
	{"sendAction", 						sendAction},
	{"GetOldLevelExp", 				GetOldLevelExp},
#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
	{"getCharSkill", 					getCharSkill},
	{"setCharSkill", 					setCharSkill},
	{"DelSProfeesionSkill", 		DelSProfeesionSkill},
#endif
	{"WriteShopData", 		AB_WriteShopData},
	{"GetEmptyItemBoxNum", 		GetEmptyItemBoxNum},
	{"ClearEncounter", 		ClearEncounter},
#ifdef _NEW_TITLE
	{"getCharNewTitleMode", 		getCharNewTitleMode},
	{"setCharNewTitleMode", 		setCharNewTitleMode},
	{"clrCharNewTitleMode",			clrCharNewTitleMode},
#endif
#ifdef _ITEM_USE_TIME
	{"CheckUserItem",	CheckUserItem},
#endif
  {NULL, 										NULL}
};

LUALIB_API int luaopen_Char (lua_State *L) {
  luaL_register(L, "char", charlib);
  return 1;
}

#endif
