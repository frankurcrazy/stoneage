//cyg  實作第一個係統 (綫上迴報係統)
#include"../systeminc/version.h"
#include"../systeminc/system.h"
#include"../systeminc/loadrealbin.h"
#include"../systeminc/loadsprbin.h"
#include"../systeminc/anim_tbl.h"
#include"../systeminc/login.h"
#include"../systeminc/menu.h"
#include"../systeminc/map.h"
#include"../systeminc/lssproto_cli.h"
#include"../systeminc/pc.h"
#include"../systeminc/netmain.h"
#include"../systeminc/handletime.h"
#include"../systeminc/character.h"
#include"../other/caryIme.h"
#include"../systeminc/ime_sa.h"
#include"../systeminc/t_music.h"
#include"../systeminc/netproc.h"
#include"../systeminc/tool.h"
#include "time.h"
#include "../wgs/descrypt.h"
#include"../systeminc/onlinegm.h"

char ProblemClass[DEF_CLASS_TOTAL][16]={
	"異常問題",
	"一般問題"
};
char ProblemC1[DEF_C1_TOTAL][30]={
	"卡人卡石",
    "網頁指正",
	"客服産品活動",
	"安裝與更新",
	"會員帳號",
	"産品序號",		
	"贈品序號",
	"遊戲點數卡購買及儲值",
	"包月相關",
	"超級/炫風來吉卡/周邊商品",
	"服務器/連綫/網路狀況反應",
    "遊戲操作詢問",
	"非法檢舉投拆",
	"其他"	
};
char ProblemC1Help[DEF_C1_TOTAL][60]={
	"請注明異常帳號、座標、地點、錯誤訊息、星係",
	"請提供相關連結",
	"請先查詢遊戲專屬網站以及過往客服公告",
	"請盡量留下您的電腦配備",
	"請詳述遇到的狀況",
	"請提供完整的序號",
	"請提供完整的序號",
	"登入遊戲發現扣點不正常，請改選擇問題類彆為(遊戲扣點問題)",
	"",
	"請先查詢專屬網頁相關活動",
	"",
	"請先查詢網頁FAQ",
	"",
	""
};
char ProblemC2[DEF_C2_TOTAL][16]={
	"人物異常",
	"道具異常",
	"寵物異常",
	"交易問題",
	"疑似盜用",
	"傢族問題",
	"寵物＆道具問題",
	"ＷＧＳ扣點問題",
	"其他",  
	"會員升級",
	"星係移民",	
};
//人物異常
char ProblemC2_1[3][16]={
	"人物消失",
	"人物資料異常",
	"其他"
};
//道具異常
char ProblemC2_2[3][16]={
	"道具消失",
	"其他",
	"道具功能異常"
};
//寵物異常
char ProblemC2_3[5][16]={
	"寵物消失",
	"寵物郵件問題",
	"溜寵問題",
	"寵物蛋問題",
	"其他"
};
//交易問題
char ProblemC2_4[2][16]={
	"交易後消失",
	"其他"
};
//疑似盜用
char ProblemC2_5[2][16]={
	"疑似盜用查詢",
	"其他"
};
//傢族問題
char ProblemC2_6[3][16]={
	"傢族被解散",
	"聲望異常",
	"其他"
};
//星係移民
char ProblemC2_7[3][16]={
	"道具消失",
	"人物消失",
	"其他"
};

//HELP中使用到的頁資料結構
typedef struct PAGE{
	short	desc_index;			//說明結構開始的索引號(此desc_index為根據seg_index在help_index取得DESC的陣列的index)
	int		desc_num;//BYTE	desc_num;			//說明的結構數
}*LPPAGE;

//注意事項
//HELP中使用到說明的文字資料結構
typedef struct DESC{
	BYTE	color;				//顔色
	char	description[60];	//說明文字
}*LPDESC;


// 問題參數儲存結構 cyg  
typedef struct{
	char no[20];
	char state[40];	  							
	char okdate[10];
	int  okH;
	char wrongdate[10];
	int  wrongH;
	int	 class0;
	char class1[40];
	char cont[4000];
	char answer[4000];
	char error[2000];
	BOOL delflag;
}PRODATA;


DESC Prohelp_desc1[]={
			//顔色與說明 //fix				
			{ 4 , "1. 使用說明"},
			{ 0 , "		綫上留單上限為20筆，若已達上限須先將舊有問題單刪除，纔能"},
			{ 0 , "		繼續留單或至網頁留單。異常問題須輸入正常日期與錯誤日期。"},
			{ 0 , "		※ 最新問題單會顯示在最上方。"},
			{ 4 , "2. 寵物蛋異常"},
			{ 0 , "		於2003/12/31日服務器更新時，己放置修正寵物蛋設定的程式"},
			{ 0 , "		，即日起客服中心將不再受理玩傢寵物蛋能力異常的情況，修正"},
			{ 0 , "		後的寵物蛋設定如下："},
			{ 0 , "		※ 人物在綫上喂養設定和以往一樣，超過一小時會有能力下"},
			{ 0 , "		   降的情況。人物離綫或寵物蛋放置在寵店中，再次登入會"},
			{ 0 , "		   重新計算喂養的時間。"},
			{ 4 , "3. 溜寵消失"},
			{ 0 , "		遊戲程式設定己可在同一顆服務器內，與薩村門口的[工程人員]"},						
};

DESC Prohelp_desc2[]={
			{ 0 , "		取迴；如無法領取請提供以下資料寵物名稱、等級、寵物原持有"},
			{ 0 , "		帳號、寵物持有日期、寵物消失日期。"},
			{ 4 , "4. 寵郵消失"},
			{ 0 , "		遊戲程式設定己可在同一顆服務器內，與薩村門口的[工程人員]"},
			{ 0 , "		取迴；如無法領取請提供以下資料寵物名稱、等級、寵物原持有"},
			{ 0 , "		帳號、寵物持有日期、寵物消失日期。"},
			//{ 4 , "4. 寵物戰鬥脫逃-無法處理"},
			//{ 0 , "		寵物的忠誠度低於20以下，在戰鬥中就會跑走。此為原遊戲設定"},
			//{ 0 , "		，客服中心不受理迴覆寵物。"},
			{ 4 , "5. 交易後物品消失-請提供以下資料"},
			{ 0 , "		交易方的帳號或人物名稱、交易日期、交易的寵物名稱以及等級"},
			{ 0 , "		、道具名稱以及數量。"},
			{ 4 , "6. 寵物或道具賣給NPC-無法處理"},
			{ 0 , "		此為原遊戲設定，客服中心不受理迴覆寵物或道具。"},
			{ 4 , "7. 寵物或道具丟齣後被係統清除-無法處理"},
			{ 0 , "		此為原遊戲設定，客服中心不受理迴覆寵物或道具；玩傢可在遊"},			
};

DESC Prohelp_desc3[]={
			{ 0 , "		戲中透過交易介麵轉移。"},
			{ 4 , "8. 傢族異常-請提供以下資料"},
			{ 0 , "		傢族異常請族長本人帳號留單，注明傢族名稱、傢族編號、異常"},
			{ 0 , "		狀況。如因為傢族人數不足，係統自動解散的傢族，連同傢族銀"},
			{ 0 , "		行存款客服中心無法受理。"},
			{ 0 , "		※ 對於傢族解散與成員因過久未上綫而自動退齣傢族設定，係"},
			{ 0 , "		   統每天會不定時的掃描、偵測。"},
			{ 0 , "		※ 目前傢族成員設定，在退齣後7日內無法再加入傢族。"},
			{ 4 , "9. 人物DP異常-無法處理	"},
			{ 0 , "		由於DP對於遊戲中並不會有影響，並無開放此功能供玩傢查詢。"},
			{ 4 , "10. 人物名片消失-無法處理"},
			{ 0 , "		由於名片的對應會有一對多的情況(一個人物擁有多位玩傢的名"},
			{ 0 , "		片)，若單方麵僅處理一名玩傢並無法使資料正確，並無開放此"},
};

DESC Prohelp_desc4[]={
			{ 0 , "		功能供玩傢查詢。"},
			{ 4 , "11. 盜用&詐騙案件-請提供以下資料"},
			{ 0 , "		寵物名稱、等級以及道具名稱、數量、疑似盜用日期 工程人員"},
			{ 0 , "		可查詢人物刪除紀錄，需請玩傢不要創立新人物以便迴覆空人物"},
			{ 0 , "		(沒有寵物、道具以及石幣)。 工程人員僅以玩傢提供之道具、"},
			{ 0 , "		寵物進行查詢的動作。"},
			{ 4 , "12. 硃雀轉生設定  2003/06/21"},
			{ 0 , "		活動贈送之硃雀能力值，於轉生後仍有小幅成長空間，但原能力"},
			{ 0 , "		值部份不一定能維持轉生前高點，在此提醒玩傢要轉生硃雀時，"},
			{ 0 , "		請多加考慮。客服中心不受理迴覆轉生前硃雀之留單案件。"},
};

