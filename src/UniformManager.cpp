#include "UniformManager.h"
#include <GL/glew.h>

using namespace gliby;

UniformManager::UniformManager(GLuint shader, int num, const char** uniform){
    for(int i = 0; i < num; i++){
        locs[uniform[i]] = glGetUniformLocation(shader,uniform[i]);
    }
}

int UniformManager::get(const char* str){
    return locs[str];
}
