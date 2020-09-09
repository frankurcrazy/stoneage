/************************/
/*	ohta.c				*/
/************************/
#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "ohta.h"
#include "../systeminc/loadsprbin.h"
#include "../systeminc/t_music.h"

ACTION *MakeJiki( void );
void Jiki( ACTION *pAct );

ACTION *MakeJikiTama( int x, int y, int dx, int dy, int bmpNo );
void JikiTama( ACTION *pAct );

ACTION *MakeEnemy( void );
void Enemy( ACTION *pAct );

ACTION *MakeEnemyTama( ACTION *pOya );
void EnemyTama( ACTION *pAct );

ACTION *MakeBg( void );
void Bg( ACTION *pAct );

ACTION *MakeKen( void );
void Ken( ACTION *pAct );

ACTION *MakeGameOver( void );
void GameOver( ACTION *pAct );

/* 爆kデ`タ */
int bomData[] = { 21, 22, 23, 23, 22, 21 };

/* 自Cのポインタ */
ACTION *pJiki;


/* 攻膜畏N */
enum{
	TAMA_NORMAL,	/* ノ`マル */
	TAMA_TWIN,		/* ツイン */
	TAMA_3WAY,		/* ３方嚮 */
	TAMA_DIR,		/* 全方嚮 */
	TAMA_END		/* Kわり */
};
	
/********************************************/
/*	自C									*/
/********************************************/

/* 自C予造體 */
typedef struct{
	int cnt,cnt2,cnt3;	/* 用カウンタ */
	int tamaDir;		/* の方嚮 */
	int tamaDx;			/* のＸ分 */
	int attackKind;		/* 攻膜畏N */
	STR_BUFFER strTestBuffer;	/* テスト文字列 */
}JIKI;

static int No = 36000;

/* 自C作成 *******************************************************************/
ACTION *MakeJiki( void )
{
	ACTION *pAct;
	JIKI *pYobi;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_JIKI, sizeof( JIKI ) );
	if( pAct == NULL ) return NULL;
	
	/* 予造體のアドレス */
	pYobi = ( JIKI *)pAct->pYobi;
	
	/* g行v數 */
	pAct->func = Jiki;
	/* 錶示先度 */
	pAct->dispPrio = DISP_PRIO_JIKI;
	// 當たり判定 + ボックス錶示
	pAct->atr |= ACT_ATR_HIT_BOX;
	/* スプライト番號 */
	//pAct->bmpNo = 31;
	//pAct->anim_chr_no = 20001;
	// anim_tbl.h の番號
	pAct->anim_chr_no = 31555; // イノシシ
	//pAct->anim_chr_no = 5200; // マウスカ`ソル
	//pAct->anim_chr_no = 9350; // SCORE
	// 幼鞣號
	//pAct->anim_no = ANIM_ATTACK;
	pAct->anim_no = ANIM_STAND;
	pAct->anim_no = ANIM_STAND + 1;
	// アニメ`ション嚮き( ０～７ )( 下が０で右迴り )
	pAct->anim_ang = 0;
	/* ＨＰ */
	pAct->hp = 100;
	/* 初期位置 */
	pAct->x = 304;
	pAct->y = 400;

	/* 匙鞽 */
//	MakeEnemy();
	/* ＢＧ作成 */
	//MakeBg();
	
	/* ケン作成 */
//	MakeKen();
	
	/* 攻膜畏N */
	//pYobi->attackKind = TAMA_DIR;
	pYobi->attackKind = TAMA_3WAY;
	/* 方嚮 */
	pYobi->tamaDir = 1;
	pYobi->tamaDx = 1;
	/* グロ`バルに保存 */
	pJiki = pAct;
	
	// 文字列のLさ
	pYobi->strTestBuffer.len = 10;
	// 文字列の色
	pYobi->strTestBuffer.color = 1;
	pYobi->strTestBuffer.x = 320;
	pYobi->strTestBuffer.y = 260;
	
	return pAct;
	
}

