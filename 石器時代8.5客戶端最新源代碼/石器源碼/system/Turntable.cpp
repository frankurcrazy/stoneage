#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/Turntable.h"
#include "../newproto/autil.h"
#include "../systeminc/menu.h"
#include "../systeminc/shop.h"
#include "../systeminc/t_music.h"
#include "../newproto/protocol.h"
#include "../other/caryIme.h"
#include "../systeminc/field.h"
#include "../systeminc/netmain.h"
char 二級窗口內容[1024];
#ifdef _ICONBUTTONS_
extern unsigned int sockfd;
extern int nowGx, nowGy;
extern int indexWN;
extern int idWN;
ACTION* 轉盤動作地址=0;

typedef struct {
	int 形像;
	char 名[64];
	char 數據[512];
}轉盤道具結構;

typedef struct {
	int x;
	int y;
}轉盤坐標結構;

int 轉盤道具位置[10][2]={
						{0x0,-0x74},
						{0x53,-0x5B},
						{0x86,-0x13},
						{0x86,0x43},
						{0x57,0x8A},
						{0x2,0xA6},
						{-0x51,0x8A},
						{-0x84,0x46},
						{-0x85,-0x10},
						{-0x52,-0x58},
						};

轉盤坐標結構 轉盤坐標[10];

typedef struct {
	int x;
	int y;
	int 選中索引;
	BOOL 二級窗口;
	int 轉動;//(0未轉動 1轉動中 2轉動完瞭)
	int 指針位置;
	int 指針次數;
	int 指針圈數;
	轉盤道具結構 道具[10];
}轉盤窗口結構;

轉盤窗口結構 轉盤窗口;

void 轉盤窗口初始化(char * 內容)
{
	轉盤坐標[0].x=0;
	轉盤坐標[0].y=-0x30;
	轉盤坐標[1].x=0x2C;
	轉盤坐標[1].y=-0x21;
	轉盤坐標[2].x=0x49;
	轉盤坐標[2].y=0x7;
	轉盤坐標[3].x=0x48;
	轉盤坐標[3].y=0x2F;
	轉盤坐標[4].x=0x2D;
	轉盤坐標[4].y=0x57;
	轉盤坐標[5].x=0x4;
	轉盤坐標[5].y=0x66;
	轉盤坐標[6].x=-0x27;
	轉盤坐標[6].y=0x5A;
	轉盤坐標[7].x=-0x48;
	轉盤坐標[7].y=0x32;
	轉盤坐標[8].x=-0x47;
	轉盤坐標[8].y=0x8;
	轉盤坐標[9].x=-0x2A;
	轉盤坐標[9].y=-0x20;
	memset(&轉盤窗口,0,sizeof(轉盤窗口結構));
	memset(二級窗口內容,0,1024);
	if(轉盤動作地址) DeathAction(轉盤動作地址);
	轉盤動作地址=0;
	char *臨時=new char [513];
	char *臨時1=new char [513];
	int i;
	for(i=0;i<10;i++){
		memset(臨時,0,512);
		memset(臨時1,0,20);
		getStringFromIndexWithDelim_body((char *) 內容,(char *)"#@",i+1,臨時,512);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",1,臨時1,512);
		轉盤窗口.道具[i].形像 = atoi(臨時1);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",2,轉盤窗口.道具[i].名,64);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",3,轉盤窗口.道具[i].數據,512);
	}
	delete 臨時;
	delete 臨時1;
	int 窗口寬=424;
	int 窗口高=424;
	轉盤窗口.x=(800-窗口寬)/2+窗口寬/2;
	轉盤窗口.y=(600-窗口高)/2-40+窗口高/2;
}

ACTION* 創建轉盤窗口()
{
	if(轉盤動作地址) DeathAction(轉盤動作地址);
	轉盤動作地址=0;
	轉盤動作地址 = MakeWindowDisp(轉盤窗口.x,轉盤窗口.y,0,0,40166,0,FALSE);
	play_se(202,320,240);
	return 轉盤動作地址;
}

void 轉動後沒給道具()
{
	if(轉盤窗口.轉動==1){
		轉盤窗口.轉動=2;
		lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"2");
	}
}
extern short wnCloseFlag;
extern int windowTypeWN;
void 清除轉盤動作()
{
	if(轉盤動作地址) DeathAction(轉盤動作地址);
	轉動後沒給道具();
	轉盤動作地址=0;
	wnCloseFlag=0;
	windowTypeWN = -1;
	wnCloseFlag = 1;
}
extern int cloasewindows;

