#include "UIElement.h"
#include "TextureWindow.h"
#include "Math3D.h"
#include "GeometryFactory.h"
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace gliby;
using namespace Math3D;

UIElement::UIElement(const char* location, int width, int height, int x, int y, Matrix44f &screenSpace, int window_width, int window_height,  GLuint shader, bool transparent, bool debug):window(NULL),batch(NULL),over(false),w(width),h(height),xpos(x),ypos(y),window_w(window_width),window_h(window_height),shaderObj(shader) {
    // create a relative file:// url if url doesn't start with http://
    // TODO: this is horrible and will probably only work on linux
    const char* path = location;
    const char* http = "http://";
    char prefix[7];
    strncpy(prefix,location,7);
    if(strcmp(http,prefix) !=  0){
        char newstring[1024];
        // add file://
        strcpy(newstring,"file://");
        // add local path
        char buf[1024];
        readlink("/proc/self/exe",buf,1024);
        char *loc;
        loc = strrchr(buf,'/');
        char fullpath[1024];
        strncpy(fullpath,buf,loc-buf+1);
        strcat(newstring,fullpath);
        // add actual filename
        strcat(newstring,location);
        std::cout << newstring << std::endl;
        path = newstring;
    }
    // set up matrices
    projectionMatrix = &screenSpace;
    resize(window_w, window_h);
    // create texture window
    window = new TextureWindow(width,height,transparent,debug);
    window->clear();
    window->window()->focus();
    window->window()->navigateTo(path,strlen(path));
    // create batch
    batch = &GeometryFactory::overlay(float(width),float(height),0.0f,0.0f);
}
UIElement::~UIElement(){
    delete window;
    delete batch;
}

void UIElement::draw(){
    glUniform1i(glGetUniformLocation(shaderObj,"textureUnit"),0);
    glUniformMatrix4fv(glGetUniformLocation(shaderObj,"mvpMatrix"), 1, GL_FALSE, combinedMatrix);
    glBindTexture(GL_TEXTURE_2D, window->texture());
    batch->draw();
}
void UIElement::resize(int w, int h){
    window_w = w; window_h = h;
    // build a new transformation matrix
    translationMatrix(modelViewMatrix, (float)xpos, (float)window_h-(float)ypos, 0.0f);
    multiplyMatrix44(combinedMatrix, *projectionMatrix, modelViewMatrix);
}
void UIElement::mouseUpdate(int x, int y){
    mousex = x; mousey = y; 
    // check if mouse is within bounds
    if(mousex > xpos && mousex < xpos+w && mousey > ypos && mousey < ypos+h){
       over = true;
       window->window()->mouseMoved(mousex-xpos,mousey-ypos);
    }else{
        over = false;
    }
}
void UIElement::mouseEvent(int id, int state){
    if(over) window->window()->mouseButton(0,state);
}
void UIElement::charEvent(int character, int state){
    wchar_t c[2];
    c[0] = character;
    c[1] = 0;
    if(over) window->window()->textEvent(c,1);
}
void UIElement::keyEvent(int key, int state){
    
}
void UIElement::setX(int x){
    xpos = x;
}
void UIElement::setY(int y){
    ypos = y;
}
