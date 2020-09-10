#ifndef __VERSION_H__
#define __VERSION_H__
#include "correct_bug.h"  //BUG FIX
#include "common.h"
#include "longzoro/version.h"
#include "longzoro/debug.h"

/*  網絡模型  */
//#define _EPOLL_ET_MODE									//EPOLL ET模型
//#define _EPOLL_POOL_COUNT		5					//綫程池數量

/*Server 版本控製*/
#define _NEW_SERVER_
#define _SERVER_NUMS

#define UNIQUE_KEYCODEITEM	100
#define UNIQUE_KEYCODEPET	"i"

#define _FAMILY_MANORNUM_CHANGE	 // CoolFish 用來修改裝園數量(4.0)
#ifdef _FAMILY_MANORNUM_CHANGE
#define FAMILY_MAXHOME 		MANOR_MAX_NUM        // (4.0) 家族據點
#define MANORNUM       		MANOR_MAX_NUM        // (4.0) 莊園數量
#define FMPOINTNUM     		MANOR_MAX_NUM        // (4.0) 有據點家族的最大數量
#endif
#define _FMVER21                 // (可開放) 家族職掌功能
#define _PERSONAL_FAME           // (可開放) Arminius 8.30 家族個人聲望
// -------------------------------------------------------------------
//專案：石器活動自動化		人員：曉威、傢麟

//#define _COMFIRM_TRADE_REQUEST    //接收交易請求確認

#define _EVERYONE_RIDE           // (可開放) Robin 0924 騎寵平民化
// -------------------------------------------------------------------
//專案：攻擊性咒術的製作	人員：篤誌
#define _ATTACK_MAGIC            // (可開放)	提供戰場中的攻擊性咒術
#define _ADD_ACTION              // (可開放) 一般NPC動作狀況的設定

// -------------------------------------------------------------------
//專案：寵物、道具編碼		人員：小瑜
#define _UNIQUE_P_I              // (可開放) CoolFish 2001/10/11

