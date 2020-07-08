#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <random>

class vec3 {
public:
    vec3() : e{0, 0, 0} {};
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

    double x() const {
        return e[0];
    };
    double y() const {
        return e[1];
    };
    double z() const {
        return e[2];
    }

    vec3 operator~() const {
        return vec3(vec3(-e[0], -e[1], -e[2]));
    }

    double operator[](int i) const {
        return e[i];
    }

    double& operator[](int i) {
        return e[i];
    }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

public:
    double e[3];        
};

//alises of vec3
using point3 = vec3;    //3D Point
using color = vec3;     //RGB

    //vec3 Utility Functions;

    inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline vec3 operator+(const vec3& u, const vec3& v) {
        return vec3( u.x()+v.x(), u.y()+v.y(), u.z()+v.z() );
    }

    inline vec3 operator-(const vec3& u, const vec3& v) {
        return vec3( u.x()-v.x(), u.y()-v.y(), u.z()-v.z() );
    }

    inline vec3 operator*(const vec3& u, const vec3& v) {
        return vec3( u.x()*v.x(), u.y()*v.y(), u.z()*v.z() );
    }

    inline vec3 operator*(double t, const vec3& v) {
        return vec3( t*v.x(), t*v.y(), t*v.z() );
    }

    inline vec3 operator*(const vec3& v, double t) {
        return t*v;
    }

    inline vec3 operator/(const vec3& v, double t) {
        return (1/t)*v;
    }

    inline double dot(const vec3& u, const vec3& v) {
        return u.x()*v.x() + u.y()*v.y() + u.z()*v.z() ;
    }

    inline vec3 cross(const vec3& u, const vec3& v) {
        return vec3( u.y()*v.z() - u.z()*v.y(),
                    u.z()*v.x() - u.x()*v.z() , 
                    u.x()*v.y() - u.y()*v.x() );
    }

    inline vec3 unit_vector(vec3 v) {
        return v / v.length();
    }

    //inline double random_double() {
    //    return rand() / (RAND_MAX + 1.0);
    //}

    inline double random_double() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double random_double( double min, double max ) {
        return min + (max-min)*random_double();
    }

    inline vec3 randomVec() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline vec3 randomVec( double min, double max ) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    //在单位球上内随机选取1点
    vec3 random_in_unit_sphere() {
        while( true ) {
            auto p = randomVec(-1, 1);
            if( p.length_squared() >= 1 ) {
                continue;
            }
            return p;
        }
    }

#endif