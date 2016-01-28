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


class scene
{
public:
    scene() = default;
    ~scene();
    scene(scene&& mov) = delete;
    scene(const scene& cpy) = delete;
    
    std::vector<cube*>& get();
    void add(cube * cb);
    
private:
    std::vector<cube*> cvec;
};

#endif /* CAScene_hpp */
