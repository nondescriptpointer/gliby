#include <Math3D.h>
#include <string.h>
#include <iostream>
using namespace Math3D;

unsigned int Math3D::firstPowOf2(unsigned int val){
    unsigned int pow2 = 1;
    while(val > pow2){
        pow2 = (pow2 << 1);
    }
    return pow2;
}

/*
 * VECTOR OPERATIONS
 * */

void Math3D::outputVector2(Vector3f v){
    std::cout << "{" << v[0] << ", " << v[1] << "}" << std::endl;
}
void Math3D::outputVector2(Vector3d v){
    std::cout << "{" << v[0] << ", " << v[1] << "}" << std::endl;
}
void Math3D::outputVector3(Vector3f v){
    std::cout << "{" << v[0] << ", " << v[1] << ", " << v[2] << "}" << std::endl;
}
void Math3D::outputVector3(Vector3d v){
    std::cout << "{" << v[0] << ", " << v[1] << ", " << v[2] << "}" << std::endl;
}
void Math3D::outputVector4(Vector3f v){
    std::cout << "{" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "}" << std::endl;
}
void Math3D::outputVector4(Vector3d v){
    std::cout << "{" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "}" << std::endl;
}

void Math3D::addVectors2(Vector2f r, const Vector2f a, const Vector2f b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; }
void Math3D::addVectors2(Vector2d r, const Vector2d a, const Vector2d b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; }
void Math3D::addVectors3(Vector3f r, const Vector3f a, const Vector3f b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
void Math3D::addVectors3(Vector3d r, const Vector3d a, const Vector3d b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
void Math3D::addVectors4(Vector4f r, const Vector4f a, const Vector4f b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }
void Math3D::addVectors4(Vector4d r, const Vector4d a, const Vector4d b){ r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }

void Math3D::subtractVectors2(Vector2f r, const Vector2f a, const Vector2f b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; };
void Math3D::subtractVectors2(Vector2d r, const Vector2d a, const Vector2d b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; };
void Math3D::subtractVectors3(Vector3f r, const Vector3f a, const Vector3f b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; };
void Math3D::subtractVectors3(Vector3d r, const Vector3d a, const Vector3d b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; };
void Math3D::subtractVectors4(Vector4f r, const Vector4f a, const Vector4f b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; };
void Math3D::subtractVectors4(Vector4d r, const Vector4d a, const Vector4d b){ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; };

void Math3D::scaleVector2(Vector2f v, const float scale){ v[0] *= scale; v[1] *= scale; }
void Math3D::scaleVector2(Vector2d v, const double scale){ v[0] *= scale; v[1] *= scale; }
void Math3D::scaleVector3(Vector3f v, const float scale){ v[0] *= scale; v[1] *= scale; v[2] *= scale; }
void Math3D::scaleVector3(Vector3d v, const double scale){ v[0] *= scale; v[1] *= scale; v[2] *= scale; }
void Math3D::scaleVector4(Vector4f v, const float scale){ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }
void Math3D::scaleVector4(Vector4d v, const double scale){ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }

void Math3D::crossProduct(Vector3f r, const Vector3f u, const Vector3f v){ 
    r[0] = u[1]*v[2] - v[1]*u[2];
    r[1] = -u[0]*v[2] + v[0]*u[2];
    r[2] = u[0]*v[1] - v[0]*u[1];
}
void Math3D::crossProduct(Vector3d r, const Vector3d u, const Vector3d v){
    r[0] = u[1]*v[2] - v[1]*u[2];
    r[1] = -u[0]*v[2] + v[0]*u[2];
    r[2] = u[0]*v[1] - v[0]*u[1];
}

float Math3D::dotProduct(const Vector3f u, const Vector3f v){ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }
double Math3D::dotProduct(const Vector3d u, const Vector3d v){ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }

float Math3D::getVectorLengthSquared(const Vector3f v){ return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]); }
double Math3D::getVectorLengthSquared(const Vector3d v){ return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]); }

float Math3D::getVectorLength(const Vector3f v){ return sqrt(getVectorLengthSquared(v)); }
double Math3D::getVectorLength(const Vector3d v){ return sqrt(getVectorLengthSquared(v)); }

void Math3D::normalizeVector(Vector3f v){ scaleVector3(v,1/getVectorLength(v)); }
void Math3D::normalizeVector(Vector3d v){ scaleVector3(v,1/getVectorLength(v)); }

float Math3D::angleBetweenVectors(const Vector3f u, const Vector3f v){
    float temp = dotProduct(u, v);
    return acos(temp);
}
double Math3D::angleBetweenVectors(const Vector3d u, const Vector3d v){
    double temp = dotProduct(u, v);
    return acos(temp);
}

