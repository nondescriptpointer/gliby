#include "Grid.h"
#include "ShaderManager.h"
#include "GeometryFactory.h"
#include "Batch.h"
#include "TransformPipeline.h"
#include "TriangleBatch.h"

using namespace gliby;
using namespace Math3D;

Grid::Grid(ShaderManager* shaderManager, float size, int subdivs):sz(size){
    // build the shader
    ShaderAttribute attrs[] = {{0,"vVertex"}};
    gridProgram = shaderManager->buildShaderPair("flatcolor_perspective.vp","flatcolor_perspective.fp",sizeof(attrs)/sizeof(ShaderAttribute),attrs);
    // set up geometry
    gridBatch = &GeometryFactory::grid(size,subdivs);
    coneBatch = &GeometryFactory::cylinder(size/30,0.0f,size/10,20,1);
}
Grid::~Grid(){
    delete gridBatch;
}

void Grid::draw(MatrixStack &modelViewMatrix, TransformPipeline &pipeline, const GLfloat* color){
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.5f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(gridProgram);
    glUniform4fv(glGetUniformLocation(gridProgram,"vColor"), 1, color);

    Matrix44f mat;

    // draw grids
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    gridBatch->draw();

    modelViewMatrix.pushMatrix();
    rotationMatrix44(mat,PI/2,1.0f,0.0f,0.0f);
    modelViewMatrix.multMatrix(mat);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    gridBatch->draw();
    modelViewMatrix.popMatrix();

    modelViewMatrix.pushMatrix();
    rotationMatrix44(mat,PI/2,0.0f,1.0f,0.0f);
    modelViewMatrix.multMatrix(mat);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    gridBatch->draw();
    modelViewMatrix.popMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // draw cones
    // z?
    modelViewMatrix.pushMatrix();
    translationMatrix(mat,0,0,sz/2); 
    modelViewMatrix.multMatrix(mat);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    modelViewMatrix.popMatrix();
    GLfloat blue[] = {0.0f,0.0f,1.0f,1.0f};
    glUniform4fv(glGetUniformLocation(gridProgram,"vColor"), 1, blue);
    coneBatch->draw();

    // x
    modelViewMatrix.pushMatrix();
    translationMatrix(mat,sz/2,0,0); 
    modelViewMatrix.multMatrix(mat);
    rotationMatrix44(mat,PI/2,0.0f,1.0f,0.0f);
    modelViewMatrix.multMatrix(mat);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    modelViewMatrix.popMatrix();
    GLfloat red[] = {1.0f,0.0f,0.0f,1.0f};
    glUniform4fv(glGetUniformLocation(gridProgram,"vColor"), 1, red);
    coneBatch->draw();

    // y
    modelViewMatrix.pushMatrix();
    translationMatrix(mat,0,sz/2,0); 
    modelViewMatrix.multMatrix(mat);
    rotationMatrix44(mat,PI/2,-1.0f,0.0f,0.0f);
    modelViewMatrix.multMatrix(mat);
    glUniformMatrix4fv(glGetUniformLocation(gridProgram,"mvpMatrix"), 1, GL_FALSE, pipeline.getModelViewProjectionMatrix()); // TODO: cache the uniform location
    modelViewMatrix.popMatrix();
    GLfloat green[] = {0.0f,1.0f,0.0f,1.0f};
    glUniform4fv(glGetUniformLocation(gridProgram,"vColor"), 1, green);
    coneBatch->draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}
