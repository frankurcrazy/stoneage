#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef _WIN32
#include <crtdbg.h>
#endif


#ifdef _SA_VERSION_SPECIAL
#define _SA_VERSION_60
#define __ALBUM_47
#define _FONT_SIZE					// Robin (要開) 可改字型大小
#define _ITEM_PILENUMS				// (可開放) ANDY 道具素材堆疊
#define _ITEM_INTENSIFY				// (可開) Change 寵技:強化道具
#define _ALCHEMIST					// Robin 精煉功能 
#define _CHAR_NEWLOGOUT				// (可開放) ANDY 新登齣機製
//#define _ITEM_JIGSAW				// (可開) Change 拼圖道具
#define	_TELLCHANNEL				// (可開放) ROG ADD 密語頻道
#define _TRADETALKWND				// (可開放) Syu ADD 交易新增對話框架
#define _DROPPETWND					// (可開放) Syu ADD 丟棄寵物確認
#define _TEAM_KICKPARTY				// (可開放) ANDY 隊長踢人
#define _MONEYINPUT					// (可開放) Syu ADD 手動輸入金錢量

#define _STREET_VENDOR				// 擺攤功能
#define _STREET_VENDOR_CHANGE_ICON	// 修改擺攤圖示
#define _NEW_MANOR_LAW				// 新莊園規則
#define _PETS_SELECTCON				// (可開放) ANDY 寵物選擇
#define _FM_MODIFY					// 傢族功能修改
#define _CHANNEL_MODIFY				// 頻道功能整閤
#define _TRADELOCKBTN				// (可開放) Syu ADD 增加鎖定鍵
#define _MAILSHOWPLANET				// (可開放) Syu ADD 顯示名片星球
#define _LOCKPARTYFLOOR				// (可開放) Syu ADD 增加不可組隊的地圖編號
#define _LOCKHELP_OK				// (可開放) Syu ADD 鎖定不可加入戰鬥
#define _JOBDAILY					// cyg 任務日誌功能
//	#define _TALK_WINDOW				// 對話視窗
#define _SHOW_FUSION				// (可開) Change 融閤寵物在CLIENT端隻顯示轉生數,修改為融閤寵顯示為融閤
#define _ITEM_FIREWORK				// 煙火功能
#define _FIREWORK_SOUND				// cyg 新增音效(煙火用)
//#define _GET_HOSTNAME				// (可開) Change 取得電腦名稱
#define _NPC_MAGICCARD				// cyg 魔法牌遊戲
#define _THEATER					// Terry 劇場功能
#define _MOVE_SCREEN				// Terry 移動熒幕到指定的座標
#define _NPC_DANCE					// cyg 動一動npc
#define _CHANNEL_WORLD				// 增加世界頻道
#define _STANDBYPET					// Robin 送待機寵列錶到Server
#define _MAILSHOWPLANET				// (可開放) Syu ADD 顯示名片星球
#define _EXTEND_AB					// cyg 擴充名片功能
#define _ITEM_EQUITSPACE			// (可開放) ANDY 新增裝備欄位
#define _EQUIT_ARRANGE				// (可開放) ANDY 格擋
#define _EQUIT_NEWGLOVE				// (可開放) ANDY 手套欄位
//#define _ALCHEMIST					// Robin 精煉功能 
//#define _ALCHEPLUS					// Robin 鑒定功能 
//#define _NPC_ITEMUP					// (可開) Change 讓道具升級的NPC
//#define _ITEM_COUNTDOWN				// cyg 道具倒數功能
//#define _CHATROOMPROTOCOL			// (可開放) Syu ADD 聊天室頻道
//#define _FRIENDCHANNEL				// (可開放) ROG ADD 好友頻道
//#define __ONLINEGM
#endif
//#define _BATTLE_PK_PLAYER_FOR_40		// 40人戰鬥
//#define  _BATTLE_PK_PLAYER_FOR_6VS6		// 6 vs 6       XIEZI 添加

#ifdef _BATTLE_PK_PLAYER_FOR_40
#define BATTLESIDENUM 4					//戰鬥隊伍數量
#define BATTLKPKPLYAERNUM 40			//最大參戰角色數
#define MAX_BATTLE_ROW_CHARS   5		//每行最大戰鬥角色數
#else
#define BATTLESIDENUM 2					//戰鬥隊伍數量
#ifdef _BATTLE_PK_PLAYER_FOR_6VS6
#define BATTLKPKPLYAERNUM 24			//最大參戰角色數
#define MAX_BATTLE_ROW_CHARS   6		//每行最大戰鬥角色數
#else
#define BATTLKPKPLYAERNUM 20			//最大參戰角色數
#define MAX_BATTLE_ROW_CHARS   5		//每行最大戰鬥角色數
#endif
#endif

