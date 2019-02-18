# Introduction

This program aims to judge if the equation can be solved and give the answer.

Notice that it can't judge whether the equation is valid.

For example, HF + I2 = HI + F2, it may not happen but can still be solved.

# How to use it

First make the project
`make && make clean`

Then run the project
`./main`

Then input an equation, and then the program will give you the result.

End input by EOF.

## Real Examples with only one answer:

C2H2 + H2 = CH4

H2O + Fe = Fe3O4 + H2

Cu + HNO3 = Cu(NO3)2 + NO2 + H2O

KMnO4 + NaOH + PH3 = K2MnO4 + Na2MnO4 + Na3PO4 + H2O

CrCl3 + KMnO4 + H2O = K2Cr2O7 + MnCl2 + HCl + MnCr2O7

Fe2(SO4)3 + H2O + Na2CO3 = Na2Fe6(SO4)4(OH)12 + Na2SO4 + CO2

K2Cr2O7 + CH3CH2OH + H2SO4 = Cr2(SO4)3 + CH3COOH + K2SO4 + H2O

CuCl2 + NH3H2O = [Cu(NH3)4]Cl2 + H2O

## Real Examples with multiple answers:

C + O2 = CO + CO2

C2H2 + H2 = CH4 + CH3CH3

## Real Examples with no answers:

H2O = H2O + H2 + O2

Fe = Au

## Fake Example with only one answer

A + B + C + D + E + F + G + H + I + J + K + L + M + N = A2B([C2D(EF[GH4]3IJK)3]4L2)3MN3

## Fake Example with no answers

ABCDEFGHIJKLMN = A2B([C2D(EF[GH4]3IJK)3]4L2)3MN3

# How does it work
## File structure

### 1. utils.h

Provide gcd and lcm function.

### 2. substance.h

Provide a class to describe chemicals, including name and elements it contains and the count.
This is a core file, it mainly parse the chemical string to element map.

### 3. helper.h

Provides basic Gaussian elimination to solve the matrix. Then give out the lcm of coefficient.

### 4. fraction.h

Provide basic class for fraction operator.

### 5. format.h

Provide function to parse input string and format the output result.

## Main idea

The main process is list below.
1. parse input string, get the reactant and the resultant.
2. parse each reactant and resultant, get the map of element and count.
3. build a matrix base on element conservation, for each element, build a equation, the coefficients become a row of matrix.
4. use Gaussian elimination to solve the matrix, then get the result.
5. parse the result into string, and output the string.

And the most difficult part is 2 and 4.

For 2, I use DFA to parse the chemical string, it has 6 states. And the meaning of each state is described in the code. And I use a stack
to deal with `()` and `[]`, like building a calculator. There are many corner cases here, and I comment them in the code.

For 4, I transform the origin matrix to upper triangular matrix, and judge the result by the matrix's rank(one solution, no solutions, multiple solutions).
If there's only one solution, then I set the last chemical's coefficient 1, and then determine others' coefficient. Lastly convert fraction coefficient to integer coefficient using lcm.
There are many corner cases too.

If you find any bug, please write an email to me, Thank you very much!