float Math3D::getDistanceSquared(const Vector3f u, const Vector3f v){
    float x = u[0]-v[0];
    x = x*x;
    float y = u[1]-v[1];
    y = y*y;
    float z = u[2]-v[2];
    z = z*z;
    return (x + y + z);
}
double Math3D::getDistanceSquared(const Vector3d u, const Vector3d v){
    double x = u[0]-v[0];
    x = x*x;
    double y = u[1]-v[1];
    y = y*y;
    double z = u[2]-v[2];
    z = z*z;
    return (x + y + z);
}
float Math3D::getDistance(const Vector3f u, const Vector3f v){ return sqrtf(getDistanceSquared(u,v)); }
double Math3D::getDistance(const Vector3d u, const Vector3d v){ return sqrt(getDistanceSquared(u,v)); }

float Math3D::getMagnitudeSquared(const Vector3f v){ return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }
double Math3D::getMagnitudeSquared(const Vector3d v){ return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }
float Math3D::getMagnitude(const Vector3f v){ return sqrtf(getMagnitudeSquared(v)); }
double Math3D::getMagnitude(const Vector3d v){ return sqrt(getMagnitudeSquared(v)); }

/*
 * MATRIX OPERATIONS
 * */

// macro's to get an item at row/column
#define el4(matrix,row,col) matrix[(col<<2)+row]
#define el3(matrix,row,col) matrix[(col*3)+row]

void Math3D::outputMatrix33(Matrix33f m){
    std::cout << "| " << el3(m,0,0) << " " << el3(m,0,1) << " " << el3(m,0,2) << " |" << std::endl;
    std::cout << "| " << el3(m,1,0) << " " << el3(m,1,1) << " " << el3(m,1,2) << " |" << std::endl;
    std::cout << "| " << el3(m,2,0) << " " << el3(m,2,1) << " " << el3(m,2,2) << " |" << std::endl;
    std::cout << std::endl;
}
void Math3D::outputMatrix33(Matrix33d m){
    std::cout << "| " << el3(m,0,0) << " " << el3(m,0,1) << " " << el3(m,0,2) << " |" << std::endl;
    std::cout << "| " << el3(m,1,0) << " " << el3(m,1,1) << " " << el3(m,1,2) << " |" << std::endl;
    std::cout << "| " << el3(m,2,0) << " " << el3(m,2,1) << " " << el3(m,2,2) << " |" << std::endl;
    std::cout << std::endl;
}
void Math3D::outputMatrix44(Matrix44f m){
    std::cout << "| " << el4(m,0,0) << " " << el4(m,0,1) << " " << el4(m,0,2) << " " << el4(m,0,3) << " |" << std::endl;
    std::cout << "| " << el4(m,1,0) << " " << el4(m,1,1) << " " << el4(m,1,2) << " " << el4(m,1,3) << " |" << std::endl;
    std::cout << "| " << el4(m,2,0) << " " << el4(m,2,1) << " " << el4(m,2,2) << " " << el4(m,2,3) << " |" << std::endl;
    std::cout << "| " << el4(m,3,0) << " " << el4(m,3,1) << " " << el4(m,3,2) << " " << el4(m,3,3) << " |" << std::endl;
    std::cout << std::endl;
}
void Math3D::outputMatrix44(Matrix44d m){
    std::cout << "| " << el4(m,0,0) << " " << el4(m,0,1) << " " << el4(m,0,2) << " " << el4(m,0,3) << " |" << std::endl;
    std::cout << "| " << el4(m,1,0) << " " << el4(m,1,1) << " " << el4(m,1,2) << " " << el4(m,1,3) << " |" << std::endl;
    std::cout << "| " << el4(m,2,0) << " " << el4(m,2,1) << " " << el4(m,2,2) << " " << el4(m,2,3) << " |" << std::endl;
    std::cout << "| " << el4(m,3,0) << " " << el4(m,3,1) << " " << el4(m,3,2) << " " << el4(m,3,3) << " |" << std::endl;
    std::cout << std::endl;
}

void Math3D::loadIdentity33(Matrix33f m){
    static Matrix33f identity = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    memcpy(m, identity, sizeof(Matrix33f));
}
void Math3D::loadIdentity33(Matrix33d m){
    static Matrix33d identity = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    memcpy(m, identity, sizeof(Matrix33d));
}
void Math3D::loadIdentity44(Matrix44f m){
    static Matrix44f identity = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    memcpy(m, identity, sizeof(Matrix44f));
}
void Math3D::loadIdentity44(Matrix44d m){
    static Matrix44d identity = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    memcpy(m, identity, sizeof(Matrix44d));
}

