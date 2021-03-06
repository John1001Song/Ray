/* CS 3GC3 - Texturing sample
 * by R. Teather
 */
#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include "structs.h"


//position of camera
float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;

//array used for intersect test
double start[] ={0,0,0};
double endy[]={1,1,1};

//angle rotate
float angleX=0;
float angleY=0;
float angleZ=0;

//flag used to draw axis
int flag_axis = 0;

//lighting
int countL=0;
int light=0;
// light 0
float position0[4] = {600,50,0, 1};
float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {1,1,1, 1};
float spec0[4] = {1,1,1, 1};
// light 1
float position1[4] = {0,50,600, 1};
float amb1[4] = {1, 1, 1, 1};
float diff1[4] = {1,1,1, 1};
float spec1[4] = {1,1,1, 1};

//bounded box value

float RadToD=180/3.14;
float ang=0;

//node ids
int masterID = 0;
int getID(){
    return masterID++;
}

//sceneGraph
#include "node.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"
#include "nodeMaterial.h"
SceneGraph *SG;

/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */

//function which will populate a sample graph
void initGraph(){
    
    
    
    
    //temporary place which holds out values
    Vector3D tempVec3;
    
    //TRANSFORMATION
    //a tranlation transformation node
    //how much translation
    tempVec3.x = 1;
    tempVec3.y = 1;
    tempVec3.z = 1;
    //add the node as a child of root node
    NodeTransform *T1 = new NodeTransform(Translate, tempVec3);
    //insert the node into the graph
    SG->insertChildNodeHere(T1);
    
    //create a cube and scale it to a platform
    NodeModel *P = new NodeModel(Cube);
    SG->insertChildNodeHere(P);
    SG->currentNode = P;
    //how much to scale
    Vector3D scalVec3D = {100, .5, 100};
    //Transformation: scale
    NodeTransform *S = new NodeTransform(Scale, scalVec3D);
    SG->insertChildNodeHere(S);
    
    //Platform material is Jade
    NodeMaterial *PM = new NodeMaterial(Jade);
    SG->insertChildNodeHere(PM);
    
    //move dowm the platform
    Vector3D moveDowm = {0, -1.5, 0};
    NodeTransform *MD = new NodeTransform(Translate, moveDowm);
    SG->insertChildNodeHere(MD);
    
    //go back to root
    SG->goToRoot();
    //go to the child node and all objects are following the child node child(0)
    SG->goToChild(0);
    
    
    //MODEL
    //we will now add a teapot model to the graph as a child of the
    //transformation node
    //insert the node into the graph
    
    //THE SAME FLOW CAN BE USED TO DYNAMICALLY ADD NODES
    //DURING RUNTIME
}

//light controller
void lightC(int light,int dir,int unit){
    //control light0
    if(light==0){
        //which direction (x,y,z)
        switch(dir){
                //x
            case 0:
                // x up
                if(unit==1 && position0[0]<=300){
                    position0[0]+=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                    
                }//x down
                else if(unit==0 && position0[0]>=-300){
                    position0[0]-=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                }
                //printf("x pos: %f \n",position0[0]);
                //y
            case 1:
                //y up
                if(unit==1 && position0[1]<=300){
                    position0[1]+=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                    
                }//y down
                else if(unit==0 && position0[1]>=-300){
                    position0[1]-=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                }
                
                
                //z
            case 2:
                //z up
                if(unit==1 && position0[2]<=300){
                    position0[2]+=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                    
                }//z down
                else if(unit==0 && position0[2]>=-300){
                    position0[2]-=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                }
        }
    }else if(light==1){
        switch(dir){
                //x
            case 0:
                // x up
                if(unit==1 && position1[0]<=300){
                    position1[0]+=10;
                    glLightfv(GL_LIGHT1,GL_POSITION,position1);
                    
                }//x down
                else if(unit==0 && position1[0]>=-300){
                    position1[0]-=10;
                    glLightfv(GL_LIGHT1,GL_POSITION,position1);
                }
                //printf("x pos: %f \n",position1[0]);
                //y
            case 1:
                //y up
                if(unit==1 && position1[1]<=300){
                    position0[1]+=10;
                    glLightfv(GL_LIGHT1,GL_POSITION,position1);
                    
                }//y down
                else if(unit==0 && position1[1]>=-300){
                    position0[1]-=10;
                    glLightfv(GL_LIGHT1,GL_POSITION,position1);
                }
                
                //z
            case 2:
                //z up
                if(unit==1 && position0[2]<=300){
                    position0[2]+=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                    
                }//z down
                else if(unit==0 && position0[2]>=-300){
                    position0[2]-=10;
                    glLightfv(GL_LIGHT0,GL_POSITION,position0);
                }
        }
        
    }
}

