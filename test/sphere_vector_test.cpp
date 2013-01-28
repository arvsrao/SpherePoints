/*
*
*	Test functionality of sphere_vector operations
*
*	author: Arvind Rao
*	date : 1/26/2013
*   license: GNU
*/

#include <iostream>
#include "../sphere_vector.h"
#include <cmath>

const double tolerance = 1e-4;

void dot_product_test( sphere_vector<double> &x, sphere_vector<double> &y, double expected)
{
	
	if( std::abs((x * y) - expected) < tolerance)
		std::cout<< "dot product PASSED test\n";
	else
		std::cout<< "dot product FAILED test\n";
}

void distance_test( sphere_vector<double> &x, sphere_vector<double> &y, double expected)
{
	
	if( (std::abs( x.dist(y) ) - expected) < tolerance)
		std::cout<< "geodesic distance test PASSED\n";
	else
		std::cout<< "geodesic distance test FAILED \n";
}

void subtract_test( sphere_vector<double> &x, sphere_vector<double> &y, sphere_vector<double> &expected)
{
	bool result = true;
    
    sphere_vector<double> sum = x-y;
    
    for( int i =0; i <3 ; i++ )
    {
        if( std::abs(sum[i] - expected[i]) > tolerance)
            result = false;
    }
    
	if(result)
		std::cout<< "Vector Subtraction test PASSED\n";
	else
		std::cout<< "Vector Subtraction test FAILED \n";
}

void add_test( sphere_vector<double> &x, sphere_vector<double> &y, sphere_vector<double> &expected)
{
	bool result = true;
    
    sphere_vector<double> sum = x+y;
    
    for( int i =0; i <3 ; i++ )
    {
        if( std::abs(sum[i] - expected[i]) > tolerance)
            result = false;
    }
    
	if(result)
		std::cout<< "Vector Addition test PASSED\n";
	else
		std::cout<< "Vector Addition test FAILED \n";
}

void array_index_test( sphere_vector<double> &x)
{
	bool result = true;

	if( (x[0] - x.get_x()) > tolerance)
		result = false;
	if( (x[1] - x.get_y()) > tolerance)
        result = false;
	if( (x[2] - x.get_z()) > tolerance)
        result = false;

	if(result)
		std::cout<< "array index test PASS\n";
	else
		std::cout<< "array index test FAIL\n";
}

void initialization_test()
{
    try
	{
		sphere_vector<double> first(0.983319, 0.0686227, 0.168447);
		sphere_vector<double> second(0.253845, -0.634348, 0.730182);
    	std::cout<< "Instantiation test PASS\n";
	}
	catch(...)
	{
		std::cerr<< "Instantiation test FAIL\n";
    }
    
}


void print_test()
{
    sphere_vector<double> first(0.983319, 0.0686227, 0.168447);
    sphere_vector<double> second(0.253845, -0.634348, 0.730182);

    try
	{
		first.print();
		second.print();
		std::cerr<< "print sphere_vector test PASS";
	}
	catch(...)
	{
		std::cerr<< "print sphere_vector test FAIL";
	}
}

int main()
{
    initialization_test();
    
    sphere_vector<double> first(0.983319, 0.0686227, 0.168447);
    sphere_vector<double> second(0.253845, -0.634348, 0.730182);
    sphere_vector<double> sum(1.237164 , -0.5657253,  0.898629);
    sphere_vector<double> diff(0.729474 ,  0.7029707, -0.561735);
    
	dot_product_test(first, second, 0.329077);
    
	array_index_test(first);
	array_index_test(second);
    
    distance_test(first, second, 1.2354703587330047);
    
    add_test(first, second, sum );
    subtract_test(first, second, diff );
    
	return 0;
}