/* 自CI理 *******************************************************************/
void Jiki( ACTION *pAct )
{
	JIKI *pYobi = ( JIKI *)pAct->pYobi;
	//int i;
	
	/* 攻氖埭堡r */
	if( pAct->damage > 0 ){
		pAct->hp -= pAct->damage;
		if( pAct->hp <= 0 ){ 
			pAct->state = ACT_STATE_DEAD;
			pYobi->cnt  = 0;
			pYobi->cnt2 = 0;
			pYobi->cnt3 = 0;
		}
		pAct->damage = 0;
	}
	// 取齣す座
//	rcX = Rnd( 0,608 );
//	rcY = Rnd( 0,400 );
//	SetRect( &Rc[ pAct->bmpNo ], rcX, rcY, rcX + 32, rcY + 32 ); 
	
	// マウス移
	//pAct->x = mouse.nowPoint.x;
	//pAct->y = mouse.nowPoint.y;

	// マウスでk射
	if( pYobi->cnt3 <= 0 ){
		// k射
		//if( mouse.state == MOUSE_LEFT_CRICK ){
		if( mouse.onceState & MOUSE_LEFT_CRICK ){
			// 入力フォ`カス取得
			//GetKeyInputFocus( &pYobi->strTestBuffer );
			/* 作成 */
			//MakeJikiTama( pAct->x , pAct->y -16, 0, -8, Rnd( 0, BMP_FILE - 1 ) );
			//MakeJikiTama( pAct->x , pAct->y -16, 0, -8, 1034 );
			//MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, 25 );
			
			//MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 0, BMP_FILE - 2 ) );
			
			//MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 31554, 31557 ) ); // ＴＧＳ
			//MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 31000, 31069 ) ); // モンスタ`
//			MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 30100, 30135 ) ); // ＰＣ
			//MakeJikiTama( pAct->x + 10, pAct->y -16, 0, -8, Rnd( 0, BMP_FILE - 1 ) );
			//MakeJikiTama( pAct->x, pAct->y -16, 0, -8, 29 );
			//MakeJikiTama( pAct->x - 10, pAct->y -16, 0, -8, 29 );
			//MakeJikiTama( pAct->x + 10, pAct->y -16, 0, -8, 29 );
			pYobi->cnt3 = 5;
#if 0
			for( i = 0; i < (int)256; i++ ){
				// 明るくする
				Palette[i].peRed 	 *= 0.95;
				Palette[i].peGreen *= 0.95;
				Palette[i].peBlue  *= 0.95;
			}
			// パレットの中身をO定
			lpDraw->lpPALETTE->SetEntries( 0, 0, 256, Palette );
#endif
		}
		// 真中ボタン
		if( GetAsyncKeyState( VK_MBUTTON ) ){
			//MakeJikiTama( pAct->x, pAct->y -16, 0, -8, 29 );
			//MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 0, BMP_FILE - 1 ) );
	//		MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, 32 );
			pYobi->cnt3 = 5;
			
		}
		// k射
		//if( mouse.onceState & MOUSE_RIGHT_CRICK ){
		if( mouse.state & MOUSE_RIGHT_CRICK ){
			// 入力フォ`カス取得
			//GetKeyInputFocus( &MyChatBuffer );
		//if( GetAsyncKeyState( VK_RBUTTON ) 	& 0x8000 ){
		//	MakeJikiTama( pAct->x, pAct->y -16, 0, -8, 29 );
		// サ`フェスがあったら
		//if( lpSurface[ 0 ] != NULL ){
		//	// リリ`ス
		//	lpSurface[ 0 ]->Release( );
		//	lpSurface[ 0 ] = NULL;
		//}
		//	MakeBg();
#if 0		
			MakeJikiTama( pAct->x - 10, pAct->y -16, -6, -8, Rnd( 0, BMP_FILE - 2 ) );
			MakeJikiTama( pAct->x -  5, pAct->y -16, -3, -8, Rnd( 0, BMP_FILE - 2 ) );
			MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, Rnd( 0, BMP_FILE - 2 ) );
			MakeJikiTama( pAct->x +  5, pAct->y -16,  3, -8, Rnd( 0, BMP_FILE - 2 ) );
			MakeJikiTama( pAct->x + 10, pAct->y -16,  6, -8, Rnd( 0, BMP_FILE - 2 ) );
#else
	//		MakeJikiTama( pAct->x - 10, pAct->y -16, -6, -8, No );
	//		MakeJikiTama( pAct->x -  5, pAct->y -16, -3, -8, No );
	//		MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, No );
	//		MakeJikiTama( pAct->x +  5, pAct->y -16,  3, -8, No );
	//		MakeJikiTama( pAct->x + 10, pAct->y -16,  6, -8, No );
#endif		
			pYobi->cnt3 = 5;
#if 0
			for( i = 0; i < (int)256; i++ ){
				// 暗くする
				Palette[i].peRed  *= 1.05;
				Palette[i].peGreen*= 1.05;
				Palette[i].peBlue *= 1.05;
			}
			//パレットの中身をO定
			lpDraw->lpPALETTE->SetEntries( 0, 0, 256, Palette );
#endif
		}
		
	}else pYobi->cnt3--;

	/* 狀Bで分岐 */
	switch( pAct->state ){
		/* 通常r */
		case ACT_STATE_ACT:
		
			/* との當たり判定 */
			//Hit( pAct, PRIO_ENEMY_TAMA );
			/* 長趣蔚堡郡昱卸 */
			//Hit( pAct, PRIO_ENEMY );

			/* 移 */
			if( joy_con[ 0 ] & JOY_UP ){	/* 上 */
				pAct->y -= 2;
				if( pAct->y < 0 ) pAct->y = 0;
			}
			if( joy_con[ 0 ] & JOY_DOWN ){	/* 下 */
				pAct->y += 2;
				if( pAct->y > 448 ) pAct->y = 448;
			}
			if( joy_con[ 0 ] & JOY_LEFT ){	/* 左 */
				pAct->x -= 2;
				if( pAct->x < 0 ) pAct->x = 0;
			}
			if( joy_con[ 0 ] & JOY_RIGHT ){	/* 右 */
				pAct->x += 2;
				if( pAct->x > 608 ) pAct->x = 608;
			}
			
			// 匙鞽
			//if( joy_con[ 0 ] & JOY_B )	MakeEnemy();
			
			/* k射 */
			if( pYobi->cnt3 <= 0 ){ /* ウェイト */
				if( joy_con[ 0 ] & JOY_A ){
					
					/*DeathAllAction();*/
					/* のNで分岐 */
					switch( pYobi->attackKind ){
						
						case TAMA_NORMAL:
						
							/* 作成 */
							MakeJikiTama( pAct->x, pAct->y -16, 0, -8, 28 );
							
							break;
							
						case TAMA_TWIN:
						
							/* 作成 */
							MakeJikiTama( pAct->x - 10, pAct->y -16, 0, -8, 29 );
							MakeJikiTama( pAct->x + 10, pAct->y -16, 0, -8, 29 );
							
							break;
							
						case TAMA_3WAY:
						
							MakeJikiTama( pAct->x - 10, pAct->y -16, -4, -8, 29 );
							MakeJikiTama( pAct->x, 	   	pAct->y -16,  0, -8, 29 );
							MakeJikiTama( pAct->x + 10, pAct->y -16,  4, -8, 29 );
							
							break;
							
						case TAMA_DIR:
						
							MakeJikiTama( pAct->x, pAct->y -16,  pYobi->tamaDx, -8, 29 );
							MakeJikiTama( pAct->x, pAct->y -16, -pYobi->tamaDx, -8, 29 );
							/* 方嚮 */
							pYobi->tamaDx += pYobi->tamaDir;
							if(	pYobi->tamaDx <= -10 || 10 <= pYobi->tamaDx ){
								pYobi->tamaDir *= -1;
							}
							break;
					}
					pYobi->cnt3 = 2; /*  ウェイト */
					//pYobi->cnt3 = 0; /*  ウェイト */
				}
			}else{
				if( pYobi->cnt3 > 0 ) pYobi->cnt3--;
			}
			
			/* 點 */
/*			if( ( int )pAct->x % 2 ) pAct->atr |= ACT_ATR_HIDE;
			else pAct->atr &= ~ACT_ATR_HIDE;
*/		
			/* 匙鞽 */
			pYobi->cnt++;
			if( pYobi->cnt >= 1 ){
				//MakeEnemy();
				pYobi->cnt2++;
				if( pYobi->cnt2 >= 5 ){
					pYobi->cnt2 = 0;
					/* 涓 */
					//pYobi->attackKind++;
					if( pYobi->attackKind >= TAMA_END ){
						pYobi->attackKind = 0;
					}
				}
				pYobi->cnt = 0;
			}
			
			break;
	
		/* 死亡r */	
		case ACT_STATE_DEAD:
		
			if( pYobi->cnt == 0 ){ 
				pAct->bmpNo = bomData[ 0 ];
				pYobi->cnt = 1;
			}
			/* 爆kアニメ`ション */
			pYobi->cnt2++;
			if( pYobi->cnt2 >= 5 ){
				pAct->bmpNo = bomData[ pYobi->cnt ];
				pYobi->cnt++;
				pYobi->cnt2 = 0;
				/* Kわったら死ぬ */
				if( pYobi->cnt == 6 ){
					DeathAction( pAct );
					MakeGameOver( );
				}
			}
			
			break;
	}
	
	// 錶示デ`タをバッファに溜める
	//StockDispBuffer( pAct->x + 32, pAct->y, pAct->dispPrio, pAct->anim_chr_no, 0 );
	//StockDispBuffer( pAct->x - 32, pAct->y, pAct->dispPrio, pAct->anim_chr_no, 0 );
	{
		char szMoji[ 256 ];
		wsprintf( szMoji,"BmpNo = %d",No );
	//	StockFontBuffer( pAct->x, pAct->y, FONT_PRIO_FRONT, 2, szMoji, 0 );
	}
	
	// アニメ`ション
	pattern( pAct, ANM_NOMAL_SPD, ANM_LOOP );
	// テスト文字列錶示
	//StockFontBuffer( 320, 200, FONT_PRIO_FRONT, pYobi->strTestBuffer.color, pYobi->strTestBuffer.buffer, 0 );
	StockFontBuffer2( &pYobi->strTestBuffer );
}

