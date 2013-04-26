#pragma once

#include <GL/glew.h>
#include "Math3D.h"
#include "Geometry.h"

namespace gliby {

class TriangleBatch : public Geometry {
    public:
        TriangleBatch(void);
        ~TriangleBatch(void);

        void begin(GLuint nMaxVerts);
        void addTriangle(Math3D::Vector3f verts[3], Math3D::Vector3f norms[3], Math3D::Vector2f texCoords[3]);
        void end(void);

        virtual void draw(void);
    protected:
        GLushort *indexesArr;
        Math3D::Vector3f *vertsArr;
        Math3D::Vector3f *normsArr;
        Math3D::Vector2f *texCoordsArr;
        
        GLuint nMaxIndexes;
        GLuint nNumIndexes;
        GLuint nNumVerts;

        GLuint bufferObjects[4];
        GLuint vertexArrayBufferObject;
};

}
