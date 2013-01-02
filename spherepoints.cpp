/*
 *  spherepoints.cpp is a class that seeds S^2 with N uniformly
 *  distributed points. Addtionally functionality is provided,
 *  such as flowing the points.
 *
 */

    
//default Constructor
template< int N >
SpherePoints< N >::SpherePoints()
{
    numType azimuth, elevation, prob;
    
    //uniformly seed the sphere with points
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_real_distribution< numType > distribution_azimuth(0, 2 * M_PI);
    std::uniform_real_distribution< numType > distribution_elevation( 0, 1);
    
    for( int i = 0; i < N ; i++)
    {
        azimuth = distribution_azimuth( generator );
        prob = distribution_elevation( generator );
        
        elevation = acos(1 - 2*prob);
        d_point x;
        coords(x, azimuth, elevation);
        points[i] = x;
    }
}

//default deconstructor
template< int N >
SpherePoints<N>::~SpherePoints(){}

template< int N >
void SpherePoints<N>::print_points()
{
    for( int i=0; i < N; i++)
    {
        std::cout<< points[i][0] << ", " << points[i][1] << ", " << points[i][2] << "\n";
    }
}

/*
 * Convert spherical coordinates into euclidean coordinates
 *
 * phi = azimuth angle
 * theta = elevation angle
 *
 */

template< int N >
void SpherePoints< N >::coords( d_point &point, numType phi, numType theta)
{
    d_point apoint = { cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta)};
    point = apoint;
}