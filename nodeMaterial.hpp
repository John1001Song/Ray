//
//  nodeMaterial.hpp
//  Ray
//
//  Created by Jinyue Song on 2015-12-01.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

#ifndef nodeMaterial_hpp
#define nodeMaterial_hpp

#include <stdio.h>
#include "node.h"

enum MaterialType{
    CyanPlastic,//cyan plastic
    Gold,//gold
    Jade,
    YellowRubber,
    Random
};

class NodeMaterial: public Node{
public:
    NodeMaterial(MaterialType whatType); //constructor
    MaterialType materialType;
    
    virtual void nodeSpecificCodeDown();
    
};

#endif /* nodeMaterial_hpp */
