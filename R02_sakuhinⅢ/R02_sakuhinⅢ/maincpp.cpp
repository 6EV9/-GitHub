#include "DxLib.h"

#define IDI_ICON1 333

#define GAME_MAP_TATE_MAX	9	
#define GAME_MAP_YOKO_MAX	13	
#define GAME_MAP_KIND_MAX	2	

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")		

#define MAP_DIV_WIDTH		64	
#define MAP_DIV_HEIGHT		64	
#define MAP_DIV_TATE		10	
#define MAP_DIV_YOKO		4	
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	

#define GAME_WIDTH			GAME_MAP_YOKO_MAX * MAP_DIV_WIDTH	//画面幅
#define GAME_HEIGHT		 	9 * MAP_DIV_HEIGHT					//画面高さ
#define GAME_COLOR			32	

#define GAME_WINDOW_BAR		0	
#define GAME_WINDOW_NAME	"GAME TITLE"	
#define GAME_FPS			60


#define PATH_MAX			255	
#define NAME_MAX			255


#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")		


#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")


#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")


#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\playBK.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\play.png")
#define IMAGE_SETUMEI_PATH      TEXT(".\\IMAGE\\setumei.png")
#define IMAGE_END_PATH		TEXT(".\\IMAGE\\END.png")

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\haikei1.png")		
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\ROGO2.png")	
#define IMAGE_TITLE_ROGO_ROTA		0.005		
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0			
#define IMAGE_TITLE_ROGO_X_SPEED	1			
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\ROGO.png")	
#define IMAGE_TITLE_START_CNT		1			
#define IMAGE_TITLE_START_CNT_MAX	30	

#define MUSIC_LOAD_ERR_TITLE TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH TEXT(".\\MUSIC\\BGMpaly.mp3")
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\SHOT.mp3")
#define MUSIC_BGM_TITLE_PATH		TEXT(".\\MUSIC\\BGMSTR.mp3")

#define TAMA_CHANGE_MAX 5
#define TAMA_MAX       16

#define TAMA_CHANGE_MAX		 5	//5フレーム目で弾の画像を変える
#define TAMA_MAX			16	//最大16発まで

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\tama.png")		//赤弾の画像

#define TAMA_DIV_WIDTH		16	//画像を分割する幅サイズ
#define TAMA_DIV_HEIGHT		16	//画像を分割する高さサイズ

#define TAMA_DIV_TATE		3	//画像を縦に分割する数
#define TAMA_DIV_YOKO		1	//画像を横に分割する数

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")


#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

#define TAMA_CHANGE_MAX 5
#define TAMA_MAX       16

#define TAMA_CHANGE_MAX		 5	//5フレーム目で弾の画像を変える
#define TAMA_MAX			16	//最大16発まで

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\tama.png")		//赤弾の画像

#define TAMA_DIV_WIDTH		16	//画像を分割する幅サイズ
#define TAMA_DIV_HEIGHT		16	//画像を分割する高さサイズ

#define TAMA_DIV_TATE		3	//画像を縦に分割する数
#define TAMA_DIV_YOKO		1	//画像を横に分割する数

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO

#define GAME_MAP_TATE_MAX	(9 * 6)	
#define GAME_MAP_YOKO_MAX	13	
#define GAME_MAP_KIND_MAX	2	

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")		

#define MAP_DIV_WIDTH		64	
#define MAP_DIV_HEIGHT		64	
#define MAP_DIV_TATE		10	
#define MAP_DIV_YOKO		4	
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	


#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

#define KEY_RETURN_CLICK_TITLE		TEXT("ゲーム中断")
#define KEY_RETURN_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

#define STR_SCORE            TEXT("SCORE:XXXXX")


enum GAME_MAP_KIND
{
	m = -1,	//(NONE)未定
	k = 10,	//壁
	k2 = 11,//壁
	k3 = 13,//壁
	b = 14,//浮遊物
	c = 17,
	c1 = 18,

