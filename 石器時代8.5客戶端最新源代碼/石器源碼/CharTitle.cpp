#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/font.h"
#include "../systeminc/action.h"
#include "systeminc\sprdisp.h"
#include "systeminc\menu.h"
#include "systeminc\mouse.h"
#include "newproto\autil.h"
#include "newproto\protocol.h"
#ifdef _CHARTITLE_STR_
extern unsigned int sockfd;
typedef struct{
	BOOL 窗口顯示;
	BOOL 確定窗口顯示;
	int 當前頁數;
	int 確定圖檔索引;
	char 介紹[100][32];
	int 稱號索引[100];
	TITLE_STR title;//當前稱號
	TITLE_STR titledata[100];//稱號數據
	BOOL 關閉窗口;
}稱號數據結構;
extern int play_se(int tone, int x, int y);
稱號數據結構 稱號;

void 打開稱號窗口初始化()
{
	if(稱號.窗口顯示){
		稱號.窗口顯示=FALSE;
		稱號.確定窗口顯示=FALSE;
	}else{
		稱號.當前頁數=0;
		稱號.窗口顯示=TRUE;
		稱號.確定窗口顯示=FALSE;
	}
}

extern void PutTitleText(int x,int y,char fontPrio,TITLE_STR str,BOOL hitFlag);

BOOL 獲取稱號取消窗口()
{
	return 稱號.關閉窗口;
}

void 設置稱號取消窗口()
{
	if(稱號.關閉窗口) 稱號.關閉窗口=FALSE;
	else 稱號.關閉窗口=TRUE;
}

BOOL 獲取當前稱號是否存在()
{
	return 稱號.title.flg;
}

void 稱號展示()
{
	if(稱號.title.flg){
		PutTitleText(78-稱號.title.len/2,49,FONT_PRIO_FRONT,稱號.title,0);
	}
	int bnt;
	bnt = StockFontBuffer(18,49,1,FONT_PAL_GREEN,"                             ",2);
	if(mouse.onceState & MOUSE_LEFT_CRICK>0){
		if(HitFontNo == bnt){
			if(稱號.關閉窗口) 稱號.關閉窗口=FALSE;
			else 稱號.關閉窗口=TRUE;
			play_se(203, 320, 240);
		}
	}
}