// -------------------------------------------------------------------
//專案：新版人物儲存pn 及 當機不迴朔 1018	人員：彥勛
#define _NEWSAVE                 // (可開放) Robin
#define _STORECHAR               // (可開放) Robin
#define _DROPCHECK               // (可開放) Robin 防止重復丟道具
#define _DROPCHECK2              // (可開放) Robin 防止重復丟道具
// -------------------------------------------------------------------
//專案 : 精靈王	人員 : 彥豪
#define _PET_TRANS               // (可開放) 寵物轉生功能
#define _NEW_WARPMAN             // (可開放) NPC多重WARP功能
#define _PET_TALK                // (可開放) 寵物對話
#define _PET_LIMITLEVEL          // (可開放) 特殊寵設計(瑪蕾)
#define _MAP_NOEXIT              // (可開放) 特殊地圖不得原登&原登迴指定點
// -------------------------------------------------------------------
// 專案：GM指令、層級Reload		人員：小瑜
#define _GMRELOAD                // (可開放) CoolFish: 2001/11/12
// -------------------------------------------------------------------
// 專案：伊甸大陸	人員：彥豪、阿民、小瑜
#define _GAMBLE_ROULETTE         // (可開放) 彥豪 賭場輪盤	寶寶小豬
#define _FIX_GAMBLENUM           // (可開放) 輪盤修正 : 下綫扣積分
#define _GAMBLE_BANK             // (可開放) 彥豪  賭場銀行
#define _DROPSTAKENEW            // (可開放) CoolFish:  賭場下注
#define _PETRACE                 // (可開放) CoolFish: 2001/12/3 寵物競速場
#define _NEWEVENT                // (可開放) CoolFish: 2001/12/5 新的任務旗標
// -------------------------------------------------------------------
//專案：鞭炮製作	人員：曉威
#define _ITEM_FIRECRACKER        // (可開放) 戰鬥中使用鞭炮可以把年獸嚇走
// -------------------------------------------------------------------
//新功能：莊園PK規則(酷哥定的)		人員：誌偉、誌旺
#define _MANOR_PKRULE            // (可開放)
// -------------------------------------------------------------------
// 新功能：新功能&寵物技能		人員：彥豪
#define _PSKILL_FALLGROUND       // (可開放) 寵物技能  (落馬術)
#define _ENEMY_FALLGROUND        // (可開放) NPC 落馬
#define _Item_MoonAct            // (可開放) 月神的守護
#define _Item_DeathAct           // (可開放) 惡魔的首飾
#define _Item_PetAct             // (可開放) 馴獸戒指
#define _Item_ReLifeAct          // (可開放) 需要itemset1.txt 纔能開) 替身娃娃
#define _BATTLESTEAL_FIX         // (可開放) 修正偷竊
#define _CFREE_petskill          // (可開放) 需要petskill1.txt 纔能開) 新學習寵物技能技能
#define _data_newreadfile        // (可開放) 新的server setup.cf 檔案 包含 itemset1.txt petskill1.txt 兩個新檔
#define _ITEM_MAXUSERNUM         // (可開放) 新 itemset1.txt ITEM 使用次數
// -------------------------------------------------------------------
//新功能：伊甸二期    人員：彥豪
#define _PET_TALKPRO             // (可開放) 寵物對話加強  & 改 END
#define _PRO_NPCFIX              // (可開放) NPC功能加強
#define _PRO_BATTLEENEMYSKILL    // (可開放) 戰鬥加強  提升NPC的AI技能
#define _NEW_WARPPOINT           // (可開放) 傳送點多重條件判斷WARP
#define _FIX_CHECKITEM           // (可開放) 道具不做非法檢查
// -------------------------------------------------------------------
//新功能：伊甸二  人員：小民,WON
#define _ADD_ENCOUNT             // (可開放) WON 增加敵遭遇觸發修件
#define _WON_PET_MAIL_LOG        // (可開放) WON 玩傢寄寵郵 LOG
// -------------------------------------------------------------------
// 新功能：伊甸叁期  4.0  人員：彥豪, 誌偉 , 又榮 , 誌旺
//#define _LOSE_FINCH_           // (不可開) ANDY 硃雀技能
#define _ADD_POOL_ITEM           // (可開放) WON 增加可寄放的道具
#define _ITEM_METAMO             // (可開放) shan metamo sprite. code:robin->shan
#define _ENEMY_ATTACK_AI         // (可開放) shan enemy attack mode. code:shan
#define _ITEM_TIME_LIMIT         // (可開放) shan time limit of item. code:shan
#define _MIND_ICON               // (可開放) shan show icon from char mind. code:shan
#define _BATTLENPC_WARP_PLAYER   // (可開放) shan npc warp player when n round. code:shan
#define _ITEM_WARP_FIX_BI        // (可開放) shan fix bbi to bi. code:shan
#define _SKILL_DAMAGETOHP        // (可開放) ANDY 嗜血技
#define _Skill_MPDAMAGE          // (可開放) ANDY MP傷害
#define _WAEI_KICK               // (可開放) ANDY 跨星球踢人
#define _BATTLE_TIMESPEED        // (可開放) ANDY 戰鬥時間 測試(北京不必開，擋加速功能)
#define _FIXBUG_ATTACKBOW        // (可開放) ANDY 修正騎寵使用投擲武器bug
#define _NPCCHANGE_PLAYERIMG     // (可開放) ANDY NPC改變玩傢圖號, 強制落馬,認玩傢圖號 (測完)
#define _EQUIT_DEFMAGIC          // (可開放) ANDY 抗魔裝備
#define _FIX_MAGICDAMAGE         // (可開放) ANDY 修正魔法公式 叁期開放
#define _ITEM_CONSTITUTION       // (可開放) ANDY 修正個人體質
#define _MAGIC_REHPAI            // (可開放) ANDY 補血AI
#define _TRANSER_MAN             // (可開放) ANDY 傳送師
#define _FIX_FIRECRACKER         // (可開放) ANDY 修正 鞭炮
#define _FIX_ITEMPROB            // (可開放) ANDY 修正 掉寶率
#define _ADD_DEAMGEDEFC          // (可開放) ANDY 額外傷害 & 附加攻擊  ITEMSET2
#define _FIX_MAXCHARMP           // (可開放) ANDY MP上限
#define _ITEM_INSLAY             // (可開放) ANDY 鑲寶石 動作
#define _ITEMSET2_ITEM           // (可開放) ANDY ITEMSET2
#define _ITEM_NPCCHANGE          // (可開放) ANDY 工匠 (提煉, 精工)
#define _FIX_SETWORKINT          // (可開放) ANDY (FIXWORKINT)
#define _ITEM_ADDEXP             // (可開放) vincent  道具:指定時間內增加經驗值上升幅度
#define _ITEM_ADDEXP2            // 智果時間可以纍加 Robin
#define _FIX_METAMORIDE          // (可開放) ANDY
#define _SKILL_WILDVIOLENT_ATT   // (可開放) vincent  寵技:狂暴攻擊
#define _MAGIC_WEAKEN            // (可開放) vincent  精靈:虛弱
#define _SKILL_WEAKEN            // (可開放) vincent  寵技:虛弱//需要開#define _MAGIC_WEAKEN
#define _SKILL_SPEEDY_ATT        // (可開放) vincent  寵技:疾速攻擊
#define _SKILL_GUARDBREAK2       // (可開放) vincent  寵技:破除防禦2
#define _SKILL_SACRIFICE         // (可開放) vincent  寵技:救援
#define _PSKILL_MODIFY           // (可開放) ANDY 屬性強化攻擊
#define _PSKILL_MDFYATTACK       // (可開放) ANDY 攻擊轉化屬性
#define _MAGIC_DEFMAGICATT       // (可開放) ANDY 魔法防禦
#define _MAGIC_SUPERWALL         // (可開放) ANDY 鐵壁防禦
#define _OTHER_MAGICSTAUTS       // (可開放) ANDY
#define _SKILL_TOOTH             // (可開放) ANDY   齒術
#define _MAGIC_DEEPPOISON        // (可開放) vincent  精靈:劇毒
#define _MAGIC_BARRIER           // (可開放) vincent  精靈:魔障
#define _MAGIC_NOCAST            // (可開放) vincent  精靈:沉默
#define _ITEM_CRACKER            // (可開放) vincent  道具:拉炮 //需要開#define _MIND_ICON
#define _SKILL_DEEPPOISON        // (可開放) vincent  寵技:劇毒 //需要開#define _MAGIC_DEEPPOISON
#define _SKILL_BARRIER           // (可開放) vincent  寵技:魔障 //需要開#define _MAGIC_BARRIER
#define _SKILL_ROAR              // (可開放) vincent  寵技:大吼(剋年獸)
#define _SKILL_REFRESH           // (可開放) vincent  寵技:解除異常狀態
#define _ITEM_REFRESH            // (可開放) vincent  解除異常狀態道具
#define _MAGIC_TOCALL            // (可開放) kjl     召喚  02/06/20 kjl

