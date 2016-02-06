//
//  CARenderTexture2D.hpp
//  ShadowPOC
//
//  Created by David on 2/3/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CARenderTexture2D_hpp
#define CARenderTexture2D_hpp

#include <stdio.h>
#include "glew.h"

// TODO
class render_texture_2D
{
public:
    render_texture_2D();
    
private:
    GLuint FBO;
};

#endif /* CARenderTexture2D_hpp */
