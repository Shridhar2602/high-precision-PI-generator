#pragma once

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define BASE 64
#define BASE_BITS 6

struct num
{
	vector <int> n;
	int prec = 0;
};

struct div
{
	struct num q;	// quotient
	struct num r;	// remainder 
};

struct num ADD(struct num, struct num, int);
struct num SUB(struct num, struct num, int);
struct num MUL(struct num, struct num, int);
struct num MUL_PREC(struct num, struct num, int, int);
struct num KARATSUBA(struct num, struct num, int);
struct num KARATSUBA_PREC(struct num, struct num, int, int);
struct div DIV(struct num, struct num, int, int);
struct num SQ_ROOT(struct num, int, int);
struct num CALC_PI(int, int);
struct num CALC_PI_KARATSUBA(int, int);

struct num LEFT_SHIFT(struct num, int);
struct num BASE_B_TO_DECIMAL(struct num, int);
struct num REMOVE_LEADING_ZERO(struct num);
int COMPARE(struct num, struct num);
int CHECK_PI(struct num);
int CHECK_SQ_ROOT(struct num);
int PRECISION_IN_BASE_B(int);
int PRINT(struct num);
int PRINT_PREC(struct num, int);