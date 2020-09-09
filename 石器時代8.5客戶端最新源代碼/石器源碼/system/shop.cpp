/************************/
#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/pc.h"
#include "../systeminc/shop.h"
#include "../systeminc/tool.h"
#include "../systeminc/menu.h"
#include "../systeminc/t_music.h"
#include "../systeminc/netmain.h"
#include "../systeminc/map.h"
#include "../NewProto/protocol.h"
#include "../systeminc/login.h"
#include "../other/caryIme.h"
#include "../systeminc/field.h"
#include "../wgs/tea.h"
#include "../systeminc/VMProtectSDK.h"
int getfilesize(FILE* fp)
{
	if( fp == NULL) return 0;
	int size;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	return size;
}
#ifdef _NEWSHOP_

void 商城結算(short x,short y,UCHAR 層次);
void 清除商城動作();
void 購物車商品刪除(short 索引);

extern void getStrSplit( char *, char *, int, int, int );
void StockFontBufferSplit(int x, int y, char unk1, int color, char* data, int unk2,int strLen){

	char token[310]={0};
	getStrSplit(token,(char *)data,0x64,3,strLen);
	char * b = token;
	int c = 20;
	int d = 0;
	do{
		if(strlen(b)!=1) StockFontBuffer(x,y+c*d,unk1,color,b,unk2);
		++d;
		b+=100;
	}while(d < 3);
}

typedef int                 BOOL;
extern int indexWN;
extern int idWN;
extern int cloasewindows;
typedef struct {
	char 商品名[32];
	unsigned int 商品形像;
	unsigned int 詳細商品形像;
	unsigned int 商品價格;
	char 商品說明[500];
	short 序號;

}商品數據結構;


商城文件_ 商城文件[5];

typedef struct {
  short 當前;
  short 終點;
} 滾動條結構;

typedef struct {
	BOOL 使用;
	unsigned int 數量;
	商品數據結構 * 商品;
}購物車商品結構;

typedef struct {
  購物車商品結構 購物欄[15];
  short 商品總數;
  short 商品類型個數;
  short 當前頁數;
  short 總頁數;
  unsigned int 總價格;
} 購物車結構;

typedef struct {
  滾動條結構 滾動條;
  購物車結構 購物車;
  short 道具空;
  short 窗口ID;
  short 提示類型;
  short 商品數量;
  BOOL 結算窗口;
  unsigned int 玩傢彩幣;
  ACTION * 寵物動作結構;
  ACTION * 窗口動作結構;
  short 寬;
  short 高;
  short X;
  short Y;
  short 寵物位置;
  BOOL 寵物購物欄狀態;
} 商城結構;



商品數據結構 商品數據[200];
商城結構 商城數據;

short 商城道具坐標[][2] = {
							{90,100},
							{245,100},
							{90,193},
							{245,193},
							{90,282},
							{242,282},
							{90,369},
							{242,369}
						  };

short 道具內容坐標[][2]={
							{0,5},
							{1,9},
							{2,11},
							{3,14},
							{4,17},
							{5,19}
						 };

unsigned short 窗口顯示[][4] ={
								{40041,40046,40066,35},
								{40042,40047,40067,106},
								{40043,40048,40068,176},
								{40044,40049,40069,246},
								{40045,40050,40070,316},
							   }; 

void 在綫商城數據初始化()
{
	memset(&商品數據,0,sizeof(商品數據結構)*200);
	memset(&商城數據,0,sizeof(商城結構));
}

int 字符串切割( char *arr[], char *str, const char *del)//字符分割函數的簡單定義搜索和實現
{
	int num = 0;
	char *s =NULL;
	char *p =NULL;
	s=strtok_s(str,del,&p); 
	while(s != NULL) {
		arr[num] = s;
		s = strtok_s(NULL,del,&p);
		num++;
	}
	num--;
	return num;
}


