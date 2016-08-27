#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int MAX = 100;
const int FULL = 10;

struct fraction
{
	int numerator;
	int denominator;
	fraction(void)
	{
		numerator = 0;
		denominator = 1;
	}
	void simplify(void);
	friend fraction operator + (fraction &a, fraction &b);
	friend fraction operator - (fraction &a, fraction &b);
	friend fraction operator * (fraction &a, fraction &b);
	friend fraction operator / (fraction &a, fraction &b);
};

int gcd(int a, int b)//for a > 0 && b > 0
{
	return b > 0 ? gcd(b, a % b) : a;
}

int lcm(int a, int b)//for a > 0 && b > 0
{
	return a * b / gcd(a, b);
}

void fraction::simplify(void)
{
	int temp = gcd(abs(numerator), abs(denominator));
	numerator /= temp;
	denominator /= temp;
	if (numerator * denominator > 0)
	{
		numerator = abs(numerator);
		denominator = abs(denominator);
	}
	else if (numerator * denominator == 0)
	{
		numerator = 0;
		denominator = 1;
	}
	else
	{
		numerator = -abs(numerator);
		denominator = abs(denominator);
	}
}

fraction operator + (fraction &a, fraction &b)
{
	fraction res;
	res.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
	res.denominator = a.denominator * b.denominator;
	res.simplify();
	return res;
}

fraction operator - (fraction &a, fraction &b)
{
	fraction res;
	res.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
	res.denominator = a.denominator * b.denominator;
	res.simplify();
	return res;
}

fraction operator * (fraction &a, fraction &b)
{
	fraction res;
	res.numerator = a.numerator * b.numerator;
	res.denominator = a.denominator * b.denominator;
	res.simplify();
	return res;
}

fraction operator / (fraction &a, fraction &b)
{
	fraction res;
	res.numerator = a.numerator * b.denominator;
	res.denominator = a.denominator * b.numerator;
	res.simplify();
	return res;
}

struct element
{
	char symbol[FULL];//the symbol of an element
	int count;//for number of itom of that element in a substance
};

struct item
{
	char name[MAX];
	fraction count;
	element ele[MAX];
	int ele_cnt;//number of all kinds of elements in the substance
	bool type;//0 for reactant and 1 for resultant
	bool judge(void);
	void fill_ele(char *str, element *ele, int *cnt);
};

bool item::judge(void)
{
	int bracket = 0;
	if (!(name[0] >= 'A' && name[0] <= 'Z') && name[0] != '(' && name[0] != '[')//the first one must be upper letter or '(' or '['
	{
		return false;
	}

	for (int i = 0; name[i] != '\0'; i++)
	{
		if (name[i] >= '0' && name[i] <= '9')//if it is a number and the next one is a lower letter
		{
			if (name[i + 1] >= 'a' && name[i + 1] <= 'z')
			{
				return false;
			}
			if (!(name[i - 1] >= '0' && name[i - 1] <= '9') && name[i] == '0')//numbers begins with 0 is not allowed
			{
				return false;
			}
		}
		if (name[i] == '(' || name[i] == '[')
		{
			if (!(name[i + 1] == '(' || name[i + 1] == '[' || name[i + 1] >= 'A' && name[i + 1] <= 'Z'))
			{
				return false;
			}
			bracket++;
		}
		if (name[i] == ')' || name[i] == ']')
		{
			if (name[i + 1] >= 'a' && name[i + 1] <= 'z')
			{
				return false;
			}
			bracket--;
			if (bracket < 0)
			{
				return false;
			}
		}
	}

	if (bracket != 0)
	{
		return false;
	}
	return true;
}

