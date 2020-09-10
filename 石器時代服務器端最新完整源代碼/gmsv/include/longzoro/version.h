#ifndef __ALLBLUES_H__
#define __ALLBLUES_H__

#include "longzoro.h"


//私服版本控製----------------------------------------

#if _ATTESTAION_ID == 1
	#define _VERSION_NEW
	#define _VERSION_NEW60
//#define _VERSION_GF
#define _VERSION_60
#define _VERSION_80
//#define _NEW_SA80                // 新石器8.0
#else
#if _ATTESTAION_ID == 2
	#define _VERSION_25
#else
	#define _VERSION_80
#endif
#endif


#ifdef _VERSION_80
	#if _ATTESTAION_ID == 0 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 23 || _ATTESTAION_ID == 28 || _ATTESTAION_ID == 29 || _ATTESTAION_ID == 30 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 32 || _ATTESTAION_ID == 33 || _ATTESTAION_ID == 34 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 36 || _ATTESTAION_ID == 37 || _ATTESTAION_ID >= 39
		#if  _ATTESTAION_ID != 49
			#define _NEW_SA80                // 新石器8.0
		#endif
	#endif
	
	#ifdef _NEW_SA80
		#if _ATTESTAION_ID != 43
			#define _ONLINE_SHOP             // 8.0在線商城
		#endif
		#define _ONLINE_TALK_IP          // 玩傢舉報
		#define _ONLINE_TALK_GM          // 在線聯係GM
		#define _NEW_ONLINE_SHOP         // 新在線商城
	#endif
	#define _ANGLE_EMAIL             // 精召後自動交換名片
#endif

#ifdef _VERSION_NEW
	#define _CHATROOMPROTOCOL        // (可開放) Syu ADD 聊天室頻道 8/27
	#define _OBJSEND_C               // (可開放) ANDY _OBJSEND_C
	#define _ADD_SHOW_ITEMDAMAGE     // (可開放) WON  顯示物品耐久度
	#define _CHANGETRADERULE         // (可開放) Syu ADD 交易規則修訂
	#define _TRADE_SHOWHP            // (可開放) Syu ADD 交易顯示血量
	#define _TRADESYSTEM2            // (可開放) Syu ADD 新交易係統
	#define _NPC_MAKEPAIR            // (可開放) ANDY NPC 配對
	#define _ITEM_PILENUMS           // (可開放) ANDY 道具素材堆疊 需 itemset4
	#define _ITEM_PILEFORTRADE       // (可開放) ANDY 交易堆疊
	#define _ITEM_EQUITSPACE         // (可開放) ANDY 新裝備欄位
	#define _EQUIT_ARRANGE           // (可開放) ANDY 擋格 需要 itemset5.txt
	#define _EQUIT_ADDPILE           // (可開放) ANDY 增加可堆疊數 需要 itemset5.txt
	#define _EQUIT_NEWGLOVE          // (可開放) ANDY 手套欄位
	// 新功能：職業
	#define _NEWREQUESTPROTOCOL      // (可開放) Syu ADD 新增Protocol要求細項
	#define _OUTOFBATTLESKILL        // (可開放) Syu ADD 非戰鬥時技能Protocol
	#define _NPC_ADDLEVELUP          // (可開放) ANDY NPC增加玩傢等級
	#define _CHAR_NEWLOGOUT          // (可開放) ANDY 登出新機製
	#define _NPC_ProfessionTrans     // (可開) Change 替職業NPC加入判斷轉生
	#define _CHANNEL_MODIFY          // 頻道功能整閤(開放)
	//--------------------------------------------------------------------------
	#define _STREET_VENDOR           // 擺攤功能(開放)
	#define _WATCH_EVENT             // 查詢任務功能(開放)
	#define _ADD_DUNGEON             // (可開) Change 追加地牢
	#define _ADD_STATUS_2            // 新增傳送人物狀態第二類
	#define  _ALCHEMIST              // Robin 精  功能
	#define _JOBDAILY                // cyg 任務日誌功能
	#define _FONT_SIZE               // (可開) Robin 字型大小功能
	#define _PETSKILL_FIXITEM        // (可開放) ANDY 修復 && 同道具損壞
	#define _CHECK_ITEMDAMAGE        // (可開放) 道具損壞修正  7/26
	#define _TEAM_KICKPARTY          // (可開放) ANDY 隊長踢人(非戰鬥狀態)
	#define _TELLCHANNEL             // (可開放) Syu ADD 密語頻道
	#define _EMENY_CHANCEMAN         // (可開放) ANDY EMENY 選擇
	#define _STANDBYPET              // Robin 待機寵封包
	#define _CHAR_POOLITEM           // (可開放) ANDY 人物道具倉庫共用
	#define _CHAR_POOLPET            // (可開放) Robin 人物寵物倉庫共用
	#define _NPC_DEPOTPET            // (可開放) Robin 人物寵物倉庫共用
	#define _NPC_DEPOTITEM           // (可開放) ANDY 人物道具倉庫共用
	#define _NEW_MANOR_LAW           // 新莊園規則(開放)
	#define _CHANNEL_MODIFY          // 頻道功能整閤(開放)
	#define _TAKE_ITEMDAMAGE         // (可開放) ANDY 道具損壞  ITEMSET2
#ifdef _VERSION_NEW60
	#define _SKILL_NOCAST            // (可開放) vincent  寵技:沉默 //需要開#define _MAGIC_NOCAST
	#define _PET_FUSION              // (可開放) ANDY 寵物融合 enemybase1.txt
	#define _NPC_FUSION              // (可開放) ANDY NPC寵物融合
	#define _ITEM_EDITBASES          // (可開放) ANDY 營養劑
	#define _PET_EVOLUTION           // (可開放) ANDY 進化錶
	#define _STATUS_WATERWORD        // (可開放) ANDY 水世界狀態
	#define _ITEM_WATERWORDSTATUS    // (可開放) ANDY 水世界狀態道具
	#define _PETSKILL_ACUPUNCTURE    // (可開放) Change 寵技:針刺外皮 (client端的_PETSKILL_ACUPUNCTURE也要開)
	#define _SHOW_FUSION             // (可開) Change 融合寵物在CLIENT端隻顯示轉生數,修改為融合寵顯示為融合(client端也要開)
	#define _TREASURE_BOX            // (可開放) ANDY 寶箱
	#define _SHOOTCHESTNUT           // (可開放) Syu ADD 寵技：丟栗子
#endif

#endif