	t = 18,	//通路
	s = 32,	//スタート
	g = 3	//ゴール
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_Explanation
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//キャラクターのリロード


typedef struct STRUCT_TAMA
{
	char path[PATH_MAX];
	int handle[TAMA_DIV_NUM];
	int x;
	int y;
	int width;
	int height;
	BOOL IsDraw;
	int nowImageKind;
	int changeImageCnt;
	int changeImageCntMAX;
	int speed;
}TAMA;


typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;





typedef struct STRUCT_FONT
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;


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
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
	MUSIC musicShot;

	BOOL CanShot;
	int ShotReLoadCnt;
	int ShotReLoadCntMAX;


	int CenterX;
	int CenterY;

	int speed;
	TAMA tama[TAMA_MAX];

	RECT coll;


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

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int width;
	int height;
}MAP;





int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;


char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

//スコア
int score;

FONT FontTanu32;

int GameScene;

//スクロールのスピード
int scrollspeed = 1;

int PlayerX, PlayerY;
int PlayerGraph;

MUSIC BGM;
MUSIC BGM_TITLE;//タイトルBGM

IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;



IMAGE ImageBack;
CHARA player;
IMAGE ImageStumei;
IMAGE END;



GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		k,k,k,k,k,k,t,t,t,t,t,t,k,	// 0準備2
		k,t,t,t,t,k,t,t,t,c,t,t,k,	// 1
		k,t,t,t,t,k,b,t,t,t,t,t,k,	// 2
		k,t,t,t,t,k,t,t,t,t,b,t,k,	// 3
		k,t,t,t,t,k,t,t,t,t,t,t,k,	// 4
		k,t,c,t,t,k,t,t,t,t,t,t,k,	// 5
		k,t,b,t,t,k,c,t,t,t,t,t,k,	// 6
		k,t,t,t,t,k,t,t,t,t,t,t,k,	// 7
		k,t,t,t,t,k,t,t,t,t,t,t,k,	// 8	

		//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		k,t,t,t,t,t,t,t,t,c,t,t,k,	// 0準備2
		k,t,t,t,t,b,t,t,t,t,t,t,k,	// 1
		k,k,k,k,t,t,k,k,k,k,k,k,k,	// 2
		k,t,t,k,t,t,t,t,t,t,k,t,k,	// 3
		k,t,t,t,t,t,t,t,t,c,t,t,k,	// 4
		k,t,t,t,t,t,k,k,k,k,k,k,k,	// 5
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 7
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 8

		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 0準備1
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 1
		k,k,k,k,t,t,k,k,k,k,k,k,k,	// 2
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 3
		k,t,t,t,b,t,t,t,t,t,t,t,k,	// 4
		k,t,c,t,t,t,t,t,t,t,t,t,k,	// 5
		k,t,t,t,t,t,c,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 7
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 8

		k,t,t,t,t,t,b,t,t,t,t,t,k,	// 0描画
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 1
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 2
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 3
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 4
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 5
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 7
		k,k,k,k,k,k,k,k,k,k,k,k,k	// 8
};


GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];


MAPCHIP mapChip;


MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//ステージ当たり判定
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_DRAW(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);



BOOL MY_FONT_INSTALL_ONCE(VOID);
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);
VOID MY_FONT_DELETE(VOID);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_Explanation(VOID);
VOID MY_Explanation_PROC(VOID);//ゲーム説明の処理
VOID MY_Explanation_DRAW(VOID);//ゲーム画面の描画

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

//BGM
BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

//ステージ当たり判定
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

VOID MY_CHECK_MAP1_TAMA_COLL(VOID);//弾当たり判定








int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));
	SetAlwaysRunFlag(TRUE);
	SetWindowIconID(IDI_ICON1);
	int Key;

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;

	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }

	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_Explanation:
			MY_Explanation();
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

	if (CountFps == SampleNumFps)
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
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	return;
}


VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{


	char TempKey[256];


	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;
		}
	}
	return;
}