void item::fill_ele(char *str, element *ele, int *cnt)
{
	*cnt = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == '[')
		{
			int bracket = 0, end;
			for (end = i; str[end] != '\0'; end++)
			{
				if (str[end] == '(' || str[end] == '[')
				{
					bracket++;
				}
				else if (str[end] == ')' || str[end] == ']')
				{
					bracket--;
				}
				if (!bracket)
				{
					break;
				}
			}
			//prepare for recursive call
			char rec[MAX];
			element rec_ele[MAX];
			int rec_cnt;
			for (int j = i + 1; j <= end - 1; j++)
			{
				rec[j - i - 1] = str[j];
			}
			rec[end - i - 1] = '\0';
			item::fill_ele(rec, rec_ele, &rec_cnt);
			//merge
			//read the times
			if (str[end + 1] >= '0' && str[end + 1] <= '9')
			{
				int times = 0, j;
				for (j = end + 1; str[j] >= '0' && str[j] <= '9'; j++)//read the number(it can be more than 10)
				{
					times = times * 10 + str[j] - '0';
				}
				for (int j = 0; j <= rec_cnt - 1; j++)//multiple times
				{
					rec_ele[j].count *= times;
				}
				i = j;
			}
			else
			{
				i = end + 1;
			}

			for (int j = 0; j <= rec_cnt - 1; j++)
			{
				bool find = false;
				for (int k = 0; k <= *cnt - 1; k++)
				{
					if (rec_ele[j].symbol == ele[k].symbol)
					{
						ele[k].count += rec_ele[j].count;
						find = true;
						break;
					}
				}
				if (!find)
				{
					ele[*cnt] = rec_ele[j];
					(*cnt)++;
				}
			}
		}

		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			char temp[FULL];
			temp[0] = str[i];
			int j;
			for (j = i + 1; str[j] >= 'a' && str[j] <= 'z'; j++)
			{
				temp[j - i] = str[j];
			}
			temp[j - i] = '\0';

			int num = 0;
			while (str[j] >= '0' && str[j] <= '9')
			{
				num = num * 10 + str[j] - '0';
				j++;
			}
			num = num == 0 ? 1 : num;
			i = j;//update i

			bool find = false;
			for (int k = 0; k <= *cnt - 1; k++)
			{
				if (strcmp(ele[k].symbol, temp) == 0)
				{
					ele[k].count += num;
					find = true;
					break;
				}
			}

			if (!find)
			{
				strcpy(ele[*cnt].symbol, temp);
				ele[*cnt].count = num;
				(*cnt)++;
			}
		}
	}
}

int input(char *eqt, item *sub)//return the number of substance
{
	int cnt = 0;
	char *equal = NULL, *add[MAX];
	for (int i = 0; eqt[i] != '\0'; i++)
	{
		if (eqt[i] == '=')
		{
			if (equal != NULL)//multiple '='
			{
				return 0;
			}
			equal = &eqt[i];
		}
		else if (eqt[i] == '+')
		{
			add[cnt++] = &eqt[i];
		}
	}

	if (equal == NULL)//no '='
	{
		return 0;
	}

	*equal = '\0';
	for (int i = 0; i <= cnt - 1; i++)
	{
		*add[i] = '\0';
	}
	
	int num, k = 0;
	for (num = 0; num <= cnt + 1; num++)
	{
		strcpy(sub[num].name, &eqt[k]);
		if (!sub[num].judge())
		{
			return 0;
		}
		sub[num].fill_ele(sub[num].name, sub[num].ele, &sub[num].ele_cnt);
		sub[num].type = &eqt[k] < equal ? false : true;

		while (eqt[k] != '\0')
		{
			k++;
		}
		k++;
	}

	return cnt + 2;
}

