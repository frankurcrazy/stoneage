#include "version.h"

#include <string.h>
#include "common.h"
#include "char.h"
#include "char_base.h"
#include "object.h"
#include "buf.h"
#include "util.h"
#include "configfile.h"
#include "readmap.h"
#include "map_warppoint.h"
#include "autil.h"
#ifdef _MAP_WARPPOINT
#define MAP_MAXWARPPOINT 6000

typedef struct _tagMAPwarpPoints{
	int use;
	int ofloor;
	int ox;
	int oy;

	int floor;
	int x;
	int y;
	int type;
}_MAPwarpPoints;

_MAPwarpPoints *MapWarppoint;
static int MapWarpPoints=0;
char PointType[3][256]={ "NONE", "FREE", "ERROR"};

char Filename[256];
int MAPPOINT_InitMapWarpPoint()
{
	MapWarppoint = ( _MAPwarpPoints *)calloc( 1, sizeof( struct _tagMAPwarpPoints)*MAP_MAXWARPPOINT);
	if( MapWarppoint == NULL ) return 0;

	sprintf(Filename, "%s/mapwarp.txt", getMapdir());
	MAPPOINT_resetMapWarpPoint( 0);
	return MAP_MAXWARPPOINT;
}
/*
void MAPPOINT_checkMapWarpPoint( int floor, int x, int y)
{
	OBJECT	object;

	for( object = MAP_getTopObj(fl,x,y) ; object ;
			object = NEXT_OBJECT(object) ){
		int o = GET_OBJINDEX(object);
		if( OBJECT_getType(o) == OBJTYPE_WARPPOINT){
			if( !MAPPOINT_CHECKINDEX( OBJECT_getIndex( o)) ) continue;
			if( OBJECT_getchartype( o) != event ) continue;
			MAPPOINT_MapWarpHandle( charaindex, OBJECT_getIndex( o), fl, x, y );
			found = TRUE;
			break;
		}

}
*/
void MAPPOINT_resetMapWarpPoint( int flg)
{
	int i;
	if( MapWarppoint == NULL ) return;
	for( i=0; i<MAP_MAXWARPPOINT; i++){
		MapWarppoint[i].use = 0;
		MapWarppoint[i].floor = -1;
	}

	if( flg == 1 ){
		int objindex;
		int objmaxnum = OBJECT_getNum();
		for( objindex=0; objindex<objmaxnum; objindex++)	{
			if( CHECKOBJECT( objindex ) == FALSE ) continue;
			if( OBJECT_getType( objindex) != OBJTYPE_WARPPOINT )continue;
			CHAR_ObjectDelete( objindex);	
		}
	}
}

int MAPPOINT_creatMapWarpObj( int pointindex, char *buf, int objtype)
{
	int     objindex;
	Object  obj;
	char buf1[256];
	obj.index= pointindex;
	memset( obj.objname, 0, sizeof( obj.objname));
	if( getStringFromIndexWithDelim( buf, ",", 1, buf1, sizeof(buf1)) ==FALSE ){
		return -1;//原點
	}
	obj.floor   = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 2, buf1, sizeof(buf1)) ==FALSE ){
		return -1;//原點
	}
	obj.x = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 3, buf1, sizeof(buf1)) ==FALSE ){
		return -1;//原點
	}
	obj.y = atoi( buf1);
	obj.type = OBJTYPE_WARPPOINT;
	obj.chartype = objtype;
	obj.dir		= 0;
	objindex = initObjectOne( &obj );
	if( objindex == -1 ){
		//andy_log
		//print( " creatMapWarpObj() initObjectOne err !!\n");
		return -1;
	}
	return objindex;
}

BOOL MAPPOINT_CHECKINDEX( int ps)
{
	if( ps < 0 || ps >= MAP_MAXWARPPOINT )
		return FALSE;

	return MapWarppoint[ ps].use;
}

