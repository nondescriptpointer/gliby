#pragma once

#include "Geometry.h"
#include <GL/glew.h>

namespace gliby {

class Model : public Geometry {
    public:
        Model(GLuint vertexArray, unsigned int nIndexes);
        virtual void draw(void);
    protected:
        GLuint _vertexArray;
        unsigned int _nIndexes;
};

class ModelLoader {
    public:
        ModelLoader(void);
        Model* load(const char* file);
    protected:
};

}
