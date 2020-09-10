#include "version.h"
#include <time.h>
#include <string.h>
#include "char.h"
#include "object.h"
#include "char_base.h"
#include "npcutil.h"
#include "lssproto_serv.h"
#include "handletime.h"
#include "readmap.h"
#include "log.h"
#include "enemy.h"
#include "npc_eventaction.h"
#include "pet.h"
#include "battle.h"
#include "chatmagic.h"

#ifdef _NPC_MAGICCARD
#include "npc_magiccard.h"

void NPC_Magiccard_selectWindow(int meindex,int toindex,int num,int select);
int NPC_magiccard_checkplace( int meindex , int toindex , char *token );
void NPC_magiccard_gameinit( int meindex , int bkid );
void NPC_magiccard_selectcard( int meindex , int bkid );
void NPC_magiccard_checkselect( int meindex , int toindex ,int choise);
void NPC_magiccard_waitselect( int meindex , int bkid );
void NPC_magiccard_aiselect( int meindex , int bkid );
//void NPC_magiccard_showcard( int meindex , int bkid );
//void NPC_magiccard_summonpet(int meindex , int bkid , int charindex , int mode );
//void NPC_magiccard_fightcard( int meindex , int bkid , int playtotal);
//void NPC_magiccard_damage( int meindex , int bkid , int charindex , int player , int playtotal);
void NPC_magiccard_out( int meindex , int bkid , int player );
void NPC_magiccard_turnover( int meindex , int bkid	);
void NPC_magiccard_gameover( int meindex , int bkid );
void NPC_magiccard_resetbanker( int meindex , int bkid );
int NPC_magiccard_checkExist( int meindex , int bkid , int player );
//void NPC_magiccard_action( int meindex , int charindex , int bkid , int player );
void NPC_magiccard_selectback( int meindex , int toindex );
void NPC_magiccard_action2( int meindex , int charindex , int user , int card , int action );
void NPC_magiccard_checkdamage( int meindex , int bkid );
void NPC_magiccard_showdamage( int meindex , int charindex , int position , int damage );
void NPC_magiccard_specialcard( int meindex , int bkid );
int NPC_magiccard_sort( const void *card1, const void *card2 );

enum {
	NPC_WORK_BANKER = CHAR_NPCWORKINT1,		// 記錄跟哪一個莊傢玩
	NPC_WORK_GIVEGOLD = CHAR_NPCWORKINT2,   // 紀錄挑戰者是否是付保證金的
	//NPC_WORK_ABANDON = CHAR_NPCWORKINT2,	// 挑戰者是否放棄出牌
	//NPC_WORK_TURN = CHAR_NPCWORKINT3,		// 記錄迴閤數
	NPC_WORK_HAND = CHAR_NPCWORKINT4,		// 記錄挑戰者手上的牌
	NPC_WORK_SELECT = CHAR_NPCWORKINT5,		// 記錄挑戰者選擇出第幾張牌
	NPC_WORK_ACTION = CHAR_NPCWORKINT6,		// 記錄挑戰者選擇攻擊還是防禦
	NPC_WORK_HISTORY = CHAR_NPCWORKINT7,	// 記錄挑戰者出過的牌
	NPC_WORK_DAMAGE = CHAR_NPCWORKINT8,		// 記錄挑戰者受的傷害
	//NPC_WORK_LOCATION = CHAR_NPCWORKINT9,	// 記錄挑戰者的位置
	//NPC_WORK_ = CHAR_NPCWORKINT10,		// 記錄莊傢的index	
};

enum {	
	ATTACK=1,
	DEFENCE,
	MAGIC,
};

enum {
	START,
	RULES,
	INGAME,	
	SCORE,
	END,
};


#define LOOPTIME			100 // 0.1秒
#define SHOWCARDLOOPTIME	800//1000  //1秒  
#define FIGHTLOOPTIME		800//1000//2000 
#define TURNOVERTIME		1300//1500//4000
#define GAMEOVERTIME        4800//5000

#define MAXHP				50
#define MAXGUY				6
#define BANKERID            6

#define SHIFTBASE			1	//用來左移的基準值
//#define MAGIC_MOVE_SCREEN_XY			(18 << 16) | 10		// 熒幕要移動到的XY座標
//#define MAGIC_MOVE_SCREEN_XY			(14 << 16) | 13		// 熒幕要移動到的XY座標

struct BANKER banker[BANKERTOTAL];  

int  Bettotal[BANKERTOTAL];
int  Wintotal[BANKERTOTAL];
int  tickettotal[BANKERTOTAL];

//位置資料
typedef struct Posstruct
{
	int humanX;
	int humanY;
	int petX;
	int petY;	
	int npcX;
	int npcY;
	int direct;
}Position;
static Position Positiontable[]=
{
	{19,12,17,12,15,13,6},	//0 挑戰者
	{18,17,16,15,15,14,7},	//1 挑戰者
	{13,18,13,16,14,14,0},	//2 挑戰者
	{ 9,14,11,14,13,13,2},	//3 挑戰者
	{10, 9,12,11,13,12,3},	//4 挑戰者
	{15, 8,15,10,14,12,4},	//5 挑戰者
	{15,12,14,13,14,13,5},	//6 莊傢
	{24,18, 0, 0,0,0,6},	//7 死掉	
	
/*
	{23, 9,21, 9,6},	//0 挑戰者
	{22,14,20,12,7},	//1 挑戰者
	{17,15,17,13,0},	//2 挑戰者
	{13,11,15,11,2},	//3 挑戰者
	{14, 6,16, 8,3},	//4 挑戰者
	{19, 5,19, 7,4},	//5 挑戰者
	{18,18,18,10,5},	//6 莊傢
	{15,13, 0, 0,6},	//7 死掉
*/
};

typedef struct st_cardbox
{
	BOOL use;
	int cardindex;
}CardBoxType;
static CardBoxType Cardbox[BANKERTOTAL*7][30];

//魔法牌
typedef struct Cardstruct
{
    STRING64    name;
	int			petid;
	int			attack;
	int			defence;	
	int			effect;
    void*       functionPointer;   
}Cardfunction;
static Cardfunction Cardfunctiontable[]=
{
	{{"寵物牌1:	 翟貝裏恩    攻 13 防 1"}               ,2565 ,13 , 1 , 101437,NULL},
	{{"寵物牌2:	 尼修喀      攻 13 防 1"}               ,0    ,13 , 1 , 101962,NULL},
	{{"寵物牌3:	 菲奇亞      攻 13 防 1"}               ,2571 ,13 , 1 , 101616,NULL},
	{{"寵物牌4:	 美拉        攻 1 防 13"}               ,2563 , 1 ,13 , 101760,NULL},
	{{"寵物牌5:	 洛狄雷諾    攻 1 防 13"}               ,0    , 1 ,13 , 101946,NULL},
	{{"寵物牌6:	 伊亞歐萊    攻 1 防 13"}               ,0    , 1 ,13 , 101485,NULL},
	{{"寵物牌7:  凱恩        攻 8 防 8"}                ,0    , 8 , 8 , 101180,NULL},
	{{"寵物牌8:  佩露夏      攻 8 防 8"}                ,0    , 8 , 8 , 100872,NULL},
	{{"寵物牌9:	 雷諾夫      攻 8 防 7"}                ,0    , 8 , 7 , 101952,NULL},	
	{{"寵物牌10: 懷沃夫      攻 8 防 6"}                ,0    , 8 , 6 , 101875,NULL},
	{{"寵物牌11: 比斯吉      攻 7 防 7"}                ,0    , 7 , 7 , 101914,NULL},	
	{{"寵物牌12: 帖伊諾斯    攻 7 防 7"}                ,2456 , 7 , 7 , 101819,NULL},	
	{{"寵物牌13: 雷帝斯洛    攻 7 防 8"}                ,0    , 7 , 8 , 101501,NULL},	
	{{"寵物牌14: 安古力      攻 7 防 6"}                ,0    , 7 , 6 , 101922,NULL},	
	{{"寵物牌15: 拉佛洛斯    攻 6 防 6"}                ,0    , 6 , 6 , 101464,NULL},	
	{{"寵物牌16: 塔塔拉      攻 6 防 6"}                ,0    , 6 , 6 , 101928,NULL},		
	{{"寵物牌17: 菲斯瑪      攻 6 防 8"}                ,0    , 6 , 8 , 101446,NULL},	
	{{"寵物牌18: 阿伊薩      攻 6 防 7"}                ,0    , 6 , 7 , 100390,NULL},	//	
	{{"寵物牌19: 奇斯古德    攻 3 防 3"}                ,0    , 3 , 3 , 101954,NULL},	
	{{"寵物牌20: 坎普洛司    攻 3 防 3"}                ,0    , 3 , 3 , 101957,NULL},	
	{{"寵物牌21: 史比特      攻 3 防 3"}                ,0    , 3 , 3 , 101556,NULL},	
	{{"寵物牌22: 邦斯卡      攻 3 防 2"}                ,0    , 3 , 2 , 101933,NULL},	
	{{"寵物牌23: 可可恩      攻 2 防 3"}                ,2570 , 2 , 3 , 100898,NULL},	
	{{"寵物牌24: 巴特        攻 2 防 2"}                ,0    , 2 , 2 , 101870,NULL},	
	{{"寵物牌25: 艾恩剋      攻 2 防 2"}                ,0    , 2 , 2 , 101918,NULL},	
	{{"魔法牌1: 幻鏡術《將對方的攻擊反彈迴去》"}       ,2604 , 0 , 0 , 101652,NULL},
	{{"魔法牌2: 幻影術《不受到對方任何攻擊》"}		   ,2605 , 0 , 0 , 101695,NULL},
	{{"魔法牌3: 封印術《將對方暫停一迴閤》"}           ,2606 , 0 , 0 , 101120,NULL},
	{{"魔法牌4: 召靈術《迴復HP->滿血量50%》"}          ,2607 , 0 , 0 , 101828,NULL},
	{{"魔法牌5: 召雷術《隨機攻擊  攻 20》"}            ,2608 , 20 , 0 , 101628,NULL},	

};

