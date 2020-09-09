#define _SASQL_C_

#include "version.h"

#ifdef _SASQL//新添加

#include "main.h"
#include "sasql.h"
#include "util.h"
#include "md5.h"
#include <mysql/mysql.h>

MYSQL mysql;
MYSQL_RES *mysql_result;
MYSQL_ROW mysql_row;
MYSQL_FIELD *fields;

typedef struct tagConfig
{
    char    sql_IP[32]; 

		int     sql_Port; 
		
		char    sql_Port1[16];
		
    char    sql_ID[16];
    
    char    sql_PS[32];

    char    sql_DataBase[16];  

    char    sql_Table[16];    
    
    char    sql_LOCK[16];   
    
    char    sql_NAME[16];  
    
    char    sql_PASS[16];  
    
    int 		AutoReg;
    
    int 		uLoginDay;

		int 		openbackground;
}Config;

Config config;

static int readSqlConfig( char *path )
{
    char buf[255];
    FILE *fp;

    fp = fopen( path , "r" );
    if( fp == NULL ){ return -2; }

    while( fgets( buf , sizeof( buf ) , fp )){
        char command[255];
        char param[255];
        chop(buf);
        
        easyGetTokenFromString( buf , 1 , command , sizeof( command ));
        easyGetTokenFromString( buf , 2 , param , sizeof( param ));

        if( strcmp( command , "sql_IP" ) == 0 ){
            snprintf( config.sql_IP , sizeof( config.sql_IP) , param );
            printf("\n數據庫地址：  %s",config.sql_IP);
        } else if( strcmp( command , "sql_Port" ) == 0 ){
        		config.sql_Port = atoi( param );
            snprintf( config.sql_Port1 , sizeof( config.sql_Port1) , param );
				  	printf("\n數據庫端口：  %d",config.sql_Port);
        } else if( strcmp( command , "sql_ID" ) == 0 ){
            snprintf( config.sql_ID , sizeof( config.sql_ID) , param );
						printf("\n數據庫用戶：  %s",config.sql_ID);
        } else if( strcmp( command , "sql_PS" ) == 0 ){
            snprintf( config.sql_PS , sizeof( config.sql_PS) , param );
						printf("\n數據庫密碼：  %s",config.sql_PS);
        } else if( strcmp( command , "sql_DataBase" ) == 0 ){
            snprintf( config.sql_DataBase , sizeof( config.sql_DataBase) , param );
						printf("\n登陸數據庫名：%s",config.sql_DataBase);
        } else if( strcmp( command , "sql_Table" ) == 0 ){
            snprintf( config.sql_Table , sizeof( config.sql_Table) , param );
				  	printf("\n用戶信息錶名：  %s",config.sql_Table);
				} else if( strcmp( command , "sql_LOCK" ) == 0 ){
            snprintf( config.sql_LOCK , sizeof( config.sql_LOCK) , param );
				  	printf("\n用戶鎖定錶名：  %s",config.sql_LOCK);
				} else if( strcmp( command , "sql_NAME" ) == 0 ){
            snprintf( config.sql_NAME , sizeof( config.sql_NAME) , param );
				  	printf("\n賬號字段名稱：  %s",config.sql_NAME);
				} else if( strcmp( command , "sql_PASS" ) == 0 ){
            snprintf( config.sql_PASS , sizeof( config.sql_PASS) , param );
				  	printf("\n密碼字段名稱：  %s",config.sql_PASS);
				} else if( strcmp( command , "uLoginDay" ) == 0 ){
            config.uLoginDay = atoi( param );
				  	printf("\n禁止天數登陸：  %d", config.uLoginDay);
				} else if( strcmp( command , "openbackground" ) == 0 ){
        		config.openbackground = atoi( param );
        		if(config.openbackground == 1){
        			printf("\n後颱功能：    YES");
        		}else{
        			printf("\n後颱功能：    NO");
        		}
				} else if( strcmp( command , "AutoReg" ) == 0 ){
        		config.AutoReg = atoi( param );
        		if(config.AutoReg){
        			printf("\n開放自動注冊：YES");
        		}else{
        			printf("\n開放自動注冊：NO");
        		}
    		}
    }
    fclose(fp);
    return 0;
}

