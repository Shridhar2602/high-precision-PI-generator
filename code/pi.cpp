#include "pi.hpp"

/*
	Borwein's exp-2 Algorithm to calculate pi
*/
struct num CALC_PI(int prec_req, int B)
{
	// Calculating for x digits after decimal gives (x - 2) correct digits irrespective of no. of iterations
	prec_req += 2;	

	struct num a, b, p, one, two;

	two.n = {2};
	a = SQ_ROOT(two, prec_req, B);

	one.n = {1};
	b.n = {0};
	p = ADD(two, a, B);

	// Approximation for number of iterations
	int num_iterations = ceil(log(prec_req)) + 3;

	for(int i = 0; i < num_iterations; i++)
	{
		struct num tmp = SQ_ROOT(a, prec_req, B);
		struct num a0 = a;
    
		a = DIV(ADD(tmp, DIV(one, tmp, prec_req, B).q, B), two, prec_req, B).q;
		b = DIV(MUL_PREC(ADD(one, b, B), tmp, prec_req, B), ADD(a0, b, B), prec_req, B).q;
		p = DIV(MUL_PREC(ADD(one, a, B), MUL_PREC(p, b, prec_req, B), prec_req, B), ADD(one, b, B), prec_req, B).q;
	}

	return p;
}

struct num CALC_PI_KARATSUBA(int prec_req, int B)
{
	prec_req += 2;

	struct num a, b, p, one, two;

	two.n = {2};
	a = SQ_ROOT(two, prec_req, B);

	one.n = {1};
	b.n = {0};
	p = ADD(two, a, B);

	int num_itr = ceil(log(prec_req)) + 3;

	for(int i = 0; i < num_itr; i++)
	{
		struct num tmp = SQ_ROOT(a, prec_req, B);
		struct num a0 = a;
    
		a = DIV(ADD(tmp, DIV(one, tmp, prec_req, B).q, B), two, prec_req, B).q;
		b = DIV(KARATSUBA_PREC(ADD(one, b, B), tmp, prec_req, B), ADD(a0, b, B), prec_req, B).q;
		p = DIV(KARATSUBA_PREC(ADD(one, a, B), KARATSUBA_PREC(p, b, prec_req, B), prec_req, B), ADD(one, b, B), prec_req, B).q;
	}

	return p;
}