//callbacks
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 'Q':
            exit (0);
            break;
            
            //press key "1" to get a cube at position (0, 0, 0)
        case '1':
        {
            SG->currentNode->flag_frame = 0;
            NodeModel *m = new NodeModel(Cube);
            m->flag_frame = 1;
            m->parent = SG->rootNode->children->at(0);
            SG->rootNode->children->at(0)->children->push_back(m);
            SG->currentNode = m;

            break;
        }
            
            //press "2" to get a Sphere
        case '2':
        {
            SG->currentNode->flag_frame = 0;
            NodeModel *m = new NodeModel(Sphere);
            m->flag_frame = 2;
            m->parent = SG->rootNode->children->at(0);
            SG->rootNode->children->at(0)->children->push_back(m);
            SG->currentNode = m;
            
            break;
        }
            
            //press "3" to get a Teapot
        case '3':
        {
            SG->currentNode->flag_frame = 0;
            NodeModel *m = new NodeModel(Teapot);
            m->flag_frame = 3;
            m->parent = SG->rootNode->children->at(0);
            SG->rootNode->children->at(0)->children->push_back(m);
            SG->currentNode = m;
            
            break;
        }
            
            //press "4" to get a Cone
        case '4':
        {
            SG->currentNode->flag_frame = 0;
            NodeModel *m = new NodeModel(Cone);
            m->flag_frame = 4;
            m->parent = SG->rootNode->children->at(0);
            SG->rootNode->children->at(0)->children->push_back(m);
            SG->currentNode = m;
            
            break;
        }
            
            //press "5" to get a Torus
        case '5':
        {
            SG->currentNode->flag_frame = 0;
            NodeModel *m = new NodeModel(Torus);
            m->flag_frame = 5;
            m->parent = SG->rootNode->children->at(0);
            SG->rootNode->children->at(0)->children->push_back(m);
            SG->currentNode = m;
            
            break;
        }
            
        //press b: cancel previous movement
        case 'b':
        {
            SG->deleteThisNode();
            break;
        }
            
        case 'r':
        case 'R':
        {
            SG->goToParent();
            while (SG->currentNode->children->size() > 0) {
                SG->deleteThisNode();
            }
            break;
        }
            
            //pree '7' to get Gold surface
        case '7':
        {
            NodeMaterial *m = new NodeMaterial(Gold);
            SG->insertChildNodeHere(m);
            break;
        }
            
            //press 8 to get CyanPlastic surface
        case '8':
        {
            NodeMaterial *m = new NodeMaterial(CyanPlastic);
            SG->insertChildNodeHere(m);
            break;
        }
            
            //press 9 to get YellowRubber surface
        case '9':
        {
            NodeMaterial *m = new NodeMaterial(YellowRubber);
            SG->insertChildNodeHere(m);
            break;
        }
            
            //press 'm' to get surface with Jade
        case '6':
        {
            NodeMaterial *m = new NodeMaterial(MaterialType::Jade);
            SG->insertChildNodeHere(m);
            break;
        }
            
            //press n to get a random surface. Try to press many times and you will get a surprice surface!
        case 'n':
        {
            NodeMaterial *m = new NodeMaterial(Random);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case 'h':
            flag_axis++;
            break;
            
    }
    
    //turn on / off the light
    if (key=='o'||key=='O'){
        switch(countL){
            case 0:
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                glEnable(GL_LIGHT1);
                glEnable(GL_DEPTH_TEST);
                
                glLightfv(GL_LIGHT0, GL_POSITION, position0);
                glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
                glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
                glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
                
                glLightfv(GL_LIGHT1, GL_POSITION, position1);
                glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
                glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
                glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
                
                countL++;
                break;
                // printf("light%f \n", light);
            case 1:
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
                glDisable(GL_LIGHT1);
                countL=0;
                break;
        }
    }
    //light controller switch light
    if (key=='0'){
        if(light==0){
            light++;
        }else{light=0;}
    }
    //switch from x,y,z axis
    //x-axis
    //x + shift, x++
    //x + alt, x--
    if (key=='x'||key=='X'){
        int mod= glutGetModifiers();
        if (mod== GLUT_ACTIVE_SHIFT){
            lightC(light,0,1);
        }
        if (mod== GLUT_ACTIVE_ALT){
            lightC(light,0,0);
        }
    }
    //y-axis
    //y + shift,y++
    //y + alt,y--
    if (key=='y'||key=='Y'){
        int mod= glutGetModifiers();
        if (mod== GLUT_ACTIVE_SHIFT){
            lightC(light,1,1);
        }
        if (mod== GLUT_ACTIVE_ALT){
            lightC(light,1,0);
        }
    }
    //z-axis
    //z + shift, z++
    //z + alt, z--
    if (key=='z'||key=='Z'){
        int mod= glutGetModifiers();
        if (mod== GLUT_ACTIVE_SHIFT){
            lightC(light,2,1);
        }
        if (mod== GLUT_ACTIVE_ALT){
            lightC(light,2,0);
        }
    }
    // scale
    // x-axis
    // x + shift,x*2
    // x + alt, x/2
    if (key=='c'||key=='C'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            Vector3D tempVec3D = {2,1,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeFar.x*=2;
            SG->currentNode->nodeNear.x*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {0.5,1,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.x*=0.5;
            SG->currentNode->nodeFar.x*=0.5;
        }
    }
    
    // scale
    // y-axis
    // y + shift,y*=2
    // y + alt, y/=2
    if (key=='v'||key=='V'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            Vector3D tempVec3D = {1,2,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeFar.y*=2;
            SG->currentNode->nodeNear.y*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {1,0.5,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.y*=0.5;
            SG->currentNode->nodeFar.y*=0.5;
        }
    }
    // scale
    // z-axis
    // z + shift,z*2
    // z + alt, z/2
    if (key=='b'||key=='B'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            Vector3D tempVec3D = {1,1,2};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.z*=2;
            SG->currentNode->nodeFar.z*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {1,1,0.5};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeFar.z*=0.5;
            SG->currentNode->nodeNear.z*=0.5;
        }
    }
    
    // rotate
    // x-axis
    // j + shift, angleX++
    // j + alt, angleX--
    if (key=='j'||key=='J'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            angleX+=1;
            Vector4D rotVec4D= {1,0,0,angleX};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleX*RadToD;
            
            float yn, zn;//temp variable to store the y near and z near
            yn = SG->currentNode->nodeNear.y;
            zn = SG->currentNode->nodeNear.z;
            
            float yf, zf;//temp variable to store the y far and z far
            yf = SG->currentNode->nodeFar.y;
            zf = SG->currentNode->nodeFar.z;
            
            //node near; rotate about x-axis, so x of node near vertex does not change
            yn = yn * cos(ang) - zn * sin(ang);
            zn = yn * sin(ang) + zn * cos(ang);
            
            //node far; rotate about x-axis.
            yf = yf * cos(ang) - zf * sin(ang);
            zf = yf * sin(ang) + zf * cos(ang);

            
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleX-=1;
            Vector4D rotVec4D= {1,0,0,angleX};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleX*RadToD;
            
            float yn, zn;//temp variable to store the y near and z near
            yn = SG->currentNode->nodeNear.y;
            zn = SG->currentNode->nodeNear.z;
            
            float yf, zf;//temp variable to store the y far and z far
            yf = SG->currentNode->nodeFar.y;
            zf = SG->currentNode->nodeFar.z;
            
            //node near; rotate about x-axis, so x of node near vertex does not change
            yn = yn * cos(ang) - zn * sin(ang);
            zn = yn * sin(ang) + zn * cos(ang);
            
            //node far; rotate about x-axis.
            yf = yf * cos(ang) - zf * sin(ang);
            zf = yf * sin(ang) + zf * cos(ang);
            
            //node far and near get the after-rotate value
            SG->currentNode->nodeFar.y = yf;
            SG->currentNode->nodeFar.z = zf;
            SG->currentNode->nodeNear.y = yn;
            SG->currentNode->nodeNear.z = zn;
        }
    }
    
    // rotate
    // y-axis
    // k + shift, angleY++
    // k + alt, angleY--
    if (key=='k'||key=='K'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            angleY+=1;
            Vector4D rotVec4D= {0,1,0,angleY};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleY*RadToD;
            
            float xn, zn;//temp variable to store the x near and z near
            xn = SG->currentNode->nodeNear.x;
            zn = SG->currentNode->nodeNear.z;
            
            float xf, zf;//temp variable to store the x far and z far
            xf = SG->currentNode->nodeFar.x;
            zf = SG->currentNode->nodeFar.z;
            
            //node near; rotate about y-axis, so y of node near vertex does not change
            xn = xn * cos(ang) + zn * sin(ang);
            zn = xn * sin(ang) * (-1) + zn * cos(ang);
            
            //node far; rotate about x-axis.
            xf = xf * cos(ang) + zf * sin(ang);
            zf = xf * sin(ang) * (-1) + zf * cos(ang);
            
            //node far and near get the after-rotate value
            SG->currentNode->nodeFar.x = xf;
            SG->currentNode->nodeFar.z = zf;
            SG->currentNode->nodeNear.x = xn;
            SG->currentNode->nodeNear.z = zn;
            
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleY-=1;
            Vector4D rotVec4D= {0,1,0,angleY};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleY*RadToD;
            
            float xn, zn;//temp variable to store the x near and z near
            xn = SG->currentNode->nodeNear.x;
            zn = SG->currentNode->nodeNear.z;
            
            float xf, zf;//temp variable to store the x far and z far
            xf = SG->currentNode->nodeFar.x;
            zf = SG->currentNode->nodeFar.z;
            
            //node near; rotate about y-axis, so y of node near vertex does not change
            xn = xn * cos(ang) + zn * sin(ang);
            zn = xn * sin(ang) * (-1) + zn * cos(ang);
            
            //node far; rotate about x-axis.
            xf = xf * cos(ang) + zf * sin(ang);
            zf = xf * sin(ang) * (-1) + zf * cos(ang);
            
            //node far and near get the after-rotate value
            SG->currentNode->nodeFar.x = xf;
            SG->currentNode->nodeFar.z = zf;
            SG->currentNode->nodeNear.x = xn;
            SG->currentNode->nodeNear.z = zn;
            
        }
    }
    // rotate
    // z-axis
    //l + shift, angleZ++
    // l+ alt, angleZ--
    if (key=='l'||key=='L'){
        int mod= glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT){
            angleZ+=1;
            Vector4D rotVec4D= {0,0,1,angleZ};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleZ*RadToD;
            
            float xn, yn;//temp variable to store the x near and y near
            xn = SG->currentNode->nodeNear.x;
            yn = SG->currentNode->nodeNear.y;
            
            float xf, yf;//temp variable to store the x far and y far
            xf = SG->currentNode->nodeFar.x;
            yf = SG->currentNode->nodeFar.y;
            
            //node near; rotate about z-axis, so z of node near vertex does not change
            xn = xn * cos(ang) - yn * sin(ang);
            yn = xn * sin(ang) + yn * cos(ang);
            
            //node far; rotate about z-axis.
            xf = xf * cos(ang) - yf * sin(ang);
            yf = xf * sin(ang) + yf * cos(ang);
            
            //node far and near get the after-rotate value
            SG->currentNode->nodeFar.x = xf;
            SG->currentNode->nodeFar.y = yf;
            SG->currentNode->nodeNear.x = xn;
            SG->currentNode->nodeNear.y = yn;
            
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleZ-=1;
            Vector4D rotVec4D= {0,0,1,angleZ};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleZ*RadToD;
            
            float xn, yn;//temp variable to store the x near and y near
            xn = SG->currentNode->nodeNear.x;
            yn = SG->currentNode->nodeNear.y;
            
            float xf, yf;//temp variable to store the x far and y far
            xf = SG->currentNode->nodeFar.x;
            yf = SG->currentNode->nodeFar.y;
            
            //node near; rotate about z-axis, so z of node near vertex does not change
            xn = xn * cos(ang) - yn * sin(ang);
            yn = xn * sin(ang) + yn * cos(ang);
            
            //node far; rotate about z-axis.
            xf = xf * cos(ang) - yf * sin(ang);
            yf = xf * sin(ang) + yf * cos(ang);
            
            //node far and near get the after-rotate value
            SG->currentNode->nodeFar.x = xf;
            SG->currentNode->nodeFar.y = yf;
            SG->currentNode->nodeNear.x = xn;
            SG->currentNode->nodeNear.y = yn;
            
        }
    }
    
    
    glutPostRedisplay();
}

