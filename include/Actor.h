#pragma once

#include <GL/glew.h>
#include "Batch.h"
#include "Frame.h"

namespace gliby {

class Actor {
    public:
        Actor(Batch* geometry, GLuint text = 0);
        Frame& getFrame();
        Batch& getGeometry();
        GLuint getTexture();
    protected:
        Batch* batch;
        GLuint texture;
        Frame frame;
};

}