/********************************************/
/*	自C									*/
/********************************************/

/* 自C作成 *********************************************************************/
ACTION *MakeJikiTama( int x, int y, int dx, int dy, int bmpNo )
{
	ACTION *pAct;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_JIKI_TAMA, 0 );
	if( pAct == NULL ) return NULL;
	
	/* g行v數 */
	pAct->func = JikiTama;
	// anim_tbl.h の番號
	pAct->anim_chr_no = bmpNo; // イノシシ
	// 幼鞣號
	//pAct->anim_no = ANIM_ATTACK;
	pAct->anim_no = Rnd( ANIM_ATTACK, ANIM_WALK );
	//pAct->anim_no = ANIM_WALK;
	// アニメ`ション嚮き( ０～７ )( 下が０で右迴り )
	pAct->anim_ang = Rnd( 0, 7 );
	///* スプライト番號 */
	//pAct->bmpNo = bmpNo;
	/* 錶示先度 */
	pAct->dispPrio = 2;
	/* ＨＰ */
	pAct->hp = 10000;
	/* 初期位置 */
	pAct->x = x - dx;
	pAct->y = y - dy;
	/* 分 */
	pAct->dx = dx / 2;
	pAct->dy = dy / 2;
	
	return pAct;
}

/* 自CI理 *********************************************************************/
void JikiTama( ACTION *pAct )
{

	/* 攻氖埭堡r */
	if( pAct->damage > 0 ){
		pAct->hp -= pAct->damage;
		if( pAct->hp <= 0 ){ 
			pAct->state = ACT_STATE_DEAD;
		}
		pAct->damage = 0;
	}

	/* 狀Bで分岐 */
	switch( pAct->state ){
		/* 通常r */
		case ACT_STATE_ACT:

			/* 長趣蔚堡郡昱卸 */
			//Hit( pAct, PRIO_ENEMY );

			/* 移 */
			pAct->x += pAct->dx;
			pAct->y += pAct->dy;
	
			/* リミット */
			if(	pAct->y <= -32 ){ 
				pAct->y = -32;
				MakeEnemyTama( pAct );
				DeathAction( pAct );
			}else
			if( lpDraw->ySize <= pAct->y ){ 
				pAct->y = lpDraw->ySize;
				DeathAction( pAct );
			}
			
			if(	pAct->x <= -32 ){
				pAct->x = -32;
				DeathAction( pAct );
			}else
			if( lpDraw->xSize <= pAct->x ){ 
				pAct->x = lpDraw->xSize;
				DeathAction( pAct );
			}

			break;
		
		/* 死亡r */	
		case ACT_STATE_DEAD:
		
			DeathAction( pAct );
			
			break;
	}
	
	
	// アニメ`ション
	pattern( pAct, ANM_NOMAL_SPD, ANM_LOOP );
}


