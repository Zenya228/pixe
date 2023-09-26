
#include "Application.h"

Application* Application::instance=0;

Application::Application(void)
{
	isExit=false;
	gdiPlus=0;
	iconNormal=0;
	iconSmall=0;
	appInstance=0;
	window=0;
	backgroundWindow=0;

	fieldManager=0;
}

Application::~Application(void)
{
	if(window)
	{
		DestroyWindow(window);
		window=0;
	}

	if(backgroundWindow)
	{
		DeleteObject(backgroundWindow);
		backgroundWindow=0;
	}

	if(iconNormal)
	{
		DestroyIcon(iconNormal);
		iconNormal=0;
	}

	if(iconSmall)
	{
		DestroyIcon(iconSmall);
		iconSmall=0;
	}

	if(fieldManager)
	{
		fieldManager->Release();
		fieldManager=0;
	}

	if(gdiPlus)
	{
		GdiplusShutdown(gdiPlus);
		gdiPlus=0;
	}
}

Application* Application::GetInstance(void)
{
	if(!instance) instance=new Application();

	return instance;
}

void Application::Release(void)
{
	if(instance)
	{
		delete instance;
		instance=0;
	}
}

HINSTANCE Application::GetAppInstance(void) const
{
	return appInstance;
}

HWND Application::GetWindow(void) const
{
	return window;
}

HICON Application::GetIconNormal(void) const
{
	return iconNormal;
}

HICON Application::GetIconSmall(void)const
{
	return iconSmall;
}

HBRUSH Application::GetBackgroundWindow(void) const
{
	return backgroundWindow;
}

void Application::SetExit(void)
{
	isExit=true;
}

void Application::SetMouse(const int _mouseX,const int _mouseY)
{
	fieldManager->HitMouseMove(_mouseX,_mouseY);
}

void Application::FieldsHitDownL(const int _mouseX,const int _mouseY)
{
	fieldManager->HitMouseDownL(_mouseX,_mouseY);
}

void Application::FieldsHitUpL(const int _mouseX,const int _mouseY)
{
	fieldManager->HitMouseUpL(_mouseX,_mouseY);
}

void Application::FieldsHitDownR(const int _mouseX,const int _mouseY)
{
	fieldManager->HitMouseDownR(_mouseX,_mouseY);
}

void Application::FieldsHitUpR(const int _mouseX,const int _mouseY)
{
	fieldManager->HitMouseUpR(_mouseX,_mouseY);
}

int Application::Loop(void)
{
	MSG message;

	memset(&message,0,sizeof(MSG));

	while(!isExit)
	{
		if(GetMessage(&message,window,0,0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return 0;
}

long _stdcall Application::WinMessage(HWND _window,UINT _message,WPARAM _wParam,LPARAM _lParam)
{
	Application* app=Application::GetInstance();
	FieldManager* fieldManager=FieldManager::GetInstance();
	HDC hdc;
	PAINTSTRUCT ps;

	switch(_message)
	{
		case WM_INITDIALOG:
			SetClassLong(_window,GCL_HICON,(LONG)app->GetIconNormal());
			SetClassLong(_window,GCL_HICONSM,(LONG)app->GetIconSmall());
			break;

		case WM_CTLCOLORDLG:
			return (long)app->GetBackgroundWindow();
			return (long)0;

		case WM_PAINT:
			hdc=BeginPaint(_window,&ps);
			app->Paint(hdc);
			EndPaint(_window,&ps);
			break;

		case WM_MOUSEMOVE:
			app->SetMouse(LOWORD(_lParam),HIWORD(_lParam));
			break;

		case WM_LBUTTONDOWN:
			app->FieldsHitDownL(LOWORD(_lParam),HIWORD(_lParam));
			break;

		case WM_LBUTTONUP:
			app->FieldsHitUpL(LOWORD(_lParam),HIWORD(_lParam));
			break;

		case WM_RBUTTONDOWN:
			app->FieldsHitDownR(LOWORD(_lParam),HIWORD(_lParam));
			break;

		case WM_RBUTTONUP:
			app->FieldsHitUpR(LOWORD(_lParam),HIWORD(_lParam));
			break;

		case WM_COMMAND:
			switch(LOWORD(_wParam))
			{
				case ID_SMI_NEW_GAME_1:
					fieldManager->Create(10,10,20);
					break;

				case ID_SMI_NEW_GAME_2:
					fieldManager->Create(15,15,45);
					break;

				case ID_SMI_NEW_GAME_3:
					fieldManager->Create(20,20,100);
					break;

				case ID_SMI_NEW_GAME_4:
					fieldManager->Create(25,25,200);
					break;

				case ID_SMI_EXIT:
					SendMessage(_window,WM_CLOSE,0,0);
					break;
			}
			break;

		case WM_CLOSE:
			app->SetExit();
			break;
	}

	return 0;
}

void Application::Paint(HDC _hdc)
{
	fieldManager->Paint();
}

int Application::Init(const HINSTANCE _appInstance)
{
	GdiplusStartupInput gdiPlusStartupInput;

	appInstance=_appInstance;
   
	GdiplusStartup(&gdiPlus,&gdiPlusStartupInput,0);

	if((iconNormal=LoadIcon(appInstance,MAKEINTRESOURCE(IDI_ICON1)))==0)
	{
		MessageBox(0,"Не удаётся загрузить иконку окна для панели задач. Игра будет закрыта.","Ошибка!",MB_ICONERROR);
		return 1;
	}

	if((iconSmall=LoadIcon(appInstance,MAKEINTRESOURCE(IDI_ICON_SMALL)))==0)
	{
		MessageBox(0,"Не удаётся загрузить иконку окна для окна. Игра будет закрыта.","Ошибка!",MB_ICONERROR);
		return 1;
	}

	backgroundWindow=CreateSolidBrush(RGB(32,128,192));

	if((window=CreateDialog(appInstance,MAKEINTRESOURCE(IDD_MAIN_WINDOW),0,(DLGPROC)&WinMessage))==0)
	{
		MessageBox(0,"Не удаётся создать главное окно. Игра будет закрыта.","Ошибка!",MB_ICONERROR);
		return 1;
	}

	fieldManager=FieldManager::GetInstance();

	if(fieldManager->Init(appInstance,window))
	{
		MessageBox(0,"Не удаётся загрузить ресурсы игры. Игра будет закрыта.","Ошибка!",MB_ICONERROR);
		return 1;
	}

	fieldManager->Create(10,10,20);

	UpdateWindow(window);
	ShowWindow(window,SW_SHOW);

	return Loop();
}