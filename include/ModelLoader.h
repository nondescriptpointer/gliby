#pragma once

#include "Geometry.h"
#include <GL/glew.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>

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
        std::vector<Model*>* loadAll(const char* file);
    protected:
        Model* loadMesh(const aiMesh* mesh);
};

}
