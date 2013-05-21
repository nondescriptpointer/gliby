#pragma once

#include "TriangleBatch.h"
#include "Batch.h"

namespace gliby {

class GeometryFactory {
    public:
        static TriangleBatch& sphere(GLfloat radius, GLint slices, GLint stacks);
        static Batch& plane(GLfloat width, GLfloat height, GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0);
        static Batch& grid(GLfloat size, GLint subdivs);
        static Batch& overlay(GLfloat width, GLfloat height, GLfloat x = 0, GLfloat y = 0);
        static Batch& cube(GLfloat size);
        static TriangleBatch& cylinder(GLfloat baseRadius, GLfloat topRadius, GLfloat length, GLint slices, GLint stacks);
};

}
