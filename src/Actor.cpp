#include "Actor.h"
#include "Batch.h"

using namespace gliby;

Actor::Actor(Batch* geometry, GLuint text):batch(geometry),texture(text){
    // do nothing
}

Frame& Actor::getFrame(){
    return frame;
}
Batch& Actor::getGeometry(){
    return *batch;
}
GLuint Actor::getTexture(){
    return texture;
}