//DESC Prohelp_desc5[]={
//};

LPDESC Prohelp_Index[] ={
	&Prohelp_desc1[0],
	&Prohelp_desc2[0],
	&Prohelp_desc3[0],
	&Prohelp_desc4[0]
//	&Prohelp_desc5[0]
};

PAGE ProHelp_page[]={
			{ 0 , sizeof(Prohelp_desc1)/sizeof(Prohelp_desc1[0])},
			{ 0 , sizeof(Prohelp_desc2)/sizeof(Prohelp_desc2[0])},
			{ 0 , sizeof(Prohelp_desc3)/sizeof(Prohelp_desc3[0])},
			{ 0 , sizeof(Prohelp_desc4)/sizeof(Prohelp_desc4[0])}
//			{ 0 , sizeof(Prohelp_desc5)/sizeof(Prohelp_desc5[0])}
};


INPUT_HISTORY  InputHistory ;	// 用來記憶每一行的內容，往後纔能拿來索引

STR_BUFFER  SubBuffer ;		//  每一行儲存的buf

#ifdef __ONLINEGM  // 全關掉

char DataBuffer[500];		//  儲存組閤好的問題迴報一連串的參數
char InputBuffer[8050];		//  儲存玩傢的輸入內容   
char ContentBuf[8050];		//  儲存組閤好的問題內容

PRODATA  Prodata[100];		//  假設玩傢最多可以建100筆

int		PutKey,PushKey ; 

int		ProNoSelect;        //	現在正選擇的單號索引
int     HistorySelect;      //  上次選擇查詢的單號索引
BOOL	ProNoSelectFlag;	//  有沒有選單號的旗標
int		ProNoIndex;			//  用來秀問題單號
int		ProNoValue;			//  錶示有幾筆問題單號

BOOL    TitleFlag ;			
int     SegmentIndex ;		//  一段一段內容的索引
int     SegmentTotal ;		//  紀錄總共有幾段
char    SegmentBuf[2][2500];//  紀錄某筆單號的內容和客服迴應

int		okY,okM,okD,okH,wrongY,wrongM,wrongD,wrongH;
int 	ClassIndex , ClassIndex1 , ClassIndex2 ;  //  問題類彆索引

BOOL	DeleteBtnFlag;      //要有選到某單號纔能刪除的旗標
      

//OnlineGm 的Log 專用區 Begin
#ifdef _STONDEBUG_
char    inlogstr[512];
#define filename     "onlinegm.log"
#endif
//OnlineGm 的Log 專用區 End

//綫迴係統 測試Server IP : 10.1.0.17 

BOOL QueryOnlineGmIP(char HostName[]);
char *OnlineGmIP;	   //使用domain name
//char OnlineGmIP[20];   //使用直接ip
#define SMSDomainName   "ingame.wayi.com.tw"//"sms.hwaei.com.tw"

int     ResultCode;  // 傳輸産生的偵錯碼 

static char *pContent=NULL;

BOOL ResetFlag = TRUE;
BOOL DirFlag = TRUE;
DWORD  LastTime = 0;
int  iReturnNo;  //紀錄迴傳的單號

int	 TotalAddValue;   //紀錄玩傢目前留單總數

int  ProblemType ;  //紀錄按傳送鍵時問題單的類型  一般0異常1
int  SendType    ;  //紀錄傳送給server前的問題類型

unsigned int  ichecklooptime = 0;    //檢查連綫迴圈時間

//*************************************
//	初始資料
//*************************************
void InitOnlineGm( void )
{
	int i;
	
	PutKey = 0;
	PushKey = 0;
	ProNoSelectFlag = FALSE;
	ProNoSelect = 0;
	HistorySelect = 5000;  //無意義 區彆用
	ProNoIndex = 0;
	ProNoValue = 0;
	SegmentIndex =0;
	SegmentTotal = 0;
	okY=okM=okD=okH=wrongY=wrongM=wrongD=wrongH=0;
	ClassIndex = 1;
	ClassIndex1 = ClassIndex2 =0;
	
	ResetFlag = TRUE ;
	DirFlag = TRUE ;
	DeleteBtnFlag = FALSE ;

	DataBuffer[0] = '\0';
	InputBuffer[0] = '\0';
	ContentBuf[0] = '\0';

	SegmentBuf[0][0]='\0';
	SegmentBuf[1][0]='\0';

	for( i=0;i<DEF_MAX_ADD_VALUE;i++){
		Prodata[i].no[0] = '\0';
		Prodata[i].state[0] = '\0';
		Prodata[i].okdate[0] = '\0';	
	    Prodata[i].okH = 0;
		Prodata[i].wrongdate[0] = '\0';
		Prodata[i].wrongH = 0;	
		Prodata[i].class0 = 0;	
		Prodata[i].class1[0] = '\0';
		Prodata[i].cont[0] = '\0';
		Prodata[i].answer[0] = '\0';	
		Prodata[i].error[0] = '\0';
		Prodata[i].delflag = FALSE;		
	}
	LastTime = 0;
	iReturnNo = 0;
	TotalAddValue = 0;
	ProblemType = 0;
	SendType = 0;
}

//************************************************
//函式 : 産生Log檔(於Local端目錄下)的專用函式
//迴傳值 : None
//附  注 : 隻有Debug mode纔在硬碟寫入log檔!!
//************************************************
#ifdef _STONDEBUG_
void WriteInLog( char cData[], char cFile[])
{
	char totals[65536];//[1024];
	struct tm nowTime;
	time_t longTime;
	time( &longTime );
	localtime_s(&nowTime, &longTime );
	sprintf_s(totals,"%02d/%02d/%02d %02d:%02d:%02d ",(nowTime.tm_year % 100), nowTime.tm_mon+1, nowTime.tm_mday,
				nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	lstrcat(totals,cData);
	lstrcat(totals,"\r\n\r\n\r\n");
	FILE *fp;
	fp = fopen(filename, "a" );
	if(fp)
	{
		fprintf(fp,totals);
		fclose(fp);
	}
}
#endif

//************************************************
//函式一 : 處理主程式與ASP間溝通的專用函式
//迴傳值 :  0 --- 處理完畢 & 問題迴報成功
//         1 --- 問題迴報發送失敗
//         2 --- 手機號碼參數錯誤(時間或類彆錯誤)
//         3 --- 手機訊息參數錯誤(過長)
//         4 --- 網路端錯誤
//         5 --- WGS點數(或通數)已不足!!(小於五點)
//         6 --- 連綫逾時(或DNS失敗)
//         7 --- ASP迴傳錯誤
//************************************************
// pid:id ppw:password pdb:內部資料 pinput:玩傢輸入的內容
int SendProblemMsg(char pid[16], char ppw[16], char pdb[] , char pinput[])
{
	char returndata[20] ;  //紀錄迴傳的字串
	int nRet,wait=1;

	if(!QueryOnlineGmIP(SMSDomainName)) return 6;
	//if((pdb[0] =='\0') || (lstrlen(pdb) != 23)) return 2;    
	//if(lstrlen(pc.name)>16)	return 3;

#ifdef _FIX_URLENCODE
		char OutTmp[8000];
		char *pOutTmp ;
		char *pInTmp ;
		char Hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
		//  do  encoding
		pInTmp=pinput;
		pOutTmp=OutTmp;
		while  (*pInTmp)
		{
			if ( (*pInTmp>= '0') && (*pInTmp <= '9') 
				||	(*pInTmp>= 'a') && (*pInTmp <= 'z')
				||	(*pInTmp>= 'A') && (*pInTmp <= 'Z') 
				)
				*pOutTmp++  =  *pInTmp;
			else
			{
				if(*pInTmp==0x20&&(!IsDBCSLeadByte(*pInTmp)))
					*pOutTmp++  =  '+';
				else
				{
					*pOutTmp++  =  '%';
					*pOutTmp++  =  Hex[(*pInTmp>>4)&0x0f];
					*pOutTmp++  =  Hex[(*pInTmp)&0x0f];
				}
			}
				
				pInTmp++;
				
		}
		*pOutTmp  =  '\0';
		sprintf_s(pinput,8050,"&qcontent=%s",OutTmp);
#endif

	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;
	int   len, cnt, ret ;
	
	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80);
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[3000];  
				if(ProblemType==0){   
					SendType=0;		//一般問題
					sprintf_s(buf,"GET //normal_check.asp?wgsid=%s&gamepwd=%s&game=1%s%s",pid,ppw,pdb,pinput);   
				}else{
					SendType=1;		//異常問題
					sprintf_s(buf,"GET //handle_check.asp?wgsid=%s&gamepwd=%s&game=1%s%s",pid,ppw,pdb,pinput);   
				}
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
#ifdef _STONDEBUG_   //寫入onlinegm.log
			WriteInLog( buf , filename);
#endif
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}else if(nRet == 0){
						closesocket(hSock);
						return 8;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() - ichecklooptime > 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
				Sleep(500);
				len = (InputHistory.newNo*70)+500 ; //1024;
				cnt = 0;
				ichecklooptime = TimeGetTime();  
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return 8;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
				 		ret = recv( hSock, &buf[cnt], len, 0);
						if(ret<0){
							closesocket(hSock);
							return 4;
						}
					}
					buf[cnt+ret] = 0;
					result = strstr( buf, "\r\n\r\n") + 4;
					getStringToken(result ,',',1,sizeof(returndata)-1,returndata);
					if(atoi(returndata)!=1){  //如果迴傳負數錶示有誤，1錶示ok
						closesocket(hSock);
						return atoi(returndata);
					}else{ 
						getStringToken(result ,':',2,sizeof(returndata)-1,returndata);
						iReturnNo = atoi(returndata);  //讀齣單號
					}
					if(result)  break;
					cnt += ret;
					len -= ret;
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
			}else{
				closesocket(hSock);
				return 6;
			}
		}	
		closesocket(hSock);
		return 1;
	}
	return 4;			
}

