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
    x.print_points();

    return 0;
}

//    typedef double  numType;
//    const int VEC_LENGTH = 3;
//    typedef std::array< numType, VEC_LENGTH>          d_point;
//
//    d_point x = {12,24,35};
//
//    for(int i = 0; i < 3; i++)
//    {
//        std::cout<< " x value at " << i << " is: " << x[i] << "\n";
//    }