// -------------------------------------------------------------------
// 新功能：來吉卡功能  人員：彥豪
#define _ITEMSET3_ITEM           // (可開放) ANDY itemset3.txt
#define _SUIT_ITEM               // (可開放) ANDY (套裝) 來吉卡 需用itemset3.txt
#define _PETSKILL_SETDUCK        // (可開放) ANDY 濛奇技能
#define _VARY_WOLF               // (可開放) pet skill : vary wolf. code:shan
// -------------------------------------------------------------------
// 新功能：專案5.0    人員：
#define _USEWARP_FORNUM          // (可開放) ANDY 記憶羽毛 來吉卡
#define _IMPRECATE_ITEM          // (可開放) ANDY 特殊道具 來吉卡
#define _MAGICPET_SKILL          // (可開放) ANDY 魔法寵技能
#define _ITEM_CHECKWARES         // (可開放) ANDY 鎖定傳送不能
#define _NPC_REPLACEMENT         // (可開放) ANDY 置換戰鬥npc
#define _TYPE_TOXICATION         // (可開放) ANDY 中毒無法迴血

// -------------------------------------------------------------------
// 新功能：5.0追加部分    人員：
#define _AVID_TRADETRYBUG        // (可開放) ANDY 防止交易中丟寵/道具 寄(寵物)郵件 石幣
#define _ASSESS_SYSEFFICACY      // (可開放) ANDY 評估係統效能 12/04 更新
#define _ASSESS_SYSEFFICACY_SUB  // (可開放) Robin 評估係統效能 增加檢查內迴圈
#define _ITEM_ORNAMENTS          // (可開放) ANDY 裝飾道具  12/04 更新  //出版部
#define _CHIKULA_STONE           // (可開放) ANDY 奇剋拉之石 12/04 更新  //來吉卡 寵包
#define _SEND_EFFECT             // (可開放) WON  AC送下雪、下雨等特效 12/04 更新
#define _PETMAIL_DEFNUMS         // (可開放) ANDY 寵物郵件限製
#define _PETSKILL_TIMID          // (可開放) ANDY 寵技-怯戰
#define _PETS_SELECTCON          // (可開放) ANDY 寵物不可點選出戰
#define _CHRISTMAS_REDSOCKS      // (可開放) ANDY 聖誕紅襪
#define _FIX_ARRAYBUG            // (可開放) ANDY 修正array 溢位
#define _USER_CHARLOOPS          // (可開放) ANDY 新用物件LOOP
#define _BATTLE_PROPERTY         // (可開放) ANDY 戰鬥屬性特性
#define _PETSKILL_PROPERTY       // (可開放) ANDY 無屬魔獸寵技
#define _ITEM_FIXALLBASE         // (可開放) ANDY 修復之石
#define _ITEM_LOVERPARTY         // (可開放) ANDY 情人節道具
#define _ITEM_FORUSERNAMES       // (可開放) ANDY 道具所有人
#define _BATTLECOMMAND_TIME      // (可開放) ANDY 防止玩傢開緩速(迴閤戰鬥時間)
#define _NPCENEMY_ADDPOWER       // (可開放) ANDY 修改怪物的能力值


