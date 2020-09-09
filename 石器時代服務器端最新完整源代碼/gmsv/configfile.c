#define __CONFIGFILE_C__
#include "version.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "util.h"
//#include "configfile.h"
//ttom
#include "lssproto_util.h"
#include "configfile.h"
#include "net.h"
//ttom end
#include "npcutil.h"
// Arminius 7.12 login announce
#include "char.h"
#include "char_data.h"
// CoolFish: add 
#include "lssproto_serv.h"
#include "autil.h"

#ifdef _ANGEL_SUMMON
extern struct MissionInfo missionlist[MAXMISSION];
extern struct MissionTable missiontable[MAXMISSIONTABLE];
#endif

extern char* CHAR_setintdata[CHAR_DATAINTNUM];
extern char* CHAR_setchardata[CHAR_DATACHARNUM];

/* 澀爛毛忡  允月厭瞻   */
typedef struct tagConfig
{
    /*皿夫弘仿丞  (憤  讀卞菲戶凶中仃升引分蟯  */
  char    progname[8];
  char    configfilename[32]; /* config白央奶夥   */
    unsigned char debuglevel;   /* 犯田永弘伊矛夥 */
  unsigned int  usememoryunit;    /*丟乒伉及交瓦永玄扔奶術 */
  unsigned int  usememoryunitnum; /*丟乒伉及交瓦永玄醒 */
  char    asname[32];         /*失市它件玄扔□田及  蟆*/
  unsigned short  acservport; /*失市它件玄扔□田及禾□玄  */
  char    acpasswd[32];       /*失市它件玄扔□田尺及由旦伐□玉*/
  char    gsnamefromas[32];   /*
                                 * 失市它件玄扔□田井日葦尹月
                                 * 必□丞扔□田午仄化及  蟆
                                 */
                                 
    // Arminius 7.24 manor pk
  char gsid[32];	// game server chinese id
  unsigned short allowmanorpk;	// is this server allow manor pk
  unsigned short port;        /* 扔□田及謹切熬仃禾□玄 */
	int				servernumber;	/* 必□丞扔□田及  寞 */
	int				reuseaddr;	/* Address already used... 互鞅引日卅中凜及凶戶卞 */
  int             do_nodelay;     /* TCP_NODELAY 卞允月井升丹井 */
  int             log_write_time; /* 踏五仇心夫弘毛允月井升丹井［ */
  int             log_io_time;    /* I/O蟈  及凜棉反井月井升丹井［ */
  int             log_game_time;  /* 必□丞及質  蟈  及凜棉毛反井月 */
  int             log_netloop_faster; /* netloop_faster 及夫弘 */
	int				saacwritenum;	/* 失市它件玄扔□田尺及窒諦  卞write允月井 */
	int				saacreadnum;	/* 失市它件玄扔□田井日及dispatch 毛窒莢允月井 */
  unsigned short fdnum;           /*升木分仃戊生弁撲亦件毛忡  允月井 */
  unsigned short charnum;           /*升木分仃戊生弁撲亦件毛忡  允月井 */
  unsigned int   othercharnum;    /*  公及職及平乓仿及醒  */
  unsigned int objnum;            /* 左皮斥尼弁玄及    醒*/
  unsigned int   petcharnum;   	/* 矢永玄及醒    */
  unsigned int itemnum;           /* 失奶  丞及    醒*/
  unsigned int battlenum;         /* 田玄夥及    */
#ifdef _GET_BATTLE_EXP
  unsigned int battleexp;         /* 田玄夥及    */
#endif
    char    topdir[64];         	/* 玄永皿犯奴伊弁玄伉  */

    char    mapdir[64];         	/* 穴永皿犯奴伊弁玄伉  */
    char    maptilefile[64];    	/* 穴永皿澀爛白央奶夥  */
    char    battlemapfile[64];    	/* 田玄夥穴永皿澀爛白央奶夥  */
    char    itemfile[64];       	/* 失奶  丞澀爛白央奶夥  */
    char    invfile[64];        	/*   襯澀爛白央奶夥  */
    char    appearfile[64];     	/* 請蜇匏  澀爛白央奶夥  */
	char	titlenamefile[64];		/* 憊寞白央奶夥   */
	char	titleconfigfile[64];	/* 憊寞澀爛白央奶夥   */
	char	encountfile[64];		/* 巨件市它件玄澀爛白央奶夥   */
	char	enemybasefile[64];		/* 襯湘  澀爛白央奶夥   */
	char	enemyfile[64];			/* 襯澀爛白央奶夥   */
	char	groupfile[64];			/* 弘夥□皿澀爛白央奶夥   */
	char	magicfile[64];			/* 熱諸澀爛白央奶夥   */
#ifdef _ATTACK_MAGIC
	char  attmagicfile[64];       // 攻擊性咒術
#endif

	char	petskillfile[64];		/* 矢永玄  熱諸澀爛白央奶夥   */
    char    itematomfile[64];       /* 失奶  丞及箋    白央奶夥 */
    char    effectfile[64];     	/* 梢請澀爛白央奶夥  */
    char    quizfile[64];     		/* 弁奶術澀爛白央奶夥  */


    char    lsgenlog[64];       /*扔□田及lsgen 失它玄皿永玄白央奶夥  */

    char    storedir[64];       /*旦玄失犯奴伊弁玄伉    */
    char    npcdir[64];         /*NPC及澀爛白央奶夥毛  仁犯奴伊弁玄伉   */

    char    logdir[64];         /*
                                 * 夫弘犯奴伊弁玄伉
                                 */
    char    logconfname[64];    /*
                                 * 夫弘澀爛白央奶夥
                                 */
    char	chatmagicpasswd[64];	/* 民乓永玄  芊由旦伐□玉 */

#ifdef _STORECHAR
    char	storechar[64];
#endif
	unsigned int 	chatmagiccdkeycheck;	/* 民乓永玄  芊匹CDKEY毛民尼永弁允月井 */
  unsigned int    filesearchnum;     /*白央奶夥毛腹綢匹五月白央奶夥及醒*/
  unsigned int    npctemplatenum;     /*NPC及  件皿伊□玄白央奶夥及醒*/
  unsigned int    npccreatenum;       /*NPC及戲遣白央奶夥及醒*/
  unsigned int    walksendinterval;   /* 洶仁及毛霜月棉厥 */
  unsigned int    CAsendinterval_ms;     /* CA毛霜月棉厥 (ms)*/
  unsigned int    CDsendinterval_ms;     /* CD毛霜月棉厥 (ms)*/
  unsigned int    Onelooptime_ms;     	/* 1夥□皿卞井仃月凜棉 */
	unsigned int	Petdeletetime;		/* 矢永玄互壅  允月凜棉 */
	unsigned int	Itemdeletetime;		/* 失奶  丞互壅  允月凜棉 */
    /* 夫弘奶件  及平乓仿及本□皮毛允月棉厥 */
  unsigned int    CharSavesendinterval;
  unsigned int    addressbookoffmsgnum;  /*
                                          * 失玉伊旦皮永弁卞左白仿奶件
                                          * 丟永本□斥毛
                                          * 窒丟永本□斥酸六月井
                                          */
  unsigned int    protocolreadfrequency;  /*
                                           * 皿夫玄戊夥毛窒立伉
                                           * 卞  戈井
                                           */
  unsigned int    allowerrornum;          /*
                                           * 巨仿□毛窒蜊引匹袱允井
                                           */
  unsigned int    loghour;          		/*
                                           * 夫弘毛忡綉允月凜對  ＂凜
                                           */
  unsigned int    battledebugmsg;    		/*
                                           * 田玄夥  及犯田永弘丟永本□斥毛請允井［ㄟ卅日請今卅中
                                           */
  //ttom add this because the second had this                                         
  unsigned int    encodekey;              
  unsigned int    acwbsize;             
  unsigned int    acwritesize;
  unsigned int    ErrUserDownFlg;
  //ttom end
#ifdef _GMRELOAD
	char	gmsetfile[64];				/* GM帳號、權限設定檔 */
#endif

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
	char profession[32];
#endif
#ifdef _ITEM_QUITPARTY
    char itemquitparty[32];
#endif

#ifdef _DEL_DROP_GOLD	
	unsigned int	Golddeletetime;
#endif
#ifdef _NEW_PLAYER_CF
	int	newplayertrans;
	int	newplayerlv;
	int	newplayergivepet[5];
	int newplayergiveitem[15];
	int	newplayerpetlv;
	int newplayergivegold;
	int ridepetlevel;
#ifdef _VIP_SERVER
	int	newplayerpetvip;
#endif
#endif
#ifdef _USER_EXP_CF
	char	expfile[64];
#endif
#ifdef _UNLAW_WARP_FLOOR
	char	unlawwarpfloor[512];
#endif
#ifdef _NO_JOIN_FLOOR
	char	nojoinfloor[512];
#endif
#ifdef _WATCH_FLOOR
	int	watchfloor[6];
#endif
#ifdef _BATTLE_FLOOR
	int	battlefloor;
	char battlefloorcf[512];
#endif
#ifdef _UNREG_NEMA
	char	unregname[5][16];
#endif
#ifdef _TRANS_LEVEL_CF
	int chartrans;
	int pettrans;
	int yblevel;
	int maxlevel;
#endif
#ifdef _POINT
int point;
	int transpoint[8];
#endif
#ifdef _VIP_SERVER
	int vippoint;
#endif
#ifdef _PET_AND_ITEM_UP
	int petup;
	int itemup;
#endif
#ifdef _LOOP_ANNOUNCE
	char loopannouncepath[32];
	int loopannouncetime;
	char loopannounce[10][1024];
	int loopannouncemax;
#endif
#ifdef _SKILLUPPOINT_CF
	int skup;
#endif
#ifdef _RIDELEVEL
	int ridelevel;
	int ridetrans;
#endif
#ifdef _REVLEVEL
	int revlevel;
#endif
#ifdef _NEW_PLAYER_RIDE
	int npride;
#endif
#ifdef _FIX_CHARLOOPS
	int charloops;
#endif
#ifdef _PLAYER_ANNOUNCE
	int pannounce;
#endif
#ifdef _PLAYER_MOVE
	int pmove;
#endif
	int recvbuffer;
	int sendbuffer;
	int recvlowatbuffer;
	int runlevel;
#ifdef _SHOW_VIP_CF
	int showvip;
#endif
#ifdef _PLAYER_NUM
	int playernum;
#endif
#ifdef _BATTLE_GOLD
	int battlegold;
#endif
#ifdef _ANGEL_TIME
	int angelplayertime;
	int angelplayermun;
#endif
#ifdef _RIDEMODE_20
	int ridemode;
#endif
#ifdef _FM_POINT_PK
	int fmpointpk;
#endif
#ifdef _ENEMY_ACTION
	int	enemyact;
#endif
#ifdef _FUSIONBEIT_TRANS
	char	fusionbeittrans;
#endif
#ifdef _CHECK_PEPEAT
	int	CheckRepeat;
#endif
	int	cpuuse;
#ifdef _FM_JOINLIMIT
	int	joinfamilytime;
#endif
#ifdef _MAP_HEALERALLHEAL
	char	mapheal[256];
#endif
#ifdef _THE_WORLD_SEND
	int	thewordtrans;
	int	thewordlevel;
	int	thewordsend;
#endif
#ifdef _LOGIN_DISPLAY
	int	logindisplay;
#endif
#ifdef _VIP_POINT_PK
	char	vippointpk[256];
	int vippointpkcost;
#endif
#ifdef _SPECIAL_MAP
	char specialmap[256];
#endif
#ifdef _NEW_AUTO_PK
	int	autopk;
	int	autopktrans;
	int	autopklv;
#ifdef _FORMULATE_AUTO_PK
	int	autopkpoint;
	int	killpoint;
#endif
#endif
#ifdef _AUTO_DEL_PET
	char autodelpet[256];
#endif
#ifdef _AUTO_DEL_ITEM
	char autodelitem[256];
#endif
#ifdef _BT_PET
	int btpet;
#endif
#ifdef _BT_ITEM
	int btitem;
#endif
#ifdef _LUCK_STAR
	int luckstartime;
	int luckstarchances;
#endif
#ifdef _BATTLE_GETITEM_RATE
	char battlegetitemrate[256];
	int battlegetitemratemap;
#endif
#ifdef _BOUND_TIME_EXPANSION
	char unboundtimemap[64];
	int unboundtimelevel;
	int unboundtimetrans;
#endif

#ifdef _UNLAW_THIS_LOGOUT
	char unlawthislogout[256];
#endif

#ifdef _TRANS_POINT_UP
	char transpointup[256];
#endif
#ifdef _OPEN_STW_SEND
	int stwsendtype;
	int stwsendpoint;
#endif
#ifdef _POOL_ITEM_BUG
	int poolitembug;
	char poolitem[256];
#endif
#ifdef _NO_STW_ENEMY
	int nostwenemy;
	int nostwenemypoint;
#endif
#ifdef _NEW_STREET_VENDOR
	char streetvendorpoint[256];
#endif
#ifdef _ITEM_PET_LOCKED
	int itampetlocked;
#endif
#ifdef _TALK_SAVE
	int savefame;
#endif
#ifdef _TALK_CHECK
	int talkcheckmax;
	int talkcheckmin;
#endif
#ifdef _DISABLE_PROFESSION_SKILL
	char disableprofessionskill[256];
#endif
#ifdef _ALL_SERV_SEND
	int	allservtrans;
	int	allservlevel;
	int	allservsend;
#endif
#ifdef _PET_TRANS_ABILITY
	int	pettransability;
	int	pettransability1;
	int	pettransability2;
#endif
#ifdef _NEED_ITEM_ENEMY
	int delneeditem;
#endif
#ifdef _NOT_ESCAPE
	char notescape[256];
#endif
#ifdef _PLAYER_OVERLAP_PK
	char playeroverlappk[256];
#endif
#ifdef _FIMALY_PK_TIME
	int fimalypktime;
#endif
#ifdef _PETSKILL_SHOP_LUA
	char freepetskillshoppath[256];
#endif
#ifdef _CANCEL_ANGLE_TRANS
	int cancelanlgetrans;
#endif
#ifdef _VIP_BATTLE_EXP
	int vipbattleexp;
#endif
#ifdef _NO_HELP_MAP
	char nohelpmap[256];
#endif
#ifdef _BATTLE_TIME
	int battletime;
#endif
#ifdef _SAME_IP_ONLINE_NUM
	int sameiponlinenum;
#endif
#ifdef _STREET_VENDOR_TRANS
	int streetvendortrans;
#endif
#ifdef _CHECK_SEVER_IP
	char serverip[256];
#endif
#ifdef _DAMMAGE_CALC
	int dammagecalc;
#endif
#ifdef _PET_ENEMY_DEVELOP_UP
	int PetEnemyDevelopUp;
#endif
#ifdef _FIRST_LOCK_ITEM
	char FirstLockItem[256];
#endif
	int Connectnum;
#ifdef _PETSKILL_NEW_PASSIVE
int autogetskill;
int getskillpos;
char skillinfolv[5][100];
int skillfusion;
char fusionrange[50];
int skillcount;
#endif
#ifdef _SHARE_EXP
	int expshare;
#endif
#ifdef _DEFEND_BIGBAO
  int bigbao;
	int bigbao2;
#endif
#ifdef _MO_SHOW_DEBUG
  int isdebug;
#endif
#ifdef _CHAR_LOOP_TIME
	int charlooptime;
#endif
#ifdef _MO_RELOAD_NPC
	int reloadnpctime;
	int reloadnpctype;
#endif
#ifdef _JZ_NEWSCRIPT_LUA
	char luafile[256];
#endif
#ifdef _ITEM_LUA
char itemluafile[256];
#endif
#ifdef _MO_LNS_NLSUOXU
  int mapstart;
#endif
#ifdef _ROOKIE_ITEM
  unsigned int rookieitem[5];
#endif
#ifdef _NO_TRANS_ITEM
  unsigned int notransitem;
#endif

#ifdef _MAX_MERGE_LEVEL
  unsigned int maxmergelevel;
#endif

#ifdef _NO_ATTACK
	int atttime;
	int attsafetime;
	int attcnt;
	int latetime;
	int attdmetime;
	int attdmecnt;
#endif
	char noattip[5][18];
#ifdef _NO_FULLPLAYER_ATT
	int nofullplayer;
	int nofull2player;
	int nocdkeyplayer;
	int nocdkeymode;
	int nocdkeytype;
	int nofulltime;
	int fengtype;
	int nofullendplayer;
	int nofullendtime;
	int manrennum;
#endif
	int locktype;
#ifdef _NEW_FUNC_DECRYPT
	int allowerrornum2;
#endif
#ifdef _MO_LOGIN_NO_KICK
  	 int loginnokick;
#endif
#ifdef _MO_ILLEGAL_NAME
	char illegalname[256];
#endif
#ifdef _NO_USE_PACKET_MAP
	char nousepacketmap[256];
#endif
#ifdef _NO_USE_MAGIC_MAP
	char nousemagicmap[256];
#endif
#ifdef _SOME_PETMAIL
	int petmailflg;
	char somepetmail[256];
#endif
#ifdef _CTRL_TRANS_DEVELOP
	int ctrltrans;
#endif
#ifdef	_PETMAIL_TIME
	int petmailtime;
#endif

#ifdef _UP_BBPETPROB
	int upbbprob;
#endif
}Config;

