// *****************************************************************
// Автор: Дубровкин Сергей
// Название: Text
// Описание: Класс для работы с текстом
// Дата: 16.07.2010 (Пятница) - 22:12
// ICQ: 597-023-587
// *****************************************************************

#pragma once

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

class Text
{
	private:
		char* text;								// Указатель на текст в памяти

		unsigned int textLength;				// Размер текста

		void Release(void);						// Освобождение занятой памяти

		unsigned int GetTextLength(				// Получение длины текста
			const char* _text) const;

		void TextCopy(							// Копирование текста из одного участка памяти в другой
			char* _textReceiver,
			const char* _textSource,
			const unsigned int _index,
			const unsigned int _length) const;

	public:
		Text(void);								// Конструктор
		Text(const Text& _text);				// Конструктор с присвоением объекта
		Text(const char* _text);				// Конструктор с присвоением текста
		Text(const int _number);				// Конструктор с присвоением целого числа
		Text(const double _number);				// Конструктор с присвоением вещественного числа

		~Text(void);							// Деструктор

		unsigned int GetLength(void) const;		// Получение длины текста
		char* GetText(void) const;				// Получение указателя на начало текста

		char GetChar(							// Получение символа
			const unsigned int _index) const;

		int TextToInt(void) const;				// Получение целого числа из текста
		double TextToDouble(void) const;		// Получение вещественного числа из текста

		Text& operator=(const Text& _text);		// Присвоение объекта
		Text& operator=(const char* _text);		// Присвоение текста
		Text& operator=(const int _number);		// Присвоение целого числа
		Text& operator=(const double _number);	// Присвоение вещественного числа

		Text& operator+=(const Text& _text);	// Добавление объекта
		Text& operator+=(const char* _text);	// Добавление текста
		Text& operator+=(const int _number);	// Добавление целого числа
		Text& operator+=(const double _number);	// Добавление вещественного числа

		Text operator+(const Text& _text)		// Сложение с объектом
			const;

		Text operator+(const char* _text)		// Сложение с текстом
			const;

		Text operator+(const int _number)		// Сложение с целым числом
			const;

		Text operator+(const double _number)	// Сложение с вещественным числом
			const;
};