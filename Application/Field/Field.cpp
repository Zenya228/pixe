
#include "Field.h"

HINSTANCE Field::appInstance=0;
HWND Field::window=0;
HDC Field::hdc=0;

Bitmap* Field::bitmapFieldCloseOut=0;
Bitmap* Field::bitmapFieldCloseOver=0;
Bitmap* Field::bitmapFieldCloseDown=0;

Bitmap* Field::bitmapFieldFlagOut=0;
Bitmap* Field::bitmapFieldFlagOver=0;
Bitmap* Field::bitmapFieldFlagDown=0;

Bitmap* Field::bitmapFieldDoubtOut=0;
Bitmap* Field::bitmapFieldDoubtOver=0;
Bitmap* Field::bitmapFieldDoubtDown=0;

Bitmap* Field::bitmapFieldEmptily=0;

Bitmap* Field::bitmapField1=0;
Bitmap* Field::bitmapField2=0;
Bitmap* Field::bitmapField3=0;
Bitmap* Field::bitmapField4=0;
Bitmap* Field::bitmapField5=0;
Bitmap* Field::bitmapField6=0;
Bitmap* Field::bitmapField7=0;
Bitmap* Field::bitmapField8=0;

Bitmap* Field::bitmapFieldMine=0;

Field::Field(void)
{
	isOpen=false;
	isOver=false;
	isDownL=false;
	isDownR=false;
	isFind=true;

	x=0;
	y=0;

	indexX=0;
	indexY=0;

	entity=0;
	comment=0;
}

Field::~Field(void)
{
}

bool Field::Init(const HINSTANCE _appInstance,const HWND _window,const HDC _hdc)
{
	appInstance=_appInstance;
	window=_window;
	hdc=_hdc;

	bitmapFieldCloseOut=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_CLOSE_OUT));
	bitmapFieldCloseOver=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_CLOSE_OVER));
	bitmapFieldCloseDown=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_CLOSE_DOWN));

	bitmapFieldFlagOut=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_FLAG_OUT));
	bitmapFieldFlagOver=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_FLAG_OVER));
	bitmapFieldFlagDown=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_FLAG_DOWN));

	bitmapFieldDoubtOut=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_DOUBT_OUT));
	bitmapFieldDoubtOver=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_DOUBT_OVER));
	bitmapFieldDoubtDown=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_DOUBT_DOWN));

	bitmapFieldEmptily=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_EMPTILY));

	bitmapField1=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD1));
	bitmapField2=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD2));
	bitmapField3=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD3));
	bitmapField4=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD4));
	bitmapField5=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD5));
	bitmapField6=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD6));
	bitmapField7=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD7));
	bitmapField8=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD8));

	bitmapFieldMine=new Bitmap(appInstance,MAKEINTRESOURCEW(IDB_FIELD_MINE));

	return false;
}

void Field::End(void)
{
	
	if(bitmapFieldCloseOut)
	{
		delete bitmapFieldCloseOut;
		bitmapFieldCloseOut=0;
	}

	if(bitmapFieldCloseOver)
	{
		delete bitmapFieldCloseOver;
		bitmapFieldCloseOver=0;
	}

	if(bitmapFieldCloseDown)
	{
		delete bitmapFieldCloseDown;
		bitmapFieldCloseDown=0;
	}

	if(bitmapFieldFlagOut)
	{
		delete bitmapFieldFlagOut;
		bitmapFieldFlagOut=0;
	}

	if(bitmapFieldFlagOver)
	{
		delete bitmapFieldFlagOver;
		bitmapFieldFlagOver=0;
	}

	if(bitmapFieldFlagDown)
	{
		delete bitmapFieldFlagDown;
		bitmapFieldFlagDown=0;
	}

	if(bitmapFieldDoubtOut)
	{
		delete bitmapFieldDoubtOut;
		bitmapFieldDoubtOut=0;
	}

	if(bitmapFieldDoubtOver)
	{
		delete bitmapFieldDoubtOver;
		bitmapFieldDoubtOver=0;
	}

	if(bitmapFieldDoubtDown)
	{
		delete bitmapFieldDoubtDown;
		bitmapFieldDoubtDown=0;
	}

	if(bitmapFieldEmptily)
	{
		delete bitmapFieldEmptily;
		bitmapFieldEmptily=0;
	}

	if(bitmapField1)
	{
		delete bitmapField1;
		bitmapField1=0;
	}

	if(bitmapField2)
	{
		delete bitmapField2;
		bitmapField2=0;
	}

	if(bitmapField3)
	{
		delete bitmapField3;
		bitmapField3=0;
	}

	if(bitmapField4)
	{
		delete bitmapField4;
		bitmapField4=0;
	}

	if(bitmapField5)
	{
		delete bitmapField5;
		bitmapField5=0;
	}

	if(bitmapField6)
	{
		delete bitmapField6;
		bitmapField6=0;
	}

	if(bitmapField7)
	{
		delete bitmapField7;
		bitmapField7=0;
	}

	if(bitmapField8)
	{
		delete bitmapField8;
		bitmapField8=0;
	}

	if(bitmapFieldMine)
	{
		delete bitmapFieldMine;
		bitmapFieldMine=0;
	}
}

bool Field::GetIsOpen(void) const
{
	return isOpen;
}

