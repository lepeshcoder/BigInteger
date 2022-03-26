#include "BigInteger.h"



/*
	CONSTRUCTORS
*/

BigInteger::BigInteger()
{
	sign = POSITIVE;
	digits.push_back(0);
	//std::cout << "Вызвался конструктор по умолчанию" << this << std::endl;
}

BigInteger::BigInteger(std::string num)
{
	//std::cout << "Вызвался конструктор по строке " << this << std::endl;
	if (num.size() == 0)
	{
		sign = POSITIVE;
		digits.push_back(0);
	}
	else
	{
		sign = (num[0] == '-') ? NEGATIVE : POSITIVE;
		if (sign == NEGATIVE) num = num.substr(1, num.size() - 1);
		for (int_64 i = num.size() - 1; i >= 0; i -= 9)
		{
			if (i < 9) digits.insert(digits.begin(),atoi(num.substr(0, i + 1).c_str()));
			else digits.insert(digits.begin(),atoi(num.substr(i - 8, 9).c_str()));
		}
	}
}

BigInteger::BigInteger(signed long long l) {
	if (l < 0) { sign = NEGATIVE; l = -l; }
	else this->sign = POSITIVE;
	do {
		this->digits.insert(digits.begin(),l % base);
		l /= base;
	} while (l != 0);
}

BigInteger::BigInteger(unsigned long long l) {
	this->sign = POSITIVE;
	do {
		this->digits.insert(digits.begin(),l % base);
		l /= base;
	} while (l != 0);
}

BigInteger::BigInteger(int l)
{
	if (l < 0) { sign = NEGATIVE; l = -l; }
	else sign = POSITIVE;
	do {
		digits.insert(digits.begin(), l % base);
		l /= base;
	} while (l != 0);
}

BigInteger::~BigInteger()
{
	//std::cout << "Вызвался деструктор у обьекта " << this << std::endl;
}



/*
	OPERATORS
*/

std::ostream& operator<<(std::ostream& out, const BigInteger& bi)
{
	if (bi.sign == NEGATIVE) out << "-";
	std::stringstream ss;
	for (int_64 i = 0; i < bi.digits.size(); ++i)
	{
		ss << bi.digits[i];
		std::string temp;
		ss >> temp;
		ss.clear();
		if(i != 0) temp.insert(temp.begin(), 9 - temp.size(), '0');
		out << temp;
	}
	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& bi)
{
	std::string temp;
	in >> temp;
	BigInteger a(temp);
	bi = a;
	return in;
}

const BigInteger operator-(const BigInteger& bi)
{
	BigInteger temp = bi;
	temp.sign = !bi.sign;
	return temp;
}

const BigInteger operator+(const BigInteger& bi)
{
	return BigInteger(bi);
}

bool operator==(const BigInteger& arg1, const BigInteger& arg2)
{
	return (arg1.sign == arg2.sign && arg1.digits == arg2.digits);
}

bool operator!=(const BigInteger& arg1, const BigInteger& arg2)
{
	return !(arg1 == arg2);
}

bool operator<(const BigInteger& arg1, const BigInteger& arg2)
{
	if (arg1 == arg2) return false;
	if (arg1.sign == NEGATIVE && arg2.sign == POSITIVE) return true;
	else if (arg1.sign == POSITIVE && arg2.sign == NEGATIVE) return false;
	else
	{
		if (arg1.digits.size() > arg2.digits.size() && arg1.sign == POSITIVE) return false;
		else if (arg1.digits.size() > arg2.digits.size() && arg1.sign == NEGATIVE) return true;
		else if (arg1.digits.size() < arg2.digits.size() && arg1.sign == POSITIVE) return true;
		else if (arg1.digits.size() < arg2.digits.size() && arg1.sign == NEGATIVE) return false;
		else
		{
			for (uint_64 i = 0; i < arg1.digits.size(); i++)
			{
				if (arg1.digits[i] > arg2.digits[i] && arg1.sign == POSITIVE) return false;
				if (arg1.digits[i] > arg2.digits[i] && arg1.sign == NEGATIVE) return true;
				if (arg1.digits[i] < arg2.digits[i] && arg1.sign == POSITIVE) return true;
				if (arg1.digits[i] < arg2.digits[i] && arg1.sign == NEGATIVE) return false;
			}
		}
	}
}

bool operator>(const BigInteger& arg1, const BigInteger& arg2)
{
	if (arg1 == arg2) return false;
	else return !(arg1 < arg2);
}

bool operator<=(const BigInteger& arg1, const BigInteger& arg2)
{
	return (arg1 < arg2 || arg1 == arg2);
}

bool operator>=(const BigInteger& arg1, const BigInteger& arg2)
{
	return (arg1 > arg2 || arg1 == arg2);
}

const BigInteger operator+(BigInteger arg1, const BigInteger& arg2)
{
	if (arg1.sign == NEGATIVE && arg2.sign == NEGATIVE) return -(-arg1 + -arg2);
	else if (arg1.sign == NEGATIVE && arg2.sign == POSITIVE) return arg2 - -arg1;
	else if (arg1.sign == POSITIVE && arg2.sign == NEGATIVE) return arg1 - -arg2;
	else
	{
		BigInteger result;
		result.digits.resize(std::max(arg1.digits.size(), arg2.digits.size()) + 1);
		result.sign = POSITIVE;
		BigInteger num1 = arg1; BigInteger num2 = arg2;
		BigInteger::ResizeNums(num1, num2, std::max(arg1.digits.size(), arg2.digits.size()) + 1);
		uint_64 carry = 0;
		for (int_64 i = num1.digits.size() - 1; i >= 0; --i)
		{
			int CurrRank = num1.digits[i] + num2.digits[i] + carry; 
			result.digits[i] = CurrRank % BigInteger::base;
			if (CurrRank > MAX_RANK_VALUE) carry = 1;
			else carry = 0;
		}
		BigInteger::FixNum(result);
		return result;
	}
}

