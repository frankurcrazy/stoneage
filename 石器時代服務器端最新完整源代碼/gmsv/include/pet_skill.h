#ifndef __PET_SKILL_H__
#define __PET_SKILL_H__

#include "util.h"

typedef enum
{
	PETSKILL_FIELD_ALL,			/* 允屯化及樺赭匹銀尹月 */
	PETSKILL_FIELD_BATTLE,				/* 爵    及心 */
	PETSKILL_FIELD_MAP,				/* 騷橘穴永皿曉及心 */

}PETSKILL_FIELDTYPE;

typedef enum
{
	PETSKILL_TARGET_MYSELF,		/* 憤坌及心 */
	PETSKILL_TARGET_OTHER,			/* 職及諦  憤坌殖戈) */
	PETSKILL_TARGET_ALLMYSIDE,		/*     蟈   */
	PETSKILL_TARGET_ALLOTHERSIDE,	/* 鍬澎礎蟈   */
	PETSKILL_TARGET_ALL,			/* 蟈化 */
	PETSKILL_TARGET_NONE,			/* 簿手薊  請  卅中［  豢支凶戶及凜 */
	PETSKILL_TARGET_OTHERWITHOUTMYSELF,/* 職及諦  憤坌殖引卅中) */
	PETSKILL_TARGET_WITHOUTMYSELFANDPET,  /* 憤坌午矢永玄動陸 */
}PETSKILL_TARGETTYPE;

typedef enum
{
	PETSKILL_ID,
	PETSKILL_FIELD,
	PETSKILL_TARGET,
#ifdef _PETSKILL2_TXT
	PETSKILL_USETYPE,
#endif
	PETSKILL_COST,
	PETSKILL_ILLEGAL,
	PETSKILL_DATAINTNUM,
}PETSKILL_DATAINT;

typedef enum
{
	PETSKILL_NAME,					/*      */
	PETSKILL_COMMENT,				/* 戊丟件玄*/
	PETSKILL_FUNCNAME,				/* 楮醒   */
	PETSKILL_OPTION,				/* 左皿撲亦件 */
#ifdef _CFREE_petskill
	PETSKILL_FREE,					/*條件*/
	PETSKILL_KINDCODE,				/*種類碼*/
#endif

	PETSKILL_DATACHARNUM,
}PETSKILL_DATACHAR;

typedef struct tagPetskill
{
	int			data[PETSKILL_DATAINTNUM];
	STRING64	string[PETSKILL_DATACHARNUM];

}Petskill;

typedef int (*PETSKILL_CALLFUNC)( int, int, int, char * );

INLINE BOOL PETSKILL_CHECKINDEX( int index );
INLINE int PETSKILL_getInt( int index, PETSKILL_DATAINT element);
INLINE int PETSKILL_setInt( int index, PETSKILL_DATAINT element, int data);
INLINE char* PETSKILL_getChar( int index, PETSKILL_DATACHAR element);
INLINE BOOL PETSKILL_setChar( int index ,PETSKILL_DATACHAR element, char* new );
int PETSKILL_getPetskillNum( void);

#define		PETSKILL_GetArray( charaindex, havepetskill)	_PETSKILL_GetArray( __FILE__, __LINE__, charaindex, havepetskill)
int _PETSKILL_GetArray( char *file, int line, int charaindex, int havepetskill );

BOOL PETSKILL_initPetskill( char *filename);
BOOL PETSKILL_reinitPetskill( void );
int PETSKILL_getPetskillArray( int petskillid);
PETSKILL_CALLFUNC PETSKILL_getPetskillFuncPointer(char* name);

int PETSKILL_Use(
	int charaindex,
	int toindex,
	int array,
	char *data
	//BOOL isCLI	// Robin 2001/02/26 if owner is player
);

int PETSKILL_ContinuationAttack(
	int charaindex,
	int toindex,
	int array,
	char *data
);
int PETSKILL_ChargeAttack(
	int charaindex,
	int toindex,
	int array,
	char *data
);


#define PETSKILL_ID_GBREAK		0	// 布□玉皮伊奶弁
#define PETSKILL_ID_RENZOKU		1	//   糧  猾
#define PETSKILL_ID_GUARDIAN	2	// 鏑舅甩民跤
#define PETSKILL_ID_CHARGE		3	// 民乓□斥  猾
#define PETSKILL_ID_ICHIGEKI	100	// 域猾  誚
#define PETSKILL_ID_POWERBALANCE 110	//     及諷

//**********************************************************************
//
//  檗  -- 職諦毛潮曰卅互日  猾
//
int PETSKILL_Guardian(
	int charaindex,
	int toindex,
	int array,
	char *data
);
//
//**********************************************************************

int PETSKILL_PowerBalance(
	int charaindex,
	int toindex,
	int array,
	char *data
);

