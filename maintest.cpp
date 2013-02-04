//  main.cpp
//  Sphere Points
//
//  Created by Arvind Rao on 12/30/12.

#include <iostream>
#include <cmath>
#include <string>
#include <random>

int main(int argc, char * argv[])
{
	std::random_device rd;
	std::default_random_engine generator( rd() );
	std::uniform_real_distribution<double> distribution(0.0,10.0);
	
	double number = distribution( generator );
	std::cout<< number << "\n";
	std::cout<< M_PI ;
    return 0;
}

