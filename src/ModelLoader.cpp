#include "ModelLoader.h"
#include "Math3D.h"
#include "TextureManager.h"

#include <iostream>
#include <Math3D.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <vector>
#include <unordered_set>
#include <string>

// TODO: support for multiple texture coordinates
// TODO: support for more vertex attributes
// TODO: support for animations
// TODO: figure out a way to clean up loaded stuff
// TODO: maybe add loading of following material properties: shading_model, blend_func, refrection index, bumbscaling, reflectivity
// TODO: there are more advanced things to do with textures like supporting multiple textures, having different mappings/uv's,blend factors, mapping modes etc.

using namespace std;
using namespace gliby;
using namespace Math3D;

/*
 * MATERIAL
 * */

Material::Material(const char* name):
    _colorDiffuse{0.0f,0.0f,0.0f},
    _colorSpecular{0.0f,0.0f,0.0f},
    _colorAmbient{0.0f,0.0f,0.0f},
    _colorEmissive{0.0f,0.0f,0.0f},
    _colorTransparent{0.0f,0.0f,0.0f},
    _wireframe(false),
    _twoSided(false),
    _shininess(0.0f),
    _shininessStrength(1.0f),
    _opacity(1.0f),
    _textureDiffuse(NULL),
    _textureSpecular(NULL),
    _textureOpacity(NULL),
    _textureNormal(NULL)
    {
    _name = strdup(name);
}
void Material::setColorDiffuse(float r, float g, float b){ _colorDiffuse[0] = r; _colorDiffuse[1] = g; _colorDiffuse[2] = b; }
Vector3f* Material::getColorDiffuse(void){ return &_colorDiffuse; }
void Material::setColorSpecular(float r, float g, float b){ _colorSpecular[0] = r; _colorSpecular[1] = g; _colorSpecular[2] = b; }
Vector3f* Material::getColorSpecular(void){ return &_colorSpecular; }
void Material::setColorAmbient(float r, float g, float b){ _colorAmbient[0] = r; _colorAmbient[1] = g; _colorAmbient[2] = b; }
Vector3f* Material::getColorAmbient(void){ return &_colorAmbient; }
void Material::setColorEmissive(float r, float g, float b){ _colorEmissive[0] = r; _colorEmissive[1] = g; _colorEmissive[2] = b; }
Vector3f* Material::getColorEmissive(void){ return &_colorEmissive; }
void Material::setColorTransparent(float r, float g, float b){ _colorTransparent[0] = r; _colorTransparent[1] = g; _colorTransparent[2] = b; }
Vector3f* Material::getColorTransparent(void){ return &_colorTransparent; }
void Material::setWireframe(bool wireframe){ _wireframe = wireframe; }
bool Material::getWireframe(void){ return _wireframe; }
void Material::setTwoSided(bool twoSided){ _twoSided = twoSided; }
bool Material::getTwoSided(void){ return _twoSided; }
void Material::setShininess(float shininess){ _shininess = shininess; }
float Material::getShininess(void){ return _shininess; }
void Material::setShininessStrength(float shininessStrength){ _shininessStrength = shininessStrength; }
float Material::getShininessStrength(void){ return _shininessStrength; }
void Material::setOpacity(float opacity){ _opacity = opacity; }
float Material::getOpacity(void){ return _opacity; }
void Material::setTextureDiffuse(const char* textureDiffuse){ 
    string str(textureDiffuse);
    replace(str.begin(),str.end(),'\\','/');
    _textureDiffuse = str.c_str();
}
const char* Material::getTextureDiffuse(void){ return _textureDiffuse; }
void Material::setTextureSpecular(const char* textureSpecular){ 
    string str(textureSpecular);
    replace(str.begin(),str.end(),'\\','/');
    _textureSpecular = str.c_str();
}
const char* Material::getTextureSpecular(void){ return _textureSpecular; }
void Material::setTextureOpacity(const char* textureOpacity){ 
    string str(textureOpacity);
    replace(str.begin(),str.end(),'\\','/');
    _textureOpacity = str.c_str();
}
const char* Material::getTextureOpacity(void){ return _textureOpacity; }
void Material::setTextureNormal(const char* textureNormal){ 
    string str(textureNormal);
    replace(str.begin(),str.end(),'\\','/');
    _textureNormal = str.c_str();
} 
const char* Material::getTextureNormal(void){ return _textureNormal; }