//************************************************
// 傳送要刪除單號的主程式
// 迴傳值 :0 --- 處理完畢 & 問題刪除成功
//		   3 --- 參數傳遞錯誤
//         4 --- 網路端錯誤
//         6 --- 連綫逾時(或DNS失敗)
//************************************************
int SendDeleteMsg(char pid[16], char ppw[16] , char pno[16] )
{
	int nRet;
	if(!QueryOnlineGmIP(SMSDomainName)) return 6;

	int ret,len,cnt,icheck,wait=1;
	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;
	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80); 
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[1024];
				sprintf_s(buf,"GET //DelForm.asp?wgsid=%s&gamepwd=%s&rcount=1&idno=%s",pid,ppw,pno);				
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}else if(nRet == 0){
						closesocket(hSock);
						return 8;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
				Sleep(500);
				len = 1024;
				cnt = 0;
				ichecklooptime = TimeGetTime();
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return 8;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					nRet =  select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
						ret = recv( hSock, &buf[cnt], len, 0);							
						if(ret<0){
							closesocket(hSock);
							return 4;
						}
						buf[cnt+ret] = 0;
						result = strstr( buf, "\r\n\r\n") + 4;
						char *sss;
						strtok_s(result,",",&sss);
						icheck=atoi(result);
						if(icheck != 1){
							closesocket(hSock);
							return icheck;
						}
						if(result)  break;
						cnt += ret;
						len -= ret;
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
			}else{
				closesocket(hSock);
				return 6;
			}
		}
		closesocket(hSock);
		return 1 ;
	}
	return 4 ;
}

//************************************************
//	嚮Server要玩傢的問題單所有內容
//  迴傳值 0: 正確無誤
//         2: 玩傢無任何問題單
//         4: 網路端錯誤
//         6: 連綫逾時(或DNS失敗)
//************************************************
int SendDirMsg(char pid[16], char ppw[16] )
{
	if(!QueryOnlineGmIP(SMSDomainName)) return 6;

	int nRet,i=1;
	int wait=1,j=1;		
	char alldata[65536],getdata[6000],perdata[3000],statedata[100];  //全部的,每筆,每欄,處理狀態
	char returndata[20] ;
	BOOL Okflag = FALSE , Firstflag = TRUE;
#ifdef _STONDEBUG_
	char logbuf[50];
#endif
	int ret,len,cnt; 
	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;

	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	memset(alldata,0,sizeof(alldata));
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80); 
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[65536];
				sprintf_s(buf,"GET //userFormList.asp?wgsid=%s&gamepwd=%s",pid,ppw);				
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return -400;
					}else if(nRet == 0){
						closesocket(hSock);
						return -800;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return -800;
					}
				}				
				Sleep(500);
				len = 65536;//8000;
				cnt = 0;
				ichecklooptime = TimeGetTime();
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return -800;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					nRet = select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return -400;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
						ret = recv( hSock, &buf[cnt], len, 0);							
						if(ret<0){
							closesocket(hSock);
							return -400;
						}								
						buf[cnt+ret] = 0;   
						result = strstr( buf, "\r\n\r\n") + 4;
						if(strcmp(result,"0")==0){
							closesocket(hSock);
							return -200;
						}
						strcpy(alldata,result);
						cnt += ret;
						len -= ret;
					}
					if(strstr(alldata,"&#")){ //ok
						break;
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return -800;
					}
				}
				getStringToken(result ,',',1,sizeof(returndata)-1,returndata);
				if(atoi(returndata)<0){  //如果迴傳負數錶示有誤，大於0數子代錶單子數量，同時也錶示ok
					closesocket(hSock);
					return atoi(returndata);
				}else{
					TotalAddValue = atoi(returndata);
				}
				result = alldata;
				result = strstr( result , ",") + 1;
				strcpy(alldata,result);	
			}else{
#ifdef _STONDEBUG_
				sprintf_s(logbuf,"Get last error:%d",WSAGetLastError());
				WriteInLog( logbuf , filename);
#endif
				return -600;
			}
		}
		closesocket(hSock);
		ProNoValue = 0;
		ProNoSelectFlag = FALSE;
#ifdef _STONDEBUG_   //寫入onlinegm.log
			WriteInLog( alldata , filename);
#endif
		perdata[0] = '\0';
		getdata[0] = '\0';
		//sprintf_s(alldata,"21|測試|*|*|*|*|18|卡人卡石|親愛的維護部阿俊您好謝謝您的用心與努力~感謝您的支持與愛護！也再次的預祝您修改愉快！順心如意！|親愛的維護部阿俊您好謝謝您的用心與努力~感謝您的支持與愛護！也再次的預祝您修改愉快！順心如意！|&#");
		while(getStringToken( alldata,'&',i,sizeof(getdata)-1,getdata)!=1){
			while(getStringToken(getdata,'|',j,sizeof(perdata)-1,perdata)!=1){
				if( strcmp( perdata , "*")){
					switch(j){
					case 1:sprintf_s(Prodata[ProNoValue].no,"%s",perdata); break;
					case 2:
						getStringToken(perdata,'>',2,sizeof(statedata)-1,statedata);
						getStringToken(statedata,'<',1,sizeof(statedata)-1,statedata);
						if(lstrlen(statedata) == NULL)
							sprintf_s(Prodata[ProNoValue].state,"%s",perdata);
						else
							sprintf_s(Prodata[ProNoValue].state,"%s",statedata);
						break;
					case 3:sprintf_s(Prodata[ProNoValue].okdate,"%s",perdata);break;
					case 4:Prodata[ProNoValue].okH=atoi(perdata); break;
					case 5:sprintf_s(Prodata[ProNoValue].wrongdate,"%s",perdata);break;
					case 6:Prodata[ProNoValue].wrongH=atoi(perdata); break;
					case 7:Prodata[ProNoValue].class0=atoi(perdata);break;
					case 8:sprintf_s(Prodata[ProNoValue].class1,"%s",perdata);break;
					case 9:sprintf_s(Prodata[ProNoValue].cont,"%s",perdata);break;
					case 10:sprintf_s(Prodata[ProNoValue].answer,"%s",perdata);break;
					default: sprintf_s(Prodata[ProNoValue].error,"%s",perdata);break;
					}
				}
				perdata[0] = '\0';
				j++;		
			}
			getdata[0] = '\0';
			ProNoValue++;
			j=1; 
			i++;
		}
		//TotalAddValue = ProNoValue; 
		return 1 ; // ok
	}
	return 4 ;
}
//************************************************
//	查詢問題單的內容
//************************************************
void vReadContent( int pno )
{
	static char *pRecv ;
	char date[10];
	char data[40];
	char classbuf1[40],classbuf2[40];
	int i=1;
		
	ClassIndex=Prodata[pno].class0 - 18;

	if(ClassIndex == 0 ){   //異常問題
		while(getStringToken(Prodata[pno].okdate,'/',i,sizeof(date)-1,date)!=1){ 
			if( i==1 )	okY = atoi(date);
			else if( i==2)	okM = atoi(date);
			i ++;
		}
		okD = atoi(date);
		okH = Prodata[pno].okH;
		i = 1;
		date[0] = '\0';
		while(getStringToken(Prodata[pno].wrongdate,'/',i,sizeof(date)-1,date)!=1){ 
			if( i==1 )	wrongY = atoi(date);
			else if( i==2)	wrongM = atoi(date);
			i ++;
		}
		wrongD = atoi(date);
		wrongH = Prodata[pno].wrongH;
	}

	if(getStringToken(Prodata[pno].class1,',',1,sizeof(data)-1,data)!=1){ 
		sprintf_s(classbuf1,"%s",data);
		data[0] = '\0';
		if(getStringToken(Prodata[pno].class1,',',2,sizeof(data)-1,data)==1) 
			sprintf_s(classbuf2,"%s",data);
	}else{
		sprintf_s(classbuf1,"%s",data);
	}

	if(ClassIndex){ // 一般問題
		for(i=0;i<DEF_C1_TOTAL;i++){
			if(strcmp(ProblemC1[i],classbuf1)==NULL)
			break;
		}
		ClassIndex1 = i;
	}else{			// 異常問題
		for(i=0;i<DEF_C2_TOTAL;i++){
			if(strcmp(ProblemC2[i],classbuf1)==NULL)
			break;
		}
		ClassIndex1 = i;
		switch(ClassIndex1){
		case 0: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_1[i],classbuf2)==NULL)
					break;
				}break;
		case 1: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_2[i],classbuf2)==NULL)
					break;
				}break;
		case 2: for(i=0;i<5;i++){
					if(strcmp(ProblemC2_3[i],classbuf2)==NULL) 
					break;
				}break;
		case 3: for(i=0;i<2;i++){
					if(strcmp(ProblemC2_4[i],classbuf2)==NULL) 
					break;
				}break;
		case 4: for(i=0;i<2;i++){ 
					if(strcmp(ProblemC2_5[i],classbuf2)==NULL) 
					break;
				}break;
		case 5: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_6[i],classbuf2)==NULL)
					break;
				}break;
		case 10:for(i=0;i<3;i++){
					if(strcmp(ProblemC2_7[i],classbuf2)==NULL)
					break;
				}break;
			default: i=0;
		}
		ClassIndex2=i;
	}
		
	if (lstrlen(Prodata[pno].cont)!=NULL){
		sprintf_s(SegmentBuf[SegmentTotal],"%s",Prodata[pno].cont);
		SegmentTotal++;
		if(lstrlen(Prodata[pno].answer)!=NULL){
			sprintf_s(SegmentBuf[SegmentTotal],"%s",Prodata[pno].answer);
			SegmentTotal++;
		}
	}
}

