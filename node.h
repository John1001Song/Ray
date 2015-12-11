#ifndef __NODE_H__	//guard against cyclic dependancy
#define __NODE_H__

//Node Class.
//should act as a template class for other sub-types of
//Nodes

#include <vector>
#include "structs.h"
using namespace std;

extern int getID();

//if you add more derived classes
//add the types here
enum NodeType{
	root,
	group,
	transformation,
    material,
	model
};

class Node{
public:
	Node();	//constructor

	NodeType nodeType;
	bool isDrawable;
	int ID;
    int flag_frame;
	vector<Node*> *children;
	Node* parent;
	int currentChild;
    Vector3D nodePos3D;
    Vector4D nodePos4D;
    
	void draw();
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
};

#endif