BOOL sasql_init( void )
{
		if( (mysql_init(&mysql) == NULL) & readSqlConfig("acserv.cf"))
		{
			  printf("\n數據庫初始化失敗！");
			  exit(1);
		    return FALSE;
		}
	
	  if( !mysql_real_connect( &mysql,
	          config.sql_IP,
	          config.sql_ID,//帳號
	          config.sql_PS,//密碼
	          config.sql_DataBase,//選擇的資料庫
	          config.sql_Port,
	          NULL,
	          0 ) )
		{
			printf("\n數據庫連接失敗！\n");
			return FALSE;
		}

		mysql_query(&mysql,"set names 'gbk'");
  	printf("\n數據庫連接成功！\n");
  	return TRUE;
}

int sasql_mysql_query( char *sqlstr )
{
	mysql_query(&mysql,"set names 'gbk'");
  return mysql_query(&mysql,sqlstr);
}

void sasql_close( void )
{
  mysql_close( &mysql );
}

BOOL sasql_ckeckStrint( char *str )
{
  int i;
  for(i=0;i<strlen(str);i++){
  	if((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && (str[i] < '0' || str[i] > '9') && (str[i] != '.') && (str[i] != '-')){
  		return FALSE;
  	}
  }
  return TRUE;
}

int sasql_query(char *nm, char *pas){
	
	char sqlstr[1024];
	if(sasql_ckeckStrint(nm) == FALSE){
		printf("異常字符的用戶名%s\n",nm);
	  return 3;
	}
	
	//sprintf(sqlstr,"select `%s`, `salt` from %s where %s=BINARY'%s'",config.sql_PASS, config.sql_Table,config.sql_NAME,nm);
	sprintf(sqlstr,"select `%s`,TO_DAYS( NOW( ) ) - TO_DAYS( LoginTime ) from %s where %s=BINARY'%s'",config.sql_PASS, config.sql_Table,config.sql_NAME,nm);
	
	if(!sasql_mysql_query(sqlstr)){
	  int num_row=0;
	  mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
		
	  if(num_row>0){
	  	char token[64];
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	strcpy(token, mysql_row[0]);
#ifdef _OLDPS_TO_MD5PS
			if(strlen(mysql_row[0])>16 && strlen(pas) <= 16){
				if(strcmp(MD5String(pas),token) == 0){
	  			return 1;
			  }else{
			  	printf("用戶%s密碼錯誤！\n",nm);
			  	return 2;
			  }
			}else if(strlen(pas)>16 && strlen(mysql_row[0]) <= 16){
				if(strcmp(MD5String(token),pas) == 0){
	  			return 1;
			  }else{
			  	printf("用戶%s密碼錯誤！\n",nm);
			  	return 2;
			  }
			}else{
				if(strcmp(pas,token) == 0){
	  			return 1;
			  }else{
			  //	printf("用戶%s密碼錯誤！\n",nm);
			  	return 2;
			  }
			}
#else
	  	if(strcmp(pas,token) == 0){
	  		return 1;
		  }else{
		  	printf("用戶%s密碼錯誤！\n",nm);
		  	return 2;
		  }
#endif
	  }else{
	  	printf("用戶%s未注冊！\n",nm);
	  	return 3;
	  }
	}else{
		printf("\n數據庫查找失敗！\n");
		printf("重新連接數據庫...");
		sasql_close();
		sasql_init();
		printf("完成\n");
		return 0;
	}
}


#ifdef _SQL_BACKGROUND
BOOL sasql_online( char *ID, char *NM, char *IP, char *MAC, int flag )
{
	if(config.openbackground == 1){
		if(ID!=NULL){
			if(sasql_ckeckStrint(ID) == FALSE){
				printf("異常字符的用戶名%s\n",ID);
			  return TRUE;
			}
		}
		
		char sqlstr[256];
		if(flag==0)
			sprintf(sqlstr,"update %s set Online=0 where %s=BINARY'%s'", config.sql_Table, config.sql_NAME, ID);
		else if(flag==1)
			sprintf(sqlstr,"update %s set LoginTime=NOW(), IP='%s', Online=0 where %s=BINARY'%s'", config.sql_Table, IP, config.sql_NAME, ID);
		else if(flag==2)
			sprintf(sqlstr,"update %s set LoginTime=NOW(), OnlineName='%s', Online=1, Path='char/0x%x'where %s=BINARY'%s'", config.sql_Table, NM, getHash(ID) & 0xff, config.sql_NAME, ID);
		else if(flag==3)
			sprintf(sqlstr,"update %s set Online=0", config.sql_Table);
		if(!sasql_mysql_query(sqlstr)){
			return TRUE;
		}
		printf("\n更新數據庫失敗%s\n", sqlstr);
	}
	return TRUE;
}
#endif

#ifdef _SQL_REGISTER
BOOL sasql_register(char *id, char *ps)
{
	char sqlstr[256];
	if(config.AutoReg!=1)return FALSE;
		
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符的用戶名%s\n",id);
		 return FALSE;
	}	
	if(sasql_ckeckStrint(ps) == FALSE){
		printf("異常字符的遊戲密碼%s\n",ps);
		 return FALSE;
	}
		
		
#ifdef _OLDPS_TO_MD5PS
	sprintf(sqlstr,"INSERT INTO %s (%s,%s,RegTime,Path) VALUES (BINARY'%s','%s',NOW(),'char/0x%x')",config.sql_Table, config.sql_NAME, config.sql_PASS, id, MD5String(ps), getHash(id) & 0xff);
#else
	sprintf(sqlstr,"INSERT INTO %s (%s,%s,RegTime,Path) VALUES (BINARY'%s','%s',NOW(),'char/0x%x')",config.sql_Table, config.sql_NAME, config.sql_PASS, id, ps, getHash(id) & 0xff);
#endif

	if(!sasql_mysql_query(sqlstr)){
		printf("\n新用戶注冊成功！\n");
		return TRUE;
	}
	printf("\n新用戶注冊失敗！\n");
	return FALSE;
}
#endif


