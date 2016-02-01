//
//  Header.h
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <string>
#include <stdlib.h>
class camera;
class scene;

camera get_default_camera();
scene& get_current_scene();

int get_width();
int get_height();

inline char* read_file_contents(const std::string& file_name)
{
    FILE *_file = fopen(file_name.c_str(), "r");
    size_t len;
    fseek(_file, 0, SEEK_END);
    len = ftell(_file);
    fseek(_file, 0, SEEK_SET);
    char *buffer = (char*)malloc(len + 1);
    fread(buffer, 1, len, _file);
    buffer[len] = '\0';
    fclose(_file);
    
    return buffer;
}




#endif /* Header_h */
