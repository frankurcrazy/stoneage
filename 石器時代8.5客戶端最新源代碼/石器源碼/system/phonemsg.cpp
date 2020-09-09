//==========================================================================
// 檔名 : PhoneMsg.cpp
// 功用 : 石器時代[簡訊]按鈕的功能實作(V3.0後新增的功能)
// 撰寫人   : 林 昌 磊  (Leiboy)
// 初版完成日期 : 2002年01月26日
// 第二版更新日期 : 2002年02月02日==>新增Multithread(函式五)
// 第三版更新日期 : 2002年02月20日==>將MFC改寫成Winsock方式!(本版為已完成版!)
// 第四版完成日期 : 2002年02月26日==>新增DNS(函式七)
// 綫上正式運作日期 : 2002年03月04日
// 補充說明 : 遊戲中成功地傳送一通簡訊每次將扣WGS點數五點!
//==========================================================================

//先做版本的控製
#include "../systeminc/version.h"
#ifdef __PHONEMESSAGE

#include <winsock2.h>
#include "time.h"
#include "../systeminc/system.h"
#include "../systeminc/loadrealbin.h"
#include "../systeminc/anim_tbl.h"
#include "../systeminc/login.h"
#include "../systeminc/menu.h"
#include "../systeminc/map.h"
#include "../systeminc/ime_sa.h"
#include "../systeminc/t_music.h"
#include "../systeminc/field.h"
#include "../systeminc/pc.h"
#include "../wgs/descrypt.h"
#include "../other/caryIme.h"

#define MSG_SURE_D	     26288 //確定(按下)(黃色的)
#define MSG_SURE_U	     26289 //確定(彈起)(黃色的)
#define MSG_CANCEL_U	 26284 //取消(未按下)
#define MSG_CANCEL_D	 26285 //取消(按下)
#define MSG_CLEAR_U      26298 //清除(彈起)
#define MSG_CLEAR_D      26299 //清除(按下)

//Messsage 的Log 專用區 Begin
#ifdef _STONDEBUG_
char    logstr[512];
#define logfilename     "message.log"
#endif
//Messsage 的Log 專用區 End

