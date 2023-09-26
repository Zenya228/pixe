// *****************************************************************
// Автор: Дубровкин Сергей
// Название: Text
// Описание: Класс для работы с текстом
// Дата: 16.07.2010 (Пятница) - 22:12
// ICQ: 597-023-587
// *****************************************************************

#include "Text.h"

// Конструктор
Text::Text(void)
{
	text=0;
	textLength=0;
}

// Конструктор с присвоением объекта
Text::Text(const Text& _text)
{
	textLength=_text.GetLength();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,_text.GetText(),0,textLength);
}

// Конструктор с присвоением текста
Text::Text(const char* _text)
{
	textLength=GetTextLength(_text);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,_text,0,textLength);
}

// Конструктор с присвоением целого числа
Text::Text(const int _number)
{
	char textNumber[16];

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%d",_number);
	textLength=GetTextLength(textNumber);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textNumber,0,textLength);
}

// Конструктор с присвоением вещественного числа
Text::Text(const double _number)
{
	char textNumber[16];

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%g",_number);
	textLength=GetTextLength(textNumber);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textNumber,0,textLength);
}

// Деструктор
Text::~Text(void)
{
	Release();
}

// Освобождение занятой памяти
void Text::Release(void)
{
	if(text)
	{
		delete[] text;
		text=0;
	}
}

// Получение длины текста
unsigned int Text::GetLength(void) const
{
	return textLength;
}

// Получение указателя на начало текста
char* Text::GetText(void) const
{
	return text;
}

// Получение символа
char Text::GetChar(const unsigned int _index) const
{
	if(_index>=textLength) return 0;

	return text[_index];
}

// Получение целого числа из текста
int Text::TextToInt(void) const
{
	return atoi(text);
}

// Получение вещественного числа из текста
double Text::TextToDouble(void) const
{
	return atof(text);
}

// Получение длины текста
unsigned int Text::GetTextLength(const char* _text) const
{
	unsigned int textLength=0;

	if(!_text) return 0;

	while(_text[textLength]!=0) textLength++;

	return textLength;
}

// Копирование текста из одного участка памяти в другой
void Text::TextCopy(
	char* _textReceiver,
	const char* _textSource,
	const unsigned int _index,
	const unsigned int _length) const
{
	unsigned int i=0;

	for(i=0;i<_length;i++)
	{
		_textReceiver[i+_index]=_textSource[i];
	}
}

// Присвоение объекта
Text& Text::operator=(const Text& _text)
{
	Release();
	textLength=_text.GetLength();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,_text.GetText(),0,textLength);

	return *this;
}

// Присвоение текста
Text& Text::operator=(const char* _text)
{
	Release();
	textLength=GetTextLength(_text);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,_text,0,textLength);

	return *this;
}

// Присвоение целого числа
Text& Text::operator=(const int _number)
{
	char textNumber[16];

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%d",_number);
	Release();
	textLength=GetTextLength(textNumber);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textNumber,0,textLength);

	return *this;
}

// Присвоение вещественного числа
Text& Text::operator=(const double _number)
{
	char textNumber[16];

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%g",_number);
	Release();
	textLength=GetTextLength(textNumber);
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textNumber,0,textLength);

	return *this;
}

// Добавление объекта
Text& Text::operator+=(const Text& _text)
{
	char* textOld=0;
	unsigned int textOldLength=0;
	unsigned int length=_text.GetLength();

	textOldLength=textLength;
	textOld=new char[textOldLength+1];
	memset(textOld,0,textOldLength+1);
	TextCopy(textOld,text,0,textOldLength);

	textLength+=length;
	Release();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textOld,0,textOldLength);
	TextCopy(text,_text.GetText(),textOldLength,length);
	
	if(textOld)
	{
		delete[] textOld;
		textOld=0;
	}

	return *this;
}