BOOL NPC_Magiccard_Init( int meindex )
{
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	char buf[64];
	int j,k;

	memset( banker,0,sizeof(banker));
	for(j=0;j<BANKERTOTAL;j++){
		banker[j].state = -1;
		Bettotal[j]=0;
		Wintotal[j]=0;
		tickettotal[j]=0;
	}
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, LOOPTIME );
	
	for(j=0;j<14;j++){
		for(k=0;k<30;k++){
			Cardbox[j][k].use = 0;
			Cardbox[j][k].cardindex = k;
		}
	}

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL)	return FALSE;

	NPC_Util_GetStrFromStrWithDelim( argstr , "ID", buf, sizeof( buf));

	CHAR_setInt( meindex, CHAR_LV, atoi(buf));  // 莊傢的id紀錄在CHAR_LV
	print("\n ------------bankerid= %d ------------------- ",atoi(buf));
	return TRUE;
}

void NPC_Magiccard_Talked( int meindex , int talkerindex , char *szMes , int color )
{
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];

	if( CHAR_getInt( talkerindex , CHAR_WHICHTYPE ) != CHAR_TYPEPLAYER ){
    		return;
	}
	if(NPC_Util_isFaceToFace( meindex ,talkerindex , 2) == FALSE) {
		if(NPC_Util_isFaceToChara( talkerindex, meindex, 1) == FALSE) return;
	}

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return;
	}	
	CHAR_setWorkInt( talkerindex , CHAR_WORKSHOPRELEVANT,0);
	NPC_Magiccard_selectWindow( meindex , talkerindex, START , -1 );
}

void NPC_Magiccard_selectWindow(int meindex,int toindex,int num,int select)
{
	int fd;
	char	argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	int i,pagenum;
	int buttontype = 0, windowtype = 0, windowno = 0;
	char token[1024],buf2[256],buf1[256];

	windowtype = WINDOW_MESSAGETYPE_MESSAGE;
    fd = getfdFromCharaIndex( toindex );
    if( fd == -1 )  return;

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return;
	}

	switch(num) 
	{
	case START:  //一切的開始
		i = 1;
		strcpy( token, "\0");
		sprintf( buf2,"%s%d", "menu_msg0", i);
		while( NPC_Util_GetStrFromStrWithDelim( argstr, buf2, buf1, sizeof( buf1) ) != NULL )	{
			if( strstr( buf1, "NULL" ) == NULL )	{
				strcat( token , buf1);
				strcat( token, "\n");
			}else	{
				strcat( token, "\n");
			}
			i++;
			sprintf( buf2,"%s%d", "menu_msg0", i);
		}
		windowtype = WINDOW_MESSAGETYPE_SELECT;
		buttontype = WINDOW_BUTTONTYPE_NONE;
		windowno = CHAR_WINDOWTYPE_MAGIC_START;
		break;	
	case RULES:
		pagenum = CHAR_getWorkInt( toindex , CHAR_WORKSHOPRELEVANT);
		strcpy( token, "\0");
		if( select >= 0 ){
			sprintf( buf2,"%s%d", "page_num", select);
			CHAR_setWorkInt( toindex , CHAR_WORKSHOPRELEVANT, select+1);
		}else{
			sprintf( buf2,"%s%d", "page_num", pagenum );
			pagenum+=1;
			CHAR_setWorkInt( toindex , CHAR_WORKSHOPRELEVANT, pagenum);
		}

		if( NPC_Util_GetStrFromStrWithDelim( argstr, buf2, token, sizeof( token) ) == NULL )	{
			print("\n error: not found token:%s", token);
			CHAR_setWorkInt( toindex , CHAR_WORKSHOPRELEVANT,0);
			return;
		}

		sprintf( buf2,"%s%d", "page_num", CHAR_getWorkInt( toindex , CHAR_WORKSHOPRELEVANT));
		if( NPC_Util_GetStrFromStrWithDelim( argstr, buf2, buf1, sizeof( buf1) ) == NULL )	{		
			buttontype = WINDOW_BUTTONTYPE_OK;
			windowno = CHAR_WINDOWTYPE_MAGIC_NORMAL;
		}else	{
			buttontype = WINDOW_BUTTONTYPE_NEXT;
			windowno = CHAR_WINDOWTYPE_MAGIC_RULES;
		}
		break;
	case INGAME:
		//warp挑戰者到戰鬥位置上 開始玩牌
		if( NPC_magiccard_checkplace( meindex , toindex , token ) == TRUE ){ //檢查有沒有空位
			return; 
		}else{
			//不能參加
			buttontype = WINDOW_BUTTONTYPE_OK;
			windowno = CHAR_WINDOWTYPE_MAGIC_NORMAL;
		}
		break;
	case SCORE:
		{	
			int  G_num = CHAR_getInt( toindex, CHAR_GAMBLENUM );

			if( G_num < 0 ) G_num = 0;
			sprintf( token,"你的遊樂場積分為%d。", G_num );
			buttontype = WINDOW_BUTTONTYPE_OK;
			windowno = CHAR_WINDOWTYPE_MAGIC_NORMAL;
		}
		break;
	case END:
		if( NPC_Util_GetStrFromStrWithDelim( argstr, "end_msg", token, sizeof( token) ) == NULL ){
			print("\n read arg err");
		}
		buttontype = WINDOW_BUTTONTYPE_OK;
		windowno = CHAR_WINDOWTYPE_MAGIC_NORMAL;
		break;
	}

	lssproto_WN_send( fd, windowtype, buttontype, windowno, 
		CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX), token);
}

void NPC_Magiccard_WindowTalked( int meindex, int talkerindex, int seqno, int select, char *data)
{
	int pagenum,datanum;

	switch(seqno)
	{
	case CHAR_WINDOWTYPE_MAGIC_START:
		pagenum = atoi( data );
		if( pagenum == 4 ){				// 離開
			NPC_Magiccard_selectWindow( meindex, talkerindex, END , -1 );
		}else	{
			if( pagenum == 3 ){			// 個人積分
				NPC_Magiccard_selectWindow( meindex, talkerindex, SCORE , -1 );
			}else if( pagenum == 2 ){	// 參加遊戲				
				NPC_Magiccard_selectWindow( meindex, talkerindex, INGAME , -1 );
			}else{						// 遊戲規則
				NPC_Magiccard_selectWindow( meindex, talkerindex, RULES, 1 );
			}
		}
		break;
	case CHAR_WINDOWTYPE_MAGIC_RULES:
		NPC_Magiccard_selectWindow( meindex, talkerindex, RULES, -1 );
		break;
	case CHAR_WINDOWTYPE_MAGIC_NORMAL:
		break;
	case CHAR_WINDOWTYPE_MAGIC_SELECT:
		datanum = atoi(data);
		if( CHAR_getWorkInt( talkerindex , NPC_WORK_SELECT ) == -1 ) {	
			NPC_magiccard_checkselect( meindex , talkerindex ,datanum );
		}else{
			if( select == WINDOW_BUTTONTYPE_OK ){
				CHAR_setWorkInt( talkerindex , NPC_WORK_ACTION , MAGIC );	
			}else if( select == WINDOW_BUTTONTYPE_CANCEL ){
				CHAR_setWorkInt( talkerindex , NPC_WORK_SELECT , -1 );
				NPC_magiccard_selectback( meindex , talkerindex );
			}else{
				if(datanum == 2 )
					CHAR_setWorkInt( talkerindex , NPC_WORK_ACTION , ATTACK );
				else if(datanum == 4)
					CHAR_setWorkInt( talkerindex , NPC_WORK_ACTION , DEFENCE );
			}
		}
		break;
	}	
}

void NPC_Magiccard_Loop( int meindex )  //莊傢跑自己的LOOP
{
	int j,playertotal,bkid;
	char buf[256];

	if( !CHAR_CHECKINDEX( meindex) ) return;
	bkid = CHAR_getInt( meindex, CHAR_LV );
	
	playertotal = 0;
	for( j=0 ; j < MAXGUY ; j++){
		if( NPC_magiccard_checkExist( meindex , bkid , j ) != -1 )
			playertotal++;
	}
	if( playertotal == 0 ) NPC_magiccard_resetbanker( meindex , bkid );  //這個莊傢已經沒有挑戰者在了
	else banker[bkid].playertotal = playertotal ;

	switch( banker[bkid].state )  //由莊傢來控製流程
	{ 
	case 0: //等待挑戰者
		if( banker[bkid].waittime < NowTime.tv_sec ){		
			NPC_magiccard_gameinit( meindex , bkid);
		}else{
			if((long)banker[bkid].waittime - NowTime.tv_sec != banker[bkid].turntime ){
				banker[bkid].turntime = (long)banker[bkid].waittime - NowTime.tv_sec;
				if( banker[bkid].turntime < 6 ){
					sprintf( buf ,"遊戲將在〈 %d秒 〉後開始", banker[bkid].turntime );
					showString( meindex, buf , 0);
				}
			}
		}
		break;
	case 1: //要求出牌
		NPC_magiccard_selectcard( meindex , bkid);			
		break;
	case 2: //等待出牌
		if( (long)banker[bkid].turntime - NowTime.tv_sec != banker[bkid].waittime ){
			banker[bkid].waittime = (long)banker[bkid].turntime - NowTime.tv_sec;
			if(banker[bkid].waittime < 4 && banker[bkid].waittime >= 0 ){
				sprintf( buf ,"出牌時間剩下%d秒", banker[bkid].waittime );
				showString( meindex, buf , 0);
			}
		}
		NPC_magiccard_waitselect( meindex , bkid);
		break;
	case 3: //計算傷害和秀動畫
		NPC_magiccard_checkdamage( meindex,bkid);
		break;
	case 4: //特殊牌
		NPC_magiccard_specialcard( meindex , bkid);
		break;
	case 5: //迴閤結束
		NPC_magiccard_turnover( meindex , bkid);
		break;
	case 9: //比賽結束看輸贏
		NPC_magiccard_gameover( meindex , bkid);
		break;
	default:
		break;
	}
}

