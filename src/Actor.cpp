#include "Actor.h"
#include "Batch.h"

using namespace gliby;

Actor::Actor(Geometry* geometry, GLuint text):geom(geometry),texture(text){
    // do nothing
}

Frame& Actor::getFrame(){
    return frame;
}
Geometry& Actor::getGeometry(){
    return *geom;
}
GLuint Actor::getTexture(){
    return texture;
}