Config config;

#ifdef _USER_EXP_CF
int NeedLevelUpTbls[200];
#endif

/*
 *  戊件白奴弘白央奶夥毛  戈凜卞銀丹厭瞻
 *  xxxx=yyyy 心凶中卅及毛  戈
 */

typedef struct tagReadConf
{
    char    name[32];       /*xxxx卞丐凶月襖*/

    /*戚及2勾反NULL毛  木月午窒手質  仄卅中*/
    char  *charvalue;      /*yyyy毛公及引引醫  允月凜及醫  燮*/
    size_t  charsize;       /*charvalue及扔奶術*/

    /*
     *     酷  午仄化=及  互 "ON"分勻凶日 intvalue 卞反1毛醫  允月
     * 公木動陸反 atoi 及瑛絆
     */
    void*    value;       /*yyyy毛  晶允月醫  允月凜及醫  燮*/
    CTYPE    valuetype;
}ReadConf;

ReadConf readconf[]=
{
    { "debuglevel"      , NULL ,0 , (void*)&config.debuglevel      ,CHAR},

    { "usememoryunit"   , NULL ,0 , (void*)&config.usememoryunit   ,INT},
    { "usememoryunitnum", NULL ,0 , (void*)&config.usememoryunitnum,INT},

    { "acserv",			config.asname,sizeof(config.asname) ,NULL , 0},
    { "acservport",		NULL ,0 , (void*)&config.acservport     ,SHORT},
    { "acpasswd",		config.acpasswd,sizeof( config.acpasswd),NULL,0},
    { "gameservname",	config.gsnamefromas,sizeof(config.gsnamefromas),
     NULL,0},

    // Arminius 7.24 manor pk
    { "gameservid", config.gsid, sizeof(config.gsid), NULL, 0}, 
    { "allowmanorpk", NULL, 0, (void*)&config.allowmanorpk, SHORT},

    { "port",			NULL ,0 , (void*)&config.port           ,SHORT},
    { "servernumber",	NULL ,0 , (void*)&config.servernumber           ,INT},

    { "reuseaddr",			NULL ,0 , (void*)&config.reuseaddr  ,		INT},
    { "nodelay",			NULL , 0 , (void*)&config.do_nodelay ,		INT},
    { "log_write_time", 	NULL, 0 , (void*)&config.log_write_time,	INT},
    { "log_io_time", 		NULL, 0 , (void*)&config.log_io_time, 		INT},
    { "log_game_time",		NULL, 0 , (void*)&config.log_game_time,		INT},
    { "log_netloop_faster", NULL,0,(void*)&config.log_netloop_faster,	INT},
    { "saacwritenum",		NULL,0,(void*)&config.saacwritenum, 		INT},
    { "saacreadnum",		NULL,0,(void*)&config.saacreadnum, 			INT},
    { "fdnum",				NULL ,0 , (void*)&config.fdnum,				SHORT},
    { "charnum",				NULL ,0 , (void*)&config.charnum,				SHORT},
    { "petnum",				NULL ,0 , (void*)&config.petcharnum,		INT},
    { "othercharnum",		NULL ,0 , (void*)&config.othercharnum,		INT},

    { "objnum",			NULL ,0 , (void*)&config.objnum,				INT},
    { "itemnum",		NULL ,0 , (void*)&config.itemnum,				INT},
    { "battlenum",		NULL ,0 , (void*)&config.battlenum,				INT},
#ifdef _GET_BATTLE_EXP
    { "battleexp",		NULL ,0 , (void*)&config.battleexp,				INT},
#endif
    { "topdir"          , config.topdir,sizeof(config.topdir),NULL,0},
    { "mapdir"          , config.mapdir,sizeof(config.mapdir),NULL,0},
    { "maptilefile"     , config.maptilefile,sizeof(config.maptilefile),NULL,0},
    { "battlemapfile"   , config.battlemapfile,sizeof(config.battlemapfile),NULL,0},

#ifdef _ITEMSET6_TXT
	{ "itemset6file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET5_TXT
	{ "itemset5file",	config.itemfile,	sizeof(config.invfile),	NULL,	0},
#else
#ifdef _ITEMSET4_TXT
	{ "itemset4file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#else
#ifdef _ITEMSET3_ITEM
	{ "itemset3file"  , config.itemfile,sizeof(config.invfile),NULL,0},
#endif
#endif
#endif
#endif
  { "invinciblefile"  , config.invfile,sizeof(config.invfile),NULL,0},
  { "appearpositionfile"  , config.appearfile,sizeof(config.appearfile),NULL,0},
	{ "titlenamefile", config.titlenamefile, sizeof( config.titlenamefile),NULL,0},
	{ "titleconfigfile", config.titleconfigfile, sizeof( config.titleconfigfile),NULL,0},
	{ "encountfile", config.encountfile, sizeof( config.encountfile),NULL,0},
	{ "enemyfile", config.enemyfile, sizeof( config.enemyfile),NULL,0},
	{ "enemybasefile", config.enemybasefile, sizeof( config.enemybasefile),NULL,0},
	{ "groupfile", config.groupfile, sizeof( config.groupfile),NULL,0},
	{ "magicfile", config.magicfile, sizeof( config.magicfile),NULL,0},
#ifdef _ATTACK_MAGIC
	{ "attmagicfile" , config.attmagicfile , sizeof( config.attmagicfile )  , NULL , 0 },
#endif

#ifdef _PETSKILL2_TXT
	{ "petskillfile2", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#else
	{ "petskillfile1", config.petskillfile, sizeof( config.petskillfile),NULL,0},
#endif

    { "itematomfile" , config.itematomfile, sizeof( config.itematomfile),NULL,0},
    { "effectfile"  , config.effectfile,sizeof(config.effectfile),NULL,0},
    { "quizfile"  , config.quizfile,sizeof(config.quizfile),NULL,0},

    { "lsgenlogfilename", config.lsgenlog,sizeof(config.lsgenlog),NULL,0},
#ifdef _GMRELOAD
	{ "gmsetfile", config.gmsetfile, sizeof( config.gmsetfile),NULL,0},
#endif

    { "storedir"        ,config.storedir,sizeof(config.storedir),NULL,0},
    { "npcdir"          ,config.npcdir,sizeof(config.npcdir),NULL,0},
    { "logdir"          ,config.logdir,sizeof(config.logdir),NULL,0},
    { "logconfname"     ,config.logconfname,sizeof(config.logconfname),NULL,0},
    { "chatmagicpasswd", config.chatmagicpasswd, sizeof( config.chatmagicpasswd),NULL,0},
#ifdef _STORECHAR
    { "storechar", config.storechar, sizeof( config.storechar),NULL,0},
#endif
    { "chatmagiccdkeycheck",  NULL,0, &config.chatmagiccdkeycheck,INT},
    { "filesearchnum",  NULL,0, &config.filesearchnum,INT},
    { "npctemplatenum",  NULL,0, &config.npctemplatenum,INT},
    { "npccreatenum",    NULL,0, &config.npccreatenum,INT},
    { "walkinterval" ,NULL,0,(void*)&config.walksendinterval,INT},
    { "CAinterval" ,NULL,0,(void*)&config.CAsendinterval_ms,INT},
    { "CDinterval" ,NULL,0,(void*)&config.CDsendinterval_ms,INT},
    { "CharSaveinterval" ,NULL,0,(void*)&config.CharSavesendinterval,INT},
    { "Onelooptime" ,NULL,0,(void*)&config.Onelooptime_ms,INT},
    { "Petdeletetime" ,NULL,0,(void*)&config.Petdeletetime,INT},
    { "Itemdeletetime" ,NULL,0,(void*)&config.Itemdeletetime,INT},
	 { "addressbookoffmesgnum" ,NULL,0,
      (void*)&config.addressbookoffmsgnum,INT},

    { "protocolreadfrequency" ,NULL,0,
      (void*)&config.protocolreadfrequency,INT},

    { "allowerrornum" ,NULL,0,(void*)&config.allowerrornum,INT},
    { "loghour" ,NULL,0,(void*)&config.loghour,INT},
    { "battledebugmsg" ,NULL,0,(void*)&config.battledebugmsg,INT},
    //ttom add because the second had
    { "encodekey" ,NULL,0,(void*)&config.encodekey,INT},
    { "acwritesize" ,NULL,0,(void*)&config.acwritesize,INT},
    { "acwbsize" ,NULL,0,(void*)&config.acwbsize,INT},
    { "erruser_down" ,NULL,0,(void*)&config.ErrUserDownFlg,INT},    

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
    { "profession",		config.profession, sizeof(config.profession) ,NULL , 0},
#endif

#ifdef _ITEM_QUITPARTY
    { "itemquitparty",	config.itemquitparty, sizeof(config.itemquitparty) ,NULL , 0},
#endif

#ifdef _DEL_DROP_GOLD
	{ "Golddeletetime" ,NULL,0,(void*)&config.Golddeletetime,	INT},
#endif

#ifdef _NEW_PLAYER_CF
	{ "TRANS" ,NULL,0,(void*)&config.newplayertrans,	INT},
	{ "LV" ,NULL,0,(void*)&config.newplayerlv,	INT},	
	{ "PET1" ,NULL,0,(void*)&config.newplayergivepet[1],	INT},
	{ "PET2" ,NULL,0,(void*)&config.newplayergivepet[2],	INT},	
	{ "PET3" ,NULL,0,(void*)&config.newplayergivepet[3],	INT},	
	{ "PET4" ,NULL,0,(void*)&config.newplayergivepet[4],	INT},	
	{ "ITEM1" ,NULL,0,(void*)&config.newplayergiveitem[0],	INT},
	{ "ITEM2" ,NULL,0,(void*)&config.newplayergiveitem[1],	INT},	
	{ "ITEM3" ,NULL,0,(void*)&config.newplayergiveitem[2],	INT},	
	{ "ITEM4" ,NULL,0,(void*)&config.newplayergiveitem[3],	INT},	
	{ "ITEM5" ,NULL,0,(void*)&config.newplayergiveitem[4],	INT},
	{ "ITEM6" ,NULL,0,(void*)&config.newplayergiveitem[5],	INT},	
	{ "ITEM7" ,NULL,0,(void*)&config.newplayergiveitem[6],	INT},	
	{ "ITEM8" ,NULL,0,(void*)&config.newplayergiveitem[7],	INT},	
	{ "ITEM9" ,NULL,0,(void*)&config.newplayergiveitem[8],	INT},
	{ "ITEM10" ,NULL,0,(void*)&config.newplayergiveitem[9],	INT},	
	{ "ITEM11" ,NULL,0,(void*)&config.newplayergiveitem[10],	INT},	
	{ "ITEM12" ,NULL,0,(void*)&config.newplayergiveitem[11],	INT},	
	{ "ITEM13" ,NULL,0,(void*)&config.newplayergiveitem[12],	INT},	
	{ "ITEM14" ,NULL,0,(void*)&config.newplayergiveitem[13],	INT},	
	{ "ITEM15" ,NULL,0,(void*)&config.newplayergiveitem[14],	INT},
	{ "PETLV" ,NULL,0,(void*)&config.newplayerpetlv,	INT},	
	{ "GOLD" ,NULL,0,(void*)&config.newplayergivegold,	INT},
	{ "RIDEPETLEVEL" ,NULL,0,(void*)&config.ridepetlevel,	INT},
#ifdef _VIP_SERVER
	{ "GIVEVIPPOINT" ,NULL,0,(void*)&config.newplayerpetvip,	INT},
#endif
#endif

#ifdef _USER_EXP_CF
	{ "USEREXP", config.expfile, sizeof( config.expfile),NULL,0},
#endif

#ifdef _UNLAW_WARP_FLOOR
	{ "UNLAWWARPFLOOR" ,config.unlawwarpfloor, sizeof( config.unlawwarpfloor),NULL,0},
#endif

#ifdef _NO_JOIN_FLOOR
	{ "NOJOINFLOOR" ,config.nojoinfloor, sizeof( config.nojoinfloor),NULL,0},
#endif

#ifdef _WATCH_FLOOR
	{ "WATCHFLOOR" ,NULL,0,(void*)&config.watchfloor[0],	INT},
	{ "WATCHFLOOR1" ,NULL,0,(void*)&config.watchfloor[1],	INT},
	{ "WATCHFLOOR2" ,NULL,0,(void*)&config.watchfloor[2],	INT},	
	{ "WATCHFLOOR3" ,NULL,0,(void*)&config.watchfloor[3],	INT},	
	{ "WATCHFLOOR4" ,NULL,0,(void*)&config.watchfloor[4],	INT},	
	{ "WATCHFLOOR5" ,NULL,0,(void*)&config.watchfloor[5],	INT},
#endif

#ifdef _BATTLE_FLOOR
	{ "BATTLEFLOOR" ,NULL,0,(void*)&config.battlefloor,	INT},
	{ "BATTLEFLOORCF" ,config.battlefloorcf, sizeof( config.battlefloorcf),NULL,0},
#endif

#ifdef _UNREG_NEMA
	{ "NAME1" ,config.unregname[0], sizeof( config.unregname[0]),NULL,0},
	{ "NAME2" ,config.unregname[1], sizeof( config.unregname[1]),NULL,0},
	{ "NAME3" ,config.unregname[2], sizeof( config.unregname[2]),NULL,0},
	{ "NAME4" ,config.unregname[3], sizeof( config.unregname[3]),NULL,0},
	{ "NAME5" ,config.unregname[4], sizeof( config.unregname[4]),NULL,0},
#endif
#ifdef _TRANS_LEVEL_CF
	{ "CHARTRANS" ,NULL,0,(void*)&config.chartrans,	INT},
	{ "PETTRANS" ,NULL,0,(void*)&config.pettrans,	INT},	
	{ "LEVEL" ,NULL,0,(void*)&config.yblevel,	INT},	
	{ "MAXLEVEL" ,NULL,0,(void*)&config.maxlevel,	INT},	
#endif
#ifdef _POINT
	{ "POINT" ,NULL,0,(void*)&config.point,	INT},
	{ "TRANS0" ,NULL,0,(void*)&config.transpoint[0],	INT},	
	{ "TRANS1" ,NULL,0,(void*)&config.transpoint[1],	INT},	
	{ "TRANS2" ,NULL,0,(void*)&config.transpoint[2],	INT},	
	{ "TRANS3" ,NULL,0,(void*)&config.transpoint[3],	INT},	
	{ "TRANS4" ,NULL,0,(void*)&config.transpoint[4],	INT},	
	{ "TRANS5" ,NULL,0,(void*)&config.transpoint[5],	INT},	
	{ "TRANS6" ,NULL,0,(void*)&config.transpoint[6],	INT},	
	{ "TRANS7" ,NULL,0,(void*)&config.transpoint[7],	INT},	
#endif

#ifdef _PET_AND_ITEM_UP
	{ "PETUP" ,NULL,0,(void*)&config.petup,	INT},
	{ "ITEMUP" ,NULL,0,(void*)&config.itemup,	INT},
#endif
#ifdef _LOOP_ANNOUNCE
	{ "ANNOUNCEPATH" ,config.loopannouncepath, sizeof( config.loopannouncepath),NULL,0},
	{ "ANNOUNCETIME" ,NULL,0,(void*)&config.loopannouncetime,	INT},
#endif
#ifdef _SKILLUPPOINT_CF
	{ "SKILLUPPOINT" ,NULL,0,(void*)&config.skup,	INT},	
#endif
#ifdef _RIDELEVEL
	{ "RIDELEVEL" ,NULL,0,(void*)&config.ridelevel,	INT},	
	{ "RIDETRANS" ,NULL,0,(void*)&config.ridetrans,	INT},	
#endif

#ifdef _REVLEVEL
	{ "REVLEVEL" ,NULL,0,(void*)&config.revlevel,	INT},	
#endif
#ifdef _NEW_PLAYER_RIDE
	{ "NPRIDE" ,NULL,0,(void*)&config.npride,	INT},	
#endif
#ifdef _FIX_CHARLOOPS
	{ "CHARLOOPS" ,NULL,0,(void*)&config.charloops,	INT},	
#endif
#ifdef _PLAYER_ANNOUNCE
	{ "PANNOUNCE" ,NULL,0,(void*)&config.pannounce,	INT},
#endif
#ifdef _PLAYER_MOVE
	{ "PMOVE" ,NULL,0,(void*)&config.pmove,	INT},
#endif

	{ "recvbuffer" ,NULL,0,(void*)&config.recvbuffer,	INT},
	{ "sendbuffer" ,NULL,0,(void*)&config.sendbuffer,	INT},
	{ "recvlowatbuffer" ,NULL,0,(void*)&config.recvlowatbuffer,	INT},
	{ "runlevel" ,NULL,0,(void*)&config.runlevel,	INT},
	
#ifdef _SHOW_VIP_CF
	{ "SHOWVIP" ,NULL,0,(void*)&config.showvip,	INT},
#endif

#ifdef _PLAYER_NUM
	{ "PLAYERNUM" ,NULL,0,(void*)&config.playernum,	INT},
#endif

#ifdef _BATTLE_GOLD
	{ "BATTLEGOLD" ,NULL,0,(void*)&config.battlegold,	INT},
#endif
#ifdef _ANGEL_TIME
	{ "ANGELPLAYERTIME" ,NULL,0,(void*)&config.angelplayertime,	INT},
	{ "ANGELPLAYERMUN" ,NULL,0,(void*)&config.angelplayermun,	INT},
#endif
#ifdef _RIDEMODE_20
	{ "RIDEMODE" ,NULL,0,(void*)&config.ridemode,	INT},
#endif
#ifdef _FM_POINT_PK
	{ "FMPOINTPK" ,NULL,0,(void*)&config.fmpointpk,	INT},
#endif
#ifdef _ENEMY_ACTION
	{ "ENEMYACTION" ,NULL,0,(void*)&config.enemyact,	INT},
#endif
#ifdef _FUSIONBEIT_TRANS
	{ "FUSIONBEIT" ,NULL,0,(void*)&config.fusionbeittrans,	INT},
#endif
#ifdef _CHECK_PEPEAT
	{ "CHECKPEPEAT" ,NULL,0,(void*)&config.CheckRepeat,	INT},
#endif
	{ "CPUUSE" ,NULL,0,(void*)&config.cpuuse,	INT},
#ifdef _FM_JOINLIMIT
	{ "JOINFAMILYTIME" ,NULL,0,(void*)&config.joinfamilytime,	INT},
#endif
#ifdef _MAP_HEALERALLHEAL
	{ "MAPHEAL" ,config.mapheal, sizeof( config.mapheal),NULL,0},
#endif

#ifdef _THE_WORLD_SEND
	{ "THEWORLDTRANS" ,NULL,0,(void*)&config.thewordtrans,	INT},
	{ "THEWORLDLEVEL" ,NULL,0,(void*)&config.thewordlevel,	INT},
	{ "THEWORLDSNED" ,NULL,0,(void*)&config.thewordsend,	INT},
#endif
#ifdef _LOGIN_DISPLAY
	{ "LOGINDISPLAY" ,NULL,0,(void*)&config.logindisplay,	INT},
#endif
#ifdef _VIP_POINT_PK
	{ "PKMAP" ,config.vippointpk, sizeof( config.vippointpk),NULL,0},
	{ "PKMAPCOST" ,NULL,0,(void*)&config.vippointpkcost,	INT},
#endif
#ifdef _SPECIAL_MAP
	{ "SPECIALMAP" ,config.specialmap, sizeof( config.specialmap),NULL,0},
#endif
#ifdef _NEW_AUTO_PK
	{ "AUTOPK" ,NULL,0,(void*)&config.autopk,	INT},
	{ "AUTOPKTRANS" ,NULL,0,(void*)&config.autopktrans,	INT},
	{ "AUTOPKLV" ,NULL,0,(void*)&config.autopklv,	INT},
#ifdef _FORMULATE_AUTO_PK
	{ "AUTOPKPOINT" ,NULL,0,(void*)&config.autopkpoint,	INT},
	{ "KILLPOINT" ,NULL,0,(void*)&config.killpoint,	INT},
#endif
#endif
#ifdef _AUTO_DEL_PET
	{ "AUTODELPET" ,config.autodelpet, sizeof( config.autodelpet),NULL,0},
#endif
#ifdef _AUTO_DEL_ITEM
	{ "AUTODELITEM" ,config.autodelitem, sizeof( config.autodelitem),NULL,0},
#endif
#ifdef _BT_PET
	{ "BTPET" ,NULL,0,(void*)&config.btpet,	INT},
#endif
#ifdef _BT_ITEM
	{ "BTITEM" ,NULL,0,(void*)&config.btitem,	INT},
#endif
#ifdef _LUCK_STAR
	{ "LUCKSTARTIME" ,NULL,0,(void*)&config.luckstartime,	INT},
	{ "LUCKSTARCHANCES" ,NULL,0,(void*)&config.luckstarchances,	INT},
#endif
#ifdef _BATTLE_GETITEM_RATE
	{ "BATTLEGETITEMRATE" ,config.battlegetitemrate, sizeof( config.battlegetitemrate),NULL,0},
	{ "BATTLEGETITEMRATEMAP" ,NULL,0,(void*)&config.battlegetitemratemap,	INT},
#endif
#ifdef _UNLAW_THIS_LOGOUT
	{ "UNLAWTHISLOGOUT" ,config.unlawthislogout, sizeof( config.unlawthislogout),NULL,0},
#endif
#ifdef _TRANS_POINT_UP
	{ "TRANSPOINTUP" ,config.transpointup, sizeof( config.transpointup),NULL,0},
#endif
#ifdef _OPEN_STW_SEND
	{ "STWSENDTYPE" ,NULL,0,(void*)&config.stwsendtype,	INT},
	{ "STWSENDPOINT" ,NULL,0,(void*)&config.stwsendpoint,	INT},
#endif
#ifdef _POOL_ITEM_BUG
	{ "POOLITEMBUG" ,NULL,0,(void*)&config.poolitembug,	INT},
	{ "POOLITEM" ,config.poolitem, sizeof( config.poolitem),NULL,0},
#endif
#ifdef _NO_STW_ENEMY
	{ "NOSTWENEMY" ,NULL,0,(void*)&config.nostwenemy,	INT},
	{ "NOSTWENEMYGOLD" ,NULL,0,(void*)&config.nostwenemypoint,	INT},
#endif
#ifdef _NEW_STREET_VENDOR
	{ "STREETVENDORPOINT" ,config.streetvendorpoint, sizeof( config.streetvendorpoint),NULL,0},
#endif
#ifdef _ITEM_PET_LOCKED
	{ "ITEMPETLOCKED" ,NULL,0,(void*)&config.itampetlocked,	INT},
#endif
#ifdef _TALK_SAVE
	{ "SAVEFAME" ,NULL,0,(void*)&config.savefame,	INT},
#endif
#ifdef _TALK_CHECK
	{ "TALKCHECKMAX" ,NULL,0,(void*)&config.talkcheckmax,	INT},
	{ "TALKCHECKMIN" ,NULL,0,(void*)&config.talkcheckmin,	INT},
#endif
#ifdef _DISABLE_PROFESSION_SKILL
	{ "DISABLEPROFESSION" ,config.disableprofessionskill, sizeof( config.disableprofessionskill),NULL,0},
#endif
#ifdef _ALL_SERV_SEND
	{ "ALLSERVTRANS" ,NULL,0,(void*)&config.allservtrans,	INT},
	{ "ALLSERVLEVEL" ,NULL,0,(void*)&config.allservlevel,	INT},
	{ "ALLSERVSNED" ,NULL,0,(void*)&config.allservsend,	INT},
#endif
#ifdef _PET_TRANS_ABILITY
	{ "PETTRANSABILITY" ,NULL,0,(void*)&config.pettransability,	INT},
	{ "PETTRANSABILITY1" ,NULL,0,(void*)&config.pettransability1,	INT},
	{ "PETTRANSABILITY2" ,NULL,0,(void*)&config.pettransability2,	INT},
#endif
#ifdef _NEED_ITEM_ENEMY
	{ "DELNEEDITEM" ,NULL,0,(void*)&config.delneeditem,	INT},
#endif
#ifdef _NOT_ESCAPE
	{ "NOTESCAPE" ,config.notescape, sizeof( config.notescape),NULL,0},
#endif
#ifdef _PLAYER_OVERLAP_PK
	{ "PLAYEROVERLAPPK" ,config.playeroverlappk, sizeof( config.playeroverlappk),NULL,0},
#endif
#ifdef _FIMALY_PK_TIME
	{ "FIMALYPKTIME" ,NULL,0,(void*)&config.fimalypktime,	INT},
#endif
#ifdef _PETSKILL_SHOP_LUA
	{ "PETSKILLSHOPPATH" ,config.freepetskillshoppath, sizeof( config.freepetskillshoppath),NULL,0},
#endif
#ifdef _CANCEL_ANGLE_TRANS
	{ "CANCELANGLETRANS" ,NULL,0,(void*)&config.cancelanlgetrans,	INT},
#endif
#ifdef _VIP_BATTLE_EXP
	{ "vipbattleexp" ,NULL,0,(void*)&config.vipbattleexp,	INT},
#endif
#ifdef _NO_HELP_MAP
	{ "nohelpmap" ,config.nohelpmap, sizeof( config.nohelpmap),NULL,0},
#endif
#ifdef _BATTLE_TIME
	{ "battletime" ,NULL,0,(void*)&config.battletime,	INT},
#endif
#ifdef _SAME_IP_ONLINE_NUM
	{ "sameiponlinenum" ,NULL,0,(void*)&config.sameiponlinenum,	INT},
#endif
#ifdef _STREET_VENDOR_TRANS
	{ "streetvendortrans" ,NULL,0,(void*)&config.streetvendortrans,	INT},
#endif
#ifdef _CHECK_SEVER_IP
	{ "serverip" ,config.serverip, sizeof( config.serverip),NULL,0},
#endif
#ifdef _DAMMAGE_CALC
	{ "dammagecalc" ,NULL,0,(void*)&config.dammagecalc,	INT},
#endif
#ifdef _PET_ENEMY_DEVELOP_UP
	{ "PetEnemyDevelopUp" ,NULL,0,(void*)&config.PetEnemyDevelopUp,	INT},
#endif
#ifdef _FIRST_LOCK_ITEM
	{ "FirstLockItem" ,config.FirstLockItem, sizeof( config.FirstLockItem),NULL,0},
#endif
	{ "Connectnum" ,NULL,0,(void*)&config.Connectnum,	INT},
#ifdef _PETSKILL_NEW_PASSIVE
		{ "AUTUGETSKILL",		NULL ,0 , (void*)&config.autogetskill,				INT},
		{ "GETSKILLPOS",		NULL ,0 , (void*)&config.getskillpos,				INT},
		{ "SKILLINFOLV1", config.skillinfolv[0], sizeof( config.skillinfolv[0]),NULL,0},
		{ "SKILLINFOLV2", config.skillinfolv[1], sizeof( config.skillinfolv[1]),NULL,0},
		{ "SKILLINFOLV3", config.skillinfolv[2], sizeof( config.skillinfolv[2]),NULL,0},
		{ "SKILLINFOLV4", config.skillinfolv[3], sizeof( config.skillinfolv[3]),NULL,0},
		{ "SKILLINFOLV5", config.skillinfolv[4], sizeof( config.skillinfolv[4]),NULL,0},
		{ "FUSIONRANGE", config.fusionrange, sizeof( config.fusionrange),NULL,0},
		{ "SKILLFUSION",		NULL ,0 , (void*)&config.skillfusion,				INT},
		{ "SKILLCOUNT",		NULL ,0 , (void*)&config.skillcount,				INT},
#endif
#ifdef _SHARE_EXP
		{ "EXPSHARE"      , NULL ,0 , (void*)&config.expshare      ,INT},
#endif
#ifdef _DEFEND_BIGBAO
		{ "BIGBAO" ,NULL,0,(void*)&config.bigbao,	INT},
		{ "BIGBAO2" ,NULL,0,(void*)&config.bigbao2,	INT},
#endif
#ifdef _MO_SHOW_DEBUG
    { "ISDEBUG",		NULL ,0 , (void*)&config.isdebug,				INT},
#endif
#ifdef _CHAR_LOOP_TIME
	{ "charlooptime" ,NULL,0,(void*)&config.charlooptime,	INT},
#endif
#ifdef _MO_RELOAD_NPC
	{ "RELOADNPCTIME" ,NULL,0,(void*)&config.reloadnpctime,	INT},
	{ "RELOADNPCTYPE" ,NULL,0,(void*)&config.reloadnpctype,	INT},
#endif
#ifdef _JZ_NEWSCRIPT_LUA
	{ "LUAFILE"  , config.luafile,sizeof(config.luafile),NULL,0},
#endif
#ifdef _ITEM_LUA
	{ "ITEMLUAFILE"  , config.itemluafile,sizeof(config.itemluafile),NULL,0},
#endif
#ifdef _ROOKIE_ITEM
    { "ROOKIEITEM",		NULL ,0 , (void*)&config.rookieitem[0],				INT},
    { "ROOKIEITEM2",		NULL ,0 , (void*)&config.rookieitem[1],				INT},
    { "ROOKIEITEM3",		NULL ,0 , (void*)&config.rookieitem[2],				INT},
    { "ROOKIEITEM4",		NULL ,0 , (void*)&config.rookieitem[3],				INT},
    { "ROOKIEITEM5",		NULL ,0 , (void*)&config.rookieitem[4],				INT},
#endif
#ifdef _NO_TRANS_ITEM
    { "NOTRANSITEM",		NULL ,0 , (void*)&config.notransitem,				INT},
#endif
#ifdef _MAX_MERGE_LEVEL
    { "MAXMERGELEVEL",		NULL ,0 , (void*)&config.maxmergelevel,				INT},
#endif
#ifdef _NO_ATTACK
	{ "ATTTIME" ,NULL,0,(void*)&config.atttime,	INT},
	{ "ATTSAFETIME" ,NULL,0,(void*)&config.attsafetime,	INT},
	{ "ATTCNT" ,NULL,0,(void*)&config.attcnt,	INT},
	{ "LATETIME" ,NULL,0,(void*)&config.latetime,	INT},
	{ "ATTDMETIME" ,NULL,0,(void*)&config.attdmetime,	INT},
	{ "ATTDMECNT" ,NULL,0,(void*)&config.attdmecnt,	INT},
#endif
	{ "NOATTIP1" ,config.noattip[0], sizeof( config.noattip[0]),NULL,0},
	{ "NOATTIP2" ,config.noattip[1], sizeof( config.noattip[1]),NULL,0},
	{ "NOATTIP3" ,config.noattip[2], sizeof( config.noattip[2]),NULL,0},
	{ "NOATTIP4" ,config.noattip[3], sizeof( config.noattip[3]),NULL,0},
	{ "NOATTIP5" ,config.noattip[4], sizeof( config.noattip[4]),NULL,0},
#ifdef _NO_FULLPLAYER_ATT
	{ "NOFULLPLAYER" ,NULL,0,(void*)&config.nofullplayer,	INT},
	{ "NOFULL2PLAYER" ,NULL,0,(void*)&config.nofull2player,	INT},
	{ "NOCDKEYPLAYER" ,NULL,0,(void*)&config.nocdkeyplayer,	INT},
	{ "NOCDKEYMODE" ,NULL,0,(void*)&config.nocdkeymode,	INT},
	{ "NOCDKEYTYPE" ,NULL,0,(void*)&config.nocdkeytype,	INT},
	{ "NOFULLTIME" ,NULL,0,(void*)&config.nofulltime,	INT},
	{ "FENGTYPE" ,NULL,0,(void*)&config.fengtype,	INT},
	{ "NOFULLENDPLAYER" ,NULL,0,(void*)&config.nofullendplayer,	INT},
	{ "NOFULLENDTIME" ,NULL,0,(void*)&config.nofullendtime,	INT},
	{ "MANRENNUM" ,NULL,0,(void*)&config.manrennum,	INT},
#endif
	{ "LOCKTYPE" ,NULL,0,(void*)&config.locktype,	INT},
#ifdef _NEW_FUNC_DECRYPT
	{ "ALLOWERRORNUM2" ,NULL,0,(void*)&config.allowerrornum2,	INT},
#endif
#ifdef _MO_LOGIN_NO_KICK
    { "LOGINNOKICK",		NULL ,0 , (void*)&config.loginnokick,				INT},
#endif
#ifdef _MO_ILLEGAL_NAME
		{ "ILLEGALNAME" ,config.illegalname, sizeof( config.illegalname),NULL,0},
#endif
#ifdef _NO_USE_PACKET_MAP
		{ "NOPACKETMAP" ,config.nousepacketmap, sizeof( config.nousepacketmap),NULL,0},
#endif
#ifdef _NO_USE_MAGIC_MAP
		{ "NOMAGICMAP" ,config.nousemagicmap, sizeof( config.nousemagicmap),NULL,0},
#endif
#ifdef _SOME_PETMAIL
    { "PETMAILFLG",		NULL ,0 , (void*)&config.petmailflg,				INT},
    { "SOMEPETMAIL" ,config.somepetmail, sizeof( config.somepetmail),NULL,0},
#endif
#ifdef _CTRL_TRANS_DEVELOP
    { "CTRLTRANS",		NULL ,0 , (void*)&config.ctrltrans,				INT},
#endif
#ifdef	_PETMAIL_TIME
			{ "PETMAILTIME" ,NULL,0,(void*)&config.petmailtime,	INT},
#endif
#ifdef _UP_BBPETPROB
			{ "UPBBPROB" ,NULL,0,(void*)&config.upbbprob,	INT},
#endif

};

// Arminius 7.12 login announce
char announcetext[8192];
void AnnounceToPlayer(int charaindex)
{
  char *ptr,*qtr;
  
  ptr=announcetext;
  while ((qtr=strstr(ptr,"\n"))!=NULL) {
    qtr[0]='\0';
//    printf("ptr=%s\n",ptr);
    CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
    qtr[0]='\n';
    ptr=qtr+1;
  }
  CHAR_talkToCli(charaindex, -1, ptr, CHAR_COLORYELLOW);
  
}

// Robin 0720
void AnnounceToPlayerWN(int fd)
{
	char buf[8192];
#ifdef _VIP_LOGOUT
	char token[8192];
	int charaindex = CONNECT_getCharaindex( fd );
	long lastleavetime = CHAR_getInt( charaindex , CHAR_LASTLEAVETIME);
	struct tm *p;
	p=localtime(&lastleavetime);
			
	sprintf( token , "您最後離綫時間 %d年%d月%d日 %d:%d:%d\n\n%s",p->tm_year + 1900,
																																		p->tm_mon + 1,
																																		p->tm_mday,
																																		p->tm_hour,
																																		p->tm_min,
																																		p->tm_sec,
																																		announcetext);
	lssproto_WN_send( fd , WINDOW_MESSAGETYPE_LOGINMESSAGE,
			WINDOW_BUTTONTYPE_OK,
			-1,-1,
			makeEscapeString( token, buf, sizeof(buf)));
#else	
	lssproto_WN_send( fd , WINDOW_MESSAGETYPE_LOGINMESSAGE,
		WINDOW_BUTTONTYPE_OK,
		-1,-1,
		makeEscapeString( announcetext, buf, sizeof(buf)));
#endif
}


void LoadAnnounce(void)
{
    FILE *f;

    memset(announcetext, 0, sizeof(announcetext));
    if ((f=fopen("./announce.txt","r"))!=NULL) {
      fread(announcetext, sizeof(announcetext), 1, f);
      announcetext[sizeof(announcetext)-1]='\0';
      fclose(f);
    }
}
#ifdef _PET_TALKPRO
PTALK pettalktext[PETTALK_MAXID];

void LoadPetTalk(void)
{
	FILE *fp;
	char fn[256];
	char line[ 4096];
	char talkmem[4096];
	int maxid=0;
	char buf1[256], buf2[256], buf3[256];
	int talkNO=-1, mark=-1, i;
	int len = sizeof( talkmem);
	
	memset(talkmem, 0, sizeof(talkmem));
	sprintf(fn, "%s/pettalk/pettalk.menu", getNpcdir());

	for( i=0;i<PETTALK_MAXID;i++)	{
		pettalktext[i].ID = -1;
		strcpy( pettalktext[i].DATA, "\0");
	}

	print("\n裝載寵物對話文件:%s...", fn);
	
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", fn);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen( fn, "r");
}
    if( fp != NULL ) {
		while( fgets( line, sizeof( line), fp)) {
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(line);
			}
#endif
			if( strlen( talkmem) != 0 ) {
				if( talkmem[strlen( talkmem) -1] != '|' ) {
					strcatsafe( talkmem, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( talkmem,len,  line);
		}
		fclose( fp);
    }else	{
		print("錯誤:找不到文件!");
	}

	talkNO=1;
	while( getStringFromIndexWithDelim( talkmem,"END",talkNO, buf1, sizeof( buf1)) != FALSE	){
		talkNO++;
		if( NPC_Util_GetStrFromStrWithDelim( buf1, "PETTEMPNO", buf2, sizeof( buf2)) == NULL  )
			continue;
		mark=1;
		strcpy( fn,"\0");

		if( getStringFromIndexWithDelim( buf2,",", mark+1,buf3,sizeof( buf3)) != FALSE )	{
			pettalktext[maxid].ID = atoi( buf3);
			if( getStringFromIndexWithDelim( buf2,",", mark,buf3,sizeof( buf3)) != FALSE )	{
				sprintf(fn, "%s/pettalk/%s", getNpcdir(), buf3);
				//print("\n ...file:%s", fn);
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", fn);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
				fp = fopen( fn, "r");
}
				if( fp != NULL )	{
					char line[4096];
					while( fgets( line, sizeof( line), fp ) ) {
#ifdef _CRYPTO_DATA		
						if(crypto==TRUE){
							DecryptKey(line);
						}
#endif
						if( strlen( pettalktext[maxid].DATA) != 0 ) {
							if( pettalktext[maxid].DATA[strlen( pettalktext[maxid].DATA) -1] != '|' ) {
								strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), "|");
							}
						}
						chompex( line);
						strcatsafe( pettalktext[maxid].DATA, sizeof( pettalktext[maxid].DATA), line);
					}
					maxid++;
					fclose( fp);
				}else	{
					print("錯誤:[%s] 找不到!", fn);
					pettalktext[maxid].ID=-1;
				}
			}else	{
				pettalktext[maxid].ID=-1;
			}
		}
		print(".");
		if( maxid >= PETTALK_MAXID )
			break;
	}
	print("最大ID=%d...", maxid);
	{
		int haveid=0;
		for( i=0;i<PETTALK_MAXID;i++)	{
			if( pettalktext[i].ID >= 0 )	{
				haveid++;
			}
		}
		print("載入總數=%d", haveid);
	}

}

#else
char pettalktext[4096];
void LoadPetTalk(void)
{
  FILE *fp;
  char fn[256];
  char	line[ 4096];
  int len = sizeof( pettalktext);
  
  memset(pettalktext, 0, sizeof(pettalktext));
  sprintf(fn, "%s/pettalk/pettalk.mem", getNpcdir());
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", fn);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
  fp = fopen( fn, "r");
}
    if( fp != NULL ) {
		print("\n\n 讀取 pettalk.mem");
		while( fgets( line, sizeof( line), fp)) {
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(line);
			}
#endif
			if( strlen( pettalktext) != 0 ) {
				if( pettalktext[strlen( pettalktext) -1] != '|' ) {
					strcatsafe( pettalktext, len, "|");		
				}
			}
			chompex( line);
			strcatsafe( pettalktext,len,  line);
		}
		fclose( fp);
		print("\n %s", pettalktext);
    }else	{
		print("\n 不能找到 pettalk.mem");
	}
}
#endif