int NPC_magiccard_checkplace( int meindex , int toindex , char *token )
{
	int i,offsetx,offsety;
	unsigned int movescreenXY=0;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	char buf[64];
	OBJECT object;
	int bossindex,objindex;
	
	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return FALSE;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);
    
	if( CHAR_getWorkInt( toindex, CHAR_WORKPARTYMODE) != CHAR_PARTY_NONE )
	{
		strcpy(token,"組隊中不能參加!!!");
		return FALSE;
	}

	//判斷有沒有資格參賽
	if( CHAR_getInt( toindex , CHAR_GAMBLENUM) < 6 && CHAR_getInt( toindex , CHAR_GOLD) < 15000 ){
		strcpy(token,"您沒有足夠的錢付保證金和門票喔，很抱歉不能參加!!!");
		return FALSE;			
	}else if( CHAR_getInt( toindex , CHAR_GOLD) < 5000 ){
		strcpy(token,"您沒有足夠的石幣付門票喔，很抱歉不能參加!!!");
		return FALSE;			
	}

	i = CHAR_getInt( meindex, CHAR_LV );
	if( banker[i].state > 0 || banker[i].playertotal >= MAXGUY ){ //continue; //滿了或遊戲進行中
		strcpy(token,"比賽已經額滿了或是進行中，請等候下一場謝謝");
		return FALSE;	
	}

	if( banker[i].playertotal == 0 ){  //第一位挑戰者		
		banker[i].waittime = NowTime.tv_sec + 15 ; //30 
		banker[i].state = 0 ;		//進入等待loop
	}else
		banker[i].waittime = NowTime.tv_sec + 10 ;  //隻要有挑戰者進來就再加10秒
		
	sprintf( banker[i].cdkey[banker[i].playertotal] , "%s" , CHAR_getChar( toindex , CHAR_CDKEY ));
	sprintf( banker[i].name[banker[i].playertotal] , "%s" , CHAR_getChar( toindex , CHAR_NAME ));			

	if(CHAR_getInt( toindex , CHAR_GAMBLENUM) < 6){
		CHAR_setInt( toindex , CHAR_GOLD, CHAR_getInt( toindex , CHAR_GOLD)-15000 ); 
		CHAR_setWorkInt( toindex , NPC_WORK_GIVEGOLD , 1 );
		sprintf( buf,"已繳交門票5000Ｓ和保證金10000Ｓ" ); 
		CHAR_talkToCli( toindex , -1 , buf,  CHAR_COLORYELLOW);
	}else{
		CHAR_setInt( toindex , CHAR_GOLD, CHAR_getInt( toindex , CHAR_GOLD)-5000 ); 
		CHAR_setInt( toindex , CHAR_GAMBLENUM, CHAR_getInt( toindex , CHAR_GAMBLENUM) - 6 );		
		CHAR_setWorkInt( toindex , NPC_WORK_GIVEGOLD , 0 );
		sprintf( buf,"已繳交門票5000Ｓ" ); 
		CHAR_talkToCli( toindex , -1 , buf,  CHAR_COLORYELLOW);
	}

	Bettotal[i] += 6;
	tickettotal[i]++;
	
	CHAR_setInt( toindex , CHAR_DIR , Positiontable[banker[i].playertotal].direct );
	CHAR_setWorkInt( toindex , NPC_WORK_BANKER , i );
	//紀錄此項用來確認是否是中途離開	
	CHAR_setWorkInt(toindex, CHAR_WORK_TEMP_FLOOR, CHAR_getInt(meindex, CHAR_FLOOR));	

	//sprintf( buf ,"紀錄的地圖為%d", CHAR_getWorkInt(toindex, CHAR_WORK_TEMP_FLOOR ));
	//showString( meindex, buf , 0);

	CHAR_warpToSpecificPoint( toindex, CHAR_getInt( meindex, CHAR_FLOOR), 
		Positiontable[banker[i].playertotal].humanX + offsetx ,
		Positiontable[banker[i].playertotal].humanY + offsety );
	//移動該挑戰者的視角	
	movescreenXY = ((Positiontable[banker[i].playertotal].humanX + offsetx) << 16) | ( Positiontable[banker[i].playertotal].humanY + offsety)	;
	lssproto_MoveScreen_send(getfdFromCharaIndex(toindex), TRUE, movescreenXY);	
	banker[i].playertotal += 1;		//加入一個挑戰者

	//雷爾變身
	object = MAP_getTopObj(CHAR_getInt(meindex, CHAR_FLOOR), Positiontable[BANKERID].humanX + offsetx, Positiontable[BANKERID].humanY + offsety );
	if( object ){
		objindex = GET_OBJINDEX( object);
		bossindex = OBJECT_getIndex(objindex);
		if( banker[i].playertotal < 3 )
			CHAR_CHAT_DEBUG_metamo( bossindex , "101813" );
		else if( banker[i].playertotal < 5 )
			CHAR_CHAT_DEBUG_metamo( bossindex , "101814" );
		else
			CHAR_CHAT_DEBUG_metamo( bossindex , "101815" );
	}

	return TRUE;
}

void NPC_magiccard_gameinit( int meindex , int bkid )
{
	int  i,j=0,charindex,k;	
	unsigned int card;
	char buf[256];
	unsigned int movescreenXY=0;
	int offsetx,offsety;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	BOOL flag = FALSE;

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	banker[bkid].turn = 1;	
	banker[bkid].hand = 0;
	banker[bkid].history = 0;
	banker[bkid].turntime = NowTime.tv_sec + 20 ;
	banker[bkid].process = 0;	
	sprintf( buf,"第一迴閤開始 戰鬥" );
	showString( meindex, buf , 0);
	
	//莊傢的牌
	while(j<5){
		if( tickettotal[bkid] > 5000 && flag == FALSE ){
			i = rand()%100;
			if( i > 50 ) k = 25 + rand()%5;
			else if( i > 20 ) k = rand()%3;
			else k = 3 + rand()%3;					
			flag = TRUE;
		}else{
			k = rand()%(30-j);
			if( Cardbox[6+7*bkid][k].cardindex == 28 && flag == FALSE && rand()%100 > 50){	//降低召靈出現機率
				flag = TRUE;
				continue;
			}
		}
		Cardbox[6+7*bkid][k].use = 1;
		card = SHIFTBASE << Cardbox[6+7*bkid][k].cardindex ; 
		banker[bkid].hand |= card;
		qsort( &Cardbox[6+7*bkid] , 30 , sizeof(CardBoxType) , &NPC_magiccard_sort );
		j++;
	}
	flag = FALSE;
	for( i=0;i<MAXGUY;i++){
		//檢查挑戰者還在不在 
		charindex = NPC_magiccard_checkExist(meindex,bkid,i);
		if( charindex == -1 ) continue;
		
		banker[bkid].starttotal += 1;
		
		CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , 0 );		
		banker[bkid].hp[i] = MAXHP ;							//給血量
		CHAR_setWorkInt( charindex , NPC_WORK_HAND , 0 );		//重新拿牌
		CHAR_setWorkInt( charindex , NPC_WORK_HISTORY , 0 );	//記錄清除
		CHAR_setWorkInt( charindex , NPC_WORK_SELECT , -1 );		//選擇清除
		CHAR_setWorkInt( charindex , NPC_WORK_ACTION , 0 );		//動作清除
		j=0;
		while(j<5){
			k = rand()%(30-j);
			if( Cardbox[i+7*bkid][k].cardindex == 28 && flag == FALSE && rand()%100 > 50){	//降低召靈出現機率
				flag = TRUE;
				continue;
			}
			Cardbox[i+7*bkid][k].use = 1;
			card = SHIFTBASE << Cardbox[i+7*bkid][k].cardindex ; 
			CHAR_setWorkInt( charindex , NPC_WORK_HAND ,
				(unsigned int)CHAR_getWorkInt( charindex , NPC_WORK_HAND )|card );			
			qsort( &Cardbox[i+7*bkid] , 30 , sizeof(CardBoxType) , &NPC_magiccard_sort );
			j++;
		}
		/*
		for( j=0;j<30;j++){
			char tempbuf[256];
			sprintf( tempbuf,"%d ",Cardbox[i+7*bkid][j].use );	
			strcat( buf, tempbuf );	
		}
		showString( meindex, buf , 0);
		buf[0]='\0';
		for( j=0;j<30;j++){
			char tempbuf[256];
			sprintf( tempbuf,"%d ",Cardbox[i+7*bkid][j].cardindex );	
			strcat( buf, tempbuf );	
		}
		showString( meindex, buf , 0);
		*/

		//移動該挑戰者的視角	
		movescreenXY = ((14+offsetx) << 16) | (13+offsety)	;
		lssproto_MoveScreen_send(getfdFromCharaIndex(charindex), TRUE, movescreenXY);	

	}			
	banker[bkid].hp[BANKERID] = banker[bkid].starttotal * MAXHP ;
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, 1000 );
	banker[bkid].state = 1;
}