/********************************************/
/*											*/
/********************************************/

/* 秤造體 */
typedef struct{
	int cnt,cnt2,cnt3,animCnt;	/* 用カウンタ */
}ENEMY;

/* 匙鞽 *********************************************************************/
ACTION *MakeEnemy( void )
{
	ACTION *pAct;
	ENEMY *pYobi;
	short bmpTbl[] = { 1, 3, 5, 7, 9, 29 };
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_ENEMY, sizeof( ENEMY ) );
	if( pAct == NULL ) return NULL;
	
	/* 予造體のアドレス */
	pYobi = ( ENEMY *)pAct->pYobi;
	
	/* g行v數 */
	pAct->func = Enemy;
	/* スプライト番號 */
	pAct->bmpNo = bmpTbl[ ( int )Rnd( 0, 4 ) ];
	//pAct->bmpNo = Rnd( 1, 10 );
	/* 錶示先度 */
	pAct->dispPrio = 1;
	/* ＨＰ */
    pAct->hp = 10;//Rnd( 10, 50 );
	/* 初期位置ランダム */
//	pAct->x = Rnd( 0, 608 );
	pAct->x = Rnd( 0, lpDraw->xSize );
	ATR_CRS(pAct) = 16;
	ATR_SPD(pAct) = Rnd( 28, 36 );
	pAct->dx = 0;

	pAct->y = 0;
	/* 分ランダム */
	pAct->dx = Rnd( -3, 3 );
	pAct->dy = Rnd( 1, 3 );
	
	return pAct;
}