BOOL 人物稱號處理(ACTION * pct)
{
	int x,y;
	x = pct->x;
	y = pct->y + 133;
	int 按鈕左=-1;
	int 按鈕右=-1;
	int 按鈕關閉=-1;
	int 按鈕ID;
	按鈕左 = StockDispBuffer( x -55, y + 7, DISP_PRIO_IME3, 55250, 2 );
	按鈕右 = StockDispBuffer( x -20, y + 7, DISP_PRIO_IME3, 55251, 2 );
	按鈕關閉 = StockDispBuffer( x+40, y + 7, DISP_PRIO_IME3, 55252, 2 );
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if(!稱號.確定窗口顯示){
			if(按鈕左 == HitDispNo){
				if(稱號.當前頁數){
					稱號.當前頁數--;
				}
			}
			if(按鈕右 == HitDispNo){
				if(稱號.當前頁數!=19 && 稱號.titledata[(稱號.當前頁數+1)*5].flg)
				{
					稱號.當前頁數++;
				}
			}
			if(按鈕關閉 == HitDispNo){
				DeathAction(pct);
				稱號.窗口顯示=FALSE;
				稱號.確定窗口顯示=FALSE;
				return TRUE;
			}
		}
	}

	int i=0;
	int 稱號圖檔索引;
	for(;i<5;i++){
		稱號圖檔索引 = 稱號.當前頁數*5+i;
		if(稱號.titledata[稱號圖檔索引].flg)
		{
			PutTitleText(380-稱號.titledata[稱號圖檔索引].len/2,43+i*0x20,FONT_PRIO_FRONT,稱號.titledata[稱號圖檔索引],0);
			char 稱號序號[128];
			sprintf_s(稱號序號,"%03d",稱號圖檔索引+1);
			StockFontBufferExt(0x130,0x2D+i*0x20,1,FONT_PAL_GREEN,稱號序號,0,19);
			if(!稱號.確定窗口顯示){
				if(MakeHitBox(0x124,0x26+i*0x20,0x1B8,0x44+i*0x20,0x6D)==1){
					StockFontBuffer(0x123,0xD1,2,0,稱號.介紹[稱號圖檔索引],0);
					if(mouse.onceState & MOUSE_LEFT_CRICK>0){
						稱號.確定圖檔索引=稱號.稱號索引[ 稱號圖檔索引];
						稱號.確定窗口顯示=TRUE;
					}
				}
			}
		}else break;
	}
	if(稱號.確定窗口顯示){
		StockFontBuffer(0x123,0xD1,2,0,稱號.介紹[稱號.確定圖檔索引],0);
		StockFontBuffer(0x130,0x118,2,0,"確定使用該稱號嗎？",0);
		StockDispBuffer(0x16D,0x130,0x6C,55253,1);//確定窗口底圖
		按鈕ID = StockDispBuffer(0x194,0x148,109,55252,2);//關閉
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(按鈕ID == HitDispNo){
				稱號.確定窗口顯示=FALSE;
				稱號.確定圖檔索引=0;
			}
		}
		按鈕ID = StockDispBuffer(0x148,0x148,109,55254,2);//確定
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(按鈕ID == HitDispNo){
				int checksum=0;
				char buf[1024*4];
				memset(buf,0,1024*4);
				checksum += util_mkint(buf, 稱號.確定圖檔索引);
				util_mkint(buf, checksum);
				util_SendMesg(sockfd, LSSPROTO_CHARTITLE_SEND, buf);
				稱號.確定窗口顯示=FALSE;
				稱號.確定圖檔索引=0;
			}
		}
	}
	return FALSE;
}
extern void getCharTitleSplit( char *str,TITLE_STR* title);
void 人物稱號數據更新(char *數據)
{
	char 基礎內容[126],圖檔內容[1024],圖檔索引[1024],內容介紹[4000],臨時[126];
	memset(基礎內容,0,126);
	memset(圖檔內容,0,1024);
	memset(圖檔索引,0,1024);
	memset(內容介紹,0,4000);
	getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",1,基礎內容,126);
	getStringFromIndexWithDelim_body((char *) 基礎內容,(char *)"|",1,臨時,126);
	int titleindex = atoi(臨時);
	extern char* FreeGetTitleStr(int id);
	if(titleindex>0) getCharTitleSplit(FreeGetTitleStr(titleindex),&稱號.title);
	else memset(&稱號.title,0,sizeof(TITLE_STR));
	getStringFromIndexWithDelim_body((char *) 基礎內容,(char *)"|",2,臨時,126);
	int 數量 = atoi(臨時);
	if(數量!=0){
		memset(&稱號.titledata,0,sizeof(稱號.titledata[0])*100);
		memset(&稱號.稱號索引,0,sizeof(int)*100);
		memset(&稱號.介紹,0,32*100);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",2,圖檔內容,1024);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",3,內容介紹,4000);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",4,圖檔索引,1024);
		int i=0;
		extern char* FreeGetTitleStr(int id);
		for(i;i<數量;i++){
			getStringFromIndexWithDelim_body((char *)圖檔內容,(char *)"|",i+1,臨時,126);
			titleindex = atoi(臨時);
			getCharTitleSplit(FreeGetTitleStr(titleindex),&稱號.titledata[i]);
			getStringFromIndexWithDelim_body((char *)圖檔索引,(char *)"|",i+1,臨時,126);
			稱號.稱號索引[i]=atoi(臨時);
			getStringFromIndexWithDelim_body((char *)內容介紹,(char *)"|",i+1,臨時,126);
			sprintf_s(稱號.介紹[i],32,"%s",臨時);
		}
	}
}

void 初始化稱號結構()
{
	memset(&稱號,0,sizeof(稱號數據結構));
}
#endif



