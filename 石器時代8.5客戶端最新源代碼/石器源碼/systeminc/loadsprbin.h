#ifndef _SPRITE_H_
#define _SPRITE_H_

//????????????????
#define mxSPRITE	40000

#define maxBUFFER	1024*1024*6



typedef unsigned char MOJI;
typedef unsigned char U1;
typedef          char S1;
typedef unsigned short U2;
typedef          short S2;
typedef unsigned long U4;
typedef          long S4;
typedef float  F4;
typedef double F8;

typedef enum {
	ANIM_ATTACK, //攻擊
	ANIM_DAMAGE, //受傷
	ANIM_DEAD,  //死亡
	ANIM_STAND, //站立
	ANIM_WALK, //行走
	ANIM_SIT, //坐下
	ANIM_HAND, //揮手
	ANIM_HAPPY, //高興
	ANIM_ANGRY, //生氣
	ANIM_SAD, //傷心
	ANIM_GUARD, //防守
	ANIM_NOD, //點頭
	ANIM_THROW, //投擲
	ANIM_LIST_
} ANIM_LIST;


// 1?????
typedef struct
{
	U4 BmpNo;				//Adrn圖片編號
	S2 PosX,PosY;			//圖片顯示時的x，y偏移
	U2 SoundNo;				// 小於10000代錶音效編號,錶示要放音效;大於等於10000小於10100代錶要顯示傷害效果,數字或其他效果
							// 大於等於10100代錶連擊?????
} FRAMELIST;//一幀動作的具體信息

typedef struct
{
	U2 dir;	// 動作方嚮(0-8)
	U2 no;	// 動作的分類見後麵的ANIM_LIST的定義
	U4 dtAnim;	// 次動作循環的耗時
	U4 frameCnt; // FRAMELIST的數量
	FRAMELIST *ptFramelist;	
} ANIMLIST;


// SPR??
typedef struct
{
	U4 sprNo;	// Spr序號
	U4 offset;	// 指明在spr.bin中的地址
	U2 animSize;	// 腳色有多少個完整的動作
} SPRADRN;


typedef struct
{
	U2 animSize;
	ANIMLIST	*ptAnimlist;
} SPRITEDATA;


typedef struct {
	U2			dtz;
	U2			noSpritedata;
	U2			mdAnim;
	U2			mdAnim2;
	U2			dir;
	U2			ctLoop;
	float		ctAnim;
	float		dtAnim;
} SPRITE;


typedef struct
{
	U2 dir;		// 動作方嚮(0-8)
	U2 no;		// 動作的分類見後麵的ANIM_LIST的定義
	U4 dtAnim;	// 一次動作循環的耗時
	U4 frameCnt;	// 動作楨的數量
} ANIM_HEADER;


extern SPRITEDATA SpriteData[mxSPRITE];


BOOL InitSprBinFileOpen( char *, char * );


#endif
