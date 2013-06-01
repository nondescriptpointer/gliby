#pragma once

#include <map>
#include <string>
#include <GL/glew.h>

namespace gliby {

class UniformManager {
    public:
        UniformManager(GLuint shader, int num, const char** uniform);
        int get(const char* str);
    protected:
        std::map<std::string, int> locs;
};

}
