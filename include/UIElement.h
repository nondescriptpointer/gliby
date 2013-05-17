#pragma once

#include "TextureWindow.h"
#include "Batch.h"
#include "Math3D.h"
#include <string>

namespace gliby {

class UIElement {
    public:
        UIElement(const char* location, int width, int height, int x, int y, Math3D::Matrix44f &screenSpace, int window_width, int window_height, GLuint shader, bool transparent = true, bool debug = false);
        ~UIElement();
        void resize(int w, int h);
        void mouseUpdate(int x, int y);
        void mouseEvent(int id, int state);
        void charEvent(int character, int state);
        void keyEvent(int key, int state, bool shift_down = false, bool ctrl_down = false, bool alt_down = false); 
        void draw();
        void setX(int x);
        void setY(int y);
    protected:
        TextureWindow* window;
        Batch* batch;
        bool over;
        int w;
        int h;
        int xpos;
        int ypos;
        int window_w;
        int window_h;
        int mousex;
        int mousey;
        Math3D::Matrix44f *projectionMatrix;
        Math3D::Matrix44f modelViewMatrix;
        Math3D::Matrix44f combinedMatrix;
        GLuint shaderObj;
};

}
