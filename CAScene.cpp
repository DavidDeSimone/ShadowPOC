//
//  CAScene.cpp
//  ShadowPOC
//
//  Created by David on 1/27/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAScene.h"
#include "CAPointLight.h"
#include "CACube.h"
#include "CAQuad.h"

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
    assert(clvec.size() <= 32);
    clvec.push_back(cl);
}

void scene::add(quad * q)
{
    qvec.push_back(q);
}

std::vector<point_light*>& scene::get_point_lights()
{
    return clvec;
}

std::vector<cube*>& scene::get()
{
    return cvec;
}

std::vector<quad*>& scene::get_quads()
{
    return qvec;
}

void scene::renderq(float dt) const
{
    for (auto q : qvec)
    {
        q->draw(dt);
    }
}

void scene::lighting_pass(float dt) const
{
    for (auto l : clvec)
    {
        l->draw(dt);
    }
    
}

void scene::render(float dt) const
{
    for (auto c : cvec)
    {
        c->draw();
    }

}