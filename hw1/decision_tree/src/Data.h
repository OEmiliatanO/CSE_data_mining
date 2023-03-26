#ifndef __DATA_H__
#define __DATA_H__
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <limits>
#include <utility>

struct hyperplane_t;

struct point_t
{
    std::vector<double> x;

    point_t() = default;
    point_t(const point_t& other): x{other.x} { }
    point_t(point_t&& other): x{std::move(other.x)} { }
    point_t(const std::vector<double>& vx): x{vx} { }
    point_t(std::vector<double>&& vx): x{vx} { }
    point_t(std::initializer_list<double>& list): x{list} { }
    point_t(std::initializer_list<double>&& list): x{list} { }

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

constexpr double minerr = std::numeric_limits<double>::epsilon();

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
    int label;

    data_t() = default;
    
    data_t(const data_t& other): point{other.point}, label{other.label} { }
    data_t(data_t&& other): point{std::move(other.point)}, label{std::move(other.label)} { }

    data_t(const std::vector<double>& x, int y): point{x}, label{y} { }
    data_t(std::vector<double>&& x, int y): point{std::forward<decltype(x)>(x)}, label{y} { }
    
    data_t(const point_t& x, int y): point{x}, label{y} {}
    data_t(point_t&& x, int y): point{std::forward<decltype(x)>(x)}, label{y} {}
    
    data_t(std::initializer_list<double>& x, int y): point{x}, label{y} { }
    data_t(std::initializer_list<double>&& x, int y): point{std::forward<decltype(x)>(x)}, label{y} { }
    
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

    // exprimental
    std::vector<data_t> operator[](const std::vector<bool>& mask) const 
    {
        std::vector<data_t> ret;
        for (std::size_t i = 0; i < this->data.size(); ++i)
            if (mask.at(i)) ret.emplace_back(this->data.at(i));
        return ret;
    }

    // allocate
    void emplace_back(const data_t& _data) { this->data.emplace_back(_data); }
    void emplace_back(data_t&& _data) { this->data.emplace_back(std::forward<decltype(_data)>(_data)); }

    void emplace_back(const std::vector<double>& x, int y) { this->data.emplace_back(x, y); }
    void emplace_back(std::vector<double>&& x, int y) { this->data.emplace_back(std::forward<decltype(x)>(x), y); }
    
    void emplace_back(std::initializer_list<double>& x, int y) { this->data.emplace_back(x, y); }
    void emplace_back(std::initializer_list<double>&& x, int y) { this->data.emplace_back(std::forward<decltype(x)>(x), y); }

    // release
    void clear() { this->data.clear(); }

	// size
	std::size_t size() const { return this->data.size(); }
    std::size_t column() const
    { 
        if (this->data.size()) return this->data.front().size(); 
        else return 0; 
    }

    // cout
    friend std::ostream& operator<<(std::ostream& os, const dataset_t& a);

	// assignment
	dataset_t& operator=(const dataset_t& other);
	dataset_t& operator=(dataset_t&& other);

    // utility
    std::vector<double> extract(std::size_t column);
    std::vector<data_t> extract_with_label(std::size_t column);
};

#endif
