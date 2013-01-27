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
    
private:
    typedef TNumType numType;
    TNumType x, y, z;

public:

    sphere_vector(numType _x = 0, numType _y = 0, numType _z = 0);
    ~sphere_vector();
    
    TNumType get_x() const;
    TNumType get_y() const;
    TNumType get_z() const;
    
    TNumType operator-(const sphere_vector &vec) const;
    TNumType operator*(const sphere_vector &vec) const;
    TNumType operator[](const int index) const;
    
    void print();
};

#include "sphere_vector.cpp"
#endif

