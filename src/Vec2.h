#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

template < class T >
class vec2
{
public:
    vec2(T x=0, T y=0)
        : _x(x), _y(y)
    {}

    bool operator==(const vec2 &) const;
    bool operator!=(const vec2 &) const;

    T get_x() const;
    T get_y() const;

    void set_x(T);
    void set_y(T);

    T operator[](int) const;
    T & operator[](int);
    
    vec2 & operator+=(const vec2 &);
    vec2 operator+(const vec2 &) const;

    vec2 & operator-=(const vec2 &);
    vec2 operator-(const vec2 &) const;

    vec2 operator-() const;
    
    vec2 & operator*=(T);
    vec2 operator*(T) const;

    vec2 & operator/=(T);
    vec2 operator/(T) const;

    double len() const;

private:
    T _x, _y;
};

template < class T >
vec2< T > operator*(T, const vec2< T > &);

template < class T >
T dot(const vec2< T > &, const vec2< T > &);

template < class T >
std::ostream & operator<<(std::ostream &, const vec2< T > &);

template <class T>
bool vec2< T >::operator==(const vec2 & v) const
{
    return (_x == v._x && _y == v._y);
}

template <class T>
bool vec2< T >::operator!=(const vec2< T > & v) const
{
    return !(*this == v);
}

template < class T >
T vec2< T >::get_x() const
{
    return _x;
}

template < class T >
T vec2< T >::get_y() const
{
    return _y;
}

template < class T >
void vec2< T >::set_x(T x)
{
    _x = x;
}

template < class T >
void vec2< T >::set_y(T y)
{
    _y = y;
}

template < class T >
T vec2< T >::operator[](int i) const
{
    return i == 0 ? _x : _y;
}

template < class T >
T & vec2< T >::operator[](int i) 
{
    return i == 0 ? _x : _y;
}

template < class T >
vec2< T > & vec2< T >::operator+=(const vec2< T > & v)
{
    _x += v._x;
    _y += v._y;
}

template < class T >
vec2< T > vec2< T >::operator+(const vec2< T > & v) const
{
    return vec2(*this) += v;

}

template < class T >
vec2< T > & vec2< T >::operator-=(const vec2< T > & v)
{
    _x -= v._x;
    _y -= v._y;
    
    return *this;
}

template < class T >
vec2< T > vec2< T >::operator-(const vec2< T > & v) const
{
    return vec2(*this) -= v;

}

template < class T >
vec2< T > vec2< T >::operator-() const
{
    return vec2< T >(-_x, -_y);
}

template <class T>
vec2< T > & vec2< T >::operator*=(T c)
{
    _x *= c;
    _y *= c;

    return *this;
}

template <class T>
vec2< T > operator*(T c, const vec2< T > & u)
{
    return u * c;
}

template <class T>
vec2< T > vec2< T >::operator*(T c) const
{
    return vec2(*this) *= c;
}

template <class T>
vec2< T > & vec2< T >::operator/=(T c)
{
    _x /= c;
    _y /= c;

    return *this;
}

template <class T>
vec2< T > vec2< T >::operator/(T c) const
{
    return vec2(*this) /= c;
}

template <class T>
double vec2< T >::len() const
{
    std::cout << _x << ' ' << _x * _x << ' ' << _y << ' ' << _y * _y << std::endl;
    return sqrt(_x * _x + _y * _y);
}

template <class T>
T dot(const vec2< T > & u, const vec2< T > & v)
{
    return u.get_x() * v.get_x() + u.get_y() * v.get_y();
}

template < class T >
std::ostream & operator<<(std::ostream & os, const vec2< T > & v)
{
    os << '<' << v.get_x() << ", " << v.get_y() << '>';

    return os;
}

typedef vec2< double > vec2d;

typedef vec2< int > vec2i;

#endif
