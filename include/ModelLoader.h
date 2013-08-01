#pragma once

#include "Geometry.h"
#include <GL/glew.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include "Math3D.h"

namespace gliby {

class Material {
    public:
        Material(const char* name);
        void setColorDiffuse(float r, float g, float b);
        Math3D::Vector3f* getColorDiffuse(void);
        void setColorSpecular(float r, float g, float b);
        Math3D::Vector3f* getColorSpecular(void);
        void setColorAmbient(float r, float g, float b);
        Math3D::Vector3f* getColorAmbient(void);
        void setColorEmissive(float r, float g, float b);
        Math3D::Vector3f* getColorEmissive(void);
        void setColorTransparent(float r, float g, float b);
        Math3D::Vector3f* getColorTransparent(void);
        void setWireframe(bool wireframe);
        bool getWireframe(void);
        void setTwoSided(bool twoSided);
        bool getTwoSided(void);
        void setShininess(float shininess);
        float getShininess(void);
        void setShininessStrength(float shininessStrength);
        float getShininessStrength(void);
        void setOpacity(float opacity);
        float getOpacity(void);
        void setTextureDiffuse(const char* textureDiffuse);
        const char* getTextureDiffuse(void);
        void setTextureSpecular(const char* textureSpecular);
        const char* getTextureSpecular(void);
        void setTextureOpacity(const char* textureOpacity);
        const char* getTextureOpacity(void);
        void setTextureNormal(const char* textureNormal);
        const char* getTextureNormal(void);
    protected:
        const char* _name;
        Math3D::Vector3f _colorDiffuse;
        Math3D::Vector3f _colorSpecular;
        Math3D::Vector3f _colorAmbient;
        Math3D::Vector3f _colorEmissive;
        Math3D::Vector3f _colorTransparent;
        bool _wireframe;
        bool _twoSided;
        float _shininess;
        float _shininessStrength;
        float _opacity;
        const char* _textureDiffuse;
        const char* _textureSpecular;
        const char* _textureOpacity;
        const char* _textureNormal;
};

class Model : public Geometry {
    public:
        Model(GLuint vertexArray, unsigned int nIndexes);
        virtual void draw(void);
        void setMaterial(Material* material);
        Material* getMaterial();
    protected:
        GLuint _vertexArray;
        unsigned int _nIndexes;
        Material* _material;
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