#ifdef _VERSION_60
	#define _PETSKILL_FIXITEM        // (可開放) ANDY 修復 && 同道具損壞
	#define _CHECK_ITEMDAMAGE        // (可開放) 道具損壞修正  7/26
	#define _TAKE_ITEMDAMAGE         // (可開放) ANDY 道具損壞  ITEMSET2
	#define _SKILL_NOCAST            // (可開放) vincent  寵技:沉默 //需要開#define _MAGIC_NOCAST
	#define _EMENY_CHANCEMAN         // (可開放) ANDY EMENY 選擇
	#define _PET_FUSION              // (可開放) ANDY 寵物融合 enemybase1.txt
	#define _NPC_FUSION              // (可開放) ANDY NPC寵物融合
	#define _ITEM_EDITBASES          // (可開放) ANDY 營養劑
	#define _PET_EVOLUTION           // (可開放) ANDY 進化錶
	#define _TEAM_KICKPARTY          // (可開放) ANDY 隊長踢人(非戰鬥狀態)
	#define _STATUS_WATERWORD        // (可開放) ANDY 水世界狀態
	#define _ITEM_WATERWORDSTATUS    // (可開放) ANDY 水世界狀態道具
	#define _TELLCHANNEL             // (可開放) Syu ADD 密語頻道
	#define _PETSKILL_ACUPUNCTURE    // (可開放) Change 寵技:針刺外皮 (client端的_PETSKILL_ACUPUNCTURE也要開)
	#define _SHOW_FUSION             // (可開) Change 融合寵物在CLIENT端隻顯示轉生數,修改為融合寵顯示為融合(client端也要開)
	#define _FONT_SIZE               // (可開) Robin 字型大小功能
	#define _TREASURE_BOX            // (可開放) ANDY 寶箱
	#define _DP_NPC                  // DP腳本
	#define _SHOOTCHESTNUT           // (可開放) Syu ADD 寵技：丟栗子
#endif

#ifdef _VERSION_80
	#define _PETSKILL_FIXITEM        // (可開放) ANDY 修復 && 同道具損壞
	#define _CHECK_ITEMDAMAGE        // (可開放) 道具損壞修正  7/26
	#define _TAKE_ITEMDAMAGE         // (可開放) ANDY 道具損壞  ITEMSET2
	#define _SKILL_NOCAST            // (可開放) vincent  寵技:沉默 //需要開#define _MAGIC_NOCAST
	#define _EMENY_CHANCEMAN         // (可開放) ANDY EMENY 選擇
	#define _PET_FUSION              // (可開放) ANDY 寵物融合 enemybase1.txt
	#define _NPC_FUSION              // (可開放) ANDY NPC寵物融合
	#define _ITEM_EDITBASES          // (可開放) ANDY 營養劑
	#define _PET_EVOLUTION           // (可開放) ANDY 進化錶
	#define _TEAM_KICKPARTY          // (可開放) ANDY 隊長踢人(非戰鬥狀態)
	#define _STATUS_WATERWORD        // (可開放) ANDY 水世界狀態
	#define _ITEM_WATERWORDSTATUS    // (可開放) ANDY 水世界狀態道具
	#define _TELLCHANNEL             // (可開放) Syu ADD 密語頻道
	#define _PETSKILL_ACUPUNCTURE    // (可開放) Change 寵技:針刺外皮 (client端的_PETSKILL_ACUPUNCTURE也要開)
	#define _SHOW_FUSION             // (可開) Change 融合寵物在CLIENT端隻顯示轉生數,修改為融合寵顯示為融合(client端也要開)
	#define _FONT_SIZE               // (可開) Robin 字型大小功能
	#define _TREASURE_BOX            // (可開放) ANDY 寶箱
	#define _DP_NPC                  // DP腳本
	
	//#define _PREVENT_TEAMATTACK      // (可開放) ANDY 防止同隊互打 12/04 更新
	#define _OBJSEND_C               // (可開放) ANDY _OBJSEND_C
	#define _ADD_SHOW_ITEMDAMAGE     // (可開放) WON  顯示物品耐久度
	#define _CHANGETRADERULE         // (可開放) Syu ADD 交易規則修訂
	#define _TRADE_SHOWHP            // (可開放) Syu ADD 交易顯示血量
	#define _SHOOTCHESTNUT           // (可開放) Syu ADD 寵技：丟栗子
	#define _SKILLLIMIT              // (可開放) Syu ADD 不得攻擊我方限製
	#define _TRADESYSTEM2            // (可開放) Syu ADD 新交易係統
	#define _NPC_MAKEPAIR            // (可開放) ANDY NPC 配對
	#define _ITEM_PILENUMS           // (可開放) ANDY 道具素材堆疊 需 itemset4
	#define _ITEM_PILEFORTRADE       // (可開放) ANDY 交易堆疊
	#define _ITEM_EQUITSPACE         // (可開放) ANDY 新裝備欄位
	#define _EQUIT_ARRANGE           // (可開放) ANDY 擋格 需要 itemset5.txt
	#define _EQUIT_ADDPILE           // (可開放) ANDY 增加可堆疊數 需要 itemset5.txt
	#define _EQUIT_NEWGLOVE          // (可開放) ANDY 手套欄位
	// 新功能：職業
	#define _NEWREQUESTPROTOCOL      // (可開放) Syu ADD 新增Protocol要求細項
	#define _OUTOFBATTLESKILL        // (可開放) Syu ADD 非戰鬥時技能Protocol
	#define _CHAR_PROFESSION         // (可開放) WON ADD 人物職業欄位
	#define _PROFESSION_SKILL        // (可開放) WON ADD 人物職業技能
	#define _NPC_WELFARE             // (可開放) WON ADD 職業NPC
	#define _NPC_ADDLEVELUP          // (可開放) ANDY NPC增加玩傢等級
	#define _CHAR_NEWLOGOUT          // (可開放) ANDY 登出新機製
	#define _CHATROOMPROTOCOL        // (可開放) Syu ADD 聊天室頻道 8/27
	#define _CHAR_POOLITEM           // (可開放) ANDY 人物道具倉庫共用
	#define _CHAR_POOLPET            // (可開放) Robin 人物寵物倉庫共用
	#define _NPC_DEPOTPET            // (可開放) Robin 人物寵物倉庫共用
	#define _NPC_DEPOTITEM           // (可開放) ANDY 人物道具倉庫共用
	#define _NPC_ProfessionTrans     // (可開) Change 替職業NPC加入判斷轉生
	#define _CHANNEL_MODIFY          // 頻道功能整閤(開放)
	#define _STANDBYPET              // Robin 待機寵封包
	#define  _PROSKILL_OPTIMUM       // Robin 職業技能處理最佳化
	//2004/05/12
	
	#define _MAGIC_RESIST_EQUIT      // (可開) WON ADD 職業抗性裝備
	#define _ALLDOMAN                // (可開放) Syu ADD 排行榜NPC
	#define _ALLDOMAN_DEBUG          // (可開) Change 修正重啓server後排行榜消失bug
	// -------------------------------------------------------------------
	// 新功能：GM密頻功能擴充
	//復刻版
	#define _REDHAT_V9               //(可開) Change 在REDHAT9.0的版本下編譯時打開
	//--------------------------------------------------------------------------
	#define _NPC_EXCHANGEMANTRANS    // (可開) Change 替exchangeman加入判斷轉生
	#define  _ANGEL_SUMMON           // Robin 天使召喚
	#define _STREET_VENDOR           // 擺攤功能(開放)
	#define _WATCH_EVENT             // 查詢任務功能(開放)
	#define _NEW_MANOR_LAW           // 新莊園規則(開放)
	#define _PETSKILL_LER            // 雷爾技能(開放)
	#define _FIX_MAGIC_RESIST        // (可開) Change 職業魔法抗性
	#define _ADD_DUNGEON             // (可開) Change 追加地牢
	#define _PROFESSION_ADDSKILL     // (可開) Change 追加職業技能
	#define _EQUIT_RESIST            // (可開) Change 單一裝備抗性(可抗單一功能異常狀態)有抗火 雷 冰 虛弱 魔障 沉默 落馬
	#define _PROSK99                 // (可開) Change 檢查職技等級送白狼
	#define _ADD_STATUS_2            // 新增傳送人物狀態第二類
	#define _SUIT_ADDPART4           // (可開) Change 套裝功能第四彈 中毒攻擊% 加強法師魔法(機率30%) 抵抗法師的魔法


	#define _ITEM_TYPETABLE          // (可開) Change 追加typetable
	#define _RIGHTCLICK              // Robin 滑鼠右鍵功能
	#define _JOBDAILY                // cyg 任務日誌功能
	#define  _ALCHEMIST              // Robin 精  功能
	#define _TEACHER_SYSTEM          // 導師係統(開放)
	#define _PET_ITEM                // 寵物裝備
