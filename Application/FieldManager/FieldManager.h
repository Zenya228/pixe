
#pragma once

#include <time.h>
#include "../Field/Field.h"

class FieldManager
{
	private:
		static FieldManager* instance;

		HINSTANCE appInstance;
		HWND window;

		unsigned int fieldWidht;
		unsigned int fieldHeight;
		unsigned int fieldCount;
		Field* fields;

		unsigned int mines;
		unsigned int openFields;

		FieldManager(void);
		~FieldManager(void);

		void Random(void);
		void FieldFindMines(Field* _field);
		void FieldFindEmptily(Field* _field);

		void End(void);

	public:
		static FieldManager* GetInstance(void);

		void Release(void);

		bool Init(const HINSTANCE _appInstance,const HWND _window);

		void Create(const unsigned int _width,const unsigned int _height,const unsigned int _mines);
		void Delete(void);

		void HitMouseMove(const int _mouseX,const int _mouseY) const;
		void HitMouseDownL(const int _mouseX,const int _mouseY) const;
		void HitMouseUpL(const int _mouseX,const int _mouseY);
		void HitMouseDownR(const int _mouseX,const int _mouseY) const;
		void HitMouseUpR(const int _mouseX,const int _mouseY) const;

		unsigned int GetWidth(void) const;
		unsigned int GetHeight(void) const;
		unsigned int GetFieldCount(void) const;

		Field* GetField(const unsigned int _i,const unsigned int _j) const;
		unsigned int GetEntity(const unsigned int _i,const unsigned int _j) const;
		unsigned int GetComment(const unsigned int _i,const unsigned int _j) const;

		void SetEntity(const unsigned int _i,const unsigned int _j,const unsigned int _entity);

		void Paint(void);
};