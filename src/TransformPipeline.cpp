#include "TransformPipeline.h"
#include "Math3D.h"
#include "MatrixStack.h"

using namespace gliby;
using namespace Math3D;

TransformPipeline::TransformPipeline(void){}

void TransformPipeline::setModelViewMatrixStack(MatrixStack& modelView){
    modelViewStack = &modelView;
}
void TransformPipeline::setProjectionMatrixStack(MatrixStack& projection){
    projectionStack = &projection;
}
void TransformPipeline::setMatrixStacks(MatrixStack& modelView, MatrixStack& projection){
    modelViewStack = &modelView;
    projectionStack = &projection;
}

const Matrix44f& TransformPipeline::getModelViewProjectionMatrix(void){
    multiplyMatrix44(modelViewProjection, projectionStack->getMatrix(), modelViewStack->getMatrix());
    return modelViewProjection;
}
const Matrix44f& TransformPipeline::getModelViewMatrix(void){
    return modelViewStack->getMatrix();
}
const Matrix44f& TransformPipeline::getProjectionMatrix(void){
    return projectionStack->getMatrix();
}
const Matrix33f& TransformPipeline::getNormalMatrix(bool normalize){
    extractRotationMatrix(normal, getModelViewMatrix());
    if(normalize){
        normalizeVector(&normal[0]);
        normalizeVector(&normal[3]);
        normalizeVector(&normal[6]);
    }
    return normal;
}
