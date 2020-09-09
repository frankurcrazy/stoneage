#include "version.h"
#include <string.h>
#include "char.h"
#include "object.h"
#include "char_base.h"
#include "npcutil.h"
#include "lssproto_serv.h"
#include "npc_airplane.h"
#include "handletime.h"

/* 
 * 加美航空 (Made from Bus)
 */
#ifdef _NEW_ITEM_
extern int CheckCharMaxItem(int charindex);
#endif
enum {
	NPC_WORK_ROUTETOX = CHAR_NPCWORKINT1,		/* 升仇尺＂  甄   */
	NPC_WORK_ROUTETOY = CHAR_NPCWORKINT2,		/* 升仇尺＂  甄   */
	NPC_WORK_ROUTEPOINT = CHAR_NPCWORKINT3,		/* 漆窒    井 */
	NPC_WORK_ROUNDTRIP = CHAR_NPCWORKINT4,		/* 墊五井窖曰井  ㄟ“墊五 ㄠ“窖曰  */
	NPC_WORK_MODE = CHAR_NPCWORKINT5,
	NPC_WORK_CURRENTROUTE = CHAR_NPCWORKINT6, 
	NPC_WORK_ROUTEMAX = CHAR_NPCWORKINT7,
	NPC_WORK_WAITTIME = CHAR_NPCWORKINT8,
	NPC_WORK_CURRENTTIME = CHAR_NPCWORKINT9,
	NPC_WORK_SEFLG = CHAR_NPCWORKINT10,
	NPC_WORK_ONEWAYFLG = CHAR_NPCWORKINT11,
	NPC_WORK_RUNWAVE = CHAR_NPCWORKINT13,
};

/* 蛐  丟永本□斥及enum */
enum {
	NPC_AIR_MSG_GETTINGON,
	NPC_AIR_MSG_NOTPARTY,
	NPC_AIR_MSG_OVERPARTY,
	NPC_AIR_MSG_DENIEDITEM,
	NPC_AIR_MSG_ALLOWITEM,
	NPC_AIR_MSG_LEVEL,
	NPC_AIR_MSG_GOLD,
	NPC_AIR_MSG_EVENT,
	NPC_AIR_MSG_START,
	NPC_AIR_MSG_END,
};
typedef struct {
	char	option[32];
	char	defaultmsg[128];
}NPC_AIR_MSG;
NPC_AIR_MSG		airmsg[] = {
	{ "msg_gettingon",	"PAON！（你無法於中途加入我們唷！）"},
	{ "msg_notparty",	"PAPAON！！無法以團隊加入唷！"},
	{ "msg_overparty",	"PAON！！人數已滿。"},
	{ "msg_denieditem",		"PAPAON！！我可不要這個道具！"},
	{ "msg_allowitem",		"哇喔~(想要那個道具啊!)"},
	{ "msg_level",		"PAPAON！！你的等級還不夠唷！"},
	{ "msg_stone",		"PAPAON！！金錢不足唷！"},
	{ "msg_event",		"PAON！！你無法加入唷！"},
	{ "msg_start",		"哇喔~(齣發進行)"},
	{ "msg_end",		"哇喔~(到羅)"}
};

static int NPC_AirSetPoint( int meindex, char *argstr);
static void NPC_AirSetDestPoint( int meindex, char *argstr);
static BOOL NPC_AirCheckDeniedItem( int meindex, int charaindex, char *argstr);
static BOOL NPC_AirCheckLevel( int meindex, int charaindex, char *argstr);
static int NPC_AirCheckStone( int meindex, int charaindex, char *argstr);
static void NPC_AirSendMsg( int meindex, int talkerindex, int tablenum);
static int NPC_AirGetRoutePointNum( int meindex, char *argstr );
static void NPC_Air_walk( int meindex);

#define		NPC_AIR_LOOPTIME		100
#define		NPC_AIR_WAITTIME_DEFAULT	180
#define		NPC_AIR_WAITINGMODE_WAITTIME	5000

