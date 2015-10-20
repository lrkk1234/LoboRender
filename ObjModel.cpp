#include "ObjModel.h"


//================================================================
// constructor
//================================================================

ObjModel::ObjModel(const char * filename)
{
   std::string inputfile = filename; //"../../assets/obj/stanford_dragon.obj";
   std::vector<tinyobj::shape_t> shapes;

   std::string err = tinyobj::LoadObj(shapes, inputfile.c_str());

   if (!err.empty()) {
      std::cerr << err << std::endl;
      exit(1);
   }

   std::cout << std::endl;
   std::cout << "OBJ LOADED: " << inputfile << std::endl;
   std::cout << "# of shapes : " << shapes.size() << std::endl;

   for (size_t i = 0; i < shapes.size(); i++) {
      printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
      printf("shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
      assert((shapes[i].mesh.indices.size() % 3) == 0);
      printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
      assert((shapes[i].mesh.positions.size() % 3) == 0);
      printf("shape[%ld].normals: %ld\n", i, shapes[i].mesh.normals.size());
      assert((shapes[i].mesh.normals.size() % 3) == 0);
   }

   // generate VAOS 
   glGenVertexArrays(1, &vao_);

   // generate VBO
   buffers_.resize(NUM_OBJ_BUFFERS, 0);
   glGenBuffers(NUM_OBJ_BUFFERS, &buffers_[0]);

   //bind dragon vao
   glBindVertexArray(vao_);

   //vertices
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, buffers_[OBJ_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), 
                &shapes[0].mesh.positions[0], GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

   //normals
   glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, buffers_[OBJ_NORMALS]);
   glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.normals.size() * sizeof(float), 
                &shapes[0].mesh.normals[0], GL_STATIC_DRAW);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

   //indices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[OBJ_INDICES]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), 
                &shapes[0].mesh.indices[0], GL_STATIC_DRAW);

   num_indices_ = shapes[0].mesh.indices.size();

   // unbind dragon vao
   glBindVertexArray(0);

}

//================================================================
// destructor
//================================================================

ObjModel::~ObjModel()
{

}

//================================================================
// render
//================================================================

void ObjModel::render()
{
   glBindVertexArray(vao_);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[OBJ_INDICES]);
   glDrawElements(GL_TRIANGLES, num_indices_,GL_UNSIGNED_INT, 0);

}

