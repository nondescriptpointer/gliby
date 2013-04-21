#pragma once

#include "Math3D.h"
#include "Frame.h"
#include <GL/glew.h>

namespace gliby {

enum MatrixStackError { STACK_NOERROR = 0, STACK_OVERFLOW, STACK_UNDERFLOW };

class MatrixStack {
    public:
        MatrixStack(int depth = 64);
        ~MatrixStack(void);
        void loadIdentity(void);
        void loadMatrix(const Math3D::Matrix44f m);
        void loadMatrix(Frame& frame);
        void multMatrix(const Math3D::Matrix44f m);
        void multMatrix(Frame& frame);
        void pushMatrix(void);
        void pushMatrix(const Math3D::Matrix44f m);
        void pushMatrix(Frame& frame);
        void popMatrix(void);
        void scale(GLfloat x, GLfloat y, GLfloat z);
        void translate(GLfloat x, GLfloat y, GLfloat z);
        void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
        void scale(const Math3D::Vector3f v);
        void translate(const Math3D::Vector3f v);
        void rotate(GLfloat angle, const Math3D::Vector3f axis);
        const Math3D::Matrix44f& getMatrix(void);
        void getMatrix(Math3D::Matrix44f m);
        MatrixStackError getLastError(void);
    protected:
        MatrixStackError lastError;
        int stackDepth;
        int stackPointer;
        Math3D::Matrix44f *pStack;
};

}