// -------------------------------------------------------------------
// 新功能：專案6.0    人員：
//
#define _PETSKILL_CANNEDFOOD     // (可開放) ANDY 寵物技能罐頭  for 6.0
#define _TEST_DROPITEMS          // (可開放) ANDY 測試丟寵
#define _MAP_WARPPOINT           // (可開放) ANDY Map WarpPoint
#define _BENEMY_EVENTRUN         // (可開放) ANDY 戰鬥npc給道具
#define _BATTLE_ABDUCTII         // (可開放) ANDY 旅途夥伴2
#define _BATTLE_LIGHTTAKE        // (可開放) ANDY 采光術
#define _BATTLE_ATTCRAZED        // (可開放) ANDY 瘋狂暴走
#define _CAPTURE_FREES           // (可開放) ANDY 補抓條件
#define _THROWITEM_ITEMS         // (可開放) 丟擲後有奬品
//--------------------------------------------------------------------------
//專案 7.0  職業係統  人員：彥豪 誌旺 旭誠 奇銓
#define _ACFMPK_LIST             // (可開放) ANDY 家族對戰列錶修正
#define _PETSKILL2_TXT           // (可開放) ANDY petskill2.txt
#define _PETSKILL_CHECKTYPE      // (可開放) ANDY 寵物技能使用時機
#define _PETSKILL_TEAR           // (可開放) ANDY 寵技 撕裂傷口
#define _ITEMSET4_TXT            // (可開放) ANDY itemset4.txt
#define _PET_LOSTPET             // (可開放) ANDY 遺失寵物搜尋計劃寵物
#define _ITEMSET5_TXT            // (可開放) ANDY itemset5.txt
#define _ITEMSET6_TXT            // (可開放) ANDY itemset6.txt
#define _EQUIT_SEQUENCE          // (可開放) ANDY 攻擊順序 需要 itemset5.txt
#define _EQUIT_HITRIGHT          // (可開放) ANDY 命中 需要 itemset5.txt
#define _EQUIT_NEGLECTGUARD      // (可開放) ANDY 忽視目標防禦力% 需要 itemset6.txt
#define _FIX_MAX_GOLD            // (可開放) WON ADD 增加人物金錢上限
#define _PET_SKILL_SARS          // (可開放) WON ADD 毒煞蔓延
#define _SONIC_ATTACK            // (可開放) WON ADD 音波攻擊
#define _NET_REDUCESEND          // (可開放) ANDY 減少DB資料傳送
#define _FEV_ADD_NEW_ITEM        // (可開放) Change 增加復活守精
#define _LOCKHELP_OK             // (可開放) Syu ADD 鎖定不可加入戰鬥
//係統改良
#define _SIMPLIFY_ITEMSTRING     // (可開放) ANDY 簡化道具字串

