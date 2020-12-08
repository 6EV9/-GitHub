
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
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")		


#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")


#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")


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

#define MUSIC_LOAD_ERR_TITLE TEXT("���y�ǂݍ��݃G���[")

#define MUSIC_BGM_PATH            TEXT(".\\MUSIC\\BGMpaly.mp3")
#define MUSIC_PLAYER_SHOT_PATH TEXT(".\\MUSIC\\SHOT.mp3")
#define MUSIC_BGM_TITLE_PATH		TEXT(".\\MUSIC\\BGMSTR.mp3")	

#define GAME_MAP_TATE_MAX	9	
#define GAME_MAP_YOKO_MAX	13	
#define GAME_MAP_KIND_MAX	2	

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")		

#define MAP_DIV_WIDTH		64	
#define MAP_DIV_HEIGHT		64	
#define MAP_DIV_TATE		10	
#define MAP_DIV_YOKO		4	
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	


#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")


#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

#define TAMA_CHANGE_MAX 5
#define TAMA_MAX       16

#define TAMA_CHANGE_MAX		 5	//5�t���[���ڂŒe�̉摜��ς���
#define TAMA_MAX			16	//�ő�16���܂�

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\tama.png")		//�Ԓe�̉摜

#define TAMA_DIV_WIDTH		16	//�摜�𕪊����镝�T�C�Y
#define TAMA_DIV_HEIGHT		16	//�摜�𕪊����鍂���T�C�Y

#define TAMA_DIV_TATE		3	//�摜���c�ɕ������鐔
#define TAMA_DIV_YOKO		1	//�摜�����ɕ������鐔

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO

#define GAME_MAP_TATE_MAX	9	
#define GAME_MAP_YOKO_MAX	13	
#define GAME_MAP_KIND_MAX	2	

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")		

#define MAP_DIV_WIDTH		64	
#define MAP_DIV_HEIGHT		64	
#define MAP_DIV_TATE		10	
#define MAP_DIV_YOKO		4	
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	


#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define KEY_RETURN_CLICK_TITLE		TEXT("�Q�[�����f")
#define KEY_RETURN_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	k = 10,	//��
	k2 = 11,//��
	k3 = 13,//��

	t = 33,	//�ʘH
	s = 32,	//�X�^�[�g
	g = 3	//�S�[��
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//�L�����N�^�[�̃X�s�[�h

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//�L�����N�^�[�̃����[�h


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
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;

	MUSIC musicShot;

	BOOL CanShot;
	int ShotReLoadCnt;
	int ShotReLoadCntMAX;

	RECT coll;
	iPOINT collBeforePt;

	TAMA tama[TAMA_MAX];

	
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


MOUSE mouse;

FONT FontTanu32;

int GameScene;



int PlayerX, PlayerY;
int PlayerGraph;



IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;


IMAGE ImageBack;
CHARA player;


MUSIC BGM;
MUSIC BGM_TITLE;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 0
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 1
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 2
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 3
		k,k,k,k,t,k,k,k,k,k,k,k,k,// 4
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 5
		k,t,t,t,t,t,s,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 7
		k,k,k,k,k,k,k,k,k,k,k,k,k,	// 8
};	


GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];


MAPCHIP mapChip;



MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

iPOINT startPt{ -1,-1 };

RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_DRAW(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	
BOOL MY_KEY_DOWN(int);				
BOOL MY_KEY_UP(int);				
BOOL MY_KEYDOWN_KEEP(int, int);		

//VOID MY_MOUSE_UPDATE(VOID);			
//BOOL MY_MOUSE_DOWN(int);			
//BOOL MY_MOUSE_UP(int);				
//BOOL MY_MOUSEDOWN_KEEP(int, int);	

BOOL MY_FONT_INSTALL_ONCE(VOID);
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);
VOID MY_FONT_DELETE(VOID);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

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
	int Key;

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	int DrawX = 0;
	int DrawY = 0;



	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }





	//�v���C���[�̐ݒ�
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;


	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);

	GameScene = GAME_SCENE_START;



	PlayerX = 0;
	PlayerY = 0;

	SetDrawScreen(DX_SCREEN_BACK);	





	
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			
			if (mapData[tate][yoko] == s)
			{
				
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	
				startPt.y = mapChip.height * tate + mapChip.height / 2;
				break;
			}
		}
		
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}
	

	if (startPt.x == -1 && startPt.y == -1)
	{
		
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();










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

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
	SetMouseDispFlag(FALSE);
	player.CenterX = startPt.x;
	player.CenterY = startPt.y;


	player.image.x = player.CenterX;
	player.image.y = player.CenterY;
	SetMousePoint(player.image.x, player.image.y);

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
		}

		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_PLAY;

		return;
	}



	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{

		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
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

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);	//�^�C�g���w�i�̕`��


	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,	
		ImageTitleROGO.rate,							
		ImageTitleROGO.angle,							
		ImageTitleROGO.image.handle, TRUE);				

	
	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//�^�C�g���X�^�[�g�̕`��
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	DrawString(0, 0, "�X�^�[�g���(ENTER�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	//ESC�L�[����������A�G���h�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{


		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		

		GameScene = GAME_SCENE_END;
		return;
	}

	if (CheckSoundMem(BGM.handle) == 0)
	{

		ChangeVolumeSoundMem(255 *100 / 100, BGM.handle);	//50%�̉��ʂɂ���


		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		
		(BGM.handle, DX_PLAYTYPE_LOOP);
	}
	
    
	BOOL IsMove = TRUE;

	
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		IsMove = FALSE;
	}

	

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

	


	if (MY_KEY_DOWN(KEY_INPUT_LEFT))
	{
		player.CenterX -= CHARA_SPEED_MIDI;
	}
	else if (KEY_INPUT_LEFT) {

	}
		if(player.CenterX < GAME_WIDTH/2)
		{
			player.CenterX += CHARA_SPEED_MIDI;
		}

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


	player.coll.left = player.CenterX - mapChip.width / 2 + 15;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 15;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 10;




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


					player.tama[cnt].y = player.image.y;


					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}
		}
	}

	//for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	//{
	//	if (player.tama[cnt].IsDraw == FALSE)
	//	{
	//		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

	//		player.tama[cnt].y = player.image.y;

	//		player.tama[cnt].IsDraw = TRUE;
	//	}
	//}

	
	


	
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (player.CanShot == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;
		}
	}

	if (player.CanShot == FALSE)
	{
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;
		}
		player.ShotReLoadCnt++;
	}





	return;
}


//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{

	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);
	
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData[tate][yoko] == k)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}

	
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);


	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		
		if (player.tama[cnt].IsDraw == TRUE)
		{
			
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],	
				TRUE);

			
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

	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						
		&mapChip.handle[0]);								

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return;
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

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
		
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}
	//�v���C���[��`�悷��(�摜�������L�΂��ĕ`�恦�������ׂ������I���p�ɒ��ӁI)
	//DrawExtendGraph(
	//	player.image.x, player.image.y,														//�R�R����
	//	player.image.x + player.image.width * 2, player.image.y + player.image.height * 2,	//�R�R�܂ň����L�΂�
	//	player.image.handle, TRUE);


	/*
	//�v���C���[��`�悷��(�摜���g���]���ĕ`�恦�������ׂ������I���p�ɒ��ӁI)
	DrawRotaGraph(
		player.image.x, player.image.y,
		2.0,							
		DX_PI * 2 / 4 * 2,				
		player.image.handle, TRUE);
	*/


	
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);




	DrawString(0, 0, "�v���C���(ESC�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	
	MY_END_DRAW();	
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʏ���
VOID MY_END_DRAW(VOID)
{

	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "�G���h���(�X�y�[�X�L�[�������ĉ�����)", GetColor(255, 255, 255));
	
	return;
}


BOOL MY_LOAD_IMAGE(VOID)
{




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

	
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{

		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		
	player.CenterX = player.image.x + player.image.width / 2;		
	player.CenterY = player.image.y + player.image.height / 2;		
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

		
		player.tama[cnt].y = player.image.y;

		
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

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}
	return TRUE;
}


VOID MY_DELETE_IMAGE(VOID)
{

	DeleteGraph(player.image.handle);



	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);

	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}


BOOL MY_LOAD_MUSIC(VOID)
{

	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);				
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);			
	if (BGM_TITLE.handle == -1)
	{
		
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

	//�v���C���[�̃V���b�g��
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);		
	if (player.musicShot.handle == -1)
	{
		
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}


VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(BGM_TITLE.handle);

	return;
}

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				
				if (map[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
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
