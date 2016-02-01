//
//  CAScene.hpp
//  ShadowPOC
//
//  Created by David on 1/27/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CAScene_hpp
#define CAScene_hpp

#include <stdio.h>
#include <vector>
#include "CACube.h"

class point_light;


class scene
{
public:
    scene() = default;
    ~scene();
    scene(scene&& mov) = delete;
    scene(const scene& cpy) = delete;
    
    std::vector<cube*>& get();
    std::vector<point_light*>& get_point_lights();
    void add(cube * cb);
    void add(point_light * cl);
    
private:
    std::vector<cube*> cvec;
    std::vector<point_light*> clvec;
};

#endif /* CAScene_hpp */
