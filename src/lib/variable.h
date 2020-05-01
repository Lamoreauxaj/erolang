#ifndef VARIABLE_H
#define VARIABLE_H

enum VarType {
    REALV,
    POINT,
    LINE,
    SEGMENT, // later
    RAY,     // later
    PLANE,
    CIRCLE,
    ARC,     // later
    SPHERE,
    EMPTY,
    SPACE,
    CONSTRUCTION,
    TUPLE,
    UNDEFINED
};

struct Vector3D {
    double x, y, z;

    Vector3D() {
        x = 0, y = 0, z = 0;
    }

    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3D operator + (const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator - (const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator * (const double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator / (const double scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    bool operator == (const Vector3D& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    bool operator != (const Vector3D& v) const {
        return (x != v.x) || (y != v.y) || (z == v.z);
    }

    void operator = (const Vector3D& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    double mag2() {
        return x * x + y * y + z * z;
    }

    Vector3D dot(Vector3D& v) {
        return Vector3D(x * v.x, y * v.y, z * v.z);
    }
};

struct Var {
    VarType type;
    int size;
};

struct RealVar : Var {
    double val;
    RealVar(double val) : val(val) {
        type = REALV;
        size = sizeof(RealVar);
    }
};

struct Point : Var {
    Vector3D v;
    Point(Vector3D v) : v(v) {
        type = POINT;
        size = sizeof(Point);
    }
};

struct Line : Var {
    Point p;
    Vector3D m;
    Line(Point p, Vector3D m) : p(p), m(m) {
        type = LINE;
        size = sizeof(Line);
    }   
};

struct Plane : Var {
    Point p;
    Vector3D norm;
    Plane(Point p, Vector3D norm) : p(p), norm(norm) {
        type = PLANE;
        size = sizeof(Plane);
    }
};

struct Circle : Var {
    Point p;
    double r;
    Circle(Point p, double r) : p(p), r(r) {
        type = CIRCLE;
        size = sizeof(Circle);
    }
};

struct Sphere : Var {
    Point p;
    double r;
    Sphere(Point p, double r) : p(p), r(r) {
        type = SPHERE;
        size = sizeof(Sphere);
    }
};

struct Empty : Var {
    Empty() {
        type = EMPTY;
        size = sizeof(Empty);
    }
};



#endif