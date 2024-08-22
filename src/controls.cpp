#include <GLFW/glfw3.h>
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 RotationMatrix = glm::mat4(1.0f);

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}

glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::mat4 getRotationMatrix(){
	return RotationMatrix;
}

glm::vec3 position = glm::vec3( 0, 0, 5 ); 

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 0.1f; 
float mouseSpeed = 1e-5f;

float oLeft = -0.1f;
float oRight = 0.1f;
float oBottom = -0.0f;
float oTop = 0.0f;
float oNear = 0.01f;
float oFar = 100.0f;
float zoom = 5.0f;

float rotation = 0.0f;

static double scrollOffset = 0.0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollOffset += yoffset;
}

void computeMatricesFromInputs(GLFWwindow* window){
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	double xpos, ypos;
	
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, 1024/2, 768/2);

	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// glm::vec3 up = glm::cross( right, direction );
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	
	if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
		// position += direction * deltaTime * speed;
		oTop -= oTop * deltaTime * speed;
		oBottom -= oBottom * deltaTime * speed;
	}
	
	if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
		oTop += oTop * deltaTime * speed;
		oBottom += oBottom * deltaTime * speed;
	}
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
		oRight +=  oRight * deltaTime * speed;
		oLeft -=  oLeft * deltaTime * speed;
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
		oLeft +=  oLeft * deltaTime * speed;
		oRight -=  oRight * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_O ) == GLFW_PRESS){
		oNear += oNear * deltaTime * speed;
		oFar  -= oFar * deltaTime * speed;
		std::cout << "oNear " << oNear << "oFar " << oFar << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_I ) == GLFW_PRESS){
		oNear -= oNear * deltaTime * speed;
		oFar  += oFar * deltaTime * speed;
		std::cout << "oNear " << oNear << "oFar " << oFar << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_Z ) == GLFW_PRESS){
		zoom += (zoom * deltaTime * 2.0f) / 14.0f; 
		std::cout << "zoom " << zoom << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_X ) == GLFW_PRESS){
		zoom -= (zoom * deltaTime * 2.0f) / 14.0f; 
		std::cout << "zoom " << zoom << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_R ) == GLFW_PRESS){
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(rotation+=0.01f), glm::vec3(0.0f, 0.0f, 1.0f));
		if(rotation > 360.0f) {
			rotation = 0.0f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glfwSetScrollCallback(window, scroll_callback);

	// ProjectionMatrix = glm::ortho(oLeft/zoom, oRight/zoom, oBottom/zoom, oTop/zoom, oNear/zoom, oFar/zoom);
	ProjectionMatrix = glm::ortho(-1.0f/zoom, 1.0f/zoom, -1.0f/zoom, 1.0f/zoom, 0.1f/zoom, 100.0f/zoom);
	ViewMatrix = glm::lookAt(
		position,
		position+direction,
		up
	);

	lastTime = currentTime;
}