//************************************************
//函式	: 資料輸入欄位的初始化函式
//迴傳值	: None
//************************************************
void InitOnlineGmInput(int x, int y)
{
	int i;

	HistorySelect = 5000;

	SubBuffer.buffer[0]='\0';
	SubBuffer.x = x + 20;  
	SubBuffer.y = y + 400; 
	SubBuffer.len = 70;				//字數
	SubBuffer.color = FONT_PAL_AQUA;
	SubBuffer.fontPrio = FONT_PRIO_FRONT;
	SubBuffer.lineLen=70;			//每行幾個字
	SubBuffer.lineDist=25;		//行與行間隔幾個pixel

	InputHistory.newNo = 0;
	InputHistory.nowNo = 0;
	InputHistory.addNo = 0;
	InputHistory.lockNo = 0;
	for ( i=0;i<115;i++ )  
	{
		InputHistory.str[i][0]='\0';
		InputHistory.color[i]=FALSE; 
	}

	int len = lstrlen(SubBuffer.buffer);
	if(len){
		SubBuffer.cursor = len;
		SubBuffer.cnt= len;
	}else{
		SubBuffer.cnt=0;
		SubBuffer.cursor=0;
	}
	TitleFlag = TRUE;
}

//************************************************
//函式   : 處理問題單號的主函式
//迴傳值 : None
//************************************************
void ShowProblemNo( int x, int y, int Key )
{
	int i,k,word = 0;
	int Keyid;
	char buf[100]= "/0";
	static int fontId[5];
	static char *pChar ;
	
	if (Key==1){  //上箭頭
		ProNoIndex -- ;
		if (ProNoIndex < 0 ) 
			ProNoIndex = 0 ;
	}
	else if(Key==2){	//下箭頭
		ProNoIndex ++ ;
		if (ProNoIndex == ProNoValue)
		ProNoIndex = ProNoValue-1;
	}

	for ( i=0;i<5;i++ ){ // 總共五行 
		if (ProNoIndex+i>=ProNoValue)
			break ;
		if (ProNoIndex+i==ProNoSelect && ProNoSelectFlag == TRUE){
			sprintf_s(buf,"%s                 %s",Prodata[ProNoIndex+i].no,Prodata[ProNoIndex+i].state);  
			fontId[i] = StockFontBuffer( x + 20 , y+7+(i*20) , FONT_PRIO_FRONT, 1 , buf , 2 );
		}else{
			sprintf_s(buf,"%s                 %s",Prodata[ProNoIndex+i].no,Prodata[ProNoIndex+i].state);  
			fontId[i] = StockFontBuffer( x + 20 , y+7+(i*20) , FONT_PRIO_FRONT, 0 , buf, 2 );
		}
		if(Prodata[ProNoIndex+i].delflag == TRUE){
			sprintf_s(buf,"已刪除");
			StockFontBuffer( x + 70 , y+7+(i*20) , FONT_PRIO_FRONT, 4 , buf, 2 );
		}
	}

	Keyid = selFontId( fontId, sizeof( fontId )/sizeof( int ) );
	if ( 0 <= Keyid && Keyid < 5 ){
		if (ProNoIndex + Keyid < ProNoValue){   
			//查詢某比單號的內容
			ProNoSelectFlag = TRUE;
			ProNoSelect = ProNoIndex + Keyid;
			if ( ProNoSelect != HistorySelect ){
				HistorySelect = ProNoSelect;
				InitOnlineGmInput(x, y);
				SegmentIndex = 0;
				SegmentTotal = 0;
				SegmentBuf[0][0] = '\0';
				SegmentBuf[1][0] = '\0';
				vReadContent( ProNoSelect );
			}
		}
	}
	
	if( SegmentTotal > SegmentIndex  ){  //   秀齣內容
		InputHistory.addNo =0;  // 非玩傢輸入所以不用加
		GetKeyInputFocus(&SubBuffer);
		if( SegmentIndex %2 == 0 ){
			if(TitleFlag==TRUE){ 
				StrToNowStrBuffer1("前次問題內容：");
				for ( k=0;k<60+10;k++ )   
					StrToNowStrBuffer(" ");
				InputHistory.color[InputHistory.newNo]=TRUE;
				pContent = SegmentBuf[SegmentIndex];
				TitleFlag = FALSE;	
			}else{
				if(pContent!=NULL){
					word = StrToNowStrBuffer2(pContent);
					pContent+=word ;
					if(word<70){
						for ( k=0;k<(80-word);k++ )   
							StrToNowStrBuffer(" ");
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}				
					/*
					if (i>70){
						StrToNowStrBuffer(pContent);
						pContent+=70 ;
					}else{
						StrToNowStrBuffer(pContent);
						pContent+=i ;
						for ( k=0;k<(70-i);k++ )   //cyg 補空格
							StrToNowStrBuffer(" ");
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}
					*/
				}
			}
		}else{
			if(TitleFlag==TRUE){ 
				StrToNowStrBuffer1("客服解答：");
				for ( k=0;k<60+10;k++ )   //cyg 補空格
					StrToNowStrBuffer(" ");
				InputHistory.color[InputHistory.newNo]=TRUE;
				pContent = SegmentBuf[SegmentIndex];
				TitleFlag = FALSE;
			}else{
				if(pContent!=NULL){
					word = StrToNowStrBuffer2(pContent);
					pContent+=word ;
					if(word<70){
						for ( k=0;k<(80-word);k++ ){   
							StrToNowStrBuffer(" ");
						}
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}
				}
			}
		}
	}else{ 
		if( TitleFlag == TRUE ){
			GetKeyInputFocus(&SubBuffer);
			StrToNowStrBuffer1("新增問題內容：");
			for ( k=0;k<56+10;k++ )   
				StrToNowStrBuffer(" ");
			InputHistory.color[InputHistory.newNo]=TRUE;
			TitleFlag = FALSE;
			InputHistory.addNo = 0;
			InputHistory.lockNo = InputHistory.newNo;
			
		}
	}
}

