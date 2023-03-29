#ifndef __DATA_H__
#define __DATA_H__
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <functional>
#include <limits>
#include <utility>
#include <ranges>

constexpr double minerr = std::numeric_limits<double>::epsilon();

template<typename T>
class point_t;

template<typename T>
class hyperplane_t;

template<typename T, typename U>
class dataset_t;

// add
template<typename T> point_t<T>  operator+(const point_t<T>& a, const point_t<T>& b);
// dot
template<typename T> T operator*(const point_t<T>& a, const point_t<T>& b);
// scale
template<typename T> point_t<T> operator*(const point_t<T>& a, T scale);
template<typename T> point_t<T> operator*(T scale, const point_t<T>& a);
template<typename T> point_t<T> operator/(const point_t<T>& a, T scale);
// minus
template<typename T> point_t<T> operator-(const point_t<T>& a, const point_t<T>& b);
// point_t cout
template<typename T> std::ostream& operator<<(std::ostream& os, const point_t<T>& a);

// distance
template<typename T> point_t<T> midpoint(const point_t<T>& a, const point_t<T>& b);
template<typename T> double euclidean_dist(const point_t<T>& a, const point_t<T>& b);
template<typename T> double minkowski_dist(const point_t<T>& a, const point_t<T>& b, int p);

// hyperplane utility
template<typename T> bool operator<(const hyperplane_t<T>& plane, const point_t<T>& x);
template<typename T> bool operator>(const hyperplane_t<T>& plane, const point_t<T>& x);
template<typename T> bool operator<(const point_t<T>& x, const hyperplane_t<T>& plane);
template<typename T> bool operator>(const point_t<T>& x, const hyperplane_t<T>& plane);
template<typename T> bool onplane(const point_t<T>& x, const hyperplane_t<T>& plane);
// hyperplane_t cout
template<typename T> std::ostream& operator<<(std::ostream& os, const hyperplane_t<T>& a);

template<typename T, typename U> std::ostream& operator<<(std::ostream& os, const dataset_t<T, U>& a);

template<typename T>
class point_t
{
public:
    std::vector<T> x;

    point_t() = default;
    
	point_t(const point_t<T>& other): x{other.x} { }
    point_t(point_t<T>&& other): x{std::move(other.x)} { }
    
	point_t(const std::vector<T>& vx): x{vx} { }
    point_t(std::vector<T>&& vx): x{vx} { }
    
	point_t(std::initializer_list<T>& list): x{list} { }
    point_t(std::initializer_list<T>&& list): x{list} { }

	point_t(std::size_t n, std::function<T(void)> rd) { x.resize(n); for (auto& it : x) it = rd(); }

	// size
    std::size_t size() const noexcept { return this->x.size(); }
    void resize(std::size_t n) { this->x.resize(n); }

    // clear
    void clear() { this->x.clear(); }

    // cout
    friend std::ostream& operator<< <>(std::ostream& os, const point_t<T>& a);

    // extend && emplace_back
    void extend(const point_t<T>& other) { this->x.insert(this->x.end(), other.x.begin(), other.x.end()); }
    void extend(point_t<T>&& other) { this->x.insert(this->x.end(), other.x.begin(), other.x.end()); }
	void extend(const std::vector<T>& vx) { this->x.insert(this->x.end(), vx.begin(), vx.end()); }
    void extend(std::vector<T>&& vx) { this->x.insert(this->x.end(), vx.begin(), vx.end()); }
    void emplace_back(const T& x) { this->x.emplace_back(x); }
    void emplace_back(T&& x) { this->x.emplace_back(std::forward<decltype(x)>(x)); }

    /**** index-access ****/
    const T& operator[](std::size_t i) const { return this->x.at(i); }
          T& operator[](std::size_t i)       { return this->x.at(i); }
    const T& at(std::size_t i) const { return this->x.at(i); }
          T& at(std::size_t i)       { return this->x.at(i); }
    /**** index-access ****/
	
	/**** iterator-related ****/
	auto begin() noexcept -> decltype(x.begin()) { return x.begin(); }
	auto end()   noexcept -> decltype(x.end())   { return x.end(); }
	auto begin() const noexcept -> decltype(x.begin()) { return x.begin(); }
	auto end()   const noexcept -> decltype(x.end())   { return x.end(); }
	/**** iterator-related ****/
	
	/**** assignment ****/
	point_t<T>& operator=(const point_t<T>& other);
	point_t<T>& operator=(point_t<T>&& other);
	/**** assignment ****/

