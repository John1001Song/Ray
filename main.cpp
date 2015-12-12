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

#include "structs.h"


//position of camera
float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;

//array used for intersect test
double startI[] ={0,0,0};
double endI[]={1,1,1};

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
float help1=0;
float help2=0;
float help3=0;
float help4=0;
float help5=0;
float help6=0;

float xb0=0;
float yb0=0;
float zb0=0;

float xb1=0;
float yb1=0;
float zb1=0;

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
            
            xb0=-0.5;
            yb0=-0.5;
            zb0=0.5;
            
            xb1=0.5;
            yb1=0.5;
            zb1=-0.5;
            
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
            
            xb0=-0.5;
            yb0=-0.5;
            zb0=0.5;
            
            xb1=0.5;
            yb1=0.5;
            zb1=-0.5;
            
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
            
            xb0=-0.5;
            yb0=-0.5;
            zb0=0.5;
            
            xb1=0.5;
            yb1=0.5;
            zb1=-0.5;
            
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
            
            xb0=-0.5;
            yb0=-0.5;
            zb0=0.5;
            
            xb1=0.5;
            yb1=0.5;
            zb1=-0.5;
            
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
            
            xb0=-0.5;
            yb0=-0.5;
            zb0=0.5;
            
            xb1=0.5;
            yb1=0.5;
            zb1=-0.5;
            
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
            xb1*=2;
            xb0*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {0.5,1,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            xb1*=0.5;
            xb0*=0.5;
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
            yb1*=2;
            yb0*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {1,0.5,1};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            yb1*=0.5;
            yb0*=0.5;
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
            zb1*=2;
            zb0*=2;
        }
        if (mod==GLUT_ACTIVE_ALT){
            Vector3D tempVec3D = {1,1,0.5};
            NodeTransform *T = new NodeTransform(Scale, tempVec3D);
            SG->insertChildNodeHere(T);
            zb0*=0.5;
            zb1*=0.5;
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
            
            help1= yb0 *cos(ang)- zb0*sin(ang);
            help2= yb1 *cos(ang)- zb1*sin(ang);
            help3= yb0*sin(ang)+zb0*cos(ang);
            help4= zb1*sin(ang)+zb1*cos(ang);
            
            yb0=help1;
            yb1=help2;
            zb0=help3;
            zb1=help4;
            
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleX-=1;
            Vector4D rotVec4D= {1,0,0,angleX};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
            
            ang=angleX*RadToD;
            
            help1= yb0 *cos(ang)- zb0*sin(ang);
            help2= yb1 *cos(ang)- zb1*sin(ang);
            help3= yb0*sin(ang)+zb0*cos(ang);
            help4= zb1*sin(ang)+zb1*cos(ang);
            
            yb0=help1;
            yb1=help2;
            zb0=help3;
            zb1=help4;
            
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
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleY-=1;
            Vector4D rotVec4D= {0,1,0,angleY};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
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
        }
        if (mod==GLUT_ACTIVE_ALT){
            angleZ-=1;
            Vector4D rotVec4D= {0,0,1,angleZ};
            NodeTransform *T = new NodeTransform(Rotate, rotVec4D);
            SG->insertChildNodeHere(T);
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
bool Intersect(int x, int y){
    printf("%i, %i\n", x, y);
    
    //allocate matricies memory
    double matModelView[16], matProjection[16];
    int viewport[4];
    
    //vectors
    
    
    //grab the matricies
    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    //unproject the values
    double winX = (double)x;
    double winY = viewport[3] - (double)y;
    
    // get point on the 'near' plane (third param is set to 0.0)
    gluUnProject(winX, winY, 0.0, matModelView, matProjection,
                 viewport, &startI[0], &startI[1], &startI[2]);
    
    // get point on the 'far' plane (third param is set to 1.0)
    gluUnProject(winX, winY, 1.0, matModelView, matProjection,
                 viewport, &endI[0], &endI[1], &endI[2]);
    
    
    printf("near point: %f,%f,%f\n", startI[0], startI[1], startI[2]);
    printf("far point: %f,%f,%f\n", endI[0], endI[1], endI[2]);
    
    //check for intersection against sphere!
    //hurray!
    
    double A, B, C;
    
    double R0x, R0y, R0z;
    double Rdx, Rdy, Rdz;
    
    R0x = startI[0];
    R0y = startI[1];
    R0z = startI[2];
    
    Rdx = endI[0] - startI[0];
    Rdy = endI[1] - startI[1];
    Rdz = endI[2] - startI[2];
    
    //magnitude!
    double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);
    
    float t1x, t2x, t1y,t2y, t1z, t2z, tnear,tfar, temp;
    
    t1x =(xb0-R0x)/Rdx;
    t2x =(xb1-R0x)/Rdx;
    
    if (t1x> t2x){
        temp=t1x;
        t1x=t2x;
        t2x=temp;
        tnear= t1x;
        tfar= t2x;
    }
    if(tnear>tfar|| tfar<0){
        printf("No intersection!");
    }else{
        t1y =(yb0-R0y)/Rdy;
        t2y =(yb1-R0y)/Rdy;
        
        if (t1y> t2y){
            temp=t1y;
            t1y=t2y;
            t2y=temp;
        }
        if (t1y>tnear){
            tnear=t1y;
        }
        if (t2y<tfar){
            tfar=t2y;
        }
        
        if (tnear>tfar||tfar<0){
            printf("No intersection!");
        }else{
            t1z =(zb0-R0z)/Rdz;
            t2z =(zb1-R0z)/Rdz;
            
            if (t1z>t2z){
                temp=t1z;
                t1z=t2z;
                t2z=temp;
            }
            
            if (t1z>tnear){
                tnear=t1z;
            }
            
            if(t2z<tfar){
                tfar=t2z;
            }
            
            if (tnear>tfar||tfar<0){
                printf("No intersection!");
            }else{
                printf("Intersection at: t = %f, and t = %f\n", tnear, tfar);
                printf("near point: %f,%f,%f\n", startI[0], startI[1], startI[2]);
                printf("far point: %f,%f,%f\n", endI[0], endI[1], endI[2]);
            }
        }
        
    }
    
    return false; //else returns false
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
            xb0+=0.1;
            xb1+=0.1;
            break;
        }
            
            //Object moves X axis-
        case GLUT_KEY_F2:
        {
            Vector3D tempVec3D = {-0.1,0,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            xb0-=0.1;
            xb1-=0.1;
            break;
        }
            
            //Object moves Y axis+
        case GLUT_KEY_F3:
        {
            Vector3D tempVec3D = {0,0.1,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            yb0+=0.1;
            yb1+=0.1;
            break;
        }
            
            //Object moves Y axis-
        case GLUT_KEY_F4:
        {
            Vector3D tempVec3D = {0,-0.1,0};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            yb0-=0.1;
            yb1-=0.1;
            break;
        }
            
            //Object moves Z axis+
        case GLUT_KEY_F5:
        {
            Vector3D tempVec3D = {0,0,0.1};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            zb0+=0.1;
            zb1+=0.1;
            break;
        }
            
            //Object moves Z axis-
        case GLUT_KEY_F6:
        {
            Vector3D tempVec3D = {0,0,-0.1};
            NodeTransform *T = new NodeTransform(Translate, tempVec3D);
            SG->insertChildNodeHere(T);
            zb0-=0.1;
            zb1+=0.1;
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
        Intersect(x, y);
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
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    
    glEnable(GL_DEPTH_TEST);
    
    init();
    
    glutMainLoop();				//starts the event loop
    return(0);					//return may not be necessary on all compilers
}