//**********************************************************************
//
//  檗  -- 雄  分互莢  今木月割  互嫖中
//
int PETSKILL_Mighty(
	int charaindex,
	int toindex,
	int array,
	char *data
);
//
//**********************************************************************


//**********************************************************************
//
//  檗  -- 旦  □正旦唱橘  猾
//
int PETSKILL_StatusChange(
	int charaindex,
	int toindex,
	int array,
	char *data

);
//
//**********************************************************************


//*******************************************************
//
// 檗  -- 騷橘  猾
//
int PETSKILL_NormalAttack(
	int charaindex,
	int toindex,
	int array,
	char *data

);


#ifdef _INVERSION_PETSKILL
int PETSKILL_Inversion(
	int charaindex,
	int toindex,
	int array,
	char *data

);
#endif

#ifdef _MASSAGE_PETSKILL
int PETSKILL_Massage(
	int charaindex,
	int toindex,
	int array,
	char *data

);
#endif

#ifdef _PETOUT_PETSKILL
int PETSKILL_Petout(
	int charaindex,
	int toindex,
	int array,
	char *data

);
#endif

//
//*******************************************************

//*******************************************************
//
// 檗  -- 騷橘  豢
//
int PETSKILL_NormalGuard(
	int charaindex,
	int toindex,
	int array,
	char *data

);
//
//*******************************************************

//*******************************************************
// 檗  -- 謹窗(窒手仄卅中)
//
int PETSKILL_None(
	int charaindex,
	int toindex,
	int array,
	char *data

);
//
//*******************************************************

//*******************************************************
// 檗  -- 嘩萄域蔥(悵木化ㄠ正□件  卞鍬澎及    井日  猾)
//
int PETSKILL_EarthRound(
	int charaindex,
	int toNo,
	int array,
	char *data

);
//
//*******************************************************

//*******************************************************
// 檗  -- 布□玉皮伊奶弁
//
int PETSKILL_GuardBreak(
	int charaindex,
	int toNo,
	int array,
	char *data

);
///////////////////////////////////////////
#ifdef _SKILL_GUARDBREAK2//破除防禦2 vincent add 2002/05/20
int PETSKILL_GuardBreak2(
	int charaindex,
	int toNo,
	int array,
	char *data

);
#endif
//
//*******************************************************
//*******************************************************
// 檗  --     木
//
int PETSKILL_Abduct(
	int charaindex,
	int toNo,
	int array,
	char *data

);
//
//*******************************************************
//*******************************************************
// 檗  --   戈
int PETSKILL_Steal(
	int charaindex,
	int toNo,
	int array,
	char *data

);
//*******************************************************
#ifdef _BATTLESTEAL_FIX
int PETSKILL_StealMoney(
	int charaindex,
	int toNo,
	int array,
	char *data

);
#endif

#ifdef _ITEM_INSLAY
int PETSKILL_Inslay(
	int index,
	int toNo,
	int array,
	char *data

);
#endif

#ifdef _PETSKILL_FIXITEM
int PETSKILL_Fixitem(
	int index,
	int toNo,
	int array,
	char *data

);
#endif

// 檗  -- 失奶  丞寜嶽
//
int PETSKILL_Merge(
	int charaindex,
	int toNo,
	int array,
	char *data

);
//
//*******************************************************

//*******************************************************
// 檗  -- 用□布□玉
//
int PETSKILL_NoGuard(
	int charaindex,
	int toNo,
	int array,
	char *data

);
//
//*******************************************************