BOOL sasql_chehk_lock( char *idip )
{
	if(sasql_ckeckStrint(idip) == FALSE){
		printf("異常字符%s\n",idip);
		 return FALSE;
	}	
	char sqlstr[256];
	sprintf(sqlstr,"select * from `%s` where Name='%s'", config.sql_LOCK, idip);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
	
	  if(num_row>0){
			return TRUE;
		}
	}
	return FALSE;
}

BOOL sasql_add_lock( char *idip )
{
	if(sasql_ckeckStrint(idip) == FALSE){
		printf("異常字符%s\n",idip);
		 return FALSE;
	}	
	char sqlstr[256];
	sprintf(sqlstr,"INSERT INTO `%s` (Name) VALUES (BINARY'%s')", config.sql_LOCK, idip);
	if(!sasql_mysql_query(sqlstr)){
			printf("\n添加鎖定%s成功！\n",idip);
			return TRUE;
	}
	return FALSE;
}

BOOL sasql_del_lock( char *idip )
{
	if(sasql_ckeckStrint(idip) == FALSE){
		printf("異常字符%s\n",idip);
		return FALSE;
	}	
	char sqlstr[256];
	sprintf(sqlstr,"delete from `%s` where Name=BINARY'%s'", config.sql_LOCK, idip);
	if(!sasql_mysql_query(sqlstr)){
		printf("\n解除鎖定%s成功！\n",idip);
		return TRUE;
	}
	return FALSE;
}

#ifdef _NEW_VIP_SHOP
int sasql_query_point( char *name )
{
	if(sasql_ckeckStrint(name) == FALSE){
		printf("異常字符%s\n",name);
		return -1;
	}	
	
	char sqlstr[256];
	sprintf(sqlstr,"select VipPoint from `%s` where %s=BINARY'%s'", config.sql_Table, config.sql_NAME, name);
	
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
		
	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	return atoi(mysql_row[0]);
		}
	}
	return -1;
}


