#include "Frustum.h"
#include <string.h>
#include "Frame.h"
#include "Math3D.h"

using namespace gliby;
using namespace Math3D;

Frustum::Frustum(void){ setOrthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); }
Frustum::Frustum(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far){
    setPerspective(fov, aspect, near, far);
}
Frustum::Frustum(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax){
    setOrthographic(xmin, xmax, ymin, ymax, zmin, zmax);
}

const Matrix44f& Frustum::getProjectionMatrix(void){
    return projectionMatrix;
}

void Frustum::setOrthographic(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax){
    makeOrthographicMatrix(projectionMatrix, xmin, xmax, ymin, ymax, zmin, zmax);
    projectionMatrix[15] = 1.0f;

    // values for untransformed frustum corners
    nearUL[0] = xmin; nearUL[1] = ymax; nearUL[2] = zmin; nearUL[3] = 1.0f;
    nearLL[0] = xmin; nearLL[1] = ymin; nearLL[2] = zmin; nearLL[3] = 1.0f;
    nearUR[0] = xmax; nearUR[1] = ymax; nearUR[2] = zmin; nearUR[3] = 1.0f;
    nearLR[0] = xmax; nearLR[1] = ymin; nearLR[2] = zmin; nearLR[3] = 1.0f;
    farUL[0] = xmin; farUL[1] = ymax; farUL[2] = zmax; farUL[3] = 1.0f;
    farLL[0] = xmin; farLL[1] = ymin; farLL[2] = zmax; farLL[3] = 1.0f;
    farUR[0] = xmax; farUR[1] = ymax; farUR[2] = zmax; farUR[3] = 1.0f;
    farLR[0] = xmax; farLR[1] = ymin; farLR[2] = zmax; farLR[3] = 1.0f;
}

void Frustum::setPerspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far){
    float nxmin, nxmax, nymin, nymax; // dimensions of near clipping plane;
    float fxmin, fxmax, fymin, fymax; // dimensions of far clipping plane;

    // near clipping plane
    nymax = near * float(tan(fov * PI / 360.0));
    nymin = -nymax;
    nxmin = nymin * aspect;
    nxmax = -nxmin;

    // construct projection matrix
    loadIdentity44(projectionMatrix);
    projectionMatrix[0] = (2.0f * near)/(nxmax - nxmin);
    projectionMatrix[5] = (2.0f * near)/(nymax - nymin);
    projectionMatrix[8] = (nxmax + nxmin) / (nxmax - nxmin);
    projectionMatrix[9] = (nymax + nymin) / (nymax - nymin);
    projectionMatrix[10] = -((far + near) / (far - near));
    projectionMatrix[11] = -1.0f;
    projectionMatrix[14] = -((2.0f * far * near)/(far - near));
    projectionMatrix[15] = 0.0f;

    // do the math for the far clipping plane
    fymax = far * float(tan(fov * PI / 360.0));
    fymin = -fymax;
    fxmin = fymin * aspect;
    fxmax = -fxmin;

    // values for transformed frustum corners
    nearUL[0] = nxmin; nearUL[1] = nymax; nearUL[2] = -near; nearUL[3] = 1.0f;
    nearLL[0] = nxmin; nearLL[1] = nymin; nearLL[2] = -near; nearLL[3] = 1.0f;
    nearUR[0] = nxmax; nearUR[1] = nymax; nearUR[2] = -near; nearUR[3] = 1.0f;
    nearLR[0] = nxmax; nearLR[1] = nymin; nearLR[2] = -near; nearLR[3] = 1.0f;
    farUL[0] = fxmin; farUL[1] = fymax; farUL[2] = -far; farUL[3] = 1.0f;
    farLL[0] = fxmin; farLL[1] = fymin; farLL[2] = -far; farLL[3] = 1.0f;
    farUR[0] = fxmax; farUR[1] = fymax; farUR[2] = -far; farUR[3] = 1.0f;
    farLR[0] = fxmax; farLR[1] = fymin; farLR[2] = -far; farLR[3] = 1.0f;
}

void Frustum::transform(Frame& camera){
    Matrix44f rotMat;
    Vector3f forward, up, cross;
    Vector3f origin;

    // create the transformation matrix
    camera.getForward(forward);
    // flip the forward vector
    forward[0] = -forward[0];
    forward[1] = -forward[1];
    forward[2] = -forward[2];
    // get other vectors
    camera.getUp(up);
    camera.getOrigin(origin);
    crossProduct(cross, up, forward);

    // matrix building
    memcpy(rotMat, cross, sizeof(float)*3);
    rotMat[3] = 0.0f;
    memcpy(&rotMat[4], up, sizeof(float)*3);
    rotMat[7] = 0.0f;
    memcpy(&rotMat[8], forward, sizeof(float)*3);
    rotMat[11] = 0.0f;
    rotMat[12] = origin[0];
    rotMat[13] = origin[1];
    rotMat[14] = origin[2];
    rotMat[15] = 1.0f;

    // transform the frustum corners
    transformVector4(nearULT, nearUL, rotMat);
    transformVector4(nearLLT, nearLL, rotMat);
    transformVector4(nearURT, nearUR, rotMat);
    transformVector4(nearLRT, nearLR, rotMat);
    transformVector4(farULT, farUL, rotMat);
    transformVector4(farLLT, farLL, rotMat);
    transformVector4(farURT, farUR, rotMat);
    transformVector4(farLRT, farLR, rotMat);

    // derive plane equations
    getPlaneEquation(nearPlane, nearULT, nearLLT, nearLRT);
    getPlaneEquation(farPlane, farULT, farURT, farLRT);
    getPlaneEquation(topPlane, nearULT, nearURT, farURT);
    getPlaneEquation(bottomPlane, nearLLT, farLLT, farLRT);
    getPlaneEquation(leftPlane, nearLLT, nearULT, farULT);
    getPlaneEquation(rightPlane, nearLRT, farLRT, farURT);
}

bool Frustum::testSphere(float x, float y, float z, float radius){
    Vector3f point; point[0] = x; point[1] = y; point[2] = z;
    return testSphere(point, radius);
}

bool Frustum::testSphere(Vector3f point, float radius){
    float dist;
    dist = getDistanceToPlane(point, nearPlane);
    if(dist + radius <= 0.0) return false;
    dist = getDistanceToPlane(point, farPlane);
    if(dist + radius <= 0.0) return false;
    dist = getDistanceToPlane(point, leftPlane);
    if(dist + radius <= 0.0) return false;
    dist = getDistanceToPlane(point, rightPlane);
    if(dist + radius <= 0.0) return false;
    dist = getDistanceToPlane(point, bottomPlane);
    if(dist + radius <= 0.0) return false;
    dist = getDistanceToPlane(point, topPlane);
    if(dist + radius <= 0.0) return false;
    return true;
}
