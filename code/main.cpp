/*
	Shridhar Sharma - IMT2020065
	Mayank Chadha - IMT2020045

	NOTE: Our code works correctly only for bases <= 2^13
		  For bases >= 2^14 integer overflow occurs which is a hardware limitation.
*/

#include "pi.hpp"
#include "tester.hpp"

int main(void)
{
	int B = BASE;
	struct num c;
	
	int operation;
	cout << "+------------------------------------------+\n";
	cout << "|        SM404 - NT : Assignment - 1       |\n";
	cout << "|                                          |\n";
	cout << "|              Shridhar Sharma (IMT2020065)|\n";
	cout << "|                Mayank Chadha (IMT2020045)|\n";
	cout << "+------------------------------------------+\n";
	cout << "| 1. SQ_ROOT(2)                            |\n";
	cout << "| 2. PI (Karatsuba)                        |\n";
	cout << "| 3. PI (Using normal MUL)                 |\n";
	cout << "+------------------------------------------+\n";
	cout << "\nEnter your choice: ";
	cin >> operation;

	switch(operation)
	{
		case 1:
		{
			struct num two;
			two.n = {2};
			int prec_req;
			cout << "Enter precision required (in decimal): ";
			cin >> prec_req;
			auto start = high_resolution_clock::now();
			c = SQ_ROOT(two, PRECISION_IN_BASE_B(prec_req), B);
			auto stop = high_resolution_clock::now();
			auto duration1 = duration_cast<microseconds>(stop - start);

			start = high_resolution_clock::now();
			c = BASE_B_TO_DECIMAL(c, B);
			stop = high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(stop - start);

			int tmp2 = CHECK_SQ_ROOT(c);
			cout << endl;
			PRINT_PREC(c, tmp2);
			cout << "\n";
			cout << "+------------------------------------------+\n";
			cout << "Time taken to calculate SQ_ROOT(2): " << (float)duration1.count() / 1000000 << " seconds." << endl;
    		cout << "Time taken to convert SQ_ROOT(2) to decimal: " << (float)duration2.count() / 1000000 << " seconds.\n" << endl;
			cout << "Iterations: " << ceil(log(prec_req)) + 3 << "    Current Precision: " << tmp2 << endl;
			cout << "+------------------------------------------+\n";
			break;
		}

		case 2:
		{
			int prec_req;
			cout << "Enter precision required (in decimal): ";
			cin >> prec_req;
			auto start = high_resolution_clock::now();
			c = CALC_PI_KARATSUBA(PRECISION_IN_BASE_B(prec_req), B);
			auto stop = high_resolution_clock::now();
			auto duration1 = duration_cast<microseconds>(stop - start);

			start = high_resolution_clock::now();
			c = BASE_B_TO_DECIMAL(c, B);
			stop = high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(stop - start);

			int tmp2 = CHECK_PI(c);
			cout << endl;
			PRINT_PREC(c, tmp2);
			cout << "\n";
			cout << "+------------------------------------------+\n";
			cout << "Time taken to calculate pi: " << (float)duration1.count() / 1000000 << " seconds." << endl;
    		cout << "Time taken to convert pi to decimal: " << (float)duration2.count() / 1000000 << " seconds.\n" << endl;
			cout << "Iterations: " << ceil(log(prec_req)) + 3 << "    Current Precision: " << tmp2 << endl;
			cout << "+------------------------------------------+\n";
			break;
		}

		case 3:
		{
			int prec_req;
			cout << "Enter precision required (in decimal): ";
			cin >> prec_req;
			auto start = high_resolution_clock::now();
			c = CALC_PI(PRECISION_IN_BASE_B(prec_req), B);
			auto stop = high_resolution_clock::now();
			auto duration1 = duration_cast<microseconds>(stop - start);

			start = high_resolution_clock::now();
			c = BASE_B_TO_DECIMAL(c, B);
			stop = high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(stop - start);

			int tmp2 = CHECK_PI(c);
			cout << endl;
			PRINT_PREC(c, tmp2);
			cout << "\n";
			cout << "+------------------------------------------+\n";
			cout << "Time taken to calculate pi: " << (float)duration1.count() / 1000000 << " seconds." << endl;
    		cout << "Time taken to convert pi to decimal: " << (float)duration2.count() / 1000000 << " seconds.\n" << endl;
			cout << "Iterations: " << ceil(log(prec_req)) + 3 << "    Current Precision: " << tmp2 << endl;
			cout << "+------------------------------------------+\n";
			break;
		}

		default:
			cout << "Invalid choice!\n";
			break;
	}
}