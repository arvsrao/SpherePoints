/*
 *  spherepoints.h is a class that seeds S^2 with N uniformly
 *  distributed points. Addtionally functionality is provided,
 *  such as flowing these points so they are equidistant. 
 *
 *  Copyright @2012 Arvind S. Rao
 *  License: GNU
 */

#ifndef SPHEREPOINTS_
#define SPHEREPOINTS_
#define _USE_MATH_DEFINES

#include "sphere_vector.h"
#include <random>
#include <cmath>

class SpherePoints
{

public:
    typedef double                                       numType;
    typedef sphere_vector< numType >                     s_point;
    
    //default Constructor
    SpherePoints(int _n = 10);
    
    //default deconstructor
    ~SpherePoints();
    
    void print_points();

private:
    
	const int N;
    enum { VEC_LENGTH = 3 };
    std::vector<s_point>                                  points;
    
    /*
     * Convert spherical coordinates into euclidean coordinates
     *
     * phi = azimuth angle
     * theta = elevation angle
     */
    
    sphere_vector<numType> coords( numType phi, numType theta);
};

#include "spherepoints.cpp"
#endif
