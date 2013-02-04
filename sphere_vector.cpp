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
    return this->x;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::get_y() const
{
    return this->y;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::get_z() const
{
    return this->z;
}

template< typename TNumType>
void sphere_vector<TNumType>::set( int index, const TNumType &x)
{
    this->operator[](index) = x;
}

template< typename TNumType>
TNumType sphere_vector<TNumType>::operator*(const sphere_vector<TNumType>& vec ) const
{
    return this->x * vec.get_x() + this->y * vec.get_y() + this->z * vec.get_z();
}

template< typename TNumType>
sphere_vector<TNumType> sphere_vector<TNumType>::operator+( const sphere_vector<TNumType>& vec ) const
{
    return sphere_vector<TNumType>(this->x + vec.get_x(), this->y + vec.get_y(), this->z + vec.get_z());
}

template< typename TNumType>
sphere_vector<TNumType> sphere_vector<TNumType>::operator-(const sphere_vector<TNumType>& vec ) const
{
    return sphere_vector<TNumType>(this->x - vec.get_x(), this->y - vec.get_y(), this->z - vec.get_z());
}


/*
 * EQUALS operator
 *
 */
template< typename TNumType>
void sphere_vector<TNumType>::operator=( sphere_vector<TNumType> vec )
{

    for(int i = 0; i < VEC_LENGTH; i++)
    {
        this->operator[](i) = vec[i];
    }
}

/*
 *  "+=" operator
 *
 */
template< typename TNumType>
void sphere_vector<TNumType>::operator+=( sphere_vector<TNumType> vec )
{
    
    for(int i = 0; i < VEC_LENGTH; i++)
    {
        this->operator[](i) = this->operator[](i) + vec[i];
    }
}

/*
 *  "-=" operator
 *
 */
template< typename TNumType>
void sphere_vector<TNumType>::operator-=( sphere_vector<TNumType> vec )
{
    
    for(int i = 0; i < VEC_LENGTH; i++)
    {
        this->operator[](i) = this->operator[](i) - vec[i];
    }
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
TNumType& sphere_vector<TNumType>::operator[]( int index)
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

template< typename TNumType>
TNumType sphere_vector<TNumType>::dist( const sphere_vector<TNumType>& x ) const
{
    return acos( *this * x );
}

template<typename TNumType>
sphere_vector<TNumType> sphere_vector<TNumType>::x_theta()
{
    numType theta, phi;
    phi = atan2(this->y , this->x);
    theta = acos(this->z);
    
    return sphere_vector<TNumType>(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta));
}

template<typename TNumType>
sphere_vector<TNumType> sphere_vector<TNumType>::x_phi()
{
    numType theta, phi;
    phi = atan2(this->y , this->x);
    theta = acos(this->z);
    
    return sphere_vector<TNumType>( -sin(theta) * sin(phi), sin(theta) * cos(phi), 0);
}

/**
 *  Multiplication by a scalar
 *
 */
template<typename TNumType>
sphere_vector<TNumType> sphere_vector<TNumType>::operator*(const TNumType a) const
{
    return sphere_vector<TNumType>(a * this->x, a * this->y, a * this->z);
}

template< typename TNumType>
bool sphere_vector<TNumType>::operator==(const sphere_vector<TNumType>& vec) const
{
    return (this->x == vec.get_x()) && (this->y == vec.get_y()) && (this->z == vec.get_z());
}

template< typename TNumType >
void sphere_vector<TNumType>::normalize()
{
    TNumType norm = sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
    for(int i = 0; i < VEC_LENGTH; i++)
    {
        this->operator[](i) = this->operator[](i) / norm;
    }
}

template< class TNumType>
void sphere_vector<TNumType>::print()
{
    std::cout<< " x value: " << x << ", y value: " << y << ", x value: " << z << "\n";
}