//************************************************
//函式   : 處理資料輸入欄位的主函式
//迴傳值 : None
//************************************************
void InputOnlineGmData( int x, int y, int Key )
{
	int Changelineflag = 0;
	int i;

	if ( InputHistory.newNo - InputHistory.nowNo <= 4)
		GetKeyInputFocus(&SubBuffer);
	else
		pNowStrBuffer = NULL ;
	
	if (Key == 1)  //上箭頭
	{
		if (InputHistory.newNo >4 && InputHistory.nowNo ){
			InputHistory.nowNo -- ; 
			if (InputHistory.newNo - (InputHistory.nowNo+4) == 1 ){
				strcpy( InputHistory.str[ InputHistory.newNo ],SubBuffer.buffer);
				SubBuffer.buffer[0] = NULL ;
			}
		}
	}
	if (Key == 2) // 下箭頭
	{
		if (InputHistory.newNo >4){
			if (InputHistory.nowNo+4<InputHistory.newNo){
				InputHistory.nowNo ++ ; 
				if (InputHistory.nowNo+4==InputHistory.newNo){
				GetKeyInputFocus(&SubBuffer);
				strcpy( SubBuffer.buffer,InputHistory.str[ InputHistory.newNo ] );
				}
			}
		}
	}

	Changelineflag = StockFontBuffer3( &SubBuffer );
	if (Changelineflag){ // 換行 
		if(InputHistory.addNo < 30 ){  //0~29
			SubBuffer.cnt=0;
			SubBuffer.cursor=0;
			if (SubBuffer.y< y + 410)
				SubBuffer.y += SubBuffer.lineDist ; 
			strcpy( InputHistory.str[ InputHistory.newNo ],SubBuffer.buffer);
			SubBuffer.buffer[0]='\0';				
			InputHistory.newNo++;
			InputHistory.addNo++;
			if (InputHistory.newNo >= 5)
				InputHistory.nowNo = InputHistory.newNo -4; 
		}else{
			//SubBuffer.cursor
		}
	}
	
	for ( i=0;i<5;i++ ) // 總共五行 
	{
		if ((InputHistory.nowNo+i)!=InputHistory.newNo){
			if(InputHistory.color[InputHistory.nowNo+i]==FALSE)
				StockFontBuffer( SubBuffer.x , y+300+(i*(30-5)) , FONT_PRIO_FRONT, 0 ,InputHistory.str[ InputHistory.nowNo+i ], 0 );
			else
				StockFontBuffer(  SubBuffer.x , y+300+(i*(30-5)) , FONT_PRIO_FRONT, 5 ,InputHistory.str[ InputHistory.nowNo+i ], 0 );
		}
	}
}