BOOL QueryMyIP(char HostName[]);
//石器簡訊Server IP : 210.64.97.17
char *MsgIP;
#define SMSDomainName   "sms.hwaei.com.tw"
//目前所采用的ASP filename
#define ASPname   "//sms//stoneage.asp"  //2002 Feb. 20後啓用!
int     myvalue;
char    seqno[14];        //Wayia_seqno
//************************************************
//函式一 : 處理主程式與ASP間溝通的專用函式
//迴傳值 : 0 --- 處理完畢 & 簡訊發送成功
//         1 --- 簡訊發送失敗
//         2 --- 手機號碼參數錯誤
//         3 --- 手機訊息參數錯誤(過長)
//         4 --- 網路端錯誤
//         5 --- WGS點數(或通數)已不足!!(小於五點)
//         6 --- 連綫逾時(或DNS失敗)
//         7 --- ASP迴傳錯誤
//************************************************
int SendPhoneMsg(char pid[16], char ppw[16], char pps[], char pms[])
{
	if(!QueryMyIP(SMSDomainName)) return 6;
	if((pps[0] =='\0') || (lstrlen(pps) != 10)) return 2;
	if((pps[0] != '0') || (pps[1] != '9'))      return 2;
	int dv,i=0;
	do
	{
		dv = isdigit(pps[i+2]);
		i++;
	}while( dv && (i<8));
	if(!dv)  return 2;
	//和Jason討論後,新訂的文字上限為66bytes!!  Feb. 5,2002
	//保留16bytes給玩傢名稱用!                 Feb.22,2002
	int x=0,mc=0;
	do
	{
		if(IsDBCSLeadByte(pms[x]))
			x+=2;
		else
			x++;
		mc++;
	}while(x < lstrlen(pms));
	if((mc<1) || (mc>50)) return 3;
	char extpms[120];
	if(lstrlen(pc.name)>16)
		return 3;
	else

#ifdef _FIX_URLENCODE   // WON ADD	北京修正簡訊無法加空格的問題
	{
		char OutTmp[768];
		char *pInTmp,*pOutTmp;
		char Hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
		//  do  encoding
		pInTmp=pms;
		pOutTmp=OutTmp;
//		ZeroMemory(OutTmp,sizeof(OutTmp));
		while  (*pInTmp)
		{
		//	if(isalnum(*pInTmp)&&(!IsDBCSLeadByte(*pInTmp)))
			if ( (*pInTmp> '0') && (*pInTmp < '9') 
				||	(*pInTmp> 'a') && (*pInTmp < 'z')
				||	(*pInTmp> 'A') && (*pInTmp < 'Z') 
				)
				*pOutTmp++  =  *pInTmp;
			else
			{
			//	if(isspace(*pInTmp))
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
		sprintf_s(extpms,"%s:%s",pc.name,OutTmp);
	}
#else
		sprintf_s(extpms,"%s:%s",pc.name,pms);
#endif

	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	DWORD           timeout;
	char  *result;
	int   len, cnt, ret;
	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=0;
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_addr.s_addr = inet_addr(MsgIP);
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				timeout = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					if( select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut)>0 && FD_ISSET( hSock, &wfds))
						break;
					DWORD curtime = TimeGetTime();
					if( (timeout+5000) < curtime )
					{
						closesocket(hSock);
						return 6;
					}
					Sleep(1);
				}
				cnt = 0;
				char  buf[1024];
				sprintf_s(buf,"GET //sms//stoneage.asp?ID=%s&PWD=%s&TEL=%s&MSG=%s",pid,ppw,pps,extpms);
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,MsgIP);
				len = lstrlen(buf);
				timeout = TimeGetTime();
				while(len)
				{
					DWORD stime = TimeGetTime();
					if( (timeout+3000) < stime )
					{
						closesocket(hSock);
						return 6;
					}
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if( !FD_ISSET( hSock, &wfds) )
					{
						Sleep(1);
						continue;
					}
					ret = send( hSock, &buf[cnt], len, 0);
					if( SOCKET_ERROR == ret)
					{
						closesocket(hSock);
						return 4;
					}
					cnt += ret;
					len -= ret;
					if(len<1) break;
				}
				Sleep(500);
				len = 1024;
				cnt = 0;
				timeout = TimeGetTime();
				while(1)
				{
					DWORD rtime = TimeGetTime();
					if( (timeout+3000) < rtime )
					{
						closesocket(hSock);
						return 6;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if( !FD_ISSET( hSock, &rfds) )
					{
						Sleep(1);
						continue;
					}
					ret = recv( hSock, &buf[cnt], len, 0);
					if( SOCKET_ERROR == ret)
					{
						closesocket(hSock);
						return 4;
					}
					if( 0 == ret)
						break;
					buf[cnt+ret] = 0;
					result = strstr( buf, "\r\n\r\n") + 4;
					if(result)  break;
					cnt += ret;
					len -= ret;
				}
			}
		}
		closesocket(hSock);
		if(result[0]=='\0')  return 4;
		if(result[0]=='1')
		{
#ifdef _STONDEBUG_
			lstrcpy(logstr,"失敗 ");
			lstrcat(logstr,pps);
			sprintf_s(logstr,"%s %s",logstr,extpms);
#endif
			return 1;
		}
		else
		{
			result++;
			if(lstrlen(result) < 14)
				return 7;
			int j=0;
			i=0;
			do
			{
				seqno[i] = result[i];
				if(result[i] == '0') j++;
				i++;
			}while(i<14);
			seqno[14] = 0;
			if(j == 14) return 5;
#ifdef _STONDEBUG_
			lstrcpy(logstr,"成功-");
			lstrcat(logstr,seqno);
			lstrcat(logstr," ");
			lstrcat(logstr,pps);
			sprintf_s(logstr,"%s %s",logstr,extpms);
#endif
		}
		return 0;
	}
	else
		return 4;
}

