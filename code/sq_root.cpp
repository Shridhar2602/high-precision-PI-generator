#include "pi.hpp"

/* 
	Newton-Raphson iterative method for finding square root
*/
struct num SQ_ROOT(struct num r, int prec_req, int B)
{
	struct num x;
	struct num two;

	two.n = {2};

	// initial guess is R/2
	x = DIV(r, two, prec_req, B).q;

	// Approximating total number of iterations required
	int num_itr = ceil(log2(prec_req)) + 3;

	for(int i = 0; i < num_itr; i++)
	{
		x = DIV(ADD(x, DIV(r, x, prec_req, B).q, B), two, prec_req, B).q;
	}

	return x;
}