#ifndef _TALKWINDOW_H_
#define _TALKWINDOW_H_
#include <windows.h>
#include "../systeminc/chat.h"

#define WM_UPDATE_SKIN 0x8000
#define MAX_TALK_WINDOW_LINE 6
#define TALK_WINDOW_SXO	12				// 對話視窗輸齣文字的起始x座標
#define TALK_WINDOW_SYO 10				// 對話視窗輸齣文字的起始y座標
#define TALK_WINDOW_SXI	30				// 對話視窗輸入文字的起始x座標
#define TALK_WINDOW_SYI 128				// 對話視窗輸入文字的起始y座標
#define SKIN_WIDTH 645
#define SKIN_HEIGHT 155
#define SKIN_KIND 5
#define TALK_WINDOW_MAX_CHAT_LINE 40 // 最大聊天buffer
#ifdef _STONDEBUG_
#define FACE_SYMBOL_NUM 20				// 錶情符號數量
#define STORE_SYMBOL_NUM 200			// 記錄錶情位置數量
#define LINE_HEIGHT 20						// 文字輸齣時的行距
#define SYMBOL_WIDTH 19						// 錶情符號圖寬
#define SYMBOL_HEIGHT 19					// 錶情符號圖高
#endif

extern BOOL g_bTalkWindow;
extern int g_iCursorCount;

#ifdef _STONDEBUG_
typedef struct _tsFaceSymbol{				// 錶情符號
	HDC hDraw;
	HDC hDrawMask;
	HBITMAP hbmpMaskBMP;
	HANDLE hLoadBMP;
	HANDLE hOldLoadBMP;
	HANDLE hOldMaskBMP;
	BOOL bUse;
	char szSymbol[8];					// 符號( :) :( :D ...etc)
	char szFaceName[32];			// 檔名
}FaceSymbol;

typedef struct _tsStoreSymbol{				// 記錄在那裏顯示錶情
	BOOL bUse;
	HDC hDraw;
	HDC hDrawMask;
	int x;
	int y;
}StoreSymbol;
#endif

typedef struct _tsChatBufferLink{
	CHAT_BUFFER ChatBuffer;
	_tsChatBufferLink *prev;
	_tsChatBufferLink *next;
	BOOL bUse;
}ChatBufferLink;

LRESULT CALLBACK TalkWindowProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);

class CTalkWindow
{
private:
	HWND m_hWnd;											// 父視窗的 HWND
	HWND m_hTalkWindow;								// 自己的 HWND
	HINSTANCE m_hInstance;						// 父視窗的 HINSTANCE
	HANDLE m_hSkin[SKIN_KIND];				// SKIN_KIND->0:base 1:up arrow 2:up arrow hit 3:down arrow 4:down arrow hit
	HANDLE m_hOldSkin[SKIN_KIND];
	HDC m_hdcSkin[SKIN_KIND];					// SKIN_KIND->0:base 1:up arrow 2:up arrow hit 3:down arrow 4:down arrow hit
	HDC m_hdcBackBuffer;							// backbuffer dc for draw
	HBITMAP m_hbmpBackBuffer;					// backbuffer of memory for draw
	HANDLE m_hbmpOldBackBuffer;
	BOOL m_bUpArrowHit;								// 上捲按鈕是否按下
	BOOL m_bDownArrowHit;							// 下捲按鈕是否按下
	BOOL m_bScroll;										// 現在是否正處於捲動中
	BOOL m_bInit;											// 初始化成功或失敗
	ChatBufferLink *m_pCBLHead;				// 指嚮對話link第一個link的指標
	ChatBufferLink *m_pCBLTail;				// 指嚮對話link最後一個link的指標
	ChatBufferLink *m_pCBLString;			// 指嚮對話link準備被填入字串的link的指標
	ChatBufferLink *m_pCBLView;				// 指嚮要顯示在畫麵上第一行的字串的link指標
	ChatBufferLink *m_pCBLViewBottom;	// 指嚮要顯示在畫麵上最後一行的字串的link指標
#ifdef _STONDEBUG_
	FaceSymbol m_fsFaceSymbol[FACE_SYMBOL_NUM];			// 錶情符號
	StoreSymbol m_ssStoreSymbol[STORE_SYMBOL_NUM];	// 記錄在那邊顯示錶情
	int m_iSymbolCount;
#endif
	int m_iline;
public:
	CTalkWindow(void);
	~CTalkWindow(void);

	void Create();
	void Update(void);
	void LoadSkin(char *szSkinPath);
	void DrawSkin(BOOL bShowCursor);
	void AddString(char *szString,int color);
	HWND GetTalkWindowWND(void) { return m_hTalkWindow;};
	void UpArrowHit(BOOL bHit);
	void DownArrowHit(BOOL bHit);
	void ClearChatBuffer(void);
	void Init(HWND hWnd,HINSTANCE hInstance);
	void Visible(BOOL flag);
	void Release(void);
#ifdef _STONDEBUG_
	void ReadFaceSymbolFile(void);
	void InitFaceSymbol(COLORREF MaskColor);
	void ReleaseFaceSymbol(void);
	void SetToFaceSymbolString(char *szDestString,ChatBufferLink *pCBL,int x,int y);
	void ShowFaceSymbol(void);
#endif
};

extern CTalkWindow TalkWindow;

#endif