#ifdef _GAMBLE_BANK
GAMBLEBANK_ITEMS GB_ITEMS[GAMBLEBANK_ITEMSMAX];

void Load_GambleBankItems( void)
{

	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	int num,ID,type;
	int i=0;
	sprintf(filename, "./data/gambleitems.txt" );
	print("\n加載賭博物品文件 %s ...", filename);
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", filename);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen( filename, "r");
}
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(buf1);
			}
#endif
			if( strstr( buf1, "#") != 0 ) continue;
			sscanf( buf1,"%s %d %d %d", name, &ID, &num , &type);
			strcpy( GB_ITEMS[i].name, name);
			GB_ITEMS[i].Gnum = num;
			GB_ITEMS[i].ItemId = ID;
			GB_ITEMS[i].type = type;
			i++;
		}
		print("最大ID: %d ", i);
		fclose( fp);
    }else	{
		print("錯誤 找不到文件 %s", filename);
	}

}
#endif


#ifdef _CFREE_petskill
PETSKILL_CODES Code_skill[PETSKILL_CODE];
void Load_PetSkillCodes( void)
{
	FILE *fp;
	char filename[256];
	char buf1[256];
	char name[128];
	char type[256];
	int num,ID;
	int i=0;
	sprintf(filename, "./data/skillcode.txt" );
	print("\n加載寵物技能編碼文件:%s...", filename);
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", filename);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen( filename, "r");
}
    if( fp != NULL ) {
		while( fgets( buf1, sizeof( buf1), fp) != NULL )	{
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(buf1);
			}
#endif
			sscanf( buf1,"%s %d %d %s", name, &num, &ID, type);
			strcpy( Code_skill[i].name, name);
			Code_skill[i].TempNo = num;
			Code_skill[i].PetId = ID;
			strcpy( Code_skill[i].Code, type);
			//print("\n %s|%d|%d|%s|", Code_skill[i].name, Code_skill[i].TempNo, 
			//	Code_skill[i].PetId, Code_skill[i].Code);
			i++;
			if( i >= PETSKILL_CODE ) break;
		}
		fclose( fp);
    }else	{
		print("打不到文件 %s", filename);
	}
	print("完成\n");
}
#endif