    /**** operator ****/
    point_t<T>& operator+=(const point_t<T>& b);
    friend point_t<T>  operator+ <> (const point_t<T>& a, const point_t<T>& b);
    // dot
    friend T operator* <> (const point_t<T>& a, const point_t<T>& b);
    // scale
    friend point_t<T> operator* <> (const point_t<T>& a, T scale);
    friend point_t<T> operator* <> (T scale, const point_t<T>& a);
    friend point_t<T> operator/ <> (const point_t<T>& a, T scale);
    point_t<T>& operator*=(T scale);
    // minus
    friend point_t<T> operator- <> (const point_t<T>& a, const point_t<T>& b);
    /**** operator ****/

	// hyperplane-related
    bool on(const hyperplane_t<T>& plane);
    friend bool operator< <>(const hyperplane_t<T>& plane, const point_t<T>& x);
    friend bool operator< <>(const point_t<T>& x, const hyperplane_t<T>& plane);
    friend bool operator> <>(const hyperplane_t<T>& plane, const point_t<T>& x);
    friend bool operator> <>(const point_t<T>& x, const hyperplane_t<T>& plane);
};

template<typename T>
using vector_t = point_t<T>;

template<typename T>
class hyperplane_t
{
public:
    // n^Tx = b
    vector_t<T> n;
    T b;

    hyperplane_t() = default;
    hyperplane_t(vector_t<T> n, T b): n{n}, b{b} {}
    hyperplane_t(std::initializer_list<T>& n, T b): n{n}, b{b} {}
    hyperplane_t(std::initializer_list<T>&& n, T b): n{std::forward<decltype(n)>(n)}, b{b} {}
    
    std::size_t size() const { return this->n.size(); }
    // cout
    friend std::ostream& operator<< <>(std::ostream& os, const hyperplane_t<T>& a);

    friend bool operator< <>(const hyperplane_t<T>& plane, const point_t<T>& x);
    friend bool operator< <>(const point_t<T>& x, const hyperplane_t<T>& plane);
    friend bool operator> <>(const hyperplane_t<T>& plane, const point_t<T>& x);
    friend bool operator> <>(const point_t<T>& x, const hyperplane_t<T>& plane);
};

template<typename T, typename U>
class dataset_t
{
public:
    std::vector<point_t<T>> data;
    point_t<U> label;

    dataset_t() = default;
    dataset_t(const dataset_t<T, U>& other): data{other.data}, label{other.label} {}
    dataset_t(dataset_t<T, U>&& other): data{std::move(other.data)}, label{std::move(other.label)} {}

    dataset_t(const std::vector<point_t<T>>& other_data, const point_t<U>& other_label): data{other_data}, label{other_label} {}
    dataset_t(std::vector<point_t<T>>&& other_data, point_t<U>&& other_label): data{std::move(other_data)}, label{std::move(other_label)} {}
    
    // index-access
    const point_t<T>& operator[](std::size_t i) const { return this->data.at(i); }
          point_t<T>& operator[](std::size_t i)       { return this->data.at(i); }

	// iterator-related
	auto begin() noexcept -> decltype(data.begin()) { return data.begin(); }
	auto end()   noexcept -> decltype(data.end())   { return data.end(); }
	auto begin() const noexcept -> decltype(data.begin()) { return data.begin(); }
	auto end()   const noexcept -> decltype(data.end())   { return data.end(); }

    // allocate
    void emplace_back(const point_t<T>& _data, const U& _label) { this->data.emplace_back(_data); this->label.emplace_back(_label); }
    void emplace_back(point_t<T>&& _data, U&& _label) { this->data.emplace_back(std::forward<decltype(_data)>(_data)); this->label.emplace_back(std::forward<decltype(_label)>(_label)); }

    void emplace_back(const std::vector<T>& x, const U& y) { this->data.emplace_back(x, y); }
    void emplace_back(std::vector<T>&& x, U&& y) { this->data.emplace_back(std::forward<decltype(x)>(x), std::forward<decltype(y)>(y)); }
    
    void emplace_back(std::initializer_list<T>& x, const U& y) { this->data.emplace_back(x, y); }
    void emplace_back(std::initializer_list<T>&& x, U&& y) { this->data.emplace_back(std::forward<decltype(x)>(x), std::forward<decltype(y)>(y)); }

    // release
    void clear() { this->data.clear(); label.clear(); }

