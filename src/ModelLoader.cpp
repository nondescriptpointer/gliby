#include "ModelLoader.h"
#include "Math3D.h"

#include <iostream>
#include <Math3D.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <vector>

// TODO: support for multiple texture coordinates
// TODO: support for more vertex attributes
// TODO: support for animations

using namespace std;
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
    const aiScene* scene = importer.ReadFile(file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if(!scene){
        std::cerr << "Model import of: " << file << " failed!" << std::endl;
        std::cerr << importer.GetErrorString() << std::endl;
        return NULL;
    }
    if(scene->mNumMeshes > 0){
        return loadMesh(scene->mMeshes[0]);
    }
    return NULL;
}

vector<Model*>* ModelLoader::loadAll(const char* file){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if(!scene){
        std::cerr << "Model import of: " << file << " failed!" << std::endl;
        std::cerr << importer.GetErrorString() << std::endl;
        return NULL;
    }
    if(scene->mNumMeshes > 0){
        vector<Model*>* vect = new vector<Model*>;
        for(unsigned int i = 0; i < scene->mNumMeshes; i++){
            Model* model = loadMesh(scene->mMeshes[i]);
            if(model) vect->push_back(model);
        }
        return vect;
    }
    return NULL;
}

Model* ModelLoader::loadMesh(const aiMesh* mesh){
    unsigned int nIndexes = mesh->mNumFaces*3;
    unsigned int nVerts = mesh->mNumVertices;
    
    GLushort indexes[mesh->mNumFaces*3];
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

    // fill indexes
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        indexes[i*3] = mesh->mFaces[i].mIndices[0];
        indexes[i*3+1] = mesh->mFaces[i].mIndices[1];
        indexes[i*3+2] = mesh->mFaces[i].mIndices[2];
    }

    // fill vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vector3f vert = {mesh->mVertices[i][0],mesh->mVertices[i][1],mesh->mVertices[i][2]};
        memcpy(verts[i], vert, sizeof(Vector3f));
        // normal
        if(mesh->HasNormals()){
            Vector3f normal = {mesh->mNormals[i][0],mesh->mNormals[i][1],mesh->mNormals[i][2]};
            memcpy(norms[i], normal, sizeof(Vector3f));
        }
        // texcoords
        if(mesh->HasTextureCoords(0)){
            Vector2f tex = {mesh->mTextureCoords[0][i][0],mesh->mTextureCoords[0][i][1]};
            memcpy(texcoords[i], tex, sizeof(Vector2f));
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

    //std::cout << "Num verts: " << nVerts << std::endl;
    //std::cout << "Num indexes: " << nIndexes << std::endl;

    Model* model = new Model(vertexArray,nIndexes);
    return model;
}
