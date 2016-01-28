//
//  CAScene.cpp
//  ShadowPOC
//
//  Created by David on 1/27/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAScene.h"

scene::~scene()
{
    for (auto& c : cvec)
    {
        delete c;
    }
}


void scene::add(cube * cb)
{
    cvec.push_back(cb);
}

std::vector<cube*>& scene::get()
{
    return cvec;
}