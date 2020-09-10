#include "version.h"
#include "common.h"

#include "char.h"
#include "char_data.h"
#include "item.h"
#include "battle.h"
#include "object.h"
#include "magic_base.h"
#ifdef _MO_ADD_LUADX
#include "enemy.h"
#endif
//0-1999 CHAR_getInt
//2000-3999 CHAR_getChar
//4000-5999 CHAR_getWorkInt
//6000-7999 CHAR_getWorkChar
//8000-9999 CHAR_getFlg
#define LUA_DATALINE0 0
#define LUA_DATALINE1 2000
#define LUA_DATALINE2 4000
#define LUA_DATALINE3 6000
#define LUA_DATALINE4 8000
#define LUA_DATALINE5 10000
#ifdef _JZ_NEWSCRIPT_LUA

lua_const M_Lua_RegConstList[] = {
	{"對像_VIP%", sizeof("對像_VIP%"), LUA_DATALINE5 + 1},
	{"對像_序%", sizeof("對像_序%"), LUA_DATALINE0 + CHAR_DATAPLACENUMBER},
	{"對像_形象%", sizeof("對像_形象%"), LUA_DATALINE0 + CHAR_BASEIMAGENUMBER},
	{"對像_原形%", sizeof("對像_原形%"), LUA_DATALINE0 + CHAR_BASEBASEIMAGENUMBER},
	{"對像_臉%", sizeof("對像_臉%"), LUA_DATALINE0 + CHAR_FACEIMAGENUMBER},
	{"對像_地圖%", sizeof("對像_地圖%"), LUA_DATALINE0 + CHAR_FLOOR},
	{"對像_X%", sizeof("對像_X%"), LUA_DATALINE0 + CHAR_X},
	{"對像_Y%", sizeof("對像_Y%"), LUA_DATALINE0 + CHAR_Y},
	{"對像_方嚮%", sizeof("對像_方嚮%"), LUA_DATALINE0 + CHAR_DIR},
	{"對像_等級%", sizeof("對像_等級%"), LUA_DATALINE0 + CHAR_LV},
	{"對像_石幣%", sizeof("對像_石幣%"), LUA_DATALINE0 + CHAR_GOLD},
	{"對像_血%", sizeof("對像_血%"), LUA_DATALINE0 + CHAR_HP},
	{"對像_氣%", sizeof("對像_氣%"), LUA_DATALINE0 + CHAR_MP},
	{"對像_M氣%", sizeof("對像_M氣%"), LUA_DATALINE0 + CHAR_MAXMP},
	{"對像_體力%", sizeof("對像_體力%"), LUA_DATALINE0 + CHAR_VITAL},
	{"對像_腕力%", sizeof("對像_腕力%"), LUA_DATALINE0 + CHAR_STR},
	{"對像_耐力%", sizeof("對像_耐力%"), LUA_DATALINE0 + CHAR_TOUGH},
	{"對像_速度%", sizeof("對像_速度%"), LUA_DATALINE0 + CHAR_DEX},
	{"對像_魅力%", sizeof("對像_魅力%"), LUA_DATALINE0 + CHAR_CHARM},
	{"對像_運%", sizeof("對像_運%"), LUA_DATALINE0 + CHAR_LUCK},
	{"對像_地%", sizeof("對像_地%"), LUA_DATALINE0 + CHAR_EARTHAT},
	{"對像_水%", sizeof("對像_水%"), LUA_DATALINE0 + CHAR_WATERAT},
	{"對像_火%", sizeof("對像_火%"), LUA_DATALINE0 + CHAR_FIREAT},
	{"對像_風%", sizeof("對像_風%"), LUA_DATALINE0 + CHAR_WINDAT},
	{"對像_戰寵%", sizeof("對像_戰寵%"), LUA_DATALINE0 + CHAR_DEFAULTPET},
	{"對像_CL%", sizeof("對像_CL%"), LUA_DATALINE0 + CHAR_CRITIAL},
	{"對像_CR%", sizeof("對像_CR%"), LUA_DATALINE0 + CHAR_COUNTER},
	{"對像_珍稀%", sizeof("對像_珍稀%"), LUA_DATALINE0 + CHAR_RARE},
	{"對像_RH%", sizeof("對像_RH%"), LUA_DATALINE0 + CHAR_RADARSTRENGTH},
	{"對像_CE%", sizeof("對像_CE%"), LUA_DATALINE0 + CHAR_CHATVOLUME},
	{"對像_ML%", sizeof("對像_ML%"), LUA_DATALINE0 + CHAR_MERCHANTLEVEL},
	{"對像_記錄%", sizeof("對像_記錄%"), LUA_DATALINE0 + CHAR_SAVEPOINT},
	{"對像_DM%", sizeof("對像_DM%"), LUA_DATALINE0 + CHAR_DETERMINEITEM},
	{"對像_稱號%", sizeof("對像_稱號%"), LUA_DATALINE0 + CHAR_INDEXOFEQTITLE},
	{"對像_計毒%", sizeof("對像_計毒%"), LUA_DATALINE0 + CHAR_POISON},
	{"對像_計麻%", sizeof("對像_計麻%"), LUA_DATALINE0 + CHAR_PARALYSIS},
	{"對像_計默%", sizeof("對像_計默%"), LUA_DATALINE0 + CHAR_SLEEP},
	{"對像_計石%", sizeof("對像_計石%"), LUA_DATALINE0 + CHAR_STONE},
	{"對像_計暗%", sizeof("對像_計暗%"), LUA_DATALINE0 + CHAR_DRUNK},
	{"對像_計亂%", sizeof("對像_計亂%"), LUA_DATALINE0 + CHAR_CONFUSION},
	{"對像_登數%", sizeof("對像_登數%"), LUA_DATALINE0 + CHAR_LOGINCOUNT},
	{"對像_死次%", sizeof("對像_死次%"), LUA_DATALINE0 + CHAR_DEADCOUNT},
	{"對像_走次%", sizeof("對像_走次%"), LUA_DATALINE0 + CHAR_WALKCOUNT},
	{"對像_說次%", sizeof("對像_說次%"), LUA_DATALINE0 + CHAR_TALKCOUNT},
	{"對像_傷次%", sizeof("對像_傷次%"), LUA_DATALINE0 + CHAR_DAMAGECOUNT},
	{"對像_捕次%", sizeof("對像_捕次%"), LUA_DATALINE0 + CHAR_GETPETCOUNT},
	{"對像_殺怪%", sizeof("對像_殺怪%"), LUA_DATALINE0 + CHAR_KILLPETCOUNT},
	{"對像_寵死%", sizeof("對像_寵死%"), LUA_DATALINE0 + CHAR_DEADPETCOUNT},
	{"對像_郵數%", sizeof("對像_郵數%"), LUA_DATALINE0 + CHAR_SENDMAILCOUNT},
	{"對像_閤數%", sizeof("對像_閤數%"), LUA_DATALINE0 + CHAR_MERGEITEMCOUNT},
	{"對像_PK數%", sizeof("對像_PK數%"), LUA_DATALINE0 + CHAR_DUELBATTLECOUNT},
	{"對像_P贏數%", sizeof("對像_P贏數%"), LUA_DATALINE0 + CHAR_DUELWINCOUNT},
	{"對像_P輸數%", sizeof("對像_P輸數%"), LUA_DATALINE0 + CHAR_DUELLOSECOUNT},
	{"對像_P連數%", sizeof("對像_P連數%"), LUA_DATALINE0 + CHAR_DUELSTWINCOUNT},
	{"對像_P最高%", sizeof("對像_P最高%"), LUA_DATALINE0 + CHAR_DUELMAXSTWINCOUNT},
	{"對像_類型%", sizeof("對像_類型%"), LUA_DATALINE0 + CHAR_WHICHTYPE},
	{"對像_移間%", sizeof("對像_移間%"), LUA_DATALINE0 + CHAR_WALKINTERVAL},
	{"對像_循時%", sizeof("對像_循時%"), LUA_DATALINE0 + CHAR_LOOPINTERVAL},
#ifdef _NEWOPEN_MAXEXP
	{"對像_舊經%", sizeof("對像_舊經%"), LUA_DATALINE0 + CHAR_OLDEXP},
	{"對像_經驗%", sizeof("對像_經驗%"), LUA_DATALINE0 + CHAR_EXP},
#else
	{"對像_經驗%", sizeof("對像_經驗%"), LUA_DATALINE0 + CHAR_EXP},
#endif

#ifdef _MO_ADD_LUADX
	{"對像_血MAX%", sizeof("對像_血MAX%"), LUA_DATALINE2 + CHAR_WORKMAXHP},
	{"對像_氣MAX%", sizeof("對像_氣MAX%"), LUA_DATALINE2 + CHAR_WORKMAXMP},
	{"對像_成長%", sizeof("對像_成長%"), LUA_DATALINE0 + CHAR_ALLOCPOINT},
	{"對像_PETRANK%", sizeof("對像_PETRANK%"), LUA_DATALINE0 + CHAR_PETRANK},
	{"對像_ENEMYBASE編號%", sizeof("對像_ENEMYBASE編號%"), LUA_DATALINE0 + CHAR_PETID},
	{"對像_擺攤%", sizeof("對像_擺攤%"), LUA_DATALINE2 + CHAR_WORKSTREETVENDOR},
	{"對像_看攤者%", sizeof("對像_看攤者%"), LUA_DATALINE2 + CHAR_WORKSTREETVENDOR_WHO},
	{"對像_攤名%", sizeof("對像_攤名%"), LUA_DATALINE0 + CHAR_STREETVENDOR_NAME},
	{"對像_婚否%", sizeof("對像_婚否%"), LUA_DATALINE0 + CHAR_LOVE},
	{"對像_配偶帳%", sizeof("對像_配偶帳%"), LUA_DATALINE0 + CHAR_LOVERID},
	{"對像_配偶名%", sizeof("對像_配偶名%"), LUA_DATALINE0 + CHAR_LOVERNAME},
	{"成長_速度%", sizeof("成長_速度%"), 0},
	{"成長_耐力%", sizeof("成長_耐力%"), 1},
	{"成長_腕力%", sizeof("成長_腕力%"), 2},
	{"成長_體力%", sizeof("成長_體力%"), 3},
	{"對像_速度成長%", sizeof("對像_速度成長%"), 0},
	{"對像_耐力成長%", sizeof("對像_耐力成長%"), 1},
	{"對像_腕力成長%", sizeof("對像_腕力成長%"), 2},
	{"對像_體力成長%", sizeof("對像_體力成長%"), 3},
	{"寵模_編號%", sizeof("寵模_編號%"), LUA_DATALINE0 + E_T_TEMPNO},
	{"寵模_初始%", sizeof("寵模_初始%"), LUA_DATALINE0 + E_T_INITNUM},
	{"寵模_升級點%", sizeof("寵模_升級點%"), E_T_LVUPPOINT},
	{"寵模_體力%", sizeof("寵模_體力%"), LUA_DATALINE0 + E_T_BASEVITAL},
	{"寵模_腕力%", sizeof("寵模_腕力%"), LUA_DATALINE0 + E_T_BASESTR},
	{"寵模_耐力%", sizeof("寵模_耐力%"), LUA_DATALINE0 + E_T_BASETGH},
	{"寵模_速度%", sizeof("寵模_速度%"), LUA_DATALINE0 + E_T_BASEDEX},
	{"寵模_AI%", sizeof("寵模_AI%"), LUA_DATALINE0 + E_T_MODAI},
	{"寵模_GET%", sizeof("寵模_GET%"), LUA_DATALINE0 + E_T_GET},
	{"寵模_地%", sizeof("寵模_地%"), LUA_DATALINE0 + E_T_EARTHAT},
	{"寵模_水%", sizeof("寵模_水%"), LUA_DATALINE0 + E_T_WATERAT},
	{"寵模_火%", sizeof("寵模_火%"), LUA_DATALINE0 + E_T_FIREAT},
	{"寵模_風%", sizeof("寵模_風%"), LUA_DATALINE0 + E_T_WINDAT},
	{"寵模_毒抗%", sizeof("寵模_毒抗%"), LUA_DATALINE0 + E_T_POISON},
	{"寵模_麻抗%", sizeof("寵模_麻抗%"), LUA_DATALINE0 + E_T_PARALYSIS},
	{"寵模_默抗%", sizeof("寵模_默抗%"), LUA_DATALINE0 + E_T_SLEEP},
	{"寵模_石抗%", sizeof("寵模_石抗%"), LUA_DATALINE0 + E_T_STONE},
	{"寵模_醉抗%", sizeof("寵模_醉抗%"), LUA_DATALINE0 + E_T_DRUNK},
	{"寵模_亂抗%", sizeof("寵模_亂抗%"), LUA_DATALINE0 + E_T_CONFUSION},
	{"寵模_寵技1%", sizeof("寵模_寵技1%"), LUA_DATALINE0 + E_T_PETSKILL1},
	{"寵模_寵技2%", sizeof("寵模_寵技2%"), LUA_DATALINE0 + E_T_PETSKILL2},
	{"寵模_寵技3%", sizeof("寵模_寵技3%"), LUA_DATALINE0 + E_T_PETSKILL3},
	{"寵模_寵技4%", sizeof("寵模_寵技4%"), LUA_DATALINE0 + E_T_PETSKILL4},
	{"寵模_寵技5%", sizeof("寵模_寵技5%"), LUA_DATALINE0 + E_T_PETSKILL5},
	{"寵模_寵技6%", sizeof("寵模_寵技6%"), LUA_DATALINE0 + E_T_PETSKILL6},
	{"寵模_寵技7%", sizeof("寵模_寵技7%"), LUA_DATALINE0 + E_T_PETSKILL7},
	{"寵模_珍稀%", sizeof("寵模_珍稀%"), LUA_DATALINE0 + E_T_RARE},
	{"寵模_會心%", sizeof("寵模_會心%"), LUA_DATALINE0 + E_T_CRITICAL},
	{"寵模_反擊%", sizeof("寵模_反擊%"), LUA_DATALINE0 + E_T_COUNTER},
	{"寵模_技格%", sizeof("寵模_技格%"), LUA_DATALINE0 + E_T_SLOT},
	{"寵模_圖檔%", sizeof("寵模_圖檔%"), LUA_DATALINE0 + E_T_IMGNUMBER},
	{"寵模_FLG%", sizeof("寵模_FLG%"), LUA_DATALINE0 + E_T_PETFLG},
	{"寵模_尺寸%", sizeof("寵模_尺寸%"), LUA_DATALINE0 + E_T_SIZE},
	{"寵模_級限%", sizeof("寵模_級限%"), LUA_DATALINE0 + E_T_LIMITLEVEL},
#ifdef _PET_FUSION	
	{"寵模_融合碼%", sizeof("寵模_融合碼%"), LUA_DATALINE0 + E_T_FUSIONCODE},
#endif	
	{"寵模_原名%", sizeof("寵模_原名%"), LUA_DATALINE1 + E_T_NAME},
#endif

	{"對像_出生%", sizeof("對像_出生%"), LUA_DATALINE0 + CHAR_LASTTALKELDER},
	{"對像_配點%", sizeof("對像_配點%"), LUA_DATALINE0 + CHAR_SKILLUPPOINT},
	{"對像_LT%", sizeof("對像_LT%"), LUA_DATALINE0 + CHAR_LEVELUPPOINT},
	{"對像_圖類%", sizeof("對像_圖類%"), LUA_DATALINE0 + CHAR_IMAGETYPE},
	{"對像_CLR%", sizeof("對像_CLR%"), LUA_DATALINE0 + CHAR_NAMECOLOR},
	{"對像_話色%", sizeof("對像_話色%"), LUA_DATALINE0 + CHAR_POPUPNAMECOLOR},
	{"對像_設運%", sizeof("對像_設運%"), LUA_DATALINE0 + CHAR_LASTTIMESETLUCK},
	{"對像_DP%", sizeof("對像_DP%"), LUA_DATALINE0 + CHAR_DUELPOINT},
	{"對像_轉數%", sizeof("對像_轉數%"), LUA_DATALINE0 + CHAR_TRANSMIGRATION},
	{"對像_轉參%", sizeof("對像_轉參%"), LUA_DATALINE0 + CHAR_TRANSEQUATION},
	{"對像_IA%", sizeof("對像_IA%"), LUA_DATALINE0 + CHAR_INITDATA},
	{"對像_禁時%", sizeof("對像_禁時%"), LUA_DATALINE0 + CHAR_SILENT},
	{"對像_族引%", sizeof("對像_族引%"), LUA_DATALINE0 + CHAR_FMINDEX},
	{"對像_族職%", sizeof("對像_族職%"), LUA_DATALINE0 + CHAR_FMLEADERFLAG},
	{"對像_守精%", sizeof("對像_守精%"), LUA_DATALINE0 + CHAR_FMSPRITE},
	{"對像_個銀%", sizeof("對像_個銀%"), LUA_DATALINE0 + CHAR_BANKGOLD},
	{"對像_騎寵%", sizeof("對像_騎寵%"), LUA_DATALINE0 + CHAR_RIDEPET},
	{"對像_騎等%", sizeof("對像_騎等%"), LUA_DATALINE0 + CHAR_LEARNRIDE},
	{"對像_咒等%", sizeof("對像_咒等%"), LUA_DATALINE0 + CHAR_LIMITLEVEL},
#ifdef _PET_FUSION
	{"對像_物碼%", sizeof("對像_物碼%"), LUA_DATALINE0 + CHAR_FUSIONCODE},
	{"對像_孵寵%", sizeof("對像_孵寵%"), LUA_DATALINE0 + CHAR_FUSIONINDEX},
	{"對像_養次%", sizeof("對像_養次%"), LUA_DATALINE0 + CHAR_FUSIONRAISE},
	{"對像_蛋標%", sizeof("對像_蛋標%"), LUA_DATALINE0 + CHAR_FUSIONBEIT},
	{"對像_養時%", sizeof("對像_養時%"), LUA_DATALINE0 + CHAR_FUSIONTIMELIMIT},
#endif
#ifdef _DEATH_CONTEND
	{"對像_隊標%", sizeof("對像_隊標%"), LUA_DATALINE0 + CHAR_PKLISTTEAMNUM},
	{"對像_領標%", sizeof("對像_領標%"), LUA_DATALINE0 + CHAR_PKLISTLEADER},
#endif
#ifdef _PERSONAL_FAME
	{"對像_聲望%", sizeof("對像_聲望%"), LUA_DATALINE0 + CHAR_FAME},
#endif
#ifdef _MO_Mercenary
  {"對像_傭兵經驗%",       sizeof("對像_傭兵經驗%"), LUA_DATALINE0 + CHAR_MERCENARY},  //傭兵經驗
#endif
#ifdef _VIP_RIDE
	{"對像_VIP類型%", sizeof("對像_VIP類型%"), LUA_DATALINE0 + CHAR_VIPRIDE},
	{"對像_VIP時間%", sizeof("對像_VIP時間%"), LUA_DATALINE0 + CHAR_VIPTIME},
#endif
#ifdef _VIP_SERVER
	{"對像_積分%", sizeof("對像_積分%"), LUA_DATALINE0 + CHAR_AMPOINT},
#endif
#ifdef _EV_NUM
	{"對像_跑環%", sizeof("對像_跑環%"), LUA_DATALINE0 + CHAR_EVNUM},
#endif
  {"對像_任務鏈%",     sizeof("對像_任務鏈%"), LUA_DATALINE0 + CHAR_MISSIONTRAIN_NUM},
  {"對像_任務鏈時間%", sizeof("對像_任務鏈時間%"), LUA_DATALINE0 + CHAR_MISSIONTRAIN_TIME},
  {"對像_環數%", sizeof("對像_環數%"), LUA_DATALINE0 + CHAR_MISSIONTRAIN_NUM}, // 跑環數
  {"對像_進化%",       sizeof("對像_進化%"), LUA_DATALINE0 + CHAR_EVOLVE},
  {"對像_在線時間%",   sizeof("對像_在線時間%"), LUA_DATALINE0 + CHAR_ONLINE_TIME},
  {"對像_樓層時間%",   sizeof("對像_樓層時間%"), LUA_DATALINE0 + CHAR_FLOORDIFI_TIME},
  {"對像_極品%",       sizeof("對像_極品%"), LUA_DATALINE0 + CHAR_SUPER},
  {"對像_稱號等級%",   sizeof("對像_稱號等級%"), LUA_DATALINE0 + CHAR_TITLE_LV},
  {"對像_稱號時間%",   sizeof("對像_稱號時間%"), LUA_DATALINE0 + CHAR_TITLE_TIME},
  {"對像_任務計時%",   sizeof("對像_任務計時%"), LUA_DATALINE0 + CHAR_MISSION_TIME},

#ifdef _ATTACK_MAGIC
	{"對像_地魔熟%", sizeof("對像_地魔熟%"), LUA_DATALINE0 + CHAR_EARTH_EXP},
	{"對像_水魔熟%", sizeof("對像_水魔熟%"), LUA_DATALINE0 + CHAR_WATER_EXP},
	{"對像_火魔熟%", sizeof("對像_火魔熟%"), LUA_DATALINE0 + CHAR_FIRE_EXP},
	{"對像_風魔熟%", sizeof("對像_風魔熟%"), LUA_DATALINE0 + CHAR_WIND_EXP},
	{"對像_地魔抗%", sizeof("對像_地魔抗%"), LUA_DATALINE0 + CHAR_EARTH_RESIST},
	{"對像_水魔抗%", sizeof("對像_水魔抗%"), LUA_DATALINE0 + CHAR_WATER_RESIST},
	{"對像_火魔抗%", sizeof("對像_火魔抗%"), LUA_DATALINE0 + CHAR_FIRE_RESIST},
	{"對像_風魔抗%", sizeof("對像_風魔抗%"), LUA_DATALINE0 + CHAR_WIND_RESIST},
	{"對像_地熟經%", sizeof("對像_地熟經%"), LUA_DATALINE0 + CHAR_EARTH_ATTMAGIC_EXP},
	{"對像_水熟經%", sizeof("對像_水熟經%"), LUA_DATALINE0 + CHAR_WATER_ATTMAGIC_EXP},
	{"對像_火熟經%", sizeof("對像_火熟經%"), LUA_DATALINE0 + CHAR_FIRE_ATTMAGIC_EXP},
	{"對像_風熟經%", sizeof("對像_風熟經%"), LUA_DATALINE0 + CHAR_WIND_ATTMAGIC_EXP},
	{"對像_地抗經%", sizeof("對像_地抗經%"), LUA_DATALINE0 + CHAR_EARTH_DEFMAGIC_EXP},
	{"對像_水抗經%", sizeof("對像_水抗經%"), LUA_DATALINE0 + CHAR_WATER_DEFMAGIC_EXP},
	{"對像_火抗經%", sizeof("對像_火抗經%"), LUA_DATALINE0 + CHAR_FIRE_DEFMAGIC_EXP},
	{"對像_風抗經%", sizeof("對像_風抗經%"), LUA_DATALINE0 + CHAR_WIND_DEFMAGIC_EXP},
#endif
#ifdef _GAMBLE_BANK
	{"對像_賭銀%", sizeof("對像_賭銀%"), LUA_DATALINE0 + CHAR_PERSONAGOLD},
#endif
#ifdef _DROPSTAKENEW
	{"對像_賭分%", sizeof("對像_賭分%"), LUA_DATALINE0 + CHAR_GAMBLENUM},
#endif
#ifdef _AUCTIONEER
	{"對像_拍得%", sizeof("對像_拍得%"), LUA_DATALINE0 + CHAR_AUCGOLD},
#endif
#ifdef _PET_EVOLUTION
	{"對像_血藥數%", sizeof("對像_血藥數%"), LUA_DATALINE0 + CHAR_EVOLUTIONBASEVTL},
	{"對像_攻藥數%", sizeof("對像_攻藥數%"), LUA_DATALINE0 + CHAR_EVOLUTIONBASESTR},
	{"對像_防藥數%", sizeof("對像_防藥數%"), LUA_DATALINE0 + CHAR_EVOLUTIONBASETGH},
	{"對像_敏藥數%", sizeof("對像_敏藥數%"), LUA_DATALINE0 + CHAR_EVOLUTIONBASEDEX},
#endif
#ifdef _FAMILYBANKSTONELOG
	{"對像_族銀%", sizeof("對像_族銀%"), LUA_DATALINE0 + CHAR_FMBANKGOLD},
#endif
#ifdef _FM_JOINLIMIT
	{"對像_加族間%", sizeof("對像_加族間%"), LUA_DATALINE0 + CHAR_FMTIMELIMIT},
#endif
#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	{"對像_職業%", sizeof("對像_職業%"), LUA_DATALINE0 + PROFESSION_CLASS},
	{"對像_職等%", sizeof("對像_職等%"), LUA_DATALINE0 + PROFESSION_LEVEL},
	//{"對像_職經", sizeof("對像_職經"), LUA_DATALINE0 + PROFESSION_EXP},
	{"對像_職技點%", sizeof("對像_職技點%"), LUA_DATALINE0 + PROFESSION_SKILL_POINT},
	{"對像_職增疊%", sizeof("對像_職增疊%"), LUA_DATALINE0 + ATTACHPILE},
	{"對像_職火熟%", sizeof("對像_職火熟%"), LUA_DATALINE0 + PROFESSION_FIRE_P},
	{"對像_職冰熟%", sizeof("對像_職冰熟%"), LUA_DATALINE0 + PROFESSION_ICE_P},
	{"對像_職雷熟%", sizeof("對像_職雷熟%"), LUA_DATALINE0 + PROFESSION_THUNDER_P},
	{"對像_職火抗%", sizeof("對像_職火抗%"), LUA_DATALINE0 + PROFESSION_FIRE_R},
	{"對像_職冰抗%", sizeof("對像_職冰抗%"), LUA_DATALINE0 + PROFESSION_ICE_R},
	{"對像_職雷抗%", sizeof("對像_職雷抗%"), LUA_DATALINE0 + PROFESSION_THUNDER_R},
#endif
#ifdef _ALLDOMAN // (不可開) Syu ADD 排行榜NPC
	{"對像_戰層%", sizeof("對像_戰層%"), LUA_DATALINE0 + CHAR_HEROFLOOR},
#endif
#ifdef _PETSKILL_BECOMEPIG
	{"對像_烏力時%", sizeof("對像_烏力時%"), LUA_DATALINE0 + CHAR_BECOMEPIG},
	{"對像_烏力樣%", sizeof("對像_烏力樣%"), LUA_DATALINE0 + CHAR_BECOMEPIG_BBI},
#endif
	{"對像_離綫時%", sizeof("對像_離綫時%"), LUA_DATALINE0 + CHAR_LASTLEAVETIME},
#ifdef _NEW_MANOR_LAW
	{"對像_氣勢%", sizeof("對像_氣勢%"), LUA_DATALINE0 + CHAR_MOMENTUM},
#endif
#ifdef _ANGEL_SUMMON
	{"對像_勇數%", sizeof("對像_勇數%"), LUA_DATALINE0 + CHAR_HEROCNT},
#endif
#ifdef _TEACHER_SYSTEM
	{"對像_導聲望%", sizeof("對像_導聲望%"), LUA_DATALINE0 + CHAR_TEACHER_FAME},
#endif
#ifdef _MO_ESC_REPORT
	{"對像_簽到%", sizeof("對像_簽到%"), LUA_DATALINE0 + CHAR_REPORT},
#endif
#ifdef _RACEMAN
	{"對像_CKN%", sizeof("對像_CKN%"), LUA_DATALINE0 + CHAR_CHECKIN},
	{"對像_CN1%", sizeof("對像_CN1%"), LUA_DATALINE0 + CHAR_CATCHCNT1},
	{"對像_CN2%", sizeof("對像_CN2%"), LUA_DATALINE0 + CHAR_CATCHCNT2},
	{"對像_CN3%", sizeof("對像_CN3%"), LUA_DATALINE0 + CHAR_CATCHCNT3},
	{"對像_CN4%", sizeof("對像_CN4%"), LUA_DATALINE0 + CHAR_CATCHCNT4},
	{"對像_CN5%", sizeof("對像_CN5%"), LUA_DATALINE0 + CHAR_CATCHCNT5},
	{"對像_KN1%", sizeof("對像_KN1%"), LUA_DATALINE0 + CHAR_KINDCNT1},
	{"對像_KN2%", sizeof("對像_KN2%"), LUA_DATALINE0 + CHAR_KINDCNT2},
	{"對像_KN3%", sizeof("對像_KN3%"), LUA_DATALINE0 + CHAR_KINDCNT3},
	{"對像_KN4%", sizeof("對像_KN4%"), LUA_DATALINE0 + CHAR_KINDCNT4},
	{"對像_KN5%", sizeof("對像_KN5%"), LUA_DATALINE0 + CHAR_KINDCNT5},
	{"對像_KN6%", sizeof("對像_KN6%"), LUA_DATALINE0 + CHAR_KINDCNT6},
	{"對像_KN7%", sizeof("對像_KN7%"), LUA_DATALINE0 + CHAR_KINDCNT7},
	{"對像_KN8%", sizeof("對像_KN8%"), LUA_DATALINE0 + CHAR_KINDCNT8},
	{"對像_KN9%", sizeof("對像_KN9%"), LUA_DATALINE0 + CHAR_KINDCNT9},
	{"對像_KN10%", sizeof("對像_KN10%"), LUA_DATALINE0 + CHAR_KINDCNT10},
#endif
  {"對像_祝福%", sizeof("對像_祝福%"), LUA_DATALINE0 + CHAR_BEATITUDE},
#ifdef	_ACTIVE_GAME
	{"對像_活力%", sizeof("對像_活力%"), LUA_DATALINE0 + CHAR_ACTIVE},
#endif
  {"對像_整數緩存1%",   sizeof("對像_整數緩存1%"), LUA_DATALINE0 + CHAR_LUASAVE_WORKINT_1},  //lua存儲 玩傢下綫清零
  {"對像_整數緩存2%",   sizeof("對像_整數緩存2%"), LUA_DATALINE0 + CHAR_LUASAVE_WORKINT_2},  //lua存儲 玩傢下綫清零
  {"對像_整數緩存3%",   sizeof("對像_整數緩存3%"), LUA_DATALINE0 + CHAR_LUASAVE_WORKINT_3},  //lua存儲 玩傢下綫清零
  {"對像_整數存儲1%", sizeof("對像_整數存儲1%"), LUA_DATALINE0 + CHAR_LUASAVE_INT_1},      //整數存儲，保存至存檔內
  {"對像_整數存儲2%", sizeof("對像_整數存儲2%"), LUA_DATALINE0 + CHAR_LUASAVE_INT_2},      //整數存儲，保存至存檔內
  {"對像_整數存儲3%", sizeof("對像_整數存儲3%"), LUA_DATALINE0 + CHAR_LUASAVE_INT_3},      //整數存儲，保存至存檔內
 // {"對像_IP%",sizeof("對像_IP%"),LUA_DATALINE1 + CHAR_CHARPLAYIP},
 
  {"對像_會員等級%", sizeof("對像_會員等級%"), LUA_DATALINE0 + CHAR_VIPRIDE},
	{"對像_會員時間%", sizeof("對像_會員時間%"), LUA_DATALINE0 + CHAR_VIPTIME},
	
//	{"對像_NPC時間%", sizeof("對像_NPC時間%"), LUA_DATALINE0 + CHAR_NPCTIME},

	{"對像_原名%", sizeof("對像_原名%"), LUA_DATALINE1 + CHAR_NAME},
	{"對像_名稱%", sizeof("對像_名稱%"), LUA_DATALINE1 + CHAR_USERPETNAME},
	{"對像_帳號%", sizeof("對像_帳號%"), LUA_DATALINE1 + CHAR_CDKEY},
	{"對像_屬帳%", sizeof("對像_屬帳%"), LUA_DATALINE1 + CHAR_OWNERCDKEY},
	{"對像_屬人%", sizeof("對像_屬人%"), LUA_DATALINE1 + CHAR_OWNERCHARANAME},
	{"對像_家族名%", sizeof("對像_家族名%"), LUA_DATALINE1 + CHAR_FMNAME},
#ifdef _TEACHER_SYSTEM
	{"對像_導師帳%", sizeof("對像_導師帳%"), LUA_DATALINE1 + CHAR_TEACHER_ID},
	{"對像_導師名%", sizeof("對像_導師名%"), LUA_DATALINE1 + CHAR_TEACHER_NAME},
#endif
#ifdef _MO_LUA_BETT01
	{"對像_戰接1%", sizeof("對像_戰接1%"), LUA_DATALINE2 + CHAR_WORKBATTLECOM1},
	{"對像_戰接2%", sizeof("對像_戰接2%"), LUA_DATALINE2 + CHAR_WORKBATTLECOM2},
	{"對像_戰模%", sizeof("對像_戰模%"), LUA_DATALINE2 + CHAR_WORKBATTLEMODE},
#endif
	{"對像_隊模式%", sizeof("對像_隊模式%"), LUA_DATALINE2 + CHAR_WORKPARTYMODE},
#ifdef _ATTACK_EFFECT
	{"對像_攻擊特效%", sizeof("對像_攻擊特效%"), LUA_DATALINE0 + CHAR_ATTACK_EFFECT},
#endif
	{"對像_物索引%", sizeof("對像_物索引%"), LUA_DATALINE2 + CHAR_WORKOBJINDEX},
#ifdef _ADD_ACTION          //npc動作
	{"對像_動作%", sizeof("對像_動作%"), LUA_DATALINE2 + CHAR_WORKACTION},
#endif
//	{"對像_LUA%", sizeof("對像_LUA%"), LUA_DATALINE2 + CHAR_WORKLUANPCINT},
//	{"對像_1LUA%", sizeof("對像_1LUA%"), LUA_DATALINE2 + CHAR_WORKLUANPCINT1},

#ifdef _CHARSIGNDAY_
	{"對像_簽到狀態%", sizeof("對像_簽到狀態%"), LUA_DATALINE0 + CHAR_QIANDAOZT},
	{"對像_簽到月%", sizeof("對像_簽到月%"), LUA_DATALINE0 + CHAR_QIANDAOYUE},
	{"對像_簽到日%", sizeof("對像_簽到日%"), LUA_DATALINE0 + CHAR_QIANDAORI},
#endif
	{"對像_IAK%", sizeof("對像_IAK%"), LUA_DATALINE4 + CHAR_ISATTACK},
	{"對像_戰令%", sizeof("對像_戰令%"), LUA_DATALINE4 + CHAR_ISATTACKED},
	{"對像_IOR%", sizeof("對像_IOR%"), LUA_DATALINE4 + CHAR_ISOVER},
	{"對像_檔路%", sizeof("對像_檔路%"), LUA_DATALINE4 + CHAR_ISOVERED},
	{"對像_HHT%", sizeof("對像_HHT%"), LUA_DATALINE4 + CHAR_HAVEHEIGHT},
	{"對像_隱身%", sizeof("對像_隱身%"), LUA_DATALINE4 + CHAR_ISVISIBLE},
	{"對像_ITP%", sizeof("對像_ITP%"), LUA_DATALINE4 + CHAR_ISTRANSPARENT},
	{"對像_IFG%", sizeof("對像_IFG%"), LUA_DATALINE4 + CHAR_ISFLYING},
	{"對像_死亡%", sizeof("對像_死亡%"), LUA_DATALINE4 + CHAR_ISDIE},
	{"對像_IBIG%", sizeof("對像_IBIG%"), LUA_DATALINE4 + CHAR_ISBIG},
	{"對像_顯戰%", sizeof("對像_顯戰%"), LUA_DATALINE4 + CHAR_ISSHOWBATTLEMSG},
	{"對像_組隊標%", sizeof("對像_組隊標%"), LUA_DATALINE4 + CHAR_ISPARTY},
	{"對像_允許記%", sizeof("對像_允許記%"), LUA_DATALINE4 + CHAR_ISWARP},
	{"對像_族戰標%", sizeof("對像_族戰標%"), LUA_DATALINE4 + CHAR_ISDUEL},
	{"對像_隊聊標%", sizeof("對像_隊聊標%"), LUA_DATALINE4 + CHAR_ISPARTYCHAT},
	{"對像_名片標%", sizeof("對像_名片標%"), LUA_DATALINE4 + CHAR_ISTRADECARD},
	{"對像_交易標%", sizeof("對像_交易標%"), LUA_DATALINE4 + CHAR_ISTRADE},
#ifdef _CHANNEL_MODIFY
	{"對像_密頻標%", sizeof("對像_密頻標%"), LUA_DATALINE4 + CHAR_ISTELL},
	{"對像_族頻標%", sizeof("對像_族頻標%"), LUA_DATALINE4 + CHAR_ISFM},
	{"對像_職頻標%", sizeof("對像_職頻標%"), LUA_DATALINE4 + CHAR_ISOCC},
	{"對像_對話存%", sizeof("對像_對話存%"), LUA_DATALINE4 + CHAR_ISSAVE},
	{"對像_聊頻標%", sizeof("對像_聊頻標%"), LUA_DATALINE4 + CHAR_ISCHAT},
#endif

	{"道具_ID%", sizeof("道具_ID%"), LUA_DATALINE0 + ITEM_ID},
	{"道具_圖號%", sizeof("道具_圖號%"), LUA_DATALINE0 + ITEM_BASEIMAGENUMBER},
	{"道具_成本%", sizeof("道具_成本%"), LUA_DATALINE0 + ITEM_COST},
	{"道具_類型%", sizeof("道具_類型%"), LUA_DATALINE0 + ITEM_TYPE},
	{"道具_AUF%", sizeof("道具_AUF%"), LUA_DATALINE0 + ITEM_ABLEUSEFIELD},
	{"道具_TARGET%", sizeof("道具_TARGET%"), LUA_DATALINE0 + ITEM_TARGET},
	{"道具_等級%", sizeof("道具_等級%"), LUA_DATALINE0 + ITEM_LEVEL},
#ifdef _ITEM_MAXUSERNUM
	{"道具_次數%", sizeof("道具_次數%"), LUA_DATALINE0 + ITEM_DAMAGEBREAK},
#endif
#ifdef _ITEMSET4_TXT
	{"道具_堆疊%", sizeof("道具_堆疊%"), LUA_DATALINE0 + ITEM_USEPILENUMS},
	{"道具_可疊%", sizeof("道具_可疊%"), LUA_DATALINE0 + ITEM_CANBEPILE},
	{"道具_STR%", sizeof("道具_STR%"), LUA_DATALINE0 + ITEM_NEEDSTR},
	{"道具_DEX%", sizeof("道具_DEX%"), LUA_DATALINE0 + ITEM_NEEDDEX},
	{"道具_轉數%", sizeof("道具_轉數%"), LUA_DATALINE0 + ITEM_NEEDTRANS},
	{"道具_職業%", sizeof("道具_職業%"), LUA_DATALINE0 + ITEM_NEEDPROFESSION},
#endif
#ifdef _TAKE_ITEMDAMAGE
	{"道具_耐久%", sizeof("道具_耐久%"), LUA_DATALINE0 + ITEM_DAMAGECRUSHE},
	{"道具_MAX耐久%", sizeof("道具_MAX耐久%"), LUA_DATALINE0 + ITEM_MAXDAMAGECRUSHE},
#endif
#ifdef _ADD_DEAMGEDEFC
	{"道具_傷%", sizeof("道具_傷%"), LUA_DATALINE0 + ITEM_OTHERDAMAGE},
	{"道具_吸%", sizeof("道具_吸%"), LUA_DATALINE0 + ITEM_OTHERDEFC},
#endif
#ifdef _SUIT_ITEM
	{"道具_套%", sizeof("道具_套%"), LUA_DATALINE0 + ITEM_SUITCODE},
#endif
	{"道具_AKMIN%", sizeof("道具_AKMIN%"), LUA_DATALINE0 + ITEM_ATTACKNUM_MIN},
	{"道具_AKMAX%", sizeof("道具_AKMAX%"), LUA_DATALINE0 + ITEM_ATTACKNUM_MAX},
	{"道具_附攻%", sizeof("道具_附攻%"), LUA_DATALINE0 + ITEM_MODIFYATTACK},
	{"道具_附防%", sizeof("道具_附防%"), LUA_DATALINE0 + ITEM_MODIFYDEFENCE},
	{"道具_附敏%", sizeof("道具_附敏%"), LUA_DATALINE0 + ITEM_MODIFYQUICK},
	{"道具_附體%", sizeof("道具_附體%"), LUA_DATALINE0 + ITEM_MODIFYHP},
	{"道具_附氣%", sizeof("道具_附氣%"), LUA_DATALINE0 + ITEM_MODIFYMP},
	{"道具_附運%", sizeof("道具_附運%"), LUA_DATALINE0 + ITEM_MODIFYLUCK},
	{"道具_附魅%", sizeof("道具_附魅%"), LUA_DATALINE0 + ITEM_MODIFYCHARM},
	{"道具_附避%", sizeof("道具_附避%"), LUA_DATALINE0 + ITEM_MODIFYAVOID},
	{"道具_屬性%", sizeof("道具_屬性%"), LUA_DATALINE0 + ITEM_MODIFYATTRIB},
	{"道具_屬性值%", sizeof("道具_屬性值%"), LUA_DATALINE0 + ITEM_MODIFYATTRIBVALUE},
	{"道具_精靈%", sizeof("道具_精靈%"), LUA_DATALINE0 + ITEM_MAGICID},
	{"道具_精靈率%", sizeof("道具_精靈率%"), LUA_DATALINE0 + ITEM_MAGICPROB},
	{"道具_精靈耗%", sizeof("道具_精靈耗%"), LUA_DATALINE0 + ITEM_MAGICUSEMP},
#ifdef _ITEMSET5_TXT
	{"道具_格檔率%", sizeof("道具_格檔率%"), LUA_DATALINE0 + ITEM_MODIFYARRANGE},
	{"道具_攻序%", sizeof("道具_攻序%"), LUA_DATALINE0 + ITEM_MODIFYSEQUENCE},
	{"道具_負重%", sizeof("道具_負重%"), LUA_DATALINE0 + ITEM_ATTACHPILE},
	{"道具_命中%", sizeof("道具_命中%"), LUA_DATALINE0 + ITEM_HITRIGHT},
#endif
#ifdef _ITEMSET6_TXT
	{"道具_忽防%", sizeof("道具_忽防%"), LUA_DATALINE0 + ITEM_NEGLECTGUARD},
#endif
	{"道具_毒耐%", sizeof("道具_毒耐%"), LUA_DATALINE0 + ITEM_POISON},
	{"道具_麻耐%", sizeof("道具_麻耐%"), LUA_DATALINE0 + ITEM_PARALYSIS},
	{"道具_睡耐%", sizeof("道具_睡耐%"), LUA_DATALINE0 + ITEM_SLEEP},
	{"道具_石耐%", sizeof("道具_石耐%"), LUA_DATALINE0 + ITEM_STONE},
	{"道具_酒耐%", sizeof("道具_酒耐%"), LUA_DATALINE0 + ITEM_DRUNK},
	{"道具_混耐%", sizeof("道具_混耐%"), LUA_DATALINE0 + ITEM_CONFUSION},
	{"道具_附一擊%", sizeof("道具_附一擊%"), LUA_DATALINE0 + ITEM_CRITICAL},
	{"道具_動作%", sizeof("道具_動作%"), LUA_DATALINE0 + ITEM_USEACTION},
	{"道具_登消%", sizeof("道具_登消%"), LUA_DATALINE0 + ITEM_DROPATLOGOUT},
	{"道具_丟消%", sizeof("道具_丟消%"), LUA_DATALINE0 + ITEM_VANISHATDROP},
	{"道具_檔路%", sizeof("道具_檔路%"), LUA_DATALINE0 + ITEM_ISOVERED},
	{"道具_郵寄%", sizeof("道具_郵寄%"), LUA_DATALINE0 + ITEM_CANPETMAIL},
	{"道具_從閤成%", sizeof("道具_從閤成%"), LUA_DATALINE0 + ITEM_CANMERGEFROM},
	{"道具_閤成到%", sizeof("道具_閤成到%"), LUA_DATALINE0 + ITEM_CANMERGETO},
	{"道具_份量0%", sizeof("道具_份量0%"), LUA_DATALINE0 + ITEM_INGVALUE0},
	{"道具_份量1%", sizeof("道具_份量1%"), LUA_DATALINE0 + ITEM_INGVALUE1},
	{"道具_份量2%", sizeof("道具_份量2%"), LUA_DATALINE0 + ITEM_INGVALUE2},
	{"道具_份量3%", sizeof("道具_份量3%"), LUA_DATALINE0 + ITEM_INGVALUE3},
	{"道具_份量4%", sizeof("道具_份量4%"), LUA_DATALINE0 + ITEM_INGVALUE4},
	{"道具_丟時%", sizeof("道具_丟時%"), LUA_DATALINE0 + ITEM_PUTTIME},
	{"道具_LL%", sizeof("道具_LL%"), LUA_DATALINE0 + ITEM_LEAKLEVEL},
	{"道具_曾閤%", sizeof("道具_曾閤%"), LUA_DATALINE0 + ITEM_MERGEFLG},
	{"道具_損等%", sizeof("道具_損等%"), LUA_DATALINE0 + ITEM_CRUSHLEVEL},
//	{"道具_限時%", sizeof("道具_限時%"), LUA_DATALINE0 + ITEM_TIME},
	{"道具_VAR1%", sizeof("道具_VAR1%"), LUA_DATALINE0 + ITEM_VAR1},
	{"道具_VAR2%", sizeof("道具_VAR2%"), LUA_DATALINE0 + ITEM_VAR2},
	{"道具_VAR3%", sizeof("道具_VAR3%"), LUA_DATALINE0 + ITEM_VAR3},
	{"道具_VAR4%", sizeof("道具_VAR4%"), LUA_DATALINE0 + ITEM_VAR4},

	{"道具_物索%", sizeof("道具_物索%"), LUA_DATALINE2 + ITEM_WORKOBJINDEX},
	{"道具_索引%", sizeof("道具_索引%"), LUA_DATALINE2 + ITEM_WORKCHARAINDEX},
#ifdef _ITEM_TIME_LIMIT
	{"道具_倒時%", sizeof("道具_倒時%"), LUA_DATALINE2 + ITEM_WORKTIMELIMIT},
#endif

	{"道具_原名%", sizeof("道具_原名%"), LUA_DATALINE1 + ITEM_NAME},
	{"道具_名%", sizeof("道具_名%"), LUA_DATALINE1 + ITEM_SECRETNAME},
	{"道具_說明%", sizeof("道具_說明%"), LUA_DATALINE1 + ITEM_EFFECTSTRING},
	{"道具_參%", sizeof("道具_參%"), LUA_DATALINE1 + ITEM_ARGUMENT},
	{"道具_帳%", sizeof("道具_帳%"), LUA_DATALINE1 + ITEM_CDKEY},
	{"道具_愛帳%", sizeof("道具_愛帳%"), LUA_DATALINE1 + ITEM_FORUSERCDKEY},
	{"道具_份0%", sizeof("道具_份0%"), LUA_DATALINE1 + ITEM_INGNAME0},
	{"道具_份1%", sizeof("道具_份1%"), LUA_DATALINE1 + ITEM_INGNAME1},
	{"道具_份2%", sizeof("道具_份2%"), LUA_DATALINE1 + ITEM_INGNAME2},
	{"道具_份3%", sizeof("道具_份3%"), LUA_DATALINE1 + ITEM_INGNAME3},
	{"道具_份4%", sizeof("道具_份4%"), LUA_DATALINE1 + ITEM_INGNAME4},

	{"道欄_頭位%", sizeof("道欄_頭位%"), CHAR_HEAD},
	{"道欄_身位%", sizeof("道欄_身位%"), CHAR_BODY},
	{"道欄_右手%", sizeof("道欄_右手%"), CHAR_ARM},
	{"道欄_飾1%", sizeof("道欄_飾1%"), CHAR_DECORATION1},
	{"道欄_飾2%", sizeof("道欄_飾2%"), CHAR_DECORATION2},
#ifdef _ITEM_EQUITSPACE
	{"道欄_左手%", sizeof("道欄_左手%"), CHAR_EQSHIELD},
	{"道欄_腰位%", sizeof("道欄_腰位%"), CHAR_EQBELT},
	{"道欄_腳位%", sizeof("道欄_腳位%"), CHAR_EQSHOES},
#endif
#ifdef _EQUIT_NEWGLOVE
	{"道欄_手套%", sizeof("道欄_手套%"), CHAR_EQGLOVE},
#endif
	{"道欄_1%", sizeof("道欄_1%"), CHAR_STARTITEMARRAY + 0},
	{"道欄_2%", sizeof("道欄_2%"), CHAR_STARTITEMARRAY + 1},
	{"道欄_3%", sizeof("道欄_3%"), CHAR_STARTITEMARRAY + 2},
	{"道欄_4%", sizeof("道欄_4%"), CHAR_STARTITEMARRAY + 3},
	{"道欄_5%", sizeof("道欄_5%"), CHAR_STARTITEMARRAY + 4},
	{"道欄_6%", sizeof("道欄_6%"), CHAR_STARTITEMARRAY + 5},
	{"道欄_7%", sizeof("道欄_7%"), CHAR_STARTITEMARRAY + 6},
	{"道欄_8%", sizeof("道欄_8%"), CHAR_STARTITEMARRAY + 7},
	{"道欄_9%", sizeof("道欄_9%"), CHAR_STARTITEMARRAY + 8},
	{"道欄_10%", sizeof("道欄_10%"), CHAR_STARTITEMARRAY + 9},
	{"道欄_11%", sizeof("道欄_11%"), CHAR_STARTITEMARRAY + 10},
	{"道欄_12%", sizeof("道欄_12%"), CHAR_STARTITEMARRAY + 11},
	{"道欄_13%", sizeof("道欄_13%"), CHAR_STARTITEMARRAY + 12},
	{"道欄_14%", sizeof("道欄_14%"), CHAR_STARTITEMARRAY + 13},
	{"道欄_15%", sizeof("道欄_15%"), CHAR_STARTITEMARRAY + 14},

	{"寵欄_1%", sizeof("寵欄_1%"), 0},
	{"寵欄_2%", sizeof("寵欄_2%"), 1},
	{"寵欄_3%", sizeof("寵欄_3%"), 2},
	{"寵欄_4%", sizeof("寵欄_4%"), 3},
	{"寵欄_5%", sizeof("寵欄_5%"), 4},
	
	{"隊員_1%", sizeof("隊員_1%"), 1},
	{"隊員_2%", sizeof("隊員_2%"), 2},
	{"隊員_3%", sizeof("隊員_3%"), 3},
	{"隊員_4%", sizeof("隊員_4%"), 4},

	{"IT_爪%", sizeof("IT_爪%"), ITEM_FIST},
	{"IT_斧頭%", sizeof("IT_斧頭%"), ITEM_AXE},
	{"IT_棍棒%", sizeof("IT_棍棒%"), ITEM_CLUB},
	{"IT_槍%", sizeof("IT_槍%"), ITEM_SPEAR},
	{"IT_弓%", sizeof("IT_弓%"), ITEM_BOW},
	{"IT_SHIELD%", sizeof("IT_SHIELD%"), ITEM_SHIELD},
	{"IT_HELM%", sizeof("IT_HELM%"), ITEM_HELM},
	{"IT_ARMOUR%", sizeof("IT_ARMOUR%"), ITEM_ARMOUR},
	{"IT_手環%", sizeof("IT_手環%"), ITEM_BRACELET},
	{"IT_樂器%", sizeof("IT_樂器%"), ITEM_MUSIC},
	{"IT_項鏈%", sizeof("IT_項鏈%"), ITEM_NECKLACE},
	{"IT_環%", sizeof("IT_環%"), ITEM_RING},
	{"IT_BELT%", sizeof("IT_BELT%"), ITEM_BELT},
	{"IT_耳環%", sizeof("IT_耳環%"), ITEM_EARRING},
	{"IT_鼻環%", sizeof("IT_鼻環%"), ITEM_NOSERING},
	{"IT_護身符%", sizeof("IT_護身符%"), ITEM_AMULET},
	{"IT_其他%", sizeof("IT_其他%"), ITEM_OTHER},
	{"IT_迴鏇標%", sizeof("IT_迴鏇標%"), ITEM_BOOMERANG},
	{"IT_投擲斧%", sizeof("IT_投擲斧%"), ITEM_BOUNDTHROW},
	{"IT_投擲石%", sizeof("IT_投擲石%"), ITEM_BREAKTHROW},
	{"IT_DISH%", sizeof("IT_DISH%"), ITEM_DISH},
#ifdef _ITEM_INSLAY
	{"IT_金屬%", sizeof("IT_金屬%"), ITEM_METAL},
	{"IT_首飾%", sizeof("IT_首飾%"), ITEM_JEWEL},
#endif
#ifdef _ITEM_CHECKWARES
	{"IT_貨物%", sizeof("IT_貨物%"), ITEM_WARES},
#endif
#ifdef _ITEM_EQUITSPACE
	{"IT_腰帶%", sizeof("IT_腰帶%"), ITEM_WBELT},
	{"IT_盾牌%", sizeof("IT_盾牌%"), ITEM_WSHIELD},
	{"IT_鞋子%", sizeof("IT_鞋子%"), ITEM_WSHOES},
#endif
#ifdef _EQUIT_NEWGLOVE 
	{"IT_手套%", sizeof("IT_手套%"), ITEM_WGLOVE},
#endif
#ifdef _JZ_PETEQU
	{"IT_寵頭套%", sizeof("IT_寵頭套%"), ITEM_PET_HEAD},
	{"IT_寵翅膀%", sizeof("IT_寵翅膀%"), ITEM_PET_WING},
	{"IT_寵牙套%", sizeof("IT_寵牙套%"), ITEM_PET_TOOTH},
	{"IT_寵胸甲%", sizeof("IT_寵胸甲%"), ITEM_PET_BREAST},
	{"IT_寵背甲%", sizeof("IT_寵背甲%"), ITEM_PET_BACK},
	{"IT_寵爪套%", sizeof("IT_寵爪套%"), ITEM_PET_CLAW},
	{"IT_寵護腳2%", sizeof("IT_寵護腳2%"), ITEM_PET_FEET},
	{"IT_寵護腳4%", sizeof("IT_寵護腳4%"), ITEM_PET_FEET4},
	{"IT_寵鰭套%", sizeof("IT_寵鰭套%"), ITEM_PET_FIN},
#endif

	{"家族_沒%", sizeof("家族_沒%"), FMMEMBER_NONE},
	{"家族_一般%", sizeof("家族_一般%"), FMMEMBER_MEMBER},
	{"家族_申請%", sizeof("家族_申請%"), FMMEMBER_APPLY},
	{"家族_族長%", sizeof("家族_族長%"), FMMEMBER_LEADER},
	{"家族_長老%", sizeof("家族_長老%"), FMMEMBER_ELDER},
	//{"家族_祭司", sizeof("家族_祭司"), FMMEMBER_INVITE},
	//{"家族_財務", sizeof("家族_財務"), FMMEMBER_BAILEE},
	//{"家族_副族", sizeof("家族_副族"), FMMEMBER_VICELEADER},

	{"戰類_普%", sizeof("戰類_普%"), BATTLE_TYPE_NONE},
	{"戰類_人怪%", sizeof("戰類_人怪%"), BATTLE_TYPE_P_vs_E},
	{"戰類_人人%", sizeof("戰類_人人%"), BATTLE_TYPE_P_vs_P},
	{"戰類_怪怪%", sizeof("戰類_怪怪%"), BATTLE_TYPE_E_vs_E},
	{"戰類_觀%", sizeof("戰類_觀%"), BATTLE_TYPE_WATCH},
	{"戰類_DP%", sizeof("戰類_DP%"), BATTLE_TYPE_DP_BATTLE},
	{"戰類_BOSS%", sizeof("戰類_BOSS%"), BATTLE_TYPE_BOSS_BATTLE},

	{"戰鬥_無%", sizeof("戰鬥_無%"), BATTLE_MODE_NONE},
	{"戰鬥_初%", sizeof("戰鬥_初%"), BATTLE_MODE_INIT},
	{"戰鬥_中%", sizeof("戰鬥_中%"), BATTLE_MODE_BATTLE},
	{"戰鬥_結束%", sizeof("戰鬥_結束%"), BATTLE_MODE_FINISH},
	{"戰鬥_結束中%", sizeof("戰鬥_結束中%"), BATTLE_MODE_STOP},
	{"戰鬥_觀初%", sizeof("戰鬥_觀初%"), BATTLE_MODE_WATCHBC},
	{"戰鬥_觀1%", sizeof("戰鬥_觀1%"), BATTLE_MODE_WATCHPRE},
	{"戰鬥_觀2%", sizeof("戰鬥_觀2%"), BATTLE_MODE_WATCHWAIT},
	{"戰鬥_觀3%", sizeof("戰鬥_觀3%"), BATTLE_MODE_WATCHMOVIE},
	{"戰鬥_觀4%", sizeof("戰鬥_觀4%"), BATTLE_MODE_WATCHAFTER},

	{"女孩%", sizeof("女孩%"), CHAR_IMAGETYPE_GIRL},
	{"男孩%", sizeof("男孩%"), CHAR_IMAGETYPE_BOY},
	{"男童%", sizeof("男童%"), CHAR_IMAGETYPE_CHILDBOY},
	{"女童%", sizeof("女童%"), CHAR_IMAGETYPE_CHILDGIRL},
	{"男人%", sizeof("男人%"), CHAR_IMAGETYPE_MAN},
	{"婦女%", sizeof("婦女%"), CHAR_IMAGETYPE_WOMAN},
	{"老人%", sizeof("老人%"), CHAR_IMAGETYPE_OLDMAN},
	{"狗%", sizeof("狗%"), CHAR_IMAGETYPE_DOG},

	{"對像_玩%", sizeof("對像_玩%"), CHAR_TYPEPLAYER},
	{"對像_怪%", sizeof("對像_怪%"), CHAR_TYPEENEMY},
	{"對像_寵%", sizeof("對像_寵%"), CHAR_TYPEPET},
	{"對像_NPC1%", sizeof("對像_NPC1%"), CHAR_TYPEDOOR},
	{"對像_NPC2%", sizeof("對像_NPC2%"), CHAR_TYPEBOX},
	{"對像_NPC3%", sizeof("對像_NPC3%"), CHAR_TYPEMSG},
	{"對像_NPC4%", sizeof("對像_NPC4%"), CHAR_TYPEWARP},
	{"對像_NPC5%", sizeof("對像_NPC5%"), CHAR_TYPESHOP},
	{"對像_NPC6%", sizeof("對像_NPC6%"), CHAR_TYPEHEALER},
	{"對像_NPC7%", sizeof("對像_NPC7%"), CHAR_TYPEOLDMAN},
	{"對像_NPC8%", sizeof("對像_NPC8%"), CHAR_TYPEROOMADMIN},
	{"對像_NPC9%", sizeof("對像_NPC9%"), CHAR_TYPETOWNPEOPLE},
	{"對像_NPC10%", sizeof("對像_NPC10%"), CHAR_TYPEDENGON},
	{"對像_NPC11%", sizeof("對像_NPC11%"), CHAR_TYPEADM},
	{"對像_NPC12%", sizeof("對像_NPC12%"), CHAR_TYPETEMPLE},
	{"對像_NPC13%", sizeof("對像_NPC13%"), CHAR_TYPESTORYTELLER},
	{"對像_NPC14%", sizeof("對像_NPC14%"), CHAR_TYPERANKING},
	{"對像_NPC15%", sizeof("對像_NPC15%"), CHAR_TYPEOTHERNPC},
	{"對像_NPC16%", sizeof("對像_NPC16%"), CHAR_TYPEPRINTPASSMAN},
	{"對像_NPC17%", sizeof("對像_NPC17%"), CHAR_TYPENPCENEMY},
	{"對像_NPC18%", sizeof("對像_NPC18%"), CHAR_TYPEACTION},
	{"對像_NPC19%", sizeof("對像_NPC19%"), CHAR_TYPEWINDOWMAN},
	{"對像_NPC20%", sizeof("對像_NPC20%"), CHAR_TYPESAVEPOINT},
	{"對像_NPC21%", sizeof("對像_NPC21%"), CHAR_TYPEWINDOWHEALER},
	{"對像_NPC22%", sizeof("對像_NPC22%"), CHAR_TYPEITEMSHOP},
	{"對像_NPC23%", sizeof("對像_NPC23%"), CHAR_TYPESTONESHOP},
	{"對像_NPC24%", sizeof("對像_NPC24%"), CHAR_TYPEDUELRANKING},
	{"對像_NPC25%", sizeof("對像_NPC25%"), CHAR_TYPEWARPMAN},
	{"對像_NPC26%", sizeof("對像_NPC26%"), CHAR_TYPEEVENT},
	{"對像_NPC27%", sizeof("對像_NPC27%"), CHAR_TYPEMIC},
	{"對像_NPC28%", sizeof("對像_NPC28%"), CHAR_TYPELUCKYMAN},
	{"對像_NPC29%", sizeof("對像_NPC29%"), CHAR_TYPEBUS},
	{"對像_NPC30%", sizeof("對像_NPC30%"), CHAR_TYPECHARM},
	{"對像_NPC31%", sizeof("對像_NPC31%"), CHAR_TYPECHECKMAN},
	{"對像_NPC32%", sizeof("對像_NPC32%"), CHAR_TYPEJANKEN},
	{"對像_NPC33%", sizeof("對像_NPC33%"), CHAR_TYPETRANSMIGRATION},
	{"對像_NPC34%", sizeof("對像_NPC34%"), CHAR_TYPEFMWARPMAN},
	{"對像_NPC35%", sizeof("對像_NPC35%"), CHAR_TYPEFMSCHEDULEMAN},
	{"對像_NPC36%", sizeof("對像_NPC36%"), CHAR_TYPEMANORSCHEDULEMAN},
#ifdef _SERVICE
	{"對像_NPC37%", sizeof("對像_NPC37%"), CHAR_TYPESTONESERVICEMAN},
#endif
#ifdef _GAMBLE_BANK
	{"對像_NPC38%", sizeof("對像_NPC38%"), CHAR_GAMBLEBANK},
#endif
#ifdef _NEW_WARPMAN
	{"對像_NPC39%", sizeof("對像_NPC39%"), CHAR_NEWNPCMAN},
#endif
#ifdef _MARKET_TRADE
	{"對像_NPC40%", sizeof("對像_NPC40%"), CHAR_MAPTRADEMAN},
#endif
#ifdef _GAMBLE_ROULETTE
	{"對像_NPC41%", sizeof("對像_NPC41%"), CHAR_GAMBLEROULETTE},
	{"對像_NPC42%", sizeof("對像_NPC42%"), CHAR_GAMBLEMASTER},
#endif
#ifdef _TRANSER_MAN
	{"對像_NPC43%", sizeof("對像_NPC43%"), CHAR_TRANSERMANS},
#endif
#ifdef _JZ_NEW_ADDMEMBERPOINT
	{"對像_NPC44%", sizeof("對像_NPC44%"), CHAR_MEMBERMANS},
#endif
#ifdef _NPC_SELLSTH
	{"對像_NPC45%", sizeof("對像_NPC45%"), CHAR_SELLSTHMAN},
#endif
#ifdef _NPC_MAKEPAIR
	{"對像_NPC46%", sizeof("對像_NPC46%"), CHAR_MAKEPAIR},
#endif
#ifdef _NPC_FUSION
	{"對像_NPC47%", sizeof("對像_NPC47%"), CHAR_PETFUSIONMAN},
#endif
#ifdef _PAUCTION_MAN
//	{"對像_NPC48%", sizeof("對像_NPC48%"), CHAR_PAUCTIONMAN},
#endif
#ifdef _ITEM_NPCCHANGE
	{"對像_NPC49%", sizeof("對像_NPC49%"), CHAR_ITEMCHANGENPC},
#endif
#ifdef _CFREE_petskill
	{"對像_NPC50%", sizeof("對像_NPC50%"), CHAR_FREESKILLSHOP},
#endif
#ifdef _PETRACE
	{"對像_NPC51%", sizeof("對像_NPC51%"), CHAR_PETRACEMASTER},
	{"對像_NPC52%", sizeof("對像_NPC52%"), CHAR_PETRACEPET},
#endif
#ifdef _AUCTIONEER
	{"對像_NPC53%", sizeof("對像_NPC53%"), CHAR_TYPEAUCTIONEER},
#endif
#ifdef _ALLDOMAN // (不可開) Syu ADD 排行榜NPC
	{"對像_NPC54%", sizeof("對像_NPC54%"), CHAR_TYPEALLDOMAN},
#endif
	{"對像_NPC55%", sizeof("對像_NPC55%"), CHAR_TYPEPETMAKER},
#ifdef _NPC_WELFARE
	{"對像_NPC56%", sizeof("對像_NPC56%"), CHAR_TYPEWELFARE},
#endif
#ifdef _NPC_VERYWELFARE
	{"對像_NPC57%", sizeof("對像_NPC57%"), CHAR_TYPEVERYWELFARE},
#endif
#ifdef _NPC_WELFARE_2				// WON ADD 職業NPC-2
	{"對像_NPC58%", sizeof("對像_NPC58%"), CHAR_TYPEWELFARE2},
#endif
#ifdef _RACEMAN
	{"對像_NPC59%", sizeof("對像_NPC59%"), CHAR_RACEMAN},
#endif

	{"物件_沒%", sizeof("物件_沒%"), OBJTYPE_NOUSE},
	{"物件_人%", sizeof("物件_人%"), OBJTYPE_CHARA},
	{"物件_道%", sizeof("物件_道%"), OBJTYPE_ITEM},
	{"物件_幣%", sizeof("物件_幣%"), OBJTYPE_GOLD},
#ifdef _NPCSERVER_NEW
	{"物件_NPC%", sizeof("物件_NPC%"), OBJTYPE_NPCSCHARA},
#endif
#ifdef _MAP_WARPPOINT
	{"物件_傳%", sizeof("物件_傳%"), OBJTYPE_WARPPOINT},
#endif

	{"按鈕_沒%", sizeof("按鈕_沒%"), WINDOW_BUTTONTYPE_NONE},
	{"按鈕_確定%", sizeof("按鈕_確定%"), WINDOW_BUTTONTYPE_OK},
	{"按鈕_關閉%", sizeof("按鈕_關閉%"), WINDOW_BUTTONTYPE_CANCEL},
	{"按鈕_是%", sizeof("按鈕_是%"), WINDOW_BUTTONTYPE_YES},
	{"按鈕_否%", sizeof("按鈕_否%"), WINDOW_BUTTONTYPE_NO},
	{"按鈕_上一頁%", sizeof("按鈕_上一頁%"), WINDOW_BUTTONTYPE_PREV},
	{"按鈕_下一頁%", sizeof("按鈕_下一頁%"), WINDOW_BUTTONTYPE_NEXT},

	{"組隊_沒隊%", sizeof("組隊_沒隊%"), CHAR_PARTY_NONE},
	{"組隊_隊長%", sizeof("組隊_隊長%"), CHAR_PARTY_LEADER},
	{"組隊_隊員%", sizeof("組隊_隊員%"), CHAR_PARTY_CLIENT},

	{"左上%", sizeof("左上%"), 0},
	{"上%", sizeof("上%"), 1},
	{"右上%", sizeof("右上%"), 2},
	{"右%", sizeof("右%"), 3},
	{"右下%", sizeof("右下%"), 4},
	{"下%", sizeof("下%"), 5},
	{"左下%", sizeof("左下%"), 6},
	{"左%", sizeof("左%"), 7},

	{"白色%", sizeof("白色%"), CHAR_COLORWHITE},
	{"青色%", sizeof("青色%"), CHAR_COLORCYAN},
	{"紫色%", sizeof("紫色%"), CHAR_COLORPURPLE},
	{"藍色%", sizeof("藍色%"), CHAR_COLORBLUE},
	{"黃色%", sizeof("黃色%"), CHAR_COLORYELLOW},
	{"綠色%", sizeof("綠色%"), CHAR_COLORGREEN},
	{"紅色%", sizeof("紅色%"), CHAR_COLORRED},
	{"灰色%", sizeof("灰色%"), CHAR_COLORGRAY},
	{"深藍色%", sizeof("深藍色%"), CHAR_COLORBLUE2},
	{"深綠色%", sizeof("深綠色%"), CHAR_COLORGREEN2},
//	{"黑色%", sizeof("黑色%"), CHAR_COLORBLACK},

	{"隊更新_OBJ%", sizeof("隊更新_OBJ%"), CHAR_N_STRING_OBJINDEX},
	{"隊更新_LV%", sizeof("隊更新_LV%"), CHAR_N_STRING_LV},
	{"隊更新_MAXHP%", sizeof("隊更新_MAXHP%"), CHAR_N_STRING_MAXHP},
	{"隊更新_HP%", sizeof("隊更新_HP%"), CHAR_N_STRING_HP},
	{"隊更新_MP%", sizeof("隊更新_MP%"), CHAR_N_STRING_MP},
	{"隊更新_名字%", sizeof("隊更新_名字%"), CHAR_N_STRING_NAME},
	
	{"更新3_HP%", sizeof("更新3_HP%"), CHAR_P_STRING_HP},
	{"更新3_MAXHP%", sizeof("更新3_MAXHP%"), CHAR_P_STRING_MAXHP},
	{"更新3_MP%", sizeof("更新3_MP%"), CHAR_P_STRING_MP},
	{"更新3_MAXMP%", sizeof("更新3_MAXMP%"), CHAR_P_STRING_MAXMP},
	{"更新3_體%", sizeof("更新3_體%"), CHAR_P_STRING_VITAL},
	{"更新3_腕%", sizeof("更新3_腕%"), CHAR_P_STRING_STR},
	{"更新3_耐%", sizeof("更新3_耐%"), CHAR_P_STRING_TOUGH},
	{"更新3_速%", sizeof("更新3_速%"), CHAR_P_STRING_DEX},
	{"更新3_經驗%", sizeof("更新3_經驗%"), CHAR_P_STRING_EXP},
	{"更新3_下一級經驗%", sizeof("更新3_下一級經驗%"), CHAR_P_STRING_NEXTEXP},
	{"更新3_等級%", sizeof("更新3_等級%"), CHAR_P_STRING_LV},
	{"更新3_攻擊%", sizeof("更新3_攻擊%"), CHAR_P_STRING_ATK},
	{"更新3_防禦%", sizeof("更新3_防禦%"), CHAR_P_STRING_DEF},
	{"更新3_敏捷%", sizeof("更新3_敏捷%"), CHAR_P_STRING_QUICK},
	{"更新3_魅力%", sizeof("更新3_魅力%"), CHAR_P_STRING_CHARM},
	{"更新3_運氣%", sizeof("更新3_運氣%"), CHAR_P_STRING_LUCK},
	{"更新3_地屬性%", sizeof("更新3_地屬性%"), CHAR_P_STRING_EARTH},
	{"更新3_水屬性%", sizeof("更新3_水屬性%"), CHAR_P_STRING_WATER},
	{"更新3_火屬性%", sizeof("更新3_火屬性%"), CHAR_P_STRING_FIRE},
	{"更新3_風屬性%", sizeof("更新3_風屬性%"), CHAR_P_STRING_WIND},
	{"更新3_石幣%", sizeof("更新3_石幣%"), CHAR_P_STRING_GOLD},
	{"更新3_稱號%", sizeof("更新3_稱號%"), CHAR_P_STRING_TITLE},
	{"更新3_DP%", sizeof("更新3_DP%"), CHAR_P_STRING_DUELPOINT},
	{"更新3_轉數%", sizeof("更新3_轉數%"), CHAR_P_STRING_TRANSMIGRATION},
	{"更新3_名稱%", sizeof("更新3_名稱%"), CHAR_P_STRING_NAME},
	{"更新3_昵稱%", sizeof("更新3_昵稱%"), CHAR_P_STRING_OWNTITLE},
	{"更新3_騎寵%", sizeof("更新3_騎寵%"), CHAR_P_STRING_RIDEPET},
	{"更新3_學騎等級%", sizeof("更新3_學騎等級%"), CHAR_P_STRING_LEARNRIDE},
	{"更新3_形象%", sizeof("更新3_形象%"), CHAR_P_STRING_BASEBASEIMAGENUMBER},
	{"更新3_天行者模式%", sizeof("更新3_天行者模式%"), CHAR_P_STRING_SKYWALKER},
	{"更新3_調試模式%", sizeof("更新3_調試模式%"), CHAR_P_STRING_DEBUGMODE},
	{"精靈_名%", sizeof("精靈_名%"), LUA_DATALINE1 + MAGIC_NAME},
	{"精靈_描述%", sizeof("精靈_描述%"), LUA_DATALINE1 + MAGIC_COMMENT},
	{"精靈_函數名%", sizeof("精靈_函數名%"), LUA_DATALINE1 + MAGIC_FUNCNAME},
	{"精靈_選項%", sizeof("精靈_選項%"), LUA_DATALINE1 + MAGIC_OPTION},
	{"精靈_ID%", sizeof("精靈_ID%"), LUA_DATALINE0 + MAGIC_ID},
	{"精靈_FIELD%", sizeof("精靈_FIELD%"), LUA_DATALINE0 + MAGIC_FIELD},
	{"精靈_目標%", sizeof("精靈_目標%"), LUA_DATALINE0 + MAGIC_TARGET},
	{"精靈_死目標%", sizeof("精靈_死目標%"), LUA_DATALINE0 + MAGIC_TARGET_DEADFLG},
	{"精靈_IDX%", sizeof("精靈_IDX%"), LUA_DATALINE0 + MAGIC_IDX},
	{NULL, 0, 0},
};

#endif
