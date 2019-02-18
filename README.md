# chemical-equation-solver
Judge if the equation can be solved and give the answer
Notice that it can't judge whether the equation is valid.
For example, HF + I2 = HI + F2, it may not happen but can still be solved.

Input end by EOF

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
