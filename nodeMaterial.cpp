//
//  nodeMaterial.cpp
//  Ray
//
//  Created by Jinyue Song on 2015-12-01.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

#include "nodeMaterial.hpp"
#include <stdio.h> //needed for printf command
#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#endif

NodeMaterial::NodeMaterial(MaterialType whatType){
    nodeType = material;
    materialType = whatType;
    isDrawable = true;
}

void NodeMaterial::nodeSpecificCodeDown(){//not finished yet
    switch (materialType) {
        case Plastic:
            
            break;
        
        case Metal:
            break;
        
        case Paper:
            break;
        
        case Cotton:
            break;
        
        case Random:
            break;
        
        default:
            break;
    }
}