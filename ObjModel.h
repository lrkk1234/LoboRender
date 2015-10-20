#ifndef _OBJMODEL_H
#define _OBJMODEL_H

#include <iostream>
#include <vector>
#include <assert.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "../common/tiny_obj_loader.h"

enum OBJ_BUFERS
{
   OBJ_VERTICES = 0,
   OBJ_NORMALS,
   OBJ_INDICES,
   NUM_OBJ_BUFFERS
};



//================================================================
// ObjModel
//================================================================

class ObjModel 
{

public:

   ObjModel(){}
   ObjModel(const char * filename);
   ~ObjModel();
   void render();


private:

   int num_indices_;
   GLuint vao_;
   std::vector <GLuint> buffers_;

};

#endif