int getRank(fraction matrix[][MAX], int row, int col)
{
	int i, j, k;
	for (i = 0; i <= row - 1; i++)
	{
		bool find = false;//find the first non-zero element
		for (j = i; j <= col - 1; j++)
		{
			for (k = i; k <= row - 1; k++)
			{
				if (matrix[k][j].numerator != 0)
				{
					find = true;
					break;
				}
			}
			if (find)
			{
				break;
			}
		}
		if (!find)//all of the following are 0
		{
			break;
		}
		//swap
		if (i != k)
		{
			for (int cnt = 0; cnt <= col - 1; cnt++)
			{
				swap(matrix[i][cnt], matrix[k][cnt]);
			}
		}
		//simplify
		for (int r = i + 1; r <= row - 1; r++)
		{
			fraction temp = matrix[r][j] / matrix[i][j];
			for (int c = j; c <= col - 1; c++)
			{
				fraction ls = temp * matrix[i][c];
				matrix[r][c] = matrix[r][c] - ls;
			}
		}
	}
	//calculate rank
	int cnt = 0;
	for (i = 0; i <= row - 1; i++)
	{
		for (j = 0; j <= col - 1; j++)
		{
			if (matrix[i][j].numerator != 0)
			{
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

void deal(item *sub, int cnt)//cnt is the number of the substance
{
	fraction matrix[MAX][MAX];
	char all_ele[MAX][FULL];
	int row = 0, &col = cnt;//row equals to the number of all different elements and col equals to the number of substance
	for (int i = 0; i <= cnt - 1; i++)
	{
		for (int j = 0; j <= sub[i].ele_cnt - 1; j++)
		{
			bool find = false;
			for (int k = 0; k <= row - 1; k++)
			{
				if (strcmp(sub[i].ele[j].symbol, all_ele[k]) == 0)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				strcpy(all_ele[row], sub[i].ele[j].symbol);
				row++;//number of all elements + 1
			}
		}
	}

	for (int i = 0; i <= row - 1; i++)//check all the elements
	{
		for (int j = 0; j <= col - 1; j++)//for each element, check all the substance(wether it contains such element)
		{
			for (int k = 0; k <= sub[j].ele_cnt - 1; k++)//check all the elements of each substance
			{
				if (strcmp(sub[j].ele[k].symbol, all_ele[i]) == 0)
				{
					matrix[i][j].numerator = sub[j].type == false ? sub[j].ele[k].count : -sub[j].ele[k].count;
					break;
				}
			}
		}
	}
	//get rank
	int rank = getRank(matrix, row, col);
	int solution = col - rank;
	if (col == rank)
	{
		cout << "No Solution!" << endl;
	}
	//find all the possible solutions
	else if (col - rank == 1)
	{
		sub[rank].count.numerator = 1;//set the last one's cof 1
		for (int i = rank - 1; i >= 0; i--)//i = rank - 1 means to start with a non-zero row which row-number is the largest
		{
			fraction temp;
			for (int j = col - 1; j >= i + 1; j--)
			{
				fraction ls = matrix[i][j] * sub[j].count;
				temp = temp + ls;
			}
			sub[i].count = temp / matrix[i][i];
			sub[i].count.denominator = -sub[i].count.denominator;
			sub[i].count.simplify();
		}
		//adjust cof
		int mul = 1;
		for (int i = 0; i <= cnt - 1; i++)
		{
			mul = lcm(mul, sub[i].count.denominator);
		}
		fraction temp;
		temp.numerator = mul;
		for (int i = 0; i <= cnt - 1; i++)
		{
			sub[i].count = sub[i].count * temp;
		}
		//print
		for (int i = 0; i <= cnt - 1; i++)
		{
			if (sub[i].count.numerator != 1 && sub[i].count.numerator != 0)
			{
				cout << sub[i].count.numerator;
			}
			if (sub[i].count.numerator != 0)
			{
				cout << sub[i].name;
			}
			if (sub[i].type == false && sub[i + 1].type == false || sub[i].type == true && i != cnt - 1)
			{
				cout << "+";
			}
			if (sub[i].type == false && sub[i + 1].type == true)
			{
				cout << "=";
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Multiple Solutions!" << endl;
	}
}

int main(void)
{
	char eqt[MAX];
	item sub[MAX];
	int cnt;
	while (cin >> eqt)
	{
		cnt = input(eqt, sub);
		if (cnt == 0)
		{
			cout << "wrong input" << endl;
		}
		else
		{
			deal(sub, cnt);
		}
	}
	return 0;
}