#ifdef _GMRELOAD
BOOL LoadGMSet( char* filename )
{
	FILE* fp;
	int i = 0, gm_num = 0;
	
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", filename);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
  	fp = fopen(filename,"r");
}
	if (fp == NULL)
	{
		print("無法打開文件\n");
		return FALSE;
	}
	for (i = 0; i < GMMAXNUM; i++)
	{
		strcpy(gminfo[i].cdkey, "");
		gminfo[i].level = 0;
	}
	while(1){
		char	line[64], cdkey[64], level[64];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(line);
		}
#endif
		chop(line);
		//change 使gmset.txt可以增加注解*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		gm_num = gm_num + 1;
		if (gm_num > GMMAXNUM)	break;
		easyGetTokenFromString(line, 1, cdkey, sizeof(cdkey));
		if (strcmp(cdkey, "") == 0)	break;
		strncpy(gminfo[gm_num].cdkey, cdkey, sizeof(gminfo[gm_num].cdkey));
		easyGetTokenFromString(line, 2, level, sizeof(level));
		if (strcmp(level, "") == 0)	break;
		gminfo[gm_num].level = atoi(level);
//		print("\ncdkey:%s, level:%d", gminfo[gm_num].cdkey, gminfo[gm_num].level);
	}
	fclose(fp);
	return TRUE;
}
#endif

/*------------------------------------------------------------
 * 皿夫弘仿丞  毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  cahr*
 ------------------------------------------------------------*/
char* getProgname( void )
{
    return config.progname;
}
/*------------------------------------------------------------
 * configfilename 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getConfigfilename( void )
{
    return config.configfilename;
}
/*------------------------------------------------------------
 * configfilename 毛澀爛允月［
 * 婁醒
 *  newv    char*   蕙仄中襖
 * 忒曰襖
 *  卅仄
 ------------------------------------------------------------*/
void setConfigfilename( char* newv )
{
    strcpysafe( config.configfilename, sizeof( config.configfilename ),
                newv );
}

