#include "Engine.h"
#include "interface.h"
#include "GameMain.h"


#include "Console.h"
#include "direct.h"
#include "HMDWrapper.h"

#include "EngineConsole.h"
#include "FileSystem.h"

int main(int argc, char* argv[])
{
#ifdef USE_HMD		
	g_pHMD->Init();
	int useHmd = g_pHMD->GetUseHMD();
	if (useHmd)
	{
		//ͷ��3d
		render_stereo = 2;

		//�Զ��崰�ڷֱ��� ��ͷ���ֱ���һֱ
		video_mode = -1;
		video_width = 2160;
		video_height = 1200;

		// ȫ����ʽ 0������    1��ȫ��
		video_fullscreen = 0;

		video_resizable = 0;
		video_vsync = 0;
	}

}