/*********************************
* 賡渝質
*********************************/
BOOL NPC_AirInit( int meindex )
{
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	int	i;
	char	buf[256],buf1[256];
	int	routenum;
	int	waittime;
	int	seflg;
	int	onewayflg;
	
	NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));
	
	/* 卅仃木壬中仃卅中婁醒及民尼永弁 */
	routenum = NPC_Util_GetNumFromStrWithDelim( argstr, "routenum");
	if( routenum == -1 ) {
		print( "npcair:nothing routenum \n");
		return FALSE;
	}
	CHAR_setWorkInt( meindex, NPC_WORK_ROUTEMAX, routenum);
	
	for( i = 1; i <= routenum; i ++ ) {
		char routetostring[64];
		snprintf( routetostring, sizeof( routetostring), "routeto%d", i);
		if( NPC_Util_GetStrFromStrWithDelim( argstr, routetostring,buf, sizeof(buf))
			== NULL ) 
		{
			print( "npcair:nothing route to \n");
			return FALSE;
		}
	}
	//ANDY_ADD	NPC_WORK_RUNWAVE
	if( NPC_Util_GetStrFromStrWithDelim( argstr, "WAVE",buf1, sizeof(buf1)) == NULL )	{
		CHAR_setWorkInt( meindex, NPC_WORK_RUNWAVE, 77);
	}else	{
		CHAR_setWorkInt( meindex, NPC_WORK_RUNWAVE, atoi( buf1) );
	}

	waittime = NPC_Util_GetNumFromStrWithDelim( argstr, "waittime");
	if( waittime == -1 ) waittime = NPC_AIR_WAITTIME_DEFAULT;
	CHAR_setWorkInt( meindex, NPC_WORK_WAITTIME, waittime);
	seflg = NPC_Util_GetNumFromStrWithDelim( argstr, "seflg");
	if( seflg == -1 ) seflg = TRUE;
	CHAR_setWorkInt( meindex, NPC_WORK_SEFLG, seflg);
	
	onewayflg = NPC_Util_GetNumFromStrWithDelim( argstr, "oneway");
	if( onewayflg == -1 ) onewayflg = FALSE;	// default
	CHAR_setWorkInt( meindex, NPC_WORK_ONEWAYFLG, onewayflg);
	
	CHAR_setInt( meindex , CHAR_WHICHTYPE , CHAR_TYPEBUS );
	
	CHAR_setWorkInt( meindex, NPC_WORK_MODE, 0);
	CHAR_setWorkInt( meindex, NPC_WORK_ROUTEPOINT, 2);
	CHAR_setWorkInt( meindex, NPC_WORK_ROUNDTRIP, 0);
	CHAR_setWorkInt( meindex, NPC_WORK_CURRENTROUTE, 0);
			
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, 
		NPC_AIR_WAITINGMODE_WAITTIME);
    
    /* 蜇箕及凜棉毛本永玄 */
    CHAR_setWorkInt( meindex, NPC_WORK_CURRENTTIME, NowTime.tv_sec);

    for( i = 0; i < getPartyNum(meindex  ); i ++) {
    	CHAR_setWorkInt( meindex, CHAR_WORKPARTYINDEX1 + i, -1);
    }
	
	/* 夥□玄瑁爛允月 */
{
	int rev;
	int r = CHAR_getWorkInt( meindex, NPC_WORK_ROUTEMAX);
	CHAR_setWorkInt( meindex, NPC_WORK_CURRENTROUTE, RAND( 1, r));
	//print( "route:%d\n",CHAR_getWorkInt( meindex, NPC_WORK_CURRENTROUTE));

	/*   欠旦正□玄 */
	rev = NPC_Util_GetNumFromStrWithDelim( argstr, "reverse");
	if( rev == 1 ) {
		int num = NPC_AirGetRoutePointNum( meindex, argstr);
		if( num <= 0 ) {
			print( "npcairplane:真奇怪！\n");
			return FALSE;
		}
		CHAR_setWorkInt( meindex, NPC_WORK_ROUTEPOINT, num-1);
		CHAR_setWorkInt( meindex, NPC_WORK_ROUNDTRIP, 1);
	}
	/* 夥□玄毛本永玄允月 */
	NPC_AirSetPoint( meindex, argstr);
	/* 墊五燮毛  憎允月 */
	NPC_AirSetDestPoint( meindex, argstr);
}

    return TRUE;
}


