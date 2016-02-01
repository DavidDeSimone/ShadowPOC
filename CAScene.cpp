//
//  CAScene.cpp
//  ShadowPOC
//
//  Created by David on 1/27/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAScene.h"
#include "CAPointLight.h"

scene::~scene()
{
    for (auto& c : cvec)
    {
        delete c;
    }
    
    for (auto& c : clvec)
    {
        delete c;
    }
}


void scene::add(cube * cb)
{
    cvec.push_back(cb);
}

void scene::add(point_light *cl)
{
    clvec.push_back(cl);
}

std::vector<point_light*>& scene::get_point_lights()
{
    return clvec;
}

std::vector<cube*>& scene::get()
{
    return cvec;
}