#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include <string>
#include <vector>
#include "transform.h"

/**
 * Everything in a scene must be a GameObject
 * 
 **/

class GameObject {
protected:
    std::shared_ptr<GameObject> parent;
    std::vector<std::shared_ptr<GameObject>> children;
    std::shared_ptr<Transform> transform;
public:
    //variables
    std::string name;
    

    //methods
    

};

#endif