#define _NEW_SYSTEM_MENU				// 新係統菜單 2011/12/21
#define _PTTERN_SEPARATION_BIN			// 分離補丁加載
//#define _SFUMATO						// 二次渲染 未完善，需美術資源配閤
#define _SPECIAL_LOGO					// 新登陸圖
#define _CHANNEL_ALL_SERV				// 增加星球頻道 2011/12/21
#define _EXTEND_FONT_PAL				// 擴展字體顔色色闆 2011/12/22
//#define _FONT_PARAGRAPH_COLOR			// 字體分離顔色 2011/12/22
#define _NEW_CLIENT_LOGIN				// 登陸記錄MAC地址及綫路選擇 2011/12/22
//#define _NEW_SHOP_FRAME  				// 新商店框架 2011/12/22

#define _HI_COLOR_16				// (可開) ANDY (8bit to 16bit) 含圖檔
#define _HI_COLOR_32				// (可開) longzoro (32 bit) 含圖檔
#define _NEW_RESOMODE				 //800 600模式
#define _MOUSE_SHOW_INFO_FOR_HEAD	// (可開) longzoro 鼠標顯示信息
//#define _NEWLOGO				   // (可開放) Syu ADD 6.0登入畫麵新logo 要關_v4_0 
/* -------------------------------------------------------------------
* 新功能：石器 800 * 600
* 人員：旭誠,鎮瑋
* 說明：
*/

extern int DISPLACEMENT_X;
extern int DISPLACEMENT_Y;
extern int viewOffsetX;
extern int viewOffsetY;

//#define _NEWDRAWBATTLEMAP_FIX		   // (不可開)ROG ADD 戰鬥地圖修改

// 版本分割
#ifdef _SA_VERSION_85
#define _SA_VERSION_80
#endif

#ifdef _SA_VERSION_80
#define _SA_VERSION_75
#endif

#ifdef _SA_VERSION_75
#define _SA_VERSION_70
#endif

#ifdef _SA_VERSION_70
#define _SA_VERSION_60
#endif

#ifdef _SA_VERSION_60
#define _SA_VERSION_50
#endif

#ifdef _SA_VERSION_50
#define _SA_VERSION_40
#endif



/* 請將控製專案的 definition 放在這個檔案
* 然後藉由 remark/unmark 來開關功能
*/



/* -------------------------------------------------------------------
* 專案：族人職務與傢族功能補充
* 人員：小瑜、彥勛、誌偉、小民
* 說明：
*/
#define  _FMVER21                      // (可開放) 傢族職掌功能
#define _PERSONAL_FAME                 // (可開放) Arminius 8.30 傢族個人聲望


// -------------------------------------------------------------------
// 專案：伊甸大陸新NPC交談介麵
// 人員：曉威
// 說明：__EDEN_EFFECT:賭場的銀行NPC'委托交易的NPC
//			 __EDEN_AUCTION:委托NPC拍賣物品介麵
#define __EDEN_EFFECT			// (可開放) 但測試時要打開
#define __EDEN_AUCTION		    // (可開放) 但測試時要打開

// -------------------------------------------------------------------
// 專案：攻擊性咒術的製作
// 人員：篤誌
// 說明：
#define __ATTACK_MAGIC

// -------------------------------------------------------------------
// 專案：嚇年獸的鞭炮
// 人員：曉威
// 說明：
#define _ITEM_FIRECREAKER

/* -------------------------------------------------------------------
* 新功能：PK星係
* 人員：彥勛
* 說明：
*/
//#define _PKSERVER // (不可開放)


// -------------------------------------------------------------------
// 專案：傳送手機簡訊的玩傢界麵實作
// 人員：昌磊  (LeiBoy)
// 說明：讓玩傢可以傳簡訊給特定的ASP網頁處理
// 主要相關檔 : PhoneMsg.cpp
// 完成日期 : 2002年01月28日
// 開放日期 : 2002年03月04日
// Status : Ready!
//#define __PHONEMESSAGE    
#define _FIX_URLENCODE             // WON ADD (可 開 放) 北京修正簡訊無法加空格的問題


// -------------------------------------------------------------------
// 專案：傳送手機簡訊的二期工程
// 人員：(原定)昌磊  (接班人未定)
// 說明：讓玩傢可以傳簡訊到名片中好友的手機中
// 開放日期 : 禁止開放!!
// Status : 建構中...
//#define __CARDMESSAGE   //(禁用)!!


