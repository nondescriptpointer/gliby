#pragma once

#include "TextureWindow.h"
#include "Batch.h"
#include "Math3D.h"
#include <string>

namespace gliby {

class UIElement {
    public:
        UIElement(const char* location, int width, int height, int x, int y, Math3D::Matrix44f &screenSpace, GLuint shader, bool transparent = true, bool debug = false);
        ~UIElement();
        void resize(int w, int h);
        void mouseUpdate(int x, int y);
        void mouseEvent(int id, int state);
        void charEvent(int character, int state);
        void keyEvent(int key, int state); 
        void draw();
    protected:
        TextureWindow* window;
        Batch* batch;
        bool over;
        int xpos;
        int ypos;
        Math3D::Matrix44f *projectionMatrix;
        GLuint shaderObj;
};

}
