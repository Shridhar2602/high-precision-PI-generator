#include "pi.hpp"

struct num SUB(struct num a, struct num b, int B)
{
	int carry = 0;
	int tmp = 0;
	int swapped;
	struct num c;
	
	// ============== Precision handling ==============
	if(a.prec != b.prec)
	{
		if(a.prec > b.prec)
		{
			c.prec = a.prec;

			tmp = a.prec - b.prec;
			for(int i = 0; i < tmp; i++)
				b.n.push_back(0);
		}

		else
		{
			c.prec = b.prec;
		
			tmp = b.prec - a.prec;
			for(int i = 0; i < tmp; i++)
				a.n.push_back(0);
		}
	}

	else
		c.prec = a.prec;
	// ================================================

	if(a.n.size() < b.n.size())
		a.n.swap(b.n);

	for(int i = b.n.size() - 1, j = a.n.size() - 1; i >= 0; i--, j--)
	{
		tmp = a.n[j] - b.n[i] + carry;
		
		if(tmp < 0)
		{
			c.n.insert(c.n.begin(), tmp + B);
			carry = -1;
		}

		else
		{
			c.n.insert(c.n.begin(), tmp);
			carry = 0;
		}
	}

	for(int i = a.n.size() - b.n.size() - 1; i >= 0; i--)
	{
		tmp = a.n[i] + carry;
		
		if(tmp < 0)
		{
			c.n.insert(c.n.begin(), tmp + B);
			carry = -1;
		}

		else
		{
			c.n.insert(c.n.begin(), tmp);
			carry = 0;
		}
	}

	if(carry == -1)
	{
		struct num base;
		base.n.push_back(B);

		struct num tmp;
		tmp.n.push_back(1);

		for(int i = 0; i < a.n.size(); i++)
			tmp.n.push_back(0);

		tmp.prec = c.prec;
		c = SUB(tmp, c, B);
	}

	c = REMOVE_LEADING_ZERO(c);
	return c;
}