//#define __NEW_CLIENT_ONLY_WRITE	//Cary(禁用,未測過)
//#define CHINA_VER			//Cary (禁用)
//#define __ALBUM_4
//#define __ALBUM_6			//Cary 加入新的寵物相簿(含年獸)
//#define __TEST_SERVER		//Cary 3.0的測試server

#define __HELP				//Cary 綫上說明
#define __NEW_PROTOCOL		//Cary 新的底層

#define __NEW_CLIENT_MEM	//Cary
#define __SKYISLAND			//Cary 加入天空島的功能
#define __HI_COLOR			//Cary 加入高彩的功能(debug version專用)
#define __TALK_TO_NPC		//Cary 使用左鍵和npc說話
#define __NEW_BATTLE_EFFECT	//Cary 2002.2.21 新的戰鬥特效，如:替身娃娃
#define _AFTER_TRADE_PETWAIT_	   // (可 開 放) set pet status to wait after trade :vincent



#ifdef _SA_VERSION_40
/* -------------------------------------------------------------------
* 新功能：伊甸4
* 人員：誌旺
* 說明：
*/
#define _FIX_DEL_MAP			   // (可開放) WON ADD 修正玩傢抽地圖

#define _FIX_9_FMPOINT			   // (可開放) WON ADD 九大莊園
#define _FIX_10_FMPOINT			//(可開) Change 十大莊園 20050404
#ifdef _FIX_10_FMPOINT
#define fm_point_num	10		   // 莊園數
#else
#define fm_point_num	9		   // (可開放) WON ADD 莊園數
#endif

#define _ADD_POOL_ITEM				// (可開放) WON ADD 增加寄放道具
//#define _ADD_FAMILY_TAX				// (不可開) WON ADD 增加莊園稅收

#define _LOST_FOREST_FOG			// (可開放) the lostforest's fog. code:shan 
#define _MIND_ICON					// (可開放) show icon from char mind. code:shan
#define _MAGIC_WEAKEN				// (可開放) show magic(weaken). code:shan

#define _BLACK_MARKET            // (不可開) a black market. code:shan 

// -------------------------------------------------------------------
// vincent define
#define _MAGIC_DEEPPOISION         // (可開放) show magic(deeppoison). code:vincent
#define _MAGIC_BARRIER             // (可開放) show magic(barrier). code:vincent
#define _MAGIC_NOCAST              // (可開放) show magic(nocast). code:vincent
#define _ITEM_CRACKER              // (可開放) 道具:拉炮 code:vincent
#define _SKILL_ROAR                // (可開放) vincent  寵技:大吼(剋年獸)
#define _SKILL_SELFEXPLODE         // (可開放) vincent  寵技:自爆

#define _NEW_RIDEPETS			   // (可開放) 新騎寵

#define _ATTDOUBLE_ATTACK	       // (可開放) 屬性強化攻擊
#define __TOCALL_MAGIC			   // (可開放) kjl 02/06/24	
#define _VARY_WOLF                 // (可開放) pet skill : vary wolf. code:shan
#define _PIRATE_ANM                // (可開放) monster move(海盜王). code: shan
#define _TRADE_PETCOLOR            // (可開放) Syu ADD 改變交易時寵物轉生顔色
#define _FIXSHOWMPERR			   // (可開放) Syu ADD 修正補氣時動畫顯示錯誤
#define _LIZARDPOSITION			   // (可開放) Syu ADD 修正龍蜥顯示位置過低


/* -------------------------------------------------------------------
* 新功能：
* 更新日期2002/12/18 14:00 更新
*/

#define _TEAM_KICKPARTY				// (可開放) ANDY 隊長踢人
#define _MONEYINPUT					// (可開放) Syu ADD 手動輸入金錢量

#define _PETS_SELECTCON				// (可開放) ANDY 寵物選擇

#endif		// _SA_VERSION_40