void Math3D::getMatrixColumn33(Vector3f dst, const Matrix33f src, const int column){ memcpy(dst, src + (3 * column), sizeof(float) * 3); }
void Math3D::getMatrixColumn33(Vector3d dst, const Matrix33d src, const int column){ memcpy(dst, src + (3 * column), sizeof(double) * 3); }
void Math3D::getMatrixColumn44(Vector4f dst, const Matrix44f src, const int column){ memcpy(dst, src + (4 * column), sizeof(float) * 4); }
void Math3D::getMatrixColumn44(Vector4d dst, const Matrix44d src, const int column){ memcpy(dst, src + (4 * column), sizeof(double) * 4); }
void Math3D::setMatrixColumn33(Matrix33f dst, const Vector3f src, const int column){ memcpy(dst + (3 * column), src, sizeof(float) * 3); }
void Math3D::setMatrixColumn33(Matrix33d dst, const Vector3d src, const int column){ memcpy(dst + (3 * column), src, sizeof(double) * 3); }
void Math3D::setMatrixColumn44(Matrix44f dst, const Vector4f src, const int column){ memcpy(dst + (4 * column), src, sizeof(float) * 4); }
void Math3D::setMatrixColumn44(Matrix44d dst, const Vector4d src, const int column){ memcpy(dst + (4 * column), src, sizeof(double) * 4); }

void Math3D::extractRotationMatrix(Matrix33f dst, const Matrix44f src){
    memcpy(dst, src, sizeof(float) * 3); // x
    memcpy(dst + 3, src + 4, sizeof(float) * 3); // y
    memcpy(dst + 6, src + 8, sizeof(float) * 3); // z
}
void Math3D::extractRotationMatrix(Matrix33d dst, const Matrix44d src){
    memcpy(dst, src, sizeof(double) * 3); // x
    memcpy(dst + 3, src + 4, sizeof(double) * 3); // y
    memcpy(dst + 6, src + 8, sizeof(double) * 3); // z
}

void Math3D::injectRotationMatrix(Matrix44f dst, const Matrix33f src){
    memcpy(dst, src, sizeof(float) * 4);
    memcpy(dst + 4, src + 4, sizeof(float) * 4);
    memcpy(dst + 8, src + 8, sizeof(float) * 4);
}
void Math3D::injectRotationMatrix(Matrix44d dst, const Matrix33d src){
    memcpy(dst, src, sizeof(double) * 4);
    memcpy(dst + 4, src + 4, sizeof(double) * 4);
    memcpy(dst + 8, src + 8, sizeof(double) * 4);
}

void Math3D::multiplyMatrix33(Matrix33f p, const Matrix33f a, const Matrix33f b){
    for(int i = 0; i < 3; i++){
        float a0 = el3(a,i,0), a1 = el3(a,i,1), a2 = el3(a,i,2);
        el3(p,i,0) = a0 * el3(b,0,0) + a1 * el3(b,1,0) + a2 * el3(b,2,0);
        el3(p,i,1) = a0 * el3(b,0,1) + a1 * el3(b,1,1) + a2 * el3(b,2,1);
        el3(p,i,2) = a0 * el3(b,0,2) + a1 * el3(b,1,2) + a2 * el3(b,2,2);
    }
}
void Math3D::multiplyMatrix33(Matrix33d p, const Matrix33d a, const Matrix33d b){
    for(int i = 0; i < 3; i++){
        double a0 = el3(a,i,0), a1 = el3(a,i,1), a2 = el3(a,i,2);
        el3(p,i,0) = a0 * el3(b,0,0) + a1 * el3(b,1,0) + a2 * el3(b,2,0);
        el3(p,i,1) = a0 * el3(b,0,1) + a1 * el3(b,1,1) + a2 * el3(b,2,1);
        el3(p,i,2) = a0 * el3(b,0,2) + a1 * el3(b,1,2) + a2 * el3(b,2,2);
    }
}
void Math3D::multiplyMatrix44(Matrix44f p, const Matrix44f a, const Matrix44f b){
    for(int i = 0; i < 4; i++){
        float a0 = el4(a,i,0), a1 = el4(a,i,1), a2 = el4(a,i,2), a3 = el4(a,i,3);
        el4(p,i,0) = a0 * el4(b,0,0) + a1 * el4(b,1,0) + a2 * el4(b,2,0) + a3 * el4(b,3,0);
        el4(p,i,1) = a0 * el4(b,0,1) + a1 * el4(b,1,1) + a2 * el4(b,2,1) + a3 * el4(b,3,1);
        el4(p,i,2) = a0 * el4(b,0,2) + a1 * el4(b,1,2) + a2 * el4(b,2,2) + a3 * el4(b,3,2);
        el4(p,i,3) = a0 * el4(b,0,3) + a1 * el4(b,1,3) + a2 * el4(b,2,3) + a3 * el4(b,3,3);
    }
}
void Math3D::multiplyMatrix44(Matrix44d p, const Matrix44d a, const Matrix44d b){
    for(int i = 0; i < 4; i++){
        double a0 = el4(a,i,0), a1 = el4(a,i,1), a2 = el4(a,i,2), a3 = el4(a,i,3);
        el4(p,i,0) = a0 * el4(b,0,0) + a1 * el4(b,1,0) + a2 * el4(b,2,0) + a3 * el4(b,3,0);
        el4(p,i,1) = a0 * el4(b,0,1) + a1 * el4(b,1,1) + a2 * el4(b,2,1) + a3 * el4(b,3,1);
        el4(p,i,2) = a0 * el4(b,0,2) + a1 * el4(b,1,2) + a2 * el4(b,2,2) + a3 * el4(b,3,2);
        el4(p,i,3) = a0 * el4(b,0,3) + a1 * el4(b,1,3) + a2 * el4(b,2,3) + a3 * el4(b,3,3);
    }
}

