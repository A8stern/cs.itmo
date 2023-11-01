//
// Created by Kovalev Gleb on 19.10.2023.
//

#include "LN.h"

LN::LN()
{
	sze = 1;
	number = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
	if (number == nullptr)
	{
		free(number);
		isMem = true;
	}
	number[0] = 0;
}

LN::LN(long long num)
{
	if (num < 0)
	{
		negative = true;
		num = -num;
	}
	char *tHexChar = (char *)(malloc(sizeof(char) * 1));
	if (tHexChar == nullptr)
	{
		free(tHexChar);
		isMem = true;
		return;
	}
	size_t index = 0;
	long long tempNum = num;
	int symbol = 0;
	while (tempNum > 15)
	{
		symbol = tempNum % 16;
		tHexChar[index] = digit(symbol);
		index++;
		increaseArraySize(tHexChar, index, index + 1);
		tempNum /= 16;
	}
	symbol = tempNum % 16;
	tHexChar[index] = digit(symbol);
	index++;
	char *hexChar = (char *)(malloc(sizeof(char) * index));
	if (hexChar == nullptr)
	{
		free(hexChar);
		isMem = true;
		return;
	}
	for (size_t j = 0; j < index; j++)
	{
		hexChar[j] = tHexChar[strlen(tHexChar) - 1 - j];
	}
	size_t i = 0;
	size_t len = index;
	sze = len / 4;
	if (len % 4 != 0)
	{
		sze++;
	}
	number = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
	if (number == nullptr)
	{
		free(number);
		isMem = true;
		return;
	}
	uint16_t value;
	int k = 0;
	uint16_t temp = 0;
	index = 0;
	for (size_t j = strlen(hexChar); j > i; j--)
	{
		char digit = hexChar[j - 1];
		if (isdigit(digit))
		{
			value = digit - '0';
		}
		else if (isalpha(digit))
		{
			if (isupper(digit))
			{
				value = digit - 'A' + 10;
			}
			else
			{
				value = digit - 'a' + 10;
			}
		}
		if (k != 0)
		{
			temp += value * (2 << (k - 1));
		}
		else
		{
			temp += value;
		}
		k += 4;
		if (k == 16)
		{
			number[index] = temp;
			index++;
			temp = 0;
			k = 0;
		}
	}
	if (temp != 0)
	{
		number[index] = temp;
	}
}

LN::LN(const std::string_view &hexString)
{
	if (hexString[0] == '-')
	{
		negative = true;
	}
	size_t i = 0;
	size_t len = hexString.length();
	sze = hexString.size();
	if (negative || hexString[0] == '+')
	{
		i = 1;
		len--;
	}
	sze = len / 4;
	if (len % 4 != 0)
	{
		sze++;
	}
	number = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
	if (number == nullptr)
	{
		free(number);
		isMem = true;
		return;
	}
	uint16_t value;
	int k = 0;
	uint16_t temp = 0;
	size_t index = 0;
	for (size_t j = hexString.length(); j > i; j--)
	{
		char digit = hexString[j - 1];
		if (isdigit(digit))
		{
			value = digit - '0';
		}
		else if (isalpha(digit))
		{
			if (isupper(digit))
			{
				value = digit - 'A' + 10;
			}
			else
			{
				value = digit - 'a' + 10;
			}
		}
		if (k != 0)
		{
			temp += value * (2 << (k - 1));
		}
		else
		{
			temp += value;
		}
		k += 4;
		if (k == 16)
		{
			number[index] = temp;
			index++;
			temp = 0;
			k = 0;
		}
	}
	if (temp != 0)
	{
		number[index] = temp;
	}
}

