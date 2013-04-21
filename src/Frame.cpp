#include "Frame.h"
#include <string.h>
#include "Math3D.h"

using namespace Math3D;
using namespace gliby;

Frame::Frame(void){
    origin[0] = 0.0f; origin[1] = 0.0f; origin[2] = 0.0f;
    up[0] = 0.0f; up[1] = 1.0f; up[2] = 0.0f;
    forward[0] = 0.0f; forward[1] = 0.0f; forward[2] = -1.0f;
}

void Frame::setOrigin(const Vector3f point){ memcpy(origin,point,sizeof(Vector3f)); }
void Frame::setOrigin(float x, float y, float z){ origin[0] = x; origin[1] = y; origin[2] = z; }
void Frame::getOrigin(Vector3f point){ memcpy(point,origin,sizeof(Vector3f)); }
float Frame::getOriginX(void){ return origin[0]; }
float Frame::getOriginY(void){ return origin[1]; }
float Frame::getOriginZ(void){ return origin[2]; }

void Frame::setForward(Vector3f direction){ memcpy(forward, direction, sizeof(Vector3f)); }
void Frame::setForward(float x, float y, float z){ origin[0] = x; origin[1] = y; origin[2] = z; }
void Frame::getForward(Vector3f vector){ memcpy(vector, forward, sizeof(Vector3f)); }

void Frame::setUp(Vector3f direction){ memcpy(up, direction, sizeof(Vector3f)); }
void Frame::setUp(float x, float y, float z){ up[0] = x; up[1] = y; up[2] = z; }
void Frame::getUp(Vector3f vector){ memcpy(vector, up, sizeof(Vector3f)); }

void Frame::getXAxis(Vector3f vector){ crossProduct(vector, up, forward); }
void Frame::getYAxis(Vector3f vector){ getUp(vector); }
void Frame::getZAxis(Vector3f vector){ getForward(vector); }

void Frame::translateWorld(float x, float y, float z){ origin[0] += 0; origin[1] += y; origin[2] += z; }
void Frame::translateLocal(float x, float y, float z){ moveForward(z); moveUp(y); moveRight(x); }

void Frame::moveForward(float delta){
    origin[0] += forward[0] * delta;
    origin[1] += forward[1] * delta;
    origin[2] += forward[2] * delta;
}
void Frame::moveUp(float delta){
    origin[0] += up[0] * delta;
    origin[1] += up[1] * delta;
    origin[2] += up[2] * delta;
}
void Frame::moveRight(float delta){
    Vector3f cross;
    crossProduct(cross, up, forward);
    origin[0] += cross[0] * delta;
    origin[1] += cross[1] * delta;
    origin[2] += cross[2] * delta;
}

void Frame::getMatrix(Matrix44f matrix, bool rotationOnly){
    // calculate right side (x) vector, drop it into the matrix
    Vector3f xAxis;
    crossProduct(xAxis, up, forward);
    setMatrixColumn44(matrix, xAxis, 0);
    matrix[3] = 0.0f;
    // y
    setMatrixColumn44(matrix, up, 1);
    // z
    setMatrixColumn44(matrix, forward, 2);
    // translation
    if(rotationOnly){
        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
    }else{
        setMatrixColumn44(matrix, origin, 3);
    }
    matrix[15] = 1.0f;
}
void Frame::getCameraMatrix(Matrix44f matrix, bool rotationOnly){
    Vector3f x, z;
    z[0] = -forward[0]; z[1] = -forward[1]; z[2] = -forward[2];
    crossProduct(x, up, z);
    // Matrix has no translation information and is
    // transposed.... (rows instead of columns)
    #define M(row,col)  matrix[col*4+row]
        M(0, 0) = x[0];
        M(0, 1) = x[1];
        M(0, 2) = x[2];
        M(0, 3) = 0.0;
        M(1, 0) = up[0];
        M(1, 1) = up[1];
        M(1, 2) = up[2];
        M(1, 3) = 0.0;
        M(2, 0) = z[0];
        M(2, 1) = z[1];
        M(2, 2) = z[2];
        M(2, 3) = 0.0;
        M(3, 0) = 0.0;
        M(3, 1) = 0.0;
        M(3, 2) = 0.0;
        M(3, 3) = 1.0;
    #undef M
    if(rotationOnly) return;
    // translation
    Matrix44f trans, result;
    translationMatrix(trans, -origin[0], -origin[1], -origin[2]);
    multiplyMatrix44(result, matrix, trans);
    memcpy(matrix, result, sizeof(float)*16);
}