#ifdef _SA_VERSION_60
/* -------------------------------------------------------------------
* 新功能：石器6.0
* 更新日期
*/
#define _OBJSEND_C					// (可開放) ANDY 6.0
#define _ADD_SHOW_ITEMDAMAGE		// (可開放) WON ADD 顯示道具的耐久度
#define _WATERANIMATION				// (可開放) Syu ADD 淚之海動畫層
#define _NEWDRAWBATTLEMAP			// (可開放) Syu ADD 水世界戰鬥地錶與戰鬥特效 
#define _AniCharBubble				// (可開放) Syu ADD 動畫層人物吐齣氣泡
#define _AniCrossFrame				// (可開放) Syu ADD 動畫層遊過畫麵生物
#define _AniImmobile				// (可開放) Syu ADD 定點産生特定動畫
#define _AniRandom					// (可開放) Syu ADD 隨機産生環境動畫
//#define _DELBORNPLACE				// (可開放) Syu ADD 6.0 統一齣生於新手村
#define _NEWMUSICFILE6_0			// (可開放) Syu ADD 6.0 新地圖音樂
#define _TRADESHOWNAME				// (可開放) Syu ADD 交易顯示對方名稱
#define _TRADEINPUTMONEY			// (可開放) Syu ADD 交易手動輸入金錢
#define _TRADE_SHOWHP				// (可開放) Syu ADD 交易顯示血量
#define _CHANGETRADERULE			// (可開放) Syu ADD 交易規則修訂
#define _PETSKILL_CANNEDFOOD		// (可開放) ANDY 寵物技能罐頭
#define _SPECIALSPACEANIM			// (可開放) Syu ADD 特殊場景動畫配置
#define _SHOOTCHESTNUT				// (可開放) Syu ADD 寵技：丟栗子
//#define _NEWLOGO				   // (可開放) Syu ADD 6.0登入畫麵新logo 要關_v4_0 
#endif		//SA_VERSION_60

#define _TRADESYSTEM2				// (可開放) Syu ADD 新交易係統

#ifdef _SA_VERSION_70
/* -------------------------------------------------------------------
* 新功能：石器7.0
* 更新日期
*/
//已開放
#define _SARS						// (可開放) WON ADD 毒煞蔓延
#define _FIX_MAXGOLD			    // (可開放) WON ADD 增加人物金錢上限

#define _ITEM_PILENUMS				// (可開放) ANDY 道具素材堆疊

#define _ITEM_EQUITSPACE			// (可開放) ANDY 新增裝備欄位
#define _EQUIT_ARRANGE				// (可開放) ANDY 格擋
#define _EQUIT_NEWGLOVE				// (可開放) ANDY 手套欄位

#define _LOCKPARTYFLOOR				// (可開放) Syu ADD 增加不可組隊的地圖編號
#define _LOCKHELP_OK				// (可開放) Syu ADD 鎖定不可加入戰鬥

#define _TRADETALKWND				// (可開放) Syu ADD 交易新增對話框架
#define _TRADELOCKBTN				// (可開放) Syu ADD 增加鎖定鍵

#define _WAVETRACK					// (可開放) Syu ADD 音波攻擊軌道修正

#define _CHAR_NEWLOGOUT				// (可開放) ANDY 新登齣機製

//新功能：人物職業
#define _TABLEOFSKILL				// (可開放) Syu ADD 7.0 新增人物技能錶單
//#define _NEWPANEL_71				// (可開放) ROG ADD 新login畫麵
//#define	_NEWPANEL_70				// (可開放) Syu ADD 石器7.0 LOGIN 畫麵
#define _CHAR_PROFESSION			// (可開放) WON ADD 人物職業
#define _SKILLSORT					// (可開放) Syu ADD 職業技能排列分類
#define _NEWREQUESTPROTOCOL			// (可開放) Syu ADD 新增Protocol要求能力細項
#define _OUTOFBATTLESKILL			// (可開放) Syu ADD 非戰鬥時技能Protocol
#define _NEWSOUNDEFFECT				// (可開放) Syu ADD 動畫音效檔
#define _FIXSTATUS					// (可開放) Syu ADD 新戰鬥狀態顯示方式
#define _ALLDOMAN					// (可開放) Syu ADD 排行榜NPC
#define _CHATROOMPROTOCOL			// (可開放) Syu ADD 聊天室頻道
#define _FRIENDCHANNEL				// (可開放) ROG ADD 好友頻道
#define	_TELLCHANNEL				// (可開放) ROG ADD 密語頻道

#define _DROPPETWND					// (可開放) Syu ADD 丟棄寵物確認

#define _MAILSHOWPLANET				// (可開放) Syu ADD 顯示名片星球
#define _MOON_FAIRYLAND				// (可開放) ROG ADD 月之仙境
#define _SPECIALSPACEANIM_FIX		// (可開放) ROG ADD 修正動畫
//#define _TIMEBAR_FUNCTION			// (不可開) ROG ADD 時間bar函式


//10/23
#define _FM_MODIFY				// 傢族功能修改

#define _FIREHUNTER_SKILL			// (可開放) ROG ADD 硃雀技能_火綫獵殺
#define _PETSKILL_ACUPUNCTURE       // (可開放) Change 寵技:針刺外皮
#define _PETSKILL_DAMAGETOHP	    // (可開放) Change 寵技:暗月狂狼(嗜血技的變體) 
#define _PETSKILL_BECOMEFOX         // (可開放) Change 寵技:媚惑術
#define _PETSKILL_BECOMEPIG         // (可開) Change 寵技:烏力化