//讓挑戰者選擇出什麼牌
void NPC_magiccard_selectcard( int meindex , int bkid )
{
	int i,j,fd,allhp=0,charindex;
	unsigned int card=1;
	char token[256];
	
	for(i=0;i<MAXGUY;i++) allhp += banker[bkid].hp[i];
	for(i=0;i<MAXGUY;i++)
	{	
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;
////////////
		if( banker[bkid].pauseflag[i] == TRUE ){	
			sprintf( token,"%d號挑戰者%s被封印了，暫停一迴閤",i+1,CHAR_getChar( charindex, CHAR_NAME) );
			showString( meindex, token , 0);
			continue;
		}
////////////
		fd = getfdFromCharaIndex( charindex );		
		sprintf( token, "魔王HP%d 挑戰者HP%d【你的HP%d】\n",banker[bkid].hp[BANKERID],allhp,banker[bkid].hp[i]);
		for( j=0;j<30;j++){
			if( (card<<j) & (unsigned int)CHAR_getWorkInt( charindex , NPC_WORK_HAND ) ){
				strcat( token , Cardfunctiontable[j].name.string );
				strcat( token, "\n");
			}
		}	
		lssproto_WN_send( fd, WINDOW_MESSAGETYPE_SELECT ,
			WINDOW_BUTTONTYPE_NONE , 
			CHAR_WINDOWTYPE_MAGIC_SELECT , 
			CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX), token);

	}		
	banker[bkid].waittime = NowTime.tv_sec + 20 ;
	banker[bkid].state = 2;
}

//檢查是什麼牌 
void NPC_magiccard_checkselect( int meindex , int toindex ,int choise )
{
	int fd,i,j=0;
	unsigned int card=1;
	char token[128];
	int buttontype;

    fd = getfdFromCharaIndex( toindex );
    if( fd == -1 )  return;//要檢查挑戰者還在不在 目前還沒檢查
		
	for( i=0;i<30;i++){
		if( (card<<i) & (unsigned int)CHAR_getWorkInt( toindex , NPC_WORK_HAND) ){
			j++;
			if( j == choise ){ 
				CHAR_setWorkInt( toindex , NPC_WORK_SELECT , i ); //記錄挑戰者選擇出的牌0~29
				sprintf( token, "%s\n",Cardfunctiontable[i].name.string);
				//if( Cardfunctiontable[i].attack > 0 || Cardfunctiontable[i].defence > 0 ){
				if( i < 25 ){
					//確定是寵物牌				
					strcat( token , "\n攻擊\n" );				
					strcat( token , "\n防禦");
					buttontype = WINDOW_BUTTONTYPE_CANCEL;
				}else{
					buttontype = WINDOW_BUTTONTYPE_OK|WINDOW_BUTTONTYPE_CANCEL;
				}
				lssproto_WN_send( fd, WINDOW_MESSAGETYPE_SELECT ,
					buttontype, 
					CHAR_WINDOWTYPE_MAGIC_SELECT , 
					CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX), token);
				break;
			}	
		}
	}
}

//反悔想要重選時
void NPC_magiccard_selectback( int meindex , int toindex )
{
	unsigned int handcard;
	char token[256];
	int i,j,fd,bkid,allhp=0;

	handcard = CHAR_getWorkInt( toindex , NPC_WORK_HAND);
    bkid = CHAR_getWorkInt( toindex , NPC_WORK_BANKER );
	for(i=0;i<MAXGUY;i++) allhp += banker[bkid].hp[i];	
	for(i=0;i<MAXGUY;i++){
		if( strcmp( banker[bkid].cdkey[i] , CHAR_getChar( toindex, CHAR_CDKEY) ) == 0 &&
			strcmp( banker[bkid].name[i] , CHAR_getChar( toindex, CHAR_NAME) ) == 0){
			break;
		}
	}

	fd = getfdFromCharaIndex( toindex );
	if( fd == -1 )  return;

	sprintf( token, "魔王HP%d 挑戰者HP%d【你的HP%d】\n",banker[bkid].hp[BANKERID],allhp,banker[bkid].hp[i]); 
	for( j=0;j<30;j++){
		if( (SHIFTBASE<<j) & handcard ){
			strcat( token , Cardfunctiontable[j].name.string );
			strcat( token, "\n");
		}
	}	
	
	lssproto_WN_send( fd, WINDOW_MESSAGETYPE_SELECT ,
		WINDOW_BUTTONTYPE_NONE , 
		CHAR_WINDOWTYPE_MAGIC_SELECT , 
		CHAR_getWorkInt( meindex, CHAR_WORKOBJINDEX), token);

}

//檢查挑戰者是否都選擇好了
void NPC_magiccard_waitselect( int meindex , int bkid )
{
	int i,charindex,select=0;
	BOOL okflag = FALSE;
	char buf[256];

	for( i=0;i<MAXGUY;i++){		
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;
		if( //CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) != -1 &&
			CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) != 0 || banker[bkid].pauseflag[i] == TRUE ){	
			select++;  //選好了
		}else if( banker[bkid].turntime < NowTime.tv_sec ){
			CHAR_setWorkInt( charindex , NPC_WORK_SELECT , -1 );
			CHAR_setWorkInt( charindex , NPC_WORK_ACTION , 0 );
			//取消選擇			
			lssproto_MagiccardDamage_send(getfdFromCharaIndex(charindex), 10 , 0 ,0 ,0 );
			sprintf(buf,"出牌時間到，%d號挑戰者放棄出牌",i+1);	
			showString( meindex, buf , 0);
			select++;  //不等了不讓你選了 
		}
	}	 
	if( select >= banker[bkid].playertotal )  okflag = TRUE;	//大傢都選好了
	//sprintf(buf,"剩餘%d挑戰者  已選擇挑戰者有%d ",banker[bkid].playertotal,select);	
	//showString( meindex, buf , 0);
	if( okflag == TRUE ) {
		banker[bkid].state = 3;
		NPC_magiccard_aiselect( meindex , bkid );
		
		//sprintf(buf,"ai select %d action %d",banker[bkid].select,banker[bkid].action);	
		//showString( meindex, buf , 0);

		CHAR_setInt( meindex, CHAR_LOOPINTERVAL, SHOWCARDLOOPTIME );	
	}
}

void NPC_magiccard_aiselect( int meindex , int bkid )
{
	int i,j,k,enemy=0;	
	//int maxattack=0,maxdefence=0;
	//int maxacard=0,maxdcard=0;
	char buf[256];
	int charindex,allattack,alldefence,bestattack,bestdefence;
	int getdamage=0,givedamage=0;	
	int card25=0,allhp=0;
	int attacklist[5],defencelist[5],cardnum[5];
	BOOL selectflag = FALSE;
	BOOL checkflag = FALSE;

	for( i=0;i<6;i++){
		attacklist[i] = 0;
		defencelist[i] = 0;
		cardnum[i]=0;
		if(banker[bkid].pauseflag[i] == TRUE){
			banker[bkid].pauseflag[i] = FALSE;
			checkflag = TRUE;  //有人被封印 絕不隨機
		}
	}
	allattack=0;
	alldefence=0;
	bestattack=0;
	bestdefence=0;
//-----------------------------------------------------------------------------	
	if( banker[bkid].pauseflag[BANKERID] == TRUE )
	{
		banker[bkid].pauseflag[BANKERID] = FALSE;
		sprintf( buf,"魔王被封印了 暫停一迴閤" );
		showString( meindex, buf , 0);
		return;
	}
//-----------------------------------------------------------------------------
	if( rand()%200 > 5 + banker[bkid].playertotal * 1 || checkflag == TRUE || banker[bkid].turn == 10 ){	//80%
		selectflag = FALSE;
		for( i=0;i<MAXGUY;i++){
			charindex = NPC_magiccard_checkExist( meindex , bkid , i );
			if( charindex == -1 ) continue;
			enemy++;
			allhp += banker[bkid].hp[i];
			if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == 0 ) continue;
			if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == ATTACK ){
				allattack += Cardfunctiontable[CHAR_getWorkInt(charindex,NPC_WORK_SELECT)].attack ;
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == DEFENCE ){
				alldefence += Cardfunctiontable[CHAR_getWorkInt(charindex,NPC_WORK_SELECT)].defence ;
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 25 ){ //幻鏡
				if( rand()%100 > 40 + 5 * banker[bkid].playertotal ){
					allattack += rand()%10;						
					alldefence += rand()%10;
				}else{
					alldefence += Cardfunctiontable[0].attack ;		//可抵擋最強的攻擊-->代錶猜到
					card25++;
				}
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 26 ){ //幻影
				if( rand()%100 > 40 + 5 * banker[bkid].playertotal )
					alldefence += rand()%10;		
				else
					alldefence += Cardfunctiontable[0].attack ;		
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 27 ){ //封印
				if( rand()%100 > 30 + 5 * banker[bkid].playertotal ){
					allattack += rand()%5;						
					alldefence += rand()%5;
				}
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 28 ){ //召靈
				if( rand()%100 > 70 + 5 * banker[bkid].playertotal ){
					allattack += rand()%5;						
					alldefence += rand()%5;
				}
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 29 ){ //召雷		
				if( rand()%100 > 30 + 5 * banker[bkid].playertotal ){
					allattack += rand()%5;						
					alldefence += rand()%5;
				}	
			}
		}
		//sprintf( buf,"allA=%d   allD=%d",allattack,alldefence );
		//showString( meindex, buf , 0);

		//紀錄每一張牌的結果 沒有給值表示是0
		j=0;
		for( k=0;k<30;k++){
			if((SHIFTBASE<<k) & banker[bkid].hand ){
				if( k < 25 ){
					//攻擊
					if( 1 ){ //Cardfunctiontable[k].attack * enemy > alldefence ){
						givedamage =  Cardfunctiontable[k].attack * enemy - alldefence ;
						if( allhp > banker[bkid].hp[BANKERID] )
							getdamage = allattack + Cardfunctiontable[k].attack * card25;				
						else
							getdamage = allattack ;				
						attacklist[j] = givedamage - getdamage;
					}
					//防守
					if( Cardfunctiontable[k].defence * enemy < allattack ){
						defencelist[j] = Cardfunctiontable[k].defence * enemy - allattack;
					}
				}else{ //魔法牌
					attacklist[j] -= allattack;	//讓下面判斷寵牌不用考慮到魔法牌
					defencelist[j] -= allattack; 
				}
				cardnum[j]=k;
				j++;	
			}
		}
		//sprintf( buf,"讀出的手牌是 %d %d %d %d %d",cardnum[0],cardnum[1],cardnum[2],cardnum[3],cardnum[4]);
		//showString( meindex, buf , 0);