BOOL sasql_add_vippoint( char *ID, int point )
{
	if(sasql_ckeckStrint(ID) == FALSE){
		printf("異常字符%s\n",ID);
		return -1;
	}	
	
	char sqlstr[256];
	sprintf(sqlstr,"select VipPoint from %s where %s=BINARY'%s'",config.sql_Table,config.sql_NAME,ID);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
		mysql_result=mysql_store_result(&mysql);
		num_row=mysql_num_rows(mysql_result);

		if(num_row>0){
			mysql_row=mysql_fetch_row(mysql_result);
			point+=atoi(mysql_row[0]);
			if(point < 0){
				printf("%s會員點數小於0\n",ID);
				return -1;
			}
			sprintf(sqlstr,"update %s set VipPoint=%d where %s=BINARY'%s'", config.sql_Table, point,config.sql_NAME, ID);	
			if(!sasql_mysql_query(sqlstr)){
				printf("用戶%s當前會員點%d！\n",ID,point);
				return point;
			}
		}
	}
	printf("修改%s會員點數失敗！\n",ID);
	return -1;
}

BOOL sasql_add_Paypoint( char *ID, int point )
{
	if(sasql_ckeckStrint(ID) == FALSE){
		printf("異常字符%s\n",ID);
		return -1;
	}	
	
	char sqlstr[256];
	sprintf(sqlstr,"select PayPoint from %s where %s=BINARY'%s'",config.sql_Table,config.sql_NAME,ID);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
		mysql_result=mysql_store_result(&mysql);
		num_row=mysql_num_rows(mysql_result);

		if(num_row>0){
			mysql_row=mysql_fetch_row(mysql_result);
			point+=atoi(mysql_row[0]);
			if(point < 0){
				printf("%s充值點數小於0\n",ID);
				return -1;
			}
			sprintf(sqlstr,"update %s set PayPoint=%d where %s=BINARY'%s'", config.sql_Table, point,config.sql_NAME, ID);	
			if(!sasql_mysql_query(sqlstr)){
				printf("用戶%s當前充值點%d！\n",ID,point);
				return point;
			}
		}
	}
	printf("修改%s充值點數失敗！\n",ID);
	return -1;
}


#endif

#ifdef _ITEM_PET_LOCKED
char *sasql_ItemPetLocked( char *id, char *safepasswd )
{
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符%s\n",id);
		return "無法解鎖，請與本服管理員聯係！";
	}	
	if(sasql_ckeckStrint(safepasswd) == FALSE){
		printf("異常字符%s\n",safepasswd);
		return "無法解鎖，請與本服管理員聯係！";
	}	
	char sqlstr[256];
	sprintf(sqlstr,"select SafePasswd from `%s` where %s=BINARY'%s'", config.sql_Table, config.sql_NAME, id);
	
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);

	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	if( mysql_row[0] != NULL && strlen(mysql_row[0])>0){
		  	if(strcmp(safepasswd, mysql_row[0])==0){
		  		return "安全鎖已經成功解鎖！";
		  	}else{
		  		return "密碼錯誤，安全鎖無法解開！";
		  	}
		  }else{
		  	return "您還未設置安全鎖解鎖密碼，為瞭確保安全，請輸入一次六位以上密碼做為安全鎖密碼並勞勞記住！";
		  }
		}
	}
	return "無法解鎖，請與本服管理員聯係！";
}