int MAPPOINT_getMPointEVType( int ps)
{
	if( !MAPPOINT_CHECKINDEX( ps) )
		return -1;
	return MapWarppoint[ ps].type;
}

int  MAPPOINT_setMapWarpFrom( int ps, char *buf)
{
	char buf1[256];

	if( MAPPOINT_CHECKINDEX( ps) ){
		print(" 放置傳送點從 %s 獲得!!\n", buf);
		return -1;
	}

	memset( buf1, 0, sizeof( buf1));
	if( getStringFromIndexWithDelim( buf, ",", 1, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].ofloor = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 2, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].ox = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 3, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].oy = atoi( buf1);
	return 1;
}

int  MAPPOINT_setMapWarpGoal( int ps, char *buf)
{
	char buf1[256];
	if( MAPPOINT_CHECKINDEX( ps) ){
		print(" 放置傳送點獲得 :%s!!\n", buf);
		return -1;
	}

	memset( buf1, 0, sizeof( buf1));
	if( getStringFromIndexWithDelim( buf, ",", 1, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].floor = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 2, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].x = atoi( buf1);
	if( getStringFromIndexWithDelim( buf, ",", 3, buf1, sizeof(buf1)) ==FALSE ) return -1;//原點
	MapWarppoint[ps].y = atoi( buf1);
	return 1;
}

int MAPPOINT_getMapWarpGoal( int ps, int ofl, int ox, int oy, int *fl, int *x, int *y)
{
	if( !MAPPOINT_CHECKINDEX( ps) ){
		print("獲取傳送點PS:%d 錯誤!!\n", ps);
		return -1;
	}

	if( MapWarppoint[ps].ofloor != ofl ||
		MapWarppoint[ps].ox != ox || MapWarppoint[ps].oy != oy ){
		print( "不正常傳送點: 舊的有問題傳送點 %d %d %d !!\n" , ofl,ox,oy );
		return -1;
	}
	//可加判斷條件
	if( MAP_IsValidCoordinate( MapWarppoint[ps].floor, MapWarppoint[ps].x, MapWarppoint[ps].y)== FALSE ){
		print( "不正常傳送點:有問題 %d %d %d !!\n" ,
			MapWarppoint[ps].floor,MapWarppoint[ps].x, MapWarppoint[ps].y );
		return -1;
	}
	*fl = MapWarppoint[ps].floor;
	*x  = MapWarppoint[ps].x;
	*y  = MapWarppoint[ps].y;
	return 1;
}

