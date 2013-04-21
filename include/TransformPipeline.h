#pragma once

#include "Math3D.h"
#include "MatrixStack.h"

namespace gliby {

class TransformPipeline {
    public:
        TransformPipeline(void);
        void setModelViewMatrixStack(MatrixStack& modelView);
        void setProjectionMatrixStack(MatrixStack& projection);
        void setMatrixStacks(MatrixStack& modelView, MatrixStack& projection);
        const Math3D::Matrix44f& getModelViewProjectionMatrix(void);
        const Math3D::Matrix44f& getModelViewMatrix(void);
        const Math3D::Matrix44f& getProjectionMatrix(void);
        const Math3D::Matrix33f& getNormalMatrix(bool normalize = false);
    protected:
        Math3D::Matrix44f modelViewProjection;
        Math3D::Matrix33f normal;
        MatrixStack* modelViewStack;
        MatrixStack* projectionStack;
};

}
