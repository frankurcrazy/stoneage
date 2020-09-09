#ifndef _FIELD_H_ 
#define _FIELD_H_

#include<time.h>

// ??????????
#define FIELD_BTN_PUSH_WAIT			500		// 0.5

// ?????????
#define FIELD_MAIL_LAMP_FLASH_TIME	1000	// 1??

enum
{
	FIELD_FUNC_MENU,
	FIELD_FUNC_CARD,
	FIELD_FUNC_PARTY,
	FIELD_FUNC_JOIN_BATTLE,
	FIELD_FUNC_DUEL,
	FIELD_FUNC_ACT,
	FIELD_FUNC_TRADE,	// Robin 04/12 trade
	FIELD_FUNC_CHANNEL,
#ifdef __HELP
	FIELD_FUNC_HELP,	//CARY
#endif
#ifdef __PHONEMESSAGE
	FIELD_FUNC_MSG,     //LeiBoy
#endif
#ifdef _STREET_VENDOR
	FIELD_FUNC_STREET_VENDOR,
#else
	#ifdef _TABLEOFSKILL
	FIELD_FUNC_SKILL,
	#endif
#endif

#ifdef _FRIENDCHANNEL			//ROG ADD 好友頻道
	FIELD_FUNC_CHATROOM,
#endif

#ifdef _ANGEL_SUMMON
	FIELD_FUNC_ANGEL,
#endif

#ifdef _TEACHER_SYSTEM
	FIELD_FUNC_TEACHER,
#endif
#ifdef _MO_SIGN_IN
	FIELD_FUNC_SIGNIN,						
#endif 
#ifdef _NEWSHOP_
	FIELD_FUNC_MARKET,					
#endif
#ifdef _CHANGETEAM_ 
	FIELD_FUNC_CHANGETEAM,
#endif
#ifdef _RED_MEMOY_
	FIELD_FUNC_RED_MEMOY,
#endif
	FIELD_FUNC_END
};

#ifdef _PET_ITEM
typedef struct SPetItemInfo
{
	int bmpNo;										// 圖號
	int color;										// 文字顔色
	char memo[ITEM_MEMO_LEN+1];						// 說明
	char name[ITEM_NAME_LEN+1];						// 名字
	char damage[16];								// 耐久度
}PetItemInfo;
#endif

#ifdef _STREET_VENDOR
#define MAX_SELL_ITEM 20							// 道具加寵物共可賣二十個
typedef struct _Show_Sell_Item{
	int index;										// 索引
	int pile;										// 數量
	int price;										// 價格
	bool needGetPrice;								// 是否要得到價格
	bool usage;										// 是否使用中
	char name[ITEM_NAME_LEN+1];						// 名字
	char freeName[ITEM_NAME_LEN+1];					// 名字
	char kind;										// 道具或是寵物 0:道具 1:寵物
}Show_Sell_Item;

typedef struct _Show_Vendor_Item{
	int bmpNo;										// 圖號
	int pile;										// 數量
	int price;										// 價格
	int color;										// 文字顔色
	int level;										// 等級
	int maxhp,attack,defence,dex;					// 四圍
	int earth,water,fire,wind,fidelity;				// 四屬性及忠誠度
	int maxSkill;									// 寵技數量
	int index;										// 在server的儲存位置
	bool usage;										// 是否使用中
	bool bBuy;										// 是否要買
	bool bGetData;									// 是否已接收到詳細資料
	char name[ITEM_NAME_LEN+1];						// 名字
	char freeName[ITEM_NAME_LEN+1];					// 名字
	char memo[ITEM_MEMO_LEN+1];						// 說明
	char damage[20];								// 耐久度
	char skillname[MAX_SKILL][SKILL_NAME_LEN+1];	// 寵技名稱
	char kind;										// 道具或是寵物 0:道具 1:寵物
	char trans;										// 轉生數
#ifdef _PET_ITEM
	PetItemInfo oPetItemInfo[MAX_PET_ITEM];			// 寵物身上的道具
#endif
#ifdef _NPC_ITEMUP
	int itemup;
#endif
#ifdef _PETCOM_
	int ylv,yhp,yack,ydef,ydex;				            //初始四圍
#endif
}Show_Vendor_Item;

#endif

#ifdef _JOBDAILY

#define MAXMISSION	300 
typedef struct _JOBDAILY{
	int JobId;								// 任務編號
	char explain[200];						// 任務說明
	char state[10];							// 狀態
}JOBDAILY;

#endif

#ifdef _FRIENDCHANNEL			//ROG ADD 好友頻道
	extern short chatRoomBtn;
	extern short SelRoomBtn;
#endif

#ifdef _ANGEL_SUMMON
extern int angelFlag;
extern int angelRecvType;
extern int angelRecvButton;
extern char angelMsg[];
#endif

extern short drawTimeAnimeFlag;

extern short etcSendFlag;

extern short actBtn;
extern short menuBtn;
extern short mailLamp;

extern unsigned int fieldInfoTime;

extern struct tm serverAliveTime;
extern time_t serverAliveLongTime;


void initFieldProc( void );
void resetFieldProc( void );
void fieldProc( void );
void fieldProc2( void );
void drawField( void );

BOOL checkFieldMenuFlag( void );

void closeCharActionAnimeChange( void );
void closeEtcSwitch( void );
void closeJoinChannelWN( void );

int disconnectServer( void );

void drawFieldInfoWin( void );

void actionShortCutKeyProc( void );

#ifdef _SPECIALSPACEANIM	// Syu ADD 特殊場景動畫配置
	#ifdef _SURFACE_ANIM        //動態地上物顯示
//#define TOTAL_ANIM 5 //陣列總量
#ifdef _SA_VERSION_25
		#define MAX_ANIM   256 //同一個floor限定最大量動畫數
#endif

	#else
		#ifdef _MOON_FAIRYLAND       // ROG ADD 月之仙境
			#define TOTAL_ANIM 5 //陣列總量
			#define MAX_ANIM   4 //同一個floor內現存最大量Anim
		#else
			#define TOTAL_ANIM 1 //陣列總量
			#define MAX_ANIM  1  //同一個floor內現存最大量Anim
	#endif
#endif

void SpecAnim ( int ) ; 
void ReleaseSpecAnim( void );

#endif
#endif
