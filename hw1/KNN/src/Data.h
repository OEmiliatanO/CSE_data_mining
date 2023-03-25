#ifndef __DATA_H__
#define __DATA_H__
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <utility>

struct hyperplane_t;

struct point_t
{
    std::vector<double> x;

    point_t() = default;
    point_t(const point_t& other): x{other.x} { std::cerr << "point_t: copy constructor called" << std::endl; }
    point_t(point_t&& other): x{std::move(other.x)} { std::cerr << "point_t: move constructor called" << std::endl; }
    point_t(const std::vector<double>& vx): x{vx} { std::cerr << "point_t: calling vector& constructor." << std::endl; }
    point_t(std::vector<double>&& vx): x{vx} { std::cerr << "point_t: calling vector& constructor." << std::endl; }
    point_t(std::initializer_list<double>& list): x{list} { std::cerr << "point_t: calling initalizer_list& constructor." << std::endl; }
    point_t(std::initializer_list<double>&& list): x{std::forward<decltype(list)>(list)} { std::cerr << "point_t: calling initalizer_list&& constructor." << std::endl; }

    std::size_t size() const { return this->x.size(); }

    // cout
    friend std::ostream& operator<<(std::ostream& os, const point_t& a);

    // index-access
    const double& operator[](std::size_t i) const { return this->x.at(i); }
          double& operator[](std::size_t i)       { return this->x.at(i); }
	
	// assignment
	point_t& operator=(const point_t& other);
	point_t& operator=(point_t&& other);
	
	// hyperplane-related
    bool on(const hyperplane_t& plane);
};

using vector_t = point_t;
struct hyperplane_t
{
    // n^Tx = b
    vector_t n;
    double b;

    hyperplane_t() = default;
    hyperplane_t(double b, vector_t n): n{n}, b{b} {}
    hyperplane_t(std::initializer_list<double>& n, double b): n{n}, b{b} {}
    hyperplane_t(std::initializer_list<double>&& n, double b): n{std::forward<decltype(n)>(n)}, b{b} {}
    
    std::size_t size() const { return this->n.size(); }
    // cout
    friend std::ostream& operator<<(std::ostream& os, const hyperplane_t& a);
};

constexpr double minerr = 1e-8;

// point utility
//
// add
point_t operator+(const point_t& a, const point_t& b);
// dot
double operator*(const point_t& a, const point_t& b);
// scale
point_t operator*(const point_t& a, double scale);
point_t operator*(double scale, const point_t& a);
point_t operator/(const point_t& a, double scale);
// minus
point_t operator-(const point_t& a, const point_t& b);
// cout
std::ostream& operator<<(std::ostream& os, const point_t& a);

// distance
point_t midpoint(const point_t& a, const point_t& b);
double euclidean_dist(const point_t& a, const point_t& b);
double minkowski_dist(const point_t& a, const point_t& b, int p);

// hyperplane utility
bool operator<(const hyperplane_t& plane, const point_t& x);
bool operator>(const hyperplane_t& plane, const point_t& x);
bool operator<(const point_t& x, const hyperplane_t& plane);
bool operator>(const point_t& x, const hyperplane_t& plane);
bool onplane(const point_t& x, const hyperplane_t& plane);
// cout
std::ostream& operator<<(std::ostream& os, const hyperplane_t& a);


struct data_t
{
    point_t point;
    double label;
    data_t() = default;
    data_t(const data_t& other): point{other.point}, label{other.label} { std::cerr << "data_t: calling data_t& constructor." << std::endl; }
    data_t(data_t&& other): point{std::move(other.point)}, label{std::move(other.label)} { std::cerr << "data_t: calling data&& constructor." << std::endl; }
    data_t(const std::vector<double>& x, double y): point{x}, label{y} { std::cerr << "data_t calling vector& constructor." << std::endl; }
    data_t(std::vector<double>&& x, double y): point{std::forward<decltype(x)>(x)}, label{y} { std::cerr << "data_t calling vector& constructor." << std::endl; }
    data_t(std::initializer_list<double>& x, double y): point{x}, label{y} { std::cerr << "data_t calling initalizer_list& constructor." << std::endl; }
    data_t(std::initializer_list<double>&& x, double y): point{std::forward<decltype(x)>(x)}, label{y} { std::cerr << "data_t calling initalizer_list&& constructor." << std::endl; }
    
    // cout
    friend std::ostream& operator<<(std::ostream& os, const data_t& a);
	
	// size
	std::size_t size() const { return this->point.size(); }

	// assignment
	data_t& operator=(const data_t& other);
	data_t& operator=(data_t&& other);
};

struct dataset_t
{
    std::vector<data_t> data;
    dataset_t() = default;
    dataset_t(const dataset_t& other): data{other.data} {}
    dataset_t(dataset_t&& other): data{std::move(other.data)} {}
    
    // index-access
    const data_t& operator[](std::size_t i) const { return this->data.at(i); }
          data_t& operator[](std::size_t i)       { return this->data.at(i); }

    // allocate
    void emplace_back(const data_t& _data) { this->data.emplace_back(_data); }
    void emplace_back(data_t&& _data) { this->data.emplace_back(std::forward<decltype(_data)>(_data)); }
    void emplace_back(const std::vector<double>& x, double y) { this->data.emplace_back(x, y); }
    void emplace_back(std::vector<double>&& x, double y) { this->data.emplace_back(std::forward<decltype(x)>(x), y); }
    void emplace_back(std::initializer_list<double>& x, double y) { this->data.emplace_back(x, y); }
    void emplace_back(std::initializer_list<double>&& x, double y) { this->data.emplace_back(x, y); }

    // release
    void clear() { this->data.clear(); }

	// size
	std::size_t size() const { return this->data.size(); }

    // cout
    friend std::ostream& operator<<(std::ostream& os, const dataset_t& a);

	// assignment
	dataset_t& operator=(const dataset_t& other);
	dataset_t& operator=(dataset_t&& other);
};

#endif