/*********************************
*   仄井仃日木凶凜及質
*********************************/
void NPC_AirTalked( int meindex , int talkerindex , char *szMes ,
                     int color )
{
    int i;
    int	partyflg = FALSE;
	int npc_wave = CHAR_getWorkInt( meindex, NPC_WORK_RUNWAVE);
	
    /* 皿伊奶乩□卞覆仄化分仃  殺允月 */
    if( CHAR_getInt( talkerindex , CHAR_WHICHTYPE ) != CHAR_TYPEPLAYER ) {
    	return;
    }
    /* 憤坌及由□  奴  曇菸  井升丹井譬屯月 */
    for( i = 0; i < getPartyNum(meindex  ); i ++ ) {
	int index = CHAR_getWorkInt( meindex, CHAR_WORKPARTYINDEX1+i);
	if( CHAR_CHECKINDEX(index)){
		if( index == talkerindex) {
			partyflg = TRUE;
		}
	}
    }
	if( !partyflg ) {
		//NPC_AirCheckJoinParty( meindex, talkerindex, TRUE);
	}
	else {
		if( CHAR_getWorkInt( meindex, NPC_WORK_MODE) == 0 ) {
			int i;
	//		#define NPC_AIR_DEBUGROUTINTG	"routingtable:"
			if( strstr( szMes, "齣發" )  ||
				strstr( szMes, "齣發" )  ||
				strstr( szMes, "Go" )  ||
				strstr( szMes, "go" ))
			{
				CHAR_setWorkInt( meindex, NPC_WORK_MODE,1);
				
				/* 夥□皿楮醒及裟請仄毛洶仁簧蘸卞允月 */
	 			CHAR_setInt( meindex, CHAR_LOOPINTERVAL, NPC_AIR_LOOPTIME);
				
				/* SE   日允  穴件乒旦及陲太   */
				if( CHAR_getWorkInt( meindex, NPC_WORK_SEFLG )) {
					//andy_reEdit	NPC_WORK_RUNWAVE
					CHAR_sendSEoArroundCharacter( 
									CHAR_getInt( meindex, CHAR_FLOOR),
									CHAR_getInt( meindex, CHAR_X),
									CHAR_getInt( meindex, CHAR_Y),
									npc_wave,
									TRUE);
				}
				/* 請  允月凜及丟永本□斥*/
				for( i = 1; i < getPartyNum(meindex  ); i ++ ) {
					int partyindex = CHAR_getWorkInt( meindex, CHAR_WORKPARTYINDEX1+i);
					if( CHAR_CHECKINDEX( partyindex)) {
						NPC_AirSendMsg( meindex, partyindex, NPC_AIR_MSG_START);
					}
				}
			}
		}
	}
}
/**************************************
 * 夥□皿楮醒
 **************************************/