#define _SIMPLIFY_PETSTRING      // (可開放) ANDY 簡化寵物存檔字串
#define _SIMPLIFY_ITEMSTRING2    // (可開放) ANDY 簡化道具字串2
#define _WOLF_TAKE_AXE           // (可開放) WON ADD 抓雙頭狼的限製
#define _FIX_UNNECESSARY         // (可開放) ANDY 修正不必要的判斷
#define _ITEM_MAGICRECOVERY      // (可開放) ANDY 新光鏡守
//9/17更新
#define _PETSKILL_GYRATE         // (可開放) Change 寵技:迴鏇攻擊
#define _PETSKILL_RETRACE        // (可開放) Change 寵技:追跡攻擊
#define _PETSKILL_HECTOR         // (可開放) Change 寵技:威嚇
//10/13更新
#define _PETSKILL_FIREKILL       // (可開放) Change 寵技:火綫獵殺
#define _PETSKILL_DAMAGETOHP     // (可開放) Change 寵技:暗月狂狼(嗜血技的變體)
#define _PETSKILL_BECOMEFOX      // (可開放) Change 寵技:媚惑術

//11/12更新
#define _PETSKILL_SHOWMERCY      // (可開) Change 寵技:手下留情
#define _NPC_ActionFreeCmp       // (可開) Change 替NPC參數加入新的比較方式
//--------------------------------------------------------------------------


//11/26
#define _NPC_NewDelPet           // (可開) Change 替NPC加入刪除寵物(原本就有了,只是用warpman使用時不成功,所以先做一個頂一下)

//20031217
#define _CHRISTMAS_REDSOCKS_NEW  // (可開) Change 新聖誕紅襪
#define _PETSKILL_COMBINED       // (可開) Change 寵技:難得糊塗 [綜閤魔法(依參數亂數取出魔法)]
//情人節活動
#define _NPC_ADDWARPMAN1         // (可開放) Change npcgen_warpman增加功能(設定組隊人數、設定組隊男女人數)
#define _ITEM_QUITPARTY          // (可開放) Change 隊伍解散時特定道具即會消失
#define _ITEM_ADDEQUIPEXP        // (可開) Change 裝備後經驗值增加
//2004/2/18
#define _ITEM_LVUPUP             // (可開) Change 突破寵物等級限製的藥(玄武專用)
//2004/02/25
#define _PETSKILL_BECOMEPIG      // (可開) Change 寵技:烏力化
#define _ITEM_UNBECOMEPIG        // (可開) Change 烏力化的解藥
#define _PET_TALKBBI             // (可開) Change 增加判斷bbi
#define _ITEM_USEMAGIC           // (可開) Change 由道具使用魔法
//2004/04/07
#define _ITEM_PROPERTY           // (可開) Change 改變四屬性道具
#define _SUIT_ADDENDUM           // (可開) Change 替套裝增加功能 (_SUIT_ITEM要開)
//2004/05/05
#define _ITEM_CHECKDROPATLOGOUT  // (可開) Change 檢查迴紀錄點時身上有無登出後消失道具,若有,不可迴紀錄點
#define _FM_MODIFY               // 家族功能修改(開放)
#define  _PETSKILL_OPTIMUM       // Robin 寵物技能處理最佳化
#define _MAGIC_OPTIMUM           // Robin Magic table 最佳化
#define _AC_PIORITY              // Nuke 提高AC的優先權(可開)
// -------------------------------------------------------------------
//專案 7.5  精靈的招喚  人員：彥勛 奇銓 小威
// Terry define start -------------------------------------------------------------------
#define _MAP_TIME                // 特殊地圖,會倒數(開放)

