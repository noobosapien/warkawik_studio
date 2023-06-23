#ifndef QUATERION_H
#define QUATERION_H

#define QUAT_EPSILON 0.000001f

class Quat
{
public:
    inline Quat()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
        w = 0.f;
    };

    inline Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){

                                                                               };

    inline const float getX() { return x; }
    inline const float getY() { return y; }
    inline const float getZ() { return z; }
    inline const float getW() { return w; }

    friend Quat operator+(const Quat &a, const Quat &b);
    friend Quat operator-(const Quat &a, const Quat &b);
    friend Quat operator*(const Quat &a, float b);
    friend Quat operator-(const Quat &q);

    friend Quat operator*(const Quat &Q1, const Quat &Q2);
    friend glm::vec3 operator*(const Quat &Q1, const glm::vec3 &v);

    friend bool operator==(const Quat &left, const Quat &right);
    friend bool operator!=(const Quat &left, const Quat &right);
    friend Quat operator^(const Quat &Quat, float f);

    static Quat angleAxis(float angle, const glm::vec3 &axis);
    static Quat fromTo(const glm::vec3 &from, const glm::vec3 &to);

    static glm::vec3 getAxis(const Quat &q);
    static float getAngle(const Quat &q);

    static bool sameOrientation(const Quat &left, const Quat &right);

    static float dot(const Quat &a, const Quat &b);
    static float lenSq(const Quat &q);
    static float len(const Quat &q);

    static void normalize(Quat &q);

    static Quat normalized(const Quat &q);
    static Quat conjugate(const Quat &q);
    static Quat inverse(const Quat &q);

    static Quat mix(const Quat &from, const Quat &to, float t);
    static Quat nlerp(const Quat &from, const Quat &to, float t);

    static Quat slerp(const Quat &start, const Quat &end, float t);
    static Quat lookRotation(const glm::vec3 &direction, const glm::vec3 &up);

    static glm::mat4 quatToMat4(const Quat &q);
    static Quat mat4ToQuat(const glm::mat4 &m);

private:
    float x, y, z, w;
};

Quat operator+(const Quat &a, const Quat &b);
Quat operator-(const Quat &a, const Quat &b);
Quat operator*(const Quat &a, float b);
Quat operator-(const Quat &q);

Quat operator*(const Quat &Q1, const Quat &Q2);
glm::vec3 operator*(const Quat &Q1, const glm::vec3 &v);

bool operator==(const Quat &left, const Quat &right);
bool operator!=(const Quat &left, const Quat &right);
Quat operator^(const Quat &Quat, float f);

#endif