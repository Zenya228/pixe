
#pragma once;

#include <Windows.h>
#include <GdiPlus.h>
#include "../../resource.h"

using namespace Gdiplus;

class Field
{
	private:
		static HINSTANCE appInstance;
		static HWND window;
		static HDC hdc;

		static Bitmap* bitmapFieldCloseOut;
		static Bitmap* bitmapFieldCloseOver;
		static Bitmap* bitmapFieldCloseDown;

		static Bitmap* bitmapFieldFlagOut;
		static Bitmap* bitmapFieldFlagOver;
		static Bitmap* bitmapFieldFlagDown;

		static Bitmap* bitmapFieldDoubtOut;
		static Bitmap* bitmapFieldDoubtOver;
		static Bitmap* bitmapFieldDoubtDown;

		static Bitmap* bitmapFieldEmptily;

		static Bitmap* bitmapField1;
		static Bitmap* bitmapField2;
		static Bitmap* bitmapField3;
		static Bitmap* bitmapField4;
		static Bitmap* bitmapField5;
		static Bitmap* bitmapField6;
		static Bitmap* bitmapField7;
		static Bitmap* bitmapField8;

		static Bitmap* bitmapFieldMine;

		bool isOpen;
		bool isOver;
		bool isDownL;
		bool isDownR;
		bool isFind;

		int x;
		int y;

		unsigned int indexX;
		unsigned int indexY;

		unsigned int entity;
		unsigned int comment;

	public:
		Field(void);
		~Field(void);

		static bool Init(const HINSTANCE _appInstance,const HWND _window,const HDC _hdc);
		static void End(void);

		bool GetIsOpen(void) const;

		int GetX(void) const;
		int GetY(void) const;

		void SetPosition(const int _x,const int _y);

		unsigned int GetIndexX(void) const;
		unsigned int GetIndexY(void) const;

		void SetIndex(const unsigned int _indexX,const unsigned int _indexY);

		unsigned int GetEntity(void) const;
		unsigned int GetComment(void) const;

		void SetEntity(const unsigned int _entity);

		void SetIsFind(const bool _isFind);
		bool GetIsFind(void);

		void Open(void);
		void Close(void);

		void HitMouseOver(const int _mouseX,const int _mouseY);
		void HitMouseDownL(const int _mouseX,const int _mouseY);
		bool HitMouseUpL(const int _mouseX,const int _mouseY);
		void HitMouseDownR(const int _mouseX,const int _mouseY);
		bool HitMouseUpR(const int _mouseX,const int _mouseY);

		void Draw(void) const;
};