#include "version.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include  <dirent.h>   
#include  <sys/types.h>   
#include  <sys/stat.h> 

#include "configfile.h"
#include "util.h"
#include "net.h"
#include "msignal.h"
#include "buf.h"
#include "object.h"
#include "char.h"
#include "char_data.h"
#include "item.h"
#include "readmap.h"
#include "function.h"
#include "saacproto_cli.h"
#include "lssproto_serv.h"
#include "readnpc.h"
#include "log.h"
#include "handletime.h"
#include "title.h"
#include "encount.h"
#include "enemy.h"
#include "battle.h"
#include "magic_base.h"
#include "pet_skill.h"
#include "item_gen.h"
#include "petmail.h"
#include "npc_quiz.h"
#include "char_talk.h"
#ifdef _TALK_MOVE_FLOOR
#include "longzoro/move.h"
#endif
#ifdef _LUCK_STAR
#include "longzoro/luckstar.h"
#endif
#include "autil.h"
#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
#include "profession_skill.h"
#endif
#ifdef _ALLBLUES_LUA
#include "mylua/mylua.h"
#endif
#ifdef _ONLINE_SHOP
#include "longzoro/newshop.h"
#endif

#ifdef _ITEM_QUITPARTY
#include "init.h"
//int itemquitparty_num = 0;
//static DisappearItem *Disappear_Item;
#endif

#ifdef _EPOLL_ET_MODE
#include "epollnet.h"
#endif


#define MESSAGEFILE "hoge.txt"

#define OPTIONSTRING "d:f:hcl"
#define usage() print( "Usage: %s ["OPTIONSTRING"]\n", getProgname() );

void printUsage( void )
{
    usage();
  /*print( "Usage: %s ["OPTIONSTRING"]\n", progname );*/
    print( "          [-d debuglevel]        default value is 0\n" );
    print( "          [-f configfilename]    default value is setup.cf\n"
        );
}

/*
 *
 * 婁醒
 * 忒曰襖
 *      TRUE(1)     懇橘卅戊穴件玉仿奶件婁醒分勻凶日
 *      FALSE(0)    唱橘卅戊穴件玉仿奶件婁醒分勻凶日
 */
BOOL parseCommandLine( int argc , char** argv )
{
    int c;                          /* getopt 匹銀丹 */
    extern char* optarg;            /* getopt 匹銀丹 */


    while( ( c = getopt( argc, argv ,OPTIONSTRING )) != -1 ){
        switch( c ){
        case 'd':
        {
            int     debuglevel;
            if( !strtolchecknum( optarg, (int*)&debuglevel, 10,
                                 INT)){
                print( "Specify digit number\n" );
                return FALSE;
            }
            setDebuglevel( debuglevel );
            break;
        }
        case 'f':
            setConfigfilename( optarg );
            break;
        case 'h':
            printUsage();
            return FALSE;
            break;
				case 'c':
#ifdef _CRYPTO_DATA
						if(opendir("allblues")==NULL){
							if (mkdir("allblues", 0777) == 0){
								printf("建立文件夾 allblues\n");
							}
						}
						if(opendir("allblues/data")==NULL){
							if (mkdir("allblues/data", 0777) == 0){
								printf("建立文件夾 data\n");
							}
						}
						List("data");
						printf("data加密已完成，請查閱allblues文件夾\n");
            return FALSE;
#endif
            break;
#ifdef _CRYPTO_LUA
				case 'l':
						{
							int flg = 0,id = 0;
							printf("請問需要加密還是解密？(0為解密, 1為加密):");
							scanf("%d", &flg); 
							printf("請問ID是多少:");
							scanf("%d", &id); 
							CryptoAllbluesLUA("allblues", flg, id);
							if(flg == 0){
								printf("已完成解密工作\n");
							}else{
								printf("已完成加密工作\n");
							}
							return FALSE;
          	}
            break;
#endif
        default:
            printUsage();
            return FALSE;
            break;

        }
    }
    return TRUE;
}


/*
 * 婁醒
 *
 * 漆及赭窒手仄卅中
 */
BOOL parseEnvironment( char** env )
{
    if( getDebuglevel() >= 3 ){
        int index=0;
        while( env[index] != NULL )print( "%s " , env[index++] );
        print( "\n" );
    }
    return TRUE;
}