LN::LN(const char *hexChar)
{
	if (hexChar[0] == '-')
	{
		negative = true;
	}
	if (hexChar[0] == '0')
	{
		sze = 1;
		number = (uint16_t *)(malloc(sizeof(uint16_t) * 1));
		if (number == nullptr)
		{
			free(number);
			isMem = true;
			return;
		}
		number[0] = 0;
		return;
	}
	size_t i = 0;
	size_t len = strlen(hexChar);
	if (negative || hexChar[0] == '+')
	{
		i = 1;
		len--;
	}
	sze = len / 4;
	if (len % 4 != 0)
	{
		sze++;
	}
	number = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
	if (number == nullptr)
	{
		free(number);
		isMem = true;
		return;
	}
	uint16_t value;
	int k = 0;
	uint16_t temp = 0;
	size_t index = 0;
	for (size_t j = strlen(hexChar); j > i; j--)
	{
		char digit = hexChar[j - 1];
		if (isdigit(digit))
		{
			value = digit - '0';
		}
		else if (isalpha(digit))
		{
			if (isupper(digit))
			{
				value = digit - 'A' + 10;
			}
			else
			{
				value = digit - 'a' + 10;
			}
		}
		if (k != 0)
		{
			temp += value * (2 << (k - 1));
		}
		else
		{
			temp += value;
		}
		k += 4;
		if (k == 16)
		{
			number[index] = temp;
			index++;
			temp = 0;
			k = 0;
		}
	}
	if (temp != 0)
	{
		number[index] = temp;
	}
}

LN LN::operator=(const LN &other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] number;
	sze = other.sze;
	negative = other.negative;
	isNan = other.isNan;
	number = (uint16_t *)(malloc(sizeof(uint16_t) * (sze)));
	if (number == nullptr)
	{
		free(number);
		this->isMem = true;
		return *this;
	}
	for (size_t i = 0; i < sze; i++)
	{
		number[i] = other.number[i];
	}

	return *this;
}

bool LN::operator==(const LN &other) const
{
	if (sze != other.sze)
	{
		return false;
	}
	for (size_t i = 0; i < sze; ++i)
	{
		if (number[i] != other.number[i])
		{
			return false;
		}
	}
	return true;
}

bool LN::operator!=(const LN &other) const
{
	return !(*this == other);
}

bool LN::operator>(const LN &other) const
{
	bool check = true;
	if (!negative && other.negative)
	{
		return true;
	}
	else if (negative && !negative)
	{
		return false;
	}
	else if (negative && other.negative)
	{
		check = false;
	}
	if (sze > other.sze)
	{
		return check;
	}
	else if (sze < other.sze)
	{
		return !check;
	}
	else
	{
		for (size_t i = sze; i > 0; i--)
		{
			if (number[i - 1] > other.number[i - 1])
			{
				return check;
			}
			else if (number[i - 1] < other.number[i - 1])
			{
				return !check;
			}
		}
		return false;
	}
}

bool LN::operator<(const LN &other) const
{
	return ((!(*this > other) && !(*this == other)));
}

bool LN::operator<=(const LN &other) const
{
	return ((*this < other) || (*this == other));
}

bool LN::operator>=(const LN &other) const
{
	return ((*this > other) || (*this == other));
}

LN LN::operator-() const
{
	LN negation = *this;
	if (negation.negative)
	{
		negation.negative = false;
		return negation;
	}
	negation.negative = true;
	return negation;
}

LN LN::operator+(const LN &second) const
{
	LN fa = *this;
	LN fs = second;
	if ((isNan) || (second.isNan))
	{
		return makeNaN();
	}
	if ((negative) && (second.negative))
	{
		LN res = add(*this, second);
		res.negative = !res.negative;
		return res;
	}
	if ((!negative) && (second.negative))
	{
		fs.negative = false;
		LN res = fa - fs;
		return res;
	}
	if ((negative) && (!second.negative))
	{
		fa.negative = false;
		LN res = second - fa;
		return res;
	}
	LN res = add(*this, second);
	return res;
}

LN LN::operator-(LN &second) const
{
	LN first = *this;
	if ((isNan) || (second.isNan))
	{
		return makeNaN();
	}
	if ((negative) && (second.negative))
	{
		LN res;
		LN sA = second;
		sA.negative = false;
		LN fA = *this;
		fA.negative = false;
		if (second < *this)
		{
			return sub(sA, fA);
		}
		else
		{
			res = sub(fA, sA);
			res.negative = true;
		}
		return res;
	}
	if ((!negative) && (second.negative))
	{
		LN res = add(*this, second);
		return res;
	}
	if ((negative) && (!second.negative))
	{
		LN res = add(second, *this);
		res.negative = !res.negative;
		return res;
	}
	LN res;
	if (second > *this)
	{
		res = sub(second, first);
		res.negative = true;
		return res;
	}
	res = sub(first, second);
	res.negative = false;
	return res;
}