ACTION* 轉盤數據顯示()
{
	//底圖
	StockDispBuffer(轉盤窗口.x,轉盤窗口.y+28,104,40166,1);

	//關閉
	if(MakeHitBox(轉盤窗口.x+0x61,轉盤窗口.y-0x99,轉盤窗口.x+0x80,轉盤窗口.y-0x7D,1)==1){
		StockDispBuffer(轉盤窗口.x+0x71-2,轉盤窗口.y-0x8B,105,40165,1);
		if( (mouse.onceState & MOUSE_LEFT_CRICK)  && !轉盤窗口.二級窗口){
			windowTypeWN = -1;
			wnCloseFlag = 1;
		}
	}
	//開始按鈕
	if(轉盤窗口.轉動)
		StockDispBuffer(轉盤窗口.x,轉盤窗口.y+0x1B+1,105,40164,1);
	else{
		if(MakeHitBox(轉盤窗口.x-0x30,轉盤窗口.y-0x14,轉盤窗口.x+0x30,轉盤窗口.y+0x4A,1)==1){
			StockDispBuffer(轉盤窗口.x,轉盤窗口.y+0x1B+1,105,40164,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK) && !轉盤窗口.二級窗口){
				lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"1");
			}
		}
	}
	if(轉盤窗口.轉動==1){
		if(轉盤窗口.指針次數>2){
			轉盤窗口.指針次數 = 0;
			if(轉盤窗口.指針位置==9) {
				轉盤窗口.指針圈數++;
				轉盤窗口.指針位置=0;
			}
			else 轉盤窗口.指針位置++;
		}else 轉盤窗口.指針次數++;
		if(轉盤窗口.指針圈數 == 8 && 轉盤窗口.指針位置==(轉盤窗口.選中索引-1)) {
			轉盤窗口.轉動=2;
			轉盤窗口.二級窗口=TRUE;
			lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"2");
		}
	}
	StockDispBuffer(轉盤窗口.x+轉盤坐標[轉盤窗口.指針位置].x,轉盤窗口.y+轉盤坐標[轉盤窗口.指針位置].y,106,40153+轉盤窗口.指針位置,1);
	//道具顯示
	int i;
	for(i=0;i<10;i++){
		StockDispBuffer(轉盤窗口.x+轉盤道具位置[i][0],轉盤窗口.y+轉盤道具位置[i][1],106,轉盤窗口.道具[i].形像,1);
		if(!轉盤窗口.二級窗口)
		if(MakeHitBox(轉盤窗口.x+轉盤道具位置[i][0]-30,轉盤窗口.y+轉盤道具位置[i][1]-30,轉盤窗口.x+轉盤道具位置[i][0]+30,轉盤窗口.y+轉盤道具位置[i][1]+30,1)==1){
			//extern void 顯示道具數據(short x,short y,UCHAR 層次,char* 內容,int 形像 ,char*名字);
			顯示道具數據(轉盤窗口.x+轉盤道具位置[i][0],轉盤窗口.y+轉盤道具位置[i][1],107,轉盤窗口.道具[i].數據,0,轉盤窗口.道具[i].名);
		}
	}
	//窗口提示
	if(轉盤窗口.二級窗口){
		StockDispBuffer(轉盤窗口.x-0xC1,轉盤窗口.y-0x32,107,40088,1);
		extern int getTextLength(char * str);
		StockFontBuffer(轉盤窗口.x-getTextLength(二級窗口內容)/2,轉盤窗口.y+5,2,0,二級窗口內容,1);
		int 按鈕ID = StockDispBuffer(轉盤窗口.x,轉盤窗口.y+50,109,26042,2);
		if( mouse.onceState & MOUSE_LEFT_CRICK ){
			if( HitDispNo == 按鈕ID ){
				轉盤窗口.二級窗口=0;
				windowTypeWN = -1;
				wnCloseFlag = 1;
				memset(二級窗口內容,0,1024);			
			}
		}
	}
	if(CheckMenuFlag()
		|| ((joy_trg[ 0 ] & JOY_ESC) && GetImeString() == NULL)
		|| actBtn == 1
		|| menuBtn == 1
		|| disconnectServerFlag == TRUE
		|| wnCloseFlag == 1 
		|| cloasewindows == 1) 清除轉盤動作();
	return 轉盤動作地址;
}

void 置轉盤數據(int 選中索引)
{
	轉盤窗口.轉動=1;
	轉盤窗口.選中索引=選中索引;
}
#endif