#endif


//普通版新增功能-------------------------------------
#define _PUB_ALL
#ifdef _PUB_ALL
	//#define _PROSKILL_ERR_KICK       // 非法技能自動T下綫
	#define _ITEM_SETLOVER           // 結婚功能
	#define _CREATE_MM_1_2           // 製作極品瑪蕾菲雅
	#define _SendTo                  // 傳送到玩傢身邊
	#define _GET_BATTLE_EXP          // 經驗設置
	#define _NEW_PLAYER_CF           // 新手狀態設置
	#define _USER_EXP_CF             // 用戶自定義經驗
	#define _TRANS_LEVEL_CF          // 轉生超越160級設置
	#define _UNLAW_WARP_FLOOR        // 禁止傳送地區
	#define _UNREG_NEMA              // 禁止人物名稱
	#if _ATTESTAION_ID != 1
		#define _GM_ITEM                 // 玩傢GM命令物品
	#endif
	#define _GM_METAMO_RIDE          // GM人物騎所有寵
	#ifdef _NEW_RIDEPETS
		#define _GM_RIDE                 // GM命令設置騎寵權限
	#endif
	#define _LOCK_IP                 // 鎖定IP
	#define _POINT                   // 點數上限
	#define _VIP_SERVER              // 會員服務
	#define _WATCH_FLOOR             // 自定義可觀戰地圖
	#define _BATTLE_FLOOR            // 自定義強制戰鬥地圖
	#define _VIP_SHOP                // 會員商店
	#if _ATTESTAION_ID != 1
		#define _LOOP_ANNOUNCE           // 循環公告
	#endif
	#define _SKILLUPPOINT_CF         // 自定義升級點數
	#define _RIDELEVEL               // 自定義騎寵相差等級
	#define _REVLEVEL                // 自動還原等級
	#define _FM_ITEM                 // 聲望道具
	#define _LUCK_ITEM               // 運氣道具
	#define _NEW_PLAYER_RIDE         // 新手送配套騎寵
	#define _FIX_CHARLOOPS           // 修正惡魔寶石遇敵時間
	#if _ATTESTAION_ID != 1
		#define _PLAYER_ANNOUNCE         // 玩傢喇叭
	#endif
	#define _BATTLE_GOLD             // 獲取經驗同時獲得金錢
	#define _ITEM_GOLD               // 金錢大物品
	#define _PLAYER_NUM              // 玩傢在線人數
	#define _PET_MM                  // 獲得滿石MM
	#define _MYSTERIOUS_GIFT         // 神秘禮物
	#define _RELOAD_CF               // 重讀CF
	#define _PET_AND_ITEM_UP         // 可撿彆人丟出的寵物或道具
	#define _TRANS                   // 人物轉生命令
	#ifdef _NEW_RIDEPETS
		#define _RIDEMODE_20             // 2.0騎寵模式
	#endif
	#define _TALK_ACTION             // 說話動作
	#define _ENEMY_ACTION            // 玩傢步行遇敵機率
	#define _CHAR_CDKEY              // 防止串號問題
//	#define _GMSV_DEBUG              // GMSV調試信息
	#define _CHECK_PEPEAT            // 非法寵物檢查
	#define _SILENTZERO              // 黃蓮物品
	#define _SAVE_GAME_ID            // 顯示保存的服務器名
#endif

//會員版追加功能--------------------------------------
#define _VIP_ALL
#ifdef _VIP_ALL
	#define _NEW_RIDEPETS            // (可開放) ANDY 新騎寵
	#define _RIDEMODE_20             // 2.0騎寵模式
	#define _VIP_RIDE                // 會員騎黑雞
	#define _AUTO_PK                 // 自動化PK係統
	//#define _FM_METAMO               // 家族專用變身戒指
	#define _ITEM_METAMO_TIME        // 可自定義變身的戒指
	#define _SHOW_VIP_CF             // 自定義調整VIP，愛人，家族，名稱顯示樣式
	#define _GM_KING                 // GM大魔王
	#define _ANGEL_TIME              // 自定義精靈召喚時間
	#define _FM_POINT_PK             // 莊園家族互搶莊園
	#if _ATTESTAION_ID != 1
		#define _PLAYER_MOVE             // 玩傢順移功能
	#endif
	#define _BATTLE_PK               // 強制PK道具，輸了迴記錄點
	#ifdef _PET_FUSION
		#define _FUSIONBEIT_TRANS        // 融合寵物轉生
		#define _FUSIONBEIT_FIX          // 取消融合寵的限製
	#endif
	#define _TRANS_7_NPC             // 人物七轉NPC
	#ifdef _NEW_MANOR_LAW
		#define _MOMENTUM_NPC            // 氣勢腳本
	#endif
	
	#ifdef _NEW_RIDEPETS
		#define _RIDE_CF                 // 自定義騎寵
		#define _FM_LEADER_RIDE          // 族長專用騎寵
	#endif
	#define _PET_LEVEL_ITEM          // 寵物等級提升物品
	//#define _DBSAVE_CHAR             // 雙嚮存檔
	#define _FM_JOINLIMIT            // 退族後再次加入家族的時間限製
	#define _PET_BEATITUDE           // 寵物祝福
	#define _ITEM_EFMETAMO           // 永久變身戒指
	#define _ITEM_RIDE               // 馴騎裝備
	#define _MAKE_MAP                // 地圖製作
	#define _MAKE_PET_CF             // 自定義寵物成長
	#define _MAKE_PET_ABILITY        // 自定義寵物四圍
	#define _GET_MULTI_ITEM          // 一次給多件物品
	#define _RE_GM_COMMAND           // 自定義GM命令設置
	#define _ONLINE_TIME           // 在線時間
	#define _NPC_INT_SET           // NPC整型設置
	#define _VIP_ONLINE              // 會員上綫提示

