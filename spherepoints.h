/*
 *  spherepoints.h is a class that seeds S^2 with N uniformly
 *  distributed points. Addtionally functionality is provided,
 *  such as flowing the points.
 *
 *  Copyright @2012 Arvind S. Rao
 *  License: GNU
 */

#ifndef SPHEREPOINTS_
#define SPHEREPOINTS_
#define _USE_MATH_DEFINES

#include <iostream>
#include <array>
#include <random>
#include <cmath>

template< int N = 10 >
class SpherePoints
{
private:
    
    enum { VEC_LENGTH = 3 };
    typedef double                                    numType;
    typedef std::array< numType, VEC_LENGTH>          d_point;
    std::array<d_point, N>                             points;
    
    /*
     * Convert spherical coordinates into euclidean coordinates
     *
     * phi = azimuth angle
     * theta = elevation angle
     */
    
    void coords(d_point &point, numType phi, numType theta);
    
public:
    
    //default Constructor
    SpherePoints();
    
    //default deconstructor
    ~SpherePoints();
    
    void print(){ std::cout<< "yo!!";}
    
    void print_points();
};

#include "spherepoints.cpp"
#endif