/* I理 *********************************************************************/
void enemy_missile( ACTION *a0 )
{
	gemini(a0);		//移
	//畫麵外なら
	if(ATR_H_POS(a0)>=lpDraw->xSize || ATR_H_POS(a0)<-32 || ATR_V_POS(a0)>lpDraw->ySize || ATR_V_POS(a0)<-32)
		DeathAction( a0 );		//K瞭
}

/* I理 *********************************************************************/
void Enemy( ACTION *pAct )
{
	ENEMY *pYobi = ( ENEMY *)pAct->pYobi;

	/* 攻氖埭堡r */
	if( pAct->damage > 0 ){
		pAct->hp -= pAct->damage;
		if( pAct->hp <= 0 ){ 
			pAct->state = ACT_STATE_DEAD;
			pYobi->cnt  = 0;
			pYobi->cnt2 = 0;
			pYobi->cnt3 = 0;
		}
		pAct->damage = 0;
	}

	/* 狀Bで分岐 */
	switch( pAct->state ){
		/* 通常r */
		case ACT_STATE_ACT:
		
			/* 移 */
//			pAct->x += pAct->dx;
//			pAct->y += pAct->dy;

			/* リミットチェック */
//			if( pAct->x < 0 ){ 
//				pAct->x = 0;
//				pAct->dx *= -1;
//			}
//			else
//			if( pAct->x > lpDraw->xSize ){ 
//				pAct->x = lpDraw->xSize;
//				pAct->dx *= -1;
//			}
//			if( pAct->y > lpDraw->ySize ){ 
//				pAct->y = -32;
//			}

			pAct->dx++;		//２割りzみに１迴スピ`ド涓する
			pAct->dx&=1;	//
			gemini(pAct);		//移
			if(ATR_CRS(pAct)==0){		//上移又肖勝
				if( pAct->y < -32 ){			//上端なら
					ATR_CRS(pAct)=16;			//下移娛_始
					ATR_SPD(pAct) = Rnd( 28, 36 );
					pAct->x = Rnd( 0, lpDraw->xSize );	//
				} else {
					if(pAct->dx)
						ATR_SPD(pAct)++;		//スピ`ドアップ
				}
			} else {
				if(pAct->dx){
					ATR_SPD(pAct)--;		//スピ`ドダウン
					if(!ATR_SPD(pAct)){		//停止したなら
						ATR_CRS(pAct)=0;		//上移娛_始
						ACTION *a1;		//ミサイルk射
						int d1,d2;
						/* アクションリストに登h */
						a1 = GetAction( PRIO_ENEMY_TAMA, 0 );
						if( a1 == NULL ) break;
						/* g行v數 */
						a1->func = enemy_missile;
						/* スプライト番號 */
						a1->bmpNo = No++;
						/* 錶示先度 */
						a1->dispPrio = 3;
						/* 初期位置 */
						ATR_H_POS(a1) = ATR_H_POS(pAct)+16;
						ATR_V_POS(a1) = ATR_V_POS(pAct)+16;
						d1 = pJiki->x;			//自Cの方嚮セット
						d2 = pJiki->y;			//
						radar(a1, &d1, &d2);	//
						ATR_CRS(a1)=d1;			//
						ATR_SPD(a1)=16;			//移鈾俁
						play_se( 2, ATR_H_POS(a1), ATR_V_POS(a1) );		//ミサイルk射音
					}
				}
			}
			// アニメ`ション
/*			pYobi->cnt3 += pAct->dy;
			if( pYobi->cnt3 >= 20 ){ 
				pYobi->cnt3 = 0;
				pYobi->animCnt = pYobi->animCnt * ( -2 ) + 1;
				pAct->bmpNo += pYobi->animCnt;
			}
*/
/*			
			pAct->cnt++;
			if( pAct->cnt >= 300 ){
				pAct->state = ACT_STATE_DEAD;
				pAct->cnt = 0;
			}
*/			
			//if( Rnd( 0, 300 ) == 0 ) MakeEnemyTama( pAct );
			//MakeEnemyTama( pAct );
			
			break;
		
		/* 死亡r */	
		case ACT_STATE_DEAD:
		
			if( pYobi->cnt == 0 ){ 
				pAct->bmpNo = bomData[ 0 ];
				pYobi->cnt = 1;
			}
			/* 爆kアニメ`ション */
			pYobi->cnt2++;
			if( pYobi->cnt2 >= 5 ){
				pAct->bmpNo = bomData[ pYobi->cnt ];
				pYobi->cnt++;
				pYobi->cnt2 = 0;
				/* Kわったら死ぬ */
				if( pYobi->cnt == 6 ){
					DeathAction( pAct );
				}
			}
			
			break;
	}

}

