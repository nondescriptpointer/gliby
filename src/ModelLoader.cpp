#include "ModelLoader.h"
#include "Math3D.h"

#include <iostream>
#include <Math3D.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>

// TODO: matching doesn't work
// TODO: texture coordinates not implemented yet

// TODO: support for multiple texture coordinates
// TODO: support for more vertex attributes
// TODO: support for animations

using namespace gliby;
using namespace Math3D;

Model::Model(GLuint vertexArray, unsigned int nIndexes):_vertexArray(vertexArray),_nIndexes(nIndexes){
    // pass
}
void Model::draw(void){
    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, _nIndexes, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}

ModelLoader::ModelLoader(void){
    // pass
}

Model* ModelLoader::load(const char* file){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file,aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if(!scene){
        std::cerr << "Model import of: " << file << " failed!" << std::endl;
        std::cerr << importer.GetErrorString() << std::endl;
        return NULL;
    }
    if(scene->mNumMeshes > 0){
        const aiMesh* mesh = scene->mMeshes[0];

        unsigned int nIndexes = 0;
        unsigned int nVerts = 0;
        const float e = 0.00001f; // vertex merge sensitivity
        
        GLushort indexes[mesh->mNumVertices];
        Vector3f verts[mesh->mNumVertices];
        Vector3f* norms = NULL;
        Vector2f* texcoords = NULL;
        int nBuffers = 2;
        if(mesh->HasNormals()){
            norms = new Vector3f[mesh->mNumVertices];
            nBuffers++;
        }
        if(mesh->HasTextureCoords(0)){
            texcoords = new Vector2f[mesh->mNumVertices];
            nBuffers++;
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++){
            for(unsigned int e = 0; e < mesh->mFaces[i].mNumIndices; e++){
                int index = mesh->mFaces[i].mIndices[e];
                std::cout << index << 
                // look for a match, if match found just add index
                bool matched = false;
                for(unsigned int match = 0; match < nVerts; match++){
                    matched = true;
                    if(!(closeEnough(verts[match][0], mesh->mVertices[index][0], e) && closeEnough(verts[match][1], mesh->mVertices[index][1], e) && closeEnough(verts[match][2], mesh->mVertices[index][2], e)))
                        matched = false;
                    if(matched){
                        std::cout << "matched" << std::endl;
                        indexes[nIndexes] = match;
                        nIndexes++;
                        break;
                    }
                }
                // no match, add vertex
                if(!matched && nVerts < mesh->mNumVertices && nIndexes < mesh->mNumVertices){
                    // vertex
                    Vector3f vert = {mesh->mVertices[index][0],mesh->mVertices[index][1],mesh->mVertices[index][2]};
                    memcpy(verts[nVerts], vert, sizeof(Vector3f));
                    // normal
                    if(mesh->HasNormals()){
                        Vector3f normal = {mesh->mNormals[index][0],mesh->mNormals[index][1],mesh->mNormals[index][2]};
                        memcpy(norms[nVerts], normal, sizeof(Vector3f));
                    }
                    // texcoords
                    if(mesh->HasTextureCoords(0)){
                        std::cout << "texcoords" << std::endl;
                        std::cout << mesh->mTextureCoords[index][0][0] << std::endl;
                    }
                    // index
                    indexes[nIndexes] = nVerts;
                    nIndexes++;
                    nVerts++;
                }
            }
        }

        GLuint vertexArray;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);
        
        GLuint buffers[nBuffers];
        int bufferindex = 0;
        glGenBuffers(nBuffers,buffers);
        // indexes
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[bufferindex]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*nIndexes, indexes, GL_STATIC_DRAW);
        bufferindex++;
        // vertices
        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferindex]);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nVerts*3, verts, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        bufferindex++;
        // normals
        if(mesh->HasNormals()){
            glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferindex]);
            glEnableVertexAttribArray(2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nVerts*3, norms, GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            bufferindex++;
        }
        // texcoords
        if(mesh->HasTextureCoords(0)){
            glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferindex]);
            glEnableVertexAttribArray(3);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nVerts*2, texcoords, GL_STATIC_DRAW);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
            bufferindex++;
        }
        glBindVertexArray(0);

        std::cout << "Num verts: " << nVerts << std::endl;
        std::cout << "Num indexes: " << nIndexes << std::endl;

        Model* model = new Model(vertexArray,nIndexes);
        return model;
    }
    return NULL;
}
