#ifndef VARIABLE_H
#define VARIABLE_H

enum VarType {
    REALV,
    POINT,
    LINE,
    SEGMENT,
    RAY,
    PLANE,
    CIRCLE,
    ARC,
    SPHERE,
    EMPTY,
    SPACE,
    CONSTRUCTION,
    TUPLE,
    NULL
};

struct Vector3D {
    double x, y, z;
    bool defined;

    Vector3D() {
        x = 0, y = 0, z = 0, defined = 0;
    }

    Vector3D(double x, double y, double z) {
        x(x), y(y), z(z), defined = 1;
    }

    Vector3D operator + (Vector3D& v) {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator - (Vector3D& v) {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator * (double scalar) {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
}

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
}

struct Line : Var {
    Vector3D p, m;
    Line(Vector3D p, Vector3D m) : p(p), m(m) {
        type = LINE;
        size = sizeof(Line);
    }   
}

#endif