/*------------------------------------------------------------
 * 犯田永弘伊矛夥毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getDebuglevel( void )
{
    return config.debuglevel;
}
/*------------------------------------------------------------
 * 犯田永弘伊矛夥毛澀爛允月
 * 婁醒
 *  newv    int     蕙仄中襖
 * 忒曰襖
 *  unsigned int    檣及襖
 ------------------------------------------------------------*/
unsigned int setDebuglevel( unsigned int newv )
{
    int old;
    old = config.debuglevel;
    config.debuglevel = newv;
    return old;
}
/*------------------------------------------------------------
 * memoryunit 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getMemoryunit( void )
{
    return config.usememoryunit;
}
/*------------------------------------------------------------
 * memoryunitnum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getMemoryunitnum( void )
{
    return config.usememoryunitnum;
}

/*------------------------------------------------------------
 * 失市它件玄扔□田及失玉伊旦毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char*   getAccountservername( void )
{
    return config.asname;
}
/*------------------------------------------------------------
 * 失市它件玄扔□田及禾□玄毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned short
 ------------------------------------------------------------*/
unsigned short   getAccountserverport( void )
{
    return config.acservport;
}
/*------------------------------------------------------------
 * 失市它件玄扔□田尺及由旦伐□玉毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned short
 ------------------------------------------------------------*/
char*   getAccountserverpasswd( void )
{
  return config.acpasswd;
}
/*------------------------------------------------------------
 * 失市它件玄扔□田井日葦尹月必□丞扔□田午仄化及  蟆毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned short
 ------------------------------------------------------------*/
char*   getGameservername( void )
{
    return config.gsnamefromas;
}

// Arminius 7.24 manor pk
char* getGameserverID( void )
{
    if (config.gsid[strlen(config.gsid)-1]=='\n')
      config.gsid[strlen(config.gsid)-1]='\0';
      
    return config.gsid;
}

unsigned short getAllowManorPK( void )
{
    return config.allowmanorpk;
}

unsigned short getPortnumber( void )
{
    return config.port;
}
/*------------------------------------------------------------
 * 必□丞扔□田及  寞   寞毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned short
 ------------------------------------------------------------*/
int getServernumber( void )
{
    return config.servernumber;
}
/*------------------------------------------------------------
 * reuseaddr 及襖毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned short
 ------------------------------------------------------------*/
int getReuseaddr( void )
{
    return config.reuseaddr;
}

int getNodelay( void )
{
    return config.do_nodelay;
}
int getLogWriteTime(void)
{
    return config.log_write_time;
}
int getLogIOTime( void)
{
    return config.log_io_time;
}
int getLogGameTime(void)
{
    return config.log_game_time;
}
int getLogNetloopFaster(void)
{
    return config.log_netloop_faster;
}

/*------------------------------------------------------------
 * saacwritenum 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *   int
 ------------------------------------------------------------*/
int getSaacwritenum( void )
{
    return config.saacwritenum;
}
/*------------------------------------------------------------
 * saacwritenum 毛澀爛允月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *   int
 ------------------------------------------------------------*/
void setSaacwritenum( int num )
{
    config.saacwritenum = num;
}
/*------------------------------------------------------------
 * saacreadnum 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *   int
 ------------------------------------------------------------*/
int getSaacreadnum( void )
{
    return config.saacreadnum;
}
/*------------------------------------------------------------
 * saacreadnum 毛澀爛允月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *   int
 ------------------------------------------------------------*/
void setSaacreadnum( int num )
{
    config.saacreadnum = num;
}
/*------------------------------------------------------------
 * fdnum 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/

unsigned int getFdnum( void )
{
	return config.fdnum;
}

unsigned int getPlayercharnum( void )
{
    return config.charnum;
}

/*------------------------------------------------------------
 * petcharanum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getPetcharnum( void )
{
    return config.petcharnum;
}


/*------------------------------------------------------------
 * othercharnum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getOtherscharnum( void )
{
    return config.othercharnum;
}

/*------------------------------------------------------------
 * objnum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getObjnum( void )
{
    return config.objnum;
}

/*------------------------------------------------------------
 * itemnum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getItemnum( void )
{
    return config.itemnum;
}


/*------------------------------------------------------------
 * battlenum 毛  月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getBattlenum( void )
{
    return config.battlenum;
}

#ifdef _GET_BATTLE_EXP
unsigned int getBattleexp( void )
{
    return config.battleexp;
}
void setBattleexp( int exp )
{
    config.battleexp = exp;
    return;
}
#endif
/*------------------------------------------------------------
 * topdir 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getTopdir( void )
{
    return config.topdir;
}
/*------------------------------------------------------------
 * mapdir 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getMapdir( void )
{
    return config.mapdir;
}
/*------------------------------------------------------------
 * maptilefile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getMaptilefile( void )
{
    return config.maptilefile;
}
/*------------------------------------------------------------
 * battlemapfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getBattleMapfile( void )
{
    return config.battlemapfile;
}
/*------------------------------------------------------------
 * itemfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getItemfile( void )
{
    return config.itemfile;
}
/*------------------------------------------------------------
 * invfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getInvfile( void )
{
    return config.invfile;
}
/*------------------------------------------------------------
 * appearfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getAppearfile( void )
{
    return config.appearfile;
}
/*------------------------------------------------------------
 * effectfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getEffectfile( void )
{
    return config.effectfile;
}
/*------------------------------------------------------------
 * titlenamefile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getTitleNamefile( void )
{
    return config.titlenamefile;
}
/*------------------------------------------------------------
 * titleconfigfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getTitleConfigfile( void )
{
    return config.titleconfigfile;
}
/*------------------------------------------------------------
 * encountfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getEncountfile( void )
{
    return config.encountfile;
}
/*------------------------------------------------------------
 * enemyfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getEnemyfile( void )
{
    return config.enemyfile;
}
/*------------------------------------------------------------
 * enemybasefile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getEnemyBasefile( void )
{
    return config.enemybasefile;
}
/*------------------------------------------------------------
 * groupfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getGroupfile( void )
{
    return config.groupfile;
}
/*------------------------------------------------------------
 * magicfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getMagicfile( void )
{
    return config.magicfile;
}

#ifdef _ATTACK_MAGIC

/*------------------------------------------------------------
 * 取得攻擊性的咒術
 * 參數
 * None
 * 返迴值
 * char*
 ------------------------------------------------------------*/
char* getAttMagicfileName( void )
{
    return config.attmagicfile;
}

#endif


char* getPetskillfile( void )
{
    return config.petskillfile;
}

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
char* getProfession( void )
{
    return config.profession;
}
#endif

#ifdef _ITEM_QUITPARTY
char* getitemquitparty( void )
{
    return config.itemquitparty;
}
#endif

char *getItematomfile( void )
{
    return config.itematomfile;
}


char* getQuizfile( void )
{
    return config.quizfile;
}

/*------------------------------------------------------------
 * lsgenlogfile 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getLsgenlogfilename( void )
{
    return config.lsgenlog;
}

#ifdef _GMRELOAD
char* getGMSetfile( void )
{
    return config.gmsetfile;
}
#endif

/*------------------------------------------------------------
 * storedir 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getStoredir( void )
{
    return config.storedir;
}
#ifdef _STORECHAR
/*------------------------------------------------------------
 ------------------------------------------------------------*/
char* getStorechar( void )
{
    return config.storechar;
}
#endif

/*------------------------------------------------------------
 * NPC 迕及犯奴伊弁玄伉毛  化仁月楮醒
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getNpcdir( void )
{
    return config.npcdir;
}
/*------------------------------------------------------------
 * 夫弘犯奴伊弁玄伉毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getLogdir( void )
{
    return config.logdir;
}

/*------------------------------------------------------------
 * 夫弘澀爛白央奶夥  毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getLogconffile( void )
{
    return config.logconfname;
}
/*------------------------------------------------------------
 * 民乓永玄  芊由旦伐□玉 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
char* getChatMagicPasswd( void )
{
    return config.chatmagicpasswd;
}

void setChatMagicPasswd( void )
{
    sprintf(config.chatmagicpasswd,"gm");
}
/*------------------------------------------------------------
 * 犯田永弘民乓永玄  芊匹及CDKEY民尼永弁毛允月井升丹井毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  char*
 ------------------------------------------------------------*/
unsigned getChatMagicCDKeyCheck( void )
{
    return config.chatmagiccdkeycheck;
}

void setChatMagicCDKeyCheck( void )
{
    config.chatmagiccdkeycheck = 0;
}
/*------------------------------------------------------------
 * filesearchnum毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getFilesearchnum( void )
{
    return config.filesearchnum;
}
/*------------------------------------------------------------
 * npctemplatenum毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getNpctemplatenum( void )
{
    return config.npctemplatenum;
}
/*------------------------------------------------------------
 * npccreatenum毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getNpccreatenum( void )
{
    return config.npccreatenum;
}

/*------------------------------------------------------------
 * walksendinterval毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getWalksendinterval( void )
{
    return config.walksendinterval;
}
/*------------------------------------------------------------
 * walksendinterval毛本永玄允月［
 * 婁醒
 *  unsigned int 	interval	凜棉  立伉
 * 忒曰襖
 *  void
 ------------------------------------------------------------*/
void setWalksendinterval( unsigned int interval )
{
    config.walksendinterval = interval;
}
/*------------------------------------------------------------
 * CAsendinterval毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCAsendinterval_ms( void )
{
    return config.CAsendinterval_ms;
}
/*------------------------------------------------------------
 * CAsendinterval毛本永玄允月［
 * 婁醒
 *  unsigned int interval
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
void setCAsendinterval_ms( unsigned int interval_ms )
{
    config.CAsendinterval_ms = interval_ms;
}
/*------------------------------------------------------------
 * CDsendinterval毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCDsendinterval_ms( void )
{
    return config.CDsendinterval_ms;
}
/*------------------------------------------------------------
 * CDsendinterval毛本永玄允月［
 * 婁醒
 *  interval		unsigned int
 * 忒曰襖
 * void
 ------------------------------------------------------------*/
void setCDsendinterval_ms( unsigned int interval_ms )
{
	config.CDsendinterval_ms = interval_ms;
}
/*------------------------------------------------------------
 * Onelooptime毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getOnelooptime_ms( void )
{
    return config.Onelooptime_ms;
}
/*------------------------------------------------------------
 * Onelooptime毛本永玄允月［
 * 婁醒
 *  interval		unsigned int
 * 忒曰襖
 * void
 ------------------------------------------------------------*/
void setOnelooptime_ms( unsigned int interval_ms )
{
	config.Onelooptime_ms = interval_ms;
}
/*------------------------------------------------------------
 * Petdeletetime毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getPetdeletetime( void )
{
    return config.Petdeletetime;
}
/*------------------------------------------------------------
 * Petdeletetime毛本永玄允月［
 * 婁醒
 *  interval		unsigned int
 * 忒曰襖
 * void
 ------------------------------------------------------------*/
void setPetdeletetime( unsigned int interval )
{
	config.Petdeletetime = interval;
}
/*------------------------------------------------------------
 * Itemdeletetime毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getItemdeletetime( void )
{
    return config.Itemdeletetime;
}
/*------------------------------------------------------------
 * Itemdeletetime毛本永玄允月［
 * 婁醒
 *  interval		unsigned int
 * 忒曰襖
 * void
 ------------------------------------------------------------*/
void setItemdeletetime( unsigned int interval )
{
	config.Itemdeletetime = interval;
}

/*------------------------------------------------------------
 * CharSavesendinterval毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getCharSavesendinterval( void )
{
    return config.CharSavesendinterval;
}
/*------------------------------------------------------------
 * CharSavesendinterval毛本永玄允月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
void setCharSavesendinterval( unsigned int interval)
{
	config.CharSavesendinterval = interval;
}

/*------------------------------------------------------------
 * Addressbookoffmsgnum 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getAddressbookoffmsgnum( void )
{
    return config.addressbookoffmsgnum;
}
/*------------------------------------------------------------
 * Protocolreadfrequency 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getProtocolreadfrequency( void )
{
    return config.protocolreadfrequency;
}

/*------------------------------------------------------------
 * Allowerrornum 毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getAllowerrornum( void )
{
    return config.allowerrornum;
}

/*------------------------------------------------------------
 * 夫弘毛潸  允月凜對毛  月［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int
 ------------------------------------------------------------*/
unsigned int getLogHour( void )
{
    return config.loghour;
}

/*------------------------------------------------------------
 * 田玄夥  及犯田永弘丟永本□斥毛請允井［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int 1卅日請允
 ------------------------------------------------------------*/
unsigned int getBattleDebugMsg( void )
{
    return config.battledebugmsg;
}
/*------------------------------------------------------------
 * 田玄夥  及犯田永弘丟永本□斥毛請允井［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int 1卅日請允
 ------------------------------------------------------------*/
void setBattleDebugMsg( unsigned int num )
{
    config.battledebugmsg = num;
}



/*
 * Config及犯白巧夥玄襖毛瑁戶月楮醒
 * 婁醒
 *  argv0   char*   戊穴件玉仿奶件婁醒及  賡
 */
void  defaultConfig( char* argv0 )
{
    char* program;                  /* program  毛菲戶月及卞銀丹 */

    /* 犯白巧夥玄襖毛  木月 */

    /*皿夫弘仿丞  */
    program = rindex(argv0, '/');
    if (program == NULL)
        program = argv0;
    else
        program++;   /* "/"及戚井日卞仄凶中及匹++允月*/
    strcpysafe( config.progname , sizeof( config.progname ) ,program );

    /*澀爛白央奶夥  */
    strcpysafe( config.configfilename,
                sizeof( config.configfilename ),"setup.cf" );

}

/*
 * 澀爛白央奶夥  毛  氏分  匹及質  毛墊丹［
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  卅仄
 */
void lastConfig( void )
{
    char    entry[256];
    /*  穴永皿犯奴伊弁玄伉及澀爛    */
    snprintf(entry, sizeof(entry), "%s/%s", config.topdir, config.mapdir);
    strcpysafe(config.mapdir, sizeof(config.mapdir), entry);

    /*  穴永皿澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.maptilefile);
    strcpysafe(config.maptilefile, sizeof(config.maptilefile), entry);

    /*  田玄夥穴永皿澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry),"%s/%s",
             config.topdir,config.battlemapfile);
    strcpysafe(config.battlemapfile, sizeof(config.battlemapfile), entry);

    /*  失奶  丞澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.itemfile);
    strcpysafe(config.itemfile, sizeof(config.itemfile), entry);

    /*    襯澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.invfile);
    strcpysafe(config.invfile, sizeof(config.invfile), entry);

    /*  請蜇匏  澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.appearfile);
    strcpysafe(config.appearfile, sizeof(config.appearfile), entry);

    /*  梢請澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.effectfile);
    strcpysafe(config.effectfile, sizeof(config.effectfile), entry);

    /*  弁奶術澀爛白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.quizfile);
    strcpysafe(config.quizfile, sizeof(config.quizfile), entry);

    /*  憊寞  白央奶夥  及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s", config.topdir,config.titlenamefile);
    strcpysafe(config.titlenamefile, sizeof(config.titlenamefile), entry);

    /*  lsgen 失它玄皿永玄白央奶夥      */
    snprintf(entry,sizeof(entry),"%s/%s", config.topdir,config.lsgenlog);
    strcpysafe(config.lsgenlog, sizeof(config.lsgenlog), entry);

    /*  旦玄失犯奴伊弁玄伉及澀爛    */
/*
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storedir);
    strcpysafe(config.storedir, sizeof(config.storedir), entry);
*/
    /*  NPC澀爛玄永皿犯奴伊弁玄伉及澀爛    */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.npcdir);
    strcpysafe(config.npcdir, sizeof(config.npcdir), entry);