void NPC_AirLoop( int meindex)
{
	int	i;
	int npc_wave = CHAR_getWorkInt( meindex, NPC_WORK_RUNWAVE);
	switch( CHAR_getWorkInt( meindex, NPC_WORK_MODE )) {
	  case 0:
	    /* 謹切乒□玉及凜］凜棉毛民尼永弁允月 */
		/* 凜棉互煩勻凶及匹］請  允月 */
		if( CHAR_getWorkInt( meindex, NPC_WORK_CURRENTTIME) 
			+ CHAR_getWorkInt( meindex, NPC_WORK_WAITTIME) 
			< NowTime.tv_sec)
		{
			/* SE   日允  穴件乒旦及陲太   */
			if( CHAR_getWorkInt( meindex, NPC_WORK_SEFLG )) {
				//ANDY_reEdit
				CHAR_sendSEoArroundCharacter( 
								CHAR_getInt( meindex, CHAR_FLOOR),
								CHAR_getInt( meindex, CHAR_X),
								CHAR_getInt( meindex, CHAR_Y),
								npc_wave,
								TRUE);
			}
			/* 請  允月凜及丟永本□斥*/
			for( i = 1; i < getPartyNum(meindex  ); i ++ ) {
				int partyindex = CHAR_getWorkInt( meindex, CHAR_WORKPARTYINDEX1+i);
				if( CHAR_CHECKINDEX( partyindex)) {
					NPC_AirSendMsg( meindex, partyindex, NPC_AIR_MSG_START);
				}
			}
			
			CHAR_setWorkInt( meindex, NPC_WORK_MODE,1);
			/* 夥□皿楮醒及裟請仄毛洶仁簧蘸卞允月 */
			CHAR_setInt( meindex, CHAR_LOOPINTERVAL, NPC_AIR_LOOPTIME);
		}
		return;
	  case 1:
	  	/* 洶仁 */
	  	NPC_Air_walk( meindex);
	  case 2:
		/* 鞅引勻化中月乒□玉 */
		/* 凜棉互煩勻凶及匹］請  允月 */
		if( CHAR_getWorkInt( meindex, NPC_WORK_CURRENTTIME) 
			+ (CHAR_getWorkInt( meindex, NPC_WORK_WAITTIME) /3)
			< NowTime.tv_sec)
		{
			CHAR_setWorkInt( meindex, NPC_WORK_MODE,1);
			/* 夥□皿楮醒及裟請仄毛洶仁簧蘸卞允月 */
			CHAR_setInt( meindex, CHAR_LOOPINTERVAL, NPC_AIR_LOOPTIME);
		
		}
		return;
	  case 3:
		/* 讒邋仄化手］弁仿奶失件玄及  樟謹切及啃卞］
		 * 劑仄仇仇匹它尼奶玄毛中木化支月
		 */
		if( CHAR_getWorkInt( meindex, NPC_WORK_CURRENTTIME) + 3	< NowTime.tv_sec){
			char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
			NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));
			CHAR_setInt( meindex, CHAR_LOOPINTERVAL, NPC_AIR_WAITINGMODE_WAITTIME);
			{
				int r = CHAR_getWorkInt( meindex, NPC_WORK_ROUTEMAX);
				CHAR_setWorkInt( meindex, NPC_WORK_CURRENTROUTE, RAND( 1, r));
			}
			CHAR_setWorkInt( meindex, NPC_WORK_ROUNDTRIP, 
				CHAR_getWorkInt( meindex, NPC_WORK_ROUNDTRIP)^1);
			if( CHAR_getWorkInt( meindex, NPC_WORK_ROUNDTRIP) == 1)  {
				int num = NPC_AirGetRoutePointNum( meindex, argstr);
				CHAR_setWorkInt( meindex, NPC_WORK_ROUTEPOINT, num-1);
			}else {
				CHAR_setWorkInt( meindex, NPC_WORK_ROUTEPOINT, 
					CHAR_getWorkInt( meindex, NPC_WORK_ROUTEPOINT) +1);
			}
			NPC_AirSetPoint( meindex, argstr);
			NPC_AirSetDestPoint( meindex, argstr);
			CHAR_DischargeParty( meindex, 0);
		    CHAR_setWorkInt( meindex, NPC_WORK_CURRENTTIME, NowTime.tv_sec);
			if ((CHAR_getWorkInt(meindex, NPC_WORK_ONEWAYFLG) == 1) &&
			    (CHAR_getWorkInt(meindex, NPC_WORK_ROUNDTRIP) == 1) ){
			  CHAR_setInt( meindex, CHAR_LOOPINTERVAL, NPC_AIR_LOOPTIME);
			  CHAR_setWorkInt( meindex, NPC_WORK_MODE, 1);
			} else
			  CHAR_setWorkInt( meindex, NPC_WORK_MODE, 0);
		}
		return;
	  default:
	    break;
	}
}
/**************************************
 * 洶仁［
 **************************************/
