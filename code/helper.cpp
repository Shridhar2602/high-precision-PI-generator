#include "pi.hpp"
#include "tester.hpp"

struct num REMOVE_LEADING_ZERO(struct num v)
{
	if(v.prec == 0)
	{
		while(v.n.size() > 1 && v.n[0] == 0)
			v.n.erase(v.n.begin());
	}

	else
	{
		int size = v.prec + 1;
		while(v.n.size() > size && v.n[0] == 0)
			v.n.erase(v.n.begin());
	}

	return v;
}

int PRECISION_IN_BASE_B(int prec)
{
	return ceil((prec * log2(10)) / BASE_BITS) + 3;
}

int CHECK_PI(struct num pi)
{
	int precision = 0;
	int size = pi.n.size();
	
	for(auto i = 1; i < size; i++)
	{
		if(pi.n[i] == (PI[i + 1] - 48))
			precision++;
		else
			break;
	}

	return precision;
}

int CHECK_SQ_ROOT(struct num root_two)
{
	int precision = 0;
	int size = root_two.n.size();
	
	for(auto i = 1; i < size; i++)
	{
		if(root_two.n[i] == (ROOT_2[i + 1] - 48))
			precision++;
		else
			break;
	}

	return precision;
}

struct num BASE_B_TO_DECIMAL(struct num x, int B)
{
	struct num base;
	struct num decimal;
	struct num B_pow;
	struct num temp;
	base.n = {B};
	decimal.n = {0};
	B_pow.n = {1};

	int size = x.n.size();
	int size_prec = size - x.prec;

	for(auto i = size_prec - 1; i >= 0; i--)
	{
		temp.n.push_back(x.n[i]);
		decimal = ADD(decimal, MUL(temp, B_pow, 10), 10);
		B_pow = MUL(B_pow, base, 10);
		temp.n.pop_back();
	}

	B_pow.n = {1};

	int prec_req = BASE_BITS;
	int tmp = B;
	int tmp2 = prec_req;

	base.n = {};
	while(B != 0)
	{
		base.n.push_back(B % 10);
		B /= 10;
	}

	reverse(base.n.begin(), base.n.end());

	for(auto i = size_prec; i < size; i++)
	{
		temp.n.push_back(x.n[i]);
		B_pow = DIV(B_pow, base, prec_req, 10).q;
		decimal = ADD(decimal, MUL_PREC(temp, B_pow, prec_req, 10), 10);
		prec_req += tmp2;
		temp.n.pop_back();
	}

	return decimal;
}

struct num LEFT_SHIFT(struct num n, int bits)
{
	for(int i = 0; i < bits; i++)
		n.n.push_back(0);

	return n;
}

int COMPARE(struct num a, struct num b)
{
	int size_a = a.n.size();
	int size_b = b.n.size();
	
	if(size_a - a.prec < size_b - b.prec)
		return 0;

	else if(size_a - a.prec > size_b - b.prec)
		return 1;

	else
	{
		int size_min = size_a < size_b ? size_a : size_b;
		for(int i = 0; i < size_min; i++)
		{
			if(a.n[i] < b.n[i])
				return 0;

			else if(a.n[i] > b.n[i])
				return 1;

		}
	}

	if(size_a < size_b)
		return 0;

	return 1;
}

int PRINT(struct num v)
{
	for(int i = 0; i < v.n.size(); i++)
	{
		if(v.n.size() - i == v.prec)
			cout << "."; 

		cout << v.n[i];
	}

	cout << endl;
	return 0;
}

int PRINT_PREC(struct num v, int prec_req)
{
	int size = v.n.size() - v.prec + prec_req;
	for(int i = 0; i < size; i++)
	{
		if(v.n.size() - i == v.prec)
			cout << "."; 

		cout << v.n[i];
	}

	cout << endl;
	return 0;
}