#endif

#if _ATTESTAION_ID != 9 && _ATTESTAION_ID != 11
	#define _LOGNZORO_FUNC_ALL       // 龍zoro新增功能
#else
	#define _NEW_VIP_SHOP            // 會員商店(需SAAC配閤)
	#define _ONLINE_COST             // 在線充值(需SAAC配閤)
	#define _NULL_CHECK_ITEM         // 空頭支票道具
	#define _COST_ITEM               // 充值道具
	#define _CRYPTO_DATA             // 服務端數據加密係統
#endif
#ifdef _LOGNZORO_FUNC_ALL
	#if _ATTESTAION_ID != 1
		#define _TRANS_7_SHOW            // 人物7轉顯示
	#endif
	#define _ITEM_COLOER             // 物品顔色調配
	#define _TALK_MOVE_FLOOR         // 說話移動功能
	#ifdef _TRADESYSTEM2
		#define _TRADE_PK                // 交易PK
	#endif
	#if _ATTESTAION_ID != 1
		#define _VIP_POINT_PK            // 積分點PK
	#endif
	#define _MAP_HEALERALLHEAL       // 指定地圖戰鬥後自動迴復體力
	#if _ATTESTAION_ID != 1
		#define _NEW_AUTO_PK             // 新的自動化PK係統
	#endif
	#define _OPEN_E_PETSKILL         // 開放寵物E技能
	#if _ATTESTAION_ID != 1
		#define _VIP_ONLINE              // 會員上綫提示
	#endif
	#define _VIP_LOGOUT              // 會員最後離綫時間提示
	#if _ATTESTAION_ID != 1
		#define _THE_WORLD_SEND          // 世界說話頻道
	#endif