LN LN::operator*(const LN &second)
{
	if ((isNan) || (second.isNan))
	{
		return makeNaN();
	}
	LN res;
	if (negative == second.negative)
	{
		res.negative = false;
	}
	else
	{
		res.negative = true;
	}
	LN firstArg = *this;
	firstArg.negative = false;
	res = multiply(firstArg, second);
	return res;
}

LN LN::operator/(LN &second)
{
	if ((isNan) || (second.isNan) || (second == LN("0")))
	{
		return makeNaN();
	}
	if (second > *this)
	{
		return LN("0");
	}
	std::pair< LN, LN > resOfDivide = divide(*this, second);
	LN res = resOfDivide.first;
	if (negative == second.negative)
	{
		res.negative = false;
	}
	else
	{
		res.negative = true;
	}
	return res;
}

LN LN::operator%(LN &second)
{
	if ((isNan) || (second.isNan) || (second == LN("0")))
	{
		return makeNaN();
	}
	if (second > *this)
	{
		return *this;
	}
	std::pair< LN, LN > resOfDivide = divide(*this, second);
	LN res = resOfDivide.second;
	if (res == LN("0"))
	{
		return LN("0");
	}
	if (negative && second.negative)
	{
		res.negative = true;
	}
	else if (negative && !second.negative)
	{
		res = second - res;
	}
	else if (!negative && second.negative)
	{
		LN temp = second;
		temp.negative = false;
		res = temp - res;
		res.negative = true;
	}
	return res;
}

LN LN::operator~() const
{
	if ((isNan) || (this->negative))
	{
		return makeNaN();
	}
	if (*this == LN("1"))
	{
		return LN("1");
	}
	LN res = sqrt(*this);
	return res;
}

long long LN::convertToLongLong() const
{
	if (isNan)
	{
		throw std::runtime_error("Conversion error: value is NaN");
	}
	LN copy(*this);
	if (copy > LN(std::numeric_limits< long long >::max()))
	{
		throw std::runtime_error("Conversion error: value is more than long long maximum value");
	}
	long long res = 0;
	long long k = 1;
	for (size_t i = 0; i < sze; i++)
	{
		res += copy.number[i] * k;
		k *= (2 << 15);
	}
	if (negative)
		res = -res;
	return res;
}

bool LN::isNull() const
{
	if (isNan)
	{
		throw std::runtime_error("Conversion error: value is NaN");
	}
	return *this == LN("0");
}

