//
//  CATexture2D.hpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CATexture2D_hpp
#define CATexture2D_hpp

#include <stdio.h>
#include <map>
#include "glew.h"

struct texture_count
{
    GLuint texture;
    size_t count;
};

class texture_2D
{
public:
    texture_2D(const char * name);
    ~texture_2D();
    GLuint texture;
    
private:
    static std::map<std::string, texture_count> texture_cache;
};

#endif /* CATexture2D_hpp */
