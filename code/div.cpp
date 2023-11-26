#include "pi.hpp"

struct div DIV(struct num a, struct num b, int prec_req, int B)
{
	struct div ans;
	struct num q;
	int carry = 0, tmp = 0;

	// When the dividend is smaller than divisor and precison is not required -> q = 0 and r = a
	if(prec_req == 0)
	{
		if(!COMPARE(a, b))
		{
			ans.q.n.push_back(0);
			ans.r = a;

			return ans;	
		}
	}

	// ============== Precision handling ==============
	if(a.prec < b.prec)
	{
		tmp = b.prec - a.prec;
		for(int i = 0; i < tmp; i++)
			a.n.push_back(0);
	}

	else if(a.prec > b.prec)
		q.prec = a.prec - b.prec;

	tmp = prec_req - q.prec;
	for(int i = 0; i < tmp; i++)
		a.n.push_back(0);
	// ===============================================

	// ============== Normalization ==============
	int normalized = 0;
	struct num normalizing_factor;
	if( (b.n[0] * b.n[0]) < B )
	{
		normalized = 1;

		struct num two;
		normalizing_factor.n.push_back(1);
		two.n.push_back(2);

		while((b.n[0] * b.n[0]) < B)
		{
			a = MUL(a, two, B);
			b = MUL(b, two, B);
			normalizing_factor = MUL(normalizing_factor, two, B);
		}
	}
	// ===========================================

	reverse(a.n.begin(), a.n.end());
	reverse(b.n.begin(), b.n.end());

	int l = b.n.size();
	int k = a.n.size();

	for(int i = 0; i < k - l + 1; i++)
		q.n.push_back(0);

	// r = remainder 
	struct num r;
	r = a;
	r.n.push_back(0);

	// finding quotient starting from the msb
	for(int i = k - l; i >= 0; i--)
	{
		q.n[i] = (r.n[i + l] * B + r.n[i + l - 1]) / b.n[l - 1];

		if(q.n[i] >= B)
			q.n[i] = B - 1;

		carry = 0;
		for(int j = 0; j < l; j++)
		{
			// tmp = r[i+j] - q[i]*b[j] + carry
			// ( carry, r[i+j] ) <--- DIV(tmp, carry) 

			tmp = r.n[i + j] - (q.n[i] * b.n[j]) + carry;
			carry = 0;
			int tmp_cpy = tmp;

			if(tmp_cpy >= 0)
			{
				while(tmp_cpy >= 0)
				{
					tmp_cpy -= B;
					carry++;
				}

				carry--;
				r.n[i + j] = tmp - carry * B;
			}

			else
			{
				while(tmp_cpy < 0)
				{
					tmp_cpy += B;
					carry--;
				}

				r.n[i + j] = tmp - (carry * B);
			}
		}

		r.n[i + l] += carry;

		while(r.n[i + l] < 0)
		{
			carry = 0;

			for(int j = 0; j < l; j++)
			{
				tmp = r.n[i + j] + b.n[j] + carry;
				carry = 0;
				int tmp_cpy = tmp;	

				if(tmp_cpy >= 0)
				{
					while(tmp_cpy >= 0)
					{
						tmp_cpy -= B;
						carry++;
					}

					carry--;
					r.n[i + j] = tmp - carry * B;
				}

				else
				{
					while(tmp_cpy < 0)
					{
						tmp_cpy += B;
						carry--;
					}

					r.n[i + j] = tmp - (carry * B);
				}
			}

			r.n[i + l] += carry;
			q.n[i] -= 1;
		}
	}

	reverse(q.n.begin(), q.n.end());
	reverse(r.n.begin(), r.n.end());

	// ============== Precision handling ==============
	tmp = prec_req - q.prec;
	for(int i = 0; i < tmp; i++)
	{
		a.n.pop_back();
	}

	if(a.prec < b.prec)
	{
		tmp = b.prec - a.prec;
		for(int i = 0; i < tmp; i++)
			a.n.pop_back();
	}

	if(q.prec < prec_req)
		q.prec = prec_req;

	// ================================================

	q = REMOVE_LEADING_ZERO(q);
	r = REMOVE_LEADING_ZERO(r);

	// ============== Normalization ==============
	if(normalized)
	{
		ans = DIV(r, normalizing_factor, 0, B);
		r = ans.q;
		r = REMOVE_LEADING_ZERO(r);
	}
	// ===========================================

	ans.q = q;
	ans.r = r;

	return ans;
}