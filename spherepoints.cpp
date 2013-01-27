/*
 *  spherepoints.cpp is a class that seeds S^2 with N uniformly
 *  distributed points. Addtionally functionality is provided,
 *  such as flowing the points.
 *
 */

typedef SpherePoints::s_point                 s_point;
typedef SpherePoints::numType                 numType;


//default Constructor

SpherePoints::SpherePoints(int _n) : N(_n)
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
        s_point x = coords(azimuth, elevation);
        points.push_back( x );
    }
}

//default deconstructor
SpherePoints::~SpherePoints(){}

void SpherePoints::print_points()
{
    for( s_point &x : points)
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

s_point SpherePoints::coords( numType phi, numType theta)
{
    return sphere_vector<numType>(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
}

/*
 * Returns the Coulumb Energy acting on a single point.
 *
 *
 */
//s_point SpherePoints::energy(s_point &p, s_point &q)
//{
//    numType theta = p - q;
//    
//    numType norm_diff = 0;
//    for(int i = 0; i < VEC_LENGTH; i++)
//   {
//        
//    }
//
//    for(int i = 0; i < VEC_LENGTH; i++) diff[i] /= norm_diff;
//    
//    return diff;
//}