BOOL MY_KEY_DOWN(int KEY_INPUT_)
{

	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1
		&& AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{

	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
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

	//エンターキーを押したら、プレイシーン
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//プレイヤーの最初の位置
		player.CenterX = GAME_WIDTH / 2;	//画面の中心
		player.CenterY = GAME_HEIGHT / 2;	//画面の中心

		player.x = player.CenterX - player.width / 2;
		player.y = player.CenterY - player.height / 2;

		//弾の位置を元に戻す
		for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		{
				player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;
				player.tama[cnt].y = player.y;
				player.tama[cnt].IsDraw = FALSE;
		}

		//マップを上にずらす
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{

				//位置を元に戻す
				map[tate][yoko].y = tate * map[tate][yoko].height;

				mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
				mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;

				//マップを上にずらす
				map[tate][yoko].y -= GAME_MAP_TATE_MAX / 2 * map[tate][yoko].height;

				//当たり判定をずらす
				mapColl[tate][yoko].top -= GAME_MAP_TATE_MAX / 2 * map[tate][yoko].height;
				mapColl[tate][yoko].bottom -= GAME_MAP_TATE_MAX / 2 * map[tate][yoko].height;
			}
		}


		GameScene = GAME_SCENE_Explanation;

	


		return;
	}



	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}


	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{



		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{

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
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,
		ImageTitleROGO.rate,
		ImageTitleROGO.angle,
		ImageTitleROGO.image.handle, TRUE);


	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//タイトルスタートの描画
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	DrawString(0, 0, "スタート画面(ENTERキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

VOID MY_Explanation(VOID)
{
	MY_Explanation_PROC();	//説明画面の処理
	MY_Explanation_DRAW();	//説明画面の描画

	return;
}

//説明画面の処理
VOID MY_Explanation_PROC(VOID)
{
	//エスケープキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGMを止める
		}
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//説明画面の描画
VOID MY_Explanation_DRAW(VOID)
{
	DrawGraph(ImageStumei.x, ImageStumei.y, ImageStumei.handle, TRUE);
	/*DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(255, 0, 0), TRUE);*/

	DrawString(0, 0, "スタート画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
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
	//ESCキーを押したら、エンドシーンへ移動する
	//if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	//{
	//	if (CheckSoundMem(BGM.handle) != 0)
	//	{
	//		StopSoundMem(BGM.handle);
	//	}

	//	SetMouseDispFlag(TRUE);

	//	GameScene = GAME_SCENE_END;
	//	return;
	//}

	if (CheckSoundMem(BGM.handle) == 0)
	{
		
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	

	
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}
	//キー上
	if (MY_KEY_DOWN(KEY_INPUT_UP))
	{
		player.CenterY -= CHARA_SPEED_MIDI;
	}
	else if (KEY_INPUT_UP)
	{
		if (player.CenterY < GAME_HEIGHT / 2)
		{
			player.CenterY += CHARA_SPEED_MIDI;
		}
	}
	//キー下
	if (MY_KEY_DOWN(KEY_INPUT_DOWN))
	{
		player.CenterY += CHARA_SPEED_MIDI;
	}
	else if (KEY_INPUT_DOWN)
	{
		if (player.CenterY > GAME_HEIGHT / 2)
		{
			player.CenterY -= CHARA_SPEED_MIDI;
		}
	}
	//キー左
	if (MY_KEY_DOWN(KEY_INPUT_LEFT))
	{
		player.CenterX -= CHARA_SPEED_MIDI;
	}
	else if (KEY_INPUT_LEFT) {
		if (player.CenterX < GAME_WIDTH / 2)
		{
			player.CenterX += CHARA_SPEED_MIDI;
		}
	}
	//キー右
	if (MY_KEY_DOWN(KEY_INPUT_RIGHT))
	{
		player.CenterX += CHARA_SPEED_MIDI;
	}
	else if (KEY_INPUT_RIGHT)
	{
		if (player.CenterX > GAME_WIDTH / 2)
		{
			player.CenterX -= CHARA_SPEED_MIDI;
		}
	}

	if (player.x < 0) { player.x = 0; }
	if (player.x + player.width > GAME_WIDTH) { player.x = GAME_WIDTH - player.width; }
	if (player.y < 0) { player.y = 0; }
	if (player.y + player.height > GAME_HEIGHT) { player.y = GAME_HEIGHT - player.height; }


	//マップのスクロール
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			map[tate][yoko].y += scrollspeed;

			//当たり判定をずらす
			mapColl[tate][yoko].top += scrollspeed;
			mapColl[tate][yoko].bottom += scrollspeed;
		}
	}


	//プレイヤーの位置を更新
	player.x = player.CenterX - player.width / 2;
	player.y = player.CenterY - player.height / 2;

	//ステージ当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 15;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 15;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 10;

	//スペースキーで球が出る
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{

		if (player.CanShot == TRUE)
		{

			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{

					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;


					player.tama[cnt].y = player.y;


					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}

		}
	}



	//ショット
	if (player.CanShot == FALSE)
	{

		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;
		}

		player.ShotReLoadCnt++;	//リロードする
	}

	//当たり判定
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		GameScene = GAME_SCENE_END;
		return;
	}

	//弾の当たり判定
	MY_CHECK_MAP1_TAMA_COLL();

	return;
}