void 在綫商城窗口初始化(char * 內容)
{
	if(商城數據.窗口動作結構) DeathAction(商城數據.窗口動作結構);
	商城數據.窗口動作結構=0;
	if(商城數據.寵物動作結構) DeathAction(商城數據.寵物動作結構);
	商城數據.寵物動作結構=0;
	商城數據.寵物位置=-1;
	在綫商城數據初始化();
	商城數據.道具空 = getIntegerToken(內容,'|',1);
	商城數據.玩傢彩幣 = getIntegerToken(內容,'|',2);
	商城數據.窗口ID = getIntegerToken(內容,'|',3);
	商城數據.滾動條.當前=1;
	if(商城文件[商城數據.窗口ID-1].商城數據!=NULL){
		int strlena=strlen(商城文件[商城數據.窗口ID-1].商城數據);
		char *臨時商城內容 = new char [strlena+1];
		memset(臨時商城內容,0,strlena+1);
		memcpy(臨時商城內容,商城文件[商城數據.窗口ID-1].商城數據,strlena);
		char *臨時全部道具數據[200] ={0};
		char *臨時單個道具數據[5]={0};
		商城數據.商品數量 = 字符串切割(臨時全部道具數據,臨時商城內容,"#");
		int i=0;
		for(;i<=商城數據.商品數量;i++){
			字符串切割(臨時單個道具數據,臨時全部道具數據[i],"|");
			sprintf_s(商品數據[i].商品名,"%s",臨時單個道具數據[0]);
			商品數據[i].商品形像 = atoi( 臨時單個道具數據[1]);
			商品數據[i].詳細商品形像 = atoi( 臨時單個道具數據[2]);
			商品數據[i].商品價格 =  atoi( 臨時單個道具數據[3]);
			sprintf_s(商品數據[i].商品說明,"%s",臨時單個道具數據[4]);
			商品數據[i].商品名[strlen(商品數據[i].商品名)]=0;
			商品數據[i].商品說明[strlen(商品數據[i].商品說明)]=0;
			商品數據[i].序號=i;
		}
		商城數據.商品數量++;
		if(商城數據.商品數量 > 8)
			商城數據.滾動條.終點= 商城數據.商品數量%8 ? 商城數據.商品數量/8+1 : 商城數據.商品數量/8;
		else 商城數據.滾動條.終點= 1;
		商城數據.寵物位置=-1;
		商城數據.寵物購物欄狀態=FALSE;
		delete 臨時商城內容;
	}
	商城數據.寬=628;
	商城數據.高=386;
	商城數據.X=(800-商城數據.寬)/2;
	商城數據.Y=(600-商城數據.高)/2-40;
}


ACTION* 創建商城窗口()
{
	
	if(商城數據.窗口動作結構) DeathAction(商城數據.窗口動作結構);
	商城數據.窗口動作結構 = MakeWindowDisp(商城數據.X,商城數據.Y,0,0,窗口顯示[商城數據.窗口ID-1][0],0,FALSE);
	play_se(202,320,240);
	return 商城數據.窗口動作結構;
}



