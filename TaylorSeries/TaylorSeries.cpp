#include <math.h>
#include <iostream> 
#define PI 3.1415926535

double sin(double arg, int n) {
	// dynamic programming/memorization  approach + angle [0, PI/2] 
	// series  (n=0, inf) (-1)^n (x^(2n+1)/(2n+1)!)
	double pow = arg; 
	double fact = 1;
	double sin = 0; // result 	
	int sign = 1; // either -1 or 1 
	for ( int i = 0; i < n; i++ ) { 
		sin  +=  sign / fact * pow;
		sign = -sign;
		pow *= arg*arg; // next odd power 
		fact *= ((i*2) + 2) * ((i*2) + 3); // next odd factorial 
	}
	return sin;	
}

double constrainAngle (double& arg) { 
	// if 1st quarter -> just arg 
	// if 2nd quarter -> PI -arg 
	// if 3rd quarter -> arg -PI
	// if 4th quarter -> 2PI -arg 
 	arg = fmod(arg,2*PI); 
	if ( arg < 0  ) { 
		arg += 2*PI;
	}
	return arg;
}


int main() {
	int prec;
	double arg;
	int op;
	double rad;
	std::cout << "Select angle type of degrees (0) or radians (1)" << std::endl;
	std::cin >> op;
	std::cout << "Enter " << (op == 0? "degrees" : "radians") << " and precision:" << std::endl;
	std::cin >> arg >> prec;
	rad = arg; 
	if (op == 0) { 
		rad *= PI/180; // converting degrees to radians 
	}
	rad = constrainAngle(rad); 
	std::cout.precision(17);
	std::cout << "sin(" << arg << ") = " << sin(rad, prec) << std::endl;

	return 0;
}	