#define _THE_WORLD_SEND          // 世界說話頻道
	#define _SUPER_FLOOR_MIC         // 地圖麥剋風
	#define _NPC_GET_PETABI          // NPC給自定義成長的寵物
	#define _SAMETHING_SAVEPOINT     // 玩傢某些事件自動存檔
	#define _NEW_VIP_SHOP            // 會員商店(需SAAC配閤)
	#if _ATTESTAION_ID != 8 && _ATTESTAION_ID != 10 && _ATTESTAION_ID != 21 
		#define _ITEM_PET_LOCKED         // 物品寵物鎖(需SAAC配閤)
	#endif
	#define _ONLINE_COST             // 在線充值(需SAAC配閤)
	#if _ATTESTAION_ID != 3
		#define _VIPPOINT_OLD_TO_NEW     // 積分點舊轉新(需SAAC配閤)
	#endif
	#define _LOGIN_DISPLAY           // 玩傢上綫提示開關
	//#define _NEED_ITEM_ENEMY         // 抓寵所需物品自定義
	#define _SUPER_MAN_ITEM          // 極品人道具
	#define _AUTO_DEL_PET            // 自動刪除寵物
	#define _AUTO_DEL_ITEM           // 自動刪除物品
	#define _POOL_ITEM_BUG           // 禁止強存的BUG
	
	#if _ATTESTAION_ID != 5
		#if _ATTESTAION_ID != 1
			#define _BOUND_TIME              // 玩傢包時功能
		#endif
		#define _SPECIAL_MAP             // 特殊地圖
		#ifdef _FONT_SIZE
			#define _TALK_SIZE_ITEM          // 大聲公道具
		#endif
		#define _NEW_NAME                // 自定義稱號
		#define _CRYPTO_DATA             // 服務端數據加密係統
		#ifdef _NEW_VIP_SHOP
			#define _COST_ITEM             // 充值道具
		#endif
		#define _ITEM_EXP                // 神奇藥水(經驗道具)
		#define _NULL_CHECK_ITEM         // 空頭支票道具
		#define _MEMORY_ITEM             // 記憶戒指
		#define _NPC_SCRIPT              // NPC腳本包
		//#define _BT_PET                  // BT寵物倍數設置
		#define _BT_ITEM                 // BT物品倍數設置
		#define _NO_JOIN_FLOOR           // 禁止傳送地區
		#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 4 || _ATTESTAION_ID == 6 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 10 || _ATTESTAION_ID == 14 || _ATTESTAION_ID == 15 || _ATTESTAION_ID == 17 || _ATTESTAION_ID >= 19
			#ifdef _STREET_VENDOR
				#define _NEW_STREET_VENDOR       // 新擺攤功能
			#endif
		#endif

		#if _ATTESTAION_ID != 1 && _ATTESTAION_ID != 18
			#define _LUCK_STAR               // 幸運星(隨機隨時給隨機玩傢隨機物品或寵物)
		#endif
		#if _ATTESTAION_ID != 1 
			#define _BT_ITEM                 // BT物品倍數設置
		#endif
		#ifdef _CHATROOMPROTOCOL
			#define _NPC_SAVEPOINT           // 紀錄點存人物資料
		#endif
		#define _SPECIAL_SUIT            // 特殊套裝
		#define _MANOR_EQUIP             // 莊園專屬套裝
		#define _ITEM_UPLEVEL            // 裝備升級
		#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 4 || _ATTESTAION_ID == 6 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 10 || _ATTESTAION_ID == 14 || _ATTESTAION_ID == 15 || _ATTESTAION_ID >= 17
			//#define _TRANS_POINT_UP          // 每轉點數上限
			#if _ATTESTAION_ID != 8
				#if _ATTESTAION_ID != 1 
					#define _FIND_TREASURES          // 尋找寶物
				#endif
				#define _UNLAW_THIS_LOGOUT       // 禁止原登
				#define _ITEM_PERCENTAGE         // 設置物品百分比
			#endif
			#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 4 || _ATTESTAION_ID == 6 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 10 || _ATTESTAION_ID == 14 || _ATTESTAION_ID == 17 || _ATTESTAION_ID >= 20 
				#define _ITEM_POOLITEM           // 隨身道具倉庫
				#define _ITEM_POOLPET            // 隨身寵物倉庫
				#define _ADD_NEWEVENT_1024       // 增加旗標至1024
				#define _SUPER                   // 紫雲端的垃圾功能支持
				#define _NEW_SKILL               // 新技能開發
				#if _ATTESTAION_ID != 1
					#define _NEW_GM_ITEM             // 新玩傢GM命令物品
				#endif
				#define _SHOW_PET_ABL            // 顯示寵物能力
				#define _NEWEVENT_ITEM           // 新增任務道具
				#ifdef _NEW_RIDEPETS
					#define _ADD_RIDE_CF             // 增加自定義騎寵設置
				#endif
				#define _NO_STW_ENEMY            // 禁止外掛快速遇敵
				#define _NEW_PET_BEATITUDE       // 新一代寵物祝福
				#define _BATTLE_GETITEM_RATE     // 戰鬥獲得物品機率
				#define _INSLAY_NOT_PILENUMS     // 不能精工疊加物品
				#if _ATTESTAION_ID == 14 || _ATTESTAION_ID == 28
					#define _ONLINE_TIME           // 在線時間
					#define _NPC_INT_SET           // NPC整型設置
				#endif
				#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 4 || _ATTESTAION_ID == 6 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 14 || _ATTESTAION_ID == 20 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 23 || _ATTESTAION_ID >= 25
					#if _ATTESTAION_ID != 1 || _ATTESTAION_ID != 25 
						#define _TALK_SAVE               // 說話存檔
						#define _PLAYER_QUESTION_ONLIEN  // 玩傢在線答題
					#endif
				#endif
				#if _ATTESTAION_ID == 28
					#define _LOTTERY_SYSTEM          // 彩票係統
					#define _NPC_CHECK_SCRIPT          // 判斷腳本包
				#endif
				#if _ATTESTAION_ID == 38
					//#define _PET_TRANS_ABILITY       // 寵物轉生能力定義上限
				#endif
				#if _ATTESTAION_ID != 38 && _ATTESTAION_ID != 49
					#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 8 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 23 || _ATTESTAION_ID >= 30
						#define _OLYMPIC_TORCH           // 奧林匹剋火舉
						#if _ATTESTAION_ID != 1
							#define _LOTTERY_SYSTEM          // 彩票係統
							#define _PLAYER_DIY_MAP          // 玩傢DIY地圖功能
						#endif
						#define _AMPOINT_LOG             // 積分點記錄
						#define _SQL_VIPPOINT_LOG        // 重迴幣記錄
						#define _NPC_CHECK_SCRIPT        // 判斷腳本包
						#define _TALK_CHECK              // 說話驗證
						#define _ONE_PET_SKILL           // 一次性寵技
						#define _MAGIC_SPECIAL           // 特殊魔法
						#if _ATTESTAION_ID != 1 
							#define _BATTLE_PK_TYPE          // PK類型選擇
						#endif
						#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 23 || _ATTESTAION_ID >= 31
							#if _ATTESTAION_ID != 1
								#define _NPC_AUTO_MOVE			   // 能夠自已移動的NPC
							#endif
							#define _SYSTEM_SPEAD          // 係統加速  暫不開放，會影響戰鬥掛機
							#define _FILTER_TALK    		   // 過濾說話
							#if _ATTESTAION_ID != 34
									#define _ALL_SERV_SEND       // 星球頻道
									#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 32 || _ATTESTAION_ID == 33 || _ATTESTAION_ID >= 35 || _ATTESTAION_ID != 39
										#define _PET_TRANS_ABILITY       // 寵物轉生能力定義上限
										#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 32 || _ATTESTAION_ID == 35 || _ATTESTAION_ID >= 45
											#define _CANCEL_ANGLE_TRANS      // 取消精靈召喚
										#endif
										#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 33 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 36 || _ATTESTAION_ID == 37 || _ATTESTAION_ID == 40 || _ATTESTAION_ID >= 43
											#define _COMPOUND_EXP          // 閤成經驗
											#define _ASSESS_ABILITY        // 評定能力
											#define _ONLINE_TIME           // 在線時間
											#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 37 || _ATTESTAION_ID >= 43
												#ifndef _VERSION_25
													#define _PAUCTION_MAN          // 拍賣係統
												#endif
											#endif
											#define _NOT_ESCAPE          	 // 禁止逃跑
											#define _PLAYER_OVERLAP_PK     // 玩傢重疊時PK
											#define _FIMALY_PK_TIME        // 家族開片時間設定
										#endif
									#endif
							#endif
						#endif
					#endif
				#endif
			#endif
		#endif
	#else
		#define _FORMULATE_AUTO_PK       // 製定自動化PK係統(需SAAC配閤)
	#endif
	
	#ifdef _MAGIC_SPECIAL
//		#define _MAGIC_FEATHERS          // 魔法羽毛
	#endif
	
	#ifdef _TALK_CHECK
		#define _NPC_TALK_CHECK          // NPC說話驗證
		#define _ITEM_TALK_CHECK         // 道具說話驗證
	#endif
	
	#ifdef _NPC_SCRIPT
		#define _NPC_CHECKTIME           // NPC時間判斷
		#define _FAME_CHECK_NPC          // NPC聲望判斷
		#define _SQL_BUY_FUNC            // SQL購買功能
		#define _DEL_FAME                // 扣減聲望
		#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 36 || _ATTESTAION_ID == 37 || _ATTESTAION_ID == 40 || _ATTESTAION_ID >= 43
			#define _NPC_INT_SET             // NPC整型設置
		#endif
	#endif

	#ifdef _NEW_SKILL
		#define _ITEM_ATTSKILLMAGIC      // (可開放) ANDY 道具技能
		#define _MASSAGE_PETSKILL        // 馬殺雞技能
		#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 23 || _ATTESTAION_ID >= 30
			#define _EXPANSION_ITEM_INSLAY      // 擴展鑲寶石
			#define _STRENGTH_PETSKILL          // 元氣寵技
			#define _EXPANSION_POWERBALANCE     // 擴展PETSKILL_PowerBalance
			#define _RESURRECTION_PETSKILL      // 復活寵技
			#define _LOSTLOST_PETSKILL          // 兩敗俱傷
			#define _GRAPPLING_PETSKILL         // 擒拿手
			#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 23 || _ATTESTAION_ID >= 31
				#define _PETSKILL_EXPLODE		        // (不可開) Change 寵技:爆裂攻擊
				#define _PETOUT_PETSKILL		        // 換休息寵技
				#define _FIX_PETSKILL_HECTOR		    // 修復該技能無法設置turn
			#endif
		#endif
	#endif
#endif

