#pragma once

#include "TriangleBatch.h"

namespace gliby {

class GeometryFactory {
    public:
        static TriangleBatch& sphere(GLfloat radius, GLint slices, GLint stacks);
};

}
