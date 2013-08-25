#include "TextureManager.h"
#include <FreeImage.h>
#include <iostream>

using namespace gliby;

TextureManager::TextureManager(void){
    // get largest possible anisotropy value
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_anisotropy);
}

void TextureManager::loadTextures(int numTextures, const char** texts, GLenum target, GLenum unit){
    glActiveTexture(unit);
    for(int i = 0; i < numTextures; i++){
        GLuint tex;
        glGenTextures(1,&tex);
        glBindTexture(target, tex);
        // some good defaults, may change this later
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_anisotropy);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // detect file format
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texts[i],0);
        // load
        FIBITMAP* imagen = FreeImage_Load(format, texts[i]);
        // convert
        FIBITMAP* temp = imagen;
        imagen = FreeImage_ConvertTo32Bits(imagen);
        FreeImage_Unload(temp);
        int w = FreeImage_GetWidth(imagen);
        int h = FreeImage_GetHeight(imagen);
        // load into opengl
        char* pixels = (char*)FreeImage_GetBits(imagen);
        glTexImage2D(target,0,GL_RGBA,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,pixels);
        glGenerateMipmap(target);
        // clear data
        FreeImage_Unload(imagen);
        // store tex reference in map
        textures[texts[i]] = tex;
    }
}

GLuint TextureManager::get(const char* file){
    return textures[file];
}
