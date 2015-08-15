#pragma once

#include <map>
#include <GL/glew.h>

namespace gliby {

class TextureManager {
    public:
        TextureManager(void);
        void loadTextures(int numTextures, const char** texts, GLenum target, GLenum unit);
        GLuint get(const char* file);
    protected:
        std::map<std::string, GLuint> textures;
        GLfloat largest_anisotropy;
};

}
