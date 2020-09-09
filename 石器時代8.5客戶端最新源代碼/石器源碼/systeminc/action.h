/************************/
/*	action.h			*/
/************************/
#ifndef _ACTION_H_
#define _ACTION_H_

#include "version.h"
#include "../newproto/autil.h"
//處理優先順序
enum{
	PRIO_TOP,			//最優先

	PRIO_CHR,			//同Char

	PRIO_BG,			/* ?? 	*/
	PRIO_JIKI,			/* ? 	*/
	PRIO_ENEMY,			/*  		*/
	PRIO_ENEMY_TAMA,	/*  	*/
	PRIO_JIKI_TAMA,		/* ? 	*/
	PRIO_ITEM,			/* ????	*/
	PRIO_BOSS,			/* ??		*/
	PRIO_GAME_OVER,		/* GAME OVER */
	PRIO_BTM = 255		/* ?? 	*/
};

//Action狀態
enum{
	ACT_STATE_ACT = 0,	//通常狀態
	ACT_STATE_DEAD		//死亡狀態
};
//屬性
#define ACT_ATR_HIDE 			( 1 <<  1 )	// 不顯示/*  */
#define ACT_ATR_HIT 			( 1 <<  2 )	// 可以被點選/* ????? */
#define ACT_ATR_HIT_BOX 		( 1 <<  3 )	// 可以被點選的外框/* ??? + ???? */
#define ACT_ATR_INFO 			( 1 <<  4 )	// 顯示齣相關訊息/* ?????? */
#define ACT_ATR_HIDE2 			( 1 <<  5 )	// 不顯示 + 可以被點選/* +????? */
#define ACT_ATR_BTL_CMD_END 	( 1 <<  6 )	// 戰鬥指令輸入完成旗標,未完成輸入的玩傢會動,完成則不會動/* ????????? */
#define ACT_ATR_TYPE_PC 		( 1 <<  7 )	// 玩傢/* ?? */
#define ACT_ATR_TYPE_OTHER_PC 	( 1 <<  8 )	// 彆的玩傢/* ??? */
#define ACT_ATR_TYPE_PET 		( 1 <<  9 )	/* ??? */
#define ACT_ATR_TYPE_ITEM 		( 1 << 10 )	/* ???? */
#define ACT_ATR_TYPE_GOLD 		( 1 << 11 )	/* ?? */
#define ACT_ATR_TYPE_OTHER 		( 1 << 12 )	/* ??????伡???? */
#define ACT_ATR_HIT_BOX_ALL1 	( 1 << 13 )	// 可以被點選 + 外框顯示1
#define ACT_ATR_HIT_BOX_ALL2 	( 1 << 14 )	// 可以被點選 + 外框顯示2
#define ACT_ATR_HIT_BOX_ALL3 	( 1 << 15 )	// 可以被點選 + 外框顯示3
#define ACT_ATR_HIT_BOX_ALL4 	( 1 << 16 )	// 可以被點選 + 外框顯示3
#define ACT_ATR_TRAVEL 			( 1 << 17 )	/* ??? */

#define ACT_ATR_HIT_BOX_COL1	( 1 << 18 )	// 左上第一列
#define ACT_ATR_HIT_BOX_COL2	( 1 << 19 ) // 左上第二列
#define ACT_ATR_HIT_BOX_COL3	( 1 << 20 ) // 右下第一列
#define ACT_ATR_HIT_BOX_COL4	( 1 << 21 ) // 右下第二列
#define ACT_ATR_HIT_BOX_COL5	( 1 << 22 )	// 左上第一列
#define ACT_ATR_HIT_BOX_COL6	( 1 << 23 ) // 左上第二列
#define ACT_ATR_HIT_BOX_COL7	( 1 << 24 ) // 右下第一列
#define ACT_ATR_HIT_BOX_COL8	( 1 << 25 ) // 右下第二列




/* ?????? **********************************************************/
struct action{
	struct 	action *pPrev, *pNext;			//上一個及下一個action指標
	void 	( *func )( struct action * );	//action所執行的function的指標
	void 	*pYobi;							//備用的struct指標
	void 	*pOther;						//其它用途struct指標
	UCHAR 	prio;							//action處理時的優先順序
	UCHAR 	dispPrio;						//秀圖時的優先順序	
	int 	x, y;							//圖的座標
	int		hitDispNo;						//是否命中目標編號
	BOOL	deathFlag;						//此action是否死亡旗標	
	int 	dx, dy;							//秀圖座標位移量
	int 	dir;							//方嚮
	int 	delta;  						//閤成嚮量
	