char *LN::appear() const
{
	if (isNan)
	{
		char *hexString;
		hexString = (char *)(malloc(sizeof(char) * 3));
		if (hexString == nullptr)
		{
			free(hexString);
			return nullptr;
		}
		hexString[0] = 'N';
		hexString[1] = 'a';
		hexString[2] = 'N';
		return hexString;
	}
	size_t bufferSize = sze * 4;
	if (negative)
	{
		bufferSize++;
	}
	char *hexString;
	hexString = (char *)(malloc(sizeof(char) * 1));
	hexString[0] = 0;
	if (hexString == nullptr)
	{
		free(hexString);
		return nullptr;
	}
	if (negative)
	{
		hexString[0] = '-';
	}
	size_t index = 0;
	for (size_t i = 0; i < sze; i++)
	{
		if (number[i] == 0)
		{
			if (i != sze - 1)
			{
				for (int j = 0; j < 4; j++)
				{
					char *newString = (char *)(malloc(sizeof(char) * (index + 1)));
					if (newString == nullptr)
					{
						free(newString);
						free(hexString);
						return nullptr;
					}
					for (int r = 0; r < sizeof(newString); r++)
					{
						newString[r] = '0';
					}
					for (int k = 0; k < index; k++)
					{
						newString[k + 1] = hexString[k];
					}
					hexString = newString;
					hexString[0] = '0';
					index++;
				}
			}
			else
			{
				char *newString = (char *)(malloc(sizeof(char) * (index + 1)));
				if (newString == nullptr)
				{
					free(newString);
					free(hexString);
					return nullptr;
				}
				for (int r = 0; r < sizeof(newString); r++)
				{
					newString[r] = '0';
				}
				for (int k = 0; k < index; k++)
				{
					newString[k + 1] = hexString[k];
				}
				hexString = newString;
				hexString[0] = '0';
				index++;
			}
		}
		else
		{
			uint16_t num = number[i];
			if (i != sze - 1)
			{
				for (int j = 0; j < 4 || num != 0; j++)
				{
					char *newString = (char *)(malloc(sizeof(char) * (index + 1)));
					if (newString == nullptr)
					{
						free(newString);
						free(hexString);
						return nullptr;
					}
					for (int r = 0; r < sizeof(newString); r++)
					{
						newString[r] = '0';
					}
					for (int k = 0; k < index; k++)
					{
						newString[k + 1] = hexString[k];
					}
					hexString = newString;
					uint16_t temp = num % 16;
					hexString[0] = digit(temp);
					index++;
					num /= 16;
				}
			}
			else
			{
				for (int j = 0; j < 4 && num != 0; j++)
				{
					char *newString = (char *)(malloc(sizeof(char) * (index + 1)));
					if (newString == nullptr)
					{
						free(newString);
						free(hexString);
						return nullptr;
					}
					for (int r = 0; r < sizeof(newString); r++)
					{
						newString[r] = '0';
					}
					for (int k = 0; k < index; k++)
					{
						newString[k + 1] = hexString[k];
					}
					hexString = newString;
					uint16_t temp = num % 16;
					hexString[0] = digit(temp);
					index++;
					num /= 16;
				}
			}
		}
	}
	if (negative)
	{
		char *newString = (char *)(malloc(sizeof(char) * (index + 1)));
		if (newString == nullptr)
		{
			free(newString);
			free(hexString);
			return nullptr;
		}
		for (int r = 0; r < sizeof(newString); r++)
		{
			newString[r] = '0';
		}
		for (int k = 0; k < index; k++)
		{
			newString[k + 1] = hexString[k];
		}
		hexString = newString;
		hexString[0] = '-';
	}
	const size_t sss = index + 1;
	char *tmp = (char *)malloc(sizeof(char) * sss);
	if (tmp == nullptr)
	{
		free(tmp);
		free(hexString);
		return nullptr;
	}
	for (int i = 0; i < sss - 1; i++)
	{
		tmp[i] = hexString[i];
	}
	tmp[sss - 1] = '\0';
	return tmp;
}

LN operator""_ln(const char *str)
{
	return LN(str);
}

LN LN::add(const LN &first, const LN &second)
{
	LN sumLN;
	size_t max_size = std::max(first.sze, second.sze);
	uint32_t sum = 0;
	bool extraSpace = false;
	if (first.sze == second.sze)
	{
		sum += first.number[first.sze - 1];
		sum += second.number[first.sze - 1];
		if (sum / (2 << 15) > 0)
		{
			extraSpace = true;
		}
	}
	uint16_t *result;
	if (extraSpace)
	{
		result = (uint16_t *)(malloc(sizeof(uint16_t) * (max_size + 1)));
	}
	else
	{
		result = (uint16_t *)(malloc(sizeof(uint16_t) * (max_size)));
	}
	if (result == nullptr)
	{
		free(result);
		sumLN.isMem = true;
		return sumLN;
	}
	uint16_t carry = 0;
	for (size_t i = 0; i < max_size; i++)
	{
		sum = carry;
		if (i < first.sze)
		{
			sum += first.number[i];
		}
		if (i < second.sze)
		{
			sum += second.number[i];
		}
		carry = sum / (2 << 15);
		result[i] = sum % (2 << 15);
	}
	if (extraSpace)
	{
		result[max_size] = carry;
		sumLN.sze = max_size + 1;
	}
	else
	{
		sumLN.sze = max_size;
	}
	delete[] sumLN.number;
	sumLN.number = result;

	return sumLN;
}

