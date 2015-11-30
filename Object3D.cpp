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
    //Object material for amb, dif, spec, shiny
    float initMaterial[4] = {.5, .5, .5, 1};
    float initShiny[1] = {30};
    material[0] = initMaterial;//amb
    material[1] = initMaterial;//dif
    material[2] = initMaterial;//spec
    material[3] = initShiny;//shiny     caution: value of shiny should be converted from "float" to "int" if necessary
    
    //borrow the veteces position from slide week6 page 13 and use them as the frame position
    //but don't know if the vetex order is correct or not!!!!!!!!
    float boundVetx[8][3] = { {-0.5,-0.5,0.5},{-0.5,0.5,0.5}, {0.5,0.5,0.5},{0.5,-0.5,0.5},
                              {-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}, {0.5,0.5,-0.5},{0.5,-0.5,-0.5} };
}










