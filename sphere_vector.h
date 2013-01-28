#ifndef SPHERE_VECTOR_
#define SPHERE_VECTOR_
#define _USE_MATH_DEFINES

/*
 * Sphere_vectors.cpp
 *
 * implements common properties and operations expected
 * of unit vectors when considered as point on S^2.
 *
 * EX.  x - y = 'geodesic distance' between the two points.
 */

#include <cmath>

template< typename TNumType>
class sphere_vector
{

public:

    typedef TNumType numType; // just make header file easier to read. Scope is
                              // local.
    
    sphere_vector(numType _x = 0, numType _y = 0, numType _z = 0);
    ~sphere_vector();
    
    numType get_x() const;
    numType get_y() const;
    numType get_z() const;
    
    sphere_vector<TNumType> operator-(const sphere_vector &vec) const;
    sphere_vector<TNumType> operator+(const sphere_vector &vec) const;
    numType operator*(const sphere_vector &vec) const;
    sphere_vector<TNumType> operator=(const sphere_vector &vec) const;
    
    numType dist( const sphere_vector& x ) const;
    numType operator[](const int index) const;
    
    void print();
    
private:
    numType x, y, z;
};

#include "sphere_vector.cpp"
#endif