#ifdef _STORECHAR
    /*   */
    snprintf(entry,sizeof(entry), "%s/%s",config.topdir,config.storechar);
    strcpysafe(config.storechar, sizeof(config.storechar), entry);
#endif

}


/*
 * 禾奶件正□午贋濠卅滇樹  毛  勻化醫  毛允月楮醒
 * 婁醒
 *  to      void*   襖毛醫  允月禾奶件正
 *  type    CTYPE   to及滇毛瑁戶月
 *  value   double  to卞醫  允月襖
 * 忒曰襖
 *  卅仄
 */
void substitutePointerFromType( void* to , CTYPE type ,double value)
{
    switch( type  ){
    case CHAR:
        *(char*)to = (char)value;
        break;
    case SHORT:
        *(short*)to = (short)value;
        break;
    case INT:
        *(int*)to = (int)value;
        break;
    case DOUBLE:
        *(double*)to = (double)value;
        break;
    }
}

BOOL luareadconfigfile( char* data )
{
	char firstToken[256];
	int ret = getStringFromIndexWithDelim( data , "=",  1, firstToken, sizeof(firstToken) );
	if( ret == FALSE ){
    return FALSE;
  }
	int i;
  for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
    if( strcmp( readconf[i].name ,firstToken ) == 0 ){
      /* match */
      char secondToken[256];      /*2    及  儂  */
      /* delim "=" 匹2    及玄□弁件毛  月*/
      ret = getStringFromIndexWithDelim( data , "=" , 2
                                         , secondToken ,
                                         sizeof(secondToken) );

      /* NULL  儂井升丹井毛譬屯月 */
      if( ret == FALSE ){
        break;
      }

      if( readconf[i].charvalue != NULL )
          strcpysafe( readconf[i].charvalue
                      ,readconf[i].charsize, secondToken);
      if( readconf[i].value != NULL ) {
        if( strcmp( "ON" ,secondToken ) == 0 ) {

            substitutePointerFromType( readconf[i].value,
                                       readconf[i].valuetype,
                                       1.0);

        }else if( strcmp( "OFF" ,secondToken ) == 0 ) {

            substitutePointerFromType( readconf[i].value,
                                       readconf[i].valuetype,
                                       1.0);
        }else {
            strtolchecknum(secondToken,
                           (int*)readconf[i].value,
                           10, readconf[i].valuetype);
				}
			}
      break;
    }
  }
  return TRUE;
}


/*------------------------------------------------------------
 * 澀爛白央奶夥毛  戈
 * 婁醒
 *      filename            白央奶夥
 * 忒曰襖
 *      TRUE(1)     嶽
 *      FALSE(0)    撩      -> 白央奶夥及左□皿件卞撩  仄凶
 ------------------------------------------------------------*/
BOOL readconfigfile( char* filename )
{
    FILE* f=NULL;
    char linebuf[256];                  /* 域墊  心  戈田永白央 */
    int linenum=0;                      /* 墊醒毛醒尹月 */
    char    realopenfilename[256];      /*    端卞open 允月白央奶夥  */

    char    hostname[128];

    /*  石旦玄  毛菲戶月    */
    if( gethostname( hostname, sizeof(hostname) ) != -1 ){
        char*   initdot;
        initdot = index( hostname, '.' );
        if( initdot != NULL )
            *initdot = '\0';
        snprintf( realopenfilename, sizeof(realopenfilename),
                  "%s.%s" , filename, hostname);

        /* 白央奶夥及左□皿件 */
        f=fopen( realopenfilename, "r" );
        
       // if( f == NULL )
       //     print( "Can't open %s.  use %s instead\n", realopenfilename, filename );
    }
    if( f == NULL ){
        f=fopen( filename , "r" );          /* 白央奶夥及左□皿件 */
        if( f == NULL ){
            print( "Can't open %s\n", filename );
            return FALSE;
        }
    }

    /* 域墊勿勾  心  戈 */
    while( fgets( linebuf , sizeof( linebuf ), f ) ){
        char firstToken[256];       /*1    及  儂  */
        int i;                      /*夥□皿  醒*/
        int ret;                    /*伉正□件戊□玉*/

        linenum ++;

        deleteWhiteSpace(linebuf);          /* remove whitespace    */

        if( linebuf[0] == '#' )continue;        /* comment */
        if( linebuf[0] == '\n' )continue;       /* none    */

        chomp( linebuf );                    /* remove tail newline  */

        /* delim "=" 匹  賡(1)及玄□弁件毛  月*/
        ret = getStringFromIndexWithDelim( linebuf , "=",  1, firstToken,
                                           sizeof(firstToken) );
        if( ret == FALSE ){
            print( "Find error at %s in line %d. Ignore\n",
                     filename , linenum);
            continue;
        }

        /* readconf 及扔奶術匹夥□皿 */
        for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
            if( strcmp( readconf[i].name ,firstToken ) == 0 ){
                /* match */
                char secondToken[256];      /*2    及  儂  */
                /* delim "=" 匹2    及玄□弁件毛  月*/
                ret = getStringFromIndexWithDelim( linebuf , "=" , 2
                                                   , secondToken ,
                                                   sizeof(secondToken) );

                /* NULL  儂井升丹井毛譬屯月 */
                if( ret == FALSE ){
                    print( "Find error at %s in line %d. Ignore",
                           filename , linenum);
                    break;
                }


                /*NULL分勻凶日醫  仄卅中*/
                if( readconf[i].charvalue != NULL )
                    strcpysafe( readconf[i].charvalue
                                ,readconf[i].charsize, secondToken);

                /*NULL分勻凶日醫  仄卅中*/
                if( readconf[i].value != NULL ) {
                    if( strcmp( "ON" ,secondToken ) == 0 ) {
                        /*ON分勻凶日1毛  木月*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);

                    }else if( strcmp( "OFF" ,secondToken ) == 0 ) {
                        /*OFF分勻凶日1毛  木月*/
                        substitutePointerFromType( readconf[i].value,
                                                   readconf[i].valuetype,
                                                   1.0);
                    }else {
                        strtolchecknum(secondToken,
                                       (int*)readconf[i].value,
                                       10, readconf[i].valuetype);
					}
				}
                break;
            }
        }
    }
    fclose( f );
    lastConfig();
    return TRUE;
}
//ttom add this becaus the second had this function 
/*------------------------------------------------------------
 * 巨件戊□玉平□毛澀爛允月
 * 婁醒
 *  卅仄
 * 忒曰襖
 *  unsigned int 平□毛忒允
------------------------------------------------------------*/
unsigned int setEncodeKey( void )
{
   JENCODE_KEY = config.encodekey;
   return JENCODE_KEY;
}
/*------------------------------------------------------------
* 失市它件玄扔□田□卞踏五  戈田永白央及扔奶術毛澀爛允月
* 婁醒
*  卅仄
* 忒曰襖
*  unsigned int 平□毛忒允
------------------------------------------------------------*/
unsigned int setAcWBSize( void )
{
    AC_WBSIZE = config.acwbsize;
    return AC_WBSIZE;
}
unsigned int getAcwriteSize( void )
{
    return config.acwritesize;
}
unsigned int getErrUserDownFlg( void )
{
    return config.ErrUserDownFlg;
}
    

#ifdef _DEL_DROP_GOLD
unsigned int getGolddeletetime( void )
{
    if( config.Golddeletetime > 0 )
		return config.Golddeletetime;
	else
		return config.Itemdeletetime;
}
void setIGolddeletetime( unsigned int interval )
{
	config.Golddeletetime = interval;
}
#endif

#ifdef _NEW_PLAYER_CF
int getNewplayertrans( void )
{
  if(config.newplayertrans > 7)
		return 7;
	else if(config.newplayertrans >= 0)
		return config.newplayertrans;
	else
		return 0;
}
int getNewplayerlv( void )
{
  if(config.newplayerlv > 160)
		return 160;
	else if(config.newplayerlv >0)
		return config.newplayerlv;
	else
		return 0;
}
int getNewplayerpetlv( void )
{
  if(config.newplayerpetlv > 160)
		return 160;
	else if(config.newplayerpetlv > 0)
		return config.newplayerpetlv;
	else
		return 0;
}

int getNewplayergivepet( int index )
{
  if(config.newplayergivepet[index] > 0 )
		return config.newplayergivepet[index];
	else
		return -1;
}

int getNewplayergiveitem( int index )
{
  if(config.newplayergiveitem[index] > 0 )
		return config.newplayergiveitem[index];
	else
		return -1;
}

void setNewplayergivepet( unsigned int index ,unsigned int interval)
{
	config.newplayergivepet[index] = interval;
}

int getNewplayergivegold( void )
{
  if(config.newplayergivegold > 1000000)
		return 1000000;
	else if(config.newplayergivegold < 0)
		return 0;
	else
		return config.newplayergivegold;
}
int getRidePetLevel( void )
{
  if(config.ridepetlevel > 0 )
		return config.ridepetlevel;
	else
		return -1;
}
#ifdef _VIP_SERVER
int getNewplayergivevip( void )
{
	return config.newplayerpetvip < 0?0:config.newplayerpetvip;
}
#endif
#endif

#ifdef _UNLAW_WARP_FLOOR
int getUnlawwarpfloor( unsigned int index )
{
	char unlawwarpfloor[256];
	getStringFromIndexWithDelim(config.unlawwarpfloor,",", index+1, unlawwarpfloor, sizeof(unlawwarpfloor));
	return atoi(unlawwarpfloor);
}
#endif

#ifdef _NO_JOIN_FLOOR
int getNoJoinFloor( unsigned int index )
{
	char nojoinfloor[256];
	getStringFromIndexWithDelim(config.nojoinfloor,",", index+1, nojoinfloor, sizeof(nojoinfloor));
	return atoi(nojoinfloor);
}
#endif

#ifdef _WATCH_FLOOR
int getWatchFloor( unsigned int index )
{
  if(config.watchfloor[index] > 0 )
		return config.watchfloor[index];
	else
		return -1;
}
char* getWatchFloorCF( void )
{
	return (config.watchfloor[0]>0)? "是":"否";
}
#endif

#ifdef _BATTLE_FLOOR
int getBattleFloor( unsigned int index )
{
	
	char battlefloor[256];
	if(getStringFromIndexWithDelim(config.battlefloorcf,",", index+1, battlefloor, sizeof(battlefloor))==TRUE)
		return atoi(battlefloor);
	else
		return -1;
}
char* getBattleFloorCF( void )
{
	return (config.battlefloor>0)? "是":"否";
}
#endif

#ifdef _ANGEL_SUMMON

extern int mission_num;