int MAPPOINT_loadMapWarpPoint( )
{
	int i=0, ps=0, objtype;
	FILE *fp=NULL;
	char buf[256], buf1[256];

	if( Filename == NULL ) return -1;
#ifdef _CRYPTO_DATA		
	char realopfile[256];
	BOOL crypto = FALSE;
	sprintf(realopfile, "%s.allblues", Filename);
	fp = fopen( realopfile, "r");
	if( fp != NULL ){
		crypto = TRUE;
	}else
#endif
{
	fp = fopen( Filename, "r");
}
	if( fp == NULL ){
		return 0;
	}
	while( fgets( buf, sizeof( buf)-1, fp) != NULL ){
#ifdef _CRYPTO_DATA		
		if(crypto==TRUE){
			DecryptKey(buf);
		}
#endif
		if( strstr( buf, "#") != 0 ) continue;
		if( getStringFromIndexWithDelim( buf, ":", 1, buf1, sizeof(buf1)) ==FALSE )
			continue;
		for( i=0; i<arraysizeof( PointType); i++)	{
			if( !strcmp( buf1, PointType[i]) )break;
		}
		if( i >= arraysizeof( PointType) ){
			print(" 1.map 傳送點錯誤 %s \n", buf);
			continue;
		}
		MapWarppoint[ps].type = i;
		if( getStringFromIndexWithDelim( buf, ":", 2, buf1, sizeof(buf1)) ==FALSE ) continue;
		objtype = CHAR_EVENT_WARP;
		if( !strcmp( buf1, "NULL")){
		}else if( !strcmp( buf1, "M")){
			objtype = CHAR_EVENT_WARP_MORNING;
		}else if( !strcmp( buf1, "N")){
			objtype = CHAR_EVENT_WARP_NIGHT;
		}else if( !strcmp( buf1, "A")){
			objtype = CHAR_EVENT_WARP_NOON;
		}
		memset( buf1, 0, sizeof(buf1));
		if( getStringFromIndexWithDelim( buf, ":", 3, buf1, sizeof(buf1)) ==FALSE )continue;

		if( MAPPOINT_setMapWarpFrom( ps, buf1) == -1){
			print(" 2-1.map 傳送點錯誤 %s [%s] \n", buf, buf1);
			continue;
		}
		if( MAPPOINT_creatMapWarpObj( ps, buf1, objtype) == -1 ){
			print(" 2.map 傳送點錯誤 %s [%s] \n", buf, buf1);
			continue;
		}
		memset( buf1, 0, sizeof(buf1));
		if( getStringFromIndexWithDelim( buf, ":", 4, buf1, sizeof(buf1)) ==FALSE ){
			print(" 3.map 傳送點錯誤 %s [%s] \n", buf, buf1);
			continue;
		}
		if( MAPPOINT_setMapWarpGoal( ps, buf1) == -1 ){
			print(" 4.map 傳送點錯誤 %s \n", buf);
			continue;
		}
		memset( buf1, 0, sizeof(buf1));
		if( getStringFromIndexWithDelim( buf, ":", 5, buf1, sizeof(buf1)) ==FALSE ){
			print(" 5.map 傳送點錯誤 %s [%s] \n", buf, buf1);
			continue;
		}
		MapWarppoint[ps].use = 1;
		MapWarpPoints++;
		ps++;
		if( ps >= MAP_MAXWARPPOINT ){
			break;
		}
	}
	//andy_log
	print("初始化 %d 地圖傳送點...", MapWarpPoints);
	fclose( fp);
	print("完成\n");
	return 1;
}

void MAPPOINT_MapWarpHandle( int charaindex, int ps, int ofl, int ox, int oy )
{
	int floor, x, y;
	if( MAPPOINT_getMapWarpGoal( ps, ofl, ox, oy, &floor, &x, &y) == -1 ){
		//andy_log
		print( "獲取傳送點( %d, %d,%d,%d)錯誤!!\n", ps, ofl, ox, oy);
		return;
	}
	if( floor == 777 ) return;
	CHAR_warpToSpecificPoint( charaindex, floor, x, y);
	if( CHAR_getWorkInt( charaindex, CHAR_WORKPARTYMODE ) == CHAR_PARTY_LEADER ) {
		int	i;
		for( i = 1; i < getPartyNum(charaindex  ); i ++ ) {
			int index = CHAR_getWorkInt( charaindex, i + CHAR_WORKPARTYINDEX1);
			if( CHAR_CHECKINDEX(index) ) {
				CHAR_warpToSpecificPoint( index, floor, x, y);
			}
		}
	}
}

#ifdef _MO_LNS_MAPSUOXU
int DelMapPoint( int ps)//卸載地圖傳送點
{
	if (MapWarppoint[ps].use != 1) return FALSE;
	MapWarppoint[ps].type = 0;//設置地圖的傳送點類型
	endObjectOne(get_mappointindex(MapWarppoint[ps].ofloor,MapWarppoint[ps].ox,MapWarppoint[ps].oy));//清掉obj
	MapWarppoint[ps].ofloor = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].ox = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].oy = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].floor = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].x = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].y = -1;//設置地圖的傳送點類型
	MapWarppoint[ps].use = 0;
	MapWarppoint[ps].type = 0;
	return TRUE;//注意設置傳送點時先檢查是否原來有傳送點
}