// 新功能：連接新資料庫(新付費機製)
#define _NEW_WGS_MSG				// (可開) WON ADD WGS的新視窗


#define _CHANNEL_MODIFY		// 頻道功能整閤


#define _CHANGEGALAXY // Robin 星係移民
#define _ERROR301 // Robin AP迴傳301錯誤,産品尚未注冊

#define _STANDBYPET // Robin 送待機寵列錶到Server
#endif		//SA_VERSION_70


#define	DIRECTINPUT_VERSION 0x0700	// Robin 增加DirectX SDK的相容性

#define _CLOUD_EFFECT				// (不可開) ROG ADD	雲層效果
//#define _NPC_WELFARE_2			// (不可開) WON ADD 職業NPC-2

//#define _NPC_SELLSTH				// (可開放) ANDY 拍賣
//#define _SYUTEST
//#define _SYUTEST2
//#define _SYUTEST3
//#define _AUCPROTOCOL				// (不可開) Syu ADD 拍賣頻道開關Protocol

/* -------------------------------------------------------------------
* 新功能：PK服務器
* 更新日期
*/
//測試中
//製作中

//#define _PKSERVERCHARSEL			// (不可開) Syu ADD PK服務器選擇星係人物
// -------------------------------------------------------------------
// 以下不可開
/* -------------------------------------------------------------------
* 新功能：real.bin分圖
* 更新日期
*/
//測試中F
//#define _SAHOOK				    // (不可開) Syu ADD Hook程式
//#define _REALDIVISION			    // (不可開) Syu ADD real.bin分圖，要有realtxt.txt檔
// -------------------------------------------------------------------
//#define _OMIT_WGS					// (不可開) 略過帳號、密碼至WGS. code:shan
// -------------------------------------------------------------------
#ifdef _SA_VERSION_50
/* -------------------------------------------------------------------
* 新功能：石器5.0
* 說明：
*/
//#define _CANT_ATK					// (不可開) can't attack(own team). code: shan
//#define _SETTICK_COUNT			// (不可開) ANDY 重復發話
//#define _GM_MARK					// (不可開) WON ADD GM 識彆
//#define _GM_IDENTIFY		        // (不可開)Rog ADD GM識彆的gm指令

//#define _LOGINKICK				// (不可開) Syu ADD 登入畫麵超過30秒踢迴星係列錶
#endif		//SA_VERSION_50
#define MALLOC(s) malloc(s)
#define CALLOC(c,s) calloc(c,s)
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define FREE(p) free(p)

//#define _PET_TRACE_MOUSE
//#define __EDEN_DICE  				// (不可開) 賭場骰子
#define _AI_OTHER						// AI其它功能
#define __AI							// Cary 加入自動戰鬥功能
#ifdef _AI_OTHER
#define _AI_CAPTURE
#endif
//-----------------------
unsigned int TimeGetTime(void);

#ifdef _SA_VERSION_70
#ifdef _BACK_VERSION
#define _REMAKE_20						// 石器復刻功能控製(防外掛)
#define _BACK_LOGO
#define _BACK_WINDOW //復刻版視窗化(debug版纔可開,內部人員使用)
#define _READ16BITBMP					// Terry 可讀入及顯示高彩圖
#else
#define _ATTACK_AI						// 內掛攻擊AI
#define _AI_NEW_FIRST					// AI 首次可以用職業技能
#define _BATTLESKILL					// (可開放) Syu ADD 戰鬥技能介麵
#define _NEWPANEL						// (可開放) Syu ADD 7.0 新人物狀態介麵
#endif
#endif

#ifdef _SA_VERSION_75
/* -------------------------------------------------------------------
* 新功能：石器7.5
* 更新日期
*/

#define _ANGEL_SUMMON			// 天使的招喚 Robin
#define _PROFESSION_ADDSKILL  // (可開) Change 追加職業技能
#define _TRANS_6				// (可開) Change 人物6轉
#define _PET_2TRANS			// (可開) Change 寵物2轉
//#define _75_LOGIN					// 7.5版login畫麵 
#define _STREET_VENDOR		// 擺攤功能
#define _NEW_MANOR_LAW		// 新莊園規則

#define _PETSKILL_LER			// 雷爾技能
//#define _PK_SERVER            //百萬PK活動
//#define _8_TEST					//8.0測試server

