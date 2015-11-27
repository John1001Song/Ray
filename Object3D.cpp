//
//  Object3D.cpp
//  Ray
//
//  Created by Jinyue Song on 2015-11-26.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

#include <stdio.h>
#include "Object3D.h"

//Constructor
Object3D::Object3D(){
    //inital position is (0, 0, 0)
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;
    
    //inital orientation (1, 0, 0)
    orient[0] = 1;
    orient[1] = 0;
    orient[2] = 0;
    
    //inital scale is (1, 1, 1)
    scale[0] = 1;
    scale[1] = 1;
    scale[2] = 1;
    
    //inital material all half value
    float initMaterial[4] = {.5, .5, .5, 1};
    material[0] = initMaterial;
//    material[0] = new float[4];
}










