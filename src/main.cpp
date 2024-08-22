#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "shader.hpp"
#include "file_handling.hpp"
#include "buffering.hpp"
#include "cleaning.hpp"
#include "controls.hpp"
#include "setup.hpp"

using namespace glm;

// const GLfloat BASE_LAT = 59.2373418; 
// const GLfloat BASE_LON = 17.8365887;

const GLfloat BASE_LAT = 0.0;
const GLfloat BASE_LON = 0.0;


int main(int argc, char** argv){
  if(argv == nullptr){
    std::cerr << "Missing input file flags"<< std::endl;
  }

  GLFWwindow* window = windowSetup();
  if(window == nullptr) {
    std::cerr << "window setup error" << std::endl;
    return -1;
  }

  std::string filename = get_filename(argc, argv);
  std::ifstream file(filename);
  std::vector<GLfloat> coordinates;
  if(file){
    GLfloat iVal; 
    while(file >> iVal){
      coordinates.push_back(iVal);
    }
  } else {
    std::cerr << "Could not open file: " << filename << std::endl;
    return -1;
  }

  normalize_coords(coordinates, BASE_LAT, BASE_LON);

  GLuint vertexbuffer, VertexArrayID;
  draw_triangle(&VertexArrayID, &vertexbuffer, coordinates);

  GLuint programID = LoadShaders("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint UniformColorID = glGetUniformLocation(programID, "uniformcolor"); 


  glm::mat4 test_0 = getProjectionMatrix();
  glm::mat4 test_1 = getViewMatrix();
  glm::mat4 test_2 = getRotationMatrix();
  glm::mat4 test_4 = glm::mat4(1.0f);
  glm::mat4 test_3 = test_4 * 2.0f;// test_2 * test_0 * test_1 * test_4;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      std::cout << test_3[i][j] << " ";
    }
    std::cout << std::endl;
  }

  do {
    glClear( GL_COLOR_BUFFER_BIT );
    glUseProgram(programID);

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs(window);
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    // glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 RotationMatrix = getRotationMatrix();
    glm::mat4 MVP = RotationMatrix * ProjectionMatrix * ViewMatrix;//* ModelMatrix;

    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        std::cout << MVP[i][j] << " ";
      }
      std::cout << std::endl;
    }

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0,
      2,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );

    glUniform3f(UniformColorID, 1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_LINES, 0, coordinates.size()/2);

    glDisableVertexAttribArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while( 
  glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS 
  && glfwWindowShouldClose(window) == 0 
);

  // Cleanup VBO and shader
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);

  return 0;
}
