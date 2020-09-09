#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/CharSignDay.h"
#include "../newproto/autil.h"
#include "../systeminc/menu.h"
#include "../systeminc/shop.h"
#include "../systeminc/t_music.h"
#include "../newproto/protocol.h"
#include "../other/caryIme.h"
#include "../systeminc/field.h"
#include "../systeminc/netmain.h"
#ifdef _CHARSIGNDAY_
extern unsigned int sockfd;
extern int nowGx, nowGy;
extern int indexWN;
extern int idWN;
extern short wnCloseFlag;
extern int cloasewindows;
extern int windowTypeWN;
ACTION * 簽到動作地址=0;
int 簽到窗口X,簽到窗口Y;
extern char 二級窗口內容[1024];
int 簽到二級窗口;

typedef struct {
	int ID;
	char 道具名[64];
	char 數據[512];
}簽到道具結構;

typedef struct {
	int 道具空;
	int 狀態;
	int 當月天數;
	int 當天幾號;
	簽到道具結構 道具[30];
}簽到結構;

簽到結構 簽到數據;
short 簽到道具內容坐標[][2]={
							{0,3},
							{1,6},
							{2,8},
							{3,11},
							{4,13},
							{5,16}
						 };
int 簽到窗口寬=588;
int 簽到窗口高=396;

void 簽到窗口初始化(char * 內容)
{
	memset(&簽到數據,0,sizeof(簽到結構));
	memset(二級窗口內容,0,1024);
	if(簽到動作地址) DeathAction(簽到動作地址);
	簽到動作地址=0;
	char *臨時=new char [512];
	char *臨時數據=new char [512];
	memset(臨時,0,512);
	memset(臨時數據,0,512);
	getStringFromIndexWithDelim_body((char *) 內容,(char *)"|",1,臨時,10);
	簽到數據.道具空=atoi(臨時);
	memset(臨時,0,10);
	getStringFromIndexWithDelim_body((char *) 內容,(char *)"|",2,臨時,10);
	簽到數據.當月天數=atoi(臨時);
	memset(臨時,0,10);
	getStringFromIndexWithDelim_body((char *) 內容,(char *)"|",3,臨時,10);
	簽到數據.當天幾號=atoi(臨時);
	memset(臨時,0,10);
	getStringFromIndexWithDelim_body((char *) 內容,(char *)"|",4,臨時,30);
	簽到數據.狀態=atoi(臨時);
	memset(臨時,0,512);
	memset(臨時數據,0,512);
	int i;
	for(i=0;i<簽到數據.當月天數;i++){
		getStringFromIndexWithDelim_body((char *) 內容,(char *)"#@",2+i,臨時,512);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",1,臨時數據,10);
		簽到數據.道具[i].ID=atoi(臨時數據);
		memset(臨時數據,0,10);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",2,臨時數據,64);
		sprintf(簽到數據.道具[i].道具名,"%s",臨時數據);
		memset(臨時數據,0,64);
		getStringFromIndexWithDelim_body((char *) 臨時,(char *)"|",3,臨時數據,512);
		sprintf(簽到數據.道具[i].數據,"%s",臨時數據);
		memset(臨時,0,512);
		memset(臨時數據,0,512);
	}
	delete 臨時;
	delete 臨時數據;
	簽到二級窗口=0;
	簽到窗口X=(800-簽到窗口寬)/2+簽到窗口寬/2;
	簽到窗口Y=(600-簽到窗口高)/2-40+簽到窗口高/2;
}

ACTION* 創建簽到窗口()
{
	if(簽到動作地址) DeathAction(簽到動作地址);
	簽到動作地址 = MakeWindowDisp(簽到窗口X,簽到窗口Y,0,0,55217,0,FALSE);
	play_se(202,320,240);
	return 簽到動作地址;
}

void 清除簽到動作()
{
	if(簽到動作地址) DeathAction(簽到動作地址);
	簽到動作地址=0;
	wnCloseFlag=0;
	windowTypeWN = -1;
	wnCloseFlag = 1;
}

ACTION* 簽到數據顯示()
{
	int 底座X=55;
	int 底座Y=58;
	int 當前底座數量=0;
	int i,b;
	for(i=0;i<5;++i){
		for(b=0;b<6;++b){
			當前底座數量++;
			StockDispBuffer(簽到窗口X-225+b*底座X,簽到窗口Y-65+i*底座Y,106,簽到數據.道具[當前底座數量-1].ID,1);//道具
			if(MakeHitBox(簽到窗口X-225+b*底座X-26,簽到窗口Y-65+i*底座Y-26,簽到窗口X-225+b*底座X+26,簽到窗口Y-65+i*底座Y+26,1)==1){
				if(!簽到二級窗口) 顯示道具數據(簽到窗口X-225+b*底座X,簽到窗口Y-65+i*底座Y,112,簽到數據.道具[當前底座數量-1].數據,0,簽到數據.道具[當前底座數量-1].道具名);
			}
			if((簽到數據.狀態&(1<<當前底座數量)))
			//	StockDispBuffer(400, 288, DISP_PRIO_MENU-1, 55256, 0);
				StockDispBuffer(簽到窗口X-225+b*底座X,簽到窗口Y-65+i*底座Y,107,55269,1);//簽到成功
			if(當前底座數量 >= 簽到數據.當月天數) break;
		}
	}
//底圖
	StockDispBuffer(簽到窗口X,簽到窗口Y+28,104,55217,1);
//簽到
	int 按鈕ID = StockDispBuffer(簽到窗口X+200,簽到窗口Y+207,105,55216,2);
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if( HitDispNo == 按鈕ID ){
			lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"1");
			簽到二級窗口=1;		
		}
	
	}
	
//關閉
	if(MakeHitBox(簽到窗口X+253,簽到窗口Y-175,簽到窗口X+283,簽到窗口Y-149,1)==1){
		StockDispBuffer(簽到窗口X+270,簽到窗口Y-160,105,40165,1);
		if(mouse.onceState & MOUSE_LEFT_CRICK  && !簽到二級窗口){
			windowTypeWN = -1;
			wnCloseFlag = 1;
		}
	}
	
	if(簽到二級窗口){
		StockDispBuffer(簽到窗口X-186,簽到窗口Y-58,111,40088,1);
		StockFontBuffer(簽到窗口X-138,簽到窗口Y-16,2,0,二級窗口內容,0);
		按鈕ID = StockDispBuffer(簽到窗口X+5,簽到窗口Y+37,112,26042,2);
		if( mouse.onceState & MOUSE_LEFT_CRICK ){
			if( HitDispNo == 按鈕ID ){
				簽到二級窗口=0;
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
		|| cloasewindows == 1) 清除簽到動作();
	return 簽到動作地址;
}

void 置簽到狀態(int 狀態)
{
	簽到數據.狀態=狀態;
}



#endif



