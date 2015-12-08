//
//  nodeMaterial.cpp
//  Ray
//
//  Created by Jinyue Song on 2015-12-01.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

#include "nodeMaterial.h"
#include <stdio.h> //needed for printf command
#include <time.h> //needed for random number
#include <stdlib.h>
#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#endif

using namespace std;

NodeMaterial::NodeMaterial(MaterialType whatType){
    nodeType = material;
    materialType = whatType;
    isDrawable = true;
}

void NodeMaterial::nodeSpecificCodeDown(){
    switch (materialType) {
        case CyanPlastic:
            float m_amb[4];
            float m_dif[4];
            float m_spec[4];
            float shiny;
            m_amb[0] = 0; m_amb[1] = 0.1; m_amb[2] = 0.06; m_amb[3] = 1;
            m_dif[0] = 0.0; m_dif[1] = 0.50980392; m_dif[2] = 0.50980392; m_dif[3] = 1;
            m_spec[0] = 0.50196078; m_spec[1] = 0.50196078; m_spec[2] = 0.50196078; m_spec[3] = 1;
            shiny = 32;
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
            
            break;
        
        case Gold:
            m_amb[0] = 0.24725; m_amb[1] = 0.1995; m_amb[2] = 0.0745; m_amb[3] = 1;
            m_dif[0] = 0.75164; m_dif[1] = 0.60648; m_dif[2] = 0.22648; m_dif[3] = 1;
            m_spec[0] = 0.628281; m_spec[1] = 0.555802; m_spec[2] = 0.366065; m_spec[3] = 1;
            shiny = 51.2;
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

            break;
        
        case Jade:
            m_amb[0] = 0.135; m_amb[1] = 0.2225; m_amb[2] = 0.1575; m_amb[3] = 1;
            m_dif[0] = 0.54; m_dif[1] = 0.89; m_dif[2] = 0.63; m_dif[3] = 1;
            m_spec[0] = 0.316228; m_spec[1] = 0.316228; m_spec[2] = 0.316228; m_spec[3] = 1;
            shiny = 12.8;

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

            break;
        
        case YellowRubber:
            m_amb[0] = 0.05; m_amb[1] = 0.05; m_amb[2] = 0.0; m_amb[3] = 1;
            m_dif[0] = 0.5; m_dif[1] = 0.5; m_dif[2] = 0.4; m_dif[3] = 1;
            m_spec[0] = 0.7; m_spec[1] = 0.7; m_spec[2] = 0.04; m_spec[3] = 1;
            shiny = 10;
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

            break;
        
        case Random:
            srand(time(NULL));
            m_amb[0] = (float)(double)rand()/((double)RAND_MAX+1); m_amb[1] = (float)(double)rand()/((double)RAND_MAX+1); m_amb[2] = (float)(double)rand()/((double)RAND_MAX+1); m_amb[3] = 1;
            m_dif[0] = (float)(double)rand()/((double)RAND_MAX+1); m_dif[1] = (float)(double)rand()/((double)RAND_MAX+1); m_dif[2] = (float)(double)rand()/((double)RAND_MAX+1); m_dif[3] = 1;
            m_spec[0] = (float)(double)rand()/((double)RAND_MAX+1); m_spec[1] = (float)(double)rand()/((double)RAND_MAX+1); m_spec[2] = (float)(double)rand()/((double)RAND_MAX+1); m_spec[3] = 1;
            shiny = 32;
            
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

            break;
        
        default:
            break;
    }
}