void Frame::rotateLocalY(float angle){
    Matrix44f m;
    rotationMatrix44(m, angle, up[0], up[1], up[2]);
    Vector3f v;
    v[0] = m[0] * forward[0] + m[4] * forward[1] + m[8] * forward[2];
    v[1] = m[1] * forward[0] + m[5] * forward[1] + m[9] * forward[2];
    v[2] = m[2] * forward[0] + m[6] * forward[1] + m[10] * forward[2];
    memcpy(forward, v, sizeof(Vector3f));
}
void Frame::rotateLocalZ(float angle){
    Matrix44f m;
    rotationMatrix44(m, angle, forward[0], forward[1], forward[2]);
    Vector3f v;
    v[0] = m[0] * up[0] + m[4] * up[1] + m[8] * up[2];
    v[1] = m[1] * up[0] + m[5] * up[1] + m[9] * up[2];
    v[2] = m[2] * up[0] + m[6] * up[1] + m[10] * up[2];
    memcpy(forward, v, sizeof(Vector3f));
}
void Frame::rotateLocalX(float angle){
    Matrix33f m;
    Vector3f localX;
    Vector3f rotVec;
    crossProduct(localX, up, forward);
    rotationMatrix33(m, angle, localX[0], localX[1], localX[2]);
    Math3D::rotateVector(rotVec, up, m);
    memcpy(up, rotVec, sizeof(Vector3f));
    Math3D::rotateVector(rotVec, forward, m);
    memcpy(forward, rotVec, sizeof(Vector3f));
}

void Frame::rotateWorld(float angle, float x, float y, float z){
    Matrix44f m;
    rotationMatrix44(m, angle, x, y, z);
    Vector3f v;
    v[0] = m[0] * up[0] + m[4] * up[1] + m[8] * up[2];
    v[1] = m[1] * up[0] + m[5] * up[1] + m[9] * up[2];
    v[2] = m[2] * up[0] + m[6] * up[1] + m[10] * up[2];
    memcpy(up, v, sizeof(Vector3f));
    v[0] = m[0] * forward[0] + m[4] * forward[1] + m[8] * forward[2];
    v[1] = m[1] * forward[0] + m[5] * forward[1] + m[9] * forward[2];
    v[2] = m[2] * forward[0] + m[6] * forward[1] + m[10] * forward[2];
    memcpy(forward, v, sizeof(Vector3f));
}
void Frame::rotateLocal(float angle, float x, float y, float z){
    Vector3f worldVect;
    Vector3f localVect;
    localVect[0] = x; localVect[1] = y; localVect[2] = z;
    localToWorld(localVect,worldVect,true);
    rotateWorld(angle, worldVect[0], worldVect[1], worldVect[2]);
}

void Frame::localToWorld(Vector3f local, Vector3f world, bool rotationOnly){
    // create rotation matrix
    Matrix44f m;
    getMatrix(m,true);
    // do rotation
    world[0] = m[0] * local[0] + m[4] * local[1] + m[8] * local[2];
    world[1] = m[1] * local[0] + m[5] * local[1] + m[9] * local[2];
    world[2] = m[2] * local[0] + m[6] * local[1] + m[10] * local[2];
    // translate
    if(!rotationOnly){
        world[0] += origin[0];
        world[1] += origin[1];
        world[2] += origin[2];
    }
}
void Frame::worldToLocal(const Vector3f world, Vector3f local){
    // translate origin
    Vector3f newWorld;
    newWorld[0] = world[0] - origin[0];
    newWorld[1] = world[1] - origin[1];
    newWorld[2] = world[2] - origin[2];
    // create rotation matrix
    Matrix44f rotMat;
    Matrix44f invMat;
    getMatrix(rotMat, true);
    invertMatrix44(invMat, rotMat);
    local[0] = invMat[0] * newWorld[0] + invMat[4] * newWorld[1] + invMat[8] * newWorld[2];
    local[1] = invMat[1] * newWorld[0] + invMat[5] * newWorld[1] + invMat[9] * newWorld[2];
    local[2] = invMat[2] * newWorld[0] + invMat[6] * newWorld[1] + invMat[10] * newWorld[2];
}

void Frame::transformPoint(Vector3f source, Vector3f destination){
    Matrix44f m;
    getMatrix(m, false);
    destination[0] = m[0] * source[0] + m[4] * source[1] + m[8] * source[2] + m[12];
    destination[0] = m[1] * source[0] + m[5] * source[1] + m[9] * source[2] + m[13];
    destination[0] = m[2] * source[0] + m[6] * source[1] + m[10] * source[2] + m[14];
}

void Frame::rotateVector(Vector3f source, Vector3f destination){
    Matrix44f m;
    getMatrix(m, true);
    destination[0] = m[0] * source[0] + m[4] * source[1] + m[8] * source[2];
    destination[0] = m[1] * source[0] + m[5] * source[1] + m[9] * source[2];
    destination[0] = m[2] * source[0] + m[6] * source[1] + m[10] * source[2];
}

void Frame::normalize(){
    Vector3f cross;
    crossProduct(cross, up, forward);
    crossProduct(forward, cross, up);
    normalizeVector(up);
    normalizeVector(forward);
}