// Terry add 2001/11/05
#ifdef _ATTACK_MAGIC
int PETSKILL_AttackMagic(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _VARY_WOLF
int PETSKILL_Vary( int cindex, int tindex, int id, char* data);
#endif

#ifdef _SKILL_WILDVIOLENT_ATT
//vincent add 2002/05/16
int PETSKILL_WildViolentAttack(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_SPEEDY_ATT
//vincent add 2002/05/16
int PETSKILL_SpeedyAttack(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_SACRIFICE
//vincent add 2002/05/30
int PETSKILL_Sacrifice(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_REFRESH
//vincent add 2002/08/08
int PETSKILL_Refresh(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_WEAKEN  //vincent寵技:虛弱
int PETSKILL_Weaken(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_DEEPPOISON  //vincent寵技:劇毒
int PETSKILL_Deeppoison(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_BARRIER  //vincent寵技:魔障
int PETSKILL_Barrier(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_NOCAST  //vincent寵技:沉默
int PETSKILL_Nocast(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _SKILL_ROAR //vincent寵技:大吼
int PETSKILL_Roar(
	int charaindex,
	int toindex,
	int array,
	char *data
);
#endif

#ifdef _PSKILL_FALLGROUND
int PETSKILL_FallGround( int charaindex, int toNo, int array, char *data );
#endif
#ifdef _PETSKILL_EXPLODE
int PETSKILL_Explode( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PRO_BATTLEENEMYSKILL
int ENEMYSKILL_ReLife( int enemyindex, int toNo, int array, char *data );
int ENEMYSKILL_ReHP( int enemyindex, int toNo, int array, char *data );

int ENEMYSKILL_EnemyHelp( int enemyindex, int toNo, int array, char *data );
#endif

#ifdef _SKILL_DAMAGETOHP
int PETSKILL_DamageToHp( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_TIMID
int PETSKILL_BattleTimid( int charaindex, int toNo, int array, char *data );
#endif
#ifdef _PETSKILL_2TIMID
int PETSKILL_2BattleTimid( int charaindex, int toNo, int array, char *data );
#endif
#ifdef _PETSKILL_ANTINTER
int PETSKILL_AntInter(int charaindex, int toindex, int array, char* data);		// 寵物技能戰鬥模組
#endif

#ifdef _RESURRECTION_PETSKILL
int PETSKILL_Resurrection( int charaindex, int toNo, int array, char* data);
#endif
#ifdef _LOSTLOST_PETSKILL
int PETSKILL_Lostlost( int charaindex, int toNo, int array, char* data);
#endif


#ifdef _PETSKILL_PROPERTY
int PETSKILL_BattleProperty( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_TEAR
int PETSKILL_BattleTearDamage( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _BATTLE_LIGHTTAKE
int PETSKILL_Lighttakeed( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _BATTLE_ATTCRAZED
int PETSKILL_AttackCrazed( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _SHOOTCHESTNUT	// Syu ADD 寵技：丟栗子
int PETSKILL_AttackShoot( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _Skill_MPDAMAGE
int PETSKILL_MpDamage( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_SETDUCK
int PETSKILL_SetDuck( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _MAGICPET_SKILL
int PETSKILL_SetMagicPet( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _SKILL_TOOTH
int PETSKILL_ToothCrushe( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PSKILL_MODIFY
int PETSKILL_Modifyattack( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PSKILL_MDFYATTACK
int PETSKILL_Mdfyattack( int charaindex, int toNo, int array, char *data );
#endif


#ifdef _MAGIC_SUPERWALL
int	PETSKILL_MagicStatusChange( int charaindex, int toindex, int array, char *data );
#endif

#ifdef _PET_SKILL_SARS				// WON ADD 毒煞蔓延
int PETSKILL_Sars( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _SONIC_ATTACK				// WON ADD 音波攻擊
int PETSKILL_Sonic( int charaindex, int toNo, int array, char *data );
#endif
#ifdef _PETSKILL_REGRET
int PETSKILL_Regret( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_GYRATE
int PETSKILL_Gyrate( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_ACUPUNCTURE //針刺外皮
int PETSKILL_Acupuncture( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_RETRACE
int PETSKILL_Retrace( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_HECTOR
int PETSKILL_Hector( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_FIREKILL
int PETSKILL_Firekill( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_DAMAGETOHP   //暗月狂狼(嗜血技的變體)
int PETSKILL_DamageToHp2( int charaindex, int toNo, int array, char *data );
#endif

#ifdef _PETSKILL_BECOMEFOX
int PETSKILL_BecomeFox( int charaindex, int toNo, int array, char* data);
#endif

#ifdef _PETSKILL_BECOMEPIG
int PETSKILL_BecomePig( int charaindex, int toNo, int array, char* data);
#endif

#ifdef _PETSKILL_SHOWMERCY
int PETSKILL_ShowMercy(int charaindex, int toNo, int array, char* data);
#endif

#ifdef _PETSKILL_COMBINED
int PETSKILL_Combined(int charaindex, int toNo, int array, char* data);
#endif

#ifdef _PETSKILL_LER
int PETSKILL_BatFly(int charaindex, int toNo, int array, char* data);					// 雷爾技 - 群蝠四竄
int PETSKILL_DivideAttack(int charaindex, int toNo, int array, char* data);		// 雷爾技 - 分身地裂
#endif

#ifdef _PETSKILL_BATTLE_MODEL
int PETSKILL_BattleModel(int charaindex, int toindex, int array, char* data);		// 寵物技能戰鬥模組
#endif

#ifdef _STRENGTH_PETSKILL
int PETSKILL_Strength( int charaindex, int toNo, int array, char *data );
#endif
#ifdef _GRAPPLING_PETSKILL
int PETSKILL_Grappling( int charaindex, int toNo, int array, char* data);
#endif
#ifdef _PETSKILL_PASSIVE_PET_MATCH1		//寵物單人組閤被動技能
int PETSKILL_PASSIVE_PET_MATCH1( int charaindex, int toNo, int array, char *data );
#endif

#endif
