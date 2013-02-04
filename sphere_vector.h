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
    
    sphere_vector<TNumType> operator-(const sphere_vector<TNumType> &vec) const;
    sphere_vector<TNumType> operator+(const sphere_vector<TNumType> &vec) const;
    
    TNumType operator*(const sphere_vector &vec) const;
    sphere_vector<TNumType> operator*(const TNumType a) const;
    
    void operator=( sphere_vector<TNumType> vec);
    void operator+=( sphere_vector<TNumType> vec);
    void operator-=( sphere_vector<TNumType> vec);
    
    TNumType dist( const sphere_vector<TNumType>& x ) const;
    TNumType& operator[](int index);    //returns reference; returned type can be assigned too.
    
    //sphere_vectors know their local frame
    sphere_vector<TNumType> x_theta();
    sphere_vector<TNumType> x_phi();
    
    //equality
    bool operator==(const sphere_vector<TNumType>& vec) const;
    
    void set( int index, const TNumType &x);
    
    void print();
    
private:
    TNumType x, y, z;
    enum { VEC_LENGTH = 3 };
};

#include "sphere_vector.cpp"
#endif