static void NPC_Air_walk( int meindex)
{
	POINT	start, end;
	int dir;
	int ret;
	int i;
	int npc_wave = CHAR_getWorkInt( meindex, NPC_WORK_RUNWAVE );

	/* 洶仁楮溢 */
	/* 讒邋仄凶凜及質   */
	start.x = CHAR_getInt( meindex, CHAR_X);
	start.y = CHAR_getInt( meindex, CHAR_Y);
	end.x = CHAR_getWorkInt( meindex, NPC_WORK_ROUTETOX);
	end.y = CHAR_getWorkInt( meindex, NPC_WORK_ROUTETOY);

	/* 讒邋仄凶及匹戚及禾奶件玄卞 */
	if( start.x == end.x && start.y == end.y ) {
		int add = 1;
		char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];

		NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));

		if( CHAR_getWorkInt( meindex, NPC_WORK_ROUNDTRIP ) == 1 ) {
			add *= -1;
		}
		CHAR_setWorkInt( meindex, NPC_WORK_ROUTEPOINT, 
			CHAR_getWorkInt( meindex, NPC_WORK_ROUTEPOINT) +add);
		if( NPC_AirSetPoint( meindex, argstr) == FALSE ) {
			/*     卞讒邋*/
			/* 謹切乒□玉卞允月 */
			CHAR_setWorkInt( meindex, NPC_WORK_MODE,3);
			
			/* SE   日允  穴件乒旦及陲太   */
			if( CHAR_getWorkInt( meindex, NPC_WORK_SEFLG )) {
				//ANDY_reEdit
				CHAR_sendSEoArroundCharacter( 
					CHAR_getInt( meindex, CHAR_FLOOR),
					CHAR_getInt( meindex, CHAR_X),
					CHAR_getInt( meindex, CHAR_Y),
					npc_wave,
					TRUE);
			}
			/* 邋中凶凜及丟永本□斥*/
			for( i = 1; i < getPartyNum(meindex  ); i ++ ) {
				int partyindex = CHAR_getWorkInt( meindex, CHAR_WORKPARTYINDEX1+i);
				if( CHAR_CHECKINDEX( partyindex)) {
					NPC_AirSendMsg( meindex, partyindex, NPC_AIR_MSG_END);
				}
			}
			/* 蜇箕及凜棉毛本永玄 */
			CHAR_setWorkInt( meindex, NPC_WORK_CURRENTTIME, NowTime.tv_sec);
			return;
		}
		else {
			return;
		}
	}
	/*-------------------------------------------------------*/
	/* 洶井六月質   */
	
	/*   輊毛菲戶月 */
	dir = NPC_Util_getDirFromTwoPoint( &start,&end );

	/* 漆中月樺赭及謹    由□  奴洶五匹銀丹   */
	end.x = CHAR_getInt( meindex, CHAR_X);
	end.y = CHAR_getInt( meindex, CHAR_Y);
	
	if( dir >= 0 && dir <= 7 ) {
		/* 洶仁 */
		ret = CHAR_walk( meindex, dir, 0);

		if( ret == CHAR_WALKSUCCESSED ) {
			/* 憤坌互褪卅日醮棉毛洶井六月 */
			int	i;
			int	mefl=CHAR_getInt( meindex, CHAR_FLOOR);
	//		print("airmax=%d",getPartyNum(meindex  ));
			for( i = 1; i < getPartyNum(meindex  ); i ++ ) {
				int toindex = CHAR_getWorkInt( meindex, i + CHAR_WORKPARTYINDEX1);
		//		print("\n i=%d toindex=%d check=%d",i,toindex,CHAR_CHECKINDEX(toindex));
				if( !CHAR_CHECKINDEX(toindex) )continue;
				int fl = CHAR_getInt( toindex, CHAR_FLOOR);
				int xx = CHAR_getInt( toindex, CHAR_X);
				int yy = CHAR_getInt( toindex, CHAR_Y);
		//		print("\n i=%d calc=%d",i,(abs(xx-end.x)+abs(yy-end.y)));
				if( CHAR_CHECKINDEX(toindex) &&
				    (mefl==fl) && (abs(xx-end.x)+abs(yy-end.y)<20) ) {
					int	parent_dir;
					/* 閡及匏  午］褪及洶五蟆及匏  井日  輊毛菲戶月 */
					/* 洶仁 */
					start.x = xx;
					start.y = yy;
					parent_dir = NPC_Util_getDirFromTwoPoint( &start,&end );
					/* 弘仿犯奴它旦左皿撲亦件洶五毛  蜇允月啃卞］
					 * 戚及閡反蟆及閡及  毛馨丹方丹卞允月
					 */
					end = start;
			//		print("\n i=%d parent_dir=%d",i,parent_dir);
					if( parent_dir != -1 ) {
						CHAR_walk( toindex, parent_dir, 0);
					}
				}
			}
		}
	}
}
/**************************************
 * 戚及樺赭毛本永玄允月
 **************************************/
