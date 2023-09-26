
#include "FieldManager.h"

FieldManager* FieldManager::instance=0;

FieldManager::FieldManager(void)
{
	appInstance=0;
	window=0;

	fieldWidht=0;
	fieldHeight=0;
	fieldCount=0;
	fields=0;

	mines=0;
	openFields=0;
}

FieldManager::~FieldManager(void)
{
	if(fields)
	{
		delete[] fields;
		fields=0;
	}

	Field::End();
}

FieldManager* FieldManager::GetInstance(void)
{
	if(!instance) instance=new FieldManager();

	return instance;
}

void FieldManager::Release(void)
{
	if(instance)
	{
		delete instance;
		instance=0;
	}
}

bool FieldManager::Init(const HINSTANCE _appInstance,const HWND _window)
{
	appInstance=_appInstance;
	window=_window;

	if(Field::Init(appInstance,window,GetDC(window))) return true;

	return false;
}

void FieldManager::Create(
	const unsigned int _width,
	const unsigned int _height,
	const unsigned int _mines)
{
	RECT desktopRect;
	unsigned int desktopWidth=0;
	unsigned int desktopHeight=0;
	unsigned int windowWidth=0;
	unsigned int windowHeight=0;
	unsigned int i=0;
	unsigned int j=0;
	unsigned int index=0;

	GetWindowRect(GetDesktopWindow(),&desktopRect);

	desktopWidth=desktopRect.right;
	desktopHeight=desktopRect.bottom;

	Delete();

	fieldWidht=_width;
	fieldHeight=_height;

	mines=_mines;

	fieldCount=_width*_height;

	fields=new Field[fieldCount];

	for(j=0;j<fieldHeight;j++)
	{
		for(i=0;i<fieldWidht;i++)
		{
			fields[index].SetPosition(4+i*25,5+j*25);
			fields[index].SetIndex(i,j);
			index++;
		}
	}

	windowWidth=6+fieldWidht*25+7;
	windowHeight=6+fieldHeight*25+7+43;

	MoveWindow(window,desktopWidth/2-windowWidth/2,desktopHeight/2-windowHeight/2,windowWidth,windowHeight,true);

	Random();

	InvalidateRect(window,0,true);
}

void FieldManager::Delete(void)
{
	if(fields)
	{
		delete[] fields;
		fields=0;
		fieldWidht=0;
		fieldHeight=0;
		fieldCount=0;
		mines=0;
		openFields=0;
	}
}

void FieldManager::HitMouseMove(const int _mouseX,const int _mouseY) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(!fields[i].GetIsOpen()) fields[i].HitMouseOver(_mouseX,_mouseY);
	}
}

void FieldManager::HitMouseDownL(const int _mouseX,const int _mouseY) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(!fields[i].GetIsOpen()) fields[i].HitMouseDownL(_mouseX,_mouseY);
	}
}

void FieldManager::HitMouseUpL(const int _mouseX,const int _mouseY)
{
	unsigned int i=0;
	Field* field=0;

	for(i=0;i<fieldCount;i++)
	{
		field=&fields[i];

		if(!field->GetIsOpen())
		{
			if(field->HitMouseUpL(_mouseX,_mouseY))
			{
				if(field->GetEntity()==9)
				{
					End();
					MessageBox(window,"Вы проиграли.","Поражение!",MB_ICONINFORMATION);
					break;
				}
				else if(field->GetEntity()==0)
				{
					openFields++;

					if(openFields>=fieldCount-mines)
					{
						End();
						MessageBox(window,"Вы выйграли.","Победа!",MB_ICONINFORMATION);
						break;
					}
					else
					{
						FieldFindEmptily(field);

						if(openFields>=fieldCount-mines)
						{
							End();
							MessageBox(window,"Вы выйграли.","Победа!",MB_ICONINFORMATION);
							break;
						}
					}
				}
				else
				{
					openFields++;

					if(openFields>=fieldCount-mines)
					{
						End();
						MessageBox(window,"Вы выйграли.","Победа!",MB_ICONINFORMATION);
						break;
					}
				}
			}
		}
	}
}

void FieldManager::HitMouseDownR(const int _mouseX,const int _mouseY) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(!fields[i].GetIsOpen()) fields[i].HitMouseDownR(_mouseX,_mouseY);
	}
}

void FieldManager::HitMouseUpR(const int _mouseX,const int _mouseY) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(!fields[i].GetIsOpen()) fields[i].HitMouseUpR(_mouseX,_mouseY);
	}
}

unsigned int FieldManager::GetWidth(void) const
{
	return fieldWidht;
}

unsigned int FieldManager::GetHeight(void) const
{
	return fieldHeight;
}

unsigned int FieldManager::GetFieldCount(void) const
{
	return fieldCount;
}

Field* FieldManager::GetField(const unsigned int _i,const unsigned int _j) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(fields[i].GetIndexX()==_i && fields[i].GetIndexY()==_j) return &fields[i];
	}

	return 0;
}

unsigned int FieldManager::GetEntity(const unsigned int _i,const unsigned int _j) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(fields[i].GetIndexX()==_i && fields[i].GetIndexY()==_j) return fields[i].GetEntity();
	}

	return 0;
}

unsigned int FieldManager::GetComment(const unsigned int _i,const unsigned int _j) const
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(fields[i].GetIndexX()==_i && fields[i].GetIndexY()==_j) return fields[i].GetComment();
	}

	return 0;
}

void FieldManager::SetEntity(const unsigned int _i,const unsigned int _j,const unsigned int _entity)
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		if(fields[i].GetIndexX()==_i && fields[i].GetIndexY()==_j) fields[i].SetEntity(_entity);
	}
}

void FieldManager::Paint(void)
{
	unsigned int i=0;

	for(i=0;i<fieldCount;i++)
	{
		fields[i].Draw();
	}
}

