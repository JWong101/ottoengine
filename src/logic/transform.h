#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <vector>
#include <shared_ptr>
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
/**
 * Stores positional data
 *      pos
 *      rot
 *      scale
 * 
 * Also manages parents and children
 **/

class Transform {
private:
    GameObject *gameObject;
    bool isDirty;
    glm::mat4x4 worldToLocalMatrix;
public:
    //variables
    std::shared_ptr<Transform> parent;
    std::vector<std::shared_ptr<Transform>> children;


};


#endif