/* drawAxis() -- draws an axis at the origin of the coordinate system
 *   red = +X axis, green = +Y axis, blue = +Z axis
 */
//draw axis to find XYZ direction
void drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(500,0,0);
    
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,500,0);
    
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,500);
    glEnd();
}


//borrow the following code Intersect from Thomas

//function which preforms intersection test


//this function will use intersect to check all object in the scene. If hit, get a "true". Collect the hitted object and return the nearest one.
//Then the currentNode pointer points to this object.

bool intersect(Vector3D nodeNear, Vector3D nodeFar, int mouseX, int mouseY){
    //allocate matrices memory
    double matModelView[16], matProjection[16];
    int viewport[4];
    
    //grab the matricies
    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    //unproject the values
    double winX = (double)mouseX;
    double winY = viewport[3] - (double)mouseY;
    
    // get point on the 'near' plane (third param is set to 0.0)
    gluUnProject(winX, winY, 0.0, matModelView, matProjection,
                 viewport, &start[0], &start[1], &start[2]);
    
    // get point on the 'far' plane (third param is set to 1.0)
    gluUnProject(winX, winY, 1.0, matModelView, matProjection, viewport, &endy[0], &endy[1], &endy[2]);
    
    printf("near point: %f,%f,%f\n", start[0], start[1], start[2]);
    printf("far point: %f,%f,%f\n", endy[0], endy[1], endy[2]);
    
    double R0x, R0y, R0z;//Ray origin
    double Rdx, Rdy, Rdz;//Ray direction unit vector
    
    R0x = start[0];
    R0y = start[1];
    R0z = start[2];
    
    Rdx = endy[0] - start[0];
    Rdy = endy[1] - start[1];
    Rdz = endy[2] - start[2];
    
    //magnitude
    double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz*Rdz);
    
    //get correct unit vector now
    Rdx /= M;
    Rdy /= M;
    Rdz /= M;
    
    double Tfar = std::numeric_limits<double>::infinity();
    double Tnear = -1 * Tfar;
    
    float T1x, T2x, T1y, T2y, T1z, T2z;
    
    float xl = nodeNear.x;
    float yl = nodeNear.y;
    float zl = nodeNear.z;
    
    float xh = nodeFar.x;
    float yh = nodeFar.y;
    float zh = nodeFar.z;
    
    //using X plane
    if (Rdx == 0) {
        if ((R0x < xl) || (R0x > xh)) {
            return false;
        }
    }else{
        T1x = (xl - R0x) / Rdx;
        T2x = (xh - R0x) / Rdx;
    }

    if (T1x > T2x) {
        swap(T1x, T2x);
    }
    
    if (T1x > Tnear) {
        Tnear = T1x;
    }
    
    if (T2x < Tfar) {
        Tfar = T2x;
    }
    
    if (Tnear > Tfar) {
        return false;
    }
    
    if (Tfar < 0) {
        return false;
    }
    
    //using Y plane
    if (Rdy == 0) {
        if ((R0y < yl) || (R0y > yh)) {
            return false;
        }
    }else{
        T1y = (yl - R0y) / Rdy;
        T2y = (yh - R0y) / Rdy;
    }
    
    if (T1y > T2y) {
        swap(T1y, T2y);
    }
    
    if (T1y > Tnear) {
        Tnear = T1y;
    }
    
    if (T2y < Tfar) {
        Tfar = T2y;
    }
    
    if (Tnear > Tfar) {
        return false;
    }
    
    if (Tfar < 0) {
        return false;
    }

    //using Z plane
    if (Rdz == 0) {
        if ((R0z < zl) || (R0z > zh)) {
            return false;
        }
    }else{
        T1z = (zl - R0z) / Rdz;
        T2z = (zh - R0z) / Rdz;
    }
    
    if (T1z > T2z) {
        swap(T1z, T2z);
    }
    
    if (T1z > Tnear) {
        Tnear = T1z;
    }
    
    if (T2z < Tfar) {
        Tfar = T2z;
    }
    
    if (Tnear > Tfar) {
        return false;
    }
    
    if (Tfar < 0) {
        return false;
    }

    
    return true;
    
    
}

