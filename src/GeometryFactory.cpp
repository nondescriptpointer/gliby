#include "GeometryFactory.h"
#include "Batch.h"
#include "TriangleBatch.h"
#include "Math3D.h"
#include <string.h>

using namespace gliby;
using namespace Math3D;

TriangleBatch& GeometryFactory::sphere(GLfloat radius, GLint slices, GLint stacks){
    TriangleBatch* batch = new TriangleBatch();
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) stacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) slices;
	GLfloat ds = 1.0f / (GLfloat) slices;
	GLfloat dt = 1.0f / (GLfloat) stacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
    GLint i, j;

    batch->begin(slices * stacks * 6);
    for(i = 0; i < stacks; i++){
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

        s = 0.0f;
        Vector3f vVertex[4];
        Vector3f vNormal[4];
        Vector2f vTexture[4];

        for(j = 0; j < slices; j++){
			GLfloat theta = (j == slices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));
			
			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
        
			vTexture[0][0] = 1.0 - s;
			vTexture[0][1] = t;
			vNormal[0][0] = x;
			vNormal[0][1] = y;
			vNormal[0][2] = z;
			vVertex[0][0] = x * radius;
			vVertex[0][1] = y * radius;
			vVertex[0][2] = z * radius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[1][0] = 1.0 - s;
			vTexture[1][1] = t - dt;
			vNormal[1][0] = x;
			vNormal[1][1] = y;
			vNormal[1][2] = z;
			vVertex[1][0] = x * radius;
			vVertex[1][1] = y * radius;
			vVertex[1][2] = z * radius;
			

			theta = ((j+1) == slices) ? 0.0f : (j+1) * dtheta;
			stheta = (GLfloat)(-sin(theta));
			ctheta = (GLfloat)(cos(theta));
			
			x = stheta * srho;
			y = ctheta * srho;
			z = crho;
        
            s += ds;
			vTexture[2][0] = 1.0 - s;
			vTexture[2][1] = t;
			vNormal[2][0] = x;
			vNormal[2][1] = y;
			vNormal[2][2] = z;
			vVertex[2][0] = x * radius;
			vVertex[2][1] = y * radius;
			vVertex[2][2] = z * radius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[3][0] = 1.0 - s;
			vTexture[3][1] = t - dt;
			vNormal[3][0] = x;
			vNormal[3][1] = y;
			vNormal[3][2] = z;
			vVertex[3][0] = x * radius;
			vVertex[3][1] = y * radius;
			vVertex[3][2] = z * radius;

            batch->addTriangle(vVertex, vNormal, vTexture);

            // rearrange for next triangle
			memcpy(vVertex[0], vVertex[1], sizeof(Vector3f));
			memcpy(vNormal[0], vNormal[1], sizeof(Vector3f));
			memcpy(vTexture[0], vTexture[1], sizeof(Vector2f));
			memcpy(vVertex[1], vVertex[3], sizeof(Vector3f));
			memcpy(vNormal[1], vNormal[3], sizeof(Vector3f));
			memcpy(vTexture[1], vTexture[3], sizeof(Vector2f));

            batch->addTriangle(vVertex, vNormal, vTexture);
        }
        t -= dt;
    }
    batch->end();
    return *batch;
}

Batch& GeometryFactory::plane(GLfloat width, GLfloat height, GLfloat x, GLfloat y, GLfloat z){
    Batch* batch = new Batch();
    batch->begin(GL_TRIANGLE_FAN, 4, 1);
    GLfloat verts[] = {
        -width/2+x, height/2+y, z,
        -width/2+x, -height/2+y, z,
        width/2+x, -height/2+y, z,
        width/2+x, height/2+y, z
    };
    GLfloat texcoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    batch->copyVertexData3f(verts);
    batch->copyTexCoordData2f(texcoords,0);
    batch->end();
    return *batch;
}

Batch& GeometryFactory::cube(GLfloat size){
    Batch* batch = new Batch();
    batch->begin(GL_TRIANGLES, 36, 1);
    GLfloat verts[] = {
        // top
        size, size, size,
        size, size, -size,
        -size, size, -size,
        size, size, size,
        -size, size, -size,
        -size, size, size,
        // bottom
        -size, -size, -size,
        size, -size, -size,
        size, -size, size,
        -size, -size, size,
        -size, -size, -size,
        size, -size, size,
        // left
        -size, size, size,
        -size, size, -size,
        -size, -size, -size,
        -size, size, size,
        -size, -size, -size,
        -size, -size, size,
        // right
        size, -size, -size,
        size, size, -size,
        size, size, size,
        size, size, size,
        size, -size, size,
        size, -size, -size,
        // front
        size, -size, size,
        size, size, size,
        -size, size, size,
        -size, size, size,
        -size, -size, size,
        size, -size, size,
        // back
        size, -size, -size,
        -size, -size, -size,
        -size, size, -size,
        -size, size, -size,
        size, size, -size,
        size, -size, -size
    };
    GLfloat norms[] = {
        // top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        // bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
    };
    GLfloat texcoords[] = {
        // top
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        // bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        // left
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        // right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        // front
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        // back
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    batch->copyVertexData3f(verts);
    batch->copyTexCoordData2f(texcoords,0);
    batch->copyNormalDataf(norms);
    batch->end();
    return *batch;
}