	char 	name[ 29 ];						//名字
	char 	freeName[ 33 ];					//free name
	int 	hp;		
#ifdef _PET_ITEM
	int		iOldHp;
#endif
	int 	maxHp;						
	int 	mp;							
	int 	maxMp;						
	int 	level;						
	int 	status;						
	int 	itemNameColor;					/* ?????? */
	int		charNameColor;					// ?????????????
	
	int		bmpNo;							//圖號
	int		bmpNo_bak;							//備份圖號
	int		atr;							//屬性
	int		state;							//狀態
	int		actNo;							//行動編號
	int		damage;						

	int		gx, gy;							//在目前的地圖上的座標
	int		nextGx, nextGy;					//下一個座標
	int		bufGx[10], bufGy[10];			//從目前座標到下一個座標之間座標的buffer
	short	bufCount;						//設定目前要走到那一個座標
	short	walkFlag;						// ??????????????????????
	float	mx, my;							//地圖座標
	float	vx, vy;							// ??

//屬性
	short 	earth;							// 佋 
	short 	water;							// ? 
	short 	fire;							// ? 
	short 	wind;							// ? 
//rader使用
	int		dirCnt;							// ???????
//gemini使用
	int		spd;							//移動的速度(0~63)( ?????? )
	int		crs;							//方嚮(0~31)(正上方為0,順時鍾方嚮) ?( ???? )( ?????? )
	int		h_mini;							// ??
	int		v_mini;							// ?
//pattern使用
	int		anim_chr_no;					//人物的編號(anim_tbl.h的編號)
	int		anim_chr_no_bak;				//上一次的人物編號
	int		anim_no;						//人物的動作編號
	int		anim_no_bak;					//上一次的人物編號
	int		anim_ang;						//動作的方嚮(0~7)(下0)
	int		anim_ang_bak;					//上一次的方嚮
	int		anim_cnt;						//第幾張frame
	int		anim_frame_cnt;					//這張frame停留時間
	int		anim_x;							//X座標(Sprbin+Adrnbin)
	int		anim_y;							//Y座標(Sprbin+Adrnbin)
	int		anim_hit;						// ???
	// shan add +1
	char    fmname[33];			            // 傢族名稱
	// Robin 0728 ride Pet
	int		onRide;
	char	petName[16+1];
	int		petLevel;
	int		petHp;
	int		petMaxHp;
	int		petDamage;
	int		petFall;
#ifdef _MIND_ICON
	unsigned int sMindIcon;
#endif
#ifdef _SHOWFAMILYBADGE_
	unsigned int sFamilyIcon;
#endif
#ifdef FAMILY_MANOR_
	unsigned int mFamilyIcon;
#endif
#ifdef _CHAR_MANOR_
	unsigned int mManorIcon;
#endif
#ifdef _CHARTITLE_STR_
	TITLE_STR TitleText;
#endif
#ifdef _CHARTITLE_
	unsigned int TitleIcon;
#endif
#ifdef _NPC_EVENT_NOTICE
	int noticeNo;
#endif

#ifdef _SKILL_ROAR  
	int		petRoar;		//大吼(剋年獸)
#endif 
#ifdef _SKILL_SELFEXPLODE //自爆
	int		petSelfExplode;		
#endif 
#ifdef _MAGIC_DEEPPOISION   //劇毒
	int		petDeepPoision;		 
#endif 

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	int		profession_class;
#endif
//#ifdef _BATTLESKILL				// (不可開) Syu ADD 戰鬥技能介麵
	int		warrioreffect; 
//#endif
#ifdef _GM_IDENTIFY		// Rog ADD GM識彆
	char gm_name[33];
#endif
#ifdef _STREET_VENDOR
	char szStreetVendorTitle[64];
#endif
#ifdef _NPC_PICTURE
	int picture;
	int picturetemp;
#endif
#ifdef _PETSKILL_RIDE
	int saveride;
#endif
#ifdef _MOUSE_DBL_CLICK
	int index;	// 禁斷!! Server中的charaindex
#endif

#ifdef _SFUMATO
	int sfumato;		// 二次渲染圖層色彩
#endif
};

typedef struct action ACTION;

/* ?????????????????? */
extern ACTION *pActTop;
extern ACTION *pActBtm;

/* ?????? */
extern ACTION *pJiki;

#ifdef _STONDEBUG_		
/* ?????????? */
extern int ActCnt;
#endif

/* ?????????? *****************************************************/
ACTION *GetAction( UCHAR prio, UINT yobiSize );

/* ??????????? *****************************************************/
void InitAction( void );

/* ????????? *********************************************************/
void RunAction( void );

/* ????????????************************************************/
void DeathAction( ACTION *pAct );

/* ??????? *******************************************************/
void DeathAllAction( void );

/* ???????????? ***********************************************/
void ClearAction( ACTION *pAct );

/* ???????? *********************************************************/
void EndAction( void );

#endif
