#include "version.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "object.h"
#include "char_base.h"
#include "char.h"
#include "util.h"
#include "npcutil.h"
#include "item.h"
#include "readmap.h"
#include "npc_healer.h"

#define RANGE 2
void NPC_HealerSpeak( int index, int talker);
BOOL NPC_MoneyCheck(int meindex,int talker);
int NPC_CostCheck(int talker);
void NPC_CharCheckPoint(int meindex,int talker);
int NPC_WorkInput(int meindex,int talker);


/**********************************
賡渝祭
************************************/
BOOL NPC_HealerInit( int meindex )
{
	//正奶皿毛甲□仿□卞澀爛
    CHAR_setInt( meindex , CHAR_WHICHTYPE , CHAR_TYPEHEALER );
    //  猾匹五卅中    邰卅中井手  
    CHAR_setFlg( meindex , CHAR_ISATTACKED , 0 );
    //曉卞曇木卅中
//    CHAR_setFlg( meindex , CHAR_ISOVERED , 0 );

	return TRUE;

}




/*-------------------------------------------
 *
 *   今木｝HP,MP毛蟈釩卞允月
 *
 --------------------------------------------*/
void NPC_HealerTalked( int meindex , int talker , char *msg ,int color )
{

    char*   npcarg;
    char    token[32];
	int msgNo;


	npcarg = CHAR_getChar(meindex,CHAR_NPCARGUMENT);

    getStringFromIndexWithDelim( npcarg, "|", 1, token,sizeof( token));
    msgNo  = atoi( token );

    /*---皿伊奶乩□卞覆仄化分仃  殺允月---*/
    if( CHAR_getInt( talker , CHAR_WHICHTYPE ) != CHAR_TYPEPLAYER )	return;

	/*---  區動  井＂  區反1引凶反｝仄氏匹中月井＂---*/
	/* ㄠ弘伉永玉動  及心 */
	if( NPC_Util_CharDistance( talker, meindex ) > 2) return;

	if( (CHAR_getWorkInt( talker, CHAR_WORKPARTYMODE) == 0)
	|| (CHAR_getWorkInt( talker, CHAR_WORKPARTYMODE) == 2) )
	{
		/*--莢汊今六引仄斤丹--*/
		NPC_HealerAllHeal( talker);
	    if(msgNo == 1) {
		    CHAR_talkToCli( talker, meindex,
			    "已經全部迴復。請在下次的比賽中加油唷！",CHAR_COLORWHITE);

		}else if(msgNo == 2) {
		    CHAR_talkToCli( talker, meindex,
		    	"由於你很誠實，讓我幫你迴復吧！",CHAR_COLORWHITE);
		}

	}else{
		int i = 0;
		int otherindex;

		for( i=0 ; i < getPartyNum(talker  ) ; i++)
		{
			otherindex = CHAR_getWorkInt( talker, CHAR_WORKPARTYINDEX1 + i);
			if(otherindex != -1){

				NPC_HealerAllHeal( otherindex);
				if(msgNo == 1) {
				    CHAR_talkToCli( otherindex, meindex,
				    	"已經全部迴復。請在下次的比賽中加油唷！",CHAR_COLORWHITE);

				}else if(msgNo == 2) {
					CHAR_talkToCli( otherindex, meindex, 
						"由於你很誠實，讓我幫你迴復吧！",CHAR_COLORWHITE);
				}
			}
		}
	}
}


/*----------------------*/
/* 莢汊 */
/*-----------------------*/
void NPC_HealerAllHeal( int talker )
{
	int i;
	int petindex;
	char petsend[3];	
	char msgbuf[5];
	
    CHAR_setInt( talker , CHAR_HP ,CHAR_getWorkInt( talker, CHAR_WORKMAXHP ) );
    CHAR_setInt( talker , CHAR_MP ,CHAR_getWorkInt( talker, CHAR_WORKMAXMP ) );



	for(i = 0 ; i < CHAR_MAXPETHAVE; i ++) {
		petindex = CHAR_getCharPet( talker, i);

		if( petindex == -1  )  continue;

		/*  平乓仿及    民尼永弁    */
		if( !CHAR_CHECKINDEX( talker ) )  continue;

		/* 矢永玄及index民尼永弁毛允月 */
		if( CHAR_CHECKINDEX( petindex) == FALSE ) continue;

		/*--莢汊--*/
		CHAR_setFlg( petindex, CHAR_ISDIE, 0);
		CHAR_setInt( petindex , CHAR_HP ,CHAR_getWorkInt( petindex, CHAR_WORKMAXHP ) );
		CHAR_setInt( petindex , CHAR_MP ,CHAR_getWorkInt( petindex, CHAR_WORKMAXMP ) );

		/*--由仿丟□正譬幫--*/
		CHAR_complianceParameter( petindex );
		sprintf( petsend, "K%d", i );
		CHAR_sendStatusString( talker , petsend );
	}
	
	/*---醮棉互中木壬醮棉卞手霜耨--*/
	if(CHAR_getWorkInt( talker, CHAR_WORKPARTYMODE) != CHAR_PARTY_NONE )
	{
		int	topartyarray = -1;
		int	oyaindex = CHAR_getWorkInt( talker	, CHAR_WORKPARTYINDEX1);
	
		if( CHAR_CHECKINDEX( oyaindex )) {
			int	i;
	
			/* 憤坌午慫仄凶支勾及醮棉及    及樺赭毛潸   */
			for( i = 0; i < getPartyNum(oyaindex  ); i ++ ) {
				int workindex = CHAR_getWorkInt( oyaindex, CHAR_WORKPARTYINDEX1 + i);
				if( CHAR_CHECKINDEX( workindex) ) {
					if( workindex == talker ) {
						topartyarray = i;
						break;
					}
				}
			}
			
			for( i = 0; i < getPartyNum(talker  ); i ++ ) {
				int otherindex = CHAR_getPartyIndex( talker, i);
				/* 醮棉由仿丟□正毛霜月 */
				if( CHAR_CHECKINDEX( otherindex) ) {
					snprintf( msgbuf, sizeof( msgbuf), "N%d", topartyarray);
					if( otherindex != talker) {
						CHAR_sendStatusString( otherindex, msgbuf);
					}
				}
			}
		}
	}

	/*--由仿丟□正霜曰--*/
	CHAR_send_P_StatusString( talker, CHAR_P_STRING_HP);
	CHAR_send_P_StatusString( talker, CHAR_P_STRING_MP);

}

