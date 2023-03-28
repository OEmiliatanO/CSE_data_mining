#include "../include/Data.h"

// unit test
#ifdef DATATEST
int main()
{
    point_t p1{1,2};
    point_t p2{4,5};
    point_t p3{0,0};
    
    std::cout << "p1 = ( " << p1 << ")" << std::endl;
    std::cout << "p2 = ( " << p2 << ")" << std::endl;
    
    std::cout << "euclidean distance of p1, p2: " << euclidean_dist(p1, p2) << std::endl;
    std::cout << "minkowski distance of p1, p2 (p=2): " << minkowski_dist(p1, p2, 2) << std::endl;
    std::cout << "p1 + p2 = " << p1+p2 << std::endl;
    std::cout << "p1 - p2 = " << p1-p2 << std::endl;
    std::cout << "p1 * p2 = " << p1*p2 << std::endl;
    std::cout << "p1 / 2 =  " << p1/2  << std::endl;
    std::cout << "p1 * 2 =  " << p1*2  << std::endl;
    std::cout << "mid point of p1, p2 = ( " << midpoint(p1, p2) << ")" << std::endl;
    
    hyperplane_t plane{{2, 3}, 3};
    std::cout << std::boolalpha;
    
    std::cout << "plane = " << plane << std::endl;
    std::cout << "p1 < plane is " << (p1 < plane) << std::endl;
    std::cout << "p1 > plane is " << (p1 > plane) << std::endl;
    std::cout << "p2 < plane is " << (p2 < plane) << std::endl;
    std::cout << "p2 > plane is " << (p2 > plane) << std::endl;
    std::cout << "p3 < plane is " << (p3 < plane) << std::endl;
    std::cout << "p3 > plane is " << (p3 > plane) << std::endl;
    

    point_t p4 = p1;
    point_t p5 = std::move(p2);
    point_t p6{point_t{2,3}};
    std::cout << "p1 = ( " << p1 << ")" << std::endl;
    std::cout << "p2 = ( " << p2 << ")" << std::endl;
    std::cout << "p4 = ( " << p4 << ")" << std::endl;
    std::cout << "p5 = ( " << p6 << ")" << std::endl;
    return 0;
}
#endif