ACTION* 商城數據顯示()
{
	if(商城數據.窗口ID!=5){
		if(商城數據.寵物動作結構){
			DeathAction(商城數據.寵物動作結構);
			商城數據.寵物動作結構=0;
			商城數據.寵物位置=-1;
		}
	}

	int 按鈕ID;
	StockDispBuffer(商城數據.X,商城數據.Y+28,104,窗口顯示[商城數據.窗口ID-1][0],1);
	//類型按鈕
	int i=0;
	for(;i<5;i++){
		if(i!=(商城數據.窗口ID-1)){
			if(MakeHitBox(商城數據.X+1,商城數據.Y+窗口顯示[i][3],商城數據.X+29,商城數據.Y+窗口顯示[i][3]+69,-1)==1){
				if(!商城數據.結算窗口){
					StockDispBuffer(商城數據.X+1,商城數據.Y+窗口顯示[i][3],106,窗口顯示[i][2],1);
					if( (mouse.onceState & MOUSE_LEFT_CRICK)){
						char 臨時內容[10]={0};
						sprintf_s(臨時內容,"%d",i+1);
						lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,臨時內容);
						windowTypeWN = -1;
						wnCloseFlag = 1;
					}else StockDispBuffer(商城數據.X+1,商城數據.Y+窗口顯示[i][3],106,窗口顯示[i][1],1);
				}
			}else StockDispBuffer(商城數據.X+1,商城數據.Y+窗口顯示[i][3],106,窗口顯示[i][1],1);
		}
	}


	//關閉按鈕
	if(MakeHitBox(商城數據.X+595,商城數據.Y+27,商城數據.X+626,商城數據.Y+53,-1)==1){
		StockDispBuffer(商城數據.X+594,商城數據.Y+27,105,40054,1);
		if( (mouse.onceState & MOUSE_LEFT_CRICK)){
			cloasewindows = 1;
		}
	}else StockDispBuffer(商城數據.X+595,商城數據.Y+27,105,40061,1);
	if(商城數據.結算窗口) 商城結算(商城數據.X+130,商城數據.Y+140,110);
	
	//結算按鈕

	if(MakeHitBox(商城數據.X+534,商城數據.Y+372,商城數據.X+591,商城數據.Y+391,-1)==1){
		if(!商城數據.結算窗口){
			StockDispBuffer(商城數據.X+534,商城數據.Y+372,105,40072,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)){
				if(商城數據.購物車.商品總數){
					商城數據.提示類型=1;
					商城數據.結算窗口=TRUE;
				}else{
					商城數據.提示類型=2;
					商城數據.結算窗口=TRUE;
				}
			}
		}else StockDispBuffer(商城數據.X+534,商城數據.Y+372,105,40058,1);
	}else StockDispBuffer(商城數據.X+534,商城數據.Y+372,105,40058,1);

	//清空功能
	if(MakeHitBox(商城數據.X+435,商城數據.Y+372,商城數據.X+435+58,商城數據.Y+372+19,-1)==1){
		if(!商城數據.結算窗口){
			StockDispBuffer(商城數據.X+435,商城數據.Y+372,105,40059,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)){
				商城數據.購物車.當前頁數=0;
				商城數據.購物車.總頁數=0;
				商城數據.購物車.商品類型個數=0;
				商城數據.購物車.商品總數=0;
				商城數據.購物車.總價格=0;
				商城數據.購物車.總頁數=0;
				memset(商城數據.購物車.購物欄,0,sizeof(購物車商品結構)*15);
			}
		}else StockDispBuffer(商城數據.X+435,商城數據.Y+372,105,40073,1);
	}else StockDispBuffer(商城數據.X+435,商城數據.Y+372,105,40073,1);

	
	//商品上頁
	if(MakeHitBox(商城數據.X+379,商城數據.Y+39,商城數據.X+405,商城數據.Y+66,-1)==1){
		if(!商城數據.結算窗口){
			StockDispBuffer(商城數據.X+379,商城數據.Y+39,105,40055,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)){
				if(商城數據.滾動條.當前>1) 商城數據.滾動條.當前-=1;
			}
		}else StockDispBuffer(商城數據.X+379,商城數據.Y+39,105,40062,1);
	}else StockDispBuffer(商城數據.X+379,商城數據.Y+39,105,40062,1);

	//商品下頁
	if(MakeHitBox(商城數據.X+379,商城數據.Y+370,商城數據.X+405,商城數據.Y+397,-1)==1){
		if(!商城數據.結算窗口){
			StockDispBuffer(商城數據.X+379,商城數據.Y+370,105,40056,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)){
				if(商城數據.滾動條.當前<商城數據.滾動條.終點) 商城數據.滾動條.當前+=1;
			}
		}else StockDispBuffer(商城數據.X+379,商城數據.Y+370,105,40063,1);
	}else StockDispBuffer(商城數據.X+379,商城數據.Y+370,105,40063,1);

	//printf("當前=%d  結束=%d\n",商城數據.滾動條.當前,商城數據.滾動條.終點);
	short 滾動條塊位置=0;
	if(商城數據.滾動條.當前==1 || 商城數據.滾動條.當前==0) 滾動條塊位置=75;
	else if(商城數據.滾動條.當前==商城數據.滾動條.終點) 滾動條塊位置=361;
	else 滾動條塊位置=(361-75)/(商城數據.滾動條.終點-1)*(商城數據.滾動條.當前-1)+75;
	StockDispBuffer(商城數據.X+391,商城數據.Y+滾動條塊位置,105,26447,1);
	
	//商城數據顯示
	
	if(商城數據.商品數量>0){
		short 開始,結束;
		開始 = (商城數據.滾動條.當前-1)*8+1;
		結束 = 開始+7;
		if(結束 >商城數據.商品數量) 結束 = 商城數據.商品數量;
		short 臨時位置=0;
		BOOL 寵物判斷=FALSE;
		i=開始;
		for(;i<=結束;i++){
			臨時位置++;
			按鈕ID = StockDispBuffer(商城數據.X+商城道具坐標[臨時位置-1][0],商城數據.Y+商城道具坐標[臨時位置-1][1],106,商品數據[i-1].商品形像,1);
			if(HitDispNo==按鈕ID){
				if(!商城數據.結算窗口){
					if(商城數據.寵物動作結構){
						if(商城數據.寵物位置!=按鈕ID){
							DeathAction(商城數據.寵物動作結構);
							商城數據.寵物動作結構=0;
							商城數據.寵物位置=-1;
						}
					}
					顯示道具數據(商城數據.X+商城道具坐標[臨時位置-1][0],商城數據.Y+商城道具坐標[臨時位置-1][1],109,商品數據[i-1].商品說明,商品數據[i-1].詳細商品形像,商品數據[i-1].商品名);
					寵物判斷=TRUE;
					if(商城數據.寵物動作結構) 商城數據.寵物位置=按鈕ID;
				}else{
					if(商城數據.寵物動作結構){
						DeathAction(商城數據.寵物動作結構);
						商城數據.寵物動作結構=0;
						商城數據.寵物位置=-1;
					}
				}
			}
			//購買按鈕
			if(MakeHitBox(商城數據.X+商城道具坐標[臨時位置-1][0]+40,商城數據.Y+商城道具坐標[臨時位置-1][1],商城數據.X+商城道具坐標[臨時位置-1][0]+40+59,商城數據.Y+商城道具坐標[臨時位置-1][1]+22,-1)==1){
				if(!商城數據.結算窗口){
					StockDispBuffer(商城數據.X+商城道具坐標[臨時位置-1][0]+40,商城數據.Y+商城道具坐標[臨時位置-1][1],105,40071,1);
					if( (mouse.onceState & MOUSE_LEFT_CRICK)){
						if(商城數據.玩傢彩幣 < 商城數據.購物車.總價格 + 商品數據[i-1].商品價格){
							StockChatBufferLine("係統：身上的金幣不足。",6);
							break;
						}
						if(商城數據.道具空 < 商城數據.購物車.商品總數+1){
							StockChatBufferLine("係統：身上的道具位不足。",6);
							break;
						}
						if(!商城數據.購物車.商品類型個數){
							memset(&商城數據.購物車.購物欄,0,sizeof(購物車商品結構)*15);
							商城數據.購物車.購物欄[0].使用=TRUE;
							商城數據.購物車.購物欄[0].數量=1;
							商城數據.購物車.當前頁數=1;
							商城數據.購物車.購物欄[0].商品=&商品數據[i-1];
							商城數據.購物車.商品類型個數++;
							商城數據.購物車.商品總數++;
							商城數據.購物車.總價格+=商城數據.購物車.購物欄[0].商品->商品價格;
						}else{
							BOOL 判斷是否已經購買瞭=FALSE;
							int k=0;
							for(;k<15;k++){
								if(商城數據.購物車.購物欄[k].使用){
									//printf("地址1=%x   地址2=%x\n",商城數據.購物車.購物欄[0].商品,&商品數據[i-1]);
									if(商城數據.購物車.購物欄[k].商品 == &商品數據[i-1]){
										判斷是否已經購買瞭=TRUE;
										商城數據.購物車.購物欄[k].數量++;
										商城數據.購物車.商品總數++;
										商城數據.購物車.總價格+=商城數據.購物車.購物欄[k].商品->商品價格;
										break;
									}
								}
							}
							if(!判斷是否已經購買瞭){
								if(商城數據.購物車.購物欄[0].使用){
									購物車商品結構 臨時購物車數據1;
									購物車商品結構 臨時購物車數據2;
									臨時購物車數據1.商品 = 商城數據.購物車.購物欄[0].商品;
									臨時購物車數據1.數量 = 商城數據.購物車.購物欄[0].數量;
									k=1;
									for(;k<15;k++){
										if(商城數據.購物車.購物欄[k].使用){
											臨時購物車數據2.商品 = 商城數據.購物車.購物欄[k].商品;
											臨時購物車數據2.數量 = 商城數據.購物車.購物欄[k].數量;
											商城數據.購物車.購物欄[k].商品=臨時購物車數據1.商品;
											商城數據.購物車.購物欄[k].數量=臨時購物車數據1.數量;
											臨時購物車數據1.商品=臨時購物車數據2.商品;
											臨時購物車數據1.數量=臨時購物車數據2.數量;
										}else{
											商城數據.購物車.購物欄[k].使用 = TRUE;
											商城數據.購物車.購物欄[k].商品=臨時購物車數據1.商品;
											商城數據.購物車.購物欄[k].數量=臨時購物車數據1.數量;
											break;
										}
									}
								}
								商城數據.購物車.購物欄[0].商品 = &商品數據[i-1];
								商城數據.購物車.購物欄[0].數量 = 1;
								商城數據.購物車.購物欄[0].使用 = TRUE;
								商城數據.購物車.商品類型個數++;
								商城數據.購物車.商品總數++;
								商城數據.購物車.總價格+=商城數據.購物車.購物欄[0].商品->商品價格;
							}
						}
					//	printf("商城數據.購物車.商品類型個數%3   = %d\n",商城數據.購物車.商品類型個數%3);
						商城數據.購物車.總頁數 = 商城數據.購物車.商品類型個數%3 ? 商城數據.購物車.商品類型個數/3+1 : 商城數據.購物車.商品類型個數/3;
						if(商城數據.購物車.總頁數*3-2>商城數據.購物車.商品類型個數) 商城數據.購物車.總頁數--;
						if(!商城數據.購物車.總頁數) 商城數據.購物車.總頁數=1;
					}
				}else StockDispBuffer(商城數據.X+商城道具坐標[臨時位置-1][0]+40,商城數據.Y+商城道具坐標[臨時位置-1][1],105,40057,1);
			}else StockDispBuffer(商城數據.X+商城道具坐標[臨時位置-1][0]+40,商城數據.Y+商城道具坐標[臨時位置-1][1],105,40057,1);
			char 臨時內容[128]={0};
			sprintf_s(臨時內容,"%-5d金幣",商品數據[i-1].商品價格);
			StockFontBuffer(商城數據.X+商城道具坐標[臨時位置-1][0]+15,商城數據.Y+商城道具坐標[臨時位置-1][1]-45,1,0,商品數據[i-1].商品名,0);
			StockFontBuffer(商城數據.X+商城道具坐標[臨時位置-1][0]+38,商城數據.Y+商城道具坐標[臨時位置-1][1]-20,1,4,臨時內容,0);
		}
		if(!商城數據.寵物購物欄狀態 && !寵物判斷){
			if(商城數據.寵物動作結構){
				DeathAction(商城數據.寵物動作結構);
				商城數據.寵物動作結構=0;
				商城數據.寵物位置=-1;
			}
		}
	}
	//購物車處理
	if(商城數據.購物車.商品總數>0){
		short 開始,結束;
		開始 = (商城數據.購物車.當前頁數-1)*3+1;
		結束 = 商城數據.購物車.當前頁數*3;
		if(結束>商城數據.購物車.商品類型個數) 結束 = 商城數據.購物車.商品類型個數;
		short 臨時位置 =0;
		BOOL 購物判斷 = FALSE;
		int i=開始;
		for(;i<=結束;i++){
			臨時位置++;
			
			StockDispBuffer(商城數據.X+412,商城數據.Y+67+((臨時位置-1)*80),105,40053,1);
			//購物車左頁
			if(MakeHitBox(商城數據.X+505,商城數據.Y+121+((臨時位置-1)*80),商城數據.X+505+31,商城數據.Y+121+((臨時位置-1)*80)+16,-1)==1){
				if(!商城數據.結算窗口){
					StockDispBuffer(商城數據.X+505,商城數據.Y+121+((臨時位置-1)*80),106,40064,1);
					if( (mouse.onceState & MOUSE_LEFT_CRICK)){
						商城數據.購物車.總價格-= 商城數據.購物車.購物欄[i-1].商品->商品價格;
						商城數據.購物車.商品總數-=1;
						if(商城數據.購物車.購物欄[i-1].數量==1){
							購物車商品刪除(i-1);
							商城數據.購物車.商品類型個數--;
							商城數據.購物車.總頁數  = 商城數據.購物車.商品類型個數%3 ? 商城數據.購物車.商品類型個數/3+1 : 商城數據.購物車.商品類型個數/3;
							if(商城數據.購物車.總頁數*3>商城數據.購物車.商品類型個數) 商城數據.購物車.總頁數--;
							if(!商城數據.購物車.總頁數&&商城數據.購物車.商品類型個數) 商城數據.購物車.總頁數=1;
							if(商城數據.購物車.當前頁數>商城數據.購物車.總頁數) 商城數據.購物車.當前頁數 = 商城數據.購物車.總頁數;
							if(!商城數據.購物車.商品類型個數) 
							{
								商城數據.購物車.當前頁數=0;
								商城數據.購物車.總頁數=0;
							}
							break;
						}else 商城數據.購物車.購物欄[i-1].數量-=1;
					}
				}else StockDispBuffer(商城數據.X+505,商城數據.Y+121+((臨時位置-1)*80),106,40051,1);
			}else StockDispBuffer(商城數據.X+505,商城數據.Y+121+((臨時位置-1)*80),106,40051,1);



			if(MakeHitBox(商城數據.X+571,商城數據.Y+121+((臨時位置-1)*80),商城數據.X+571+31,商城數據.Y+121+((臨時位置-1)*80)+16,-1)==1){
				if(!商城數據.結算窗口){
					StockDispBuffer(商城數據.X+571,商城數據.Y+121+((臨時位置-1)*80),106,40065,1);
					if( (mouse.onceState & MOUSE_LEFT_CRICK)){
						if(商城數據.玩傢彩幣 < 商城數據.購物車.總價格 + 商城數據.購物車.購物欄[i-1].商品->商品價格){
							StockChatBufferLine("係統：身上的金幣不足。",6);
							break;
						}
						if(商城數據.道具空 < 商城數據.購物車.商品總數+1){
							StockChatBufferLine("係統：身上的道具位不足。",6);
							break;
						}
						商城數據.購物車.商品總數++;
						商城數據.購物車.總價格+=商城數據.購物車.購物欄[i-1].商品->商品價格;
						商城數據.購物車.購物欄[i-1].數量++;
					}
				}else StockDispBuffer(商城數據.X+571,商城數據.Y+121+((臨時位置-1)*80),106,40052,1);
			}else StockDispBuffer(商城數據.X+571,商城數據.Y+121+((臨時位置-1)*80),106,40052,1);
			按鈕ID = StockDispBuffer(商城數據.X+455,商城數據.Y+105+((臨時位置-1)*80),106,商城數據.購物車.購物欄[i-1].商品->商品形像,1);

			if(HitDispNo==按鈕ID){
				if(!商城數據.結算窗口){
					if(商城數據.寵物動作結構){
						if(商城數據.寵物位置!=按鈕ID){
							DeathAction(商城數據.寵物動作結構);
							商城數據.寵物動作結構=0;
							商城數據.寵物位置=-1;
						}
					}
					顯示道具數據(商城數據.X+455,商城數據.Y+105+((臨時位置-1)*80),109,商城數據.購物車.購物欄[i-1].商品->商品說明,商城數據.購物車.購物欄[i-1].商品->詳細商品形像,商城數據.購物車.購物欄[i-1].商品->商品名);
					購物判斷=TRUE;
					if(商城數據.寵物動作結構) 商城數據.寵物位置=按鈕ID;
				}else if(商城數據.寵物動作結構){
					DeathAction(商城數據.寵物動作結構);
					商城數據.寵物動作結構=0;
					商城數據.寵物位置=-1;
				}
			}
			char 臨時內容[128]={0};
			sprintf_s(臨時內容,"%-5d金幣",商城數據.購物車.購物欄[i-1].商品->商品價格);
			StockFontBuffer(商城數據.X+500,商城數據.Y+80+((臨時位置-1)*80),1,0,商城數據.購物車.購物欄[i-1].商品->商品名,0);
			StockFontBuffer(商城數據.X+535,商城數據.Y+100+((臨時位置-1)*80),1,4,臨時內容,0);
			sprintf_s(臨時內容,"%d",商城數據.購物車.購物欄[i-1].數量);
			臨時內容[strlen(臨時內容)]=0;
			StockFontBuffer(商城數據.X+549,商城數據.Y+121+((臨時位置-1)*80),1,4,臨時內容,0);
		}
		if(購物判斷) 商城數據.寵物購物欄狀態=TRUE;
		else 商城數據.寵物購物欄狀態 = FALSE;
//購物車按鈕左頁
		if(MakeHitBox(商城數據.X+420,商城數據.Y+312,商城數據.X+420+31,商城數據.Y+312+16,-1)==1){
			if(!商城數據.結算窗口){
				StockDispBuffer(商城數據.X+420,商城數據.Y+312,105,40064,1);
				if( (mouse.onceState & MOUSE_LEFT_CRICK)){
					if(商城數據.購物車.當前頁數!=1) 商城數據.購物車.當前頁數-=1;
				}
			}else StockDispBuffer(商城數據.X+420,商城數據.Y+312,105,40051,1);
		}else StockDispBuffer(商城數據.X+420,商城數據.Y+312,105,40051,1);
//購物車按鈕右頁
		if(MakeHitBox(商城數據.X+575,商城數據.Y+312,商城數據.X+575+31,商城數據.Y+312+16,-1)==1){
			if(!商城數據.結算窗口){
				StockDispBuffer(商城數據.X+575,商城數據.Y+312,105,40065,1);
				if( (mouse.onceState & MOUSE_LEFT_CRICK)){
					if(商城數據.購物車.當前頁數!=商城數據.購物車.總頁數) 商城數據.購物車.當前頁數+=1;
				}
			}else StockDispBuffer(商城數據.X+575,商城數據.Y+312,105,40052,1);
		}else StockDispBuffer(商城數據.X+575,商城數據.Y+312,105,40052,1);
	}
	char 臨時內容[20]={0};
	sprintf_s(臨時內容,"%-3d/ %-3d",商城數據.購物車.當前頁數,商城數據.購物車.總頁數);
	StockFontBuffer(商城數據.X+490,商城數據.Y+314,1,0,臨時內容,0);
	memset(臨時內容,0,20);
	sprintf_s(臨時內容,"%d",商城數據.玩傢彩幣);
	StockFontBuffer(商城數據.X+462,商城數據.Y+342,1,0,臨時內容,0);
	memset(臨時內容,0,20);
	sprintf_s(臨時內容,"%d",商城數據.購物車.總價格);
	StockFontBuffer(商城數據.X+573,商城數據.Y+342,1,0,臨時內容,0);
	
	if( CheckMenuFlag()
		|| ((joy_trg[ 0 ] & JOY_ESC) && GetImeString() == NULL)
		|| actBtn == 1
		|| menuBtn == 1
		|| disconnectServerFlag == TRUE
		|| wnCloseFlag == 1 
		|| cloasewindows == 1)
	{
		wnCloseFlag = 0;
		cloasewindows = 0;
		清除商城動作();
	}
	return 商城數據.窗口動作結構;
}



