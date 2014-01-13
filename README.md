SpherePoints
============

![Equidistant Points](https://github.com/arvsrao/SpherePoints/blob/master/images/spherepointsMAPLE.jpg?raw=true)


Compute N equidistant points on the 2-dimensional sphere.

**Current State (1/11/2014)**
+ two stage solver: Rejection Sampling, plus gradient descent. 
+ implemented in python
+ developing method based on conjugate gradient descent and/or quasi-newton based approach, for increased speed.

Requires:

+ CMAKE 2.6 or greater
+ Python 2.7.3 or greater
+ C++11 sytax used so make sure you have a compiler that will compile the latest ISO standard of C++. For this project I used GCC 4.7
+ NumPy, MatPlotLib