float getDis(Vector3D nodeNear, int mouseX, int mouseY){
    float distance = 0;
    
    //allocate matricies memory
    double matModelView[16], matProjection[16];
    int viewport[4];
    
    //grab the matrices
    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    //unproject the values;
    double winX = (double)mouseX;
    double winY = viewport[3] - (double)mouseY;
    
    //get point on the 'near' plane (third param is set to 0.0)
    gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport, &start[0], &start[1], &start[2]);
    
    //calculate the distance between the nodeNear and start
    double xn, yn, zn;
    double x0, y0, z0;
    double xd, yd, zd;
    
    x0 = start[0];
    y0 = start[1];
    z0 = start[2];
    
    xn = nodeNear.x;
    yn = nodeNear.y;
    zn = nodeNear.z;
    
    xd = xn - x0;
    yd = yn - y0;
    zd = zn - z0;
    
    distance = sqrtf(xd*xd + yd*yd + zd*zd);
    
    return distance;
}

void raySelect(int mouseX, int mouseY){
    int objNumb; // indicate how many objects in the scene
    //SG has two children (one child is a translation at child(0) and the other is nodeModel at child(1)). All objects are linked to NodeTransform
    objNumb = SG->rootNode->children->at(0)->children->size();
    printf("objNumb is %d\n", objNumb);
    
    bool hitRes[objNumb]; //array to store the hit result of each object
    
    Vector3D currentNear, currentFar; //temp vertex to store the current node near and far vertex;
    bool currentHitRes = false; // temp bool to store the hit result
    
    float nearestDis = 0.0;//use this temp variable to store the shortest distance with the ray origin
    int nearObj = 0;// use this temp variable to store the children index and it is about the nearest object within the hitted ones
    
    //use for loop to check if the ray hits each object or not
    for (int i = 0; i < objNumb; i++) {
        //pointer "currentNode" points to the current object; copy current object near vertex to the temp "near" vertex
        SG->goToParent();
        SG->goToChild(i);
        currentNear = SG->currentNode->nodeNear;
        //copy object's far vertex to the temp "far" vertex
        currentFar = SG->currentNode->nodeFar;
        
        printf("currentNear x, y, z is %f,%f,%f\n", currentNear.x, currentNear.y, currentNear.z);
        printf("currentFar x, y, z is %f,%f,%f\n", currentFar.x, currentFar.y, currentFar.z);
        
        //compare near and far vertex first, because after transform, near would be far and far be near
        float dNear = getDis(currentNear, mouseX, mouseY);
        float dFar = getDis(currentFar, mouseX, mouseY);
        
        printf("dNear is %f\n", dNear);
        printf("dFar is %f\n", dFar);
        
        if (dNear > dFar) {
            currentFar = SG->currentNode->nodeNear;
            currentNear = SG->currentNode->nodeFar;
        }
        
        //use intersect func to check if there is a hit
        currentHitRes = intersect(currentNear, currentFar, mouseX, mouseY);
        
        //use currentDis to store the distance with the near and ray origin
        float currentDis;
        if (currentHitRes == true) {
            printf("have Intersection!!!\n");
            currentDis = getDis(currentNear, mouseX, mouseY);
        }else{
            printf("no Intersection!!!\n");
        }
        
        if ((currentDis < nearestDis) && (currentHitRes == true)) {
            nearestDis = currentDis;
            nearObj = i;
            printf("current nearest distance is %f\n", nearestDis);
            printf("current nearest object is %d\n", nearObj);
        }
        //store the hit result to the array
        hitRes[i] = currentHitRes;
    }
    
    printf("nearest object is child %d\n", nearObj);
    
    //after the for loop, we could get the shortest distance between the nearest object and the ray origin. And get the index of the child "nearObj"
    //then move the pointer "currentNode" points to this child[nearObj]
    SG->goToRoot();
    SG->goToChild(0);//go to the Transform node
    SG->goToChild(nearObj);// go to the nearest object where it is located at the childfren vector and the "currentNode" is pointing to it
    
    
}

