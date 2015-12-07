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

float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;

//lighting
int countL=0;
int light=0;
// light 0
float position0[4] = {600,50,0, 1};
float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {1,0,0, 1};
float spec0[4] = {0,0,1, 1};
// light 1
float position1[4] = {0,50,600, 1};
float amb1[4] = {1, 1, 1, 1};
float diff1[4] = {1,0,0, 1};
float spec1[4] = {0,0,1, 1};

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

//sceneGraph
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"
#include "nodeMaterial.h"
SceneGraph *SG;

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
	//go to the child node
	SG->goToChild(0);


	//MODEL
	//we will now add a teapot model to the graph as a child of the
	//transformation node
//	NodeModel *M1 = new NodeModel(Teapot);
	//insert the node into the graph
//	SG->insertChildNodeHere(M1);


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
		case 27:
			exit (0);
			break;
        case '1':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Cube);
            SG->insertChildNodeHere(m);
            break;
        }
        case '2':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Sphere);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case '3':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Teapot);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case '4':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Cone);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case '5':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Dodecahedron);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case '6':
        {
            SG->goToRoot();
            SG->goToChild(0);
            NodeModel *m = new NodeModel(Icosahedron);
            SG->insertChildNodeHere(m);
            break;
        }
            
        case 'm':
        {
            NodeMaterial *m = new NodeMaterial(MaterialType::Jade);
            SG->insertChildNodeHere(m);
            break;
        }
        
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
            //x + shift, x ++
            //x + alt, x --
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
            //y + shift,y ++
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
            
	
	glutPostRedisplay();
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



/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);

	//draw the sceneGraph
	SG->draw();

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

	init();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}