#include "MatrixStack.h"
#include "Math3D.h"
#include "Frame.h"
#include <string.h>
#include <GL/glew.h>

using namespace gliby;
using namespace Math3D;

MatrixStack::MatrixStack(int depth){
    stackDepth = depth;
    pStack = new Matrix44f[stackDepth];
    stackPointer = 0;
    loadIdentity44(pStack[0]);
    lastError = STACK_NOERROR; 
}
MatrixStack::~MatrixStack(void){ delete [] pStack; }

void MatrixStack::loadIdentity(void){
    loadIdentity44(pStack[stackPointer]);
}
void MatrixStack::loadMatrix(const Matrix44f m){
    memcpy(pStack[stackPointer], m, sizeof(Matrix44f));
}
void MatrixStack::loadMatrix(Frame& frame){
    Matrix44f m;
    frame.getMatrix(m);
    loadMatrix(m);
}

void MatrixStack::multMatrix(const Matrix44f m){
    Matrix44f temp;
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, m);
}
void MatrixStack::multMatrix(Frame& frame){
    Matrix44f m;
    frame.getMatrix(m);
    multMatrix(m);
}

void MatrixStack::pushMatrix(void){
    if(stackPointer < stackDepth){
        stackPointer++;
        memcpy(pStack[stackPointer], pStack[stackPointer-1], sizeof(Matrix44f));
    }else{
        lastError = STACK_OVERFLOW;
    }
}
void MatrixStack::pushMatrix(const Matrix44f m){
    if(stackPointer < stackDepth){
        stackPointer++;
        memcpy(pStack[stackPointer], m, sizeof(Matrix44f));
    }else{
        lastError = STACK_OVERFLOW;
    }
}
void MatrixStack::pushMatrix(Frame& frame){
    Matrix44f m;
    frame.getMatrix(m);
    pushMatrix(m);
}

void MatrixStack::popMatrix(void){
    if(stackPointer > 0){
        stackPointer--; 
    }else{
        lastError = STACK_UNDERFLOW;
    }
}

void MatrixStack::scale(GLfloat x, GLfloat y, GLfloat z){
    Matrix44f temp, sc;
    scaleMatrix44(sc, x, y, z);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, sc);
}
void MatrixStack::translate(GLfloat x, GLfloat y, GLfloat z){
    Matrix44f temp, tr;
    translationMatrix(tr, x, y, z);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, tr);
}
void MatrixStack::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){
    Matrix44f temp, rot;
    rotationMatrix44(rot, float(degToRad(angle)), x, y, z);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, rot);
}
void MatrixStack::scale(const Vector3f v){
    Matrix44f temp, sc;
    scaleMatrix44(sc, v);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, sc);
}
void MatrixStack::translate(const Vector3f v){
    Matrix44f temp, tr;
    loadIdentity44(tr);
    setMatrixColumn44(tr, v, 3);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, tr);
}
void MatrixStack::rotate(GLfloat angle, const Vector3f v){
    Matrix44f temp, rot;
    rotationMatrix44(rot, float(degToRad(angle)), v[0], v[1], v[2]);
    memcpy(temp, pStack[stackPointer], sizeof(Matrix44f));
    multiplyMatrix44(pStack[stackPointer], temp, rot);
}

const Matrix44f& MatrixStack::getMatrix(void){
    return pStack[stackPointer];
}
void MatrixStack::getMatrix(Matrix44f m){
    memcpy(m, pStack[stackPointer], sizeof(Matrix44f));
}

MatrixStackError MatrixStack::getLastError(void){
    MatrixStackError ret = lastError;
    lastError = STACK_NOERROR;
    return ret;
}