// Terry define end   -------------------------------------------------------------------
#define _ITEM_ADDPETEXP          // (可開) Change 增加寵物經驗值道具(可吃此道具寵物,平常不可獲得經驗值)
#define _TRANS_6                 // (可開) Change 人物6轉
#define _PET_2TRANS              // (可開) Change 寵物2轉
#define _PET_2LIMITLEVEL         // (可開) Change 幫助寵物2轉的瑪蕾
#define _MAGICSTAUTS_RESIST      // (可開) Change (火電冰)抗性精靈
#define _SUIT_TWFWENDUM          // (可開) Change 四屬性套裝功能 (_SUIT_ITEM要開)
#define _EXCHANGEMAN_REQUEST_DELPET   // (可開) Change 替exchangeman的TYPE:REQUEST增加刪除寵物
//--------------------------------------------------------------------------
#define _DEL_DROP_GOLD           // 刪除地上過時的石幣  Robin
#define _ITEM_STONE              // cyg 奇怪的石頭
#define _HELP_NEWHAND            // cyg 新創角色給予新手道具)
#define _DEF_GETYOU              // cyg GM指令 查詢自己兩格  圍內的玩傢帳號
#define _DEF_NEWSEND             // cyg GM指令 傳送玩傢時可加句子也可不加
#define _DEF_SUPERSEND           // cyg GM指令 可傳送已某帳號為中心附近3格內所有玩傢
#define _SUIT_ADDPART3           // (可開) Change 套裝功能第叁彈 迴避提高% 沉默抗性提高% 敏提高% 防提高% 攻提高%
#define _PETSKILL_2TIMID         // (可開) Change 怯戰第二版(狂獅怒吼)
#define _TIME_TICKET             // Robin 限時入場 森林捉寵用
#define _HALLOWEEN_EFFECT        // 萬聖節特效
#define _ADD_reITEM              // (可開) Change 檢查道具欄位空格
#define _ADD_NOITEM_BATTLE       // 新增NPC檢查人物身上沒道具會進入戰鬥
#define _PETSKILL_BATTLE_MODEL   // 寵物技能戰鬥模組
#define _PETSKILL_ANTINTER       // (可開) Change 寵技:蟻之葬 參考_PETSKILL_2TIMID
#define _PETSKILL_REGRET         // (可開) Change 寵技:憾甲一擊 參考_SONIC_ATTACK
#define _FIX_FAMILY_PK_LIMIT     // (可開放) WON 將可挑戰莊園的由前十大改為前二十大
//特殊活動功能
#define _NEWOPEN_MAXEXP          // (可開) ANDY MAX經驗值
#define _CHAR_FIXDATADEF         // (可開放) ANDY 修正人物資料初始
#define _NPC_EXCHANGEMANTRANS    // (可開) Change 替exchangeman加入判斷轉生
#define _ADD_NEWEVENT
#define _BATTLE_NEWPOWER         // (可開放)
#endif

