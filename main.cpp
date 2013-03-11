//
//  main.cpp
//  Sphere Points
//
//  Created by Arvind Rao on 12/30/12.

#include <iostream>
#include "spherepoints.h"
#include "sphere_vector.h"

int main(int argc, char ** argv)
{
    int n;
    
    if( argc < 2)
    {
        std::cerr<< "Must include a number!!\n";
        return 0;
    }
    
    n = std::atoi( argv[1] );
    SpherePoints x(n);
    //x.print_points();
    
    x.gradient_descent(200);
    //std::cout<< "The points after 10 iterations of gradient descent.\n\n";
    x.print_points();
    
    return 0;
}