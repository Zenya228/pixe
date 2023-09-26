
#pragma once

#include <Windows.h>
#include <GdiPlus.h>
#include "../resource.h"
#include "FieldManager\FieldManager.h"

using namespace Gdiplus;

class Application
{
	private:
		static Application* instance;

		bool isExit;

		ULONG_PTR gdiPlus;

		HICON iconNormal;
		HICON iconSmall;

		HINSTANCE appInstance;
		HWND window;

		HBRUSH backgroundWindow;

		FieldManager* fieldManager;

		Application(void);
		~Application(void);

		int Loop(void);

		static long _stdcall WinMessage(
			HWND _window,
			UINT _message,
			WPARAM _wParam,
			LPARAM _lParam);

		void SetMouse(const int _mouseX,const int _mouseY);
		void FieldsHitDownL(const int _mouseX,const int _mouseY);
		void FieldsHitUpL(const int _mouseX,const int _mouseY);
		void FieldsHitDownR(const int _mouseX,const int _mouseY);
		void FieldsHitUpR(const int _mouseX,const int _mouseY);

		void Paint(HDC _hdc);

	public:
		static Application* GetInstance(void);

		void Release(void);

		HINSTANCE GetAppInstance(void)		const;
		HWND GetWindow(void)				const;

		HICON GetIconNormal(void)			const;
		HICON GetIconSmall(void)			const;

		HBRUSH GetBackgroundWindow(void)	const;

		void SetExit(void);

		int Init(const HINSTANCE _appInstance);
};