HANDLE GMHandle;
extern char szUser[],szPassword[];
//************************************************
//函式   : 處理查詢單號的主函式
//迴傳值 : OL
//************************************************
DWORD WINAPI DirThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32];
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);

	ResultCode = SendDirMsg( id,password );

	switch(ResultCode)
	{
		case -200: 
			StockChatBufferLine("無任何問題單紀錄!!",FONT_PAL_RED);
			StockChatBufferLine("請新增問題單!",FONT_PAL_RED);
			ProNoValue = 0;
			break;
		case -400:
			StockChatBufferLine("網路發生錯誤!!",FONT_PAL_RED);
			StockChatBufferLine("無法查詢問題單!",FONT_PAL_RED);
			break;
		case -600:
			StockChatBufferLine("綫上迴報服務器無法連結!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case -800:
			StockChatBufferLine("網路連綫逾時!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case 1:    // 查詢成功
			break;
		case -999:
			StockChatBufferLine("網路忙綫中!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_RED);
			break;
		default:
			StockChatBufferLine("抱歉程式內部錯誤!!!",FONT_PAL_RED);
			StockChatBufferLine("問題單查詢失敗!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //寫入onlinegm.log
	if( ResultCode != 1 ){
		sprintf_s(inlogstr,"查詢失敗錯誤碼%d",ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif
	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

//************************************************
//函式   : 處理刪除單號的主函式
//迴傳值 : OL
//************************************************
DWORD WINAPI DeleteThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32] ;
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);
#ifdef _STONDEBUG_
	inlogstr[0] = 0;
#endif

	ResultCode = SendDeleteMsg(id,password,Prodata[ProNoSelect].no);

	switch(ResultCode)
	{
		case 4:
			StockChatBufferLine("網路發生錯誤!!",FONT_PAL_RED);
			StockChatBufferLine("無法刪除本則單號!",FONT_PAL_RED);
			break;
		case 6:
			StockChatBufferLine("綫上迴報服務器無法連結!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case 8:
			StockChatBufferLine("網路連綫逾時!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case 1: 
			StockChatBufferLine("問題單號已刪除瞭!",FONT_PAL_YELLOW);
			Prodata[ProNoSelect].delflag = TRUE ;
			TotalAddValue --;
			break;
		case -999:
			StockChatBufferLine("網路忙綫中!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_RED);
			break;
		default:
			StockChatBufferLine("抱歉程式內部錯誤!!!",FONT_PAL_RED);
			StockChatBufferLine("本則單號刪除失敗!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //寫入onlinegm.log
	if(	ResultCode != 1){	
		sprintf_s(inlogstr,"刪除失敗錯誤碼%d",ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif

	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

//************************************************
//函式   : 處理Multithread的主函式
//迴傳值 : OL
//************************************************
DWORD WINAPI OnlineGmThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32] ,buf[50];
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);
#ifdef _STONDEBUG_
	inlogstr[0] = 0;
#endif
	
	ResultCode = SendProblemMsg(id,password,DataBuffer,InputBuffer);

	switch(ResultCode)
	{
		case 4:
			StockChatBufferLine("網路發生錯誤!!",FONT_PAL_RED);
			StockChatBufferLine("無法發送本則問題!",FONT_PAL_RED);
			break;
		case 6:
			StockChatBufferLine("綫上迴報服務器無法連結!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case 8:
			StockChatBufferLine("網路連綫逾時!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
			break;
		case -9:
			if(SendType==0){
				StockChatBufferLine("每次發送一般問題單",FONT_PAL_RED);
				StockChatBufferLine("請間隔三十分鍾謝謝...",FONT_PAL_RED);
			}else{
				StockChatBufferLine("每次發送異常問題單",FONT_PAL_RED);
				StockChatBufferLine("請間隔一小時謝謝...",FONT_PAL_RED);
			}
			break;
		case -999:
			StockChatBufferLine("網路忙綫中!!",FONT_PAL_RED);
			StockChatBufferLine("請您稍後再試...",FONT_PAL_RED);
			break;
		case 1:
			sprintf_s(buf,"問題單號%d已送齣!",iReturnNo);
			StockChatBufferLine( buf ,FONT_PAL_YELLOW);
			TotalAddValue ++;
			ResetFlag = TRUE ; // 隻有成功纔reset
			DirFlag = TRUE ;
			break;
		default:
			StockChatBufferLine("抱歉程式內部錯誤!!!",FONT_PAL_RED);
			StockChatBufferLine("本則單號傳送失敗!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //寫入onlinegm.log
	if( ResultCode != 1 ){
		sprintf_s(inlogstr,"問題單類型:%d 建單失敗錯誤碼:%d",SendType,ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif
	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

extern int nServerGroup;
extern short selectServerIndex;
extern short onlinegmProcNo;
extern int sCharSide ;
//**************************************************
//主函式:
//迴傳值:0 錶示視窗開啓中 1 錶示完成
//**************************************************
int iOnlineGmProc()
{
	int i , id ; 
	static DWORD dwPressTime;
	static int btnId[50] , btnState[50] , HelpId[10] , HelpidState[10] ;
	static int SureId[2];
	char buf[100]= "/0" ; // test
	static ACTION *pActOnlineGmWnd = NULL;
	static ACTION *pActSureWnd = NULL;
	static struct tm nowTime;
	time_t longTime;
	DWORD  PushdirTime;
	static LPPAGE page;
	static LPDESC desc;
	static int desc_index,page_index;
	int x, y;
	if (onlinegmProcNo == 0)
	{
		// 打開一個視窗	
		if (pActOnlineGmWnd == NULL )
		{
			x = (lpDraw->xSize - 600) / 2;
			y = (lpDraw->ySize - 450) / 2;

			pActOnlineGmWnd = MakeWindowDisp(x,y,600,450,NULL,-1, FALSE);

			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;

			if(ResetFlag==TRUE){
				InitOnlineGmInput(x, y);
				InitOnlineGm(); 
				dwPressTime = 0;
				for ( i = 0 ; i < sizeof(btnId)/sizeof(int) ; i++ )
				{	
					btnId[i] = 0;
					btnState[i] = 0;
				}
				for ( i = 0 ; i < sizeof(HelpId)/sizeof(int) ; i++ )
				{
					HelpId[i] = 0;
					HelpidState[i] = 0;
				}
				time( &longTime );
				localtime_s(&nowTime, &longTime );
				wrongY = okY = nowTime.tm_year+1900 ;
				/*//fix
				wrongM = okM = nowTime.tm_mon+1 ;
				wrongD = okD = nowTime.tm_mday ;
				wrongH = okH = nowTime.tm_hour ;
				*/
				//畫麵reset
				ProNoIndex = 0;
				desc_index = 0;
				page_index = 0; 
				PushKey = 3;  // 自動查詢
			}

		}
		else	
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;

			if (DeleteBtnFlag==FALSE)
			{
				id = selGraId( btnId, sizeof( btnId )/sizeof( int ) );
				if(dwPressTime)
				{
					if( TimeGetTime()>(dwPressTime+100))
					{
						for( i = 0 ; i < DEF_BUTTON_TOTAL ; i ++ )
						{
							if(btnState[i])
							{
								btnState[i] = 0;
								switch (i)
								{
								case 0://查詢
									PushdirTime = TimeGetTime();
									if ( DirFlag==TRUE || (PushdirTime-LastTime)>5000 ){   //(關閉)有查詢過就不能在查
										LastTime = TimeGetTime();
										PushKey = 3;
										DirFlag = FALSE;
									}
									break;
								case 1://刪除
									if (ProNoSelectFlag){	//要有選到某單號纔能刪除
										DeleteBtnFlag = TRUE ;										
									}
									break;						
								case 2://傳送
									DeathAction( pActOnlineGmWnd );
									pActOnlineGmWnd = NULL;
									onlinegmProcNo = 2;
									return 0;								
								case 3://清除
									InitOnlineGmInput(x, y);	break;
								case 4://注意事項
									DeathAction( pActOnlineGmWnd );
									pActOnlineGmWnd = NULL;
									onlinegmProcNo = 1;
									return 0;
								case 5://關閉
									ResetFlag = TRUE;
									DeathAction( pActOnlineGmWnd);
									pActOnlineGmWnd = NULL;
									return 1 ;
								case 6://訊息框上捲
									if(ProNoValue){
										PushKey = 1;
									}
									break;
								case 7://訊息框下捲
									if(ProNoValue){
										PushKey = 2;
									}
									break;
								case 8:PutKey = 1;  break;//輸入框上捲
								case 9:PutKey = 2;  break;//輸入框下捲
								case 10://正常年月上捲
									okM--;
									if (okM<=0){  //fix
										okY--;
										okM=12;
									}
									break;
								case 11://正常年月下捲
									okM++;
									if (okM>12){
										okY++;
										okM=1;
									}
									break;
								case 12://正常日上捲
									okD--;
									if (okD<=0) okD = 31 ;   //fix
									break;
								case 13://正常日下捲
									okD++;
									if (okD>31) okD = 1;
									break;
								case 14://正常時上捲
									okH--;
									if (okH<0)	okH = 23;
									break;
								case 15://正常時下捲
									okH++;
									if (okH>23) okH=0;
									break;
								case 16://錯誤年月上捲
									wrongM--;
									if (wrongM<=0){ //fix
										wrongY--;
										wrongM=12;
									}
									break;
								case 17://錯誤年月下捲
									wrongM++;
									if (wrongM>12){
										wrongY++;
										wrongM=1;
									}
									break;
								case 18://錯誤日上捲
									wrongD--;
									if (wrongD<=0) wrongD = 31;  //fix
									break;								
								case 19://錯誤日下捲
									wrongD++;
									if (wrongD > 31) wrongD = 1;
									break;
								case 20://錯誤時上捲
									wrongH--;
									if (wrongH<0) wrongH = 23;
									break;
								case 21://錯誤時下捲
									wrongH++;
									if (wrongH>23) wrongH = 0;
									break;
								case 22://類彆一上捲
									ClassIndex -- ;
									ClassIndex1 = 0 ;
									ClassIndex2 = 0 ;
									if (ClassIndex<0) ClassIndex = DEF_CLASS_TOTAL-1;
									break;
								case 23://類彆一下捲
									ClassIndex ++ ;
									ClassIndex1 = 0 ;
									ClassIndex2 = 0 ;
									if (ClassIndex==DEF_CLASS_TOTAL) ClassIndex = 0;
									break;							
								case 24://類彆二上捲
									ClassIndex1 -- ;
									ClassIndex2 = 0 ;
									if (ClassIndex==1){   // 一般問題
										if (ClassIndex1<0) ClassIndex1 = DEF_C1_TOTAL-1;
									}else{
										if (ClassIndex1<0) ClassIndex1 = DEF_C2_TOTAL-1;
									}
									break;
								case 25://類彆二下捲
									ClassIndex1 ++ ;
									ClassIndex2 = 0 ;
									if (ClassIndex==1){		// 一般問題
										if (ClassIndex1==DEF_C1_TOTAL) ClassIndex1=0;
									}else{
										if (ClassIndex1==DEF_C2_TOTAL) ClassIndex1=0;
									}
									break;
								case 26://類彆三上捲
									ClassIndex2 -- ;
									switch (ClassIndex1)
									{
									case 0:if (ClassIndex2<0) ClassIndex2=2;break;
									case 1:if (ClassIndex2<0) ClassIndex2=2;break;
									case 2:if (ClassIndex2<0) ClassIndex2=4;break;
									case 3:if (ClassIndex2<0) ClassIndex2=1;break;
									case 4:if (ClassIndex2<0) ClassIndex2=1;break;
									case 5:if (ClassIndex2<0) ClassIndex2=2;break;
									case 10:if (ClassIndex2<0) ClassIndex2=2;break;
									default: ClassIndex2=0;break;
									}
									break;
								case 27://類彆三下捲
									ClassIndex2 ++ ;
									switch (ClassIndex1)
									{
									case 0:if (ClassIndex2>2) ClassIndex2=0;break;
									case 1:if (ClassIndex2>2) ClassIndex2=0;break;
									case 2:if (ClassIndex2>4) ClassIndex2=0;break;
									case 3:if (ClassIndex2>1) ClassIndex2=0;break;
									case 4:if (ClassIndex2>1) ClassIndex2=0;break;
									case 5:if (ClassIndex2>2) ClassIndex2=0;break;
									case 10:if (ClassIndex2>2) ClassIndex2=0;break;
									default: ClassIndex2=0;break;
									}
									break;
								}
							}
						}
						dwPressTime = 0;
					}
				}
				else
				{
					if ( 0 <= id && id < DEF_BUTTON_TOTAL )
					{
						btnState[id] = 1;
						dwPressTime = TimeGetTime(); 
					}
				}
			}else{ 
				if (pActSureWnd == NULL){
					pActSureWnd = MakeWindowDisp( 200+100+20 , 100-63 , 4-1 , 6-4 , NULL , -1);				
				}
				else if(pActSureWnd->hp > 0)
				{
					StockDispBuffer(416+15+15,100,DISP_PRIO_MENU,ONLINEGM_YES_OR_NO,1);
					MakeHitBox( 338+15+15,100,405+15+15,124, DISP_PRIO_BOX2 );
					MakeHitBox( 426+15+15,100,494+15+15,124, DISP_PRIO_BOX2 );
					selGraId( SureId, sizeof( SureId )/sizeof( int ) );
					SureId[0] = StockDispBuffer(  372+15+15 , 112 , DISP_PRIO_IME3, ONLINEGM_SURE_U , 1);
					SureId[1] = StockDispBuffer(  460+15+15 , 112 , DISP_PRIO_IME3, ONLINEGM_CHANCEL , 1);
					if(Prodata[ProNoSelect].delflag == TRUE){
						sprintf_s(buf,"此筆單號已刪除");
						StockFontBuffer( 365+15+15 , 81 , FONT_PRIO_FRONT, 2 , buf , 0 );
					}else{
						sprintf_s(buf,"刪除單號 %s 嗎?",Prodata[ProNoSelect].no);
						StockFontBuffer( 355+15+15 , 81 , FONT_PRIO_FRONT, 5 , buf , 0 );
					}

					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureId[0]){ //確定
						if(Prodata[ProNoSelect].delflag == FALSE){
							DWORD dwThreadID,dwThrdParam = 1;
							GMHandle = CreateThread(NULL, 0, DeleteThread,&dwThrdParam,0,&dwThreadID);
							if(GMHandle == NULL)
							{
								StockChatBufferLine("您的作業係統資源已不足!!",FONT_PAL_RED);
								StockChatBufferLine("本則單號刪除失敗!",FONT_PAL_RED);
								ResetFlag = TRUE;
								DeathAction( pActOnlineGmWnd);
								pActOnlineGmWnd = NULL;
								return 1;
							}				
						}
						DeathAction( pActSureWnd);
						pActSureWnd = NULL;			
						DeleteBtnFlag = FALSE ;
					}
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureId[1]){ //取消
						DeathAction( pActSureWnd);
						pActSureWnd = NULL;			
						DeleteBtnFlag = FALSE ;
					}
				}
			}
			if (pActOnlineGmWnd->hp > 0)
			{
				x = pActOnlineGmWnd->x;
				y = pActOnlineGmWnd->y;
				if(PushKey != 3){
					ShowProblemNo(x, y, PushKey);
				}else{ //處理查詢功能
					for( i=0;i<DEF_MAX_ADD_VALUE;i++){
						Prodata[i].no[0] = '\0';
						Prodata[i].state[0] = '\0';
						Prodata[i].okdate[0] = '\0';	
						Prodata[i].okH = 0;
						Prodata[i].wrongdate[0] = '\0';
						Prodata[i].wrongH = 0;	
						Prodata[i].class0 = 0;	
						Prodata[i].class1[0] = '\0';
						Prodata[i].cont[0] = '\0';
						Prodata[i].answer[0] = '\0';	
						Prodata[i].error[0] = '\0';
						Prodata[i].delflag = FALSE;		
					}
					DWORD dwThreadID,dwThrdParam = 1;
					GMHandle = CreateThread(NULL, 0, DirThread,&dwThrdParam,0,&dwThreadID);
					if(GMHandle == NULL)
					{
						StockChatBufferLine("您的作業係統資源已不足!!",FONT_PAL_RED);
						StockChatBufferLine("問題單號查詢失敗!",FONT_PAL_RED);
						ResetFlag = TRUE;
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						return 1;
					}
					
				}
				PushKey = 0;


				InputOnlineGmData(x, y, PutKey);	
				PutKey = 0;
				/*  for test
				sprintf_s(buf,"new%d",InputHistory.newNo);
				StockFontBuffer( 212 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"now%d",InputHistory.nowNo);
				StockFontBuffer( 350 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"add%d",InputHistory.addNo);
				StockFontBuffer( 480 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				*/
				//sprintf_s(buf,"Total  %d",TotalAddValue);
				//StockFontBuffer( 480 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				/*
				sprintf_s(buf,"ProNoValue   %d",ProNoValue);
				StockFontBuffer( 490 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"ProNoSelect  %d",ProNoSelect);
				StockFontBuffer( 350 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				*/
				StockDispBuffer( x + 320 , y + 228 , DISP_PRIO_MENU , ONLINEGM_BACKGROUND , 1);//背景圖
				StockFontBuffer( x + 80, y + 180, FONT_PRIO_FRONT, 0,"    年  月       日       時",0);
				StockFontBuffer( x + 387+21, y + 180, FONT_PRIO_FRONT, 0,"    年  月      日       時",0);
				StockFontBuffer( x + 12 , y + 180, FONT_PRIO_FRONT, 5, "正常日期", 0 );
				StockFontBuffer( x + 315+21 ,y + 180, FONT_PRIO_FRONT, 5, "錯誤日期", 0 );
				StockFontBuffer( x + 12 , y + 215, FONT_PRIO_FRONT, 5, "問題類彆", 0 );
				//顯示時間
				sprintf_s( buf ,"%d  %02d       %02d       %02d",okY,okM,okD,okH );
				StockFontBuffer( x + 100-20 , y + 180, FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s( buf ,"%d  %02d      %02d       %02d",wrongY,wrongM,wrongD,wrongH );
				StockFontBuffer( x + 387+21 , y + 180, FONT_PRIO_FRONT, 1 , buf , 0 );
				//顯示問題類彆
				StockFontBuffer( x + 90 , y + 215, FONT_PRIO_FRONT, 1, ProblemClass[ClassIndex], 0 );
				if (ClassIndex==1) //一般問題 
				{
					StockFontBuffer( x + 230-30, y + 215, FONT_PRIO_FRONT, 1, ProblemC1[ClassIndex1], 0 );
					StockFontBuffer(  x + 20, y + 250, FONT_PRIO_FRONT, 1, ProblemC1Help[ClassIndex1], 0 );
				}else{	//異常問題
					StockFontBuffer( x + 230, y + 215, FONT_PRIO_FRONT, 1, ProblemC2[ClassIndex1], 0 );
					switch (ClassIndex1)
					{
					case 0:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_1[ClassIndex2], 0 );break;
					case 1:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_2[ClassIndex2], 0 );break;
					case 2:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_3[ClassIndex2], 0 );break;
					case 3:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_4[ClassIndex2], 0 );break;
					case 4:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_5[ClassIndex2], 0 );break;
					case 5:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_6[ClassIndex2], 0 );break;
					case 10:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_7[ClassIndex2], 0 );break;
					default: break;
					}	
					if ((ClassIndex1==2&&ClassIndex2==0)||ClassIndex1==6)
						StockFontBuffer( x + 20,y + 250, FONT_PRIO_FRONT,1,"選擇此項目需注明【寵物等級】",0);
				}
				//如果user有按下按鈕 按鈕顯示按下
				for ( i = 0 ; i < DEF_BUTTON_TOTAL ; i ++ )
				{
					if (btnState[i]) 
						btnId[i] = StockDispBuffer(  x + BUTTON_XY[i][0], y + BUTTON_XY[i][1]  , DISP_PRIO_IME3, DOWN_ANIM_ID[i] , 2);
					else
						btnId[i] = StockDispBuffer(  x + BUTTON_XY[i][0], y + BUTTON_XY[i][1]  , DISP_PRIO_IME3, UP_ANIM_ID[i] , 2);
				}
			}
		}
	}
	else if (onlinegmProcNo == 1) // 注意事項
	{
		if (pActOnlineGmWnd==NULL){
			x = (lpDraw->xSize - 7*64)/2;
			y = (lpDraw->ySize - 8*48)/2;

			pActOnlineGmWnd = MakeWindowDisp( x , y , 4+3 , 6+2 ,NULL,0, FALSE);//( 210 , 120, 10 , 10 , NULL , 0 );
			pNowStrBuffer = NULL ;
		}
		else if (pActOnlineGmWnd->hp > 0)
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;
			page = &ProHelp_page[page_index];
			desc = Prohelp_Index[page_index]+page->desc_index;
			desc_index = page->desc_index;

			id = selGraId( HelpId, sizeof( HelpId )/sizeof( int ) );
			if (HelpidState[0]>=0)
				HelpId[0] = StockDispBuffer( x+207+32-160, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_PREPAGE+btnState[1], 2);
			else
				StockDispBuffer( x+207+32-160, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_PREPAGE+btnState[1], 1);

			if (HelpidState[1]>=0)
				HelpId[1] = StockDispBuffer( x+277+32-100, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_NEXTPAGE+btnState[2], 2);
			else
				StockDispBuffer( x+277+32-100, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_NEXTPAGE+btnState[2], 1);			

			HelpId[2] = StockDispBuffer( x+347+32-40, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_EXIT+btnState[3], 2);

			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[0]){  //上一頁
				if (page_index){
					page_index--;
					page = &ProHelp_page[page_index];			//指嚮上一頁
					desc_index = page->desc_index;
					desc = Prohelp_Index[page_index]+desc_index;//指嚮新一頁的desc開頭
				}
			}			
			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[1]){	//下一頁
				if (page_index < 4-1)
				{
					page_index++;
					page = &ProHelp_page[page_index];			//指嚮下一頁
					desc_index = page->desc_index;
					desc = Prohelp_Index[page_index]+desc_index;//指嚮新一頁的desc開頭
				}
			}
			HelpidState[0] = page_index==0 ? -2 : 0 ;
			HelpidState[1] = page_index==4-1 ? -2 : 0 ;

			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[2])
			{
				DeathAction( pActOnlineGmWnd);
				pActOnlineGmWnd = NULL;
				onlinegmProcNo = 0 ;
				ResetFlag = FALSE;
				return 0 ;
			}			
			for( i = 0; i < page->desc_num; i++){
				StockFontBuffer( x+30+5 , y+i*25+10, FONT_PRIO_FRONT, desc->color, desc->description, 0);			
				desc++;
			}
		}
	}
	else if (onlinegmProcNo == 2) //cyg 準備傳送的確定視窗
	{
		if (pActOnlineGmWnd==NULL){
			x = (lpDraw->xSize - 5*64)/2;
			y = (lpDraw->ySize - 5*48)/2;

			pActOnlineGmWnd =  MakeWindowDisp( x , y , 5 , 5 ,NULL,0, FALSE);
			pNowStrBuffer = NULL ;
		}
		else if (pActOnlineGmWnd->hp > 0)
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;
			MakeHitBox( x + 36,y + 238-85-35,x + 40,y  + 238-85+35, DISP_PRIO_BOX );
			MakeHitBox( x + 156+18,y + 238-85-35,x  + 156+18,y  + 238-85+35, DISP_PRIO_BOX );
			id = selGraId( btnId, sizeof( btnId )/sizeof( int ) );
			int SureBtn[2];
			SureBtn[0] = StockDispBuffer(  x + 70 , y + 250-85+35 , DISP_PRIO_IME3, ONLINEGM_SURE_U , 1);
			SureBtn[1] = StockDispBuffer(  x + 190+18 , y + 250-85+35 , DISP_PRIO_IME3, ONLINEGM_CHANCEL , 1);
			sprintf_s( buf ,"錯誤訊息->");			
			StockFontBuffer( x + 20 , y+ 20+60 , FONT_PRIO_FRONT, 4 , buf , 0 );

			if( TotalAddValue >= DEF_MAX_ADD_VALUE ){  // 有沒有達最大建單數
				sprintf_s( buf ,"您的問題單已達上限20筆!!");
				StockFontBuffer( x + 235 , y + 150 , FONT_PRIO_FRONT, 4 , buf , 0 );
				sprintf_s( buf ,"請刪除問題單後再留單謝謝",TotalAddValue );
				StockFontBuffer( x + 235 , y + 185 , FONT_PRIO_FRONT, 4 , buf , 0 );
				if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
				{
					DeathAction( pActOnlineGmWnd);
					pActOnlineGmWnd = NULL;
					onlinegmProcNo = 0 ;
					ResetFlag = FALSE;
					return 0 ;
				}
			}else{
				if (ClassIndex==1){
					sprintf_s( buf ,"問題類彆-> %s",ProblemClass[ClassIndex]);
					StockFontBuffer( x + 20 , y + 20+10, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"問題種類-> %s",ProblemC1[ClassIndex1]);
					StockFontBuffer( x + 20 , y + 20+35, FONT_PRIO_FRONT, 1 , buf , 0 );
				}else{
					sprintf_s( buf ,"問題類彆-> %s",ProblemClass[ClassIndex]);
					StockFontBuffer( x + 20 , y + 20+10, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"問題種類-> %s",ProblemC2[ClassIndex1]);	
					StockFontBuffer( x + 20 , y + 20+35, FONT_PRIO_FRONT, 1 , buf , 0 );
					switch (ClassIndex1)
					{
					case 0: sprintf_s( buf,"種類細項-> %s",ProblemC2_1[ClassIndex2] );break;
					case 1: sprintf_s( buf,"種類細項-> %s",ProblemC2_2[ClassIndex2] );break;
					case 2: sprintf_s( buf,"種類細項-> %s",ProblemC2_3[ClassIndex2] );break;
					case 3: sprintf_s( buf,"種類細項-> %s",ProblemC2_4[ClassIndex2] );break;
					case 4: sprintf_s( buf,"種類細項-> %s",ProblemC2_5[ClassIndex2] );break;
					case 5: sprintf_s( buf,"種類細項-> %s",ProblemC2_6[ClassIndex2] );break;
					case 10: sprintf_s( buf,"種類細項-> %s",ProblemC2_7[ClassIndex2] );break;
					default: buf[0] = '\0'; 
					}
					StockFontBuffer( x + 220-25 , y + 120+60, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"正常日期-> %4d年%02d月%02d日%02d時",okY,okM,okD,okH);
					StockFontBuffer( x + 220-25 , y + 120+85, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"錯誤日期-> %4d年%02d月%02d日%02d時",wrongY,wrongM,wrongD,wrongH );
					StockFontBuffer( x + 220-25 , y + 120+110, FONT_PRIO_FRONT, 1 , buf , 0 );				
				}
			
				if( lstrlen(InputHistory.str[InputHistory.lockNo+1]) == 0 && lstrlen(SubBuffer.buffer) == 0 ){
					sprintf_s( buf ,"請輸入問題內容");
					StockFontBuffer( x + 20 , y + 120, FONT_PRIO_FRONT, 4 , buf , 0 );
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						onlinegmProcNo = 0 ;
						ResetFlag = FALSE;
						return 0 ;
					}
				}else if(ClassIndex==0&&(!okY||!okM||!okD||!wrongY||!wrongM||!wrongD)){ //fix
					sprintf_s( buf ,"請填寫[正常日期]與[錯誤日期]");
					StockFontBuffer( x + 280-10+2 , y + 260 , FONT_PRIO_FRONT, 4 , buf , 0 );
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						onlinegmProcNo = 0 ;
						ResetFlag = FALSE;
						return 0 ;
					}
				}else{
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						ResetFlag = FALSE;
						ContentBuf[0] = '\0';
						for ( i=0;i<InputHistory.addNo-1;i++)
							strcat_s(ContentBuf,InputHistory.str[InputHistory.newNo-(InputHistory.addNo-1)+i]); //組閤每一行
						strcat_s(ContentBuf,SubBuffer.buffer);
						sprintf_s( InputBuffer,"%s",ContentBuf);

						if (ClassIndex==1){  // 一般問題   沒有日期和時間
							ProblemType=0;
							sprintf_s( DataBuffer,"&star=%s&earth=%s&qtype1=%s&msource=19",gmgroup[nServerGroup].name,gmsv[selectServerIndex].name,ProblemC1[ClassIndex1]);					
						}else{	// 異常問題
							ProblemType=1;
							char tempbuf[60]; 
							sprintf_s( tempbuf,"%s",ProblemC2[ClassIndex1]);
							switch (ClassIndex1)
							{
							case 0: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_1[ClassIndex2] );break;
							case 1: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_2[ClassIndex2] );break;
							case 2: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_3[ClassIndex2] );break;
							case 3: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_4[ClassIndex2] );break;
							case 4: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_5[ClassIndex2] );break;
							case 5: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_6[ClassIndex2] );break;
							case 10: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_7[ClassIndex2] );break;
							default: break;
							}