#ifdef _CHARTITLE_
extern unsigned int sockfd;
typedef struct{
	int 稱號窗口結構;
	ACTION *稱號結構[5];
	ACTION * 當前稱號結構;
	int 當前稱號圖檔;
	BOOL 窗口顯示;
	int 圖檔[100];
	int 稱號索引[100];
	char 介紹[100][32];
	int 當前頁數;
	BOOL 確定窗口顯示;
	int 確定圖檔索引;
}稱號數據結構;

稱號數據結構 稱號;

void 結束稱號展示動畫()
{
	int i=0;
	for(i;i<5;i++){
		if(稱號.稱號結構[i]){
			if(稱號.稱號結構[i]) DeathAction(稱號.稱號結構[i]);
			稱號.稱號結構[i]=0;
		}					
	}
}

void 打開稱號窗口初始化()
{
	if(稱號.窗口顯示){
		結束稱號展示動畫();
		稱號.窗口顯示=FALSE;
		稱號.確定窗口顯示=FALSE;
	}else{
		稱號.當前頁數=0;
		稱號.窗口顯示=TRUE;
		稱號.確定窗口顯示=FALSE;
	}
}


void 稱號展示()
{

	if(稱號.當前稱號圖檔)
		if(!稱號.當前稱號結構){
			if(稱號.當前稱號圖檔 < 100000){
				稱號.當前稱號結構 = 0;
				StockDispBuffer(0x7F,0x40,109,稱號.當前稱號圖檔,0);
			}else{
				稱號.當前稱號結構 = MakeAnimDisp(0x7F,0x59,稱號.當前稱號圖檔,0);
			}
		}else if(*(int *)(稱號.當前稱號結構+0x140)!= 稱號.當前稱號圖檔){
			DeathAction(稱號.當前稱號結構);
			if(稱號.當前稱號圖檔 < 100000){
				稱號.當前稱號結構 = 0;
				StockDispBuffer(0x7F,0x40,109,稱號.當前稱號圖檔,0);
			}else{
				稱號.當前稱號結構 = MakeAnimDisp(0x7F,0x59,稱號.當前稱號圖檔,0);
			}
		}
}

BOOL 人物稱號處理(ACTION * pct)
{
	int x,y;
	x = pct->x;
	y = pct->y + 133;
	int 按鈕左=-1;
	int 按鈕右=-1;
	int 按鈕關閉=-1;
	int 按鈕ID;
	按鈕左 = StockDispBuffer( x -55, y + 7, DISP_PRIO_IME3, 55250, 2 );
	按鈕右 = StockDispBuffer( x -20, y + 7, DISP_PRIO_IME3, 55251, 2 );
	按鈕關閉 = StockDispBuffer( x+40, y + 7, DISP_PRIO_IME3, 55252, 2 );
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if(!稱號.確定窗口顯示){
			if(按鈕左 == HitDispNo){
				if(稱號.當前頁數){
					稱號.當前頁數--;
					結束稱號展示動畫();
				}
			}
			if(按鈕右 == HitDispNo){
				if(稱號.當前頁數!=19 && 稱號.圖檔[(稱號.當前頁數+1)*5]){
					稱號.當前頁數++;
					結束稱號展示動畫();
				}
			}
			if(按鈕關閉 == HitDispNo){
				DeathAction(pct);
				結束稱號展示動畫();
				稱號.窗口顯示=FALSE;
				稱號.確定窗口顯示=FALSE;
				return TRUE;
			}
		}
	}

	int i=0;
	int 稱號圖檔索引;
	for(;i<5;i++){
		稱號圖檔索引 = 稱號.當前頁數*5+i;
		if(稱號.圖檔[稱號圖檔索引]){
			if(!稱號.稱號結構[i]){
				if(稱號.圖檔[稱號圖檔索引] < 100000){
					稱號.稱號結構[i] = 0;
					StockDispBuffer(0x16D+20,0x35+i*0x20,109,稱號.圖檔[稱號圖檔索引],0);
				}else{
					稱號.稱號結構[i] = MakeAnimDisp(0x16D+20,0x35+i*0x20,稱號.圖檔[稱號圖檔索引],0);
				}
			}else if(稱號.當前稱號結構==0) StockDispBuffer(0x16D,0x35+i*0x20,109,稱號.圖檔[稱號圖檔索引],0);
			char 稱號序號[128];
			sprintf_s(稱號序號,"%03d",稱號圖檔索引+1);

			StockFontBufferExt(0x130,0x2D+i*0x20,1,FONT_PAL_GREEN,稱號序號,0,16);
			if(!稱號.確定窗口顯示){
				if(MakeHitBox(0x124,0x26+i*0x20,0x1B8,0x44+i*0x20,0x6D)==1){
					StockFontBuffer(0x123,0xD1,2,0,稱號.介紹[稱號圖檔索引],0);
					if(mouse.onceState & MOUSE_LEFT_CRICK>0){
						稱號.確定圖檔索引=稱號.稱號索引[ 稱號圖檔索引];
						稱號.確定窗口顯示=TRUE;
					}
				}
			}
		}else break;
	}
	if(稱號.確定窗口顯示){
		StockFontBuffer(0x123,0xD1,2,0,稱號.介紹[稱號.確定圖檔索引],0);
		StockFontBuffer(0x130,0x118,2,0,"確定使用該稱號嗎？",0);
		StockDispBuffer(0x16D,0x130,0x6C,55253,1);//確定窗口底圖
		按鈕ID = StockDispBuffer(0x194,0x148,109,55252,2);//關閉
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(按鈕ID == HitDispNo){
				稱號.確定窗口顯示=FALSE;
				稱號.確定圖檔索引=0;
			}
		}
		按鈕ID = StockDispBuffer(0x148,0x148,109,55254,2);//確定
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(按鈕ID == HitDispNo){
				int checksum=0;
				char buf[1024*4];
				memset(buf,0,1024*4);
				checksum += util_mkint(buf, 稱號.確定圖檔索引);
				util_mkint(buf, checksum);
				util_SendMesg(sockfd, LSSPROTO_CHARTITLE_SEND, buf);
				稱號.確定窗口顯示=FALSE;
				稱號.確定圖檔索引=0;
			}
		}
	}
	return FALSE;
}