char *sasql_ItemPetLocked_Passwd( char *id, char *safepasswd )
{
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符%s\n",id);
		return "安全密碼修改失敗，請與本服管理員聯係！";
	}
	if(sasql_ckeckStrint(safepasswd) == FALSE){
		printf("異常字符%s\n",safepasswd);
		return "安全密碼修改失敗，請與本服管理員聯係！";
	}
	char sqlstr[256];
	sprintf(sqlstr,"select safepasswd from %s where %s=BINARY'%s'", config.sql_Table,config.sql_NAME, id);
	
	if(!sasql_mysql_query(sqlstr)){
	  int num_row=0;
	  mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	if( mysql_row[0] != NULL && strlen(mysql_row[0])>0){
		  	return "安全密碼已存在,無法再進行修改！";
			}else{
				char sqlstr[256];
				sprintf(sqlstr,"update %s set SafePasswd=BINARY'%s' where %s=BINARY'%s'", config.sql_Table, safepasswd, config.sql_NAME, id);	
				
				if(!sasql_mysql_query(sqlstr)){
					return "安全密碼修改成功，請妥善保管你的安全密碼！";
				}
				return "安全密碼修改失敗，請與本服管理員聯係！";
		  }
	  }else{
	  	return "賬號不存在安全密碼已存在！";
	  }
	}else{
		printf("\n數據庫查找失敗！\n");
		printf("重新連接數據庫...");
		sasql_close();
		sasql_init();
		printf("完成\n");
		return "安全密碼修改失敗，請與本服管理員聯係！";
	}
}

int sasql_ItemPetLocked_Char( char *id, char *safepasswd )
{
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符%s\n",id);
		return 0;
	}	
	if(sasql_ckeckStrint(safepasswd) == FALSE){
		printf("異常字符%s\n",safepasswd);
		return 0;
	}	
	char sqlstr[256];
	sprintf(sqlstr,"select safepasswd from %s where %s=BINARY'%s'", config.sql_Table,config.sql_NAME, id);
	
	if(!sasql_mysql_query(sqlstr)){
	  int num_row=0;
	  mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	if( mysql_row[0] != NULL && strlen(mysql_row[0])>0){
		  	if(strcmp(safepasswd,mysql_row[0]) == 0){
		  		return 1;
			  }else{
			  //	printf("用戶%s安全密碼錯誤！\n",id);
			  	return -1;
			  }
			}else{
		  	return 0;
		  }
	  }else{
	  	printf("用戶%s未注冊！\n",id);
	  	return -1;
	  }
	}else{
		printf("\n數據庫查找失敗！\n");
		printf("重新連接數據庫...");
		sasql_close();
		sasql_init();
		printf("完成\n");
		return -1;
	}
}
#endif

#ifdef _ONLINE_COST
char *sasql_OnlineCost( char *id, char *costpasswd, int fmindex, char *fmname)
{
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符%s\n",id);
		return "充值失敗，請與本服管理員聯係！";
	}	
	if(sasql_ckeckStrint(costpasswd) == FALSE){
		printf("異常字符%s\n",costpasswd);
		return "充值失敗，請與本服管理員聯係！";
	}	
	char sqlstr[256];
	static char token[256]="";
	sprintf(sqlstr,"select `CostVal`, `PayVal`, `check` from `OnlineCost` where CostPasswd = BINARY'%s'", costpasswd);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	if(atoi(mysql_row[2]) == 1){
			 	int costval = atoi(mysql_row[0]);
			 	int payval = atoi(mysql_row[1]);
			  int vippoint = sasql_add_vippoint(id, costval);
			  int paypoint = sasql_add_Paypoint(id, payval);
		  	sprintf(sqlstr,"update OnlineCost set cdkey=BINARY'%s', CostTime=NOW(), `check`=0  where CostPasswd=BINARY'%s'", id, costpasswd);	
				if(!sasql_mysql_query(sqlstr)){
					log("充值卡號%s已充值！\n",costpasswd);
				}
				addFmPayPoint(fmindex, fmname, payval);
				sprintf(token, "充值已成功，充值卡麵值為%d，充值卡點數為%d，您當前會員點數共%d，充值充分共%d", payval, costval, vippoint, paypoint);
		  	return token;
		  }else{
		  	return "該充值卡已使用過，請勿重復使用！";
		  }
		}else{
			return "充值失敗，該充值卡密碼不正確！";
		}
	}
	return "充值失敗，請與本服管理員聯係！";
}