// -------------------------------------------------------------------
// 專案：綫上迴報係統
// 人員：逸俊
// 說明：
//#define __ONLINEGM
//--------------------------------------------------------------------

#define _STREET_VENDOR_CHANGE_ICON	// 修改擺攤圖示

#define _TALK_WINDOW				// 對話視窗
#define _SHOW_FUSION				// (可開) Change 融閤寵物在CLIENT端隻顯示轉生數,修改為融閤寵顯示為融閤
#define _NPC_FUSION					// (□宮□) ANDY NPC□□芯シ

#define _FONT_SIZE					// Robin (要開) 可改字型大小
#define _CONTRACT					// Robin (要開) 契約功能
#define _HALLOWEEN_EFFECT			// 萬聖節特效
#define _ADD_STATUS_2				// 新增傳送人物狀態第二類
#define _PETSKILL_BATTLE_MODEL		// 寵物技能戰鬥模組
#define _RACEMAN					// cyg 獵寵大會新npc
#define _PETSKILL_ANTINTER			// (可開) Change 寵技:蟻之葬
#define _PETSKILL_EXPLODE			// (可開) Change 寵技:爆裂攻擊
#define _ITEM_FIREWORK				// 煙火功能
#define _FIREWORK_SOUND				// cyg 新增音效(煙火用)
#define _GET_HOSTNAME				// (可開) Change 取得電腦名稱
#define _SKILL_ADDBARRIER			// (可開) Change 寵技:為魔障增加異常抗性功能
#define _PETSKILL_PEEL				// (可開) Change 寵技:金蟬脫殼

//#define _MOUSE_DBL_CLICK			// Robin 滑鼠右鍵雙擊功能
#endif		//SA_VERSION_75

#ifdef _SA_VERSION_80
//--------------------------------------------------------------------------------------------------------
//專案 8.0 失落的世界 新加功能定義區 人員：彥勛 奇銓 曉威 逸俊
//--------------------------------------------------------------------------------------------------------
#define _PET_ITEM				// Terry 寵物可裝備道具
#define _NPC_PICTURE			// (可開) Change 新賭場功能(隨時變身的NPC)
#define _JOBDAILY				// cyg 任務日誌功能
#define _ITEM_PATH				// (可開) Change 可踏上不可走區域的道具
#define _ALCHEMIST				// Robin 精煉功能 
#define _ALCHEPLUS				// Robin 鑒定功能 
#define _EXTEND_AB				// cyg 擴充名片功能
#define _ITEM_INTENSIFY			// (可開) Change 寵技:強化道具
#define _TEACHER_SYSTEM			// Terry 導師係統
#define _ITEM_UPINSLAY			// (可開) Change 寵技:鑿孔(讓道具可鑲上更多寶石)
#define _MAG_MENU				// (可開) Change 魔法熟練度、抗性由文字顯示改為圖示化
#define _NPC_MAGICCARD			// cyg 魔法牌遊戲
#define _THEATER				// Terry 劇場功能
#define _MOVE_SCREEN			// Terry 移動熒幕到指定的座標
//	#define _80_LOGIN				// Terry 8.0 登入畫麵
#define _8_RIDEPETS				// (可開) Change 8.0騎寵
#define _8BATTLEMAP				// Change 8.0 戰鬥地錶
#define _PETKILL_COST_FAME		// Terry 寵物技能店學技能要花費聲望
#define _DRAGON_FUSION			// Robin 人龍進化

#define _MACADDRESSD			// (可開) Change get MAC card
#define _NEW_EARTH				// Terry 新地球,可看見內部服務器
//#define _80_LOGIN_PLAY		// Terry 8.0 登入畫麵
//----------------------------------------------------------------------

//#define _ITEM_JIGSAW			// (可開) Change 拼圖道具

#define _NPC_DANCE				// cyg 動一動npc
#define _ATTACK_EFFECT			// 角色攻擊完後會播放攻擊特效

//#define _2005_ValentineDay		// Terry 2005 情人節活動
#define _PETSKILL_ADDATTCRAZED	// (可開) Change 寵技:狂亂暴走增加功能
#define _PETSKILL_JUSTICE		// (可開) Change 寵技:審判
#define _CALLBUS				// (可開) Change 讓公車具有被呼叫的功能

//#define _NPC_ITEMUP				// (可開) Change 讓道具升級的NPC
//#define _ITEM_COUNTDOWN			// cyg 道具倒數功能