#if _ATTESTAION_ID == 1 && _ATTESTAION_ID != 2 && _ATTESTAION_ID != 3 && _ATTESTAION_ID != 5 && _ATTESTAION_ID != 6 && _ATTESTAION_ID != 9 && _ATTESTAION_ID != 10 && _ATTESTAION_ID != 11 && _ATTESTAION_ID != 14 && _ATTESTAION_ID != 15 && _ATTESTAION_ID != 19 && _ATTESTAION_ID != 26 && _ATTESTAION_ID != 27 && _ATTESTAION_ID != 28 &&  _ATTESTAION_ID != 31 && _ATTESTAION_ID != 33 && _ATTESTAION_ID != 34 && _ATTESTAION_ID != 36 && _ATTESTAION_ID != 38 && _ATTESTAION_ID != 39 && _ATTESTAION_ID != 45
//	#define MANOR_MAX_NUM 			2        // (4.0) 家族據點
#else
	#define MANOR_MAX_NUM       4        // (4.0) 莊園數量
#endif

#if _ATTESTAION_ID != 5 && _ATTESTAION_ID != 11
	//#define FAMILY_MAX_MEMBER 			50 	// 家族人數
#else
	#define FAMILY_MAX_MEMBER       50		// 家族人數
#endif

#define _FIX_COPY_MM_BUG         //修復復製MM的BUG
#define _FIX_PETSKILL_BUG        //修復寵物技能重疊使用

#if _ATTESTAION_ID != 3 && _ATTESTAION_ID != 5 && _ATTESTAION_ID != 11
//#define _CHARADATA_SAVE_SQL      //將數據寫入SQL
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 23 || _ATTESTAION_ID == 28 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 33 || _ATTESTAION_ID == 34 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 36 || _ATTESTAION_ID == 37 || _ATTESTAION_ID >= 40
	#if _ATTESTAION_ID != 49
		#define _SASQL                // 加入MYSQL功能
	#endif
#endif
#ifdef _SASQL
#ifdef _STREET_VENDOR
	#if _ATTESTAION_ID != 43
		#if _ATTESTAION_ID != 28 && _ATTESTAION_ID != 34
			#define _ONLINE_SHOP_MYSQL       // 在線商城改成MYSQL重迴幣
		#endif
		#define _STREET_VENDOR_MYSQL     // MYSQL重迴幣擺攤
	#endif
#endif
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 23 || _ATTESTAION_ID == 33
	#define _EXPANSION_VARY_WOLF      // 擴展暗月變身
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 21
	#define _SHOW_ITEM                // 秀裝備
	#define _SHOW_ITEM_NAME           // 秀裝備玩傢名
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 32
#ifdef _VERSION_80
	#define _DISABLE_PROFESSION_SKILL      // 禁止使用職業技能技
	#define _TAKE_ITEMDAMAGE_FIX           // 下身裝備損壞
	#define _TAKE_ITEMDAMAGE_FOR_PET       // 寵裝裝備損壞
#endif
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 35
	#define _GM_SAVE_ALL_CHAR      // GM命令存檔
#endif

#if _ATTESTAION_ID == 35
	//#define _SHOW_FMPOINT					//顯示莊園
	#define _NOT_FMPK_WAIT				//族戰無休戰期
#endif

#if _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 16 || _ATTESTAION_ID == 33 || _ATTESTAION_ID == 34 || _ATTESTAION_ID == 41
	#ifdef _BOUND_TIME
		#define _VIP_BOUND_TIME
		#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 41
			#define _BOUND_TIME_EXPANSION      // 包時功能擴展
		#endif
	#endif
#endif

//#define _ABSOLUTE_DEBUG              // 絕對調試


#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 14 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 28 || _ATTESTAION_ID == 30 || _ATTESTAION_ID == 31 || _ATTESTAION_ID == 32 || _ATTESTAION_ID == 33 || _ATTESTAION_ID == 35 || _ATTESTAION_ID == 36 || _ATTESTAION_ID == 37 || _ATTESTAION_ID == 40 || _ATTESTAION_ID == 44 || _ATTESTAION_ID == 45 || _ATTESTAION_ID == 46
	#define _ALLBLUES_LUA      // 使用LUA腳本
#endif

#ifdef _ALLBLUES_LUA
	#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 32 
		#define _ALLBLUES_LUA_1_1      // LUA1.1版
	#endif
	#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 32 
		#define _ALLBLUES_LUA_1_2      // LUA1.2版
		#define _ALLBLUES_LUA_1_3      // LUA1.3版
	#endif
	#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 32 
		#define _ALLBLUES_LUA_1_4      // LUA1.4版
	#endif
	
	#if  _ATTESTAION_ID == 1
		#define _ALLBLUES_LUA_1_5      // LUA1.5版
	#endif
	
	#if  _ATTESTAION_ID == 1
		#define _ALLBLUES_LUA_1_6      // LUA1.6版
	#endif
	#if  _ATTESTAION_ID == 1
		#define _ALLBLUES_LUA_1_7      // LUA1.7版
	#endif
	#if  _ATTESTAION_ID == 1
		#define _ALLBLUES_LUA_1_8      // LUA1.8版
	#endif
	
	#if  _ATTESTAION_ID == 1
		#define _ALLBLUES_LUA_1_9      // LUA1.9版
	#endif
	
	#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 32 
		#define _PETSKILL_SHOP_LUA       // 寵物技能商店LUA
	#endif
	#if  _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 32 
		#define _OFFLINE_SYSTEM       // 離綫係統
	#endif
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 1 || _ATTESTAION_ID == 3  || _ATTESTAION_ID == 32 
	#define _PLAYER_NPC      // 虛假玩傢
#endif

#if _ATTESTAION_ID == 0 || _ATTESTAION_ID == 3 
	#define _OTHER_SAAC_LINK  // 另一個SAAC連接
#endif

#if _ATTESTAION_ID == 1
	#define _ONE_SERVER       // 單機綁定
#endif

#if _ATTESTAION_ID == 32
	#define _NOT_NOCRYPTO_LUA // 不讓讀取非加密LUA腳本
#endif

#if _ATTESTAION_ID == 1
	#define _CRYPTO_LUA    		// lua腳本加密
#endif