int Field::GetX(void) const
{
	return x;
}

int Field::GetY(void) const
{
	return y;
}

void Field::SetPosition(const int _x,const int _y)
{
	x=_x;
	y=_y;
}

unsigned int Field::GetIndexX(void) const
{
	return indexX;
}

unsigned int Field::GetIndexY(void) const
{
	return indexY;
}

void Field::SetIndex(const unsigned int _indexX,const unsigned int _indexY)
{
	indexX=_indexX;
	indexY=_indexY;
}

unsigned int Field::GetEntity(void) const
{
	return entity;
}

unsigned int Field::GetComment(void) const
{
	return comment;
}

void Field::SetEntity(const unsigned int _entity)
{
	entity=_entity;
}

void Field::SetIsFind(const bool _isFind)
{
	isFind=_isFind;
}

bool Field::GetIsFind(void)
{
	return isFind;
}

void Field::Open(void)
{
	isOpen=true;
	
	Draw();
}

void Field::Close(void)
{
	isOpen=false;

	Draw();
}

void Field::HitMouseOver(const int _mouseX,const int _mouseY)
{
	bool isOverOld=isOver;

	if(_mouseX>=x && _mouseX<=x+24 && _mouseY>=y && _mouseY<=y+24)
		isOver=true;
	else
		isOver=false;

	if(isOver!=isOverOld)
	{
		isDownL=false;
		isDownR=false;
		Draw();
	}
}

void Field::HitMouseDownL(const int _mouseX,const int _mouseY)
{
	bool isDownLOld=isDownL;

	if(comment==1) return;

	if(_mouseX>=x && _mouseX<=x+24 && _mouseY>=y && _mouseY<=y+24)
	{
		isOver=true;
		isDownL=true;
		isDownR=false;
	}
	else
	{
		isOver=false;
		isDownL=false;
		isDownR=false;
	}

	if(isDownL!=isDownLOld) Draw();
}

bool Field::HitMouseUpL(const int _mouseX,const int _mouseY)
{
	bool isDownLOld=isDownL;

	if(_mouseX>=x && _mouseX<=x+24 && _mouseY>=y && _mouseY<=y+24 && isDownL)
	{
		isOpen=true;
		isOver=true;
		isDownL=false;
		isDownR=false;
	}
	else
	{
		isOver=false;
		isDownL=false;
		isDownR=false;
	}

	if(isDownL!=isDownLOld)
	{
		Draw();
		return true;
	}

	return false;
}

void Field::HitMouseDownR(const int _mouseX,const int _mouseY)
{
	bool isDownROld=isDownR;

	if(_mouseX>=x && _mouseX<=x+24 && _mouseY>=y && _mouseY<=y+24)
	{
		isOver=true;
		isDownL=false;
		isDownR=true;
	}
	else
	{
		isOver=false;
		isDownL=false;
		isDownR=false;
	}

	if(isDownR!=isDownROld) Draw();
}

bool Field::HitMouseUpR(const int _mouseX,const int _mouseY)
{
	bool isDownROld=isDownR;

	if(_mouseX>=x && _mouseX<=x+24 && _mouseY>=y && _mouseY<=y+24 && isDownR)
	{
		comment++;

		if(comment>2) comment=0;

		isOver=true;
		isDownL=false;
		isDownR=false;
	}
	else
	{
		isOver=false;
		isDownL=false;
		isDownR=false;
	}

	if(isDownR!=isDownROld)
	{
		Draw();
		return true;
	}

	return false;
}

void Field::Draw(void) const
{
	Graphics graphics(hdc);
	Bitmap* bitmap=0;
	HPALETTE palette;

	memset(&palette,0,sizeof(HPALETTE));

	if(isOpen)
	{
		if(entity==0)
			bitmap=bitmapFieldEmptily;
		else if(entity==1)
			bitmap=bitmapField1;
		else if(entity==2)
			bitmap=bitmapField2;
		else if(entity==3)
			bitmap=bitmapField3;
		else if(entity==4)
			bitmap=bitmapField4;
		else if(entity==5)
			bitmap=bitmapField5;
		else if(entity==6)
			bitmap=bitmapField6;
		else if(entity==7)
			bitmap=bitmapField7;
		else if(entity==8)
			bitmap=bitmapField8;
		else if(entity==9)
			bitmap=bitmapFieldMine;
	}
	else
	{
		if(comment==0)
		{
			if(isOver)
			{
				if(isDownL || isDownR)
					bitmap=bitmapFieldCloseDown;
				else
					bitmap=bitmapFieldCloseOver;
			}
			else
				bitmap=bitmapFieldCloseOut;
		}
		else if(comment==1)
		{
			if(isOver)
			{
				if(isDownL || isDownR)
					bitmap=bitmapFieldFlagDown;
				else
					bitmap=bitmapFieldFlagOver;
			}
			else
				bitmap=bitmapFieldFlagOut;
		}
		else
		{
			if(isOver)
			{
				if(isDownL || isDownR)
					bitmap=bitmapFieldDoubtDown;
				else
					bitmap=bitmapFieldDoubtOver;
			}
			else
				bitmap=bitmapFieldDoubtOut;
		}
	}

	graphics.DrawImage(bitmap,x,y);
}