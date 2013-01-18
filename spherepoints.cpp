/*
 *  spherepoints.cpp is a class that seeds S^2 with N uniformly
 *  distributed points. Addtionally functionality is provided,
 *  such as flowing the points.
 *
 */

    
//default Constructor

SpherePoints::SpherePoints(int N = 10)
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
        points.push_back( x );
    }
}

//default deconstructor
SpherePoints::~SpherePoints(){}

void SpherePoints::print_points()
{
    for( d_point &x : points)
    {
        std::cout<< x[0] << ", " << x[1] << ", " << x[2] << "\n";
    }
}

/*
 * Convert spherical coordinates into euclidean coordinates
 *
 * phi = azimuth angle
 * theta = elevation angle
 *
 */

void SpherePoints::coords( d_point &point, numType phi, numType theta)
{
    d_point apoint = { cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta)};
    point = apoint;
}