LN LN::sub(const LN &first, const LN &other)
{
	LN minusLN;
	minusLN.negative = false;
	minusLN.isNan = false;
	LN firstArg = first;
	LN secondArg = other;
	if (firstArg == secondArg)
	{
		return LN("0");
	}
	size_t max_size = firstArg.sze;
	size_t memDecrease = 0;
	if (firstArg.sze == secondArg.sze)
	{
		while (firstArg.number[max_size - 1 - memDecrease] == secondArg.number[max_size - 1 - memDecrease])
		{
			memDecrease++;
			if (max_size - 1 - memDecrease == -1)
			{
				memDecrease++;
				break;
			}
		}
	}
	uint16_t *result;
	result = (uint16_t *)(malloc(sizeof(uint16_t) * (max_size - memDecrease)));
	if (result == nullptr)
	{
		free(result);
		minusLN.isMem = true;
		return minusLN;
	}
	uint16_t carry = 0;
	for (size_t i = 0; i < max_size - memDecrease; i++)
	{
		uint32_t minus = carry;
		minus += firstArg.number[i];
		carry = 0;
		if (i < secondArg.sze && secondArg.number[i] > firstArg.number[i])
		{
			minus += (2 << 15);
			minus -= secondArg.number[i];
			carry = -1;
		}
		else if (i < secondArg.sze)
		{
			minus -= secondArg.number[i];
		}
		result[i] = minus;
	}
	minusLN.sze = max_size - memDecrease;
	delete[] minusLN.number;
	minusLN.number = result;

	return minusLN;
}

LN LN::multiply(const LN &first, const LN &other)
{
	LN multiLN;
	for (size_t i = 0; i < other.sze; i++)
	{
		LN temp = first * other.number[i];
		if (temp.isMem)
		{
			multiLN.isMem = true;
			return multiLN;
		}
		temp.sze += i;
		uint16_t *newResult;
		newResult = (uint16_t *)malloc(sizeof(uint16_t) * (temp.sze));
		if (newResult == nullptr)
		{
			free(newResult);
			multiLN.isMem = true;
			return multiLN;
		}
		for (size_t j = 0; j < i; j++)
		{
			newResult[j] = 0;
		}
		for (size_t j = 0; j < temp.sze - i; j++)
		{
			newResult[j + i] = temp.number[j];
		}
		temp.number = newResult;
		multiLN = multiLN + temp;
	}
	return multiLN;
}

std::pair< LN, LN > LN::divide(LN &first, LN &other) const
{
	std::pair< LN, LN > res;
	LN temp;
	LN modul;
	uint16_t left;
	uint16_t middle;
	uint16_t right;
	uint16_t div;
	uint16_t *num;
	uint16_t *arrRes;
	uint16_t *newNum;
	size_t k = other.sze;
	num = (uint16_t *)malloc(sizeof(uint16_t) * (k));
	if (num == nullptr)
	{
		free(num);
		temp.isMem = true;
		modul.isMem = true;
		return std::make_pair(temp, modul);
	}
	for (size_t i = 0; i < k; i++)
	{
		num[i] = first.number[first.sze - k + i];
	}
	if (other > num)
	{
		delete[] num;
		num = (uint16_t *)malloc(sizeof(uint16_t) * (k + 1));
		if (num == nullptr)
		{
			free(num);
			temp.isMem = true;
			modul.isMem = true;
			return std::make_pair(temp, modul);
		}
		for (size_t i = 0; i < k + 1; i++)
		{
			num[i] = first.number[first.sze - k - 1 + i];
		}
		k++;
	}
	size_t lenRes = first.sze - k + 1;
	arrRes = (uint16_t *)malloc(sizeof(uint16_t) * (lenRes));
	if (arrRes == nullptr)
	{
		free(arrRes);
		temp.isMem = true;
		modul.isMem = true;
		return std::make_pair(temp, modul);
	}
	for (size_t i = 0; i < lenRes; i++)
	{
		div = 0;
		left = 0;
		right = UINT16_MAX - 1;
		while (left <= right)
		{
			middle = left + ((right - left) / 2);
			temp = other * middle;
			if (temp > num)
			{
				right = middle - 1;
			}
			else
			{
				div = middle;
				left = middle + 1;
			}
		}
		if (div == 65534)
		{
			temp = other * (div + 1);
			if (!(temp > num))
			{
				div++;
			}
		}
		arrRes[lenRes - 1 - i] = div;
		LN supTemp = LN(num, k);
		temp = other * div;
		modul = supTemp - temp;
		if (modul != LN("0"))
		{
			k = modul.sze + 1;
			newNum = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
			if (newNum == nullptr)
			{
				free(newNum);
				temp.isMem = true;
				modul.isMem = true;
				return std::make_pair(temp, modul);
			}
			if (first.sze - i - 2 >= 0)
			{
				newNum[0] = first.number[first.sze - i - 2];
				for (size_t j = 1; j < k; j++)
				{
					newNum[j] = modul.number[j - 1];
				}
				num = newNum;
			}
		}
		else
		{
			newNum = (uint16_t *)(malloc(sizeof(uint16_t)));
			if (newNum == nullptr)
			{
				free(newNum);
				temp.isMem = true;
				modul.isMem = true;
				return std::make_pair(temp, modul);
			}
			k = 1;
			if (first.sze - i - 2 >= 0)
			{
				newNum[0] = first.number[first.sze - i - 2];
				num = newNum;
			}
		}
	}
	LN result = LN(arrRes, lenRes);
	res = std::make_pair(result, modul);
	return res;
}