static int NPC_AirSetPoint( int meindex, char *argstr)
{
	char	buf[4096];
	char	buf2[256];
	char	buf3[256];
	int floor,warpx,warpy;
	int ret;
	char routetostring[64];
	
	snprintf( routetostring, sizeof( routetostring), "routeto%d", 
				CHAR_getWorkInt( meindex, NPC_WORK_CURRENTROUTE));
	
	if( NPC_Util_GetStrFromStrWithDelim( argstr, routetostring,buf, sizeof(buf))
		== NULL ) 
	{
		print( "npcair:nothing route \n");
		return FALSE;
	}

	ret = getStringFromIndexWithDelim( buf, ";", 
		CHAR_getWorkInt( meindex, NPC_WORK_ROUTEPOINT),
		buf2, sizeof(buf2));
	if( ret == FALSE ) return FALSE;

	// Arminius: add floor
	
	ret = getStringFromIndexWithDelim( buf2, ",", 1,
		buf3, sizeof(buf3));
	if( ret == FALSE) return FALSE;
	floor = atoi(buf3);

	ret = getStringFromIndexWithDelim( buf2, ",", 2,
		buf3, sizeof(buf3));
	if( ret == FALSE) return FALSE;
	CHAR_setWorkInt( meindex, NPC_WORK_ROUTETOX, atoi( buf3));
	warpx = atoi(buf3);
	
	ret = getStringFromIndexWithDelim( buf2, ",", 3,
		buf3, sizeof(buf3));
	if( ret == FALSE) return FALSE;
	CHAR_setWorkInt( meindex, NPC_WORK_ROUTETOY, atoi( buf3));
	warpy = atoi(buf3);

	if (floor!=CHAR_getInt(meindex, CHAR_FLOOR)) {
		int	i;
		CHAR_warpToSpecificPoint(meindex, floor, warpx, warpy);

		for( i = 1; i < getPartyNum(meindex  ); i ++ ) {
			int toindex = CHAR_getWorkInt( meindex, i + CHAR_WORKPARTYINDEX1);
			if( CHAR_CHECKINDEX(toindex) ) {
				CHAR_warpToSpecificPoint(toindex, floor, warpx, warpy);
			}
		}
		CHAR_setWorkInt( meindex, NPC_WORK_ROUTETOX, warpx);
		CHAR_setWorkInt( meindex, NPC_WORK_ROUTETOY, warpy);
	}

	return TRUE;
}
/**************************************
 * route  寞井日］  蟆互丐勻凶日公木毛
 * 憊寞及午仇卞本永玄允月［
 **************************************/
static void NPC_AirSetDestPoint( int meindex, char *argstr)
{
	char 	buf[256];
	char	routename[256];

	snprintf( routename, sizeof( routename), "routename%d", 
				CHAR_getWorkInt( meindex, NPC_WORK_CURRENTROUTE));

	if( NPC_Util_GetStrFromStrWithDelim( argstr, routename, buf, sizeof( buf))
		!= NULL ) 
	{
		CHAR_setChar( meindex, CHAR_OWNTITLE, buf);
		CHAR_sendCToArroundCharacter( CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX));
	}
}
/**************************************
 * 隙爛今木凶失奶  丞毛  勻化中月井民尼永弁允月
 *   勻化中凶日分戶
 **************************************/
static BOOL NPC_AirCheckDeniedItem( int meindex, int charaindex, char *argstr)
{
	char	buf[1024];
	BOOL	found = TRUE;

	if( NPC_Util_GetStrFromStrWithDelim( argstr, "denieditem", buf, sizeof( buf))
		!= NULL ) 
	{
		int	i;
		int ret;
		for( i = 1; ; i ++) {
			int itemid;
			char buf2[64];
			int j;
			ret = getStringFromIndexWithDelim( buf, ",", i, buf2, sizeof(buf2));
			if( ret == FALSE ) break;
			itemid = atoi( buf2);
			for( j = 0; j < CheckCharMaxItem(charaindex); j ++) {
				int itemindex = CHAR_getItemIndex( charaindex, j);
				if( ITEM_CHECKINDEX( itemindex)) {
					if( ITEM_getInt( itemindex, ITEM_ID) == itemid) {
						found = FALSE;
						break;
					}
				}
			}
		}
	}
	return found;
}
/**************************************
 * 隙爛今木凶失奶  丞毛  勻化中月井民尼永弁允月
 *   勻化中卅中午分戶
 **************************************/
