#include <GL/glew.h>
#include "setup.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

GLFWwindow* windowSetup(){
  glewExperimental = true;
  if (!glfwInit()){
	std::cerr << "Failed to initialize glfw" << std::endl;
	throw std::runtime_error("Failed to initialize glfw");
	return nullptr;
  }
  glfwWindowHint(GLFW_SAMPLES, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);

  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
	throw std::runtime_error("Failed to initialize glfw");
	return nullptr;
  }
  
  glfwMakeContextCurrent(window); 
  glewExperimental=true; 
  
  if (glewInit() != GLEW_OK) {
	std::cerr << "Failed to initialize GLEW" << std::endl;
	throw std::runtime_error("Failed to initialize glfw");
	return nullptr;
  }
  
  if(window == nullptr){
	throw std::runtime_error("window nullptr");
	return nullptr;
  }
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwPollEvents();
  glfwSetCursorPos(window, 1024/2, 768/2);
  
  return window;
}
