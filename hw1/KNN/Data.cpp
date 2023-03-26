#include "src/Data.h"

bool onplane(const point_t& x, const hyperplane_t& plane)
{
    return abs(plane.b - plane.n*x) <= minerr;
}
bool point_t::on(const hyperplane_t& plane)
{
    return onplane(*this, plane);
}

// add
point_t operator+(const point_t& a, const point_t& b)
{
    if (a.size() != b.size()) { std::cerr << "a+b: a.size() != b.size(), return none point." << std::endl; return point_t{}; }
    std::vector<double> mx{a.x};
    for (size_t i = 0; i <= mx.size(); ++i) { mx[i] += b[i]; }
    point_t m{mx};
    return m;
}
// dot
double operator*(const point_t &a, const point_t &b)
{
    if (a.size() != b.size()) { std::cerr << "a*b: a.size() != b.size(), return 0." << std::endl; return 0.0; }
    double ret;
    for (size_t i = 0; i < a.size(); ++i) 
        ret += a[i] * b[i];
    return ret;
}
// scale
point_t operator*(const point_t &a, double scale)
{
    std::vector<double> v{a.x};
    for (auto& x : v) x *= scale;
    point_t ret{v};
    return ret;
}
point_t operator*(double scale, const point_t &a)
{
    return a*scale;
}
point_t operator/(const point_t &a, double scale)
{
    // precision ?
    // return a*(1/scale);

    std::vector<double> v{a.x};
    for (auto& x : v) x /= scale;
    point_t ret{v};
    return ret;
}
// minus
point_t operator-(const point_t& a, const point_t& b)
{
    if (a.size() != b.size()) { std::cerr << "a-b: a.size() != b.size(), return none point." << std::endl; return point_t{}; }
    // O(2n)
    // return a+(-1*b);

    // O(n)
    std::vector<double> mx{a.x};
    for (size_t i = 0; i <= mx.size(); ++i) { mx[i] -= b[i]; }
    point_t m{mx};
    return m;
}

// cout
std::ostream& operator<<(std::ostream& os, const point_t& a)
{
    for (auto& x : a.x) os << x << ' ';
    return os;
}

// assignment has been implemented as implict constructor

point_t midpoint(const point_t& a, const point_t& b)
{
    if (a.size() != b.size()) { std::cerr << "mid_point(a,b): a.size() != b.size(), return none point." << std::endl; return point_t{}; }
    return a/2+b/2;
}

double minkowski_dist(const point_t& a, const point_t& b, int p)
{
    if (a.size() != b.size()) { std::cerr << "minkowski_dist(a,b): a.size() != b.size(), return 0." << std::endl; return 0; }
    double ret = 0;
    for (std::size_t i = 0; i < a.size(); ++i) ret += pow(a[i]-b[i], p);
    return pow(ret, 1.0/p);
}
double euclidean_dist(const point_t& a, const point_t& b)
{
    // naive
    //const point_t c = a-b;
    //return sqrt(c*c);

    // minkowski
    return minkowski_dist(a, b, 2);
}

bool operator<(const hyperplane_t& plane, const point_t& x)
{
    return plane.b < plane.n*x;
}
bool operator<(const point_t& x, const hyperplane_t& plane)
{
    return plane.n*x < plane.b;
}
bool operator>(const hyperplane_t& plane, const point_t& x)
{
    return plane.b > plane.n*x;
}
bool operator>(const point_t& x, const hyperplane_t& plane)
{
    return plane.n*x > plane.b;
}
std::ostream& operator<<(std::ostream& os, const hyperplane_t& plane)
{
    os << "[ ";
    for (auto& x : plane.n.x) os << x << ' ';
    os << "]^Tx = " << plane.b;
    return os;
}

std::ostream& operator<<(std::ostream& os, const data_t& data)
{
    os << "[ " << data.point << "]" << ", [" << data.label << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const dataset_t& dataset)
{
    for (auto& data : dataset.data) os << data << std::endl;
    return os;
}


point_t& point_t::operator=(const point_t& other)
{
	this->x = other.x;
	return *this;
}
point_t& point_t::operator=(point_t&& other)
{
	this->x = std::move(other.x);
	return *this;
}

data_t& data_t::operator=(const data_t& other)
{
	this->point = other.point;
    this->label = other.label;
	return *this;
}
data_t& data_t::operator=(data_t&& other)
{
	this->point = std::move(other.point);
    this->label = other.label;
	return *this;
}

dataset_t& dataset_t::operator=(const dataset_t& other)
{
	this->data = other.data;
	return *this;
}
dataset_t& dataset_t::operator=(dataset_t&& other)
{
	this->data = std::move(other.data);
	return *this;
}

std::vector<double> dataset_t::extract(std::size_t column)
{
    if (column >= this->size())
    {
        std::cerr << "dataset_t::extract: column >= size\n";
        return std::vector<double>{};
    }
    std::vector<double> ret;
    for (const auto& data_: this->data)
        ret.emplace_back(data_.point[column]);
    return ret;
}

std::vector<data_t> dataset_t::extract_with_label(std::size_t column)
{
    std::vector<data_t> ret;
    for (const auto& data_: this->data)
        ret.emplace_back(std::initializer_list<double>{data_.point[column]}, data_.label);
    return ret;
}

// unit test
#ifdef DATATEST
int main()
{
    point_t p1{1,2};
    point_t p2{4,5};
    point_t p3{0,0};
    /*
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
    */
    hyperplane_t plane{{2, 3}, 3};
    std::cout << std::boolalpha;
    /*
    std::cout << "plane = " << plane << std::endl;
    std::cout << "p1 < plane is " << (p1 < plane) << std::endl;
    std::cout << "p1 > plane is " << (p1 > plane) << std::endl;
    std::cout << "p2 < plane is " << (p2 < plane) << std::endl;
    std::cout << "p2 > plane is " << (p2 > plane) << std::endl;
    std::cout << "p3 < plane is " << (p3 < plane) << std::endl;
    std::cout << "p3 > plane is " << (p3 > plane) << std::endl;
    */

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