BOOL NPC_AirCheckAllowItem( int meindex, int charaindex, BOOL pickupmode)
{
	char	buf[1024];
	BOOL	found = TRUE;
	BOOL	pickup = FALSE;
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	
	NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));
	
	if( NPC_Util_GetStrFromStrWithDelim( argstr, "pickupitem", buf, sizeof( buf))
		!= NULL ) 
	{
		pickup = TRUE;
	}
	if( NPC_Util_GetStrFromStrWithDelim( argstr, "allowitem", buf, sizeof( buf))
		!= NULL ) 
	{
		int	i;
		int ret;
		for( i = 1; ; i ++) {
			int itemid;
			char buf2[64];
			int j;
			BOOL	getflg;
			ret = getStringFromIndexWithDelim( buf, ",", i, buf2, sizeof(buf2));
			if( ret == FALSE ) break;
			itemid = atoi( buf2);
			getflg = FALSE;
			for( j = 0; j < CheckCharMaxItem(charaindex); j ++) {
				int itemindex = CHAR_getItemIndex( charaindex, j);
				if( ITEM_CHECKINDEX( itemindex)) {
					if( ITEM_getInt( itemindex, ITEM_ID) == itemid) {
						/* 橢瘀互繚勻化中月井日］公及失奶  丞毛潸月 */
						if( pickupmode && pickup && !getflg) {
							CHAR_DelItem( charaindex, j);
							getflg = TRUE;
						}
						break;
					}
				}
			}
			if( j == CheckCharMaxItem(charaindex)) {
				found = FALSE;
				break;
			}
		}
	}
	return found;
}

/**************************************
 * 隙爛今木凶伊矛夥動曉井民尼永弁允月
 **************************************/
static BOOL NPC_AirCheckLevel( int meindex, int charaindex, char *argstr)
{
	int		level;
	
	/* 卅仃木壬中仃卅中婁醒及民尼永弁 */
	level = NPC_Util_GetNumFromStrWithDelim( argstr, "needlevel");
	if( level == -1 ) {
		return TRUE;
	}
	if( CHAR_getInt( charaindex, CHAR_LV) >= level ) return TRUE;
	
	return FALSE;
}

/**************************************
 * 豢嗯毛民尼永弁允月
 * -1 蟯   0動曉”    ］井勾  邰Stone
 **************************************/
static int NPC_AirCheckStone( int meindex, int charaindex, char *argstr)
{
	int		gold;
	
	/* 卅仃木壬中仃卅中婁醒及民尼永弁 */
	gold = NPC_Util_GetNumFromStrWithDelim( argstr, "needstone");
	if( gold == -1 ) {
		return 0;
	}
	if( CHAR_getInt( charaindex, CHAR_GOLD) >= gold ) return gold;
	
	return -1;
}
/**************************************
 * 丟永本□斥毛霜月
 * 婁醒及丟永本□斥互卅仃木壬犯白巧夥玄丟永本□斥毛霜月
 **************************************/
static void NPC_AirSendMsg( int meindex, int talkerindex, int tablenum)
{
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	char	buf[256];
	char	msg[256];
	if( tablenum < 0 || tablenum >= arraysizeof( airmsg)) return;
	
	NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));
	
	if( NPC_Util_GetStrFromStrWithDelim( argstr, airmsg[tablenum].option, buf, sizeof( buf))
		!= NULL ) 
	{
		strcpy( msg, buf);
	}
	else {
		snprintf( msg, sizeof(msg),airmsg[tablenum].defaultmsg);
	}
	CHAR_talkToCli( talkerindex, meindex, msg, CHAR_COLORYELLOW);
}
/**************************************
 * 夥□玄  □皮夥及禾奶件玄及醒毛潸  允月
 **************************************/
