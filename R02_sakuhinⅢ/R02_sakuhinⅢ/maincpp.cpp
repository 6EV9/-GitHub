/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キー入力


#include "DxLib.h"
#include "resource.h"


#define GAME_WIDTH			800	
#define GAME_HEIGHT			600	
#define GAME_COLOR			32	

#define GAME_WINDOW_BAR		0	
#define GAME_WINDOW_NAME	"GAME TITLE"	

#define GAME_FPS			60	

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};

int StartTimeFps;				
int CountFps;					
float CalcFps;					
int SampleNumFps = GAME_FPS;	




char AllKeyState[256] = { '\0' };		
char OldAllKeyState[256] = { '\0' };	


int GameScene;

VOID MY_FPS_UPDATE(VOID);			
VOID MY_FPS_DRAW(VOID);				
VOID MY_FPS_WAIT(VOID);				



VOID MY_ALL_KEYDOWN_UPDATE(VOID);	
BOOL MY_KEY_DOWN(int);				
BOOL MY_KEY_UP(int);			
BOOL MY_KEYDOWN_KEEP(int, int);	

VOID MY_START(VOID);		
VOID MY_START_PROC(VOID);	
VOID MY_START_DRAW(VOID);	

VOID MY_PLAY(VOID);			
VOID MY_PLAY_PROC(VOID);	
VOID MY_PLAY_DRAW(VOID);	

VOID MY_END(VOID);			
VOID MY_END_PROC(VOID);		
VOID MY_END_DRAW(VOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	
	SetWindowStyleMode(GAME_WINDOW_BAR);		
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	
	SetAlwaysRunFlag(TRUE);						
	SetWindowIconID(IDI_ICON1);					

	if (DxLib_Init() == -1) { return -1; }	

	int DrawX = 0;	
	int DrawY = 0;	

	SetDrawScreen(DX_SCREEN_BACK);	

	GameScene = GAME_SCENE_START;

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	
		if (ClearDrawScreen() != 0) { break; }	

		

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		

		MY_FPS_UPDATE();	

		/*DrawString(DrawX, DrawY, "Hello World", GetColor(255, 255, 255));*/

		

		//試しにキー入力をしてみよう
		if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) { DrawY--; }
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE) { DrawY++; }
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE) { DrawX--; }
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) { DrawX++; }

		
	/*	DrawFormatString(0, 0, GetColor(255, 255, 255), "DrawX:%d", DrawX);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "DrawY:%d", DrawY);*/

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
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

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

//キーを押し上げたか、

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
VOID MY_START(VOID)
{
	MY_START_PROC();	
	MY_START_DRAW();	

	return;
}


VOID MY_START_PROC(VOID)
{
	
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}


VOID MY_START_DRAW(VOID)
{
	
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(255, 0, 0), TRUE);

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}


VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();	

	return;
}


VOID MY_PLAY_PROC(VOID)
{
	
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		GameScene = GAME_SCENE_END;
	}

	return;
}


VOID MY_PLAY_DRAW(VOID)
{
	
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 255, 0), TRUE);

	DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));
	return;
}


VOID MY_END(VOID)
{
	MY_END_PROC();	
	MY_END_DRAW();
	return;
}


VOID MY_END_PROC(VOID)
{
	
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}


VOID MY_END_DRAW(VOID)
{
	
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}


