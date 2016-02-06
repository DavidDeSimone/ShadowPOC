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

class point_light;
class cube;
class quad;

class scene
{
public:
    scene() = default;
    ~scene();
    scene(scene&& mov) = delete;
    scene(const scene& cpy) = delete;
    
    std::vector<cube*>& get();
    std::vector<point_light*>& get_point_lights();
    std::vector<quad*>& get_quads();
    void add(cube * cb);
    void add(point_light * cl);
    void add(quad * q);
    
    void render(float dt) const;
    void lighting_pass(float dt) const;
    void renderq(float dt) const;
    
private:
    std::vector<cube*> cvec;
    std::vector<point_light*> clvec;
    std::vector<quad*> qvec;
};

#endif /* CAScene_hpp */