/********************************************/
/*										*/
/********************************************/

/* 作成 *********************************************************************/
ACTION *MakeEnemyTama( ACTION *pOya )
{
	ACTION *pAct;
	//float dir;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_ENEMY_TAMA, 0 );
	if( pAct == NULL ) return NULL;
	
	/* g行v數 */
	pAct->func = EnemyTama;
	/* スプライト番號 */
	pAct->anim_chr_no = Rnd( 31554, 31556 );		//スライム
	// 當たり判定 + ボックス錶示
	pAct->atr |= ACT_ATR_HIT_BOX;
	//pAct->anim_no = Rnd( ANIM_ATTACK, ANIM_SATTACK );
	//pAct->anim_no = ANIM_ATTACK;
	pAct->anim_no = ANIM_WALK;
	/* 錶示先度 */
	pAct->dispPrio = DISP_PRIO_JIKI;
	/* ＨＰ */
	pAct->hp = 0;
	/* 初期位置 */
	//pAct->x = pOya->x + 16;
	//pAct->y = pOya->y + 32 ;
	pAct->x = Rnd( 100, 500 );
	pAct->y = Rnd( 100, 400 );
	
	// 移臃較	
	radar2( pAct, pJiki->x, pJiki->y, 1 );
	//移鈾俁
	pAct->spd = 16;			
	
	// アニメ`ション
	pattern( pAct, ANM_NOMAL_SPD, ANM_LOOP );
	return pAct;
}

/* I理 *********************************************************************/
void EnemyTama( ACTION *pAct )
{

	/* 攻氖埭堡r */
	if( pAct->damage > 0 ){
		pAct->hp -= pAct->damage;
		if( pAct->hp <= 0 ){ 
			pAct->state = ACT_STATE_DEAD;
		}
		pAct->damage = 0;
	}

	/* 狀Bで分岐 */
	switch( pAct->state ){
		/* 通常r */
		case ACT_STATE_ACT:
			
			// マウスカ`ソルがヒットしていたら
			if( pAct->hitDispNo == HitDispNo ){
				// 左クリックが押されているr
				if( mouse.state & MOUSE_LEFT_CRICK ){
					// ドラッグ移
					pAct->x = mouse.nowPoint.x;
					pAct->y = mouse.nowPoint.y;
				}
				// 左クリックが押されているr
				if( mouse.state & MOUSE_RIGHT_CRICK ){
					// ドラッグ移
					DeathAction( pAct );
				}
				
			}	
			/* 移 */
			//pAct->x += pAct->dx;
			//pAct->y += pAct->dy;
			//gemini( pAct );		//移
#if 0	
			/* リミット */
			if(	pAct->y <= 0 ){
				pAct->y = 0;
				DeathAction( pAct );
			}else
			if(	pAct->y >= 481 ){ 
				DeathAction( pAct );
			}
			if(	pAct->x <= -8 ){
				DeathAction( pAct );
			}else
			if( lpDraw->xSize <= pAct->x ){ 
				DeathAction( pAct );
			}
#endif			
			break;
		
		/* 死亡r */	
		case ACT_STATE_DEAD:
			DeathAction( pAct );
			break;
	}
	// 移臃較	
	radar2( pAct, pJiki->x, pJiki->y, Rnd( 0, 10 ) );
	// アニメ`ション
	pattern( pAct, ANM_NOMAL_SPD, ANM_LOOP );
}

