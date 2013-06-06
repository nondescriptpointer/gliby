#include "Framecounter.h"

using namespace gliby;

Framecounter::Framecounter(void):frame(0),frameRate(0){
    second = (int)glfwGetTime();
}

bool Framecounter::tick(void){
    frame++;
    unsigned int time = (unsigned int)glfwGetTime();
    if(time > second){
        frameRate = frame;
        frame = 0;
        second = time;
        return true;
    }
    return false;
}

unsigned int Framecounter::getFramerate(void){
    return frameRate;
}
