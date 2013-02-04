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
#include <list>

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
    void test_dprod();
    void gradient_descent(short int num_iterations);

private:
    
	const int N;
    enum { VEC_LENGTH = 3 };
    
    // points are stored in a linked list
    std::list<s_point>                                  points;
    
    /*
     * Convert spherical coordinates into euclidean coordinates
     *
     * phi = azimuth angle
     * theta = elevation angle
     */
    
    sphere_vector<numType> coords( numType phi, numType theta);


    /*
     * Compute Couloumb Energy imparted on a point by another point.
     *
     */
    numType energy( const sphere_vector<numType>& p, const sphere_vector<numType>& q);
    
    /* counter-clockwise motion in the direction of the tangent.
     *  spherical geodesics are great circles. So, the exponential map is curve along the
     *  great circle which is the intersection of the sphere with the plane determined by
     *  the tangent vector and the point.
     *
     */
    sphere_vector<numType> exp_map( const sphere_vector<numType> & tangent, const sphere_vector<numType>& point, const numType& time_step);

    sphere_vector<numType>& grad_dist( sphere_vector<numType>& p, sphere_vector<numType>& q, sphere_vector<numType>& temp);
    
};

#include "spherepoints.cpp"
#endif
