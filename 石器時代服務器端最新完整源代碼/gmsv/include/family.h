#ifndef __FAMILY_H__
#define __FAMILY_H__

#include "version.h"
#include "common.h"
#include "util.h"
#include "net.h"
#include "time.h"

#define FAMILY_MAXNUM			1000	// 傢族數量
#ifdef _FMVER21
#define FAMILY_MAXMEMBER		FAMILY_MAX_MEMBER	// 傢族人數
#define FAMILY_MAXCHANNELMEMBER		50	// 頻道人數
#else
#define FAMILY_MAXMEMBER		50	// 傢族人數
#define FAMILY_MAXCHANNELMEMBER		10	// 頻道人數
#endif
#define FAMILY_MAXCHANNEL 		5	// 傢族頻道

#define CHAR_MAXNAME			32
#define CHAR_MAXID			20
#define MINFMLEVLEFORPOINT      	3       // 3 申請莊園最低等級
#define FMLEADERLV			30	// 族長等級

#ifdef _FAMILY_MANORNUM_CHANGE
#define FAMILY_FMPKFLOOR		15	// 傢族ＰＫ圖層
#else
#define FAMILY_FMPKFLOOR		9	// 傢族ＰＫ圖層
#define FMPOINTNUM			4       // 有據點傢族的最大數量
#define MANORNUM                	4
#define FAMILY_MAXHOME			4	// 傢族據點
#endif

enum
{
    FM_TOP_INTEGRATE = 1,    // DPTOP 綜閤
    FM_TOP_ADV,              // DPTOP 冒險
    FM_TOP_FEED,             // DPTOP 飼育
    FM_TOP_SYNTHESIZE,       // DPTOP 閤成
    FM_TOP_DEALFOOD,         // DPTOP 料理
    FM_TOP_PK,               // DPTOP ＰＫ
#ifdef _NEW_MANOR_LAW
		FM_TOP_MOMENTUM = 8,		 // DPTOP 氣勢
#endif
    FM_TOP_NUM,              // DPTOP 數量
};

enum
{
	FM_FIX_ACCEPTFLAG = 1,
	FM_FIX_FMPK,
	FM_FIX_FMPET,
	FM_FIX_FMRULE,
	FM_FIX_DELFMTIME,
	FM_FIX_FMGOLD,
	FM_FIX_FMADV,
	FM_FIX_FMFEED,
	FM_FIX_FMSYNTHESIZE,
	FM_FIX_FMDEALFOOD,
	FM_FIX_FMLEADERCHANGE,
#ifdef _NEW_MANOR_LAW
	FM_FIX_FMMOMENTUM,
#endif
	FM_FIX_FAME = 13,
#ifdef _FAMILYBADGE_
	FM_FIX_BADGE,
#endif
};

/*
 * 扔□田    及職及樺赭午及 cdkey charname 及贏今毛寜六月凶戶卞
 * CHEKEYLEN, CHARNAMELEN
 * 毛銀丹方丹卞  凳［
 */
    
void CHAR_Family(int fd, int index, char* message);
void ACAddFM(int fd, int result, int fmindex, int index);
void ACJoinFM(int fd, int result, int recv);
void ACLeaveFM(int fd, int result, int resultflag);
void ACDelFM(int fd, int result);
void ACShowFMList(int ret, int fmnum, char *data);
void ACFMDetail(int ret, char *data, int charfdid);
void ACShowMemberList(int result, int index, int fmnumm,
int fmacceptflag, int fmjoinnum, char *data
#ifdef _FAMILYBADGE_
,int badge
#endif
);


void ACShowDpTop(int result,int num, char *data, int kindflag);
void ACShowPointList(int result, char *data);
void ACShowFMMemo(int result, int index, int num, int dataindex, char *data);

#ifdef _PERSONAL_FAME   // Arminius: 傢族個人聲望
void ACFMCharLogin(int fd, int ret, int index, int floor, int fmdp,
	int joinflag, int fmsetupflag, int flag, int charindex, int charfame
	#ifdef _NEW_MANOR_LAW
	,int momentum
	#endif
	);
#else
void ACFMCharLogin(int fd, int ret, int index, int floor, int fmdp,
	int joinflag, int fmsetupflag, int flag, int charindex);
#endif

void ACFMPointList(int ret, char *data);
void ACSetFMPoint(int ret, int r, int clifd);
void ACFMAnnounce(int ret, char *fmname, int fmindex, int index, int kindflag,
	char *data, int color);
void ACFixFMPK(int winindex, int loseindex, int data);
void ACFMJob( int fd, int ret, char* data1, char* data2 );