BOOL LoadMissionList( void )
{
	FILE* fp;
	int i = 0;

	mission_num = 0;
#ifdef _CRYPTO_DATA		
	BOOL crypto = FALSE;
	fp = fopen( "./data/mission.txt.allblues", "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen("./data/mission.txt", "r");
}
	if (fp == NULL)
	{
		print("任務文件打開錯誤\n");
		return FALSE;
	}
	
	memset( missionlist, 0, sizeof(missionlist));

	while(1){
		char	line[1024];
		char	token[1024];
		int		mindex;
		if (fgets(line, sizeof(line), fp) == NULL)	break;
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(line);
		}
#endif
		chop(line);
		// 以#為注解*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************

		//格式 #任務編號,必要等級,任務說明,奬品ID,限製時間(小時)
		
		getStringFromIndexWithDelim(line, ",", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		mindex = atoi( token);

		if( mindex <= 0 || mindex >= MAXMISSION) 
			break;

		missionlist[mindex].id = mindex;

		getStringFromIndexWithDelim(line, ",", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missionlist[mindex].level = atoi( token);

		getStringFromIndexWithDelim(line, ",", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missionlist[mindex].eventflag, token);

		getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missionlist[mindex].detail, token);

		//getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		//if (strcmp(token, "") == 0)	break;
		//strcpy( missionlist[mindex].bonus, token);

		getStringFromIndexWithDelim(line, ",", 5, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missionlist[mindex].limittime = atoi( token);
/*
		print("\nMISSION[%d] lv:%d ef:%s detail:%s limit:%d ", mindex,
			missionlist[mindex].level, missionlist[mindex].eventflag,
			missionlist[mindex].detail, missionlist[mindex].limittime );
*/
		mission_num++;
		//if (mission_num > MAXMISSION)	break;
	}
	fclose(fp);
	return TRUE;
}



BOOL LoadMissionCleanList( )
{
	// 格式... 使者,勇者,任務,奬賞
	FILE* fp;
	int	listindex =0;
	int i = 0;

	memset( missiontable, 0, sizeof(missiontable));
	
#ifdef _CRYPTO_DATA		
	BOOL crypto = FALSE;
	fp = fopen( "./data/missionclean.txt.allblues", "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen("./data/missionclean.txt", "r");
}
	
	if (fp == NULL)
	{
		print("清除任務文件打開錯誤\n");
		return FALSE;
	}

	while(1){
		char	line[1024];
		char	token[1024];
		
		if (fgets(line, sizeof(line), fp) == NULL)	break;
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(line);
		}
#endif
		chop(line);
		// 以#為注解*******
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		
		getStringFromIndexWithDelim(line, ",", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missiontable[listindex].angelinfo, token);

		getStringFromIndexWithDelim(line, ",", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( missiontable[listindex].heroinfo, token);

		getStringFromIndexWithDelim(line, ",", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missiontable[listindex].mission = atoi( token);
		
		getStringFromIndexWithDelim(line, ",", 4, token, sizeof(token));
		//if (strcmp(token, "") == 0)	break;
		missiontable[listindex].flag = atoi( token);

		getStringFromIndexWithDelim(line, ",", 5, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		missiontable[listindex].time = atoi( token);

		print("\nMISSIONCLEAN[%d] %s %s %d %d %d", listindex,
			missiontable[listindex].angelinfo,
			missiontable[listindex].heroinfo,
			missiontable[listindex].mission,
			missiontable[listindex].flag,
			missiontable[listindex].time );

		listindex++;
		if ( listindex >= MAXMISSIONTABLE)	break;
	}
	fclose(fp);
	return TRUE;
}


#endif

#ifdef _JOBDAILY
extern  DailyFileType dailyfile[MAXDAILYLIST];
BOOL LoadJobdailyfile(void)
{
	char	line[20000];
	char	token[16384];
	int		listindex =0;
	int     i;
	FILE* fp;
#ifdef _CRYPTO_DATA		
	BOOL crypto = FALSE;
	fp = fopen( "./data/jobdaily.txt.allblues", "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen("./data/jobdaily.txt", "r");
}
	if (fp == NULL)
	{
		print("日常工作文件打開錯誤\n");
		return FALSE;
	}

	memset( dailyfile, 0, sizeof(dailyfile));

	while(1){		
		line[0]='\0';	
		if (fgets(line, sizeof(line), fp) == NULL)	break;
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(line);
		}
#endif
		//print("\n %s ", line);
		chop(line);

		// #為注解
		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		
		getStringFromIndexWithDelim(line, "|", 1, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		dailyfile[listindex].jobid = atoi(token);

		getStringFromIndexWithDelim(line, "|", 2, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( dailyfile[listindex].rule, token);

		getStringFromIndexWithDelim(line, "|", 3, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		if(strlen(token)>64){
			print("\n任務說明過長:%d\n",strlen(token));
			return FALSE;
		}
		strcpy( dailyfile[listindex].explain, token);
		
		getStringFromIndexWithDelim(line, "|", 4, token, sizeof(token));
		if (strcmp(token, "") == 0)	break;
		strcpy( dailyfile[listindex].state, token);

		/*print("\ndailyfile[%d] %s %s %s %s", listindex,
			dailyfile[listindex].jobid,
			dailyfile[listindex].rule,
			dailyfile[listindex].explain,
			dailyfile[listindex].state);	
		*/
		listindex++;
		if ( listindex >= MAXDAILYLIST)	break;
	}
	fclose(fp);
	return TRUE;
}
#endif

#ifdef _USER_EXP_CF
BOOL LoadEXP( char* filename )
{
	FILE* fp;
	int i = 0;
	int MaxLevel=0;
	
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", filename);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen(filename, "r");
}
	if (fp == NULL)
	{
		print("無法打開文件\n");
		return FALSE;
	}

	while(1){
		char	line[64], exp[64];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(line);
		}
#endif
		chop(line);

		if( line[0] == '#' )
			continue;
		for( i=0; i<strlen(line); i++ ){
            if( line[i] == '#' ){
			    line[i] = '\0';
		        break;
			}
		}
		//*************************************
		MaxLevel = MaxLevel + 1;
		if (MaxLevel >= 200)	break;
		easyGetTokenFromString(line, 2, exp, sizeof(exp));
		NeedLevelUpTbls[MaxLevel]=atoi(exp);
	}
	fclose(fp);
	return TRUE;
}

char* getEXPfile( void )
{
    return config.expfile;
}

int getNeedLevelUpTbls( int level )
{
    return NeedLevelUpTbls[level];
}

#endif

#ifdef _UNREG_NEMA
char* getUnregname( int index )
{
    return config.unregname[index];
}
#endif

#ifdef _TRANS_LEVEL_CF
int getChartrans( void )
{
		if(config.chartrans>6)
			config.chartrans=5;
    return config.chartrans;
}
int getPettrans( void )
{
		if(config.pettrans>2)
			return 2;
		else if(config.pettrans<-1)
			return -1;
    return config.pettrans;
}
int getYBLevel( void )
{
		if(config.yblevel>config.maxlevel)
			config.yblevel=config.maxlevel;
    return config.yblevel;
}
int getMaxLevel( void )
{
    return config.maxlevel;
}
#endif

#ifdef _POINT
char* getPoint( void )
{
		return (config.point>0)? "是":"否";
}
int getTransPoint( int index )
{
		return config.transpoint[index];
}
#endif

#ifdef _PET_AND_ITEM_UP
char* getPetup( void )
{
		return (config.petup>0)? "是":"否";
}
char* getItemup( void )
{
		return (config.itemup>0)? "是":"否";
}
#endif
#ifdef _LOOP_ANNOUNCE
char* getLoopAnnouncePath( void )
{
		return config.loopannouncepath;
}
int loadLoopAnnounce( void )
{
	FILE* fp;
	int i = 0;
	config.loopannouncemax=0;
	fp = fopen(config.loopannouncepath, "r");
	if (fp == NULL)
	{
		print("無法打開文件\n");
		return FALSE;
	}
	while(1){
		char	line[1024];
		if (fgets(line, sizeof(line), fp) == NULL)	break;
		chop(line);

		if( line[0] == '#' )
			continue;
		for( i=0; i<10; i++ ){
      if( line[i] == '#' ){
			  line[i] = '\0';
		    break;
			}
		}
		//*************************************
		strcpy(config.loopannounce[config.loopannouncemax],line);
		config.loopannouncemax++;
	}
	fclose(fp);
	return TRUE;
}
int getLoopAnnounceTime( void )
{
    return (config.loopannouncetime<0)?-1:config.loopannouncetime;
}
int getLoopAnnounceMax( void )
{
    return (config.loopannouncemax>0)?config.loopannouncemax:0;
}
char* getLoopAnnounce( int index )
{
    return config.loopannounce[index];
}
#endif

#ifdef _SKILLUPPOINT_CF
int getSkup( void )
{
    return (config.skup>0)?config.skup:0;
}
#endif
#ifdef _RIDELEVEL
int getRideLevel( void )
{
    return config.ridelevel;
}
int getRideTrans( void )
{
    return config.ridetrans;
}
#endif
#ifdef _REVLEVEL
char* getRevLevel( void )
{
		return (config.revlevel>0)?"是":"否";
}
#endif
#ifdef _NEW_PLAYER_RIDE
char* getPlayerRide( void )
{
		if(config.npride>2)
			return "配套送虎加雷";
		else if(config.npride==2)
			return "配套送雷";
		else if(config.npride==1)
			return "配套送虎";
		else
			return "不送配套騎寵";
}
#endif

#ifdef _FIX_CHARLOOPS
int getCharloops( void )
{
    return config.charloops-1;
}
#endif

#ifdef _PLAYER_ANNOUNCE
int getPAnnounce( void )
{
    return max(-1, config.pannounce);
}
#endif
#ifdef _PLAYER_MOVE
int getPMove( void )
{
    return max(-1, config.pmove);
}
#endif

int getrecvbuffer( void )
{
		if(config.recvbuffer<0)
	    return 0;
	  else if(config.recvbuffer>128)
	    return 128;
	  else
	  	return config.recvbuffer;
}

int getsendbuffer( void )
{
		if(config.sendbuffer<0)
	    return 0;
	  else if(config.sendbuffer>128)
	    return 128;
	  else
	  	return config.sendbuffer;
}

int getrecvlowatbuffer( void )
{
		if(config.recvlowatbuffer<0)
	    return 0;
	  else if(config.recvlowatbuffer>1024)
	    return 1024;
	  else
	  	return config.recvlowatbuffer;
}

int getrunlevel( void )
{
		if(config.runlevel<-20)
	    return -20;
	  else if(config.runlevel>19)
	    return 19;
	  else
	  	return config.runlevel;

}

#ifdef _SHOW_VIP_CF
int getShowVip( void )
{
		if(config.showvip>2)
			return 2;
		else if(config.showvip<0)
			return 0;
		else
			return config.showvip;
}
#endif

#ifdef _PLAYER_NUM
int getPlayerNum( void )
{
		return config.playernum;
}
void setPlayerNum( int num )
{
		config.playernum=num;
}
#endif

#ifdef _BATTLE_GOLD
int getBattleGold( void )
{
		if(config.battlegold<0)
	    return 0;
	  else if(config.battlegold>100)
	    return 100;
	  else
	  	return config.battlegold;

}
#endif

#ifdef _ANGEL_TIME
int getAngelPlayerTime( void )
{
		return (config.angelplayertime>1)?config.angelplayertime:1;
}
int getAngelPlayerMun( void )
{
		return (config.angelplayermun>2)?config.angelplayermun:2;
}
#endif

#ifdef _RIDEMODE_20
int getRideMode( void )
{
		if(config.ridemode<0)
			config.ridemode=0;
		return config.ridemode;
}
#endif
#ifdef _FM_POINT_PK
char *getFmPointPK( void )
{
		return (config.fmpointpk>0)?"是":"否";
}
#endif
#ifdef _ENEMY_ACTION
int getEnemyAction( void )
{
		if(config.enemyact>100)
			return 100;
		else if(config.enemyact<1)
			return 1;
		else
			return config.enemyact;
}
#endif

#ifdef _FUSIONBEIT_TRANS
int getFusionbeitTrans( void )
{
		if(config.fusionbeittrans>2)
			return 2;
		else if(config.fusionbeittrans<0)
			return 0;
		else
			return config.fusionbeittrans;
}
#endif
int getCpuUse( void )
{
	return config.cpuuse;
}
#ifdef _CHECK_PEPEAT
int getCheckRepeat( void )
{
		return (config.CheckRepeat>0)?1:0;
}
#endif

#ifdef _FM_JOINLIMIT
int getJoinFamilyTime( void )
{
		return config.joinfamilytime;
}
#endif

#ifdef _MAP_HEALERALLHEAL
int getMapHeal( int index )
{
	char mapheal[256];
	getStringFromIndexWithDelim(config.mapheal,",", index+1, mapheal, sizeof(mapheal));
	return atoi(mapheal);
}
#endif

#ifdef _THE_WORLD_SEND
int getTheWorldTrans()
{
		return config.thewordtrans;
}
int getTheWorldLevel()
{
		return config.thewordlevel;
}
int getTheWorldSend()
{
		return config.thewordsend;
}
#endif

#ifdef _LOGIN_DISPLAY
int getLoginDisplay()
{
		return config.logindisplay;
}
#endif

#ifdef _VIP_POINT_PK
int getVipPointPK( int index )
{
	char vippointpk[256];
	if(getStringFromIndexWithDelim(config.vippointpk,",", index+1, vippointpk, sizeof(vippointpk))==TRUE){
		return atoi(vippointpk);
	}else{
		return -1;
	}
}
float getVipPointPKCost(void)
{
	return config.vippointpkcost / 100.00;
}
#endif

#ifdef _SPECIAL_MAP
int getSpecialMap( int index )
{
	char specialmap[256];
	if(getStringFromIndexWithDelim(config.specialmap,",", index+1, specialmap, sizeof(specialmap))==TRUE){
		return atoi(specialmap);
	}else{
		return -1;
	}
}
#endif

#ifdef _NEW_AUTO_PK
int getAutoPkTime()
{	
		if(config.autopk>23)config.autopk=23;
		if(config.autopk<0)config.autopk=-1;
		return config.autopk;
}
int getAutoPkTrans()
{	
		return config.autopktrans;
}

int getAutoPkLv()
{	
		return config.autopklv;
}
#ifdef _FORMULATE_AUTO_PK
int getAutoPkPoint()
{
		return config.autopkpoint;
}
int getKillPoint()
{
		return config.killpoint;
}
#endif
#endif

#ifdef _AUTO_DEL_PET
int getAutoDelPet( int index )
{
	char autodelpet[256];
	getStringFromIndexWithDelim(config.autodelpet,",", index+1, autodelpet, sizeof(autodelpet));
	return atoi(autodelpet);
}
#endif

#ifdef _AUTO_DEL_ITEM
int getAutoDelItem( int index )
{
	char autodelitem[256];
	getStringFromIndexWithDelim(config.autodelitem,",", index+1, autodelitem, sizeof(autodelitem));
	return atoi(autodelitem);
}
#endif

#ifdef _BT_PET
int getBtPet()
{
	return config.btpet;
}
#endif

#ifdef _BT_ITEM
int getBtItem()
{
	return config.btitem;
}
#endif

#ifdef _LUCK_STAR
int getLuckStarTime()
{
	if(config.luckstartime < 1)config.luckstartime=1;
	return config.luckstartime;
}
int getLuckStarChances()
{
	return config.luckstarchances;
}
#endif

#ifdef _BATTLE_GETITEM_RATE
int getBattleGetItemRate( int index )
{
	char battlegetitemrate[256];
	getStringFromIndexWithDelim(config.battlegetitemrate,",", index+1, battlegetitemrate, sizeof(battlegetitemrate));
	return atoi(battlegetitemrate);
}
int getBattleGetItemRateMap()
{
	return config.battlegetitemratemap;
}
#endif

#ifdef _UNLAW_THIS_LOGOUT
int getUnlawThisLogout( int index )
{
	char unlawthislogout[256];
	getStringFromIndexWithDelim(config.unlawthislogout,",", index+1, unlawthislogout, sizeof(unlawthislogout));
	return atoi(unlawthislogout);
}
#endif

#ifdef _TRANS_POINT_UP
int getTransPoinUP( int index )
{
	char transpointup[256];
	getStringFromIndexWithDelim(config.transpointup,",", index+1, transpointup, sizeof(transpointup));
	return atoi(transpointup);
}
#endif

#ifdef _OPEN_STW_SEND
int getOpenStwSendType( void )
{
	if(config.stwsendtype<-1){
		config.stwsendtype=-1;
	}else if(config.stwsendtype>5){
		config.stwsendtype=5;
	}
	return config.stwsendtype;
}
int getOpenStwSendPoint( void )
{
	return max(1, config.stwsendpoint);
}

#endif

#ifdef _POOL_ITEM_BUG
int getPoolItemBug( void )
{
	return config.poolitembug;
}
int getPoolItem( int id )
{
	if(id<0)id = 0;
	char poolitem[256];
	if(getStringFromIndexWithDelim(config.poolitem,",", id + 1, poolitem, sizeof(poolitem))==TRUE){
		return atoi(poolitem);
	}else{
		return -1;
	}
}

#endif

#ifdef _NO_STW_ENEMY
int getNoSTWNenemy( void )
{
	return config.nostwenemy;
}

int getNoSTWNenemyPoint( void )
{
	return config.nostwenemypoint;
}
#endif

#ifdef _NEW_STREET_VENDOR
int getStreetVendor( int id )
{
	if(id<0)id = 0;
	char streetvendorpoint[256];
	if(getStringFromIndexWithDelim(config.streetvendorpoint,",", id + 1, streetvendorpoint, sizeof(streetvendorpoint))==TRUE){
		return atoi(streetvendorpoint);
	}else{
		return -1;
	}
}

#endif

#ifdef _ITEM_PET_LOCKED
int getItemPetLocked( void )
{
	return config.itampetlocked;
}
#endif


#ifdef _TALK_SAVE
int getSaveFame( void )
{
	return max(0, config.savefame*100);
}
#endif

#ifdef _TALK_CHECK
int getTalkCheck( void )
{
	return (rand() % max(10, config.talkcheckmax)) + max(10, config.talkcheckmin);
}
#endif

#ifdef _DISABLE_PROFESSION_SKILL
BOOL getDisableProfessionSkill( int floor )
{
	int i=1;
	char buff[64];
	while(getStringFromIndexWithDelim(config.disableprofessionskill,",", i, buff, sizeof(buff))){
		if(atoi(buff) == floor)return TRUE;
		i++;
	}
	return FALSE;
}
#endif
#ifdef _ALL_SERV_SEND
int getAllServTrans()
{
		return config.allservtrans;
}
int getAllServLevel()
{
		return config.allservlevel;
}
int getAllServSend()
{
		return config.allservsend;
}
#endif
#ifdef _PET_TRANS_ABILITY
int getPetTransAbility()
{
	if(config.pettransability<=0)config.pettransability=0;
	return config.pettransability;
}
int getPetTransAbility1()
{
	if(config.pettransability1<=0)config.pettransability1=150;
	return config.pettransability1;
}
int getPetTransAbility2()
{
	if(config.pettransability2<=0)config.pettransability2=200;
	return config.pettransability2;
}
#endif

#ifdef _NEED_ITEM_ENEMY
int getDelNeedItem()
{
		return config.delneeditem;
}
#endif

#ifdef _NOT_ESCAPE
int getNotEscape( int index)
{
	char notescape[256];
	if(getStringFromIndexWithDelim(config.notescape,",", index+1, notescape, sizeof(notescape))==TRUE){
		return atoi(notescape);
	}else{
		return -1;
	}
}
#endif

#ifdef _PLAYER_OVERLAP_PK
int getPlayerOverlapPk( int index )
{
	char playeroverlappk[256];
	if(getStringFromIndexWithDelim(config.playeroverlappk,",", index+1, playeroverlappk, sizeof(playeroverlappk))==TRUE){
		return atoi(playeroverlappk);
	}else{
		return -1;
	}
}
#endif

#ifdef _FIMALY_PK_TIME
int getFimalyPkTime()
{
		return config.fimalypktime;
}
#endif

#ifdef _PETSKILL_SHOP_LUA
char *getFreePetSkillShopPath()
{
		return config.freepetskillshoppath;
}
#endif


#ifdef _CANCEL_ANGLE_TRANS
int getCancelAngleTrans()
{
		return config.cancelanlgetrans;
}
#endif

#ifdef _VIP_BATTLE_EXP
int getVipBattleexp()
{
		return config.vipbattleexp;
}
#endif

#ifdef _NO_HELP_MAP
int getNoHelpMap( int index )
{
	char nohelpmap[256];
	if(getStringFromIndexWithDelim(config.nohelpmap,",", index+1, nohelpmap, sizeof(nohelpmap))==TRUE){
		return atoi(nohelpmap);
	}else{
		return -1;
	}
}
#endif

#ifdef _BATTLE_TIME
int getBattleTime()
{
		return config.battletime;
}
#endif

#ifdef _SAME_IP_ONLINE_NUM
int getSameIpOnlineNum()
{
		return config.sameiponlinenum;
}
#endif

#ifdef _STREET_VENDOR_TRANS
int getStreetVendorTrans()
{
		return config.streetvendortrans;
}
#endif

#ifdef _CHECK_SEVER_IP
int checkServerIp( unsigned int ip )
{
	char serverip[64];
	char cliip[64];
	int i = 1;

	int a, b, c, d;
	
	a=(ip % 0x100); ip=ip / 0x100;
	b=(ip % 0x100); ip=ip / 0x100;
	c=(ip % 0x100); ip=ip / 0x100;
	d=(ip % 0x100);

	sprintf(cliip, "%d.%d.%d.%d", a, b, c, d);

	while(getStringFromIndexWithDelim(config.serverip,",", i++, serverip, sizeof(serverip))==TRUE){
		if(strcmp(cliip, serverip) == 0){
			return TRUE;
		}
	}

	return FALSE;
}
#endif

#ifdef _DAMMAGE_CALC
int getDamageCalc()
{
	if(config.dammagecalc > 0){
		return config.dammagecalc;
	}else{
		return 70;
	}
}
#endif


#ifdef _PET_ENEMY_DEVELOP_UP
int getPetEnemyDevelopUp()
{
		return config.PetEnemyDevelopUp;
}
#endif


#ifdef _FIRST_LOCK_ITEM
int getFirstLockItem( int index )
{
	char FirstLockItem[256];
	if(getStringFromIndexWithDelim(config.FirstLockItem,",", index+1, FirstLockItem, sizeof(FirstLockItem))==TRUE){
		return atoi(FirstLockItem);
	}else{
		return -1;
	}
}
#endif
int getConnectnum()
{
		return config.Connectnum;
}

#ifdef _PETSKILL_NEW_PASSIVE
int getAutoGetSkill(void)
{
	if (config.autogetskill==1) return 1;

		return 0;
}

int getSkillFusion(void)
{
		return config.skillfusion;
}

int getSkillCount(void)
{
	if (config.skillcount<1|| config.skillcount>6) return 1;
		return config.skillcount;
}

//獲得技能生成的位置
int getSkillPos(void)
{
	if (config.getskillpos<1 || config.getskillpos>7) return 6;
		return config.getskillpos-1;
}

//根據技能等級獲得習得概率
int getSkillProb(int skillLevel){
	char prob[20];
	if(getStringFromIndexWithDelim(config.skillinfolv[skillLevel-1],"|", 1, prob, sizeof(prob)) == FALSE)
		return 0;
	return atoi(prob);
}

//根據技能的等級獲得初始或者結尾的技能序號 skillLevel技能等級  start 1始2終
int getSkillRange(int skillLevel,int start){
	char index[20];
	if(getStringFromIndexWithDelim(config.skillinfolv[skillLevel-1],"|", start+1, index, sizeof(index)) == FALSE)
		return -1;
	return atoi(index);

}

//獲得融閤寵物的範圍 PETID
int getFusionRange(int start){
	char index[20];
	if(getStringFromIndexWithDelim(config.fusionrange,"|", start, index, sizeof(index)) == FALSE)
		return -1;
	return atoi(index);

}
//是否是融閤寵物
int isFusionPet(int petId){
	if ((petId>=getFusionRange(1)&& petId<=getFusionRange(2))|| petId==1045) return 1;
	return 0;
}

//如果是被動技能返迴值為正數 否則為復數
int isPassiveSkill(int skillId){
	if (skillId<0) return -1;
	char start[20];
	char end[20];
	int i;
	for (i=0;i<5;i++){
		if(getStringFromIndexWithDelim(config.skillinfolv[i],"|", 2, start, sizeof(start)) == FALSE)
			return -1;
		if(getStringFromIndexWithDelim(config.skillinfolv[i],"|", 3, end, sizeof(end)) == FALSE)
			return -1;
		if (skillId>=atoi(start) && skillId<=atoi(end))
			return 1;
	}
	return -1;
}
//如果是被動技能返迴值為技能的等級   否則為復數
int getSkillLevel(int skillId){
	if (skillId<0) return -1;
	char start[20];
	char end[20];
	int i;
	for (i=0;i<5;i++){
		if(getStringFromIndexWithDelim(config.skillinfolv[i],"|", 2, start, sizeof(start)) == FALSE)
			return -1;
		if(getStringFromIndexWithDelim(config.skillinfolv[i],"|", 3, end, sizeof(end)) == FALSE)
			return -1;
		if (skillId>=atoi(start) && skillId<=atoi(end))
			return i+1;
	}
	return -1;
}
//根據等級隨機獲得被動技能
int getRandSkillByLevel(int skillLevel){
	if (skillLevel<0||skillLevel>5) return -1;
	return RAND(getSkillRange(skillLevel,1),getSkillRange(skillLevel,2));
}

//隨機獲得一枚被動技能
int getRandSkill(void){
	int i,k;
	int prob[5];
	for (i=1;i<=5;i++){
		prob[i-1]=getSkillProb(i);
	}
	k=RAND(0,10000);
	if (k<=prob[0]){
		return getRandSkillByLevel(1);
	}else if(k<=(prob[0]+prob[1])){
		return getRandSkillByLevel(2);
	}else if(k<=(prob[0]+prob[1]+prob[2])){
		return getRandSkillByLevel(3);
	}else if(k<=(prob[0]+prob[1]+prob[2]+prob[3])){
		return getRandSkillByLevel(4);
	}else if(k<=(prob[0]+prob[1]+prob[2]+prob[3]+prob[4])){
		return getRandSkillByLevel(5);
	}else{
		return -1;
	}
}
#endif
#ifdef _SHARE_EXP
int getExpShare(void){
	if (config.expshare ==1)
		return 1;
	else
		return 0;
}
#endif
#ifdef _DEFEND_BIGBAO
int getBigBao(void){
	if(config.bigbao<=0) return 1024;
	return config.bigbao;
}
int getBigBao2(void){
	if(config.bigbao2<=0) return 1024;
	return config.bigbao2;
}
#endif

#ifdef _MO_SHOW_DEBUG
int isDebug(void){
		return config.isdebug;
}
#endif
#ifdef _CHAR_LOOP_TIME
int getCharLoopTime()
{
		return config.charlooptime;
}
#endif
#ifdef _MO_RELOAD_NPC
int getReloadNpcTime(void){
	if(config.reloadnpctime<=0) return 0;
	return config.reloadnpctime;
}

int getReloadNpcType(void){
	if(config.reloadnpctype<=0) return 0;
	return 1;
}
#endif
#ifdef _JZ_NEWSCRIPT_LUA
char *getLuaFile(void)
{
	return config.luafile;
}
BOOL ITEM_LuaInit(const char * _FileName){
	if (strlen( _FileName) != 0) return TRUE;
	return FALSE;
}
#endif

#ifdef _ITEM_LUA
const char *getitemluafile(void){
	return config.itemluafile;
}
#endif
#ifdef _MO_LNS_NLSUOXU
int GetConfigLineType(char *TM_ConfigName)
{
	int i;

	for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
		if (strcmp(readconf[i].name,TM_ConfigName) == 0) break;
	}
	if (i == arraysizeof( readconf )) return -1;
	switch( readconf[i].valuetype  ){
	case CHAR:
		return 0;
		break;
	case SHORT:
		return 1;
		break;
	case INT:
		return 2;
		break;
	case DOUBLE:
		return 3;
		break;
	}
}

char* GetConfigLineVal( char* TM_ConfigName )
{
	char* filename = getConfigfilename();
	FILE* f=NULL;
	char linebuf[256];                  /* 域墊  心  戈田永白央 */
	int linenum=0;                      /* 墊醒毛醒尹月 */
	char    realopenfilename[256];      /*    端卞open 允月白央奶夥  */
	char secondToken[256];
	char    hostname[128];


	if( f == NULL ){
		f=fopen( filename , "r" );          /* 白央奶夥及左□皿件 */
		if( f == NULL ){
			print( "Can't open %s\n", filename );
			return FALSE;
		}
	}

	/* 域墊勿勾  心  戈 */
	while( fgets( linebuf , sizeof( linebuf ), f ) ){
		char firstToken[256];       /*1    及  儂  */
		int i;                      /*夥□皿  醒*/
		int ret;                    /*伉正□件戊□玉*/

		linenum ++;

		deleteWhiteSpace(linebuf);          /* remove whitespace    */

		if( linebuf[0] == '#' )continue;        /* comment */
		if( linebuf[0] == '\n' )continue;       /* none    */

		chomp( linebuf );                    /* remove tail newline  */

		/* delim "=" 匹  賡(1)及玄□弁件毛  月*/
		ret = getStringFromIndexWithDelim( linebuf , "=",  1, firstToken,
			sizeof(firstToken) );
		if( ret == FALSE ){
			print( "Find error at %s in line %d. Ignore\n",
				filename , linenum);
			continue;
		}
		if (strcmp(firstToken,TM_ConfigName) != 0) continue;
		/* readconf 及扔奶術匹夥□皿 */
		for( i = 0 ; i < arraysizeof( readconf ) ; i ++ ){
			if( strcmp( readconf[i].name ,firstToken ) == 0 ){
				/* match */
				/* delim "=" 匹2    及玄□弁件毛  月*/
				ret = getStringFromIndexWithDelim( linebuf , "=" , 2
					, secondToken ,
					sizeof(secondToken) );

				/* NULL  儂井升丹井毛譬屯月 */
				if( ret == FALSE ){
					print( "Find error at %s in line %d. Ignore",
						filename , linenum);
					break;
				}
				return secondToken;
				break;
			}
		}
		break;
	}
	fclose( f );
	lastConfig();
	return NULL;
}

int getCopymapstartingID( void )
{
	return config.mapstart;
}
#endif
#ifdef _ROOKIE_ITEM
unsigned int getRookieItem(int index)
{
	if (config.rookieitem[index]>0) return config.rookieitem[index];
	return 0;
}
#endif
#ifdef _NO_TRANS_ITEM
unsigned int getNoTransItem(void)
{
	return config.notransitem;
}
#endif
#ifdef _MAX_MERGE_LEVEL
unsigned int getMaxMergeLevel(void)
{
	return config.maxmergelevel;
}
#endif
#ifdef _NO_ATTACK
int getAttTime(void)
{
	return config.atttime;
}
int getAttSafeTime(void)
{
	return config.attsafetime;
}
int getAttCnt(void)
{
	return config.attcnt;
}
int getLateTime(void)
{
	return config.latetime;
}
int getAttDmeTime(void)
{
	return config.attdmetime;
}
int getAttDmeCnt(void)
{
	return config.attdmecnt;
}
#endif
char* getNoAttIp(int num)
{
	if(num<0) num=0;
	else if(num>4) num=4;
	return config.noattip[num];
}
#ifdef _NO_FULLPLAYER_ATT
int getNoFullPlayer(void){
	return config.nofullplayer;
}
int getNoFull2Player(void){
	return config.nofull2player;
}
int getNoCdkeyPlayer(void){
	if(config.nocdkeyplayer<0 || config.nocdkeyplayer>2000)
		return 0;
	return config.nocdkeyplayer;
}
int getNoCdkeyMode(void){
	if(config.nocdkeymode<0 || config.nocdkeymode>2)
		return 0;
	return config.nocdkeymode;
}
int getNoCdkeyType(void){
	if(config.nocdkeytype<0 || config.nocdkeytype>2)
		return 0;
	return config.nocdkeytype;
}
int getNoFullTime(void){
	return config.nofulltime;
}
int getFengType(void){
	return config.fengtype;
}
int getNoFullEndPlayer(void){
	return config.nofullendplayer;
}
int getNoFullEndTime(void){
	return config.nofullendtime;
}
int getManRenNum(void){
	return config.manrennum;
}
#endif

int getLockType(void){
	if(config.locktype<=0) return 0;
	return config.locktype;
}

#ifdef _NEW_FUNC_DECRYPT
unsigned int getAllowerrornum2( void )
{
    return config.allowerrornum2;
}
#endif
#ifdef _MO_LOGIN_NO_KICK
int getLoginNoKick(void){
		if (config.loginnokick==1) return 1;
		return 0;
}
#endif

#ifdef _MO_ILLEGAL_NAME
char* getIllegalName( int index )
{
	char illegalname[256];
	if(getStringFromIndexWithDelim(config.illegalname,",", index+1, illegalname, sizeof(illegalname))==TRUE){
		return illegalname;
	}else{
		return "\0";
	}
}
#endif


#ifdef _NO_USE_PACKET_MAP
int getNoPacketMap( int index )
{
	char NoPacketMap[256];
	if(getStringFromIndexWithDelim(config.nousepacketmap,",", index+1, NoPacketMap, sizeof(NoPacketMap))==TRUE){
		return atoi(NoPacketMap);
	}else{
		return -1;
	}
}
#endif
#ifdef _NO_USE_MAGIC_MAP
int getNoMagicMap( int index )
{
	char NoMagicMap[256];
	if(getStringFromIndexWithDelim(config.nousemagicmap,",", index+1, NoMagicMap, sizeof(NoMagicMap))==TRUE){
		return atoi(NoMagicMap);
	}else{
		return -1;
	}
}
#endif


#ifdef _SOME_PETMAIL
int getPetMailFlg(void){
		if(config.petmailflg==1){
    		return config.petmailflg;
		}
		return 0;
    }
int getPetMailPetid(unsigned int index )
{
	char petid[256];
	if(getStringFromIndexWithDelim(config.somepetmail,",", index+1, petid, sizeof(petid))==TRUE){
		return atoi(petid);
	}else{
		return -1;
	}
}
#endif
#ifdef _CTRL_TRANS_DEVELOP
int getCtrlTrans(void){
		if(config.ctrltrans==1){
    		return config.ctrltrans;
		}
		return 0;
}
#endif

#ifdef	_PETMAIL_TIME
int getPetMailTime(void){
	if(config.petmailtime<=0) return 0;
	return config.petmailtime;
}
#endif
#ifdef _UP_BBPETPROB
int getUpBBProb(void){
	if(config.upbbprob==1) return 1;
	return 0;
}
#endif
