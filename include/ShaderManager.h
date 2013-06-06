#pragma once
#include <vector>
#include <unordered_map>
#include <GL/glew.h>

namespace gliby {

struct ShaderAttribute {
    GLuint index;
    const char* name;
};

class ShaderManager {
    public:
        ShaderManager(std::vector<const char*>* search_path);
        ShaderManager(int num_search_path, const char** search_path);
        ~ShaderManager(void);

        GLuint buildShaderPair(const char* vertex_file, const char* fragment_file, const unsigned int nAttributes = 0, const ShaderAttribute* attributes = NULL);
    protected:
    private:
        GLuint buildShader(const char* shader_file,GLenum type); 

        int numSearchPath;
        const char** searchPath;
        std::unordered_map<const char*,GLuint> shaderCache;
};

}