#if _ATTESTAION_ID == 1
	#define _CAMEO_MONEY      		// 貝殼貨幣
	#define _MISSION_TRAIN    		// 任務鏈
	#define _DEL_DROP_PET    			// 刪除地上寵物
	#define _PET_EVOLVE    				// 寵物進化
	//#define _PET_ADD_EXP      		// 寵物經驗提升道具
	#define _FIX_ADD_EXP      		// 修復豆子經驗疊加
	#define _FMRIDE_NOT_FMSPRITE	// 家族騎寵不分光明黑暗
	#define _NOT_SHOW_ONLINE_NUM	// 不顯示在線人數
	#define _ITEM_COLOER_DIFFER		// 道具顔色不同
	#define _SPECIAL_COUNTER			// 計數器
	#define _SPECIAL_TIMER				// 計時器
	#define _RECORD_IP						// 記錄IP
	#define _FIX_STW_SPEED_ENEMY	// 修改外掛快速遇敵
	//#define _DEL_NOT_25_NEED_ITEM	// 刪除非2.5需道具抓寵
	#define _LOCK_PET_ITEM				// 綁定寵物與道具
	#define _ULTIMATE_ANNOUNCE		// 飛人通知
	#define _SHIP_MATEMO					// 船的變身形像
	#define _FIX_CORE_LOOP				// 修改CORE_LOOP
	#define _VIP_BATTLE_EXP				// 會員戰鬥經驗
	#define _FLOOR_DIFI_FIELD			// 樓層字段
	#define _FM_FMPOINTPK_LIST		// 莊園對戰列錶
	//#define _BATTLE_BOUT_TIME			// 戰鬥迴閤時間
	#define _ACTIVE_GAME			    // 活力值
	#define _INVERSION_PETSKILL   // 反轉技能
	#define _NO_HELP_MAP					// 禁止HELP
	#define _BATTLE_TIME					// 戰鬥時間
	//#define _SAME_IP_ONLINE_NUM		// 同IP登陸數
	#define _VIP_TRANS						// VIP轉生服務
	#define _STREET_VENDOR_TRANS	// 擺攤限製轉數
	#define _KEEP_UP_NO_LOGIN			// 維護禁止登陸
	#define _FIX_CHAR_LOOP				// 修正數據循環
	#define _FIX_SAVE_CHAR				// 修正保存檔問題
	#define _FIX_P_VS_P_PARENT		// 修正PVP加入戰鬥
	#define _FMPOINT_PKTIME_SELECT// 自主選擇族戰時間
	#define _CHECK_SEVER_IP				// 判斷服務器IP
	#define _DAMMAGE_CALC					// 自定義傷害
	#define _PLAYER_TITLE					// 玩傢稱號
	#define _VIP_PET_TRANS				// 會員轉寵
	//#define _UNIFIDE_MALINASI			// 統一瑪麗娜絲魚村出生
	//#define _FIX_PET_SKILL				// 修復寵物技能
	//#define _NO1_B2_NONO					// B2學在第一位時自動鎖定21忠
	//#define _FMPOINT_APPEND_ABI		// 莊園家族成員附加能力
	#define _ITEM_OVER_LAP				// 道具重復功能
	#define _NEW_LOAD_NPC					// 讀取NPC
	#define _NEW_LOAD_MAP					// 讀取地圖
	#define _NO_CLS_EVENT_255			// 不清楚255後的旗標
	#define _MISSION_TIME					// 任務計時
	#define _MVP_LOCK_JP					// 綁定MVP極品寵
	//#define _FMPOINTPK_FOR_TWO		// 每天族戰最多為兩場
	#define _BURST_LOG						// 分段日誌
	#define _STREET_VENDOR_EFFECT // 擺攤屬性顯示
	//#define _MASK_ENCOUNTER 			// 屏蔽原地封包
	#define _NEWCLISETMAC		 			// 記錄客戶端的MAC地址
	#define _NEWCLISETSERVID 			// 記錄客戶端服務器ID
	//#define _FMPOINT_PK_MESSAGE		// 族戰全服通告
	//#define _FMPOINT_WELFARE			// 莊園福利
	#define _REGISTRATION_TIME		// 簽到時間
	#define _FAME_REG_TIME				// 家族簽到時間
#ifdef _OFFLINE_SYSTEM
	#define _OFFLINE_TIME					// 離綫時間
#endif
	#define _DATA_INFO_SHOW				// 資料信息顯示
	#define _ITEM_USE_TIME				// 道具使用時間
//	#define _PET_VALIDITY  				// 寵物有效期
	//#define _PET_FUSION_LUA  			// 融合寵LUA
	//#define _PET_ENEMY_DEVELOP_UP //全面提升寵物成長
	#define _FIRST_LOCK_ITEM			//第一次交易後自動綁定物品
	#define _CTRL_TRANS_DEVELOP		//控製成長
	#define _CANCEL_STREET_VENDOR		//防止卡擺攤
	//#define _ABDUCT_NO_PETOUT			//旅程夥伴禁直同時換寵
	//#define _SUPER_FMPOINT				//超級莊園
	#define _ATTACK_RAND_SORT			//攻擊順序隨機
	#define _POWER_UP							//能力提升
	#define _FM_POINT_APPLY_FAME	//莊園申請所需聲望
	#define _PET_MAKE_2_TRANS						// Terry □□退ネ□GM□□

#endif
#if _ATTESTAION_ID == 0
	#define _DEBUG_ALL
#endif

#if _ATTESTAION_ID == 35
	#define _DAMMAGE_CALC					// 自定義傷害
#endif

#endif

//                       SA_REVERSION NEW ADD
//======================================================================================
#define _BRAND_NEW_25				//2.5版本總控製  開啓之後將打開2.5獨有的功能
//======================================================================================

//###############                                            服務器基本信息定義                                    ####################
#define _SA_VERSION 'N'
#define _DEFAULT_PKEY "starttwneo"		// 默認的密鑰
#define _RUNNING_KEY  "runtwtrinity"		// 運行中密鑰
//###############                                            服務器基本信息定義                                    ####################

//###############                                            通用版本功能定義區                                    ####################
#define		_JZ_NEWSCRIPT_LUA				 // 吉仔 新LUA腳本引擎
#ifdef		_JZ_NEWSCRIPT_LUA
	#define _MO_LNS_NLSUOXU            // LNS-NL庫所需
	#define _MO_LNS_CHARSUOXU          // LNS-CHAR庫所需
	#define _MO_LNS_NLGSUOXU           // LNS-NLG庫所需
	#define _MO_LNS_MAPSUOXU           // LNS-MAP庫所需
	#define _MO_LNS_MYSQLSUOXU         // LNS-MYSQL庫所需
	#define _MO_LUA_BETT01			        // LUA增加接口與對象
	#define _LUA_Debug                  // LUA錯誤調試
	#define _MO_ADD_LUADX					    // LUA一些拓展
	#define _ITEM_LUA				            // 道具LUA支持