//************************************************
//函式二 : 産生Log檔(於Local端目錄下)的專用函式
//迴傳值 : None
//附  注 : 隻有Debug mode纔在硬碟寫入log檔!!
//************************************************
#ifdef _STONDEBUG_
void WriteLog( char cData[], char cFile[])
{
	char totals[1024];
	struct tm nowTime;
	time_t longTime;
	time( &longTime );
	localtime_s(&nowTime, &longTime );
	sprintf_s(totals,"%02d/%02d/%02d %02d:%02d:%02d ",(nowTime.tm_year % 100), nowTime.tm_mon+1, nowTime.tm_mday,
				nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	lstrcat(totals,cData);
	lstrcat(totals,"\r\n");
	FILE *fp;
	fp = fopen(logfilename, "a" );
	if(fp)
	{
		fprintf(fp,totals);
		fclose(fp);
	}
}
#endif

static int mx = 20, my = 10;
STR_BUFFER  pno,ptext;
static STR_BUFFER *MsgFocus[] ={ &pno, &ptext };
static int MsgFocusSw;
//************************************************
//函式三 : 資料輸入欄位的初始化函式
//迴傳值 : None
//************************************************
void InitMsgInput()
{
	pno.buffer[0]='\0';
	//ptext.buffer[0]='\0';
	pno.x = mx+125;
	pno.y = my+47;
	pno.len = 10;
	pno.color = FONT_PAL_RED;
	pno.fontPrio = FONT_PRIO_FRONT;
	pno.cnt = 0;
	pno.cursor = 0;

	ptext.x = mx+17;
	ptext.y = my+87;
	ptext.len = 100;
	ptext.color = FONT_PAL_AQUA;
	ptext.fontPrio = FONT_PRIO_FRONT;
	ptext.lineLen=34;
	ptext.lineDist=20;	
	int x = lstrlen(ptext.buffer);
	if(x)
		ptext.cursor = x;
	else
	{
		ptext.cnt=0;
		ptext.cursor=0;
	}
}

//************************************************
//函式四 : 處理資料輸入欄位的主函式
//迴傳值 : None
//************************************************
int InputMsgData()
{
	int id,x1,x2,y1,y2;
	StockFontBuffer2(&pno);
	StockFontBuffer2(&ptext);
	id = -1;
	x1 = mx + 115;
	y1 = my + 45;
	x2 = x1 + 108;
	y2 = y1 + 19;
	if( MakeHitBox( x1, y1, x2, y2, DISP_PRIO_BOX ) )
	{
		id = 0;
		MsgFocusSw = 0;
	}
	x1 = mx + 16;
	y1 = my + 80;
	x2 = x1 + 240;
	y2 = y1 + 70;
	if( MakeHitBox( x1, y1, x2, y2, DISP_PRIO_BOX ) )
	{
		id = 1;
		MsgFocusSw = 1;
	}
	x1 = mx + 39;
	y1 = my + 190;
	x2 = x1 + 67;
	y2 = y1 + 24;
	if( MakeHitBox( x1, y1, x2, y2, DISP_PRIO_BOX ) )
	{
		id = 2;
	}
	x1 = mx + 155;
	y1 = my + 190;
	x2 = x1 + 67;
	y2 = y1 + 24;
	if( MakeHitBox( x1, y1, x2, y2, DISP_PRIO_BOX ) )
	{
		id = 3;
	}
	x1 = mx + 167;
	y1 = my + 160;
	x2 = x1 + 84;
	y2 = y1 + 19;
	if( MakeHitBox( x1, y1, x2, y2, DISP_PRIO_BOX ) )
	{
		id = 4;
	}
	return id;
}

HANDLE MHandle;
extern short msgBtn;
extern char szUser[],szPassword[];
//************************************************
//函式五 : 處理Multithread的主函式
//迴傳值 : OL
//************************************************
DWORD WINAPI MsgThread(LPVOID param)
{
	msgBtn=1;
	myvalue = -1;	
	char id[32], password[32];
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);
	//GetKeyInputFocus(NULL);
#ifdef _STONDEBUG_
	logstr[0] = 0;
#endif
	myvalue = SendPhoneMsg(id,password,pno.buffer,ptext.buffer);
	//GetKeyInputFocus(&MyChatBuffer);
	switch(myvalue)
	{
				case 1:
					StockChatBufferLine("本則簡訊傳送失敗!",FONT_PAL_RED);
					StockChatBufferLine("請您重新操作!!",FONT_PAL_WHITE);
					break;
				case 2:
					StockChatBufferLine("手機號碼格式錯誤!!",FONT_PAL_RED);
					StockChatBufferLine("無法發送本則簡訊!",FONT_PAL_RED);
					break;
				case 3:
					StockChatBufferLine("手機訊息過長!!",FONT_PAL_RED);
					StockChatBufferLine("無法發送本則簡訊!",FONT_PAL_RED);
					break;
				case 4:
					StockChatBufferLine("網路發生錯誤!!",FONT_PAL_RED);
					StockChatBufferLine("無法發送本則簡訊!",FONT_PAL_RED);
					break;
				case 5:
					StockChatBufferLine("您的WGS點數(或通數)已不足!!",FONT_PAL_RED);
					StockChatBufferLine("無法發送本則簡訊!",FONT_PAL_RED);
					break;
				case 6:
					StockChatBufferLine("簡訊服務器無法連結!!",FONT_PAL_RED);
					StockChatBufferLine("請您稍後再試...",FONT_PAL_WHITE);
					break;
				case 7:
					StockChatBufferLine("簡訊服務器沒有正確地迴應!!",FONT_PAL_RED);
					StockChatBufferLine("無法確定本則簡訊是否成功?!",FONT_PAL_WHITE);
					break;
				case -1:
					StockChatBufferLine("程式內部錯誤!!!",FONT_PAL_RED);
					StockChatBufferLine("本則簡訊傳送失敗!",FONT_PAL_RED);
					break;
				default:
					StockChatBufferLine("簡訊已經送齣瞭!",FONT_PAL_YELLOW);
	}
#ifdef _STONDEBUG_
	if(logstr[0] != 0) WriteLog(logstr,logfilename);
#endif
	msgBtn=0;
	CloseHandle(MHandle);
	ExitThread(0);	
	return 0L;
}

