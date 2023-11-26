#include "pi.hpp"

struct num MUL(struct num a, struct num b, int B)
{
	int carry, tmp, j;

	struct num c;

	tmp = a.n.size() + b.n.size();
	for(int i = 0; i < tmp; i++)
		c.n.push_back(0);

	if(a.n.size() < b.n.size())
		a.n.swap(b.n);

	for(int i = b.n.size() - 1; i >= 0; i--)
	{
		carry = 0;

		for(j = a.n.size() - 1; j >= 0; j--)
		{
			tmp = a.n[j]*b.n[i] + c.n[i+j+1] + carry;
			carry = 0;
			int tmp_cpy = tmp;
			while(tmp_cpy >= 0)
			{
				tmp_cpy -= B;
				carry++;
			}

			carry--;
			c.n[i+j+1] = tmp - carry*B;
		}

		if(carry >= 0)
			c.n[i+j+1] = carry;
	}

	c = REMOVE_LEADING_ZERO(c);
	return c;
}

struct num MUL_PREC(struct num a, struct num b, int prec_req, int B)
{
	struct num c = MUL(a, b, B);
	c.prec = a.prec + b.prec;

	if(c.prec > prec_req)
	{
		int tmp = c.prec - prec_req;
		for(int i = 0; i < tmp; i++)
			c.n.pop_back();

		c.prec = prec_req;
	}

	c = REMOVE_LEADING_ZERO(c);
	return c;
}