#ifdef _CHAR_PROFESSION
							if(lstrlen(pc.profession_class_name) == NULL){
								strcpy(pc.profession_class_name,"無");
							}
#endif
							char side[10];
							if(sCharSide == 1)
								strcpy(side,"左");
							else
								strcpy(side,"右");
#ifdef _CHAR_PROFESSION
							sprintf_s( DataBuffer,"&SY=%d&SM=%d&SD=%d&EY=%d&EM=%d&ED=%d&datarighttime=%d&datawrongtime=%d&msource=18&exceptcont=%s&G1grade1=%d&G1grade2=%d&G1Loc1=%s&G1Job1=%s&star=%s&G1gname1=%s",okY,okM,okD,wrongY,wrongM,wrongD,okH,wrongH,tempbuf,pc.transmigration,pc.level,side,pc.profession_class_name,gmgroup[nServerGroup].name,pc.name);
#else
							sprintf_s( DataBuffer,"&SY=%d&SM=%d&SD=%d&EY=%d&EM=%d&ED=%d&datarighttime=%d&datawrongtime=%d&msource=18&exceptcont=%s&G1grade1=%d&G1grade2=%d&G1Loc1=%s&G1Job1=%s&G1gname1=%s",okY,okM,okD,wrongY,wrongM,wrongD,okH,wrongH,tempbuf,pc.transmigration,pc.level,side,gmgroup[nServerGroup].name,pc.name);