const BigInteger operator-(const BigInteger& arg1, const BigInteger& arg2)
{
	if (arg1.sign == NEGATIVE && arg2.sign == NEGATIVE) return -arg2 - -arg1;
	else if (arg1.sign == NEGATIVE && arg2.sign == POSITIVE) return  -(-arg1 + arg2);
	else if (arg1.sign == POSITIVE && arg2.sign == NEGATIVE) return arg1 + -arg2;
	else
	{
		if (arg1 == arg2) return BigInteger();
		else if (arg1 < arg2) return -(arg2 - arg1);
		else
		{
			BigInteger result;
			uint_64 new_size = std::max(arg1.digits.size(), arg2.digits.size());
			result.digits.resize(new_size);
			BigInteger num1 = arg1, num2 = arg2;
			BigInteger::ResizeNums(num1, num2, new_size);
			for (int_64 i = new_size - 1; i >= 0; --i)
			{
				int CurrRank = num1.digits[i] - num2.digits[i];
				if (CurrRank < 0)
				{
					int_64 j = i - 1;
					while (num1.digits[j] == 0) num1.digits[j--] = MAX_RANK_VALUE;
					--num1.digits[j];
					result.digits[i] = CurrRank + BigInteger::base;
				}
				else result.digits[i] = CurrRank;
			}
			BigInteger::FixNum(result);
			return result;
		}
	}
}

const BigInteger operator*(const BigInteger& arg1, const BigInteger& arg2)
{
	BigInteger result; 
	if (arg1 == ZERO || arg2 == ZERO) return ZERO;
	result.sign = (arg1.sign ^ arg2.sign) ? NEGATIVE : POSITIVE;
	result.digits.resize(arg1.digits.size() + arg2.digits.size());
	int shift = 0;
	for (int_64 i = arg1.digits.size() - 1; i >= 0; --i)
	{
		BigInteger temp; temp.digits.clear();
		int carry = 0;
		for (int_64 j = arg2.digits.size() - 1; j >= 0; --j)
		{
			int CurrRank = (int_64(arg1.digits[i]) * int_64(arg2.digits[j])) + carry;
			temp.digits.insert(temp.digits.begin(),CurrRank % BigInteger::base);
			carry = CurrRank / BigInteger::base;
		}
		if (carry)
		{
			temp.digits.insert(temp.digits.begin(), carry);
		}
		for (int k = 0; k < shift; k++) temp.digits.push_back(0);
		++shift;
		result += temp;
	}
	BigInteger::FixNum(result);
	return result;
}

const BigInteger operator/(const BigInteger& arg1, const BigInteger& arg2)
{
	return BigInteger();
}

const BigInteger operator%(const BigInteger& arg1, const BigInteger& arg2)
{
	return BigInteger();
}

BigInteger::operator std::string() const
{
	std::stringstream ss;
	ss << *this;
	std::string temp = ss.str();
	for (int i = 0; i < temp.size(); i++) if (temp[i] == ' ') temp.erase(i--,1);
	return temp;
}

BigInteger& BigInteger::operator=(const BigInteger& RightValue)
{
	//std::cout << "Вызвался оператор = у обьекта " << this <<" по обьекту "<< &RightValue << std::endl; а еще я чмо
	if (this != &RightValue)
	{
		digits = RightValue.digits;
		sign = RightValue.sign;
	} 
	return *this;
}

const BigInteger BigInteger::operator++()
{
	return(*this += 1);
}

const BigInteger BigInteger::operator++(int)
{
	BigInteger OldValue = *this;
	*this += 1;
	return OldValue;
}

const BigInteger BigInteger::operator--()
{
	return(*this -= 1);
}

const BigInteger BigInteger::operator--(int)
{
	BigInteger OldValue = *this;
	*this -= 1;
	return OldValue;
}

BigInteger& BigInteger::operator+=(const BigInteger& value)
{
	return *this = (*this + value);
}

BigInteger& BigInteger::operator-=(const BigInteger& value)
{
	return *this = (*this - value);
}

BigInteger& BigInteger::operator*=(const BigInteger& value)
{
	return *this = (*this * value);
}

BigInteger& BigInteger::operator/=(const BigInteger& right)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& right)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

void BigInteger::ResizeNums(BigInteger& arg1, BigInteger& arg2, uint_64 size)
{
	arg1.digits.insert(arg1.digits.begin(), size - arg1.digits.size(), 0);
	arg2.digits.insert(arg2.digits.begin(), size - arg2.digits.size(), 0);
}

void BigInteger::FixNum(BigInteger& arg)
{
	while (arg.digits.size() > 1 && arg.digits[0] == 0) 
		arg.digits.erase(arg.digits.begin());
}

bool BigInteger::IsValidNumber(const std::string& num)
{
	const std::regex r(R"(-?\d+)");
	return regex_match(num.data(), r);

}