int MsgID;
//************************************************
//函式六 : 手機簡訊功能的主要函式
//迴傳值 : 0 --- 視窗OPEN
//         1 --- 視窗CLOSE
//         2 --- 按下確定的結束
//************************************************
int MsgProc()
{
	int id , i , ret;
	static int btnId[3];
	static int btnState[2];
	static DWORD dwPressTime;
	static ACTION *pActMenuWin = NULL;
	char MsgHint[][30] = {"對方的手機號碼。","簡訊內容(最多50中/英字)。","送齣簡訊。","關閉簡訊視窗。","清空簡訊內容。"};

	if(MsgID == 0)
	{
		for( i = 0; i < sizeof(btnId)/sizeof(int); i++)
			btnId[i] = -2;
		for( i = 0; i < 3; i++)
			btnState[i] = -1;
		pActMenuWin = MakeWindowDisp(mx,my,275,225,CG_MSG_WND,-1);
		InitMsgInput();
		MsgFocusSw = 0;
		dwPressTime = 0;
		MsgID++;
	}
	if( pActMenuWin != NULL)
	{
		id = selGraId( btnId, sizeof(btnId)/sizeof(int));		
		if(dwPressTime)
		{
			if( TimeGetTime()>(dwPressTime+100))
			{
				dwPressTime = 0;
				if(btnState[2] == 1)
				{
					if(ptext.buffer[0]!='\0')
					{
						ptext.buffer[0]='\0';
						ptext.cnt=0;
						ptext.cursor=0;
					}
					if(id==-1) btnState[2] = -1;
				}
				else if(btnState[0] == 1)
				{   
					if((lstrlen(pno.buffer) > 0) && (lstrlen(ptext.buffer) > 0))
					{
						pno.buffer[pno.cnt]='\0';
						ptext.buffer[ptext.cnt]='\0';
						id=50;
					}
					else
					{
						if(id==-1)
							btnState[0] = -1;
					}
				}
			}
		}
		else
		{
			if( -1 < id && id < 3)
			{
				btnState[id] = 1;
				id = -1;
				dwPressTime = TimeGetTime();
				play_se( 217, 320, 240);  //按鈕聲
			}
		}

		if( pActMenuWin->hp > 0)
		{
			StockDispBuffer( ((WINDOW_DISP *)pActMenuWin->pYobi)->mx, ((WINDOW_DISP *)pActMenuWin->pYobi)->my, DISP_PRIO_MENU, CG_MSG_WND, 1);
			if(btnState[2] != 1)
				btnId[2] = StockDispBuffer( (mx+209), (my+170), DISP_PRIO_IME3, MSG_CLEAR_U , 1);
			else
				StockDispBuffer( (mx+209), (my+170), DISP_PRIO_IME3, MSG_CLEAR_D , 1);
			if(btnState[0] != 1)
				btnId[0] = StockDispBuffer( (mx+73), (my+202), DISP_PRIO_IME3, MSG_SURE_U , 1);
			else
				StockDispBuffer( (mx+73), (my+202), DISP_PRIO_IME3, MSG_SURE_D, 1);
			if(btnState[1] != 1)
			{
				btnId[1] = StockDispBuffer( (mx+189), (my+202), DISP_PRIO_IME3, MSG_CANCEL_U, 1);
				ret = InputMsgData();
				if(ret>=0)  ShowBottomLineString( FONT_PAL_WHITE, MsgHint[ret]);
				GetKeyInputFocus(MsgFocus[MsgFocusSw]);
			}
		}			

		if(CheckMenuFlag())
		{
			id = 99;
		}
		else //按Esc關閉
			if( (joy_trg[ 0 ] & JOY_ESC) && GetImeString() == NULL)
			{
				id = 100;
				play_se( 203, 320, 240);//視窗關閉聲
			}
			else //按下取消鈕
				if(btnState[1] == 1)
				{
					id = 100;
					play_se( 203, 320, 240);
				}
		//關閉簡訊視窗
		if( id >= 0)
		{
			DeathAction( pActMenuWin);
			pActMenuWin = NULL;
			if(id == 50)
			{
				DWORD dwThreadID,dwThrdParam = 1;
				MHandle = CreateThread(NULL, 0, MsgThread,&dwThrdParam,0,&dwThreadID);
				if(MHandle == NULL)
				{
					StockChatBufferLine("您的作業係統資源已不足!!",FONT_PAL_RED);
					StockChatBufferLine("本則簡訊發送失敗!",FONT_PAL_RED);
					return 1;
				}				
				return 2;
			}
			else
				return 1;
		}
	}
	return 0;
}

//************************************************
//函式七 : DNS專用函式
//迴傳值 : TRUE  --- 轉換成功
//         FALSE --- 轉換失敗
//************************************************
BOOL QueryMyIP(char HostName[])
{
	PHOSTENT info;
	if( (info = gethostbyname(HostName)) == NULL)
		return FALSE;
	else
		MsgIP = inet_ntoa(*(struct in_addr *)*info->h_addr_list);
	return TRUE;
}

#endif