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
	else
	{
		//��ͷ��
		render_stereo = 0;

		//�Զ��崰�ڷֱ���
		video_mode = -1;
		video_fullscreen = 0;
		video_width = 1280;
		video_height = 720;
		video_resizable = 0;
		video_vsync = 0;
	}
#else
	render_stereo = 0;

	video_mode = -1;	
	video_fullscreen = 0;	
	video_width = 1280;		
	video_height = 720;		
	video_resizable = 0;	
	video_vsync = 0;		
#endif

	char pAppPath[260];		
	getcwd(pAppPath, 260);
	strcat(pAppPath, "\\");

	CGameMain t_Game;

	CInterfaceBase *pInit = MakeInterface(&t_Game, &CGameMain::Init);
	CInterfaceBase *pUpdate = MakeInterface(&t_Game, &CGameMain::Update);
	CInterfaceBase *pShutdown = MakeInterface(&t_Game, &CGameMain::ShutDown);
	CInterfaceBase *pRender = MakeInterface(&t_Game, &CGameMain::Render);

	char *pArg[3] = { NULL, "-engine_config", "data/TestProject.cfg" };	//�������������ʲô�õģ���
	g_Engine.pEngine = new CEngine(NULL, pAppPath, NULL, NULL, 3, pArg, NULL, "1123581321", pInit);	//����CEngine��ĳ�ʼ�����Լ���ֵ��


}