#pragma once

#include <GL/glew.h>
#include "Math3D.h"
#include "Geometry.h"

namespace gliby {

class Batch : public Geometry {
    public:
        Batch(void);
        ~Batch(void);

        // start & end batch
        void begin(GLenum primitive, GLuint nVerts, GLuint nTextureUnits = 0);
        void end(void);

        // block copy in vertex data
        void copyVertexData3f(Math3D::Vector3f *verts_);
        void copyVertexData3f(GLfloat *verts_);
        void copyNormalDataf(Math3D::Vector3f *normals_);
        void copyNormalDataf(GLfloat *normals_);
        void copyColorData4f(Math3D::Vector4f *colors_);
        void copyColorData4f(GLfloat *colors_);
        void copyTexCoordData2f(Math3D::Vector2f *texCoords_, GLuint texture);
        void copyTexCoordData2f(GLfloat *texCoords_, GLuint texture);
        
        // draw
        virtual void draw(void);

        void reset(void);

    protected:
        // opengl buffer objects
        GLenum primitiveType;
        GLuint vertexArray;
        GLuint normalArray;
        GLuint colorArray;
        GLuint *texCoordArray;
        GLuint vertexArrayObject;

        // counters
        GLuint nNumVerts;
        GLuint nNumTextureUnits;

        bool done;
};

}