	// size
	std::size_t size() const 
    {
        if (this->data.size() != this->label.size())
        {
            std::cerr << "dataset_t::size(): data.size() != label.size()";
            exit(1);
        }
        return this->data.size();
    }
    std::size_t column() const
    { 
        if (this->data.size()) return this->data.front().size(); 
        else return 0; 
    }

    // cout
    friend std::ostream& operator<< <> (std::ostream& os, const dataset_t<T, U>& a);

	/**** operator ****/
	dataset_t& operator=(const dataset_t<T, U>& other);
	dataset_t& operator=(dataset_t<T, U>&& other);
    dataset_t& operator+=(const dataset_t<T, U>& other);
    dataset_t& operator+=(dataset_t<T, U>&& other);
	/**** operator ****/

    // utility
    point_t<T> extract(std::size_t column);
    auto extract_with_label(std::size_t column) -> decltype(auto);
	double delta(const dataset_t<T, U>& other, const std::function<double(const U&, const U&)>& loss);
};


/***** point_t ******/
/**** assignment ****/
template<typename T>
point_t<T>& point_t<T>::operator=(const point_t<T>& other)
{
    this->x = other.x;
    return *this;
}

template<typename T>
point_t<T>& point_t<T>::operator=(point_t<T>&& other)
{
    this->x = std::move(other.x);
    return *this;
}
/**** assignment ****/

/**** operator ****/
template<typename T>
point_t<T>& point_t<T>::operator+=(const point_t<T>& other)
{
    if (this->size() != other.size()) { std::cerr << "a+=b: a.size() != b.size(), return originally left point." << std::endl; return *this; }
    for (size_t i = 0; i <= this->size(); ++i) { (*this)[i] += other[i]; }
    return *this;
}
template<typename T>
point_t<T> operator+(const point_t<T>& a, const point_t<T>& b)
{
    if (a.size() != b.size()) { std::cerr << "a+b: a.size() != b.size(), exit..." << std::endl; exit(1); }
    point_t<T> ret{a};
    for (size_t i = 0; i < ret.size(); ++i) { ret[i] += b[i]; }
    return ret;
}
// dot
template<typename T>
T operator*(const point_t<T>& a, const point_t<T>& b)
{
    if (a.size() != b.size()) { std::cerr << "a*b: a.size() != b.size(), exit..." << std::endl; exit(1); }
    T ret = 0;
    for (size_t i = 0; i < a.size(); ++i) ret += a[i] * b[i];
    return ret;
}
// scale
template<typename T>
point_t<T> operator*(const point_t<T>& a, T scale)
{
    point_t<T> ret{a};
    for (auto& x : ret) x *= scale;
    return ret;
}
template<typename T>
point_t<T> operator*(T scale, const point_t<T>& a)
{
    return a * scale;
}
template<typename T>
point_t<T> operator/(const point_t<T>& a, T scale)
{
    point_t<T> ret{a};
    for (auto& x : ret) x /= scale;
    return ret;
}
template<typename T>
point_t<T>& point_t<T>::operator*=(T scale)
{
    for (auto& y : this->x) y *= scale;
    return *this;
}

// minus
template<typename T>
point_t<T> operator-(const point_t<T>& a, const point_t<T>& b)
{
    if (a.size() != b.size()) { std::cerr << "a-b: a.size() != b.size(), exit..." << std::endl; exit(1); }
    // O(2n)
    // return a+(-1*b);

    // O(n)
    point_t<T> ret{a};
    for (std::size_t i = 0; i < ret.size(); ++i) { ret[i] -= b[i]; }
    return ret;
}
/**** operator ****/

// point_t cout
template<typename T>
std::ostream& operator<<(std::ostream& os, const point_t<T>& a)
{
    for (auto& x : a.x) os << x << ' ';
    return os;
}

// utility
template<typename T>
point_t<T> midpoint(const point_t<T>& a, const point_t<T>& b)
{
    if (a.size() != b.size()) { std::cerr << "mid_point(a,b): a.size() != b.size(), exit..." << std::endl; exit(1); }
    return a/(T)2+b/(T)2;
}