char *sasql_TransOnlineCost()
{
	char sqlstr[256];
	static char token[256]="";
	sprintf(sqlstr,"select `PayVal`, `cdkey` from `OnlineCost` where `check` = 0");
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
	  if(num_row>0){
	  	while((mysql_row = mysql_fetch_row(mysql_result))){
	  		int paycost = atoi(mysql_row[0]);
			 	sprintf(sqlstr,"update %s set PayPoint=PayPoint + %d where %s=BINARY'%s'", config.sql_Table, paycost,config.sql_NAME, mysql_row[1]);	
				if(!sasql_mysql_query(sqlstr)){
					printf("用戶%s當前充值點增加%d！\n",mysql_row[1],paycost);
				}
			}
		}else{
			return "查找失敗";
		}
	}
	return "充值失敗，請與本服管理員聯係！";
}

void sasql_OnlineCost_add( int cost, int num, int point)
{
	char sqlstr[256];
	char CostPasswd[32];
	memset( CostPasswd, 0, sizeof( CostPasswd ) );
	int i, j, k=0;
	for(i=0;i<num;i++){
		for(j=0;j<16;j++){
			if(rand() % 2==0){
				CostPasswd[j]=(rand() % 26) + 65;
			}else{
				CostPasswd[j]=(rand() % 10) + 48;
			}
		}
		sprintf(sqlstr,"INSERT INTO OnlineCost (CostPasswd, CostVal, PayVal) VALUES (BINARY'%s', %d, %d)", CostPasswd, cost, point);
		if(!sasql_mysql_query(sqlstr)){
			k++;
		}else{
			continue;
		}
	}
	printf("成功添加%d條麵值%d的充值卡\n", k, cost);
	return ;
}

#endif


#ifdef _SQL_BUY_FUNC
char *sasql_OnlineBuy( char *id, char *costpasswd )
{
	if(sasql_ckeckStrint(id) == FALSE){
		printf("異常字符%s\n",id);
		return "提貨失敗，請與本服管理員聯係！";
	}	
	if(sasql_ckeckStrint(costpasswd) == FALSE){
		printf("異常字符%s\n",costpasswd);
		return "提貨失敗，請與本服管理員聯係！";
	}	
	char sqlstr[256];
	static char token[256]="";
	sprintf(sqlstr,"select `CostStr`, `check` from `OnlineBuy` where CostPasswd = BINARY'%s'", costpasswd);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
		
	  if(num_row>0){
	  	mysql_row=mysql_fetch_row(mysql_result);
	  	if(atoi(mysql_row[1]) == 1){
			 	char *coststr = mysql_row[0];
#ifdef _SQL_BUY_FUNC_ONE_CDKEY
			 	if(costpasswd[0]=='1'){
					sprintf(sqlstr,"select count(*) from OnlineBuy where `CostStr`='%s' and `cdkey`=BINARY'%s'", coststr, id);
					if(!sasql_mysql_query(sqlstr)){
						int num_row=0;
						mysql_free_result(mysql_result);
						mysql_result=mysql_store_result(&mysql);
						num_row=mysql_num_rows(mysql_result);
						if(num_row>0){
							mysql_row=mysql_fetch_row(mysql_result);
							if(atoi(mysql_row[0])>0){
								return "相同類型的道具卡密每個帳號僅能領取一次！";
							}
						}
					}
			 	}
#endif

		  	sprintf(sqlstr,"update OnlineBuy set cdkey=BINARY'%s', CostTime=NOW(), `check`=0  where CostPasswd=BINARY'%s'", id, costpasswd);	
				if(!sasql_mysql_query(sqlstr)){
					log("提貨卡號%s已提取！\n",costpasswd);
				}
				sprintf(token, "%c|%s", costpasswd[0], coststr);
				
		  	return token;
		  }else{
		  	return "該提貨卡已使用過，請勿重復使用！";
		  }
		}else{
			return "提貨失敗，該提貨卡密碼不正確！";
		}
	}
	return "提貨失敗，請與本服管理員聯係！";
}

