#ifndef _NETMAIN_H_
#define _NETMAIN_H_

#include "../systeminc/version.h"

struct gameserver
{
	char used;
	char ipaddr[127];
	char port[64];
	char name[64];
#ifdef _SHOW_COUNT						// WON ADD 秀服務器流量
	char count[64];
#endif
#ifdef _SHOWIPSLEEP_
	int delay;
#endif
};

struct gamegroup{
	char	used;
	char	num;
	char	startindex;
	char	name[61];
};

#define SUCCESSFULSTR	"successful"        // ??????????
#define FAILEDSTR		"failed" 
#define OKSTR           "ok"
#define CANCLE          "cancle"

#define TIMEOUT (600*1000)                   //  ????????????????????????

//#define NETBUFSIZ (1024*16)
//#define NETBUFSIZ (1024*8)
#define NETBUFSIZ (1024*64) // Robin 2004.05.04

extern char *net_writebuf;
extern char *net_readbuf;
extern int net_readbuflen;
extern int net_writebuflen;

extern unsigned int sockfd;
extern int server_choosed;
extern int init_net;

extern struct gameserver gmsv[];

#ifdef _LOG_MSG
extern char debugLogFileName[];
#endif

typedef int                 BOOL;
extern BOOL disconnectServerFlag;
extern BOOL oldDisconnectServerFlag;


int getServerInfo( int, char *, short * );


void networkLoop(void);
void networkMycharWalk( int gx , int gy , char *direction );

int initNet(void);
void cleanupNetwork( void );
int appendReadBuf(  char *buf , int size );
int appendWriteBuf( int index , char *buf , int size );
int shiftReadBuf(  int size );
int shiftWriteBuf( int size );
int getLineFromReadBuf( char *output  , int maxlen );
int sendn( unsigned int s , char *buffer , int len );



int getServerInfoByServerName( char *servername , char *hostname , short *port );


// ????????
#define NET_ERRMSG_SOCKLIBERROR		"網路尚未準備好。"
#define NET_ERRMSG_BADNAME          "服務器名稱不正確。"
#define NET_ERRMSG_SOCKETERROR      "無法執行socket的TCP。"
#define NET_ERRMSG_NOTGETADDR		"網絡故障,請聯係客服。"
#define NET_ERRMSG_NOTCONNECT_S		"無法開始進行服務器的連接。"
#define NET_ERRMSG_NOTCONNECT		"服務器尚未開啓。請嘗試其他連綫"
#define NET_ERRMSG_CONNECTTIMEOUT	"服務器連接時間已到。"
#define NET_ERRMSG_LOGINTIMEOUT		"登入處理時間已到。"
#define NET_ERRMSG_CHARLISTTIMEOUT	"讀取人物錶時間已到。"
#define NET_ERRMSG_LOGOUTTIMEOUT	"登齣處理時間已到。"
#define NET_ERRMSG_LOGINFAIL		"無法登入服務器。"
#define NET_ERRMSG_CREATECHARTIMEOUT	"人物製作時間已到。"
#define NET_ERRMSG_DELETECHARTIMEOUT	"人物削除時間已到。"
#define NET_ERRMSG_VERSIONERROR		"您當前的版本太舊，請使用更新器更新遊戲後登陸！"

#define GAMESTATE_ERRMSG_LOGOUTDENY	"服務器拒絕處理登齣。"


#endif
