#include "UIElement.h"
#include "TextureWindow.h"
#include "Math3D.h"
#include "GeometryFactory.h"
#include <string.h>

using namespace gliby;
using namespace Math3D;

UIElement::UIElement(const char* location, int width, int height, int x, int y, Matrix44f &screenSpace, GLuint shader, bool transparent, bool debug):window(NULL),batch(NULL),over(false),xpos(x),ypos(y),shaderObj(shader) {
    projectionMatrix = &screenSpace;
    // create texture window
    window = new TextureWindow(width,height,transparent,debug);
    window->clear();
    window->window()->navigateTo(location,strlen(location));
    // create batch
    batch = &GeometryFactory::overlay(float(width),float(height),10.0f,210.0f);
}
UIElement::~UIElement(){
    delete window;
    delete batch;
}

void UIElement::draw(){
    glUniform1i(glGetUniformLocation(shaderObj,"textureUnit"),0);
    glUniformMatrix4fv(glGetUniformLocation(shaderObj,"mvpMatrix"), 1, GL_FALSE, *projectionMatrix);
    glBindTexture(GL_TEXTURE_2D, window->texture());
    batch->draw();
}
void UIElement::resize(int w, int h){

}
void UIElement::mouseUpdate(int x, int y){

}
void UIElement::mouseEvent(int id, int state){

}
void UIElement::charEvent(int character, int state){

}
void UIElement::keyEvent(int key, int state){

}
