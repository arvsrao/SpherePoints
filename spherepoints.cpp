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
       // std::cout<< "[" << x[0] << ", " << x[1] << ", " << x[2] << "],\n";
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
 */
numType SpherePoints::energy( const sphere_vector<numType>& p, const sphere_vector<numType>& q)
{
    return numType(2) / (p.dist(q) * p.dist(q));
}

/*
 * Compute the 3D gradient of the dot product function ( p |--> p * q )
 * so that the result lines in the tangent plane of p \in S^2
 *
 * Once computed, use to further compute the gradient of the distance function at 
 * point p; necessary will be in the direction of q.
 *
 */
sphere_vector<numType>& SpherePoints::grad_dist( sphere_vector<numType>& p, sphere_vector<numType>& q, sphere_vector<numType>& grad)
{
    sphere_vector<numType> x_theta = p.x_theta();
    sphere_vector<numType> x_phi = p.x_phi();
    
    grad =  (x_theta * numType(x_theta * q) + x_phi * numType(q * x_phi)) * (1 / sqrt(1 - (p*q) * (p*q) ) );
    
    return grad;
}

/* counter-clockwise motion in the direction of the tangent.
 *  spherical geodesics are great circles. So, the exponential map is curve along the
 *  great circle which is the intersection of the sphere with the plane determined by
 *  the tangent vector and the point.
 *
 */
sphere_vector<numType> SpherePoints::exp_map( const sphere_vector<numType> & tangent, const sphere_vector<numType>& point, const numType& time_step)
{
    return point * cos(time_step) + tangent * sin(time_step);
}

void SpherePoints::gradient_descent(short int num_iterations)
{
    sphere_vector<numType> dir, p, temp;
    numType delta = 0.01;
    
    while( num_iterations > 0)
    {
        p = points.front();
        points.pop_front();
        dir[0]=0;
        dir[1]=0;
        dir[2]=0;
        
        for(auto &x : points)
        {
            grad_dist(x, p, temp);
            dir -= temp * energy(x,p);
        }
        dir.normalize();
        points.push_back( exp_map(dir,p,delta) );
        num_iterations--;
    }
    
}