void FAMILY_Add(int fd, int meindex, char *message);
void FAMILY_Join(int fd, int meindex, char *message);
void FAMILY_Leave(int fd, int meindex, char *message);
void FAMILY_Detail(int fd, int meindex, char *message);
void FAMILY_CheckMember(int fd, int meindex, char *message);
void FAMILY_Channel(int fd, int meindex, char *message);
void FAMILY_Bank(int fd, int meindex, char *message);
void FAMILY_SetPoint(int fd, int meindex, char *message);
void FAMILY_Init(void);
void FAMILY_SetAcceptFlag(int fd, int meindex, char *message);
void FAMILY_FixRule( int fd, int meindex, char* message );
int FAMILY_RidePet( int fd, int meindex, char* message );
void FAMILY_LeaderFunc( int fd, int meindex, char* message );

void SetFMPetVarInit(int meindex);
void SetFMVarInit(int meindex);


int CheckFMLeader(int meindex);
int getFmLv(int playerindex);

void getNewFMList( void );
void checkFamilyIndex( void );

int CheckLeaderQ(int meindex);


// shan add Begin
struct FMMEMBER_LIST
{
//  int  fmindex;
    int  fmnum; 
    int  fmjoinnum;
//  BOOL use;                                       // 0->沒使用   1->使用
    int  memberindex[FAMILY_MAXMEMBER];             
    char numberlistarray[FAMILY_MAXMEMBER][64];
    char memo[35][220];                             // family dengon
    int  accept;                                    // 召募成員與否
    int  memonum;
    int  memoindex;
#ifdef _FAMILYBADGE_
	int badge;
#endif
};
// 傢族之間的留言闆
struct FMS_MEMO
{
    char memo[140][220];
    int  memonum;
    int  memoindex;
};
// 傢族強者錶
struct FMS_DPTOP
{
    int  num;															// 記錄有多少個傢族(綜閤)
    char topmemo[FAMILY_MAXNUM][128];
    int  fmtopid[FAMILY_MAXNUM];          // 傢族索引
#ifdef _FMVER21    
    int  fmtopdp[FAMILY_MAXNUM];          // 傢族綜閤聲望
#endif    
#ifdef _NEW_MANOR_LAW
		int	fmMomentum[FAMILY_MAXNUM];		// 傢族氣勢
		char	momentum_topmemo[FAMILY_MAXNUM][96];			// 傢族氣勢 top
		int	momentum_topid[FAMILY_MAXNUM];	// 傢族氣勢 top id 索引
#endif
    int  adv_num;                // 冒險
    char adv_topmemo[30][96];    
    int  feed_num;               // 伺育
    char feed_topmemo[30][96];        
    int  syn_num;                // 閤成
    char syn_topmemo[30][96];        
    int  food_num;               // 料理
    char food_topmemo[30][96];        
    int  pk_num;                 // ＰＫ
    char pk_topmemo[30][96];        
};
// 傢族據點
struct FM_POINTLIST
{
  char pointlistarray[FAMILY_MAXHOME][1024];	// Arminius: 32->1024
#ifdef _NEW_MANOR_LAW
	int fm_momentum[FAMILY_MAXHOME];	// 記錄挑戰時期開始時的守莊傢族氣勢值
	BOOL fm_inwar[FAMILY_MAXHOME];		// 此莊園是否進行莊園排程中
#endif
};
// 傢族PK圖層
struct FM_PKFLOOR
{
    int fl;
};
// End

#ifdef _NEW_MANOR_LAW
typedef struct _ManorSchedule_t{
	int iFmIndex[10];						// 排入挑戰排程的傢族索引
	int iFmMomentum[10];				// 傢族氣勢
	int iSort[10];							// 排名用
	char szMemo[10][256];				// 記錄: 傢族名稱|約戰時間|傢族氣勢
	char szFmName[10][32];			// 傢族名稱
	struct tm tm1[10];							// 記錄挑戰時間
}ManorSchedule_t;

extern ManorSchedule_t ManorSchedule[MANORNUM];
#endif

#define MAXFAMILYLIST 128*1024
extern char    familyListBuf[MAXFAMILYLIST];

void JoinMemberIndex( int charaindex, int fmindexi);

int	channelMember[FAMILY_MAXNUM][FAMILY_MAXCHANNEL][FAMILY_MAXMEMBER];
int	familyMemberIndex[FAMILY_MAXNUM][FAMILY_MAXMEMBER];

#ifdef _MO_LNS_CHARSUOXU
int Char_GetFm( int id, int x);
char * FM_getManorData(int ManorId,int Flg);
#endif
#endif