void 清除商城動作()
{
	if(商城數據.窗口動作結構) DeathAction(商城數據.窗口動作結構);
	商城數據.窗口動作結構=0;
	if(商城數據.寵物動作結構) DeathAction(商城數據.寵物動作結構);
	商城數據.寵物動作結構=0;
	商城數據.寵物位置=-1;
	wnCloseFlag=0;
	windowTypeWN = -1;
	wnCloseFlag = 1;
}

void 商城結算(short x,short y,UCHAR 層次)
{
	if(商城數據.提示類型==1){
		StockDispBuffer(x,y,層次,40088,1);
		StockFontBuffer(x+110,y+50,2,0,"您確定需要購買這些商品嗎？",0);
		 if(MakeHitBox(x+60,y+100,x+60+105,y+100+18,-1)==1){
			StockDispBuffer(x+60,y+100,層次+1,40084,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)){
				char 內容[256]={0};
				int i=0;
				for(;i<15;i++){
					if(商城數據.購物車.購物欄[i].使用){
						char 臨時[15]={0};
						sprintf_s(臨時,"%d|%d#",商城數據.購物車.購物欄[i].商品->序號+1,商城數據.購物車.購物欄[i].數量);
						strcat_s(內容,臨時);
					}
				}
				lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,商城數據.窗口ID,內容);
				windowTypeWN = -1;
				wnCloseFlag = 1;
			}
		 }else StockDispBuffer(x+60,y+100,層次+1,40086,1);
		 if(MakeHitBox(x+220,y+100,x+220+105,y+100+18,-1)==1){
			StockDispBuffer(x+220,y+100,層次+1,40085,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)) 商城數據.結算窗口=FALSE;
		 }else StockDispBuffer(x+220,y+100,層次+1,40087,1);
	}else{
		StockDispBuffer(x,y,層次,40088,1);
		StockFontBuffer(x+130,y+50,2,0,"您的購物車沒有商品！",0);
		if(MakeHitBox(x+140,y+100,x+140+105,y+100+18,-1)==1){
			StockDispBuffer(x+140,y+100,層次+1,40090,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK)) 商城數據.結算窗口=FALSE;
		}else StockDispBuffer(x+140,y+100,層次+1,40089,1);
	}
}