//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{

	//背景を描画
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);



	//マップ描画
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}
	//ステージ当たり判定
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (map[tate][yoko].kind == k)
			{
				/*DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom,FALSE);*/
			}

			//浮遊物
			if (map[tate][yoko].kind == b)
			{
				//DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom,/* GetColor(255, 255, 255),*/ FALSE);
			}

			//通路ならば
			if (map[tate][yoko].kind == t)
			{
				//DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, /*GetColor(0, 255, 0),*/ FALSE);
			}
		}
	}

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		if (player.tama[cnt].IsDraw == TRUE)
		{
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],
				TRUE);

			//当たり判定
			//DrawBox(
			//	player.tama[cnt].x,
			//	player.tama[cnt].y,
			//	player.tama[cnt].x + player.tama[cnt].width,
			//	/*player.tama[cnt].y + player.tama[cnt].height, GetColor(0, 0, 255), FALSE);*/

			if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
			{
				player.tama[cnt].changeImageCnt++;
			}
			else
			{
				if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)
				{
					player.tama[cnt].nowImageKind++;
				}
				else
				{
					player.tama[cnt].nowImageKind = 0;
				}

				player.tama[cnt].changeImageCnt = 0;
			}


			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}
		}
	}

	//プレイヤー描画
	DrawGraph(player.x, player.y, player.handle, TRUE);
	/*DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);*/

	//スコア
	DrawFormatString(0, 0, GetColor(0, 0, 0), "スコア: %05d",score);

	/*DrawString(0, 0, "プレイ画面(ESCキーを押して下さい)", GetColor(255, 255, 255));*/
	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//スペースキーでスタート画面
	/*if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;
	}*/

	return;
}

//エンド画面描画
VOID MY_END_DRAW(VOID)
{
	DrawGraph(END.x, END.y, END.handle, TRUE);
	//DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);
	//スコア
	DrawFormatString(350, 315, GetColor(0, 0, 0), ": %05d", score);
	/*DrawString(0, 0, "エンド画面(スペースキーを押して下さい)", GetColor(255, 255, 255));*/

	return;
}


