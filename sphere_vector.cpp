/*
* Sphere_vectors.cpp
*
* implements common properties and operations expected
* of unit vectors when considered as point on S^2.
*   
* EX.  x - y = 'geodesic distance' between the two points.
*/

template< typename TNumType>
sphere_vector<TNumType>::sphere_vector(numType _x, numType _y, numType _z)
{
    x =_x;
    y =_y;
    z =_z;
}

//default deconstructor
template< typename TNumType>
sphere_vector<TNumType>::~sphere_vector(){}

template< typename TNumType>
TNumType sphere_vector<TNumType>::get_x() const
{
    return x;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::get_y() const
{
    return y;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::get_z() const
{
    return z;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::operator*(const sphere_vector& vec ) const
{
    return this->x * vec.get_x() + this->y * vec.get_y() + this->z * vec.get_z();
}

/*
 * Overloading of [] operator. Gives sphere_vector
 * array indexing functionality:  
 * 
 *  ex:
 *      sphere_vector vec(1,2,3);
 *      vec[0] =1, ..., vec[2] = 3
 *
 */
template< typename TNumType>
TNumType sphere_vector<TNumType>::operator[](const int index) const
{
    switch (index)
    {
        case 0: return this->x;
                break;
        case 1: return this->y;
                break;
        case 2: return this->z;
                break;
        default: std::cout<< "Not at valid index\n";
                break;
    }
}

template< class TNumType>
TNumType sphere_vector<TNumType>::operator-( const sphere_vector& vec) const
{
    return acos( *this * vec );
}

template< class TNumType>
void sphere_vector<TNumType>::print()
{
    std::cout<< " x value: " << x << " y value: " << z << " x value: " << z << "\n";
}