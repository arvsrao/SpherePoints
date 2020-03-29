from numpy import array, dot, zeros
from numpy.random import uniform    
from numpy.linalg import norm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from math import cos, sin, atan2, acos, pi, sqrt 
from itertools import product, permutations
from functools import partial


DELTA = 0.001

def GenerateRandomS2Point():
    """
    draw sample from the uniform distribution on S^2
    *see spherepoints_notes.pdf for a derivation of the
    algorithm.
    """
    x = uniform(0,1)
    y = uniform(0,1)
    theta = acos(1-2*x);
    phi = 2 * pi * y
    
    return (theta, phi);

    
def ConvertToEuclidean(theta, phi):
    """
    Convert spherical coordinates to euclidean coordinates
    """
    return array( (cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta)) );

    
def ConvertToSphericalCoords(point, norm=False):
    """
    Convert euclidean coordinates to spherical coordinates
    
    point is numpy array
    norm: True if the input point isn't normalized. (default is False)
    """    
    x = point[0]; y = point[1]; z = point[2];
    return (acos(z), atan2(y,x));


def Energy(dist, exponent=2):
    """
    return the columb energy between two points on the sphere
    ==========
    p & q are numpy arrays of length 3
    """
    return pow(dist, -exponent)


def GradientAtP(p,x):
    """
    Compute the gradient of columb energy (based at x) at p \in S^2
    Both p & x are numpy arrays
    """
    #basis of the tangent plane to p on S^2
    theta, phi = ConvertToSphericalCoords(p)
    p_theta = array( [ cos(theta) * cos(phi), sin(phi) * cos(theta), -sin(theta) ] )
    p_phi = array( [ -sin(theta) * sin(phi), cos(phi) * sin(theta), 0] )
    dist = acos( dot(p,x) ); # geodesic distance between points
    _coef = Energy(dist) / sqrt(1-pow(dot(p,x),2))
    return _coef * (dot(x,p_theta)*p_theta + dot(x,p_phi)*p_phi) 

    
def ExponentialMap(p,v):
    """
    exponential map on the sphere 
    
    S^2 \in (p,v) |-->  cos(||v||) * p + sin(||v||) v/||v||
    
    ||v|| must be less than pi/2 (cut locus)
    """
    a = norm(v)
    return cos(a) * p + (sin(a)/a) * v
    

def displayTotalEnergy(points,j):
    B = permutations(points, 2)
    _energy = sum([ Energy(acos(dot(x,y)), 1) for x,y in B ])
    print "total energy for iteration %d is %f" % (j, _energy)
    return (j,_energy)


def distance(p,q):
    return acos( dot(p,q) )


def Flow(points, M=10):
    """
    gradient flow of points
    M = # of iterations of the flow
    """
    N = len(points)
    j=0
    def gen_grad(p):
        """
        closure of GradientAtP
        """
        def grad(x):
            return GradientAtP(p,x);
        return grad
    
    #update positions of each points
    def NextStep(p, points, delta=DELTA):
        """
        compute the flow of x ( which we think of as x_n)
        return x_{n+1}

        p is the reference point
        """
        _grad = gen_grad(p)
        v = sum([ _grad(x) if distance(p,x) < pi/2 else 0 for x in points ])
        return ExponentialMap(p, -delta * v)  
    
    while j < M:
        new_points = [] #temp array holding the n+1 iteration of points, {p}
        # using a queue data structure, removing from the end/back and adding to the head/front
        for i in range(N):
            p = points.pop() #remove from the end of the list
            q = NextStep(p, points);
            new_points.append(q);
            points.insert(0,p)
        #total energy of the system
        i, _energy = displayTotalEnergy(points,j)
        print "length of points list is %d " % len(points)
        points = new_points; j+=1
    return array(points)

    
def RejectionSample(N):
    """
    Rejection sample the sphere to get a well distributed 
    set of N points.
    """
    
    _delta = 2 / sqrt(N)
    plist = []; j = 0
    def SampleFromS2():
        a,b = GenerateRandomS2Point()
        return ConvertToEuclidean(a,b)
                    
    plist.append( SampleFromS2() )
    while j < N-1:
        q = SampleFromS2()
        _dist = partial(distance, q)
        if not any([ _dist(x) < _delta for x in plist ]):
            plist.append(q)
            j += 1
    return plist;
    
    
def DisplayNPoints(N=100, M=10):
    """
    display N (default 100) points on the sphere using 3D
    matplotlib scatter plot
    """
    
    DELTA = min(0.2/sqrt(N), 0.001)
    
    #generate list of points sampled from Uniform(S^2)
    #coords = [ GenerateRandomS2Point() for x in range(N) ];
    coords = RejectionSample(N)
    points = Flow( coords, M )
    
    fig = plt.figure()
    ax1 = fig.add_subplot(111, projection='3d')
    ax1.scatter( points[:,0], points[:,1], points[:,2], c='r')
    ax1.set_xlabel('X Label')
    ax1.set_ylabel('Y Label')
    ax1.set_zlabel('Z Label')
    plt.show();