// distance
template<typename T>
double minkowski_dist(const point_t<T>& a, const point_t<T>& b, int p)
{
    if (a.size() != b.size()) { std::cerr << "minkowski_dist(a,b): a.size() != b.size(), exit..." << std::endl; exit(1); }
    double ret = 0;
    for (std::size_t i = 0; i < a.size(); ++i) ret += pow(a[i]-b[i], p);
    return pow(ret, 1.0/p);
}
template<typename T>
double euclidean_dist(const point_t<T>& a, const point_t<T>& b)
{
    // naive
    //const point_t c = a-b;
    //return sqrt(c*c);

    // minkowski
    return minkowski_dist(a, b, 2);
}

template<typename T>
bool point_t<T>::on(const hyperplane_t<T>& plane)
{
    return onplane(*this, plane);
}
/***** point_t ******/

/***** hyperplane_t and point_t *****/
template<typename T> bool operator<(const hyperplane_t<T>& plane, const point_t<T>& x)
{
    return plane.b < plane.n*x;
}
template<typename T> bool operator>(const hyperplane_t<T>& plane, const point_t<T>& x)
{
    return plane.n*x < plane.b;
}
template<typename T> bool operator<(const point_t<T>& x, const hyperplane_t<T>& plane)
{
    return plane.b > plane.n*x;
}
template<typename T> bool operator>(const point_t<T>& x, const hyperplane_t<T>& plane)
{
    return plane.n*x > plane.b;
}

template<typename T> bool onplane(const point_t<T>& x, const hyperplane_t<T>& plane)
{
    return abs(plane.b - plane.n*x) <= minerr;
}

/***** hyperplane_t *****/
// hyperplane_t cout
template<typename T>
std::ostream& operator<<(std::ostream& os, const hyperplane_t<T>& plane)
{
    os << "[ " << plane.n << "]^Tx = " << plane.b;
    return os;
}
/***** hyperplane_t *****/

/* ========================================== */


template<typename T, typename U>
dataset_t<T, U>& dataset_t<T, U>::operator=(const dataset_t& other)
{
    this->data = other.data;
    this->label = other.label;
    return *this;
}
template<typename T, typename U>
dataset_t<T, U>& dataset_t<T, U>::operator=(dataset_t&& other)
{
    this->data = std::move(other.data);
    this->label = std::move(other.label);
    return *this;
}
template<typename T, typename U>
dataset_t<T, U>& dataset_t<T, U>::operator+=(const dataset_t& other)
{
    this->data.insert(this->data.end(), other.data.begin(), other.data.end());
    this->label.extend(other.label);
    return *this;
}
template<typename T, typename U>
dataset_t<T, U>& dataset_t<T, U>::operator+=(dataset_t&& other)
{
    this->data.insert(this->data.end(), other.data.begin(), other.data.end());
    this->label.extend(other.label);
    return *this;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const dataset_t<T, U>& a)
{
    for (std::size_t i = 0; i < a.size(); ++i) os << "[ " << a.data[i] << "], " << a.label[i] << std::endl;
    return os;
}

template<typename T, typename U>
point_t<T> dataset_t<T, U>::extract(std::size_t column)
{
    if (column >= this->size())
    {
        std::cerr << "dataset_t::extract: column >= size\n";
        exit(1);
    }

    point_t<T> ret;
    for (const auto& data_: this->data)
        ret.emplace_back(data_[column]);
    return ret;
}

template<typename T, typename U>
auto dataset_t<T, U>::extract_with_label(std::size_t column) -> decltype(auto)
{
    if (column >= this->size())
    {
        std::cerr << "dataset_t::extract: column >= size\n";
        exit(1);
    }

    std::pair<point_t<T>, point_t<T>> ret;
    for (std::size_t i = 0; i < this->size(); ++i)
    {
        ret.first.emplace_back(this->data[i][column]);
        ret.second.emplace_back(this->label[i]);
    }
    return ret;
}

template<typename U>
double score(const point_t<U>& a, const point_t<U>& b, const std::function<double(const U&, const U&)>& loss)
{
	U ret = 0;
	if (a.size() != b.size()) { std::cerr << "score(): a.size() != b.size()" << std::endl; return 0; }
	for (std::size_t i = 0; i < a.size(); ++i)
		ret += loss(a[i], b[i]);
	return ret;
}
template<typename T, typename U>
double score(const dataset_t<T, U>& a, const dataset_t<T, U>& b, const std::function<double(const U&, const U&)>& loss)
{
	return score(a.label, b.label, loss);
}


template<typename T, typename U>
double dataset_t<T, U>::delta(const dataset_t<T, U>& other, const std::function<double(const U&, const U&)>& loss)
{
	return score<T, U>(*this, other, loss);
}

#endif