#endif
						}
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						DWORD dwThreadID,dwThrdParam = 1;
						GMHandle = CreateThread(NULL, 0, OnlineGmThread,&dwThrdParam,0,&dwThreadID);
						if(GMHandle == NULL)
						{
							StockChatBufferLine("您的作業係統資源已不足!!",FONT_PAL_RED);
							StockChatBufferLine("本則單號傳送失敗!",FONT_PAL_RED);
							ResetFlag = TRUE;
							DeathAction( pActOnlineGmWnd);
							pActOnlineGmWnd = NULL;
							return 1;
						}				
						onlinegmProcNo = 0 ;
						return 0 ;
					}	
				}
			}
			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[1])  //取消鈕
			{
				DeathAction( pActOnlineGmWnd);
				pActOnlineGmWnd = NULL;
				onlinegmProcNo = 0 ;
				ResetFlag = FALSE;
				return 0 ;
			}
		}
	}
	if(CheckMenuFlag()){
		ResetFlag = TRUE;
		DeathAction( pActOnlineGmWnd);
		pActOnlineGmWnd = NULL;
		return 1;
	}
	return 0 ;
}
//************************************************
//函式   : DNS專用函式
//迴傳值 : TRUE  --- 轉換成功
//         FALSE --- 轉換失敗
//************************************************
BOOL QueryOnlineGmIP(char HostName[])
{
	PHOSTENT info;

//	strcpy(OnlineGmIP,"10.0.1.60");    // 直接給ip,保留轉換code
//	return TRUE;

	if( (info = gethostbyname(HostName)) == NULL)
		return FALSE;
	else{
		OnlineGmIP = inet_ntoa(*(struct in_addr *)*info->h_addr_list);		
	}
	return TRUE;

}
#endif
