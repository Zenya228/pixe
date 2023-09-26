// *****************************************************************
// �����: ��������� ������
// ��������: Text
// ��������: ����� ��� ������ � �������
// ����: 16.07.2010 (�������) - 22:12
// ICQ: 597-023-587
// *****************************************************************

#pragma once

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

class Text
{
	private:
		char* text;								// ��������� �� ����� � ������

		unsigned int textLength;				// ������ ������

		void Release(void);						// ������������ ������� ������

		unsigned int GetTextLength(				// ��������� ����� ������
			const char* _text) const;

		void TextCopy(							// ����������� ������ �� ������ ������� ������ � ������
			char* _textReceiver,
			const char* _textSource,
			const unsigned int _index,
			const unsigned int _length) const;

	public:
		Text(void);								// �����������
		Text(const Text& _text);				// ����������� � ����������� �������
		Text(const char* _text);				// ����������� � ����������� ������
		Text(const int _number);				// ����������� � ����������� ������ �����
		Text(const double _number);				// ����������� � ����������� ������������� �����

		~Text(void);							// ����������

		unsigned int GetLength(void) const;		// ��������� ����� ������
		char* GetText(void) const;				// ��������� ��������� �� ������ ������

		char GetChar(							// ��������� �������
			const unsigned int _index) const;

		int TextToInt(void) const;				// ��������� ������ ����� �� ������
		double TextToDouble(void) const;		// ��������� ������������� ����� �� ������

		Text& operator=(const Text& _text);		// ���������� �������
		Text& operator=(const char* _text);		// ���������� ������
		Text& operator=(const int _number);		// ���������� ������ �����
		Text& operator=(const double _number);	// ���������� ������������� �����

		Text& operator+=(const Text& _text);	// ���������� �������
		Text& operator+=(const char* _text);	// ���������� ������
		Text& operator+=(const int _number);	// ���������� ������ �����
		Text& operator+=(const double _number);	// ���������� ������������� �����

		Text operator+(const Text& _text)		// �������� � ��������
			const;

		Text operator+(const char* _text)		// �������� � �������
			const;

		Text operator+(const int _number)		// �������� � ����� ������
			const;

		Text operator+(const double _number)	// �������� � ������������ ������
			const;
};