void sasql_OnlineBuy_add( char *coststr, int type, int num )
{
	char sqlstr[256];
	char CostPasswd[32];
	int i, j, k=0;
	for(i=0;i<num;i++){
		memset( CostPasswd, 0, sizeof( CostPasswd ) );
		CostPasswd[0]='0' + type;
		for(j=1;j<16;j++){
			if(rand() % 2==0){
				CostPasswd[j]=(rand() % 26) + 65;
			}else{
				CostPasswd[j]=(rand() % 10) + 48;
			}
		}
		sprintf(sqlstr,"INSERT INTO OnlineBuy (CostPasswd, CostStr) VALUES (BINARY'%s', '%s')", CostPasswd, coststr);
		if(!sasql_mysql_query(sqlstr)){
			k++;
		}else{
			break;
		}
	}
	if(type <= 0){
		printf("成功添加%d條寵物提貨卡\n", k);
	}else if(type == 1){
		printf("成功添加%d條物品提貨卡\n", k);
	}else if(type >= 2){
		printf("成功添加%d條石幣提貨卡\n", k);
	}
	return ;
}

#endif


int sasql_onlinenum( char *MAC )
{
	char sqlstr[256];
	sprintf(sqlstr,"select count(*) from %s where Online=1 and MAC='%s'",config.sql_Table,MAC);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
		mysql_result=mysql_store_result(&mysql);
		num_row=mysql_num_rows(mysql_result);
		if(num_row>0){
			mysql_row=mysql_fetch_row(mysql_result);
			return atoi(mysql_row[0]);
		}
	}
	return 0;
}

#ifdef _FORMULATE_AUTO_PK
BOOL sasql_add_FormulateAutoPk( char *ID, int point )
{
	if(sasql_ckeckStrint(ID) == FALSE){
		printf("異常字符%s\n",ID);
		return -1;
	}
	
	char sqlstr[256];
	sprintf(sqlstr,"select PKPoint from %s where %s=BINARY'%s'",config.sql_Table,config.sql_NAME,ID);
	if(!sasql_mysql_query(sqlstr)){
		int num_row=0;
		mysql_free_result(mysql_result);
		mysql_result=mysql_store_result(&mysql);
		num_row=mysql_num_rows(mysql_result);
		if(num_row>0){
			mysql_row=mysql_fetch_row(mysql_result);
			point+=atoi(mysql_row[0]);
			if(point < 0){
				return -1;
			}
			sprintf(sqlstr,"update %s set PKPoint=%d where %s=BINARY'%s'", config.sql_Table, point,config.sql_NAME, ID);	
			if(!sasql_mysql_query(sqlstr)){
				return point;
			}
		}
	}
	return -1;
}
#endif

#ifdef _OLDPS_TO_MD5PS
void sasql_OldpsToMd5ps()
{
	char sqlstr[256];
	sprintf(sqlstr,"select %s, %s from %s",config.sql_NAME, config.sql_PASS, config.sql_Table);
	if(!sasql_mysql_query(sqlstr)){
		mysql_free_result(mysql_result);
		mysql_result=mysql_store_result(&mysql);
		printf("      轉換賬號             原密碼               轉換MD5碼\n");
		while((mysql_row = mysql_fetch_row(mysql_result))){
			char * name = mysql_row[0];
			char * ps = mysql_row[1];                     
	    if(strlen(ps)<=16) {                        
	    	sprintf(sqlstr,"update %s set %s=BINARY'%s' where %s=BINARY'%s'", config.sql_Table, config.sql_PASS, MD5String(ps),config.sql_NAME, name);	
				if(!sasql_mysql_query(sqlstr)){
					printf("%16s  %16s    %32s\n", name, ps, MD5String(ps));
				}
	    }
	  }
	}
}
#endif