//召靈術---------------------------------------------------------------------
		for( i=0;i<5;i++){
			if( cardnum[i] == 28 ){	
				if( banker[bkid].turn == 10 )
					selectflag = TRUE;
				else{
					switch( banker[bkid].playertotal ){
					case 1:
					case 2:
						if( banker[bkid].hp[BANKERID] < banker[bkid].starttotal * (MAXHP-25) )
							selectflag = TRUE;
						break;
					case 3:
					case 4:
						if( banker[bkid].hp[BANKERID] < banker[bkid].starttotal * (MAXHP-20) || banker[bkid].turn > 8 )
							selectflag = TRUE;
						break;
					case 5:
					case 6:
						if( banker[bkid].hp[BANKERID] < banker[bkid].starttotal * (MAXHP-15) &&
							 allattack < banker[bkid].playertotal * 8  )
							selectflag = TRUE;
						else if( banker[bkid].turn > 7 )
							selectflag = TRUE;
						break;
					}
				}
				if( selectflag == TRUE ){				
					banker[bkid].select = 28;
					banker[bkid].action = MAGIC;
					return;						
				}
			}
		}
//封印術----------------------------------------------------------------	
		for( i=0;i<5;i++){
			if( cardnum[i]== 27 && banker[bkid].turn != 10 && banker[bkid].hp[BANKERID] >= banker[bkid].playertotal * 13){  
				switch( banker[bkid].playertotal ){
				case 1:		
				case 2:
					for( j=0;j<5;j++){
						if( rand()%100 > 50 && Cardfunctiontable[cardnum[j]].attack > 6 && allattack < banker[bkid].playertotal * 13 )
							selectflag = TRUE;		
					}
					break;
				case 3:
				case 4:
					for( j=0;j<5;j++){
						if( rand()%100 > 70 && Cardfunctiontable[cardnum[j]].attack > 7 && allattack < banker[bkid].playertotal * 8 )
							selectflag = TRUE;		
					}
					break;
				case 5:
				case 6:
					for( j=0;j<5;j++){
						if( rand()%100 > 50 && Cardfunctiontable[cardnum[j]].attack == 13 && allattack < banker[bkid].playertotal * 8 )
							selectflag = TRUE;							
						else if( rand()%100 > 80 && Cardfunctiontable[cardnum[j]].attack > 7 && allattack < banker[bkid].playertotal * 8 )
							selectflag = TRUE;												
					}
					break;
				}
				if( selectflag == TRUE ){				
					banker[bkid].select = 27;
					banker[bkid].action = MAGIC;
					return;						
				}
			}
		}
//如果有幻影術判斷要不要使用-----------------------------------------------------------------
		for( i=0;i<5;i++){
			if( cardnum[i] == 26 && checkflag == FALSE ){
				if( banker[bkid].turn == 10 && allhp <= banker[bkid].hp[BANKERID] ){
					selectflag = TRUE;
				}else{
					switch(	banker[bkid].playertotal ){
					case 1:
					case 2:
						if( banker[bkid].turn < 8 && rand()%100 > 80 ) selectflag = TRUE;					
						else if( banker[bkid].turn > 7 && banker[bkid].hp[BANKERID] < banker[bkid].starttotal * 15 ) selectflag = TRUE;				
						else if( allattack > 8 * banker[bkid].playertotal && rand()%100 > 40 ) selectflag = TRUE;
						break;					
					case 3:
					case 4:
						if( allhp > banker[bkid].hp[BANKERID] && allattack > 8 * banker[bkid].playertotal ) selectflag = TRUE;
						else if( allhp - banker[bkid].hp[BANKERID] > 10 && banker[bkid].turn > 5 &&
							allattack > 6 * banker[bkid].playertotal ){
							selectflag = TRUE;
						}
						break;		
					case 5:
					case 6:
						if( allhp - banker[bkid].hp[BANKERID] > 10 &&
							allattack > 8 * banker[bkid].playertotal ) selectflag = TRUE;	
						else if( banker[bkid].hp[BANKERID] > allhp && banker[bkid].turn > 5 && rand()%100 > 80) selectflag = TRUE;	
						else{
							for( j=0;j<MAXGUY;j++){
								charindex = NPC_magiccard_checkExist( meindex , bkid , i );
								if( charindex == -1 ) continue;
								if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 27 ){
									if( rand()%100 > (70-banker[bkid].turn*8) ){
										selectflag = TRUE;
										break;
									}
								}		
							}
						}
						break;
					}
				}
				if( banker[bkid].turn == 10 && allhp > banker[bkid].hp[BANKERID] ) selectflag = FALSE;
				if( selectflag == TRUE ){
					banker[bkid].select = 26;
					banker[bkid].action = MAGIC;
					return;						
				}
			}
		}
//如果有召雷術判斷要不要使用-----------------------------------------------------------------		 
		for( i=0;i<5;i++){
			if( cardnum[i] == 29 && checkflag == FALSE){
				switch(banker[bkid].playertotal){
				case 1:
				case 2:
					if( rand()%100 > 80 && banker[bkid].hp[BANKERID] < allhp ) selectflag = TRUE;
					else if( banker[bkid].turn == 10 && (allhp-banker[bkid].hp[BANKERID]) >= 10 ) selectflag = TRUE;
					break;			
				case 3:
				case 4:
					if( allattack < Cardfunctiontable[29].attack && rand()%100>30 )	selectflag = TRUE;
					else if( rand()%100 > 70 && banker[bkid].hp[BANKERID] < allhp ) selectflag = TRUE; 
					break;				
				case 5:
				case 6:
					if( allattack < Cardfunctiontable[29].attack+10 ) selectflag = TRUE;
					else if( banker[bkid].turn == 10 && (allhp - banker[bkid].hp[BANKERID]) >= 13 ) selectflag = TRUE;
					break;
				}
				if( selectflag == TRUE ){
					banker[bkid].select = 29;
					banker[bkid].action = MAGIC;
					return;						
				}
			}	
		}
//冰鏡術---------------------------------------------------------------------------------		
		for( i=0;i<5;i++){
			if( cardnum[i] == 25 && checkflag == FALSE ){
				if( banker[bkid].turn == 10 ){
					selectflag = TRUE;
				}else{
					switch(banker[bkid].playertotal){
					case 1:
					case 2:
						if( rand()%100 > 50 ) selectflag = TRUE;		
						else if( rand()%100>70-banker[bkid].turn*2 && allattack >= 6 * banker[bkid].playertotal ) selectflag = TRUE;						
						break;			
					case 3:
					case 4:
						if( rand()%100 > 60 ) selectflag = TRUE;
						else if( rand()%100 > 50 && allhp < banker[bkid].hp[BANKERID] ) selectflag = TRUE;
						else if( rand()%100>60-banker[bkid].turn*2 && allattack >= 7 * banker[bkid].playertotal ) selectflag = TRUE;
						break;				
					case 5:
					case 6:
						if( rand()%100 > 70 && allhp > banker[bkid].hp[BANKERID] ) selectflag = TRUE;
						else if( rand()%100>50-banker[bkid].turn*2 && allattack >= 8 * banker[bkid].playertotal ) selectflag = TRUE;
						else if( banker[bkid].turn > 7 && allhp < banker[bkid].hp[BANKERID] ) selectflag = TRUE;
						break;
					}
					if( selectflag == TRUE ){
						banker[bkid].select = 25;
						banker[bkid].action = MAGIC;
						return;						
					}
				}
			}	
		}
//最後一迴閤還輸一定用最強的攻擊----------------------------------------------------
		if( ( banker[bkid].turn == 10 && allhp > banker[bkid].hp[BANKERID] ) || checkflag == TRUE ){
			bestattack = 0;
			for( i=0;i<5;i++){
				if( cardnum[i] >= 25) continue;	
				if( Cardfunctiontable[cardnum[i]].attack > bestattack ){
					bestattack = Cardfunctiontable[cardnum[i]].attack;
					banker[bkid].select = cardnum[i];
					banker[bkid].action = ATTACK;						
				}
			}			
		}
//如果目前是贏的狀態 同時如果發現場上有人快沒血了  就用強攻牌------------------------
		if( banker[bkid].action == 0 ){
			if( allhp < banker[bkid].hp[BANKERID] ){
				for( j=0;j<BANKERID;j++){
					if( banker[bkid].hp[j] > 0 && banker[bkid].hp[j] < MAXHP/4 ){ 
						bestattack = 6;
						for( i=0;i<5;i++){
							if( cardnum[i] >= 25) continue;	
							if( Cardfunctiontable[cardnum[i]].attack > bestattack ){
								bestattack = Cardfunctiontable[cardnum[i]].attack;
								banker[bkid].select = cardnum[i];
								banker[bkid].action = ATTACK;						
							}
						}						
					}
				}
			}
		}
