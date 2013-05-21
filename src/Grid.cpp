#include "Grid.h"
#include "ShaderManager.h"
#include "GeometryFactory.h"
#include "Batch.h"

using namespace gliby;
using namespace Math3D;

Grid::Grid(ShaderManager* shaderManager, float size, int subdivs){
    // build the shader
    ShaderAttribute attrs[] = {{0,"vVertex"}};
    gridProgram = shaderManager->buildShaderPair("flatcolor_perspective.vp","flatcolor_perspective.fp",sizeof(attrs)/sizeof(ShaderAttribute),attrs);
    // set up geometry
    gridBatch = &GeometryFactory::grid(size,subdivs);
}
Grid::~Grid(){
    delete gridBatch;
}

void Grid::draw(const Matrix44f mvpMatrix, const GLfloat* color){
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.5f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(gridProgram);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, mvpMatrix); // TODO: cache the uniform location
    //GLfloat color[] = {1.0f,0.0f,0.0f,1.0f};
    glUniform4fv(glGetUniformLocation(gridProgram,"vColor"), 1, color);
    gridBatch->draw();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}
