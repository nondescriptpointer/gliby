#pragma once

#include "ShaderManager.h"
#include "Batch.h"
#include "Math3D.h"
#include "TransformPipeline.h"
#include "TriangleBatch.h"

namespace gliby {

class Grid {
    public:
        Grid(ShaderManager* shaderManager, float size, int subdiv);
        ~Grid();
        void draw(MatrixStack &modelViewMatrix, TransformPipeline &pipeline, const GLfloat* color);
    protected:
        GLuint gridProgram;
        Batch* gridBatch;
        TriangleBatch* coneBatch;
        float sz;
};

}
