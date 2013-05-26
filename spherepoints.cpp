//#define _DEBUG
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
    numType prob1, prob2, azimuth, elevation;
    
    //uniformly seed the sphere with points
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_real_distribution< numType > uniform_distribution(0, 1);
    
    for( int i = 0; i < N ; i++)
    {
		//uniformily generate two values between 0 and 1
        prob1 = uniform_distribution( generator );
        prob2 = uniform_distribution( generator );
		
		//the equally likely azimuth/elevation pair
        azimuth = 2 * M_PI * prob1;	
        elevation = acos(1 - 2*prob2);
		
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
numType SpherePoints::energy( const sphere_vector<numType>& p, const sphere_vector<numType>& q, const numType theta)
{
    return numType(2) / (theta * theta);
}

/*
 * Compute the 3D gradient of the dot product function ( p |--> p * q )
 * so that the result lines in the tangent plane of p \in S^2
 *
 * Once computed, use to further compute the gradient of the distance function at 
 * point p; necessary will be in the direction of q.
 *
 */
sphere_vector<numType>& 
SpherePoints::grad_dist( sphere_vector<numType>& p, sphere_vector<numType>& q, sphere_vector<numType>& grad)
{
    sphere_vector<numType> x_theta = p.x_theta();
    sphere_vector<numType> x_phi = p.x_phi();
    /*
	*  Consider using the Riemannain Gradient for spheres
	*
	*/
    grad =  (x_theta * numType(x_theta * q) + x_phi * numType(q * x_phi)) * (1 / sqrt(1 - (p*q) * (p*q) ) );
    
    return grad;
}

/* counter-clockwise motion in the direction of the tangent.
 *  spherical geodesics are great circles. So, the exponential map is a curve along the
 *  great circle which is the intersection of the sphere with the plane determined by
 *  the tangent vector and the point.
 *
 */
sphere_vector<numType> 
SpherePoints::exp_map( const sphere_vector<numType> & tangent, const sphere_vector<numType>& point, const numType time_step)
{
    return (cos(time_step) * point) + (sin(time_step) * tangent);
}

void SpherePoints::gradient_descent(short int num_iterations)
{
    sphere_vector<numType> dir, p, temp, b;
    numType delta = 0.01;
    numType theta;
       
    std::vector<s_point> stack_next;
    std::vector<s_point> stack_current = points;
    std::vector<s_point> stack_temp = points;
    
    while( num_iterations > 0)
    {
        while( !stack_temp.empty() )
        {
            p = stack_temp.front();
            stack_temp.erase( stack_temp.begin() );
            dir[0]=0;
            dir[1]=0;
            dir[2]=0;
            
            for(auto &x : stack_current)
            {
                if( x != p )
                {
                    temp = grad_dist(x, p, temp);
                    theta = p.dist(x);
                    dir -= temp * ( energy(x,p, theta) - energy(x, p, 2*M_PI - theta) );
                    theta = 0;
                }
                
                temp[0]=0;
                temp[1]=0;
                temp[2]=0;
                theta = 0;
            }
            
            dir.normalize();
            
            #ifdef _DEBUG
                std::cout<< "direction to move in:\n ";
                dir.print();
                sphere_vector<numType> a= exp_map(dir,p,delta);
                std::cout<< "the projection of the tangent vector based at p on to S^2, ";
                a.print();
                std::cout<< " with norm: " << std::sqrt(a.get_x()*a.get_x() + a.get_y()*a.get_y() + a.get_z()*a.get_z()) <<"\n";
            #endif
            
            b = exp_map(dir,p,delta);
            b.normalize();
            stack_next.push_back( b );
        }
        num_iterations--;
        stack_current = stack_next;
        stack_temp = stack_next;
        stack_next.clear();
        
        #ifdef _DEBUG
            std::cout<<"_________________________iteration "<< num_iterations <<" ---------------\n\n";
        #endif
    }
    
    points = stack_current;
}