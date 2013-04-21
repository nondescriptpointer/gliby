#include "Math3D.h"

namespace gliby {

class Frustum {
    public:
        GLFrustum(void);
        GLFrustum(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
        GLFrustum(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax);
        
        const Matrix44f& getProjectionMatrix(void);

        void setOrthographic(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax);

        void setPerspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

        void transform(GLframe& camera);

        bool testSphere(float x, float y, float z, float radius);
        bool testSphere(Vector3f point, float radius);
    protected:
        Matrix44f projectionMatrix;
        // untransformed corners of the frustum
        Vector4f nearUL, nearLL, nearUR, nearLR;
        Vector4f farUL, farLL, farUR, farLR;
        // transformed corners of the frustum
        Vector4f nearULT, nearLLT, nearURT, nearLRT;
        Vector4f farULT, farLLT, farURT, farLRT;
        // base and transformed plane equations
        Vector4f nearPlane, farPlane, leftPlane, rightPlane;
        Vector4f topPlane, bottomPlane;
};

}