void 窗口結束處理(ACTION* ID)//結束顯示動畫 
{
	稱號.窗口顯示=FALSE;
	結束稱號展示動畫();
	if(稱號.當前稱號結構) DeathAction(稱號.當前稱號結構);
	稱號.當前稱號結構=0;
	DeathAction(ID);
}

void 人物稱號數據更新(char *數據)
{
	char 基礎內容[126],圖檔內容[1024],圖檔索引[1024],內容介紹[4000],臨時[126];
	memset(基礎內容,0,126);
	memset(圖檔內容,0,1024);
	memset(圖檔索引,0,1024);
	memset(內容介紹,0,4000);
	getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",1,基礎內容,126);
	getStringFromIndexWithDelim_body((char *) 基礎內容,(char *)"|",1,臨時,126);
	int 值 = atoi(臨時);
	if(值) 稱號.當前稱號圖檔=值;
	getStringFromIndexWithDelim_body((char *) 基礎內容,(char *)"|",2,臨時,126);
	int 數量 = atoi(臨時);
	if(數量!=0){
		memset(&稱號.圖檔,0,sizeof(int)*100);
		memset(&稱號.稱號索引,0,sizeof(int)*100);
		memset(&稱號.介紹,0,32*100);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",2,圖檔內容,1024);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",3,內容介紹,4000);
		getStringFromIndexWithDelim_body((char *) 數據,(char *)"#@",4,圖檔索引,1024);
		int i=0;
		for(i;i<數量;i++){
			getStringFromIndexWithDelim_body((char *)圖檔內容,(char *)"|",i+1,臨時,126);
			稱號.圖檔[i]=atoi(臨時);
			getStringFromIndexWithDelim_body((char *)圖檔索引,(char *)"|",i+1,臨時,126);
			稱號.稱號索引[i]=atoi(臨時);
			getStringFromIndexWithDelim_body((char *)內容介紹,(char *)"|",i+1,臨時,126);
			sprintf_s(稱號.介紹[i],32,"%s",臨時);
		}
	}
}

void 初始化稱號結構()
{
	memset(&稱號,0,sizeof(稱號數據結構));
}
#endif