void FieldManager::Random(void)
{
	unsigned int createMines=0;
	unsigned int i=0;
	int indexX=0;
	int indexY=0;

	srand((unsigned int)time(0));

	while(createMines<mines)
	{
		indexX=rand() % fieldWidht;
		indexY=rand() % fieldHeight;

		if(GetEntity(indexX,indexY)==0)
		{
			SetEntity(indexX,indexY,9);
			createMines++;
		}
	}

	for(i=0;i<fieldCount;i++)
	{
		FieldFindMines(&fields[i]);
	}
}

void FieldManager::FieldFindMines(Field* _field)
{
	unsigned int tempMines=0;
	unsigned int indexX=0;
	unsigned int indexY=0;

	Field* field1=0;
	Field* field2=0;
	Field* field3=0;
	Field* field4=0;
	Field* field5=0;
	Field* field6=0;
	Field* field7=0;
	Field* field8=0;

	if(_field->GetEntity()==9) return;

	indexX=_field->GetIndexX();
	indexY=_field->GetIndexY();

	if(_field->GetIndexX()<fieldWidht && _field->GetIndexY()>0) field1=GetField(indexX+1,indexY-1);
	if(_field->GetIndexX()<fieldWidht) field2=GetField(indexX+1,indexY);
	if(_field->GetIndexX()<fieldWidht && _field->GetIndexY()<fieldHeight) field3=GetField(indexX+1,indexY+1);
	if(_field->GetIndexY()<fieldHeight) field4=GetField(indexX,indexY+1);
	if(_field->GetIndexX()>0 && _field->GetIndexY()<fieldHeight) field5=GetField(indexX-1,indexY+1);
	if(_field->GetIndexX()>0) field6=GetField(indexX-1,indexY);
	if(_field->GetIndexX()>0 && _field->GetIndexY()>0) field7=GetField(indexX-1,indexY-1);
	if(_field->GetIndexY()>0) field8=GetField(indexX,indexY-1);

	if(field1 && field1->GetEntity()==9) tempMines++;
	if(field2 && field2->GetEntity()==9) tempMines++;
	if(field3 && field3->GetEntity()==9) tempMines++;
	if(field4 && field4->GetEntity()==9) tempMines++;
	if(field5 && field5->GetEntity()==9) tempMines++;
	if(field6 && field6->GetEntity()==9) tempMines++;
	if(field7 && field7->GetEntity()==9) tempMines++;
	if(field8 && field8->GetEntity()==9) tempMines++;

	_field->SetEntity(tempMines);
}

void FieldManager::FieldFindEmptily(Field* _field)
{
	unsigned int indexX=0;
	unsigned int indexY=0;

	Field* field1=0;
	Field* field2=0;
	Field* field3=0;
	Field* field4=0;
	Field* field5=0;
	Field* field6=0;
	Field* field7=0;
	Field* field8=0;

	indexX=_field->GetIndexX();
	indexY=_field->GetIndexY();

	if(_field->GetIndexX()<fieldWidht && _field->GetIndexY()>0) field1=GetField(indexX+1,indexY-1);
	if(_field->GetIndexX()<fieldWidht) field2=GetField(indexX+1,indexY);
	if(_field->GetIndexX()<fieldWidht && _field->GetIndexY()<fieldHeight) field3=GetField(indexX+1,indexY+1);
	if(_field->GetIndexY()<fieldHeight) field4=GetField(indexX,indexY+1);
	if(_field->GetIndexX()>0 && _field->GetIndexY()<fieldHeight) field5=GetField(indexX-1,indexY+1);
	if(_field->GetIndexX()>0) field6=GetField(indexX-1,indexY);
	if(_field->GetIndexX()>0 && _field->GetIndexY()>0) field7=GetField(indexX-1,indexY-1);
	if(_field->GetIndexY()>0) field8=GetField(indexX,indexY-1);

	if(field1 && field1->GetIsFind())
	{
		openFields++;
		field1->Open();
		field1->SetIsFind(false);

		if(field1->GetEntity()==0) FieldFindEmptily(field1);
	}

	if(field2 && field2->GetIsFind())
	{
		openFields++;
		field2->Open();
		field2->SetIsFind(false);

		if(field2->GetEntity()==0) FieldFindEmptily(field2);
	}

	if(field3 && field3->GetIsFind())
	{
		openFields++;
		field3->Open();
		field3->SetIsFind(false);

		if(field3->GetEntity()==0) FieldFindEmptily(field3);
	}

	if(field4 && field4->GetIsFind())
	{
		openFields++;
		field4->Open();
		field4->SetIsFind(false);

		if(field4->GetEntity()==0) FieldFindEmptily(field4);
	}

	if(field5 && field5->GetIsFind())
	{
		openFields++;
		field5->Open();
		field5->SetIsFind(false);

		if(field5->GetEntity()==0) FieldFindEmptily(field5);
	}

	if(field6 && field6->GetIsFind())
	{
		openFields++;
		field6->Open();
		field6->SetIsFind(false);

		if(field6->GetEntity()==0) FieldFindEmptily(field6);
	}

	if(field7 && field7->GetIsFind())
	{
		openFields++;
		field7->Open();
		field7->SetIsFind(false);

		if(field7->GetEntity()==0) FieldFindEmptily(field7);
	}

	if(field8 && field8->GetIsFind())
	{
		openFields++;
		field8->Open();
		field8->SetIsFind(false);

		if(field8->GetEntity()==0) FieldFindEmptily(field8);
	}
}

void FieldManager::End(void)
{
	unsigned int i=0;
	Field* field=0;

	for(i=0;i<fieldCount;i++)
	{
		field=&fields[i];

		if(!field->GetIsOpen()) field->Open();
	}
}