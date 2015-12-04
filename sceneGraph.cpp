#include "sceneGraph.h"
#include "node.h"
#include "node.cpp"
#include <stdio.h>

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
	printf("scene graph init done\n");
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
	currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i){
	if (i < currentNode->children->size() && i >= 0)
		currentNode = currentNode->children->at(i);
	else
		printf("child out of range");
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
    //add our parent to our child node
    node->parent = currentNode;
    //now lets add it to our children!
    currentNode->children->push_back(node);
}



//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
    //this function is to delete the model-node(like cube, cone or ball).
    //Other non-model nodes (like transformation or material) are stored in current model-node vector *children
    //non-model nodes are used to move the object or change object's apperance etc.
    
    //get current node's non-model node's size. For example it is about how many steps the object translated, what material is used on the object etc
    int childrenSize = currentNode->children->size();
    //delete those operations, which are stored in vector *children
    for (int i = 0; i < childrenSize; i++) {
        delete currentNode->children->at(i);
    }
    //last step to delete the current node
    delete currentNode;
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}