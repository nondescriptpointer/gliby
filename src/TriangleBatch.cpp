#include "TriangleBatch.h"
#include <string.h>

using namespace gliby;
using namespace Math3D;

TriangleBatch::TriangleBatch(void):
    indexesArr(NULL), vertsArr(NULL), normsArr(NULL), texCoordsArr(NULL),
    nMaxIndexes(0), nNumIndexes(0), nNumVerts(0){
}

TriangleBatch::~TriangleBatch(void){
    delete [] indexesArr;
    delete [] vertsArr;
    delete [] normsArr;
    delete [] texCoordsArr;

    glDeleteBuffers(4, bufferObjects);
    glDeleteVertexArrays(1, &vertexArrayBufferObject);
}

void TriangleBatch::begin(GLuint nMaxVerts){
    delete [] indexesArr;
    delete [] vertsArr;
    delete [] normsArr;
    delete [] texCoordsArr;

    nMaxIndexes = nMaxVerts;
    nNumIndexes = 0;
    nNumVerts = 0;

    indexesArr = new GLushort[nMaxIndexes];
    vertsArr = new Vector3f[nMaxIndexes];
    normsArr = new Vector3f[nMaxIndexes];
    texCoordsArr = new Vector2f[nMaxIndexes];
}
void TriangleBatch::addTriangle(Vector3f verts[3], Vector3f norms[3], Vector2f texCoords[3]){
    const float e = 0.00001f; // difference to equate

    // normalize vectors
    for(int i = 0; i < 3; i++) normalizeVector(norms[i]);

    // search for match
    for(GLuint vertex = 0; vertex < 3; vertex++){
        GLuint match = 0;
        for(match = 0; match < nNumVerts; match++){
            // if vertex positions are the same
            if(closeEnough(vertsArr[match][0], verts[vertex][0], e) &&
               closeEnough(vertsArr[match][1], verts[vertex][1], e) &&
               closeEnough(vertsArr[match][2], verts[vertex][2], e) &&
               // and normals
               closeEnough(normsArr[match][0], norms[vertex][0], e) &&
               closeEnough(normsArr[match][1], norms[vertex][1], e) &&
               closeEnough(normsArr[match][2], norms[vertex][2], e) &&
               // and texCoords
               closeEnough(texCoordsArr[match][0], texCoords[vertex][0], e) &&
               closeEnough(texCoordsArr[match][1], texCoords[vertex][1], e) &&
               closeEnough(texCoordsArr[match][2], texCoords[vertex][2], e)){
                // add index only
                indexesArr[nNumIndexes] = match;
                nNumIndexes++;
                break;
            }
        }
        // no match, add
        if(match == nNumVerts && nNumVerts < nMaxIndexes && nNumIndexes < nMaxIndexes){
            memcpy(vertsArr[nNumVerts], verts[vertex], sizeof(Vector3f));
            memcpy(normsArr[nNumVerts], norms[vertex], sizeof(Vector3f));
            memcpy(texCoordsArr[nNumVerts], texCoords[vertex], sizeof(Vector2f));
            indexesArr[nNumIndexes] = nNumVerts;
            nNumIndexes++;
            nNumVerts++;
        }
    }
}
void TriangleBatch::end(void){
    glGenVertexArrays(1, &vertexArrayBufferObject);
    glBindVertexArray(vertexArrayBufferObject);

    glGenBuffers(4, bufferObjects);

    // copy data into video memory
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[0]);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nNumVerts*3, vertsArr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[1]);
    glEnableVertexAttribArray(2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nNumVerts*3, normsArr, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[2]);
    glEnableVertexAttribArray(3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nNumVerts*2, texCoordsArr, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*nNumIndexes, indexesArr, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete [] indexesArr; indexesArr = NULL;
    delete [] vertsArr; vertsArr = NULL;
    delete [] normsArr; normsArr = NULL;
    delete [] texCoordsArr; texCoordsArr = NULL;
}

void TriangleBatch::draw(void){
    glBindVertexArray(vertexArrayBufferObject);
    glDrawElements(GL_TRIANGLES, nNumIndexes, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