#define _PRO_KILLME				// Change 白狼職技  拾身誘敵
#define _PETSKILL_EVOLUTION		// (可開) Change 北極熊寵技:進化
#define _PETSKILL_PROVOKEFIGHT	// (可開) Change 犬年寵技:挑釁反擊
#define _FIX_ACUPUNCTURE		// (可開) Change 針刺外皮的修改
#define _PETSKILL_RIDE			// (可開) Change 寵技:上馬術

#endif		// _SA_VERSION_80

#ifdef _SA_VERSION_85
//--------------------------------------------------------------------------------------------------------
//專案 8.5 魔域大冒險 新加功能定義區 人員：奇銓 逸俊
//--------------------------------------------------------------------------------------------------------
#define _PRO_ABSOLUTE_DEFENSE	// (可開) Change 白狼職技  絕對防禦
#define _PRO3_ADDSKILL		// (可開) Change 追加8.5職業技能
#define _NPC_DAYACTION		// cyg 每日活動
#define _EVIL_KILL			// cyg 討伐魔軍係統
#define _HUNDRED_KILL			// cyg 百人無雙
#define _NEW_CLOUD			// (可開) Change 新的地圖的雲效果
//#define _85_LOGIN			// (可開) Change 8.5登入畫麵
//----------------------------------------------------------------------
#define _AI_SKILL_UPDATE		//新AI技能
#define _TEACHER_SYSTEM_2		// cyg 新導師係統
#endif
#endif


/*
新增宏增加
*/
#define _FIX_MAXGOLD			    // (可開放) WON ADD 增加人物金錢上限
#define _MOON_FAIRYLAND				// (可開放) ROG ADD 月之仙境
#define _SPECIALSPACEANIM_FIX		// (可開放) ROG ADD 修正動畫
#define _LOGINKICK					// (不可開) Syu ADD 登入畫麵超過30秒踢迴星係列錶
//#define _CHECK_GAMESPEED		    // (不可開) ANDY 檢測加速
#define _NEW_CLOUD					// (可開) Change 新的地圖的雲效果
#define _FIX_BATTLE_AI				// 修復戰鬥AI轉換的BUG
#define _WIN_LUAJIT_				//增加LUAJIT擴展功能     支持中文接口和中文路徑LUA文件
#define _NEW_COLOR_					//補丁支持16位RGB565高彩圖片
#define _NEW_WIN_POS_				//800窗口偏移設置
#define _NEW_ALPHA_					//新建半透明處理
//#define _CACHE_SURFACE_				//緩存錶麵
//#define _OPTIMIZATIONFLIP_  		//優化Flip
#define _KEY_  "AEB3A729E71F8870D4611FBDC01D0A4B"      //所有加密
//#define _NEWFONT_


#define _MO_SIGN_IN					//客戶端簽到按鈕
#define _CHANGE_HELP_BUTTON  		//修改幫助按鈕圖形
#define _PETCOM_					//寵物成長自動計算
#define _NEW_SPEED_					//新遊戲速度

#define _PETCOLOR_					//1級寵物變色
#define _PETKILL_COST_FAME			// Terry 寵物技能店學技能要花費聲
#define _AIDENGLU_					//自動登陸
#define _ZHENGSHIKAIFU_				//正式開服打開
#define _ZENGJIASHUO_				//增加一個鎖道具的圖標，同時被鎖的道具不能選中
#define _BUDING_ "554CDB1A99DF514B2F0B09DBDA0A6E9D"       //補丁加密
#define _TIME_GET_TIME				// 用QueryPerformanceCounter取代timeGetTime
#define _FAMILYBADGE_				//傢族徽章
#define _SHOWFAMILYBADGE_			//顯示傢族徽章
#define _NEWNET_					//新封包機製
//#define _LOGIP_					//登陸時獲取IP
//#define _SHOWIPSLEEP_				//顯示綫路延時
//#define _MEMORYLEAK_CHECK			//內存泄漏檢測
//#define _COMFIRM_TRADE_REQUEST		//交易請求確認
#define _DIEJIA_					//疊加功能
#define _FANILYTEXIAOY_  45			//傢族徽章偏移Y 越大則越靠窗口頂部
#define _OTHERTEXIAOY_  70			//其它圖標偏移Y 越大則越靠窗口頂部
#define _ATTACK_EFFECT				// 角色攻擊完後會播放攻擊特效
#define _SA_VERSION 'N'
#define _SA_MAC_VERSION_CONTROL		//MAC版本號控製
#define FAMILY_MANOR_				//莊園光環
#define _CHAR_MANOR_                //人物腳下光環
//#define _CHAR_MANOR_DEBUG                //人物腳下光環DEBUG
#define _ANNOUNCEMENT_				//公告係統
//#define _EFFECT_MAP_				//塔特效
#ifndef _DEBUG__
#define _VMP_						//VMP功能開啓
//#define _NODEBUG_					//反調試   測試的時候把這個屏蔽瞭，正式使用則把這個開啓
#else
#define _CMD_MODE					//調試模式
//#define _STONDEBUG__PACKET_       //調試封包
//#define _MO_SHOW_FPS				//顯示fps
#define _RELUA_						//DEBUG模式下啓用按個人信息則重讀LUA
#endif
#define SHOW_VERSION "www.shiqi.hk"
//#define _TRADE_BUG_LOG				//交易bug日誌
#define _SECONDARY_WINDOW_DATA_		//二級窗口內容
#define LABEL_STR_                 //標記重定義輸齣[普][密]

