//
//  main.cpp
//  Sphere Points
//
//  Created by Arvind Rao on 12/30/12.

#include <iostream>
#include "spherepoints.h"
#include "sphere_vector.h"
#include <vector>
#include <list>

int main(int argc, char ** argv)
{
    int n;
    
    if( argc < 2)
    {
        std::cerr<< "Must include a number!!\n";
        return 0;
    }
    
    n = std::atoi( argv[1] );
    SpherePoints x(n);
    x.print_points();
    x.gradient_descent(10);
    std::cout<< "The points after 10 iterations of gradient descent.\n\n";
    x.print_points();
    
    /**************/
    
//    std::vector<int> blah = {1,2,3,4,5,6,7,8,9,10};
//    std::list<int> mylist;
//    
//    for(auto & x : blah)
//    {
//        mylist.push_back(x);
//    }
//    
//    int myint = 11;
//    int a = mylist.front();
//    mylist.pop_front();
//    mylist.push_back(myint); 
//    
//    std::cerr<< "adding " << myint << " to the back and popping "<< a << "  from the front.\n";
//    for(auto &x : mylist)
//    {
//        std::cout<< x <<"\n";
//    }
    return 0;
}