//-----------------------------------------------------------------------------------
		bestattack = 0;	
		bestdefence = 0;
		if( banker[bkid].action == 0 ){	
			if( allhp >= banker[bkid].hp[BANKERID] || rand()%100 > 50 ){	//穩贏攻擊
				for( i=0;i<5;i++){
					if( cardnum[i] >= 25) continue;	
					if( banker[bkid].hp[BANKERID] < banker[bkid].playertotal * 13 ) break; //快沒血了
					if( attacklist[i] > bestattack ){
						bestattack = attacklist[i];
						banker[bkid].select = cardnum[i];
						banker[bkid].action = ATTACK;	
					}
				}		
			}
		}
		if( banker[bkid].action == 0 ){
			if( rand()%100 > 50 + banker[bkid].playertotal * 3 ){
				//防守
				if( rand()%100 > 50 ){	
					bestdefence = defencelist[4] ; 
					for( i=4;i>=0;i--){	//容易用好牌
						if( cardnum[i] >= 25 ) continue;		
						if( defencelist[i] > bestdefence ){
							bestdefence = defencelist[i] ; 
							banker[bkid].select = cardnum[i];
							banker[bkid].action = DEFENCE;
						}
					}
				}else{
					bestdefence = defencelist[0] ; 
					for( i=0;i<5;i++){	//容易用弱牌
						if( cardnum[i] >= 25 ) continue;	
						if( defencelist[i] > bestdefence ){
							bestdefence = defencelist[i] ; 
							banker[bkid].select = cardnum[i];
							banker[bkid].action = DEFENCE;
						}
					}
				}
			}else{
				//攻擊
				if( rand()%100 > 50 ){	
					bestattack = attacklist[4] ; 
					for( i=4;i>=0;i--){	//容易用比較好的牌
						if( cardnum[i] >= 25 ) continue;	
						if( attacklist[i] > bestattack ){
							bestattack = attacklist[i] ; 
							banker[bkid].select = cardnum[i];
							banker[bkid].action = ATTACK;
						}
					}
				}else{
					bestattack = attacklist[0] ; 
					for( i=0;i<5;i++){	//容易用比較差的牌
						if( cardnum[i] >= 25 ) continue;	
						if( attacklist[i] > bestattack ){
							bestattack = attacklist[i] ; 
							banker[bkid].select = cardnum[i];
							banker[bkid].action = ATTACK;
						}
					}
				}
			}
		}
	}

	//如果沒有選擇就隨機出寵物牌 
	if( banker[bkid].action == 0 )
	{	
		j=0;
		for( k=0;k<25;k++){
			if((SHIFTBASE<<k) & banker[bkid].hand ){
				cardnum[j]=k;
				j++;
			}
		}
		//sprintf( buf,"隨機讀出的手牌是 %d %d %d %d %d",cardnum[0],cardnum[1],cardnum[2],cardnum[3],cardnum[4]);
		//showString( meindex, buf , 0);

		if( j==0 ) j = 1; 
		banker[bkid].select = cardnum[rand()%j];
		if( rand()%100 > 50 )
			banker[bkid].action = ATTACK;
		else
			banker[bkid].action = DEFENCE;
	}

	//最終檢查
	if( banker[bkid].select < 25 ){	
		if( Cardfunctiontable[banker[bkid].select].attack == 13 )
			banker[bkid].action = ATTACK;
		if( Cardfunctiontable[banker[bkid].select].defence == 13 )
			banker[bkid].action = DEFENCE;
	}else
		banker[bkid].action = MAGIC;
}

void NPC_magiccard_checkdamage( int meindex , int bkid )
{
	int charindex,i;
	int bankerdamage=0,playerdamage=0;
	int select;
	//char buf[256];

	for( i=0;i<MAXGUY;i++)
	{
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;
		CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , 0 );
		select = CHAR_getWorkInt( charindex , NPC_WORK_SELECT );	

		if( select == 28 ){ //挑戰者用招靈術
			CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , -MAXHP/2);
			playerdamage += -MAXHP/2;
			//sprintf( buf,"%d號挑戰者%s使用召靈術",i+1,CHAR_getChar( charindex, CHAR_NAME));
			//showString( meindex, buf , 0);
		}
		if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == ATTACK && banker[bkid].select != 26 )
		{
			if( banker[bkid].select == 25 ){ //幻鏡術
				CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , Cardfunctiontable[select].attack );
				playerdamage += Cardfunctiontable[select].attack;
			}else if( banker[bkid].action == DEFENCE ){
				if( Cardfunctiontable[select].attack > Cardfunctiontable[banker[bkid].select].defence )
					bankerdamage += (Cardfunctiontable[select].attack-Cardfunctiontable[banker[bkid].select].defence);
			}else
				bankerdamage += Cardfunctiontable[select].attack;
		}	
		if( banker[bkid].action == ATTACK && CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) != 26 )
		{
			if( select == 25 ){
				bankerdamage += Cardfunctiontable[banker[bkid].select].attack;
			}else if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == DEFENCE ){
				if( Cardfunctiontable[banker[bkid].select].attack > Cardfunctiontable[select].defence )
				{
					playerdamage += (Cardfunctiontable[banker[bkid].select].attack-Cardfunctiontable[select].defence);
					CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , (Cardfunctiontable[banker[bkid].select].attack-Cardfunctiontable[select].defence) );
				}
			}else{
				playerdamage += Cardfunctiontable[banker[bkid].select].attack;
				CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , 
					CHAR_getWorkInt( charindex , NPC_WORK_DAMAGE ) + Cardfunctiontable[banker[bkid].select].attack );	
			}		
		}
		//sprintf( buf,"挑戰者%d select=%d 傷害%d",i,select,CHAR_getWorkInt( charindex , NPC_WORK_DAMAGE ) );
		//showString( meindex, buf , 0);		
	}
	//sprintf( buf,"莊傢總傷害%d  挑戰者總傷害%d",bankerdamage,playerdamage);
	//showString( meindex, buf , 0);
	
	//秀動畫
	if( banker[bkid].select != 29 &&  banker[bkid].select != 27 ){
		//sprintf( buf,"-----------------魔王選擇出 第%d張------------------",banker[bkid].select);
		//showString( meindex, buf , 0);
		NPC_magiccard_action2( meindex , meindex , BANKERID , banker[bkid].select , banker[bkid].action );
	}
	
	for( i=0;i<MAXGUY;i++ ){
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;	 
		//挑戰者扣血
		banker[bkid].hp[i] -= CHAR_getWorkInt( charindex , NPC_WORK_DAMAGE ) ;
		NPC_magiccard_showdamage( meindex , charindex , i , CHAR_getWorkInt( charindex , NPC_WORK_DAMAGE ) );
		//if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == 0 ) continue; //放棄出牌
		//sprintf( buf,"i=%d Action=%d",i,CHAR_getWorkInt( charindex , NPC_WORK_ACTION ));
		//showString( meindex, buf , 0);
		if( banker[bkid].hp[i] > MAXHP ) banker[bkid].hp[i] = MAXHP;
		if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) != 29 &&
			CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) != 27 )
			NPC_magiccard_action2( meindex , charindex , i , CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) , CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) );	
	}

	//莊傢扣血
	if( banker[bkid].select == 28 ){ //莊傢用召靈術
		bankerdamage = bankerdamage - banker[bkid].starttotal*MAXHP/2;	
		//sprintf( buf,"魔王的招靈計算  bankdamage=%d 自己=%d",bankerdamage,banker[bkid].starttotal*MAXHP/2);
		//showString( meindex, buf , 0);

	}
	banker[bkid].hp[BANKERID] -= bankerdamage;
	NPC_magiccard_showdamage( meindex, meindex , BANKERID , bankerdamage );
	if( banker[bkid].hp[BANKERID] > banker[bkid].starttotal * MAXHP )
		banker[bkid].hp[BANKERID] = banker[bkid].starttotal * MAXHP;
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, FIGHTLOOPTIME );
	banker[bkid].state = 4;
}