// Добавление текста
Text& Text::operator+=(const char* _text)
{
	char* textOld=0;
	unsigned int textOldLength=0;
	unsigned int length=GetTextLength(_text);

	textOldLength=textLength;
	textOld=new char[textOldLength+1];
	memset(textOld,0,textOldLength+1);
	TextCopy(textOld,text,0,textOldLength);

	textLength+=length;
	Release();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textOld,0,textOldLength);
	TextCopy(text,_text,textOldLength,length);
	
	if(textOld)
	{
		delete[] textOld;
		textOld=0;
	}

	return *this;
}

// Добавление целого числа
Text& Text::operator+=(const int _number)
{
	char textNumber[16];
	char* textOld=0;
	unsigned int textOldLength=0;
	unsigned int length=0;

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%d",_number);

	length=GetTextLength(textNumber);

	textOldLength=textLength;
	textOld=new char[textOldLength+1];
	memset(textOld,0,textOldLength+1);
	TextCopy(textOld,text,0,textOldLength);

	textLength+=length;
	Release();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textOld,0,textOldLength);
	TextCopy(text,textNumber,textOldLength,length);
	
	if(textOld)
	{
		delete[] textOld;
		textOld=0;
	}

	return *this;
}

// Добавление вещественного числа
Text& Text::operator+=(const double _number)
{
	char textNumber[16];
	char* textOld=0;
	unsigned int textOldLength=0;
	unsigned int length=0;

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%g",_number);

	length=GetTextLength(textNumber);

	textOldLength=textLength;
	textOld=new char[textOldLength+1];
	memset(textOld,0,textOldLength+1);
	TextCopy(textOld,text,0,textOldLength);

	textLength+=length;
	Release();
	text=new char[textLength+1];
	memset(text,0,textLength+1);
	TextCopy(text,textOld,0,textOldLength);
	TextCopy(text,textNumber,textOldLength,length);
	
	if(textOld)
	{
		delete[] textOld;
		textOld=0;
	}

	return *this;
}

// Сложение с объектом
Text Text::operator+(const Text& _text) const
{
	Text textNew;
	unsigned int length=_text.GetLength();

	textNew.textLength=textLength+length;
	textNew.text=new char[textNew.textLength+1];
	memset(textNew.text,0,textNew.textLength+1);
	TextCopy(textNew.text,text,0,textLength);
	TextCopy(textNew.text,_text.GetText(),textLength,length);

	return textNew;
}

// Сложение с текстом
Text Text::operator+(const char* _text) const
{
	Text textNew;
	unsigned int length=GetTextLength(_text);

	textNew.textLength=textLength+length;
	textNew.text=new char[textNew.textLength+1];
	memset(textNew.text,0,textNew.textLength+1);
	TextCopy(textNew.text,text,0,textLength);
	TextCopy(textNew.text,_text,textLength,length);

	return textNew;
}

// Сложение с целым числом
Text Text::operator+(const int _number) const
{
	Text textNew;
	char textNumber[16];
	unsigned int length=0;

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%d",_number);

	length=GetTextLength(textNumber);

	textNew.textLength=textLength+length;
	textNew.text=new char[textNew.textLength+1];
	memset(textNew.text,0,textNew.textLength+1);
	TextCopy(textNew.text,text,0,textLength);
	TextCopy(textNew.text,textNumber,textLength,length);

	return textNew;
}

// Сложение с вещественным числом
Text Text::operator+(const double _number) const
{
	Text textNew;
	char textNumber[16];
	unsigned int length=0;

	memset(textNumber,0,16);
	sprintf_s(textNumber,"%g",_number);

	length=GetTextLength(textNumber);

	textNew.textLength=textLength+length;
	textNew.text=new char[textNew.textLength+1];
	memset(textNew.text,0,textNew.textLength+1);
	TextCopy(textNew.text,text,0,textLength);
	TextCopy(textNew.text,textNumber,textLength,length);

	return textNew;
}