void special(int key, int x, int y)
{
    /* arrow key presses move the camera */
    switch(key)
    {
        case GLUT_KEY_LEFT:
            camPos[0]-=0.1;
            break;
            
        case GLUT_KEY_RIGHT:
            camPos[0]+=0.1;
            break;
            
        case GLUT_KEY_UP:
            camPos[2] -= 0.1;
            break;
            
        case GLUT_KEY_DOWN:
            camPos[2] += 0.1;
            break;
            
        case GLUT_KEY_HOME:
            camPos[1] += 0.1;
            break;
            
        case GLUT_KEY_END:
            camPos[1] -= 0.1;
            break;
            
            //Object moves X axis+
        case GLUT_KEY_F1:
        {
            Vector3D tempVec3D = {.1,0,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.x+=0.1;
            SG->currentNode->nodeFar.x+=0.1;
            
            printf("nodeNear x is %f\n", SG->currentNode->nodeNear.x);
            printf("nodeFar x is %f\n", SG->currentNode->nodeFar.x);
            
            break;
        }
            
            //Object moves X axis-
        case GLUT_KEY_F2:
        {
            Vector3D tempVec3D = {-0.1,0,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.x-=0.1;
            SG->currentNode->nodeFar.x-=0.1;
            
            printf("nodeNear x is %f\n", SG->currentNode->nodeNear.x);
            printf("nodeFar x is %f\n", SG->currentNode->nodeFar.x);
            
            break;
        }
            
            //Object moves Y axis+
        case GLUT_KEY_F3:
        {
            Vector3D tempVec3D = {0,0.1,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.y+=0.1;
            SG->currentNode->nodeFar.y+=0.1;
            
            printf("nodeNear y is %f\n", SG->currentNode->nodeNear.y);
            printf("nodeFar y is %f\n", SG->currentNode->nodeFar.y);
            
            break;
        }
            
            //Object moves Y axis-
        case GLUT_KEY_F4:
        {
            Vector3D tempVec3D = {0,-0.1,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.y-=0.1;
            SG->currentNode->nodeFar.y-=0.1;
            
            printf("nodeNear y is %f\n", SG->currentNode->nodeNear.y);
            printf("nodeFar y is %f\n", SG->currentNode->nodeFar.y);
            
            break;
        }
            
            //Object moves Z axis+
        case GLUT_KEY_F5:
        {
            Vector3D tempVec3D = {0,0,0.1};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.z+=0.1;
            SG->currentNode->nodeFar.z+=0.1;
            
            printf("nodeNear z is %f\n", SG->currentNode->nodeNear.z);
            printf("nodeFar z is %f\n", SG->currentNode->nodeFar.z);
            
            break;
        }
            
            //Object moves Z axis-
        case GLUT_KEY_F6:
        {
            Vector3D tempVec3D = {0,0,-0.1};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            SG->currentNode->nodeNear.z-=0.1;
            SG->currentNode->nodeFar.z-=0.1;
            
            printf("nodeFar z is %f\n", SG->currentNode->nodeNear.z);
            printf("nodeFar z is %f\n", SG->currentNode->nodeFar.z);
            
            break;
        }
            
    }
    glutPostRedisplay();
}

void init(void)
{	GLuint id = 1;
    
    glEnable(GLUT_DEPTH);
    
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    
    //init our scenegraph
    SG = new SceneGraph();
    
    //add various nodes
    //initializing our world
    initGraph();
    
    
}

void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        raySelect(x, y);
    }
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glColor3f(1,1,1);
    
    //draw the sceneGraph
    SG->draw();
    
    //draw axis or not
    if (flag_axis%2 == 1) {
        drawAxis();
    }
    
    
    
    glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);		//starts up GLUT
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    
    glutCreateWindow("SimpleSceneGraph");	//creates the window

    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    
    init();
    
    glutMainLoop();				//starts the event loop
    return(0);					//return may not be necessary on all compilers
}