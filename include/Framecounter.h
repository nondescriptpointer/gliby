#pragma once

#include <GL/glfw.h>

namespace gliby {

class Framecounter {
    public:
        Framecounter(void);
        bool tick(void);
        unsigned int getFramerate(void);
    protected:
        unsigned int frame;
        unsigned long second;
        unsigned int frameRate;
};

}
