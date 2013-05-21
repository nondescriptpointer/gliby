#pragma once

#include "ShaderManager.h"
#include "Batch.h"
#include "Math3D.h"

namespace gliby {

class Grid {
    public:
        Grid(ShaderManager* shaderManager, float size, int subdiv);
        ~Grid();
        void draw(const Math3D::Matrix44f mvpMatrix, const GLfloat* color);
    protected:
        GLuint gridProgram;
        Batch* gridBatch;
};

}
