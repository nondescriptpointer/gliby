#pragma once

namespace gliby {

class Geometry {
    public:
        virtual ~Geometry(void){};
        virtual void draw(void) = 0;
};

}
