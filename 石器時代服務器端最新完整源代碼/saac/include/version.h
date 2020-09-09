#ifndef __VERSION_H__
#define __VERSION_H__

/* 請將控製專案的 definition 放在這個檔案
 * 然後藉由 remark/unmark 來開關功能
 */

//特殊功能控製----------------------------------------

#define _SAVE_ZIP                //自動備份
#define _IP_VIP                  //IP認證
#define _FIX_FMPOINTTIME						//修正傢族占領時間
#define _FAMILYBADGE_								//傢族徽章
#define _MORECHARACTERS_     			//多頁人物
#define _SQL_BUY_FUNC_ONE_CDKEY		//每個帳號僅能領取一次道具

#define _ATTESTAION_ID 1

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2
	//#define _VERSION_25
#endif

#ifndef _VERSION_25
	#define _TEACHER_SYSTEM   // 導師係統(未開放)
	#define _ALLDOMAN				// (可開放) Syu ADD 排行榜NPC
#endif
	#define _CHANNEL_MODIFY		// 頻道功能整閤
	#define _NEW_MANOR_LAW		// 新莊園規則
/* -------------------------------------------------------------------
 * 專案：族人職務與傢族功能補充
 * 人員：小瑜、彥勛、誌偉、小民
 * 說明：
 */
#define _LEADERFLAG_VER		// 嗯、ㄟ、這個.... (可開放)
#define _FAMILY			//  (可開放)
#define _PERSONAL_FAME		// Arminius 8.30 傢族個人聲望  (可開放)
#define _FMVER21			// CoolFish: 傢族族長職務代理人 2001/8/30 (可開放)
#define _CHAR_POOLITEM			// (可開放) ANDY 共用倉庫
#define _CHAR_POOLPET			// (可開放) Robin 共用寵物倉庫

/* -------------------------------------------------------------------
 * 專案：當機不迴朔之人物資料存檔方式修正
 * 人員：小瑜、彥勛
 * 說明：修正人物資料存檔方式
 */
#define _NewSave		// CoolFish: 2001/10/16 (可開放)

/* -------------------------------------------------------------------
 * 專案：傢族ＢＵＧ修正
 * 人員：小瑜
 * 說明：
 */
#define _LEADERFUNCHECK	// CoolFish: 2002/02/06 族長功能錯誤、禪讓錯誤修正(可開放)

/* -------------------------------------------------------------------
 * 專案：跨星球踢人
 * 人員：彥豪
 * 說明：
 */
#define _WAEI_KICK				// (可開放)(北京不必開)

/* -------------------------------------------------------------------
 * 專案：九大莊園(4.0)
 * 人員：誌旺
 * 說明：
 */
#ifndef _VERSION_25
#define _FIX_10_FMPOINT			// (可開放) WON ADD 九大莊園
#endif
#define _FIX_LEADER_ERR			// (可開放) WON ADD 修正族長問題
#define _REMOVE_FM_LOG          // (可開放) WON ADD 移除不必要的傢族 LOG

/* -------------------------------------------------------------------
 * 專案：石器6.0
 * 人員：
 * 說明：
 */
#define _SEND_EFFECT		    // (可開放) WON ADD 送下雪、下雨等特效

// -------------------------------------------------------------------
#define _AC_SEND_FM_PK			// (可開放) WON ADD 莊園對戰列錶儲存在AC
#define _ACFMPK_LIST			// (可開放) ANDY 莊園對戰列錶
/* -------------------------------------------------------------------
 * 專案：石器7.0
 * 人員：
 * 說明：
 */

#define _LOCK_ADD_NAME		// LockNode 增加名字欄位(未開放)
// -------------------------------------------------------------------
#define _SLEEP_CHAR		// Robin 2004/02/12	活躍人物與非活躍人物分開儲存

// Terry define start -------------------------------------------------------------------
#define _FM_MODIFY				// 傢族功能修改

// Terry define end   -------------------------------------------------------------------

#define _ANGEL_SUMMON	// Robin 精靈的召喚

//--------------------------------------------------------
//by longzoro
#define _SASQL                   // 石器資料庫
#ifdef _SASQL
	#define _SQL_BACKGROUND        //網頁後颱功能   需同時開放_SASQL1
	#define _SQL_REGISTER          //自動注冊功能   需同時開放_SASQL1
#endif

#if _ATTESTAION_ID != 11
#define _LOGNZORO_FUNC_ALL       // 龍zoro新增功能
#endif
#ifdef _LOGNZORO_FUNC_ALL
	#define _NEW_VIP_SHOP            // 會員商店
	
	#if _ATTESTAION_ID != 8 && _ATTESTAION_ID != 10 && _ATTESTAION_ID != 21 
		#define _ITEM_PET_LOCKED         // 物品寵物鎖
	#endif
	
	#if _ATTESTAION_ID != 3
		#define _ONLINE_COST             // 在綫充值
		#define _SQL_BUY_FUNC            // SQL購買功能
		#define _VIPPOINT_OLD_TO_NEW     // 會員點舊轉新
	#endif
	
	#if _ATTESTAION_ID == 5
		#define _FORMULATE_AUTO_PK       // 製定自動化PK係統
	#else
		#define _OLDPS_TO_MD5PS         // 把舊的密碼轉成MD5密碼
		#ifdef _NEW_VIP_SHOP
			#if _ATTESTAION_ID != 3
				#define _COST_ITEM             // 充值道具
			#endif
		#endif
		#if _ATTESTAION_ID != 21
			#define _AUTO_BACKUP           // 自動備份
		#endif
		#define _FIX_CAHR_VERSION      // 存檔版本更改
		#if _ATTESTAION_ID != 38 && _ATTESTAION_ID != 49
			#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 21 || _ATTESTAION_ID == 23 || _ATTESTAION_ID == 28 || _ATTESTAION_ID >= 30
				#define _LOTTERY_SYSTEM          // 彩票係統
			#endif	
		#endif	
	#endif
#endif

#if _ATTESTAION_ID != 5 && _ATTESTAION_ID != 11
	#define FAMILY_MAX_MEMBER 			100 	// 傢族人數
#else
	#define FAMILY_MAX_MEMBER       50		// 傢族人數
#endif

#if _ATTESTAION_ID != 11
	#define _CHARADATA_SAVE_SQL      //將數據寫入SQL
#endif
#if 1
	#define _ONE_SERVER              // 單機綁定
#endif

#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 21 || _ATTESTAION_ID ==31 || _ATTESTAION_ID ==33 || _ATTESTAION_ID >=35
	#define _ALL_SERV_SEND       // 星球頻道
#endif
#if _ATTESTAION_ID == 1 || _ATTESTAION_ID == 2 || _ATTESTAION_ID == 3 || _ATTESTAION_ID == 21 || _ATTESTAION_ID ==31 || _ATTESTAION_ID ==33 || _ATTESTAION_ID ==35 || _ATTESTAION_ID >=42
	#if _ATTESTAION_ID != 43 && _ATTESTAION_ID != 47 && _ATTESTAION_ID != 49 
		//#define _DEATH_FAMILY_LOGIN_CHECK			//刪除人數不足之傢族或太久未上綫之成員
	#endif
#endif


#if _ATTESTAION_ID == 1
	//#define _SET_FMPOINT
	//#define _FAMILY_TOTEM
	#define _NEWCLISETMAC
	#define _FAMILY_PAY_POINT			//傢族充值積分
#endif

#if _ATTESTAION_ID == 0
	#define _DEBUG
#endif

#endif