BOOL MY_LOAD_IMAGE(VOID)
{

	strcpy_s(END.path, IMAGE_END_PATH);
	END.handle = LoadGraph(END.path);
	if (ImageTitleBK.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(END.handle, &END.width, &END.height);
	END.x = GAME_WIDTH / 2 - END.width / 2;
	END.y = GAME_HEIGHT / 2 - END.height / 2;



	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;


	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
	if (ImageTitleROGO.image.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
	ImageTitleROGO.image.x = 230;
	ImageTitleROGO.image.y = GAME_HEIGHT / 2;
	ImageTitleROGO.angle = DX_PI * 2;
	ImageTitleROGO.angleMAX = DX_PI * 2;
	ImageTitleROGO.rate = 0.0;
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;


	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);
	if (ImageTitleSTART.image.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;
	ImageTitleSTART.Cnt = 0.0;
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;
	ImageTitleSTART.IsDraw = FALSE;


	strcpy_s(ImageStumei.path, IMAGE_SETUMEI_PATH);
	ImageStumei.handle = LoadGraph(ImageStumei.path);
	if (ImageStumei.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_SETUMEI_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageStumei.handle, &ImageStumei.width, &ImageStumei.height);
	ImageStumei.x = GAME_WIDTH / 10 - ImageStumei.width / 10;
	ImageStumei.y = GAME_HEIGHT / 10 - ImageStumei.height / 10;

	strcpy_s(ImageBack.path, IMAGE_BACK_PATH);
	ImageBack.handle = LoadGraph(ImageBack.path);
	if (ImageBack.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;
	strcpy_s(player.path, IMAGE_PLAYER_PATH);
	player.handle = LoadGraph(player.path);
	if (player.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.handle, &player.width, &player.height);
	player.x = GAME_WIDTH / 2 - player.width / 2;
	player.y = GAME_HEIGHT / 2 - player.height / 2;
	player.CenterX = player.x + player.width / 2;
	player.CenterY = player.y + player.height / 2;
	player.speed = CHARA_SPEED_LOW;

	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.tama[0].handle[0]);


	if (tamaRedRes == -1)
	{

		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}


	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);


	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{

		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{

			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}


		player.tama[cnt].width = player.tama[0].width;


		player.tama[cnt].height = player.tama[0].height;


		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;


		player.tama[cnt].y = player.y;


		player.tama[cnt].IsDraw = FALSE;


		player.tama[cnt].changeImageCnt = 0;


		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;


		player.tama[cnt].nowImageKind = 0;


		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}





	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1)
	{

		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}


	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			mapDataInit[tate][yoko] = mapData[tate][yoko];


			map[tate][yoko].kind = mapData[tate][yoko];


			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;


			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}
	//ステージ当たり判定
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}
	return TRUE;
}




//ステージ当たり判定
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁当たり判定
				if (map[tate][yoko].kind == k){
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}
					SetMouseDispFlag(TRUE);		
					GameScene = GAME_SCENE_END;

					return TRUE;
				}

				//ビン当たり判定
				if (map[tate][yoko].kind == b) {

					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					SetMouseDispFlag(TRUE);		

					GameScene = GAME_SCENE_END;
					return TRUE;
				}

				//コイン当たり判定
				if (map[tate][yoko].kind == c) { 


					if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
					{
						//コイン当たり判定
						if (map[tate][yoko].kind == c)
						{
							map[tate][yoko].kind = t;
							score += 100;//スコア
						}
						
					}

					return FALSE;
				}



			}
		}
	}

	return FALSE;
}

//弾当たり判定
VOID MY_CHECK_MAP1_TAMA_COLL(VOID)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == TRUE)
				{
					RECT ChechTama;//弾の当たり判定の領域
					ChechTama.left = player.tama[cnt].x;
					ChechTama.top = player.tama[cnt].y;
					ChechTama.right = player.tama[cnt].x + player.tama[cnt].width;
					ChechTama.bottom = player.tama[cnt].y + player.tama[cnt].height;
	
					if (MY_CHECK_RECT_COLL(ChechTama, mapColl[tate][yoko]) == TRUE)
					{
						//ビン当たり判定
						if (map[tate][yoko].kind == b)
						{
							map[tate][yoko].kind = t;
							
							player.tama[cnt].IsDraw = FALSE;

						}
					}
				}
			}
		}
	}

	return;
}



BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;
	}

	return FALSE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{

	DeleteGraph(player.handle);

	DeleteGraph(END.handle);
	DeleteGraph(ImageStumei.handle);
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}


BOOL MY_LOAD_MUSIC(VOID)
{
	//プレ画面BGM
	strcpy_s(BGM.path, MUSIC_BGM_PATH);
	BGM.handle = LoadSoundMem(BGM.path);
	if (BGM.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ショットGBM
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);
	if (player.musicShot.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//タイトルBGM
	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);
	if (BGM_TITLE.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(player.musicShot.handle);

	DeleteSoundMem(BGM_TITLE.handle);//タイトルBGM

	return;
}