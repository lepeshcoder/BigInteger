#pragma once
#include "include.h"


class BigInteger
{
private:

	// ������� ��������� � ���������� 1e9
	static const uint_64 base = 1e9 ;

	// ��������� ��������
	std::vector<int> digits;

	// false - �������������, true - �������������
	bool sign;

	
public:


	/*
		CONSTRUCTORS
	*/

	// ����������� �� ���������
	BigInteger();

	// ����������� �� ������ � ������
	BigInteger(std::string num);

	// ����������� �� int_64
	BigInteger(signed long long l);

	// ����������� �� uint_64
	BigInteger(unsigned long long l); 

	// ����������� �� int
	BigInteger(int l);

	// ����������
	~BigInteger();

	

	/*
		OPERATORS
	*/

	// ���������� ��������� ������
	friend std::ostream& operator <<(std::ostream& out, const BigInteger& bi);
	
	// ���������� ��������� �����
	friend std::istream& operator >>(std::istream& in, BigInteger& bi);
	
	// ���������� ��������� std::string
	operator std::string() const;

	// ���������� ��������� =
	BigInteger& operator= (const BigInteger& RightValue);

	// ������� - 
	friend const BigInteger operator-(const BigInteger& bi);

	// ������� +
	friend const BigInteger operator+(const BigInteger& bi);

	// ���������� ��������� ==
	friend bool operator== (const BigInteger& arg1, const BigInteger& arg2);

	// ���������� ��������� !=
	friend bool operator!= (const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� < (��������������)
	friend bool operator< (const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� >
	friend bool operator> (const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� <=
	friend bool operator<= (const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� >=
	friend bool operator>= (const BigInteger& arg1, const BigInteger& arg2);

	// ���������� ����������� ����������
	const BigInteger operator++();

	// ���������� ������������ ����������
	const BigInteger operator++(int);

	// ���������� ����������� ����������
	const BigInteger operator--();

	// ���������� ������������ ����������
	const BigInteger operator--(int);

	// ���������� ��������� +
	friend const BigInteger operator+(BigInteger arg1, const BigInteger& arg2);

	// ���������� ��������� -
	friend const BigInteger operator-(const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� *
	friend const BigInteger operator*(const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� / (������������� �������)
	friend const BigInteger operator/(const BigInteger& arg1, const BigInteger& arg2);

	//���������� ��������� %
	friend const BigInteger operator%(const BigInteger& arg1, const BigInteger& arg2);


	// ���������� +=
	BigInteger& operator+= (const BigInteger& right);

	// ���������� -=
	BigInteger& operator-= (const BigInteger& right);

	// ���������� *=
	BigInteger& operator*= (const BigInteger& right);

	// ���������� /= 
	BigInteger& operator/= (const BigInteger& right);

	// ���������� %= 
	BigInteger& operator%= (const BigInteger& right);

	


	
	/*
		ADDITIONAL FUNCTIONS
	*/

	// ���������� ����� � ������ ������� ����������� ���������� �����(�������� ��� ��������)
	static void ResizeNums (BigInteger& arg1, BigInteger& arg2, uint_64 size);

	// �������� ���������� ����� 
	static void FixNum (BigInteger& arg);
	
	// �������� �� ������������ ������ �����
	static bool IsValidNumber(const std::string& num);

	
	





};