/* ゲ`ムオ`バ`作成 *******************************************************************/
ACTION *MakeGameOver( void )
{
	ACTION *pAct;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_GAME_OVER, 0 );
	if( pAct == NULL ) return NULL;
	
	/* g行v數 */
	pAct->func = GameOver;
	
	// 非錶示
	pAct->atr |= ACT_ATR_HIDE;
	
	/* スプライト番號 */
	pAct->bmpNo = 0;
//	pAct->bmpNo = 30;
	/* ＨＰ */
	pAct->hp = 100;
	/* 初期位置 */
	pAct->x = 250;
	pAct->y = 200;

	return pAct;
	
}

/* ゲ`ムオ`バ`I理 *******************************************************************/
void GameOver( ACTION *pAct )
{
	//char szMoji[128];
	
	// GAME OVER 錶示
	
}

/* ＢＧ作成 *********************************************************************/
ACTION *MakeBg( void )
{
	ACTION *pAct;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_BG, NULL );
	if( pAct == NULL ) return NULL;
	
	/* g行v數 */
	pAct->func = Bg;
	
	/* スプライト番號 */
	//pAct->bmpNo = 30;
//	pAct->bmpNo = 44;
	pAct->anim_chr_no = 9376;
	/* 錶示先度 */
	pAct->dispPrio = 0;
	/* 初期位置 */
	pAct->x = 320;
	pAct->y = 240;

	// 取齣す座
	//pYobi->rcX = 0;
	//pYobi->rcY = lpDraw->ySize;
	//SetRect( &Rc[ pAct->bmpNo ], pYobi->rcX, pYobi->rcY, pYobi->rcX + lpDraw->xSize, pYobi->rcY + lpDraw->ySize ); 

	return pAct;
}
	
/* ＢＧI理 *********************************************************************/
void Bg( ACTION *pAct )
{
	// 取齣す座
	// 取齣す座
	//pAct->y++;
	//if( pAct->y >= 240 ) pAct->y = -240; 
	pattern( pAct, ANM_NOMAL_SPD, ANM_LOOP );		//アニメ`ションI理
	//StockDispBuffer( pAct->x, pAct->y+lpDraw->ySize, 0, pAct->anim_chr_no, 0 );
	//StockDispBuffer( pAct->x, pAct->y, 0, pAct->anim_chr_no, 0 );
	//StockDispBuffer( pAct->x, pAct->y+lpDraw->ySize, 0, pAct->anim_chr_no, 0);
}


/* ケン作成 *********************************************************************/
ACTION *MakeKen( void )
{
	ACTION *pAct;
	
	/* アクションリストに登h */
	pAct = GetAction( PRIO_BG, NULL );
	if( pAct == NULL ) return NULL;
	
	/* g行v數 */
	pAct->func = Ken;
	
	/* スプライト番號 */
	pAct->bmpNo = 33;
	/* 錶示先度 */
	pAct->dispPrio = 100;
	/* 初期位置 */
	pAct->x = 100;
	pAct->y = 100;
	
	// 取齣す座
	//pYobi->rcX = 0;
	//pYobi->rcY = lpDraw->ySize;
	//SetRect( &Rc[ pAct->bmpNo ], pYobi->rcX, pYobi->rcY, pYobi->rcX + lpDraw->xSize, pYobi->rcY + lpDraw->ySize ); 

	return pAct;
}
	
/* ケンI理 *********************************************************************/
void Ken( ACTION *pAct )
{
	int anim[] = { 	0,0,0,0,
					1,1,1,1,
					2,2,2,2,
					3,3,3,3,
					2,2,2,2,
					1,1,1,1 
					};
}