void NPC_magiccard_specialcard( int meindex , int bkid )
{
	int thunder=0,allhp=0; 
	int i,j,k,target,targetarray[6],charindex,damage=0;
	char buf[256],buf1[256],buf2[256];	

	//計算有幾個人使用落雷術
	for( i=0;i<MAXGUY;i++)
	{
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;	 
		if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 29 ){
			thunder++;
			sprintf( buf,"%d號挑戰者使用召雷術",i+1);				
			showString( meindex, buf , 0);
		}
		allhp += banker[bkid].hp[i];
	}
	if( banker[bkid].select == 29 ){
		thunder++;	
		sprintf( buf,"魔王使用召雷術");				
		showString( meindex, buf , 0);
	}
	
	//sprintf( buf,"落雷數%d",thunder);
	//showString( meindex, buf , 0);
	i=0;
	while(thunder){	
		
		if( rand()%100 > 50 + 5 * banker[bkid].playertotal )
			target = BANKERID;	
		else
		{
			k = 0 ;
			for( j=0;j<BANKERID;j++ ){
				if( NPC_magiccard_checkExist( meindex , bkid , j ) == -1 ) continue;
				targetarray[k] = j;
				k++;
			}
			if( k == 0 )  target = BANKERID;  //沒有玩傢在場了
			else  target = targetarray[rand()%k];
		}
	
		if(target == BANKERID ) //中莊傢
		{
			charindex = meindex;
			if( banker[bkid].select != 26 )	damage = Cardfunctiontable[29].attack;
			else damage = 0;			

			banker[bkid].hp[target] -= damage;
			i++;
			if( damage == 0 ){
				sprintf( buf,"魔王被第%d發落雷擊中，因幻影術而沒事",i);		
			}else{
				sprintf( buf,"魔王被第%d發落雷擊中",i);				
			}
			showString( meindex, buf , 0);
		}else{
			charindex = NPC_magiccard_checkExist( meindex , bkid , target );
			if( charindex == -1 ) continue;
			
			if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 26 ) damage = 0;
			else damage = Cardfunctiontable[29].attack;			

			banker[bkid].hp[target] -= damage;	
			allhp -= damage;
			i++;	
			if( damage == 0 ){
				sprintf( buf,"%d號挑戰者被第%d發落雷擊中，因幻影術而沒事",target+1,i);		
			}else{
				sprintf( buf,"%d號挑戰者被第%d發落雷擊中",target+1,i);				
			}
			showString( meindex, buf , 0);
		}
		NPC_magiccard_action2( meindex , charindex , target , 29 , MAGIC );
		NPC_magiccard_showdamage( meindex , meindex , target , damage );	
		thunder--;
	}

	buf1[0] ='\0';
	buf2[0] ='\0';	
	//處理封印術
	if( banker[bkid].select == 27 )
	{
		sprintf( buf,"魔王使用封印術");				
		showString( meindex, buf , 0);

		for( i=0;i<MAXGUY;i++ ){
			charindex = NPC_magiccard_checkExist( meindex , bkid , i );
			if( charindex == -1 ) continue;	 
			NPC_magiccard_action2( meindex , meindex , i , 27 , MAGIC );

			if( ( rand()%100 > ( 30 - 4 * banker[bkid].playertotal ) ) &&
				CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) != 26 ){				
				banker[bkid].pauseflag[i] = TRUE;
				NPC_magiccard_showdamage(meindex , meindex , i , 1111 );
				sprintf(buf2,"%d號玩傢 ",i+1);
				strcat( buf1,buf2);
			}else 
				NPC_magiccard_showdamage(meindex , meindex , i , 2222 );		
		}
	}
	for( i=0;i<MAXGUY;i++)
	{
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;	 
		if( CHAR_getWorkInt( charindex , NPC_WORK_SELECT ) == 27 ){
		
			sprintf( buf,"%d號挑戰者使用封印術",i+1);					
			NPC_magiccard_action2( meindex , charindex , BANKERID , 27 , MAGIC );
			if( banker[bkid].select == 26 )
			{
				NPC_magiccard_showdamage(meindex , meindex , BANKERID , 2222 );
				strcat(buf," 因魔王使用幻影術失敗");
			}else if( rand()%100 > ( 50 + 5 * banker[bkid].playertotal ) ){	
				banker[bkid].pauseflag[BANKERID] = TRUE;
				sprintf( buf2,"魔王 ");
				strcat( buf1,buf2);
				NPC_magiccard_showdamage( meindex , meindex , BANKERID , 1111 );
				strcat(buf," 命中");	
			}else{
				NPC_magiccard_showdamage(meindex , meindex , BANKERID , 2222 ); 								
				strcat(buf," 失敗");
			}
			showString( meindex, buf , 0);
		}	
	}
	
	if(strcmp( buf1 , "" ) !=0 ){
		strcat( buf1,"被封印了");
	}

	//播報迴閤對戰結果	
	if( allhp > banker[bkid].hp[BANKERID] )
		sprintf( buf,"第%d迴閤結束【挑戰者HP%d】領先【魔王HP%d】%s",banker[bkid].turn,allhp,banker[bkid].hp[BANKERID],buf1);
	else if( allhp < banker[bkid].hp[BANKERID] )
		sprintf( buf,"第%d迴閤結束【魔王HP%d】領先【挑戰者HP%d】%s",banker[bkid].turn,banker[bkid].hp[BANKERID],allhp,buf1);
	else
		sprintf( buf,"第%d迴閤結束，雙方【HP%d】平手 %s",banker[bkid].turn,allhp,buf1);
	showString( meindex, buf , 0);

	banker[bkid].state = 5;
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, TURNOVERTIME );
}

// 新的秀圖流程
void NPC_magiccard_action2(int meindex , int charindex , int user , int card , int action )
{
	int x,y,floor;
	OBJECT object;
	int objindex,othercharindex;
	int j,k,dir,animno;
	char data[1024],buf[256];
	int offsetx,offsety;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	floor = CHAR_getInt(charindex, CHAR_FLOOR);
	x = Positiontable[user].petX + offsetx;
	y = Positiontable[user].petY + offsety;
	dir = Positiontable[user].direct;
	animno = Cardfunctiontable[card].effect;

	//用透明人npc
	if( ( card == 27 || card == 29 ) && user <= BANKERID ){
		object=MAP_getTopObj(floor, Positiontable[user].npcX + offsetx, Positiontable[user].npcY + offsety );
		if(object){ 
			objindex = GET_OBJINDEX( object);
			charindex = OBJECT_getIndex(objindex);
		}
		//sprintf( data,"npcindex %d  name: %s",charindex,CHAR_getChar(charindex, CHAR_NAME));
		//showString( charindex, data , 0);
	}

	for( j = x-CHAR_DEFAULTSEESIZ ; j <= x+CHAR_DEFAULTSEESIZ ; j++ ){
		for( k = y-CHAR_DEFAULTSEESIZ ; k <= y+CHAR_DEFAULTSEESIZ ; k ++ ){									
			for (object = MAP_getTopObj(floor, j, k); object; object = NEXT_OBJECT(object))
			{
				objindex = GET_OBJINDEX( object);
				othercharindex	= OBJECT_getIndex(objindex);

				if (OBJECT_getType(objindex) == OBJTYPE_NOUSE)
					continue;
				//if (OBJECT_getType(objindex) == OBJTYPE_CHARA &&
				//		!CHAR_getFlg(OBJECT_getIndex(objindex), CHAR_ISVISIBLE))
				//	continue;	
				if (OBJECT_getType(objindex) == OBJTYPE_CHARA &&
						CHAR_getInt(othercharindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER &&
						CHAR_getWorkInt(othercharindex, CHAR_WORKBATTLEMODE ) == BATTLE_CHARMODE_NONE){
					sprintf( data,"%d|%d|%d|%d|%d|%d|%d|%d|",CHAR_getWorkInt( charindex, CHAR_WORKOBJINDEX)
					//sprintf( data,"%d|%d|%d|%d|%d|%d|",CHAR_getWorkInt( npccharindex, CHAR_WORKOBJINDEX)
						,user,card,dir,animno,action,offsetx,offsety);
					lssproto_MagiccardAction_send(getfdFromCharaIndex(othercharindex), data );
					//lssproto_Firework_send(getfdFromCharaIndex(othercharindex), CHAR_getWorkInt( charindex, CHAR_WORKOBJINDEX), 0, 101888);
				}
			}
		}
	}
}

void NPC_magiccard_showdamage(int meindex , int charindex , int position , int damage )
{
	int x,y,j,k,floor;
	OBJECT object;
	int objindex,othercharindex,offsetx,offsety;	
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	char buf[256];
	
	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	floor = CHAR_getInt(charindex, CHAR_FLOOR);
	x = Positiontable[position].humanX + offsetx;
	y = Positiontable[position].humanY + offsety;

	for( j = x-CHAR_DEFAULTSEESIZ/2 ; j <= x+CHAR_DEFAULTSEESIZ/2 ; j++ ){
		for( k = y-CHAR_DEFAULTSEESIZ/2 ; k <= y+CHAR_DEFAULTSEESIZ/2 ; k ++ ){									
			for (object = MAP_getTopObj(floor, j, k); object; object = NEXT_OBJECT(object))
			{
				objindex = GET_OBJINDEX( object);
				othercharindex	= OBJECT_getIndex(objindex);

				if (OBJECT_getType(objindex) == OBJTYPE_NOUSE)
					continue;
				if (OBJECT_getType(objindex) == OBJTYPE_CHARA &&
						!CHAR_getFlg(OBJECT_getIndex(objindex), CHAR_ISVISIBLE))
					continue;
				if (OBJECT_getType(objindex) == OBJTYPE_CHARA &&
						CHAR_getInt(othercharindex, CHAR_WHICHTYPE) == CHAR_TYPEPLAYER &&
						CHAR_getWorkInt(othercharindex, CHAR_WORKBATTLEMODE ) == BATTLE_CHARMODE_NONE){
					lssproto_MagiccardDamage_send(getfdFromCharaIndex(othercharindex), position,damage,offsetx,offsety);			
					//sprintf( buf,"name: %s  fd%d posi %d damage %d ox %d oy %d",CHAR_getChar(othercharindex, CHAR_NAME),
					//	getfdFromCharaIndex(othercharindex),position,damage,offsetx,offsety		
					//	);
					//showString( meindex, buf , 0);
				}
			}
		}
	}

}

//哪個挑戰者出局
void NPC_magiccard_out( int meindex , int bkid , int player )
{
	int gift=0,charindex,allhp=0,i;
	char buf[128];
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	int offsetx,offsety;

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	charindex = NPC_magiccard_checkExist( meindex , bkid , player );
	if( !CHAR_CHECKINDEX(charindex)) return;
	
	for( i=0;i<MAXGUY;i++) allhp += banker[bkid].hp[i];	

	if(banker[bkid].hp[player]<=0||banker[bkid].hp[BANKERID]>=allhp ){
		if( CHAR_getWorkInt( charindex , NPC_WORK_GIVEGOLD ) == 1 ){
			sprintf(buf,"目前總積分為%d，謝謝光臨",CHAR_getInt( charindex , CHAR_GAMBLENUM));
			CHAR_talkToCli( charindex , -1 , buf,  CHAR_COLORYELLOW);
		}else{
			sprintf(buf,"很抱歉你輸了扣 6 點積分，目前總積分為%d，謝謝光臨",CHAR_getInt( charindex , CHAR_GAMBLENUM));
			CHAR_talkToCli( charindex , -1 , buf,  CHAR_COLORYELLOW);
		}
	}else{		
		if( banker[bkid].turn <= 10 && banker[bkid].hp[BANKERID] <= 0) gift = 20;
		else if(allhp >= banker[bkid].starttotal*MAXHP*80/100 ) gift = 15;
		else if(allhp >= banker[bkid].starttotal*MAXHP*60/100 ) gift = 10;	
		else gift = 5;

		if( CHAR_getWorkInt( charindex , NPC_WORK_GIVEGOLD ) == 1 ){
			CHAR_setInt( charindex , CHAR_GOLD, CHAR_getInt( charindex , CHAR_GOLD)+10000 );
			CHAR_setInt( charindex , CHAR_GAMBLENUM, CHAR_getInt( charindex , CHAR_GAMBLENUM)+gift );
			sprintf(buf,"已拿迴保證金10000Ｓ");
			CHAR_talkToCli( charindex , -1 , buf,  CHAR_COLORYELLOW);
		}else{
			CHAR_setInt( charindex , CHAR_GAMBLENUM, CHAR_getInt( charindex , CHAR_GAMBLENUM)+gift+6 );
		}
		sprintf(buf,"恭喜您得到 %d 點積分，目前總積分為%d，謝謝光臨",gift,CHAR_getInt( charindex , CHAR_GAMBLENUM));
		CHAR_talkToCli( charindex , -1 , buf,  CHAR_COLORYELLOW);
		Bettotal[bkid] -= 6;
		Wintotal[bkid] += gift;
		if( CHAR_getInt( charindex , CHAR_GAMBLENUM ) > 10000 )
			CHAR_setInt( charindex , CHAR_GAMBLENUM	, 10000 );
	}
		
	CHAR_setWorkInt( charindex , CHAR_WORK_TEMP_FLOOR, 0);
	// 熒幕歸位
	lssproto_MoveScreen_send(getfdFromCharaIndex(charindex), FALSE, 0);

	CHAR_warpToSpecificPoint( charindex , CHAR_getInt( meindex, CHAR_FLOOR) 
				,Positiontable[7].humanX + offsetx , Positiontable[7].humanY + offsety);	
	//banker[bkid].playertotal -= 1; 
}

//一迴閤結束重新抽牌
void NPC_magiccard_turnover( int meindex , int bkid	)
{
	char buf[256];
	unsigned int  card;
	int i,k,charindex,offsetx,offsety;	
	BOOL goflag = FALSE;
	OBJECT object;
	int bossindex,objindex;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);


	//清除手牌 和 抽牌
	for( i=0;i<MAXGUY;i++)
	{
		charindex = NPC_magiccard_checkExist( meindex , bkid , i );
		if( charindex == -1 ) continue;

		//檢查還有沒有資格活下來
		if( banker[bkid].hp[i] <= 0 ) {
			sprintf( buf,"%d號挑戰者出局了",i+1);
			showString( meindex, buf , 0);	
			NPC_magiccard_out( meindex , bkid , i );
			continue;
		}
		goflag = TRUE; //代錶還有玩傢可以進入下迴閤
		if( CHAR_getWorkInt( charindex , NPC_WORK_ACTION ) == 0 ) continue;	//放棄出牌的人
		//清除出過的牌
		card = SHIFTBASE << CHAR_getWorkInt( charindex , NPC_WORK_SELECT );
		CHAR_setWorkInt( charindex , NPC_WORK_HISTORY , (unsigned int)CHAR_getWorkInt( charindex , NPC_WORK_HISTORY ) | card ); 
		card = ~card;
		CHAR_setWorkInt( charindex , NPC_WORK_HAND , (unsigned int)CHAR_getWorkInt( charindex , NPC_WORK_HAND ) & card );	
		//抽牌
		k = rand()%(26-banker[bkid].turn);
		if( Cardbox[i+7*bkid][k].cardindex == 28 && rand()%100 > 50 ) k = rand()%(26-banker[bkid].turn); //降低召靈出現機率

		Cardbox[i+7*bkid][k].use = 1;
		card = SHIFTBASE << Cardbox[i+7*bkid][k].cardindex ; 
		CHAR_setWorkInt( charindex , NPC_WORK_HAND ,
			(unsigned int)CHAR_getWorkInt( charindex , NPC_WORK_HAND )|card );			
		qsort( &Cardbox[i+7*bkid] , 30 , sizeof(CardBoxType) , &NPC_magiccard_sort );

		CHAR_setWorkInt( charindex , NPC_WORK_SELECT , -1 );  //選擇清除
		CHAR_setWorkInt( charindex , NPC_WORK_ACTION , 0 );	//動作清除
		CHAR_setWorkInt( charindex , NPC_WORK_DAMAGE , 0 ); //傷害清除

	}

	if( banker[bkid].action != 0 )  //沒有被封印
	{
		//把莊傢出過的牌拿掉 
		card = SHIFTBASE << banker[bkid].select ;	
		banker[bkid].history |= card;
		card = ~card;
		banker[bkid].hand &= card;

		//莊傢抽牌
		k = rand()%(26-banker[bkid].turn);
		if( Cardbox[6+7*bkid][k].cardindex == 28 && rand()%100 > 50 ) k = rand()%(26-banker[bkid].turn); //降低召靈出現機率
		Cardbox[6+7*bkid][k].use = 1;
		card = SHIFTBASE << Cardbox[6+7*bkid][k].cardindex ; 
		banker[bkid].hand |= card;
		qsort( &Cardbox[6+7*bkid] , 30 , sizeof(CardBoxType) , &NPC_magiccard_sort );
	}

	if( banker[bkid].turn == 10 || banker[bkid].hp[BANKERID] <= 0 || goflag == FALSE ){
		//比賽結束	
		if( banker[bkid].hp[BANKERID] <= 0 && goflag == TRUE )
		{
			object = MAP_getTopObj(CHAR_getInt(meindex, CHAR_FLOOR), Positiontable[BANKERID].humanX + offsetx, Positiontable[BANKERID].humanY + offsety );
			if( object ){
				objindex = GET_OBJINDEX( object);
				bossindex = OBJECT_getIndex(objindex);
				CHAR_sendAction( bossindex , 2 , FALSE);	//暈倒	
			}
		}
		CHAR_setInt( meindex, CHAR_LOOPINTERVAL, GAMEOVERTIME );
		banker[bkid].state = 9;			
	}else{
		banker[bkid].turn += 1;
		if( banker[bkid].turn == 10 ){
			sprintf(buf,"第10迴閤 最後一迴閤 戰鬥");
		}else{
			sprintf(buf,"第%d迴閤 戰鬥",banker[bkid].turn);
		}
		showString( meindex, buf , 0);
		banker[bkid].turntime = NowTime.tv_sec + 20 ;
		banker[bkid].process = 0;
		banker[bkid].select = 0;
		banker[bkid].action = 0;
		banker[bkid].state = 1; 
		CHAR_setInt( meindex, CHAR_LOOPINTERVAL, LOOPTIME );
	}
}

