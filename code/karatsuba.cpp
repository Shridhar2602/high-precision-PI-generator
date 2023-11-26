#include "pi.hpp"

struct num KARATSUBA_PREC(struct num a, struct num b, int prec_req, int B)
{
	struct num c = KARATSUBA(a, b, B);

	// precision handling
	c.prec = a.prec + b.prec;

	if(c.prec > prec_req)
	{
		for(int i = 0; i < (c.prec - prec_req); i++)
			c.n.pop_back();

		c.prec = prec_req;
	}

	c = REMOVE_LEADING_ZERO(c);
	return c;
}

struct num KARATSUBA(struct num a, struct num b, int B)
{
	int size_a = a.n.size();
	int size_b = b.n.size();
	int min_size = size_a < size_b ? size_a / 2: size_b / 2;

	if(size_a == 1 || size_b == 1)
	{
		struct num ans;
		ans = MUL(a, b, B);
		return ans;
	}

	struct num la, ra, lb, rb;

	for(int i = 0; i < size_a - min_size ; i++)
		la.n.push_back(a.n[i]);

	for(int i = size_a - min_size; i < size_a; i++)
		ra.n.push_back(a.n[i]);

	for(int i = 0; i < size_b - min_size; i++)
		lb.n.push_back(b.n[i]);

	for(int i = size_b - min_size; i < size_b; i++)
		rb.n.push_back(b.n[i]);

	struct num z0 = KARATSUBA(ra, rb, B);
	struct num z2 = KARATSUBA(la, lb, B);
	struct num z1 = KARATSUBA(ADD(la, ra, B), ADD(rb, lb, B), B);

	z1 = LEFT_SHIFT(SUB(z1, ADD(z2, z0, B), B), min_size);
	z2 = LEFT_SHIFT(z2, min_size * 2);

	struct num ans = ADD(z2, ADD(z1, z0, B), B);

	return ans;
}
