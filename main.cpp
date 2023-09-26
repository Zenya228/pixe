
#include <Windows.h>
#include "Application\Application.h"

// Главная функция программы
int _stdcall WinMain(HINSTANCE _appInstance,HINSTANCE,LPSTR,int)
{
	Application* app=Application::GetInstance();
	int result=app->Init(_appInstance);

	app->Release();

	return result;
}