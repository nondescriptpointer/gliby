#pragma once

#include <GL/glew.h>
#include "Geometry.h"
#include "Frame.h"

namespace gliby {

class Actor {
    public:
        Actor(Geometry* geometry, GLuint text = 0);
        Frame& getFrame();
        Geometry& getGeometry();
        GLuint getTexture();
    protected:
        Geometry* geom;
        GLuint texture;
        Frame frame;
};

}