LN LN::operator*(uint16_t num) const
{
	LN res;
	res.sze = 0;
	uint16_t *result;
	result = (uint16_t *)(malloc(sizeof(uint16_t) * (sze)));
	if (result == nullptr)
	{
		free(result);
		res.isMem = true;
		return res;
	}
	uint32_t carry = 0;
	for (size_t i = 0; i < sze; i++)
	{
		uint32_t multi = 1;
		multi *= number[i];
		multi *= num;
		multi += carry;
		carry = multi / (2 << 15);
		result[i] = multi % (2 << 15);
	}
	delete[] res.number;
	if (carry != 0)
	{
		uint16_t *newResult;
		newResult = (uint16_t *)realloc(result, sizeof(uint16_t) * (sze + 1));
		if (newResult == nullptr)
		{
			free(number);
			res.isMem = true;
			return res;
		}
		newResult[sze] = carry;
		res.sze++;
		res.number = newResult;
	}
	else
	{
		res.number = result;
	}
	res.sze += sze;
	res.negative = negative;
	return res;
}

LN LN::sqrt(const LN &num)
{
	LN two = LN("2");
	LN one = LN("1");
	LN left = LN("0");
	LN right = num - one;
	LN middle;
	LN result;
	while (left <= right)
	{
		middle = left + ((right - left) / two);
		LN temp = middle * middle;
		if (temp > num)
		{
			right = middle - one;
		}
		else
		{
			result = middle;
			left = middle + one;
		}
	}
	return result;
}

LN LN::makeNaN()
{
	LN res = LN("0");
	res.isNan = true;
	return res;
}

LN::LN(const uint16_t *num, size_t size)
{
	sze = size;
	number = (uint16_t *)(malloc(sizeof(uint16_t) * sze));
	if (number == nullptr)
	{
		free(number);
		isMem = true;
		return;
	}
	for (size_t i = 0; i < sze; i++)
	{
		number[i] = num[i];
	}
}

bool LN::operator>(const uint16_t *second)
{
	for (size_t i = sze; i > 0; i--)
	{
		if (number[i - 1] > second[i - 1])
		{
			return true;
		}
		else if (number[i - 1] < second[i - 1])
		{
			return false;
		}
	}
	return false;
}

char LN::digit(int num)
{
	switch (num)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'A';
	case 11:
		return 'B';
	case 12:
		return 'C';
	case 13:
		return 'D';
	case 14:
		return 'E';
	case 15:
		return 'F';
	}
	return 0;
}

void LN::increaseArraySize(char *&array, size_t currentSize, size_t newSize)
{
	char *newArray = reinterpret_cast< char * >(new char *[newSize]);
	memcpy(newArray, array, sizeof(const char *) * currentSize);
	if (newArray == nullptr)
	{
		throw std::runtime_error("Memory trouble");
	}
	delete[] array;
	array = newArray;
}

void LN::operator+=(const LN &second)
{
	*this = *this + second;
}

void LN::operator-=(LN &second)
{
	*this = *this - second;
}

void LN::operator*=(const LN &second)
{
	*this = *this * second;
}

void LN::operator/=(LN &second)
{
	*this = *this / second;
}

void LN::operator%=(LN &second)
{
	*this = *this % second;
}

LN &LN::operator++()
{
	*this = *this + LN(1);
	return *this;
}

LN LN::operator++(int)
{
	long long res = this->convertToLongLong();
	*this = *this + LN(1);
	return LN(res);
}

LN &LN::operator--()
{
	LN a = LN(1);
	*this = *this - a;
	return *this;
}

LN LN::operator--(int)
{
	long long res = this->convertToLongLong();
	LN a = LN(1);
	*this = *this - a;
	return LN(res);
}

LN LN::operator+() const
{
	return *this;
}

bool LN::hasMem()
{
	return this->isMem;
}
