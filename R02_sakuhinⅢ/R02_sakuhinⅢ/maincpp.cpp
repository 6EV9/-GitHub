
#include "DxLib.h"
#include "resource.h"


#define GAME_WIDTH			800	
#define GAME_HEIGHT			600
#define GAME_COLOR			32	

#define GAME_WINDOW_BAR		0	
#define GAME_WINDOW_NAME	"GAME TITLE"	
#define GAME_FPS			60


#define MOUSE_BUTTON_CODE	129		


#define PATH_MAX			255	
#define NAME_MAX			255


#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")		


#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")


#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")


#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\playBK.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\play.png")

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\haikei1.png")		
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\ROGO2.png")	
#define IMAGE_TITLE_ROGO_ROTA		0.005		
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0			
#define IMAGE_TITLE_ROGO_X_SPEED	1			
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\ROGO.png")	
#define IMAGE_TITLE_START_CNT		1			
#define IMAGE_TITLE_START_CNT_MAX	30			

#define MUSIC_LOAD_ERR_TITLE TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH            TEXT(".\\MUSIC\\BGMpaly.mp3")
#define MUSIC_BGM_TITLE_PATH		TEXT(".\\MUSIC\\BGMSTR.mp3")	


#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")



enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラクターのスピード

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//キャラクターのリロード


typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;


typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	
	int WheelValue = 0;
	iPOINT Point;		
	iPOINT OldPoint;	
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	
	int Button[MOUSE_BUTTON_CODE] = { 0 };	
}MOUSE;


typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ


}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		
	int handle;					
	int x;						
	int y;						
	int width;					
	int height;					
}IMAGE;	

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		
	int handle;					
}MUSIC;	


typedef struct STRUCT_CHARA
{
	IMAGE image;				
	int speed;					
	int CenterX;				
	int CenterY;				

	MUSIC musicShot;			

	BOOL CanShot;				
	int ShotReLoadCnt;			
	int ShotReLoadCntMAX;		
	



}CHARA;






typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		
	double angle;		
	double angleMAX;	
	double rate;		
	double rateMAX;		

}IMAGE_ROTA;	

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;		
	int Cnt;			
	int CntMAX;			
	BOOL IsDraw;		

}IMAGE_BLINK;	






int StartTimeFps;				
int CountFps;					
float CalcFps;					
int SampleNumFps = GAME_FPS;	


char AllKeyState[256] = { '\0' };			
char OldAllKeyState[256] = { '\0' };	


//MOUSE mouse;

FONT FontTanu32;	

int GameScene;		





IMAGE ImageTitleBK;					
IMAGE_ROTA ImageTitleROGO;				
IMAGE_BLINK ImageTitleSTART;			


IMAGE ImageBack;
CHARA player;		


MUSIC BGM;			
MUSIC BGM_TITLE;





VOID MY_FPS_UPDATE(VOID);			
VOID MY_FPS_DRAW(VOID);			
VOID MY_FPS_WAIT(VOID);				

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

//VOID MY_MOUSE_UPDATE(VOID);			//マウスの入力情報を更新する
//BOOL MY_MOUSE_DOWN(int);			//ボタンを押しているか、マウスコードで判断する
//BOOL MY_MOUSE_UP(int);				//ボタンを押し上げたか、マウスコードで判断する
//BOOL MY_MOUSEDOWN_KEEP(int, int);	//ボタンを押し続けているか、マウスコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);			
VOID MY_FONT_DELETE(VOID);			

VOID MY_START(VOID);		
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		
VOID MY_DELETE_IMAGE(VOID);		

BOOL MY_LOAD_MUSIC(VOID);		
VOID MY_DELETE_MUSIC(VOID);		

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);	
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	
	SetWindowStyleMode(GAME_WINDOW_BAR);				
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			
	SetAlwaysRunFlag(TRUE);								
	SetWindowIconID(IDI_ICON1);							

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	int DrawX = 0;
	int DrawY = 0;
	
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//プレイヤーの設定
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;
	
	
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			

	GameScene = GAME_SCENE_START;	

	SetDrawScreen(DX_SCREEN_BACK);	

	
	
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	
		if (ClearDrawScreen() != 0) { break; }	

		MY_ALL_KEYDOWN_UPDATE();				

						

		if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) { DrawY--; }
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE) { DrawY++; }
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE) { DrawX--; }
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) { DrawX++; }

		
		DrawFormatString(0, 0, GetColor(255, 255, 255), "DrawX:%d", DrawX);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "DrawY:%d", DrawY);



		MY_FPS_UPDATE();	

		
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();	
			break;
		}

		MY_FPS_DRAW();		

		ScreenFlip();		

		MY_FPS_WAIT();		
	}


	MY_FONT_DELETE();

	
	MY_FONT_UNINSTALL_ONCE();


	MY_DELETE_IMAGE();

	
	MY_DELETE_MUSIC();

	DxLib_End();

	return 0;
}


VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) 
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
	
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}


VOID MY_FPS_DRAW(VOID)
{
	
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}


VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//キーコード：KEY_INPUT_???

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}




BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}


VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}


BOOL MY_FONT_CREATE(VOID)
{
	

	
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	
	FontTanu32.handle = -1;								
	FontTanu32.size = 32;								
	FontTanu32.bold = 1;								
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	

	
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	

	return TRUE;
}


VOID MY_FONT_DELETE(VOID)
{

	DeleteFontToHandle(FontTanu32.handle);	

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);	
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
	

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
		}

		GameScene = GAME_SCENE_PLAY;
	}

	

	//タイトルロゴを拡大
	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	//タイトルロゴを移動
	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		//タイトルロゴが移動しきったら

		//スタートを点滅
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			//描画する/しないを決める
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}


	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);	//タイトル背景の描画

	
	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,	//画像の座標
		ImageTitleROGO.rate,							//画像の拡大率
		ImageTitleROGO.angle,							//画像の回転率
		ImageTitleROGO.image.handle, TRUE);				//画像のハンドル

	//点滅
	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//タイトルスタートの描画
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//スペースキーを押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		

		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);

GameScene = GAME_SCENE_END;
return ;
	}

	if (CheckSoundMem(BGM.handle) == 0)
	{
		
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	//50%の音量にする

		
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//プレイヤーの中心位置を設定する
	//player.CenterX = mouse.Point.x;
	//player.CenterY = mouse.Point.y;

	//プレイヤーの位置に置き換える
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	//画面外にプレイヤーが行かないようにする
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	





	return;
}


//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//背景を描画する
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	


	//プレイヤーを描画する(画像を引き伸ばして描画※処理負荷が高い！多用に注意！)
	DrawExtendGraph(
		player.image.x, player.image.y,														//ココから
		player.image.x + player.image.width * 2, player.image.y + player.image.height * 2,	//ココまで引き伸ばす
		player.image.handle, TRUE);


	/*
	//プレイヤーを描画する(画像を拡大回転して描画※処理負荷が高い！多用に注意！)
	DrawRotaGraph(
		player.image.x, player.image.y,
		2.0,							//拡大率
		DX_PI * 2 / 4 * 2,				//回転率(ラジアン)　※円を４分割して、考えよう！
		player.image.handle, TRUE);
	*/

	/*
	//プレイヤーのを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	*/



	DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{

	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}


BOOL MY_LOAD_IMAGE(VOID)
{

	

	//タイトル背景
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			
	if (ImageTitleBK.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//画像の幅と高さを取得
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//左右中央揃え
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//上下中央揃え

	//タイトルロゴ
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);					
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);			
	if (ImageTitleROGO.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);	//画像の幅と高さを取得
	ImageTitleROGO.image.x = 230;							//光っている部分から描画したい
	ImageTitleROGO.image.y = GAME_HEIGHT / 2;				//中央寄せ
	ImageTitleROGO.angle = DX_PI * 2;						//回転率
	ImageTitleROGO.angleMAX = DX_PI * 2;					//回転率MAX
	ImageTitleROGO.rate = 0.0;								//拡大率
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;		//拡大率MAX

	//タイトルスタート
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);					
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);			
	if (ImageTitleSTART.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);	//画像の幅と高さを取得
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;					//左右中央揃え
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;	//ロゴの下に表示
	ImageTitleSTART.Cnt = 0.0;								//カウンタ
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//カウンタMAX
	ImageTitleSTART.IsDraw = FALSE;							//描画させない

	
	strcpy_s(ImageBack.path, IMAGE_BACK_PATH);		//パスの設定
	ImageBack.handle = LoadGraph(ImageBack.path);	//読み込み
	if (ImageBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//画像の幅と高さを取得
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//左右中央揃え
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;
	
	//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		
	player.image.handle = LoadGraph(player.image.path);	
	if (player.image.handle == -1)
	{
		
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_LOW;									//スピードを設定

	

	return TRUE;
}


VOID MY_DELETE_IMAGE(VOID)
{

	DeleteGraph(player.image.handle);



	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);

	

	
	return;
}

//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{

	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);				//パスの設定
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);			//読み込み
	if (BGM_TITLE.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM.path, MUSIC_BGM_PATH);		
	BGM.handle = LoadSoundMem(BGM.path);	
	if (BGM.handle == -1)
	{
		
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	////プレイヤーのショット音
	//strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			
	//player.musicShot.handle = LoadSoundMem(player.musicShot.path);		
	//if (player.musicShot.handle == -1)
	//{
	//	
	//	MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}

	return TRUE;
}


VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(BGM_TITLE.handle);

	return;
}