int SetMapPoint( char* buf)//加載地圖傳送點
{  // "傳送點類型:NULL:2000,50,50:2006,20,20:？"
	if( MapWarpPoints >= MAP_MAXWARPPOINT ){
		print(" 傳送點已達上限！\n");
		return -1;
	}
	char buf1[256];
	char buf2[256];
	int objtype,i;
	if( getStringFromIndexWithDelim( buf, ":", 1, buf1, sizeof(buf1)) ==FALSE )//找出傳送點類型
	{
		return -2;
	}
	for( i=0; i<arraysizeof( PointType); i++)	{
		if( !strcmp( buf1, PointType[i]) )break;
	}
	if( i >= arraysizeof( PointType) ){//傳送點類型錯誤
		return -3 ;
	}
	MapWarppoint[MapWarpPoints].type = i;//設置地圖的傳送點類型
	if( getStringFromIndexWithDelim( buf, ":", 2, buf1, sizeof(buf1)) ==FALSE ) //找出傳送點有效時間
	{
		return -4 ;
	}
	objtype = CHAR_EVENT_WARP;//設置對象為傳送點
	if( !strcmp( buf1, "NULL")){
	}else if( !strcmp( buf1, "M")){
		objtype = CHAR_EVENT_WARP_MORNING;//設置對象為早晨傳送點
	}else if( !strcmp( buf1, "N")){
		objtype = CHAR_EVENT_WARP_NIGHT;//設置對象為晚上傳送點
	}else if( !strcmp( buf1, "A")){
		objtype = CHAR_EVENT_WARP_NOON;//設置對象為中午傳送點
	}
	memset( buf1, 0, sizeof(buf1));
	if( getStringFromIndexWithDelim( buf, ":", 3, buf1, sizeof(buf1)) ==FALSE )//找出原點
	{
		return -5 ;
	}
	int fl = -1,x = -1,y = -1;
	if( getStringFromIndexWithDelim( buf1, ",", 1, buf2, sizeof(buf1)) !=FALSE )//找出原點
	{
		fl = atoi(buf2);
	}
	if( getStringFromIndexWithDelim( buf1, ",", 2, buf2, sizeof(buf1)) !=FALSE )//找出原點
	{
		x = atoi(buf2);
	}
	if( getStringFromIndexWithDelim( buf1, ",", 3, buf2, sizeof(buf1)) !=FALSE )//找出原點
	{
		y = atoi(buf2);
	}
	if (fl == -1 || x == -1 || y == -1) return -5;
	if (get_mappointindex( fl,x, y) != -1) return -5;//設置過傳送點！
	for (i=0;i<MapWarpPoints;i++)//找出一個空閑的傳送點
	{
		if (MapWarppoint[i].use != 1) break;//找到空閑傳送點
	}

	if( MAPPOINT_setMapWarpFrom( i, buf1) == -1){//放置原點
		return -6 ;
	}
	if( MAPPOINT_creatMapWarpObj( i, buf1, objtype) == -1 ){//放置原點對象
		return -7 ;
	}
	memset( buf1, 0, sizeof(buf1));
	if( getStringFromIndexWithDelim( buf, ":", 4, buf1, sizeof(buf1)) ==FALSE ){//找出傳送點
		return -8 ;
	}
	if( MAPPOINT_setMapWarpGoal( i, buf1) == -1 ){//設置傳送點
		return -9 ;
	}
	memset( buf1, 0, sizeof(buf1));
	if( getStringFromIndexWithDelim( buf, ":", 5, buf1, sizeof(buf1)) ==FALSE ){
		//print(" 缺少傳送點類型 \n", buf, buf1);
		return -10 ;
	}
	MapWarppoint[i].use = 1;
	if (i >= MapWarpPoints) MapWarpPoints++;//如果當前傳送點已經到達最後，預設下一個傳送點。
	return i;
}
#endif


#endif