void 顯示道具數據(short x,short y,UCHAR 層次,char* 內容,unsigned int 形像,char*名字 )
{
	char 臨時內容[500]={0};
	sprintf_s(臨時內容,"%s",內容);
	char *道具數據[30]={0};
	int 背景張數 = 0;
	if(商城數據.窗口ID!=5){
		背景張數 = 字符串切割(道具數據,臨時內容,"\n");
		if(道具數據[背景張數-1][0]==0) 背景張數--;
	}
	int 背景張數1=背景張數;
	int 圖片高,圖片x,圖片y,i=0;
	if(商城數據.窗口ID!=5){
		for(;i<6;i++){
			if(i==5) {
				背景張數 = 道具內容坐標[i][0];
				break;
			}
			if(道具內容坐標[i][1]>=背景張數){
				背景張數 = 道具內容坐標[i][0];
				break;
			}
		}
		圖片高 = 背景張數*48+144;
		if((x-190) >(628+商城數據.X-x-65)) 圖片x=x-190;
		else  圖片x=x+35;
		圖片y=y-(圖片高/2);
		BOOL 判斷=FALSE;
		while(true){
			if(商城數據.Y > 圖片y-20){
				圖片y +=10;
				判斷=TRUE;
			}	
			if((商城數據.Y+386+30) < (圖片y+圖片高)){
				圖片y -=10;
				判斷=TRUE;
			}
			if(判斷) 判斷=FALSE;
			else break;
		}

		StockDispBuffer(圖片x+80,圖片y+50,層次,40171,1);
		int 高=48;
		if(背景張數 >=1){
			for(i=1;i<=背景張數;i++) StockDispBuffer(圖片x+80,圖片y+50+高*(i-1)+83,層次,40172,1);
		}
		StockDispBuffer(圖片x+80,圖片y+50+高*背景張數+83,層次,40173,1);
		int 內容x,內容y;
		內容x=圖片x+6-10;
		內容y=圖片y-25+50;

		for(i=1;i<=背景張數1+1;i++) StockFontBufferSplit(內容x+15,內容y+((i-1)*20),FONT_PRIO_AFRONT,0,道具數據[i-1],0,20);
	}else{
		圖片高 = 1*48+144;
		if((x-190) >(628+商城數據.X-x-65)) 圖片x=x-190;
		else  圖片x=x+35;
		圖片y=y-(圖片高/2);
		BOOL 判斷=FALSE;
		while(true){
			if(商城數據.Y > 圖片y-20){
				圖片y +=10;
				判斷=TRUE;
			}	
			if((商城數據.Y+386+30) < (圖片y+圖片高)){
				圖片y -=10;
				判斷=TRUE;
			}
			if(判斷) 判斷=FALSE;
			else break;
		}
		StockDispBuffer(圖片x+80,圖片y+50,層次,40171,1);
		int 高=48;
		StockDispBuffer(圖片x+80,圖片y+50+83,層次,40173,1);
		if(!商城數據.寵物動作結構) 商城數據.寵物動作結構 = MakeAnimDisp(圖片x+76,圖片y+80,形像,0);
		StockFontBufferSplit(圖片x+15,圖片y+100,2,0,臨時內容,0,20);
	}
}

