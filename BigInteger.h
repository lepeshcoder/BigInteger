#pragma once
#include "include.h"


class BigInteger
{
private:

	// система счисления с основанием 1e9
	static const uint_64 base = 1e9 ;

	// Хранилище разрядов
	std::vector<int> digits;

	// false - положительное, true - отрицательное
	bool sign;

	
public:


	/*
		CONSTRUCTORS
	*/

	// конструктор по умолчанию
	BigInteger();

	// конструктор по строке с числом
	BigInteger(std::string num);

	// Конструктор по int_64
	BigInteger(signed long long l);

	// Конструктор по uint_64
	BigInteger(unsigned long long l); 

	// конструктор по int
	BigInteger(int l);

	// Деструктор
	~BigInteger();

	

	/*
		OPERATORS
	*/

	// Перегрузка оператора вывода
	friend std::ostream& operator <<(std::ostream& out, const BigInteger& bi);
	
	// Перегрузка оператора ввода
	friend std::istream& operator >>(std::istream& in, BigInteger& bi);
	
	// Перегрузка оператора std::string
	operator std::string() const;

	// Перегрузка оператора =
	BigInteger& operator= (const BigInteger& RightValue);

	// Унарный - 
	friend const BigInteger operator-(const BigInteger& bi);

	// Унарный +
	friend const BigInteger operator+(const BigInteger& bi);

	// Перегрузка оператора ==
	friend bool operator== (const BigInteger& arg1, const BigInteger& arg2);

	// Перегрузка оператора !=
	friend bool operator!= (const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка оператора < (оптимизировать)
	friend bool operator< (const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка оператора >
	friend bool operator> (const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка оператора <=
	friend bool operator<= (const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка оператора >=
	friend bool operator>= (const BigInteger& arg1, const BigInteger& arg2);

	// Перегрузка префиксного инкремента
	const BigInteger operator++();

	// Перегрузка постфиксного инкремента
	const BigInteger operator++(int);

	// Перегрузка префиксного декремента
	const BigInteger operator--();

	// Перегрузка постфиксного декремента
	const BigInteger operator--(int);

	// Перегрузка бинарного +
	friend const BigInteger operator+(BigInteger arg1, const BigInteger& arg2);

	// Перегрузка бинарного -
	friend const BigInteger operator-(const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка бинарного *
	friend const BigInteger operator*(const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка бинарного / (целочисленное деление)
	friend const BigInteger operator/(const BigInteger& arg1, const BigInteger& arg2);

	//Перегрузка оператора %
	friend const BigInteger operator%(const BigInteger& arg1, const BigInteger& arg2);


	// Перегрузка +=
	BigInteger& operator+= (const BigInteger& right);

	// Перегрузка -=
	BigInteger& operator-= (const BigInteger& right);

	// Перегрузка *=
	BigInteger& operator*= (const BigInteger& right);

	// Перегрузка /= 
	BigInteger& operator/= (const BigInteger& right);

	// Перегрузка %= 
	BigInteger& operator%= (const BigInteger& right);

	


	
	/*
		ADDITIONAL FUNCTIONS
	*/

	// Приведение чисел к одному размеру добавлением незначащих нулей(например при сложении)
	static void ResizeNums (BigInteger& arg1, BigInteger& arg2, uint_64 size);

	// Удаление незначащих нулей 
	static void FixNum (BigInteger& arg);
	
	// Проверка на корректность записи чисел
	static bool IsValidNumber(const std::string& num);

	
	





};





