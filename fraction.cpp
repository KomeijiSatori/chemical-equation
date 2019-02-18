#include "fraction.h"
#include "utils.h"

Fraction::Fraction(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw "Denominator can't be zero";
    }
    this->numerator = numerator;
    this->denominator = denominator;
	simplify();
}

Fraction::Fraction(const Fraction &a)
{
	this->numerator = a.numerator;
	this->denominator = a.denominator;
}

Fraction Fraction::operator = (Fraction a)
{
	this->numerator = a.numerator;
	this->denominator = a.denominator;
	return a;
}

int Fraction::getNumerator(void)
{
	return this->numerator;
}

int Fraction::getDenominator(void)
{
	return this->denominator;
}

void Fraction::simplify(void)
{
	int temp = gcd(numerator, denominator);
	this->numerator /= temp;
	this->denominator /= temp;
	if (this->numerator >= 0 && this->denominator < 0)
	{
		this->numerator /= -1;
		this->denominator /= -1;
	}
}

Fraction Fraction::operator - (void)
{
	Fraction res(0, 1);
	res.numerator = -this->numerator;
	res.denominator = this->denominator;
	res.simplify();
	return res;
}

Fraction Fraction::operator + (Fraction a)
{
	Fraction res(0, 1);
	res.numerator = this->numerator * a.denominator + this->denominator * a.numerator;
	res.denominator = this->denominator * a.denominator;
	res.simplify();
	return res;
}

Fraction Fraction::operator - (Fraction a)
{
	Fraction res(0, 1);
	res.numerator = this->numerator * a.denominator - this->denominator * a.numerator;
	res.denominator = this->denominator * a.denominator;
	res.simplify();
	return res;
}

Fraction Fraction::operator * (Fraction a)
{
	Fraction res(0, 1);
	res.numerator = this->numerator * a.numerator;
	res.denominator = this->denominator * a.denominator;
	res.simplify();
	return res;
}

Fraction Fraction::operator / (Fraction a)
{
	if (a.numerator == 0)
	{
		throw "Divided by zero";
	}
	Fraction res(0, 1);
	res.numerator = this->numerator * a.denominator;
	res.denominator = this->denominator * a.numerator;
	res.simplify();
	return res;
}
