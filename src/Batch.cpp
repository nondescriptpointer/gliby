#include "Batch.h"
#include <iostream>

using namespace Math3D;
using namespace gliby;

Batch::Batch(void): 
    vertexArray(0), normalArray(0), colorArray(0), texCoordArray(NULL), vertexArrayObject(0), 
    nNumVerts(0), nNumTextureUnits(0), done(false) {

}

Batch::~Batch(void){
    // cleanup gl buffer objects
    if(vertexArray != 0) glDeleteBuffers(1, &vertexArray);
    if(normalArray != 0) glDeleteBuffers(1, &normalArray);
    if(colorArray != 0) glDeleteBuffers(1, &colorArray);
    for(unsigned int i = 0; i < nNumTextureUnits; i++)
        glDeleteBuffers(1, &texCoordArray[i]);
    glDeleteVertexArrays(1, &vertexArrayObject); 
    delete [] texCoordArray;
}

// start & end batch
void Batch::begin(GLenum primitive, GLuint nVerts, GLuint nTextureUnits){
    primitiveType = primitive;
    nNumVerts = nVerts;
    nNumTextureUnits = nTextureUnits;

    if(nNumTextureUnits != 0){
        texCoordArray = new GLuint[nNumTextureUnits];
        for(unsigned int i = 0; i < nNumTextureUnits; i++){
            texCoordArray[i] = 0;
        }
    }

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
}
void Batch::end(void){
    // set up the vertex array object
    glBindVertexArray(vertexArrayObject);

    if(vertexArray != 0){
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    if(colorArray != 0){
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorArray);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }
    if(normalArray != 0){
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalArray);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    for(unsigned int i = 0; i < nNumTextureUnits; i++){
        if(texCoordArray[i] != 0){
            glEnableVertexAttribArray(3 + i);
            glBindBuffer(GL_ARRAY_BUFFER, texCoordArray[i]);
            glVertexAttribPointer(3 + i, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }
    }

    done = true;

    glBindVertexArray(0);
}

// block copy in vertex data
void Batch::copyVertexData3f(Vector3f *verts_){
    if(vertexArray == 0){
        glGenBuffers(1, &vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, verts_, GL_DYNAMIC_DRAW);
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * nNumVerts, verts_);
    }
}
void Batch::copyVertexData3f(GLfloat *verts_){
    copyVertexData3f((Vector3f *)(verts_));
}
void Batch::copyNormalDataf(Vector3f *normals_){
    if(normalArray == 0){
        glGenBuffers(1, &normalArray);
        glBindBuffer(GL_ARRAY_BUFFER, normalArray);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, normals_, GL_DYNAMIC_DRAW);
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, normalArray);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * nNumVerts, normals_);
    }
}
void Batch::copyNormalDataf(GLfloat *normals_){
    copyNormalDataf((Vector3f *)(normals_));
}
void Batch::copyColorData4f(Vector4f *colors_){
    if(colorArray == 0){
        glGenBuffers(1, &colorArray);
        glBindBuffer(GL_ARRAY_BUFFER, colorArray);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * nNumVerts, colors_, GL_DYNAMIC_DRAW);
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, colorArray);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * nNumVerts, colors_); 
    }
}
void Batch::copyColorData4f(GLfloat *colors_){
    copyColorData4f((Vector4f *)(colors_));
}
void Batch::copyTexCoordData2f(Vector2f *texCoords_, GLuint texture){
    if(texCoordArray[texture] == 0){
        glGenBuffers(1, &texCoordArray[texture]);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordArray[texture]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nNumVerts, texCoords_, GL_DYNAMIC_DRAW);
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, texCoordArray[texture]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * nNumVerts, texCoords_);
    }
}
void Batch::copyTexCoordData2f(GLfloat *texCoords_, GLuint texture){
    copyTexCoordData2f((Vector2f *)(texCoords_),texture);
}

void Batch::draw(void){
    if(!done) return;

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(primitiveType, 0, nNumVerts);
    glBindVertexArray(0);
}

void Batch::reset(void){
    done = false;
}
