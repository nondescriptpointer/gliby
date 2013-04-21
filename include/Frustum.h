#pragma once
#include <GL/glew.h>
#include "Math3D.h"
#include "Frame.h"

namespace gliby {

class Frustum {
    public:
        Frustum(void);
        Frustum(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
        Frustum(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax);
        
        const Math3D::Matrix44f& getProjectionMatrix(void);

        void setOrthographic(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax);

        void setPerspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

        void transform(gliby::Frame& camera);

        bool testSphere(float x, float y, float z, float radius);
        bool testSphere(Math3D::Vector3f point, float radius);
    protected:
        Math3D::Matrix44f projectionMatrix;
        // untransformed corners of the frustum
        Math3D::Vector4f nearUL, nearLL, nearUR, nearLR;
        Math3D::Vector4f farUL, farLL, farUR, farLR;
        // transformed corners of the frustum
        Math3D::Vector4f nearULT, nearLLT, nearURT, nearLRT;
        Math3D::Vector4f farULT, farLLT, farURT, farLRT;
        // base and transformed plane equations
        Math3D::Vector4f nearPlane, farPlane, leftPlane, rightPlane;
        Math3D::Vector4f topPlane, bottomPlane;
};

}