void Math3D::transformVector3(Vector3f out, const Vector3f v, const Matrix44f m){
    out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];
    out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];
    out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];
}
void Math3D::transformVector3(Vector3d out, const Vector3d v, const Matrix44d m){
    out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];
    out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];
    out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];
}
void Math3D::transformVector4(Vector4f out, const Vector4f v, const Matrix44f m){
    out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
    out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
    out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
    out[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}
void Math3D::transformVector4(Vector4d out, const Vector4d v, const Matrix44d m){
    out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
    out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
    out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
    out[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}

void Math3D::rotateVector(Vector3f out, const Vector3f p, const Matrix33f m){
    out[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
    out[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
    out[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
}
void Math3D::rotateVector(Vector3d out, const Vector3d p, const Matrix33d m){
    out[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
    out[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
    out[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
}

void Math3D::scaleMatrix33(Matrix33f m, const float x, const float y, const float z){
    loadIdentity33(m); m[0] = x; m[4] = y; m[8] = z;
}
void Math3D::scaleMatrix33(Matrix33d m, const double x, const double y, const double z){
    loadIdentity33(m); m[0] = x; m[4] = y; m[8] = z;
}
void Math3D::scaleMatrix33(Matrix33f m, const Vector3f scale){
    loadIdentity33(m); m[0] = scale[0]; m[4] = scale[1]; m[8] = scale[2];
}
void Math3D::scaleMatrix33(Matrix33d m, const Vector3d scale){
    loadIdentity33(m); m[0] = scale[0]; m[4] = scale[1]; m[8] = scale[2];
}
void Math3D::scaleMatrix44(Matrix44f m, const float x, const float y, const float z){
    loadIdentity44(m); m[0] = x; m[5] = y; m[10] = z;
}
void Math3D::scaleMatrix44(Matrix44d m, const double x, const double y, const double z){
    loadIdentity44(m); m[0] = x; m[5] = y; m[10] = z;
}
void Math3D::scaleMatrix44(Matrix44f m, const Vector3f scale){
    loadIdentity44(m); m[0] = scale[0]; m[5] = scale[1]; m[10] = scale[2];
}
void Math3D::scaleMatrix44(Matrix44d m, const Vector3d scale){
    loadIdentity44(m); m[0] = scale[0]; m[5] = scale[1]; m[10] = scale[2];
}

void Math3D::makePerspectiveMatrix(Matrix44f projection, const float fov, const float aspect, const float zMin, const float zMax){
    loadIdentity44(projection);
    const float yMax = zMin * tanf(fov * 0.5f);
    const float yMin = -yMax;
    const float xMin = yMin * aspect;
    const float xMax = -xMin;
    projection[0] = (2 * zMin) / (xMax - xMin);
    projection[5] = (2 * zMin) / (yMax - yMin);
    projection[8] = (xMax + xMin) / (xMax - xMin);
    projection[9] = (yMax + yMin) / (yMax - yMin);
    projection[10] = -((zMax + zMin) / (zMax - zMin));
    projection[11] = -1;
    projection[14] = -((2*(zMax*zMin))/(zMax-zMin));
    projection[15] = 0;
}
void Math3D::makeOrthographicMatrix(Matrix44f projection, const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax){
    loadIdentity44(projection);
    projection[0] = 2.0f / (xMax - xMin);
    projection[5] = 2.0f / (yMax - yMin);
    projection[10] = -2.0f / (zMax - zMin);
    projection[12] = -((xMax + xMin)/(xMax - xMin));
    projection[13] = -((yMax + yMin)/(yMax - yMin));
    projection[14] = -((zMax + zMin)/(zMax - zMin));
    projection[15] = 1.0f;
}

void Math3D::rotationMatrix33(Matrix33f m, const float angle, float x, float y, float z){
    float s = sin(angle), c = cos(angle);

    float mag = sqrt(x*x+y*y+z*z);
    // identity if no magnitude
    if(mag == 0){ loadIdentity33(m); return; }
    // normalize
    x/=mag; y/=mag; z/=mag;

    float one_c = 1 - c;
    float xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x, xs = x * s, ys = y * s, zs = z * s;
    el3(m,0,0) = (one_c * xx) + c;
    el3(m,0,1) = (one_c * xy) + zs;
    el3(m,0,2) = (one_c * zx) + ys;
    el3(m,1,0) = (one_c * xy) + zs;
    el3(m,1,1) = (one_c * yy) + c;
    el3(m,1,2) = (one_c * yz) - xs;
    el3(m,2,0) = (one_c * zx) - ys;
    el3(m,2,1) = (one_c * yz) + xs;
    el3(m,2,2) = (one_c * zz) + c;
}
void Math3D::rotationMatrix33(Matrix33d m, const double angle, double x, double y, double z){
    double s = sin(angle), c = cos(angle);

    float mag = sqrt(x*x+y*y+z*z);
    // identity if no magnitude
    if(mag == 0){ loadIdentity33(m); return; }
    // normalize
    x/=mag; y/=mag; z/=mag;

    double one_c = 1 - c;
    double xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x, xs = x * s, ys = y * s, zs = z * s;
    el3(m,0,0) = (one_c * xx) + c;
    el3(m,0,1) = (one_c * xy) + zs;
    el3(m,0,2) = (one_c * zx) + ys;
    el3(m,1,0) = (one_c * xy) + zs;
    el3(m,1,1) = (one_c * yy) + c;
    el3(m,1,2) = (one_c * yz) - xs;
    el3(m,2,0) = (one_c * zx) - ys;
    el3(m,2,1) = (one_c * yz) + xs;
    el3(m,2,2) = (one_c * zz) + c;
}
void Math3D::rotationMatrix44(Matrix44f m, const float angle, float x, float y, float z){
    float s = sin(angle), c = cos(angle);

    float mag = sqrt(x*x+y*y+z*z);
    // identity if no magnitude
    if(mag == 0){ loadIdentity44(m); return; }
    // normalize
    x/=mag; y/=mag; z/=mag;

    float one_c = 1 - c;
    float xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x, xs = x * s, ys = y * s, zs = z * s;
    el4(m,0,0) = (one_c * xx) + c;
    el4(m,0,1) = (one_c * xy) + zs;
    el4(m,0,2) = (one_c * zx) + ys;
    el4(m,0,3) = 0;
    el4(m,1,0) = (one_c * xy) + zs;
    el4(m,1,1) = (one_c * yy) + c;
    el4(m,1,2) = (one_c * yz) - xs;
    el4(m,1,3) = 0;
    el4(m,2,0) = (one_c * zx) - ys;
    el4(m,2,1) = (one_c * yz) + xs;
    el4(m,2,2) = (one_c * zz) + c;
    el4(m,2,3) = 0;
    el4(m,3,0) = 0;
    el4(m,3,1) = 0;
    el4(m,3,2) = 0;
    el4(m,3,3) = 1;
}
void Math3D::rotationMatrix44(Matrix44d m, const double angle, double x, double y, double z){
    double s = sin(angle), c = cos(angle);

    double mag = sqrt(x*x+y*y+z*z);
    // identity if no magnitude
    if(mag == 0){ loadIdentity44(m); return; }
    // normalize
    x/=mag; y/=mag; z/=mag;

    double one_c = 1 - c;
    double xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x, xs = x * s, ys = y * s, zs = z * s;
    el4(m,0,0) = (one_c * xx) + c;
    el4(m,0,1) = (one_c * xy) + zs;
    el4(m,0,2) = (one_c * zx) + ys;
    el4(m,0,3) = 0;
    el4(m,1,0) = (one_c * xy) + zs;
    el4(m,1,1) = (one_c * yy) + c;
    el4(m,1,2) = (one_c * yz) - xs;
    el4(m,1,3) = 0;
    el4(m,2,0) = (one_c * zx) - ys;
    el4(m,2,1) = (one_c * yz) + xs;
    el4(m,2,2) = (one_c * zz) + c;
    el4(m,2,3) = 0;
    el4(m,3,0) = 0;
    el4(m,3,1) = 0;
    el4(m,3,2) = 0;
    el4(m,3,3) = 1;
}

void Math3D::translationMatrix(Matrix44f m, const float x, const float y, const float z){
    loadIdentity44(m); m[12] = x; m[13] = y; m[14] = z;
}
void Math3D::translationMatrix(Matrix44d m, const double x, const double y, const double z){
    loadIdentity44(m); m[12] = x; m[13] = y; m[14] = z;
}

float Math3D::detIJ(const Matrix44f m, const int i, const int j){
    float ret, mat[3][3];
    int x = 0;
    for(int ii = 0; ii < 4; ++ii){
        if(ii == i) continue;
        int y = 0;
        for(int jj = 0; jj < 4; ++jj){
            if(jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            ++y;
        }
        ++x;
    } 
    ret =  mat[0][0] * (mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1] * (mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2] * (mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    return ret;
}
double Math3D::detIJ(const Matrix44d m, const int i, const int j){
    double ret, mat[3][3];
    int x = 0;
    for(int ii = 0; ii < 4; ++ii){
        if(ii == i) continue;
        int y = 0;
        // added conditions to this loop to stop out of bounds compiler warning
        // curiously, it's not needed for the float version of this function
        for(int jj = 0; jj < 4 && x < 3 && y < 3; ++jj){
            if(jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            ++y; 
        }
        ++x; 
    } 
    ret =  mat[0][0] * (mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1] * (mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2] * (mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    return ret;
}

void Math3D::invertMatrix44(Matrix44f inverse, const Matrix44f m){
    // calculate 4x4 determinant
    float det = 0;
    for(int i = 0; i < 4; i++){
        det += (i & 0x1) ? (-m[i] * detIJ(m,0,i)) : (m[i] * detIJ(m,0,i));
    }
    det = 1 / det;
    // calculate inverse
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            float detij = detIJ(m,j,i);
            inverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij * det);
        }
    }
}
void Math3D::invertMatrix44(Matrix44d inverse, const Matrix44d m){
    // calculate 4x4 determinant
    double det = 0;
    for(int i = 0; i < 4; i++){
        det += (i & 0x1) ? (-m[i] * detIJ(m,0,i)) : (m[i] * detIJ(m,0,i));
    }
    det = 1 / det;
    // calculate inverse
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            double detij = detIJ(m,j,i);
            inverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij * det);
        }
    }
}

#undef el4
#undef el3

/*
 * OTHER
 * */

void Math3D::findNormal(Vector3f result, const Vector3f p1, const Vector3f p2, const Vector3f p3){
    Vector3f v1, v2;
    // calculate two vectors from three points (counter clockwise winding)
    v1[0] = p1[0] - p2[0];
    v1[1] = p1[1] - p2[1];
    v1[2] = p1[2] - p2[2];
    v2[0] = p2[0] - p3[0];
    v2[1] = p2[1] - p3[1];
    v2[2] = p2[2] - p3[2];
    // take cross product of 2 vectors
    crossProduct(result,v1,v2);
}
void Math3D::findNormal(Vector3d result, const Vector3d p1, const Vector3d p2, const Vector3d p3){
    Vector3d v1, v2;
    // calculate two vectors from three points (counter clockwise winding)
    v1[0] = p1[0] - p2[0];
    v1[1] = p1[1] - p2[1];
    v1[2] = p1[2] - p2[2];
    v2[0] = p2[0] - p3[0];
    v2[1] = p2[1] - p3[1];
    v2[2] = p2[2] - p3[2];
    // take cross product of 2 vectors
    crossProduct(result,v1,v2);
}

float Math3D::getDistanceToPlane(const Vector3f point, const Vector4f plane){
    return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3];
}
double Math3D::getDistanceToPlane(const Vector3d point, const Vector4d plane){
    return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3];
}

void Math3D::getPlaneEquation(Vector4f planeEq, const Vector3f p1, const Vector3f p2, const Vector3f p3){
    // get two vectors and cross product them 
    Vector3f v1, v2;
    v1[0] = p1[0] - p2[0];
    v1[1] = p1[1] - p2[1];
    v1[2] = p1[2] - p2[2];
    v2[0] = p2[0] - p3[0];
    v2[1] = p2[1] - p3[1];
    v2[2] = p2[2] - p3[2];
    crossProduct(planeEq, v1, v2);
    normalizeVector(planeEq);
    // determine d
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}
void Math3D::getPlaneEquation(Vector4d planeEq, const Vector3d p1, const Vector3d p2, const Vector3d p3){
    // get two vectors and cross product them 
    Vector3d v1, v2;
    v1[0] = p1[0] - p2[0];
    v1[1] = p1[1] - p2[1];
    v1[2] = p1[2] - p2[2];
    v2[0] = p2[0] - p3[0];
    v2[1] = p2[1] - p3[1];
    v2[2] = p2[2] - p3[2];
    crossProduct(planeEq, v1, v2);
    normalizeVector(planeEq);
    // determine d
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}

float Math3D::raySphereTest(const Vector3f point, const Vector3f ray, const Vector3f sphereCenter, const float sphereRadius){
    // get ray to center
    Vector3f rayToCenter;
    rayToCenter[0] = sphereCenter[0] - point[0];
    rayToCenter[1] = sphereCenter[1] - point[1];
    rayToCenter[2] = sphereCenter[2] - point[2];
    // project rayToCenter on ray
    float a = dotProduct(rayToCenter, ray);
    // distance to center of sphere
    float distance = dotProduct(rayToCenter, rayToCenter);
    float dRet = (sphereRadius * sphereRadius) - distance + (a*a);
    if(dRet > 0.0) dRet = a - sqrt(dRet);
    return dRet;
}
double Math3D::raySphereTest(const Vector3d point, const Vector3d ray, const Vector3d sphereCenter, const double sphereRadius){
    // get ray to center
    Vector3d rayToCenter;
    rayToCenter[0] = sphereCenter[0] - point[0];
    rayToCenter[1] = sphereCenter[1] - point[1];
    rayToCenter[2] = sphereCenter[2] - point[2];
    // project rayToCenter on ray
    double a = dotProduct(rayToCenter, ray);
    // distance to center of sphere
    double distance = dotProduct(rayToCenter, rayToCenter);
    double dRet = (sphereRadius * sphereRadius) - distance + (a*a);
    if(dRet > 0.0) dRet = a - sqrt(dRet);
    return dRet;
}

void Math3D::projectXY(Vector2f out, const Matrix44f modelView, const Matrix44f projection, const int viewport[4], const Vector3f in){
    Vector4f back, forth;

    memcpy(back,in,sizeof(float)*3);
    back[3] = 1;

    transformVector4(forth, back, modelView);
    transformVector4(back, forth, projection);

    if(closeEnough(back[3], 0.0f, 0.000001f)){
        float div = 1 / back[3];
        back[0] *= div;
        back[1] *= div;
    }

    out[0] = float(viewport[0])+(1+back[0])*viewport[2]/2;
    out[1] = float(viewport[1])+(1+back[1])*viewport[3]/2;

    if(viewport[0] != 0) out[0] -= viewport[0];
    if(viewport[1] != 0) out[1] -= viewport[1];
}
void Math3D::projectXYZ(Vector3f out, const Matrix44f modelView, const Matrix44f projection, const int viewport[4], const Vector3f in){
    Vector4f back, forth;

    memcpy(back,in,sizeof(float)*3);
    back[3] = 1;

    transformVector4(forth, back, modelView);
    transformVector4(back, forth, projection);

    if(closeEnough(back[3], 0.0f, 0.000001f)){
        float div = 1 / back[3];
        back[0] *= div;
        back[1] *= div;
        back[2] *= div;
    }

    out[0] = float(viewport[0])+(1+back[0])*viewport[2]/2;
    out[1] = float(viewport[1])+(1+back[1])*viewport[3]/2;

    if(viewport[0] != 0) out[0] -= viewport[0];
    if(viewport[1] != 0) out[1] -= viewport[1];
    out[2] = back[2];
}

bool Math3D::closeEnough(const float candidate, const float compare, const float epsilon){
    return (fabs(candidate - compare) < epsilon);
}
bool Math3D::closeEnough(const double candidate, const double compare, const double epsilon){
    return (abs(candidate - compare) < epsilon);
}

void Math3D::catmullRom(Vector3f out, const Vector3f p0, const Vector3f p1, const Vector3f p2, const Vector3f p3, float t){
    float tt = t * t;
    float ttt = tt * t;

    out[0] = 0.5f * ( (2.0f * p1[0]) +
                      (-p0[0] + p2[0]) * t +
                      (2.0f * p0[0] - 5.0f * p1[0] + 4.0f * p2[0] - p3[0]) * tt +
                      (-p0[0] + 3.0f * p1[0] - 3.0f * p2[0] + p3[0]) * ttt);
    out[1] = 0.5f * ( (2.0f * p1[1]) +
                      (-p0[1] + p2[1]) * t +
                      (2.0f * p0[1] - 5.0f * p1[1] + 4.0f * p2[1] - p3[1]) * tt +
                      (-p0[1] + 3.0f * p1[1] - 3.0f * p2[1] + p3[1]) * ttt);
    out[2] = 0.5f * ( (2.0f * p1[2]) +
                      (-p0[2] + p2[2]) * t +
                      (2.0f * p0[2] - 5.0f * p1[2] + 4.0f * p2[2] - p3[2]) * tt +
                      (-p0[2] + 3.0f * p1[2] - 3.0f * p2[2] + p3[2]) * ttt);
}
void Math3D::catmullRom(Vector3d out, const Vector3d p0, const Vector3d p1, const Vector3d p2, const Vector3d p3, double t){
    double tt = t * t;
    double ttt = tt * t;

    out[0] = 0.5 * ( (2.0 * p1[0]) +
                      (-p0[0] + p2[0]) * t +
                      (2.0 * p0[0] - 5.0 * p1[0] + 4.0 * p2[0] - p3[0]) * tt +
                      (-p0[0] + 3.0 * p1[0] - 3.0 * p2[0] + p3[0]) * ttt);
    out[1] = 0.5 * ( (2.0 * p1[1]) +
                      (-p0[1] + p2[1]) * t +
                      (2.0 * p0[1] - 5.0 * p1[1] + 4.0 * p2[1] - p3[1]) * tt +
                      (-p0[1] + 3.0 * p1[1] - 3.0 * p2[1] + p3[1]) * ttt);
    out[2] = 0.5 * ( (2.0 * p1[2]) +
                      (-p0[2] + p2[2]) * t +
                      (2.0 * p0[2] - 5.0 * p1[2] + 4.0 * p2[2] - p3[2]) * tt +
                      (-p0[2] + 3.0 * p1[2] - 3.0 * p2[2] + p3[2]) * ttt);
}

void Math3D::calculateTangentBasis(Vector3f tangent, const Vector3f triangle[3], const Vector2f textCoords[3], const Vector3f n){
    Vector3f dv2v1, dv3v1;
    subtractVectors3(dv2v1, triangle[1], triangle[0]);
    subtractVectors3(dv3v1, triangle[2], triangle[0]);
    
    float dc2c1t, dc2c1b, dc3c1t, dc3c1b;
    dc2c1t = textCoords[1][0] - textCoords[0][0];
    dc2c1b = textCoords[1][1] - textCoords[0][1];
    dc3c1t = textCoords[2][0] - textCoords[0][0];
    dc3c1b = textCoords[2][1] - textCoords[0][1];

    float m = (dc2c1t * dc3c1b) - (dc3c1t * dc2c1b);
    m = 1.0f / m;

    scaleVector3(dv2v1, dc3c1b);
    scaleVector3(dv3v1, dc2c1b);

    subtractVectors3(tangent, dv2v1, dv3v1);
    scaleVector3(tangent, m); // can change direction of vector
    normalizeVector(tangent);

    Vector3f b;
    crossProduct(b, n, tangent);
    crossProduct(tangent, b, n);
    normalizeVector(tangent);
}

float Math3D::smoothStep(const float edge1, const float edge2, const float x){
    float t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1) t = 1;
    if(t < 0) t = 0;
    return t * t * (3 - 2 * t);
}
double Math3D::smoothStep(const double edge1, const double edge2, const double x){
    double t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1) t = 1;
    if(t < 0) t = 0;
    return t * t * (3 - 2 * t);
}

void Math3D::makePlanarShadowMatrix(Matrix44f proj, const Vector4f planeEq, const Vector3f lightPos){
    float a = planeEq[0];
    float b = planeEq[1];
    float c = planeEq[2];
    float d = planeEq[3];
    float dx = -lightPos[0];
    float dy = -lightPos[1];
    float dz = -lightPos[2];
    proj[0] = b * dy + c * dz;
    proj[1] = -a * dy;
    proj[2] = -a * dz;
    proj[3] = 0;

    proj[4] = -b * dx;
    proj[5] = a * dx + c * dz;
    proj[6] = -b * dz;
    proj[7] = 0;

    proj[8] = -c * dx;
    proj[9] = -c * dy;
    proj[10] = a * dx + b * dy;
    proj[11] = 0;

    proj[12] = -d * dx;
    proj[13] = -d * dy;
    proj[14] = -d * dz;
    proj[15] = a * dx + b * dy + c * dz;
}
void Math3D::makePlanarShadowMatrix(Matrix44d proj, const Vector4d planeEq, const Vector3d lightPos){
    double a = planeEq[0];
    double b = planeEq[1];
    double c = planeEq[2];
    double d = planeEq[3];
    double dx = -lightPos[0];
    double dy = -lightPos[1];
    double dz = -lightPos[2];
    proj[0] = b * dy + c * dz;
    proj[1] = -a * dy;
    proj[2] = -a * dz;
    proj[3] = 0;

    proj[4] = -b * dx;
    proj[5] = a * dx + c * dz;
    proj[6] = -b * dz;
    proj[7] = 0;

    proj[8] = -c * dx;
    proj[9] = -c * dy;
    proj[10] = a * dx + b * dy;
    proj[11] = 0;

    proj[12] = -d * dx;
    proj[13] = -d * dy;
    proj[14] = -d * dz;
    proj[15] = a * dx + b * dy + c * dz;
}

float Math3D::closestPointOnRay(Vector3f pointOnRay, const Vector3f rayOrigin, const Vector3f unitRayDirection, const Vector3f pointInSpace){
    Vector3f v;
    subtractVectors3(v, pointInSpace, rayOrigin);
    float t = dotProduct(unitRayDirection,v);
    pointOnRay[0] = rayOrigin[0] + (t * unitRayDirection[0]);
    pointOnRay[1] = rayOrigin[1] + (t * unitRayDirection[1]);
    pointOnRay[2] = rayOrigin[2] + (t * unitRayDirection[2]);
    return getDistanceSquared(pointOnRay, pointInSpace);
}
double Math3D::closestPointOnRay(Vector3d pointOnRay, const Vector3d rayOrigin, const Vector3d unitRayDirection, const Vector3d pointInSpace){
    Vector3d v;
    subtractVectors3(v, pointInSpace, rayOrigin);
    float t = dotProduct(unitRayDirection,v);
    pointOnRay[0] = rayOrigin[0] + (t * unitRayDirection[0]);
    pointOnRay[1] = rayOrigin[1] + (t * unitRayDirection[1]);
    pointOnRay[2] = rayOrigin[2] + (t * unitRayDirection[2]);
    return getDistanceSquared(pointOnRay, pointInSpace);
}
