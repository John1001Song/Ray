#include "NodeModel.h"
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
#include "node.h"

NodeModel::NodeModel(ModelType whatType){	//constructor
    nodeType = model;
    modelType = whatType;
    isDrawable = true;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
    glPushMatrix();
}
/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
    glBegin(GL_POLYGON);
        glVertex3fv(v[a]);
        glVertex3fv(v[b]);
        glVertex3fv(v[c]);
        glVertex3fv(v[d]);
    glEnd();
}

/* cube - takes an array of 8 vertices, and draws 6 faces
 *  with drawPolygon, making up a box
 */
void cube(float v[8][3])
{
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(0, 3, 2, 1, v);
    glDisable(GL_POLYGON_OFFSET_LINE);

    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(1, 0, 4, 5, v);
    glDisable(GL_POLYGON_OFFSET_LINE);

    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(5, 1, 2, 6, v);
    glDisable(GL_POLYGON_OFFSET_LINE);
    
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(2, 3, 7, 6, v);
    glDisable(GL_POLYGON_OFFSET_LINE);
    
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(6, 5, 4, 7, v);
    glDisable(GL_POLYGON_OFFSET_LINE);

    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPolygon(4, 0, 3, 7, v);

    glColor3f(1.0,1.0,1.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

/* drawBox - takes centre point, width, height and depth of a box,
 *  calculates its corner vertices, and draws it with the cube function
 */
void wireCube(float xn, float yn, float zn, float xm, float ym, float zm){

    float vertices[8][3]={{xn,ym,zn},
                        {xn,yn,zn},
                        {xm,yn,zn},
                        {xm,ym,zn},
                        {xn,ym,zm},
                        {xn,yn,zm},
                        {xm,yn,zm},
                        {xm,ym,zm}                   
                        };
    cube(vertices);
}
void NodeModel::nodeSpecificCodeUp(){
    switch (modelType){
            
        case Sphere:
            glutSolidSphere(.5, 12, 10);
            if (flag_frame == 2) {
                wireCube(-0.5,-0.5,0.5,0.5,0.5,-0.5);
            }
            break;
            
        case Cube:
            if (flag_frame == 1) {
                wireCube(-0.5,-0.5,0.5,0.5,0.5,-0.5);
            }
            glutSolidCube(1);
            break;
            
        case Teapot:
            if (flag_frame == 3) {
                wireCube(-1.5,-0.8,1.0,1.5,0.8,-1.0);
            }
            
            glutSolidTeapot(1);
            break;
            
        case Cone:
            if (flag_frame == 4) {
                wireCube(-0.5,-0.5,1.0,0.5,0.5,0.0);
            }
            glutSolidCone(0.5, 1, 50, 50);
            break;
            
        case Torus:
            if (flag_frame == 5) {
                wireCube(-0.5,-0.5,0.3,0.5,0.5,-0.3);
            }
            glutSolidTorus(0.15,0.35,50,50);
            break;
            
        case Custom:
            glBegin(GL_POLYGON);
            
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            
            glColor3f(.5,.5,.5);
            
            glTexCoord2f(0, 0);
            glVertex3f(-1,-1,1);
            
            glTexCoord2f(1, 1);
            glVertex3f(1,-1,1);
            
            glTexCoord2f(0, 1);
            glVertex3f(1,-1,-1);
            
            glTexCoord2f(1, 0);
            glVertex3f(-1,-1,-1);
            
            glEnd();
            break;
    }
    glPopMatrix();
}