#endif
//#define _MO_SHOW_DEBUG			//顯示封包信息
//#define _NO_ATTACK						 // 防禦CC攻擊
//#define	_NO_FULLPLAYER_ATT	     // 防滿人攻擊
//#define _NEW_VERIFICAITON 	//沫修改新的LUA驗證碼算法
#define _SHARE_EXP					  // 經驗共享
#define EXPGET_MAXLEVEL 5			//經驗不衰減最大等級
#define EXPGET_DIV 15				//經驗分割等級
#ifdef _SHARE_EXP
#define _COMBO_EXP					// 閤擊加成
#endif
#define _GAMBLE_POINT				//SQL賭博積分
#define _TRIAL_POINT				//SQL試煉積分
#define 	_MO_LUA_FMPOINT			//新增據點相關的lua接口
#define _DEFEND_BIGBAO				//防禦大包
#define _SERVER_DEF                 // 封包安全機製
//#define _DEBUG_RET_CLI
#define _NOT_FMPK_WAIT				//族戰無休戰期
#define _SINGLE_ONLINE				//單號在線
#define _CHAR_LOOP_TIME				//char運行時間
#define _MO_IMAGE_EXTENSION			//形象擴展

#define _CHANGE_PETNAME_FIX			//禁止寵物非法改名
#define		_MO_RELOAD_NPC			//重讀NPC
#define _ROOKIE_ITEM				//新手道具 1轉之後將刪除 且無法裝備
#define _NO_TRANS_ITEM				//禁止轉生攜帶的道具
#define _MAX_MERGE_LEVEL			//最高閤成道具等級
#define _MO_MAP_AUTO_UPDATE				//自動更新地圖
#define _NEW_FUNC_DECRYPT		//新解密機製

#define _PLAYER_EFFECT									//人物效果
#define _MO_PLAYER_EFFECT							//增加人物效果相關字段以擴充
#define _MO_LUA_KS_CALLBACK					//KS接口LUA迴調 用於攔截戰寵選擇事件
#define _MO_LOGIN_NO_KICK							//登錄不頂人配置
#define _ATTACK_EFFECT								  // Terry 攻擊效果
#define _STREET_VENDOR_CHECK					//擺攤標題長度限製
#define _MO_LUA_TALK_EX								//ablua說話函數擴展
#define _MO_LUA_ENCOUNTER_CONTROL		//ablua遇敵控製
#define _MO_ILLEGAL_NAME            // 禁止人物名稱
//#define _MO_NO_WALK											//禁止走路
#define _MO_FIX_ULTIMATE							//修復飛人判定
#define _TENSE_FIELD										//限時字段

#define _CHAR_NANOR_             //人物腳下光環
#define FAMILY_MANOR_         //莊園光環
#define _NETLOG_              //網絡T人日誌
#define _PETCOM_              //寵物計算
#define _MORECHARACTERS_    //多頁人物
#define _FAMILYBADGE_				//家族徽章
#define _SECONDARY_WINDOW_DATA_       //二級窗口內容封包
#define _TRUNTABLE_                 //轉盤更新封包     注：這裏主要是增加個封包宏，該封包宏主要做為數據更新
#define _PETFOLLOW_NEW_                 //開放5隻寵的項圈
#define _TRUMP_EQUIPMENT					//法寶裝備
#define _FIX_SUPERPERSON_STRANS //修復封包6轉BUG
#define _PETMAIL_TIME				     // 寵物郵件自定義時間（也就是寵物敏捷）
#define _MO_LUA_RESIST							//額外抗性的lua接口及字段
#define _MO_FIX_STREET_VENDOR	//修正擺攤接口攻擊導緻的卡端
#define _MO_LUA_BATTLE_START		//戰鬥初始化接口迴調
#define _REDUCE_MERGE_FAME				//降低無掛服的家族閤成聲望等級所需聲望
#define _ALLDOMAN                // (可開放) Syu ADD 排行榜NPC
#define _ALLDOMAN_DEBUG          // (可開) Change 修正重啓server後排行榜消失bug
#define _MO_LUA_MERGE_CALLBACK		//閤成料理的lua迴調
#define _ALWAYS_TEAM_OPEN					//登錄默認開啓組隊
#define _FIX_LER_IMG								//修復雷爾動畫
#define _NPC_MAGICCARD							// 魔法卡NPC
#define _MOVE_SCREEN								//移動屏幕
#define _BATTLE_OVER_STAR_TIME// 戰鬥後重新開始時間間隔

#define _NEW_SQL_MONEY										//新增SQL貨幣

//###############                                            通用版本功能定義區結束                                    ####################

//###############                                            2.5特有功能定義區                                    ####################
#ifdef _BRAND_NEW_25
#define _DEFAULT_PKEY "shiqi"		// 默認的密鑰
#define _RUNNING_KEY  "shiqi.hk"		// 運行中密鑰
#define DENGLUKEY1 "6D27AEB8326A2A8E7D04B9F9B44C59C7"

#define _NEW_TITLE											//新稱號係統
#define _NEW_UPDATETITLE							//更新稱號封包
#define CHAR_RECORD_POINT               //人物記錄點客戶端讀取
#define _FREE_SAVE    				// 免條件記錄
#define FAMILY_MAX_MEMBER 			50 	// 家族人數
#define MANOR_MAX_NUM 			2        // (4.0) 家族據點
#define _LEVELUP_RECOVERY					   //升級滿血
#define _NEW_ITEM_          //新道具欄

#define _VISUAL_BEATITUDE							//新可視化祝福機製
#define _RIDEFLG_        						 //騎寵開關
#define _RIDEQUERY_                            //騎寵查詢
#define _PREVENT_TEAMATTACK				//防止同隊互打
#define _SHOW_VISUAL_BEATITUDE		//交易擺攤顯示可視化祝福
#define _MO_REDUCE_PVP_COMBO				//降低PVP閤擊率
#define _BATTLE_OVER_STAR_TIME// 戰鬥後重新開始時間間隔
//#define _CANCEL_BORN_PET			// 取消出生寵

#define _NPC_EVENT_NOTICE							//沫新增NPC任務狀態提示功能，需客戶端開啓該宏功能
#ifdef _NPC_EVENT_NOTICE
	#define EVENT_NOT_RESPOND					120138	//灰色嘆號 任務已完成或者尚未達到完成條件
	#define EVENT_CAN_ACCECPT					120137	//黃色嘆號 任務可以交接
	#define EVENT_READY_TO_START			120139	//黃色問號 可以接任務
	#define EVENT_CANNOT_START				120140	//灰色問號 不能接任務
#endif
#define _CHAR_TITLE_STR_                //文字稱號
#define _NEW_UPDATETITLE							//更新稱號封包

#define _NO_TEAMWARP_SKYLAND			//禁止團體帶入天空
#define _GLORY_POINT								//SQL名聲積分
#define _MO_LUA_GOLRYCALLBACK		//名聲迴調
#define _RED_MEMOY_                 //紅包
#endif
//###############                                            2.5特有功能定義區 結束                                   ####################
