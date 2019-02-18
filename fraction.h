# ifndef __FRACTION_H__
# define __FRACTION_H__

class Fraction
{
	private:
		int numerator;
		int denominator;
		void simplify(void);
	public:
		Fraction(int numerator, int denominator);
		Fraction(const Fraction &a);
		Fraction operator = (Fraction a);
		int getNumerator(void);
		int getDenominator(void);
		Fraction operator - (void);
		Fraction operator + (Fraction);
		Fraction operator - (Fraction);
		Fraction operator * (Fraction);
		Fraction operator / (Fraction);
};

# endif