void 購物車商品刪除(short 索引)
{

	商城數據.購物車.購物欄[索引].商品=0;
	商城數據.購物車.購物欄[索引].數量=0;
	商城數據.購物車.購物欄[索引].使用=FALSE;
	int i = 索引+1;
	if(i>14) return;
	for(i;i<15;i++){
		if(!商城數據.購物車.購物欄[i].使用) break;
		商城數據.購物車.購物欄[索引].商品 = 商城數據.購物車.購物欄[i].商品;
		商城數據.購物車.購物欄[索引].數量 = 商城數據.購物車.購物欄[i].數量;
		商城數據.購物車.購物欄[索引].使用=TRUE;
		商城數據.購物車.購物欄[i].商品=0;
		商城數據.購物車.購物欄[i].數量=0;
		商城數據.購物車.購物欄[i].使用=FALSE;
		索引 = i;
	}
}

void 商城文件讀取(char * 路徑,商城文件_ *商城)
{
	FILE *fp;
	fopen_s(&fp,路徑,"rb");	
	if( fp == NULL )
	{
		商城->MD5碼[0]=NULL;
		商城->商城數據=NULL;
		return;
	}
	int size = getfilesize(fp);
	char *臨時 = (char*)malloc(size);
	fread(臨時,1,size,fp);
	fclose(fp);
	商城->商城數據 = (char*)malloc(size-34+1);
	memset(商城->商城數據,0,size-34+1);
	memset(商城->MD5碼,0,64);
	memcpy_s(商城->MD5碼,34,臨時,34);
	memcpy_s(商城->商城數據,size-34,臨時+34,size-34);
	TEA解密((long*)商城->商城數據,((size-34)/4),(long*)_KEY_);
	free(臨時);
}


void 商城文件保存(char * 路徑,商城文件_ *商城)
{
	FILE *fp;
	fopen_s(&fp,路徑,"wb");
	int length=strlen(商城->商城數據);
	int length1 = length%4?length+(4-length%4):length;
	char *臨時 = (char*)malloc(34+length1);
	memset(臨時,0,34+length1);
	memcpy_s(臨時,34,商城->MD5碼,34);
	memcpy_s((臨時+34),length,商城->商城數據,length);
#ifdef _VMP_
	TEA加密((long *)(臨時+34),(long)(length1/4),(long*)VMProtectDecryptStringA(_KEY_));
#else
	TEA加密((long *)(臨時+34),(long)(length1/4),(long*)_KEY_);
#endif
    fwrite(臨時, length1+34, 1, fp);
	free(臨時);
    fclose(fp);
}


void 商城初始化()
{
	商城文件讀取("./data/shop1.bin",&商城文件[0]);
	商城文件讀取("./data/shop2.bin",&商城文件[1]);
	商城文件讀取("./data/shop3.bin",&商城文件[2]);
	商城文件讀取("./data/shop4.bin",&商城文件[3]);
	商城文件讀取("./data/shop5.bin",&商城文件[4]);
}
#endif