#ifdef _CHARADATA_SAVE_SQL
void sasql_charadata_Save(char *id, char* table, char *data, int saveindex, int flag)
{
	if(strlen(data)==0)return;
	
	char sqlstr[1024*16];
	
	if(flag==INSERT){
		sprintf(sqlstr, "INSERT INTO %s VALUES %s" , table, data);
	}else if(flag==SELECT){
	}else if(flag==UPDATE){
		sprintf(sqlstr, "UPDATE %s set %s WHERE CHAR_CDKEY=BINARY'%s' and CHAR_SAVEINDEX=%d" , table, data, id, saveindex);
	}else if(flag==DELETE){
		sprintf(sqlstr, "DELETE FROM %s WHERE CHAR_CDKEY=BINARY'%s' and CHAR_SAVEINDEX=%d" , table, id, saveindex);
	}
	
	if(!mysql_query(&mysql,sqlstr)){
		if(flag==DELETE){
			sasql_charadata_Save(id, table, data, saveindex, INSERT);
		}
		return;
	}else{
		printf(table);
		if(flag==INSERT){
			printf(" INSERT error\n");
		}else if(flag==SELECT){
			printf(" SELECT error\n");
		}else if(flag==UPDATE){
			printf(" UPDATE error\n");
		}else if(flag==DELETE){
			printf(" DELETE error\n");
		}
	}
}

#endif

void sasql_CleanCdkey(int date)
{
	char sqlstr[256];

	sprintf(sqlstr, "select `%s` from `%s` where TO_DAYS( NOW( ) ) - TO_DAYS( LoginTime ) > %d", config.sql_NAME, config.sql_Table, date);

	if(!mysql_query(&mysql,sqlstr)){
	  int num_row=0;
	  int GroupNum=0;
	  int ServerMaxNum=0;
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
		mysql_free_result(mysql_result);
		if(num_row > 0){
		  while((mysql_row = mysql_fetch_row(mysql_result))){
		  	char tmp[256] = "";
				char charId[256];

				strcpy( charId, mysql_row[0] );

				int hash = 0;
				int i;
				for( i=0; i<strlen(charId); i++) {
					hash += (int)charId[i];
					hash = hash % 256;
				}

		  	sprintf(tmp, "rm char/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm char_sleep/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm log/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm mail/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	
		  	
		  }
		}
	}
	
	sprintf(sqlstr, "DELETE FROM `%s` WHERE TO_DAYS( NOW( ) ) - TO_DAYS( LoginTime ) > %d" , config.sql_Table, date);
	mysql_query(&mysql,sqlstr);
	printf("完成\n");
	return;
}

void sasql_CleanLockCdkey()
{
	char sqlstr[256];

	sprintf(sqlstr, "select `%s` from `%s` where `%s` LIKE '%!%'", config.sql_NAME, config.sql_Table, config.sql_PASS);

	if(!mysql_query(&mysql,sqlstr)){
	  int num_row=0;
	  int GroupNum=0;
	  int ServerMaxNum=0;
	  mysql_result=mysql_store_result(&mysql);
	  num_row=mysql_num_rows(mysql_result);
		mysql_free_result(mysql_result);
		if(num_row > 0){
		  while((mysql_row = mysql_fetch_row(mysql_result))){
		  	char tmp[256] = "";
				char charId[256];

				strcpy( charId, mysql_row[0] );

				int hash = 0;
				int i;
				for( i=0; i<strlen(charId); i++) {
					hash += (int)charId[i];
					hash = hash % 256;
				}

		  	sprintf(tmp, "rm char/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm char_sleep/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm log/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	sprintf(tmp, "rm mail/0x%x/%s.* >& /dev/null\n", hash, charId);
		  	system(tmp);
		  	
		  	
		  }
		}
	}
	
	sprintf(sqlstr, "DELETE FROM `%s` WHERE `%s` LIKE '%!%'", config.sql_Table, config.sql_PASS);
	mysql_query(&mysql,sqlstr);
	printf("完成\n");
	return;
}

BOOL sasql_craete_userinfo( void )
{
	return FALSE;
}

BOOL sasql_craete_lock( void )
{
	return FALSE;
}

#endif
