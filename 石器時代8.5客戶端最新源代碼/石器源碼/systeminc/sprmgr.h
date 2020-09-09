/************************/
/*	sprmgr.h			*/
/************************/
#ifndef _SPRMGR_H_
#define _SPRMGR_H_
#include <ddraw.h>
#ifndef _READ16BITBMP
	//關後用 _READ16BITBMPVARIABLES 的參數來代替
	#define OLD_GRAPHICS_START	1000000		// 原本realbin圖的最大量
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START	// 最大圖量// ?????
#else
	#define MAX_GRAPHICS_24		50000		// 高彩圖最大圖量
	#define OLD_GRAPHICS_START	1000000		// 原本realbin圖的最大量
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START + MAX_GRAPHICS_24  // 最大圖量// ?????
	#define MAX_GRAPHICS_ALPHA	50000		// 高彩圖alpha通道最大圖量
#endif

#ifdef _READ16BITBMPVARIABLES					//關 _READ16BITBMP 後還須要的參數
	#define MAX_GRAPHICS_24		50000		// 高彩圖最大圖量
	#define OLD_GRAPHICS_START	500000		// 原本realbin圖的最大量
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START + MAX_GRAPHICS_24  // 最大圖量// ??
#endif

#define	DEF_COLORKEY		0				//預設透明色// ????

#define SURFACE_WIDTH   64 			//存圖用的source face寬//
#define SURFACE_HEIGHT  48			//存圖用的source face高//

extern LPDIRECTDRAWSURFACE lpBattleSurface;
#ifdef _READ16BITBMP
extern LPDIRECTDRAWSURFACE lpBattleSurfaceSys;
#endif
extern int SurfaceDispCnt;
extern int SurfaceSizeX;
extern int SurfaceSizeY;
extern UINT SurfaceDate;
struct surfaceInfo{
	LPDIRECTDRAWSURFACE lpSurface;
#ifdef _CACHE_SURFACE_
	char *lpCacheData;				//緩衝數據
	int palNo;						//當前調色闆
	int sizeX;						//繪製寬度
	int sizeY;						//繪製高度
	BOOL colordepth;					//使用調色闆
#endif
#ifdef _READ16BITBMP
	BYTE *lpAlphaData;
	BOOL useAlpha;
#endif
#ifdef _NEW_COLOR_
	BOOL useAlpha;
	BYTE *lpAlphaData;				//16位分辨率下保存半透明像素
#endif
	int	bmpNo;						//圖的編號,-1 代錶source face為空的// ???????
	UINT date;						//記錄這個source face使用的日期
	short offsetX;					
	short offsetY;					
	surfaceInfo	*pNext;				
};

typedef struct surfaceInfo SURFACE_INFO;
typedef struct{
	SURFACE_INFO *lpSurfaceInfo;
#ifdef _READ16BITBMP
	SURFACE_INFO *lpSurfaceInfoSys;
#endif
	short width,height;
	int AlphaFlg;
}SPRITE_INFO;

extern SPRITE_INFO SpriteInfo[];
extern SURFACE_INFO SurfaceInfo[];
#ifdef _READ16BITBMP
extern SURFACE_INFO SurfaceInfoSys[];
#endif
extern int SurfaceCnt;
extern int VramSurfaceCnt;
extern int SysramSurfaceCnt;
extern int SurfaceSearchPoint;
#ifdef _READ16BITBMP
	#ifdef _STONDEBUG_
	extern unsigned int iTotalUseTime;
	extern unsigned int iTotalProcTime;
	extern unsigned int iTotalRunCount;
	extern LARGE_INTEGER tf;
	#endif
#endif

#ifdef _STONDEBUG_		
extern int SurfaceUseCnt;
#endif

BOOL InitOffScreenSurface( void );
void InitSurfaceInfo( void );
void InitSpriteInfo( void );
BOOL LoadBmp( int bmpNo );


#endif
