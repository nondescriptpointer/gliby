#pragma once

#include <cmath>

namespace Math3D {

// basic vector types
typedef float Vector2f[2];
typedef double Vector2d[2];
typedef float Vector3f[3];
typedef double Vector3d[3];
typedef float Vector4f[4];
typedef double Vector4d[4];

// 3x3 matrix - column major
typedef float Matrix33f[9];
typedef double Matrix33d[9];
// 4x4 matrix - column major
typedef float Matrix44f[16];
typedef double Matrix44d[16];

// constants
#define PI (3.14159265358979323846)
#define PI2 (2.0 * M_PI)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)
// macros to do angle conversions by compiler
#define degToRad(x) ((x)*PI_DIV_180)
#define radToDeg(x) ((x)*INV_PI_DIV_180)
// hour angles
#define hrToDeg(x) ((x) * (1.0 / 15.0))
#define hrToRad(x) degToRad(hrToDeg(x))
#define degToHr(x) ((x) * 15.0)
#define radToHr(x) degToHr(radToDeg(x))

// return same number if power of 2 or the next highest power of two if not
unsigned int firstPowOf2(const unsigned int val);

/*
 * VECTOR OPERATIONS
 * */

// can't overload fully because function signature of Vector2f 

// output vector
void outputVector2(Vector3f v);
void outputVector2(Vector3d v);
void outputVector3(Vector3f v);
void outputVector3(Vector3d v);
void outputVector4(Vector3f v);
void outputVector4(Vector3d v);

// add vectors (r = a + b)
void addVectors2(Vector2f r, const Vector2f a, const Vector2f b);
void addVectors2(Vector2d r, const Vector2d a, const Vector2d b);
void addVectors3(Vector3f r, const Vector3f a, const Vector3f b);
void addVectors3(Vector3d r, const Vector3d a, const Vector3d b);
void addVectors4(Vector4f r, const Vector4f a, const Vector4f b);
void addVectors4(Vector4d r, const Vector4d a, const Vector4d b);

// subtract vectors (r = a - b)
void subtractVectors2(Vector2f r, const Vector2f a, const Vector2f b); 
void subtractVectors2(Vector2d r, const Vector2d a, const Vector2d b); 
void subtractVectors3(Vector3f r, const Vector3f a, const Vector3f b); 
void subtractVectors3(Vector3d r, const Vector3d a, const Vector3d b); 
void subtractVectors4(Vector4f r, const Vector4f a, const Vector4f b); 
void subtractVectors4(Vector4d r, const Vector4d a, const Vector4d b); 

// scale vectors (in place)
void scaleVector2(Vector2f r, const float scale);
void scaleVector2(Vector2d r, const double scale);
void scaleVector3(Vector3f r, const float scale);
void scaleVector3(Vector3d r, const double scale);
void scaleVector4(Vector4f r, const float scale);
void scaleVector4(Vector4d r, const double scale);

// cross product (only makes sense for Vector3)
void crossProduct(Vector3f r, const Vector3f u, const Vector3f v);
void crossProduct(Vector3d r, const Vector3d u, const Vector3d v);

// dot product (only Vector3)
float dotProduct(const Vector3f u, const Vector3f v);
double dotProduct(const Vector3d u, const Vector3d v);

// get square of vector length
float getVectorLengthSquared(const Vector3f v);
double getVectorLengthSquared(const Vector3d v);

// get vector length
float getVectorLength(const Vector3f v);
double getVectorLength(const Vector3d v);

// normalize a vector to unit length
void normalizeVector(Vector3f v);
void normalizeVector(Vector3d v);

// angle between normalized vectors in radians
float angleBetweenVectors(const Vector3f u, const Vector3f v);
double angleBetweenVectors(const Vector3d u, const Vector3d v);

// distance between points (magnitude of difference between vector)
float getDistanceSquared(const Vector3f u, const Vector3f v);
double getDistanceSquared(const Vector3d u, const Vector3d v);
float getDistance(const Vector3f u, const Vector3f v);
double getDistance(const Vector3d u, const Vector3d v);

// magnitude of single vector
float getMagnitudeSquared(const Vector3f v);
double getMagnitudeSquared(const Vector3d v);
float getMagnitude(const Vector3f v);
double getMagnitude(const Vector3d v);

/*
 * MATRIX OPERATIONS
 * */

// output matrix
void outputMatrix33(Matrix33f m);
void outputMatrix33(Matrix33d m);
void outputMatrix44(Matrix44f m);
void outputMatrix44(Matrix44d m);

// load identity matrix
void loadIdentity33(Matrix33f m);
void loadIdentity33(Matrix33d m);
void loadIdentity44(Matrix44f m);
void loadIdentity44(Matrix44d m);

// retrieve/set columns
void getMatrixColumn33(Vector3f dst, const Matrix33f src, const int column);
void getMatrixColumn33(Vector3d dst, const Matrix33d src, const int column);
void getMatrixColumn44(Vector4f dst, const Matrix44f src, const int column);
void getMatrixColumn44(Vector4d dst, const Matrix44d src, const int column);
void setMatrixColumn33(Matrix33f dst, const Vector3f src, const int column);
void setMatrixColumn33(Matrix33d dst, const Vector3d src, const int column);
void setMatrixColumn44(Matrix44f dst, const Vector4f src, const int column);
void setMatrixColumn44(Matrix44d dst, const Vector4d src, const int column);

// extract a 3x3 rotation matrix from a 4x4 matrix
void extractRotationMatrix(Matrix33f dst, const Matrix44f src);
void extractRotationMatrix(Matrix33d dst, const Matrix44d src);

// inject 3x3 rotation matrix into a 4x4 matrix
void injectRotationMatrix(Matrix44f dst, const Matrix33f src);
void injectRotationMatrix(Matrix44d dst, const Matrix33d src);

// multiply matrices
void multiplyMatrix33(Matrix33f p, const Matrix33f a, const Matrix33f b);
void multiplyMatrix33(Matrix33d p, const Matrix33d a, const Matrix33d b);
void multiplyMatrix44(Matrix44f p, const Matrix44f a, const Matrix44f b);
void multiplyMatrix44(Matrix44d p, const Matrix44d a, const Matrix44d b);

// transform vector using transformation matrix
void transformVector3(Vector3f out, const Vector3f v, const Matrix44f m);
void transformVector3(Vector3d out, const Vector3d v, const Matrix44d m);
void transformVector4(Vector4f out, const Vector4f v, const Matrix44f m);
void transformVector4(Vector4d out, const Vector4d v, const Matrix44d m);

// rotate vector using 3x3 matrix
void rotateVector(Vector3f out, const Vector3f p, const Matrix33f m);
void rotateVector(Vector3d out, const Vector3d p, const Matrix33d m);

// create scaling matrix
void scaleMatrix33(Matrix33f m, const float x, const float y, const float z);
void scaleMatrix33(Matrix33d m, const double x, const double y, const double z);
void scaleMatrix33(Matrix33f m, const Vector3f scale);
void scaleMatrix33(Matrix33d m, const Vector3d scale);
void scaleMatrix44(Matrix44f m, const float x, const float y, const float z);
void scaleMatrix44(Matrix44d m, const double x, const double y, const double z);
void scaleMatrix44(Matrix44f m, const Vector3f scale);
void scaleMatrix44(Matrix44d m, const Vector3d scale);

// creation of projection matrices, fov is radians
void makePerspectiveMatrix(Matrix44f projection, const float fov, const float aspect, const float zMin, const float zMax);
void makeOrthographicMatrix(Matrix44f projection, const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);

// create rotation matrix (angle is radians again)
void rotationMatrix33(Matrix33f m, const float angle, float x, float y, float z);
void rotationMatrix33(Matrix33d m, const double angle, double x, double y, double z);
void rotationMatrix44(Matrix44f m, const float angle, float x, float y, float z);
void rotationMatrix44(Matrix44d m, const double angle, double x, double y, double z);

// translation matrix
void translationMatrix(Matrix44f m, float x, float y, float z);
void translationMatrix(Matrix44d m, double x, double y, double z);

// determinant 
float detIJ(const Matrix44f m, const int i, const int j);
double detIJ(const Matrix44d m, const int i, const int j);

// invert matrix
void invertMatrix44(Matrix44f inverse, const Matrix44f m);
void invertMatrix44(Matrix44d inverse, const Matrix44d m);

/*
 * OTHER
 * */

// find normal from 3 vectors
void findNormal(Vector3f result, const Vector3f p1, const Vector3f p2, const Vector3f p3);
void findNormal(Vector3d result, const Vector3d p1, const Vector3d p2, const Vector3d p3);

// calculate the signed distance of a point to a plane
float getDistanceToPlane(const Vector3f point, const Vector4f plane);
double getDistanceToPlane(const Vector3d point, const Vector4d plane);

// get plane equation from three points
void getPlaneEquation(Vector4f planeEq, const Vector3f p1, const Vector3f p2, const Vector3f p3);
void getPlaneEquation(Vector4d planeEq, const Vector3d p1, const Vector3d p2, const Vector3d p3);

// determine if ray intersects sphere (< 0 if not, 0 if tangent, > 0 is distance to intersection point)
float raySphereTest(const Vector3f point, const Vector3f ray, const Vector3f sphereCenter, const float sphereRadius);
double raySphereTest(const Vector3d point, const Vector3d ray, const Vector3d sphereCenter, const double sphereRadius);

// faster erplacements for gluProject
void projectXY(Vector2f out, const Matrix44f modelView, const Matrix44f projection, const int viewport[4], const Vector3f in);
void projectXYZ(Vector3f out, const Matrix44f modelView, const Matrix44f projection, const int viewport[4], const Vector3f in);

// compare floats and dobules
bool closeEnough(const float candidate, const float compare, const float epsilon);
bool closeEnough(const double candidate, const double compare, const double epsilon);

// Catmull-Rom spline interpolation between two points
void catmullRom(Vector3f out, const Vector3f p0, const Vector3f p1, const Vector3f p2, const Vector3f p3, float t);
void catmullRom(Vector3d out, const Vector3d p0, const Vector3d p1, const Vector3d p2, const Vector3d p3, double t);

// Calculate tangent basis of a triangle. Used for normal mapping
void calculateTangentBasis(Vector3f tangent, const Vector3f triangle[3], const Vector2f textCoords[3], const Vector3f n);

// Smoothly step between 0 and 1 between edge 1 and edge 2
float smoothStep(const float edge1, const float edge2, const float x);
double smoothStep(const double edge1, const double edge2, const double x);

// Planar shadow matrix
void makePlanarShadowMatrix(Matrix44f proj, const Vector4f planeEq, const Vector3f lightPos);
void makePlanarShadowMatrix(Matrix44d proj, const Vector4d planeEq, const Vector3d lightPos);

// Closest point on a ray to another point in space
float closestPointOnRay(Vector3f pointOnRay, const Vector3f rayOrigin, const Vector3f unitRayDirection, const Vector3f pointInSpace);
double closestPointOnRay(Vector3d pointOnRay, const Vector3d rayOrigin, const Vector3d unitRayDirection, const Vector3d pointInSpace);

}
