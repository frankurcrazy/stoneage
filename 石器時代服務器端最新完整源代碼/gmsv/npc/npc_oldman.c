#include "version.h"
#include "object.h"
#include "char_base.h"
#include "char.h"
#include "util.h"
#include "npcutil.h"
#include "npc_oldman.h"
#include "title.h"
#include "char_data.h"
#include "readmap.h"

/* hoge */

BOOL NPC_OldmanInit( int meindex )
{
	return FALSE;

}


/*
 *
 *  贏  ［
 *
 *  雲手卅酷儀反  仄井仃日木凶午五卞憊寞及  爛毛仄凶曰
 * 允月仇午分［
 * * by ringo
 */

void NPC_OldmanTalked( int meindex , int talkerindex , char *msg , int color )
{
    char message[1024];
    char *n = CHAR_getChar( talkerindex , CHAR_NAME );
    int title_change = 0;

    /* 反卅仄井仃凶蠱卞｝憤坌及ID毛筏盛今六月 */
    CHAR_setInt( talkerindex, CHAR_LASTTALKELDER ,
                 CHAR_getWorkInt( meindex, CHAR_WORKOLDMANID ) );

    /*

      if( title_change == 0 && strcmp( n , "蘋果" ) == 0 ){
        
        if( NPC_Util_HaveTitle( talkerindex , 3 ) == 0 ){
            char *ts;
            NPC_Util_AddOneTitle( talkerindex , 3 );
            ts = TITLE_makeTitleStatusString( talkerindex , 3 );
            snprintf( message , sizeof(message),
                  "那是個不錯的名字, 就叫%s吧！",
                  ts );
            title_change = 1;
        }
    }
    */
{
	int		addcnt,delcnt;
	title_change = TITLE_TitleCheck_Nomsg( talkerindex, 0, &addcnt, &delcnt);
	
    if( !title_change){
        snprintf( message, sizeof( message ) ,
              "來的好%s在給你稱號時"
              "不是還沒來嗎？" , n );
	    CHAR_talkToCli( talkerindex , meindex , message , CHAR_COLORWHITE );
    }
    else {
    	#define		NPC_OLDMAN_TITLE_UNIT1		"TSU"
    	#define		NPC_OLDMAN_TITLE_UNIT2		"KO"
    	
        snprintf( message, sizeof( message ) ,"來的好%s",n );
    	CHAR_talkToCli( talkerindex , meindex , message , CHAR_COLORWHITE );
		if( delcnt > 0 && addcnt > 0 ) {
	        snprintf( message, sizeof( message ) ,
	    			"你喪失了%d%s 稱號的資格。"
	    			"不是得到了%d%s 的稱號資格嗎？"
	    			, delcnt,
	    			delcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2,
	    			addcnt,
	    			addcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2
	    			);
	    	CHAR_talkToCli( talkerindex , meindex , message , CHAR_COLORWHITE );
		}
		else if( delcnt > 0 ) {
	        snprintf( message, sizeof( message ) ,
	    			"你已喪失得到%d%s稱號的資格。", delcnt,
	    			delcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2);
	    	CHAR_talkToCli( talkerindex , meindex , message , CHAR_COLORWHITE );
		}
		else if( addcnt > 0 ) {
	        snprintf( message, sizeof( message ) ,
	    			"給你%d%s的稱號吧！", addcnt, // CoolFish: d%s -> %d%s 2001/4/18
	    			addcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2);
	    	CHAR_talkToCli( talkerindex , meindex , message , CHAR_COLORWHITE );
		}
	    if( delcnt > 0 ) {
	        snprintf( message, sizeof( message), 
	                    "失去%d%s 稱號！", delcnt,
	    				delcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2);
	        CHAR_talkToCli( talkerindex, -1, message,  CHAR_COLORYELLOW);
	    }
	    if( addcnt > 0 ) {
	        snprintf( message, sizeof( message), 
	                    "獲得%d%s 稱號！", addcnt,
	    				addcnt < 10 ?  NPC_OLDMAN_TITLE_UNIT1:NPC_OLDMAN_TITLE_UNIT2);
	        CHAR_talkToCli( talkerindex, -1, message,  CHAR_COLORYELLOW);
	    }
    }
}
    if( title_change ) CHAR_sendStatusString( talkerindex , "T" );
    
}