#ifdef _SA_VERSION_25
#define _DEFAULT_PKEY "shiqi"		// 默認的密鑰
#define _RUNNING_KEY  "shiqi.hk"		// 運行中密鑰
#define _SYSTEM_SLEEP_   6  //遊戲速度設置
#define _SURFACE_ANIM				// 動態地上物顯示
#define _DEFENSETOOENNUM_ 5			//限幾開
#define DENGLUKEY1 "6D27AEB8326A2A8E7D04B9F9B44C59C7"
#define _LEADERRIDE	 				   // (可開放) 四大傢族騎暴功能 Robin 0921
//#define _MO_IMAGE_EXTENSION			//形象擴展
#define _NEW_ITEM_					//新道具欄
#ifdef _WIN_LUAJIT_
#define _LUA_PATCH_ ".//lua"  //LUA路徑
#define _LUA_KEY_ "6A68673107B8C5B829815A507FF5C274"   //LUA加密密鑰
#endif
#define _MAGIC_ITEM_             //法寶功能
#define _ICONBUTTONS_				//轉盤
#define _BATTLE_TIME_  99000    
#define _PET_2TRANS			// (可開) Change 寵物2轉
#define _DEBUGVER_    "2.2"    //DEBUG版本號
#define _NEWSHOP_         //商城
#define _SHOWPETTRN_       //顯示寵物轉數
#ifdef _SA_MAC_VERSION_CONTROL
#define _SA_MAC_VERSION		"7sa2"
#endif
#define _CHANGETEAM_                //隊長切換
#define SA_MUTE      "sa25.exe"
#define _NEW_CHARDATA_				//新人物資料
#define _PETBLESS_					//寵物祝福
#define _RIDEPET_					//騎寵開關
#define DEF_APPNAME		"STONEAGE"	// 遊戲標題
#define _RIDEQUERY_					//騎寵查詢
#define _CHAT_SPACING 24            //聊天行距設置 20
#define __EMOTION			//Cary 特殊的錶情，隻做client
//#define _PET_SKINS					//寵物皮膚
#define _PET_2TRANS			// (可開) Change 寵物2轉
#define	_NPC_EVENT_NOTICE			//npc任務信息提示
#define _SHOWPETTRN_       //顯示寵物轉數
//#define _PET_VAL_COLOR_             //寵物屬性上色
#define _MO_CHAT_EXPRESSION			//聊天錶情功能
#define _SA_LIAOTIAN_				//聊天刪減按鈕
#define _CHARTITLE_STR_             //文字稱號     該稱號開啓,圖形稱號失效
#define _FONT_STYLE_                //文字樣式解析
#define _MESSAGE_FRONT_             //聊天信息前麵加個符號
#define _TRADITIONAL_LONG_         //繁體係統創建人物登陸
#define _FONTDATALEN_ 100           //聊天信息長度 112
#define MAX_AIRPLANENUM				8
#define _FIX_CG_ATR_ICON
#define _PETSKILL_LER
//#define _CANCEL_FANTI				//取消繁體切換
//#define _RED_MEMOY_				//紅包
#endif

#ifdef _MO_CHAT_EXPRESSION
#define CG_FIELD_CHAT_BTN_ON					55102
#define CG_FIELD_CHAT_BTN_OFF					55102
//#define EXPRESSION_NOID_START                   55300 //錶情地圖號起始ID
//#define EXPRESSION_NOID_END                     55421 //錶情地圖號結束ID
#define EXPRESSION_NOID_START                   55117 //錶情地圖號起始ID
#define EXPRESSION_NOID_END                     55215 //錶情地圖號結束ID
#define EXPRESSION_NOID_NUM       EXPRESSION_NOID_END-EXPRESSION_NOID_START
#define	_SUNDAY_STR_SEARCH			//SUNDAY字符串搜索算法  比KMP更牛速度更快的算法
#endif

