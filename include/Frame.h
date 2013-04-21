#pragma once

#include "Math3D.h"

namespace gliby {

class Frame {
    public:
        Frame(void);
        // location
        void setOrigin(const Math3D::Vector3f point);
        void setOrigin(float x, float y, float z);
        void getOrigin(Math3D::Vector3f point);
        float getOriginX(void);
        float getOriginY(void);
        float getOriginZ(void);
        // forward direction
        void setForward(Math3D::Vector3f direction);
        void setForward(float x, float y, float z);
        void getForward(Math3D::Vector3f vector);
        // up direction
        void setUp(Math3D::Vector3f direction);
        void setUp(float x, float y, float z);
        void getUp(Math3D::Vector3f vector);
        // get axes
        void getXAxis(Math3D::Vector3f vector);
        void getYAxis(Math3D::Vector3f vector);
        void getZAxis(Math3D::Vector3f vector);
        // translate along orthonormal axis (world or local)
        void translateWorld(float x, float y, float z);
        void translateLocal(float x, float y, float z);
        // movement
        void moveForward(float delta);
        void moveUp(float delta);
        void moveRight(float delta);
        // assemble matrix
        void getMatrix(Math3D::Matrix44f matrix, bool rotationOnly = false);
        void getCameraMatrix(Math3D::Matrix44f matrix, bool rotationOnly = false);
        // rotate
        void rotateLocalY(float angle);
        void rotateLocalZ(float angle);
        void rotateLocalX(float angle);
        void rotateLocal(float angle, float x, float y, float z);
        void rotateWorld(float angle, float x, float y, float z);
        // convert coordinate systems
        void localToWorld(Math3D::Vector3f local, Math3D::Vector3f world, bool rotationOnly = false);
        void worldToLocal(const Math3D::Vector3f world, Math3D::Vector3f local);
        // transform a point by frame matrix
        void transformPoint(Math3D::Vector3f source, Math3D::Vector3f destination);
        // rotate a vector by frame matrix
        void rotateVector(Math3D::Vector3f source, Math3D::Vector3f destination);
        // reset axes to make sure they are orthonormal, should be called if matrix is long-lived and frequently transformed
        void normalize(void);
    protected:
        Math3D::Vector3f origin;
        Math3D::Vector3f forward;
        Math3D::Vector3f up;
};

}
