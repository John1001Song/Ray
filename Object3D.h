//
//  Object3D.h
//  Ray
//
//  Created by Jinyue Song on 2015-11-26.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

#ifndef Object3D_h
#define Object3D_h

enum Shape {
    Sphere, Cube, Cone, Torus, Cylinder, Teapot, Tetrahedron, Octahedron, Dodecahedron, Icosahedron
};

class Object3D{
public:
    //default constructor
    Object3D();
    
    //constructor
    Object3D(Shape shape);
    
    //deconstructor
    ~Object3D();
    
    //Object ID
    int ObjectID;
    
    //Object position
    float pos[3];
    
    //Object Orientation
    float orient[3];
    
    //Object scale for x, y, z
    float scale[3];
    
    //Object material for amb, dif, spec, shiny
    float* material[4];
    
    //Object type or called Shape
    Shape shape;
    
    //Bounding volumn infor
    float boundVetx[8][3];
    
};


#endif /* Object3D_h */
