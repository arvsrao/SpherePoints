from numpy import array, dot
from numpy.random import uniform    
from numpy.linalg import norm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from math import cos, sin, atan2 , acos, pi 


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

def ColumbEnergy(p,q, exponent=2):
    """
    return the columb energy between two points on the sphere
    ==========
    p & q are numpy arrays of length 3
    """
    dist = acos( dot(p,q) ); # geodesic distance between points
    return pow(dist, -exponent);


def GradientAtP(p,x):
    """
    Compute the gradient of columb energy at point p \in S^2
    Both p & x are numpy arrays
    """
    #basis of the tangent plane to p on S^2
    theta, phi = ConvertToSphericalCoords(x);
    x_theta = array( [ cos(theta) * cos(phi), sin(phi) * cos(theta), -sin(theta) ] )
    x_phi = array( [ -sin(theta) * sin(phi), cos(phi) * sin(theta), 0] )
    return 2 * pow( ColumbEnergy(p,x), 1.5) * ( dot(p,x_theta) * x_theta + dot(p,x_phi) * x_phi) / sin(dot(p,x))
    
    
def ExponentialMap(p,v):
    """
    exponential map on the sphere 
    
    S^2 \in (p,v) |-->  cos(||v||) * p + sin(||v||) v/||v||
    
    ||v|| must be less than pi/2 (cut locus)
    """
    a = norm(v)
    return cos(a) * p + sin(a) * v/a;
    

def Flow(points):
    """
    gradient flow of points
    """

def NextStep(p,x, delta=DELTA):
    """
    compute the flow of x ( which we think of as x_n)
    return x_{n+1}
    """
    return ExponentialMap(x, -delta * GradientAtP(p,x) );
    
    
def DisplayNPoints(N=100):
    """
    display N (default 100) points on the sphere using 3D
    matplotlib scatter plot
    """
    
    #generate list of points sampled from Uniform(S^2)
    coords = [ GenerateRandomS2Point() for x in range(N) ];
    points = array([ ConvertToEuclidean(theta, phi) for theta, phi in coords ]);
    
    fig = plt.figure()
    ax1 = fig.add_subplot(111, projection='3d')
    ax1.scatter( points[:,0], points[:,1], points[:,2], c='r')
    ax1.set_xlabel('X Label')
    ax1.set_ylabel('Y Label')
    ax1.set_zlabel('Z Label')
    plt.show();
    