static int NPC_AirGetRoutePointNum( int meindex, char *argstr )
{
	int		i;
	char	buf[4096];
	char	buf2[256];
	int ret;
	char routetostring[64];
	
	snprintf( routetostring, sizeof( routetostring), "routeto%d", 
				CHAR_getWorkInt( meindex, NPC_WORK_CURRENTROUTE));
	
	if( NPC_Util_GetStrFromStrWithDelim( argstr, routetostring,buf, sizeof(buf))
		== NULL ) 
	{
		print( "npcair:nothing route \n");
		return -1;
	}
	for( i = 1; ; i ++ ) {
		ret = getStringFromIndexWithDelim( buf, ";", i, buf2, sizeof(buf2));
		if( ret == FALSE) break;
	}
	return( i -1);
}
BOOL NPC_AirCheckJoinParty( int meindex, int charaindex, BOOL msgflg)
{
    //int		fd;
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	int		ret;
	NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr));
	
	/* ㄠ弘伉永玉動  及心 */
	if( !NPC_Util_charIsInFrontOfChar( charaindex, meindex, 1 )) return FALSE; 
	/*     曇樂反蛐  允月 */
	if( CHAR_getWorkInt( meindex, NPC_WORK_MODE) != 0 ) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_GETTINGON);
		return FALSE;
	}
	/* 天□化不分勻凶日分戶 */
	if( CHAR_getWorkInt( charaindex, CHAR_WORKPARTYMODE ) != CHAR_PARTY_NONE) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_NOTPARTY);
		return FALSE;
	}
	/* 由□  奴及諦醒毛民尼永弁允月 */
	if( CHAR_getEmptyPartyArray( meindex) == -1 ) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_OVERPARTY);
		return FALSE;
	}
	/* 失奶  丞及民尼永弁毛允月(嗟鞅失奶  丞) */
	if( !NPC_AirCheckDeniedItem( meindex, charaindex, argstr)) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_DENIEDITEM);
		return FALSE;
	}
#ifdef _ITEM_CHECKWARES
	if( CHAR_CheckInItemForWares( charaindex, 0) == FALSE )	{
		CHAR_talkToCli( charaindex, -1, "無法攜帶貨物上機。", CHAR_COLORYELLOW);
		return FALSE;
	}
#endif

	/* 失奶  丞及民尼永弁毛允月(  邰失奶  丞) */
	if( !NPC_AirCheckAllowItem( meindex, charaindex, FALSE)) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_ALLOWITEM);
		return FALSE;
	}
	/* 伊矛夥及民尼永弁毛允月 */
	if( !NPC_AirCheckLevel( meindex, charaindex, argstr)) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_LEVEL);
		return FALSE;
	}
	/* 奶矛件玄  井民尼永弁允月 */
//	if( CHAR_getInt( charaindex, CHAR_NOWEVENT) != 0 ||
//		CHAR_getInt( charaindex, CHAR_NOWEVENT2) != 0 ||
//		CHAR_getInt( charaindex, CHAR_NOWEVENT3) != 0 )
//	{
//		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_EVENT);
//		return FALSE;
//	}
	/* 豢嗯及民尼永弁毛允月  雲嗯毛潸月及匹］  蔽民尼永弁卞允月仇午″   */
	ret = NPC_AirCheckStone( meindex, charaindex, argstr);
	if( ret == -1 ) {
		if( msgflg) NPC_AirSendMsg( meindex, charaindex, NPC_AIR_MSG_GOLD);
		return FALSE;
	}
	if( ret != 0 ) {
		char msgbuf[128];
		/* 豢嗯毛午月 */
		CHAR_setInt( charaindex, CHAR_GOLD, 
					CHAR_getInt( charaindex, CHAR_GOLD) - ret);
		/* 霜耨 */
		CHAR_send_P_StatusString( charaindex, CHAR_P_STRING_GOLD);
		snprintf( msgbuf, sizeof( msgbuf), "支付瞭%d Stone！", ret);
		CHAR_talkToCli( charaindex, -1, msgbuf, CHAR_COLORYELLOW);
	}
	/* 由□  奴卞  月 */
	//CHAR_JoinParty_Main( charaindex, meindex);
	
	//fd = getfdFromCharaIndex( charaindex );
	
	//lssproto_PR_send( fd, 1, 1);
	
	return TRUE;
}
