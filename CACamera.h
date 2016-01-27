//
//  Camera.hpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "glm.hpp"
#include "CAUtil.h"


class camera
{
public:
    camera() :
    pos(0.0, 1.0, 3.0),
    front(0.0, 0.0, -1.0f),
    up(0.0, 1.0, 0.0),
    lastX(get_width() / 2),
    lastY(get_height() / 2),
    yaw(0),
    pitch(0)
    {};
    ~camera() = default;
    glm::vec3 front, up, pos;
    void update_pos(double x, double y);
    void update_mov(int key);
private:
    float yaw, pitch, roll;
    float lastX, lastY;
};

#endif /* Camera_hpp */