void NPC_magiccard_gameover( int meindex , int bkid )
{
	int i,allhp=0;
	char buf[256];

	
	for( i=0;i<MAXGUY;i++) allhp += banker[bkid].hp[i];	

	sprintf(buf,"戰鬥結束【大魔王HP%d】vs【挑戰者總閤HP%d】",banker[bkid].hp[MAXGUY],allhp);
	if( banker[bkid].hp[MAXGUY] >= allhp ){
		strcat(buf,"大魔王獲勝");
	}else{
		strcat(buf,"恭喜挑戰者獲勝");
	}
	showString( meindex, buf , 0);

	for( i=0;i<MAXGUY;i++) NPC_magiccard_out(  meindex , bkid , i );	//所有挑戰者出場
	NPC_magiccard_resetbanker(meindex,bkid);	
}

void NPC_magiccard_resetbanker( int meindex , int bkid )
{
	OBJECT object;
	int bossindex,objindex,offsetx,offsety;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE];
	char buf[256];
	int j,k;
	
	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return ;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	for(j=0;j<7;j++){
		for(k=0;k<30;k++){
			Cardbox[j+bkid*7][k].use = 0;
			Cardbox[j+bkid*7][k].cardindex = k;
		}
	}

	memset(&banker[bkid],0,sizeof(banker[bkid]));	
	banker[bkid].state = -1;
	CHAR_setInt( meindex, CHAR_LOOPINTERVAL, LOOPTIME );
	
	//雷爾變身
	object = MAP_getTopObj(CHAR_getInt(meindex, CHAR_FLOOR), Positiontable[BANKERID].humanX + offsetx, Positiontable[BANKERID].humanY + offsety );
	if( object ){
		objindex = GET_OBJINDEX( object);
		bossindex = OBJECT_getIndex(objindex);
		CHAR_sendAction( bossindex , 3 , FALSE);
		CHAR_CHAT_DEBUG_metamo( bossindex , "0" );
	}	
}

int NPC_magiccard_checkExist( int meindex , int bkid , int player )
{
	int i,floor,offsetx,offsety;
	int playernum = CHAR_getPlayerMaxNum();
	char *cdkey = NULL;
	char *name = NULL;
	OBJECT object;
	char argstr[NPC_UTIL_GETARGSTR_BUFSIZE],buf[256];

	if( NPC_Util_GetArgStr( meindex, argstr, sizeof( argstr)) == NULL )	{
		print("\n read argstr err");
		return -1;
	}		
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsetx", buf, sizeof( buf));
	offsetx = atoi(buf);
	NPC_Util_GetStrFromStrWithDelim( argstr , "offsety", buf, sizeof( buf));
	offsety = atoi(buf);

	cdkey = banker[bkid].cdkey[player];
	name = banker[bkid].name[player];
	if( cdkey == NULL || name == NULL )
		return -1;
	for( i = 0 ; i < playernum ; i ++) {
		if( CHAR_CHECKINDEX( i) &&
			strcmp( CHAR_getChar( i, CHAR_CDKEY) , cdkey ) == 0 &&
			strcmp( CHAR_getChar( i, CHAR_NAME) , name ) == 0 ){
			break;
		}
	}
	if( i == playernum ) return -1;		//沒有找到挑戰者
	floor = CHAR_getInt( meindex , CHAR_FLOOR);
	object = MAP_getTopObj( floor, Positiontable[player].humanX + offsetx , Positiontable[player].humanY + offsety );
	if( object ){  
		int findex;
		int objindex = GET_OBJINDEX(object);
		findex = OBJECT_getIndex( objindex);
		if( findex == i ) 
			return i;		//有找到
	}
	return -1;	
}

int NPC_magiccard_sort( const void *card1, const void *card2 )
{
	return ( ((CardBoxType*)card1)->use > ((CardBoxType*)card2)->use )? 1:0;
}
#endif
