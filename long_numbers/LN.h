#ifndef LONGOPERAATIONS_LN_H
#define LONGOPERAATIONS_LN_H

#include "return_codes.h"

#include <cstring>
#include <iostream>
#include <limits>

class LN
{
  public:
	LN();

	explicit LN(long long num);

	explicit LN(const std::string_view &hexString);

	explicit LN(const char *hexChar);

	LN operator=(const LN &other);

	bool operator==(const LN &other) const;

	bool operator!=(const LN &other) const;

	bool operator>(const LN &other) const;

	bool operator<(const LN &other) const;

	bool operator<=(const LN &other) const;

	bool operator>=(const LN &other) const;

	LN operator-() const;

	LN operator+() const;

	LN operator+(const LN &second) const;

	void operator+=(const LN &second);

	LN &operator++();

	LN operator++(int);

	LN operator-(LN &second) const;

	void operator-=(LN &second);

	LN &operator--();

	LN operator--(int);

	LN operator*(const LN &second);

	void operator*=(const LN &second);

	LN operator/(LN &second);

	void operator/=(LN &second);

	LN operator%(LN &second);

	void operator%=(LN &second);

	LN operator~() const;

	long long convertToLongLong() const;

	bool isNull() const;

	char *appear() const;

	bool hasMem();

  private:
	static LN add(const LN &first, const LN &second);

	static LN sub(const LN &first, const LN &other);

	LN multiply(const LN &first, const LN &other);

	std::pair< LN, LN > divide(LN &first, LN &other) const;

	LN operator*(uint16_t num) const;

	static LN sqrt(const LN &num);

	static LN makeNaN();

	LN(const uint16_t *num, size_t size);

	bool operator>(const uint16_t *second);

	static char digit(int num);

	static void increaseArraySize(char *&array, size_t currentSize, size_t newSize);

	uint16_t *number;
	size_t sze;
	bool isNan = false;
	bool negative = false;
	bool isMem = false;
};

LN operator""_ln(const char *str);

#endif	  // LONGOPERAATIONS_LN_H