extern int backdoor;

#define GOTORETURNFALSEIFFALSE(x) if(!(x))goto RETURNFALSE
/*
 * 賡渝祭夥□民件
 * 婁醒
 *      argc    argv及醒
 *      argv    戊穴件玉仿奶件婁醒
 * 忒曰襖
 */
BOOL init(int argc , char** argv , char** env )
{
#ifdef _ITEM_QUITPARTY
    FILE *f;
	int i;
	char line[256];
#endif
    srand( getpid());
    print( "This Program is compiled at %s %s by gcc %s\n",
           __DATE__ , __TIME__ , __VERSION__ );

    defaultConfig( argv[0] );
    GOTORETURNFALSEIFFALSE(parseCommandLine( argc , argv ));
    GOTORETURNFALSEIFFALSE(parseEnvironment( env ));
    
    signalset();
    

    {
        Char    aho;
        debug( sizeof( aho ), d);
        debug( sizeof( aho.data ), d);
        debug( sizeof( aho.string ), d);
        debug( sizeof( aho.flg ),d);
        debug( sizeof( aho.indexOfExistItems ), d);
        debug( sizeof( aho.haveSkill ), d);
        debug( sizeof( aho.indexOfHaveTitle ), d);
        debug( sizeof( aho.addressBook ),d);
        debug( sizeof( aho.workint ),d);
        debug( sizeof( aho.workchar ),d);
    }

    print( "配置文件: %s\n" , getConfigfilename() );
		
    GOTORETURNFALSEIFFALSE(readconfigfile( getConfigfilename() ) );

    nice(getrunlevel());
    //ttom start
    {  int iWork = setEncodeKey();
       if( iWork == 0 ){
       // 巨件戊□玉平□毛澀爛
       printf( "----------------------------------------\n" );
       printf( "-------------[編碼] 無法設置 %s\n", getConfigfilename() );
       printf( "----------------------------------------\n" );
       exit( 1 );
       }else{
            // 巨件戊□玉平□毛澀爛
               printf( "編碼 = %d\n", iWork );
       }
    }
    // AcWBuff毛澀爛
    {   int iWork = setAcWBSize();
        if( iWork == 0 ){
           printf( "----------------------------------------\n" );
           printf( "-------------[AC緩衝] 無法設置 %s\n", getConfigfilename() );
           printf( "----------------------------------------\n" );
           exit( 1 );
           }else{
                   printf( "AC緩衝 = %d\n", iWork );
           }
    }
    //ttom end

    if( getDebuglevel() >= 1 ){
//		print("ServerType: %d\n", getServerType() );
				print("調試等級: %d\n", getDebuglevel() );
				print("運行等級: %d\n", getrunlevel() );
				print("接收緩衝: %d\n", getrecvbuffer()*1024);
				print("發送緩衝: %d\n", getsendbuffer()*1024);
				print("接收緩衝下限: %d\n", getrecvlowatbuffer());
        print("內存單元大小: %d\n", getMemoryunit() );
        print("內存單元數量: %d\n", getMemoryunitnum() );

        print("賬號服務器地址: %s\n", getAccountservername() );
        print("賬號服務器端口: %d\n", getAccountserverport() );
        print("登陸服務器名稱: %s\n", getGameservername());
        print("登陸服務器密碼: %s\n", getAccountserverpasswd());

        print("等待連接端口: %d\n", getPortnumber() );

        print("服務端序列號: %d\n", getServernumber() );

        print("重復地址使用: %d\n", getReuseaddr() );


        print("最大在線人數: %d\n", getFdnum() );
        print("最大在線寵數: %d\n", getPetcharnum() );
        print("最大其他數目: %d\n", getOtherscharnum() );
        print("最大對象數目: %d\n", getObjnum() );
        print("最大物品數目: %d\n", getItemnum() );
        print("最大戰鬥數目: %d\n", getBattlenum() );
        print("頂層文件目錄: %s\n", getTopdir());
        print("地圖文件目錄: %s\n", getMapdir());
        print("地圖標識文件: %s\n", getMaptilefile());
        print("物品配置文件: %s\n", getItemfile());
        print("不可戰鬥文件: %s\n", getInvfile());
        print("顯示位置文件: %s\n", getAppearfile());
        print("遇敵配置文件: %s\n", getEffectfile());
        print("頭銜名稱文件: %s\n", getTitleNamefile());
        print("頭銜配置文件: %s\n", getTitleConfigfile());
        print("遇敵坐標文件: %s\n", getEncountfile());
        print("遇敵組群文件: %s\n", getGroupfile());
        print("寵物基本文件: %s\n", getEnemyBasefile());
        print("創建寵物文件: %s\n", getEnemyfile());
        print("精靈魔法文件: %s\n", getMagicfile());

#ifdef _ATTACK_MAGIC
        print("攻擊魔法文件: %s\n", getAttMagicfileName() );
#endif

        print("寵物技能文件: %s\n", getPetskillfile());

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
        print("職業技能文件: %s\n", getProfession());
#endif

        print("物品成份文件: %s\n", getItematomfile());
        print("猜迷問題文件: %s\n", getQuizfile());
#ifdef _GMRELOAD
				print("G M 配置文件: %s\n", getGMSetfile());
#endif
        print("日誌記錄文件: %s\n",  getLsgenlogfilename() );
        print("還原資料目錄: %s\n", getStoredir());
        print("NPC 配置目錄: %s\n", getNpcdir());
        print("日誌記載文件: %s\n",  getLogdir());
        print("日誌配置文件: %s\n", getLogconffile() );
        print("GM的指命密碼: %s\n", getChatMagicPasswd() );
        print("使用GM的權限: %d\n", getChatMagicCDKeyCheck() );

        print("NPC 模闆數目: %d\n", getNpctemplatenum() );
        print("NPC 最大數目: %d\n", getNpccreatenum() );

        print("走路時間間隔: %d\n", getWalksendinterval());
        print("清除所有間隔: %d\n", getCAsendinterval_ms());
        print("清除目標間隔: %d\n", getCDsendinterval_ms());
        print("執行一次時間: %d\n", getOnelooptime_ms());
        print("寵物清除時間: %d\n", getPetdeletetime());
        print("道具清除時間: %d\n", getItemdeletetime());
#ifdef _DEL_DROP_GOLD
				print("石器清除時間: %d\n", getGolddeletetime());
#endif
        print("數據保存間隔: %d\n", getCharSavesendinterval());

        print("名片最大數目: %d\n", getAddressbookoffmsgnum());
        print("讀取頻率協議: %d\n" ,getProtocolreadfrequency());

        print("連接錯誤上限: %d\n", getAllowerrornum());
#ifdef _GET_BATTLE_EXP
				print("戰鬥經驗倍數: %d倍\n", getBattleexp() );
#endif
#ifdef _NEW_PLAYER_CF
				print("出生人物轉數: %d轉\n", getNewplayertrans());
				print("出生人物等級: %d級\n", getNewplayerlv());
				print("出生人物金錢: %d S\n", getNewplayergivegold());
				print("出生寵物等級: %d級\n", getNewplayerpetlv());
#ifdef _VIP_SERVER
				print("出生擁有點數: %d點\n", getNewplayergivevip());
#endif
				print("出生能騎等級: %d\n", getRidePetLevel());
#ifdef _NEW_PLAYER_RIDE
				print("出生配套騎寵: %s\n", getPlayerRide());
#endif
				print("出生擁有寵物: NO1:%d NO2:%d NO3:%d NO4:%d NO5:%d\n",getNewplayergivepet(0),
																																	getNewplayergivepet(1),
																																	getNewplayergivepet(2),
																																	getNewplayergivepet(3),
																																	getNewplayergivepet(4));
				print("出生擁有物品: ITEM1:%d ITEM2:%d ITEM3:%d ITEM4:%d ITEM5:%d\n"
							"　　　　　　　ITEM1:%d ITEM2:%d ITEM3:%d ITEM4:%d ITEM5:%d\n"
							"　　　　　　　ITEM1:%d ITEM2:%d ITEM3:%d ITEM4:%d ITEM5:%d\n"
																																	,getNewplayergiveitem(0)
																																	,getNewplayergiveitem(1)
																																	,getNewplayergiveitem(2)
																																	,getNewplayergiveitem(3)
																																	,getNewplayergiveitem(4)
																																	,getNewplayergiveitem(5)
																																	,getNewplayergiveitem(6)
																																	,getNewplayergiveitem(7)
																																	,getNewplayergiveitem(8)
																																	,getNewplayergiveitem(9)
																																	,getNewplayergiveitem(10)
																																	,getNewplayergiveitem(11)
																																	,getNewplayergiveitem(12)
																																	,getNewplayergiveitem(13)
																																	,getNewplayergiveitem(14));
#endif
#ifdef _UNREG_NEMA
		print("禁止人物名稱: 名字1:%s 名字2:%s 名字3:%s 名字4:%s 名字5:%s\n",getUnregname(0),
																																	getUnregname(1),
																																	getUnregname(2),
																																	getUnregname(3),
																																	getUnregname(4));
#endif

#ifdef _WATCH_FLOOR
		print("是否全圖觀戰: %s\n",getWatchFloorCF());
		if(strcmp(getWatchFloorCF(),"是"))
			print("允許觀戰地圖: 地圖1:%d 地圖2:%d 地圖3:%d 地圖4:%d 地圖5:%d\n",getWatchFloor(1),
																																		getWatchFloor(2),
																																		getWatchFloor(3),
																																		getWatchFloor(4),
																																		getWatchFloor(5));
#endif

#ifdef _BATTLE_FLOOR
		print("是否強制戰鬥: %s\n",getBattleFloorCF());
		if(strcmp(getBattleFloorCF(),"是"))
			print("強制戰鬥地圖: 地圖1:%d 地圖2:%d 地圖3:%d 地圖4:%d 地圖5:%d\n",getBattleFloor(1),
																																		getBattleFloor(2),
																																		getBattleFloor(3),
																																		getBattleFloor(4),
																																		getBattleFloor(5));
#endif

#ifdef _TRANS_LEVEL_CF
		print("人物等級轉數: %d級\n",getChartrans());
		print("寵物等級轉數: %d級\n",getPettrans());
#endif

#ifdef _POINT
		print("禁止點數上限: %s\n",getPoint());
		if(strcmp(getPoint(),"是"))
			print("每轉點數上限: 0轉:%d 1轉:%d 2轉:%d 3轉:%d 4轉:%d 5轉:%d 6轉:%d\n",getTransPoint(0),
																																								getTransPoint(1),
																																								getTransPoint(2),
																																								getTransPoint(3),
																																								getTransPoint(4),
																																								getTransPoint(5),
																																								getTransPoint(6));
#endif

#ifdef _PET_AND_ITEM_UP
		print("寵物能否撿獲: %s\n",getPetup());
		print("道具能否撿獲: %s\n",getItemup());
#endif
#ifdef _LOOP_ANNOUNCE
		print("循環公告路徑: %s\n",getLoopAnnouncePath());
		print("循環時間間隔: %d分鍾\n",getLoopAnnounceTime());
#endif
#ifdef _SKILLUPPOINT_CF
		print("每級升級點數: %d\n",getSkup());
#endif

#ifdef _RIDELEVEL
		print("騎寵等級相差: %d級\n",getRideLevel());
#endif
#ifdef _REVLEVEL
		print("還原上限等級: %s級\n",getRevLevel());
#endif
#ifdef _TRANS_LEVEL_CF
		print("一般等級上限: %d級\n",getYBLevel());
		print("最高等級上限: %d級\n",getMaxLevel());
#endif
#ifdef _FIX_CHARLOOPS
	print("惡魔時間倍數: %d倍\n",getCharloops());
#endif
#ifdef _PLAYER_ANNOUNCE
	if(getPAnnounce()==-1)
		print("喇叭消耗點數: 關閉使用\n");
	else
		print("喇叭消耗點數: %d點\n",getPAnnounce());
#endif
#ifdef _PLAYER_MOVE
	if(getPMove()==-1)
		print("順移消耗點數: 關閉使用\n");
	else
		print("順移消耗點數: %d點\n",getPMove());
#endif
#ifdef _BATTLE_GOLD
		print("戰鬥獲得金錢: %d\n",getBattleGold());
#endif
#ifdef _ANGEL_TIME
		print("精靈召喚時間: (%d人/在線人數)分\n",getAngelPlayerTime());
		print("精靈召喚人數: %d人\n",getAngelPlayerMun());
#endif
#ifdef _RIDEMODE_20
		print("2.0 騎寵模式: %d\n",getRideMode());
#endif
#ifdef _FM_POINT_PK
		print("莊園互搶模式: %s\n",getFmPointPK());
#endif
    }

	{	//andy_add 2003/05/05 check GameServer Name
		char *GameServerName;
		GameServerName = getGameserverID();
		if( GameServerName == NULL || strlen( GameServerName) <= 0 )
			return FALSE;
		print("\n遊戲服務器ID: %s\n",  GameServerName );
	}

  print("開始初始化\n" );
    
//#define DEBUG1( arg... ) if( getDebuglevel()>1 ){##arg}
    print( "建立內存空間..." );
    GOTORETURNFALSEIFFALSE(configmem( getMemoryunit(),
                                      getMemoryunitnum() ) );
    GOTORETURNFALSEIFFALSE(memInit());
		print( "完成\n" );
				
		print( "始終化連接空間..." );
    if( !initConnect(getFdnum()) )
        goto MEMEND;
    print( "完成\n" );
    while( 1 ){
        print( "嘗試綁定本地端口 %d... " , getPortnumber());
#ifdef _EPOLL_ET_MODE
        bindedfd = epoll_bind( getPortnumber() );
#else
        bindedfd = bindlocalhost( getPortnumber() );
#endif
        if( bindedfd == -1 )
            sleep( 10 );
        else
            break;
    }
	print( "完成\n" );
	print( "建立對象..." );
    if( !initObjectArray( getObjnum()) )
        goto CLOSEBIND;
	print( "完成\n" );
	
	print( "建立人物..." );
#ifdef _OFFLINE_SYSTEM
    if(!CHAR_initCharArray( getPlayercharnum(), getPetcharnum(),getOtherscharnum()) )
#else
    if(!CHAR_initCharArray( getFdnum(), getPetcharnum(),getOtherscharnum()) )
#endif
        goto CLOSEBIND;
	print( "完成\n" );
	print( "建立物品...");
    if(!ITEM_readItemConfFile( getItemfile()) )
        goto CLOSEBIND;
    if(!ITEM_initExistItemsArray( getItemnum() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "建立戰鬥..." );
    if(!BATTLE_initBattleArray( getBattlenum() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "建立功能模塊..." );
    if( !initFunctionTable() )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "初始化郵件..." );
    if( !PETMAIL_initOffmsgBuffer( getAddressbookoffmsgnum() ))
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取不可戰鬥文件..." );
    if( !CHAR_initInvinciblePlace( getInvfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取顯示位置文件..." );
    if( !CHAR_initAppearPosition( getAppearfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取頭銜名稱文件..." );
    if( !TITLE_initTitleName( getTitleNamefile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取頭銜配置文件..." );
    if( !TITLE_initTitleConfig( getTitleConfigfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取遇敵坐標文件..." );
    if( !ENCOUNT_initEncount( getEncountfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取寵物基本文件..." );
    if( !ENEMYTEMP_initEnemy( getEnemyBasefile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取創建寵物文件..." );
    if( !ENEMY_initEnemy( getEnemyfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

	print( "讀取遇敵組群文件..." );
    if( !GROUP_initGroup( getGroupfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );
	print( "讀取魔法文件..." );
    if( !MAGIC_initMagic( getMagicfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

		#ifdef _ATTACK_MAGIC

	print( "讀取魔法攻擊文件..." );

    if( !ATTMAGIC_initMagic( getAttMagicfileName() ) )
//		if( !ATTMAGIC_initMagic( getMagicfile() ) )
        goto CLOSEBIND;

	print( "魔法攻擊文件 -->%s..." , getAttMagicfileName());
	print( "完成\n" );

    #endif
 
	print( "讀取寵物技能文件..." );
    if( !PETSKILL_initPetskill( getPetskillfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );

#ifdef _PROFESSION_SKILL			// WON ADD 人物職業技能
	print( "讀取職業技能文件..." );
	if( !PROFESSION_initSkill( getProfession() ) ){
		goto CLOSEBIND;
	}
	print( "完成\n" );
#endif

    /* 失奶  丞及箋    毛  戈 */
	print( "讀取物品成份文件..." );
    if( !ITEM_initItemAtom( getItematomfile()) )
        goto CLOSEBIND;
	print("完成\n" );

	print( "初始化料理閤成物品..." );
    if( !ITEM_initItemIngCache() )
        goto CLOSEBIND;
	print("完成\n" );
    
	print( "初始料理閤成隨機設定..." );
    if( !ITEM_initRandTable() )
        goto CLOSEBIND;
	print("完成\n" );
  
	print( "讀取遇敵配置文件..." );
    if( !CHAR_initEffectSetting( getEffectfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );
	print( "讀取猜迷問題文件..." );
    if( !QUIZ_initQuiz( getQuizfile() ) )
        goto CLOSEBIND;
	print( "完成\n" );
#ifdef _GMRELOAD
	print( "讀取GM配置文件..." );
	if ( !LoadGMSet( getGMSetfile() ) )
		goto CLOSEBIND;
	print( "完成\n" );
#endif

#ifdef _USER_EXP_CF
	print( "讀取經驗配置文件..." );
	if ( !LoadEXP( getEXPfile() ) )
		goto CLOSEBIND;
	print("最高等級: %d...",getMaxLevel());
	print("一般等級: %d...",getYBLevel());
	print( "完成\n" );
#endif

#ifdef _ANGEL_SUMMON
	print("讀取精靈召喚任務列錶文件...");
	if( !LoadMissionList( ) )
		goto CLOSEBIND;
	print("完成\n");
#endif

#ifdef _JOBDAILY
	print("讀取任務日誌文件...");
	if(!LoadJobdailyfile())
		print("...失敗\n");
	else
		print("完成\n");
#endif

#ifdef _LOOP_ANNOUNCE
	print("讀取循環公告文件...");
	if(!loadLoopAnnounce())
		print("...失敗\n");
	else
	 print("完成\n");
#endif
#ifdef _RIDE_CF
	print( "讀取自定義騎寵文件..." );
	if(!CHAR_Ride_CF_init())
		print("...失敗\n");
	print("完成\n");
#endif
#ifdef _FM_LEADER_RIDE
	print( "讀取莊園族長專用騎寵文件..." );
	if(!CHAR_FmLeaderRide_init())
		print("...失敗\n");
	print("完成\n");
#endif
#ifdef _RE_GM_COMMAND
	print( "自定義GM命令重命名文件..." );
	if(!re_gm_command())
		print("...失敗\n");
	print("完成\n");
#endif

#ifdef _FIND_TREASURES
	print( "讀取尋寶奬品配置文件..." );
	if(!FindTreasures_init())
		print("...失敗\n");
	print("完成\n");
#endif
	print( "建立地圖..." );
    if( !MAP_initReadMap( getMaptilefile() , getMapdir() ))
        goto CLOSEBIND;
	print( "完成\n" );
	print( "讀取NPC文件..." );
    if( !NPC_readNPCSettingFiles( getNpcdir(), getNpctemplatenum(),
                                  getNpccreatenum() ) )
        goto CLOSEBIND;
	print( "完成\n" );
	
#ifdef _TALK_MOVE_FLOOR
	print( "讀取說話移動地圖文件..." );
	if(!MoveMap_init())
		print("...失敗\n");
	print("完成\n");
#endif
		
#ifdef _LUCK_STAR
	print( "讀取幸運星文件..." );
	if(!LuckStar_init())
		print("...失敗\n");
	print("完成\n");
#endif

#ifdef _ONLINE_SHOP
	print( "讀取在線商城配置文件..." );
	if(!OnlineShop_init())
		print("...失敗\n");
	print("完成\n");
#endif
	
#ifdef _PLAYER_DIY_MAP
	print( "初始化玩傢DIY地圖..." );
	if(!MAP_intPlayerMap())
		print("...失敗\n");
	print("完成\n");
#endif

#ifdef _FILTER_TALK
	print( "讀取說話過濾文件..." );
	if(!ReadFilterTalk())
		print("...失敗\n");
	print("完成\n");
#endif

	print( "初始化 NPC 服務器... " );
    if( lssproto_InitServer( lsrpcClientWriteFunc, LSGENWORKINGBUFFER ) < 0 )
        goto CLOSEBIND;
	print( "完成\n" );
	print( "嘗試連接賬號服務器... " );
  acfd = connectHost( getAccountservername(), getAccountserverport());
  if(acfd == -1)
     goto CLOSEBIND;

#ifdef _EPOLL_ET_MODE
  if(epoll_add_acfd(acfd) == -1)
	  goto CLOSEBIND;
#endif

/*
	{
		int errorcode;
		int errorcodelen;
		int qs;

		errorcodelen = sizeof(errorcode);
		qs = getsockopt( acfd, SOL_SOCKET, SO_RCVBUF , &errorcode, &errorcodelen);
		//andy_log
		print("\n\n GETSOCKOPT SO_RCVBUF: [ %d, %d, %d] \n", qs, errorcode, errorcodelen);
	}
*/

	print( "完成\n" );
  initConnectOne( acfd, NULL , 0 );
  if( !CONNECT_acfdInitRB( acfd)) goto CLOSEAC;
  if( !CONNECT_acfdInitWB( acfd)) goto CLOSEAC;
  CONNECT_setCtype( acfd, AC );
	
	print( "初始化 賬號 客戶端 ... " );
  if( saacproto_InitClient( lsrpcClientWriteFunc,LSGENWORKINGBUFFER, acfd) < 0 )
        goto CLOSEAC;
	print( "完成\n" );

	print( "嚮賬號服務器發送登陸請求... " );
    /*  夫弘奶件邰菲毛請允  */
   	{
#if _ATTESTAION_ID == 1
			saacproto_ACServerLogin_send(acfd, _ATTESTAION_ID, getGameservername(), getAccountserverpasswd());
#else
			saacproto_ACServerLogin_send(acfd, getGameservername(), getAccountserverpasswd());
#endif
    }
	print( "完成\n" );
#ifdef _OTHER_SAAC_LINK
	OtherSaacConnect();
#endif

  if( isExistFile( getLsgenlogfilename() ) ){
     lssproto_SetServerLogFiles( getLsgenlogfilename(),
                                    getLsgenlogfilename() );
     saacproto_SetClientLogFiles( getLsgenlogfilename(),
                                     getLsgenlogfilename() );
  }


	print( "初始化已完成\n" );

#ifdef _LOTTERY_SYSTEM
	saacproto_LotterySystem_send();
#endif
	print( "開始記尋新的日誌 ... " );
    {
        char    logconffile[512];
        snprintf( logconffile, sizeof( logconffile), "%s/%s" ,
                  getLogdir(), getLogconffile() );
        if( !initLog( logconffile ) )
            goto CLOSEAC;
    }
  print( "完成\n" );
#ifdef  _PET_ITEM
	restoreObjects( getStoredir() );
#endif
#ifdef _ITEM_QUITPARTY
	print( "讀取隊伍解散物品消失文件..." );
    
	//讀取檔案
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", getitemquitparty());
	f = fopen( realopfile, "r");
	if( f != NULL ){
		crypto = TRUE;
	}else
#endif
{
    f = fopen( getitemquitparty(), "r" );
}
	if( f != NULL ){
		while( fgets( line, sizeof( line ), f ) ){
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(line);
			}
#endif
			if( line[0] == '#' )continue;
            if( line[0] == '\n' )continue;
		    chomp( line );
			itemquitparty_num++;
		}
		if( fseek( f, 0, SEEK_SET ) == -1 ){
			print( "物品錄找錯誤\n" );
			fclose(f);
			goto CLOSEAC;
		}
		//配記憶體
		Disappear_Item = allocateMemory( sizeof(struct tagDisappearItem) * itemquitparty_num );
		if( Disappear_Item == NULL ){
			print( "無法分配內存 %d\n", sizeof(struct tagDisappearItem) * itemquitparty_num );
			fclose( f );
			goto CLOSEAC;
		}

		i = 0;
		//將道具編號存入 Disappear_Item.string
		while( fgets( line, sizeof( line ), f ) ){
#ifdef _CRYPTO_DATA		
			if(crypto==TRUE){
				DecryptKey(line);
			}
#endif
			if( line[0] == '#' )continue;
			if( line[0] == '\n' )continue; 
			chomp( line );
			sprintf( Disappear_Item[i].string,"%s",line );
			print("\n道具編號:%s", Disappear_Item[i].string );
			i++;
		}
		fclose(f);
	}
#endif

    DEBUG_ADJUSTTIME = 0;
    print( "\n" );
    return TRUE;

CLOSEAC:
    close( acfd );
CLOSEBIND:
    close( bindedfd );
    endConnect();
MEMEND:
    memEnd();
RETURNFALSE:
    return FALSE;
}