/*
 * MODEL
 * */

Model::Model(GLuint vertexArray, unsigned int nIndexes):_vertexArray(vertexArray),_nIndexes(nIndexes),_material(NULL){
    // pass
}
void Model::draw(void){
    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, _nIndexes, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
void Model::setMaterial(Material* material){
    _material = material;
}
Material* Model::getMaterial(){
    return _material;
}

/*
 * LOADER
 */

ModelLoader::ModelLoader(TextureManager* textureManager):_textureManager(textureManager){
    // pass
}

Model* ModelLoader::load(const char* file){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenNormals);
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
    // load the scene
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenNormals);
    if(!scene){
        std::cerr << "Model import of: " << file << " failed!" << std::endl;
        std::cerr << importer.GetErrorString() << std::endl;
        return NULL;
    }
    // create all the materials
    Material** mats = new Material*[scene->mNumMaterials];
    unordered_set<string> texfiles;
    for(unsigned int i = 0; i < scene->mNumMaterials; i++){
        aiMaterial* mat = scene->mMaterials[i];
        // create instance
        aiString name;
        mat->Get(AI_MATKEY_NAME,name);
        mats[i] = new Material(name.C_Str());
        // assign colors if available
        aiColor3D color;
        if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE,color)) mats[i]->setColorDiffuse(color[0],color[1],color[2]);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_SPECULAR,color)) mats[i]->setColorSpecular(color[0],color[1],color[2]);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_AMBIENT,color)) mats[i]->setColorAmbient(color[0],color[1],color[2]);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_EMISSIVE,color)) mats[i]->setColorEmissive(color[0],color[1],color[2]);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_TRANSPARENT,color)) mats[i]->setColorTransparent(color[0],color[1],color[2]);
        // some bools
        int attr;
        if(AI_SUCCESS == mat->Get(AI_MATKEY_ENABLE_WIREFRAME,attr)) mats[i]->setWireframe(attr > 0);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_TWOSIDED,attr)) mats[i]->setTwoSided(attr > 0);
        // some floats
        float fl;
        if(AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS,fl)) mats[i]->setShininess(fl);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS_STRENGTH,fl)) mats[i]->setShininessStrength(fl);
        if(AI_SUCCESS == mat->Get(AI_MATKEY_OPACITY,fl)) mats[i]->setOpacity(fl);
        // get the textures
        aiString path;
        if(AI_SUCCESS == mat->GetTexture(aiTextureType_DIFFUSE,0,&path)){
            mats[i]->setTextureDiffuse(path.C_Str());
            texfiles.insert(string(mats[i]->getTextureDiffuse()));
        }
        if(AI_SUCCESS == mat->GetTexture(aiTextureType_SPECULAR,0,&path)){
            mats[i]->setTextureSpecular(path.C_Str());
            texfiles.insert(string(mats[i]->getTextureSpecular()));
        }
        if(AI_SUCCESS == mat->GetTexture(aiTextureType_OPACITY,0,&path)){
            mats[i]->setTextureOpacity(path.C_Str());
            texfiles.insert(string(mats[i]->getTextureOpacity()));
        }
        if(AI_SUCCESS == mat->GetTexture(aiTextureType_NORMALS,0,&path)){ 
            mats[i]->setTextureNormal(path.C_Str());
            texfiles.insert(string(mats[i]->getTextureNormal()));
        }
    }
    // load all the textures that are being used by materials
    if(_textureManager){
        const char* textures[texfiles.size()];
        int i = 0;
        for(unordered_set<string>::iterator it = texfiles.begin(); it != texfiles.end(); ++it){
            textures[i] = (*it).c_str();
            i++;
        }
        _textureManager->loadTextures(sizeof(textures)/sizeof(char*),textures,GL_TEXTURE_2D,GL_TEXTURE0);
    }
    // create all the meshes and return
    if(scene->mNumMeshes > 0){
        vector<Model*>* vect = new vector<Model*>;
        for(unsigned int i = 0; i < scene->mNumMeshes; i++){
            Model* model = loadMesh(scene->mMeshes[i]);
            model->setMaterial(mats[scene->mMeshes[i]->mMaterialIndex]);
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
