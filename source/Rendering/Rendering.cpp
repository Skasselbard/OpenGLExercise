#include "Precompiled.h"
#include "Rendering.h"

//vector and matrix calculation
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/constants.hpp>
#include "glm/gtc/matrix_inverse.hpp"

//texture wrapper
#include "Sphere.h"
#include "Cube.h"
#include "ShaderCompiler.h"
#include "Sky.h"



/************************************************************************/
/* globals                                                              */
/************************************************************************/

GLint shaderProgramID = 0;
glm::mat4 viewMatrix = glm::mat4(1.0);

const float moveModifier = 0.1;//to scale movementspeed
glm::vec3 position = glm::vec3(1.0,0.0,10.0);

GLuint vertexArrayObject = 0;
const char *vertexShaderPath;
const char *fragmentShaderPath;
std::vector<Drawable*> objectList;

/************************************************************************/
/* methods                                                             */
/************************************************************************/

/**
 * parses the command line
 * parameters:
 *  -v => vertexShaderPath
 *  -f => fragmentShaderPath
 */
void parseCommandLine(int argc, char **argv) {
  for (int i = 0; i < argc ; i++) {
    if (i + 1 != argc) {
      if (strcmp(argv[i],"-v") == 0) {
        vertexShaderPath = argv[i + 1];
      }
      if (strcmp(argv[i],"-f") == 0) {
        fragmentShaderPath = argv[i + 1];
      }
    }
  }
}


//evaluates letter-keys
void KeyPressed(unsigned char key, int x, int y)
{
  switch (key) {
  case 'a': 
  case 'b':
  default:
    ;
  }
}


//evaluates letter-keys
void KeyReleased(unsigned char key, int x, int y)
{
}

//evaluates special keys
void KeyPressed(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_PAGE_UP:{
          position = position + glm::vec3(0.0,1.0*moveModifier,0.0);
          break;
        }
        case GLUT_KEY_PAGE_DOWN:{
          position = position + glm::vec3(0.0,-1.0*moveModifier,0.0);
          break;
        }
        case GLUT_KEY_LEFT:{
          position = position + glm::vec3(-1.0*moveModifier,0.0,0.0);
          break;
        }
        case GLUT_KEY_RIGHT:{
          position = position + glm::vec3(1.0*moveModifier,0.0,0.0);
          break;
        }
        case GLUT_KEY_UP:{
            position = position + glm::vec3(0.0,0.0,-1.0*moveModifier);
            break;
        }
        case GLUT_KEY_DOWN:{
            position = position + glm::vec3(0.0,0.0,1.0*moveModifier);
            break;
        }
        //...
        default:
    ;
    }
}

//evaluates special keys
void KeyReleased(int key, int x, int y)
{
}

//evaluates mouse input
void MouseKey(int button, int state, int x, int y)
{
}

//evaluates mouse input
void MouseMove(int x, int y)
{
}

/************************************************************************/
/* scene updating and rendering                                         */
/************************************************************************/
void RenderScene() 
{
    //clear DepthBuffer
    glClear(GL_DEPTH_BUFFER_BIT);
    //toggle between wire frame and opaque view - for debugging purposes
    glPolygonMode(GL_FRONT_AND_BACK, sWireframe ? GL_LINE : GL_FILL);
    viewMatrix = glm::lookAt(
            position,
            glm::vec3((float)0.5,(float)0.5,(float)0.0), // and looks at the origin
            glm::vec3((float)0.0,(float)1.0,(float)0.0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    //renders triangle
    glUseProgram(shaderProgramID);

    GLint uniformLocation(0);
    uniformLocation = glGetUniformLocation(shaderProgramID, "viewMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &viewMatrix[0][0]);

    draw();
    glUseProgram(0);
}



/************************************************************************/
/* glut callbacks														                            */
/************************************************************************/

void Display() 
{
  //define color that is used to clear the screen
  glClearColor(0.7f, 0.7f, 0.7f, 1.0);

  //clear the current color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //render scene
  RenderScene();

  //show rendered content
  glutSwapBuffers();

  //force a redisplay for continues animation
  glutPostRedisplay();
}


void Reshape(int width, int height)
{
    //resets view port
    glViewport(0, 0, width, height);

    //create ProjectionMatrix
    float aspectRatio = static_cast<float>(width)/static_cast<float>(height);
    glm::mat4 projectionMatrix = glm::perspective(35.0f, aspectRatio, 1.0f, 100.0f);//blindly copied values from https://stackoverflow.com/questions/8115352/glmperspective-explanation
    GLint uniformLocation(0);

    glUseProgram(shaderProgramID);
    uniformLocation = glGetUniformLocation(shaderProgramID, "projectionMatrix");
    glUniformMatrix4fv(uniformLocation, 1, false, &projectionMatrix[0][0]);
    glUseProgram(0);

}


#include <regex>

/************************************************************************/
/* application main                                                     */
/************************************************************************/

int main(int argc, char* argv[]) 
{
    parseCommandLine(argc, argv);

    //init glut
    glutInit(&argc, argv);
    glutInitContextVersion(3, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE);
    glutInitContextFlags(GLUT_CORE_PROFILE);

    //create window
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("OpenGL Program");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyPressed);
    glutKeyboardUpFunc(KeyReleased);
    glutSpecialFunc(KeyPressed);
    glutSpecialUpFunc(KeyReleased);
    glutMouseFunc(MouseKey);
    glutMotionFunc(MouseMove);
    glutCloseFunc(FinalizeApplication);	// on window close -> term app

    //fix Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //activate DepthBuffer
    glEnable(GL_DEPTH_TEST);

    //init glew
    GLenum glew_err = glewInit();
    if (glew_err != GLEW_NO_ERROR) {
    std::cerr << "failed to initialize OpenGL extension wrapper: " << (const char*)glewGetErrorString(glew_err) << std::endl;
    return EXIT_FAILURE;
    }

    shaderProgramID = ShaderCompiler::compileShader(vertexShaderPath,fragmentShaderPath);
    setUpObjects();

    //enter main loop
    glutMainLoop();
    return EXIT_SUCCESS;
}

void addDrawable(Drawable* drawable) {
    objectList.push_back(drawable);
}

void draw() {
    for (int i = 0; i < objectList.size(); i++){
        objectList[i]->draw();
    }
}

void setUpObjects() {
    Sky* sky = new Sky();
    sky->setShaderProgramm(shaderProgramID);
    Cube* cube = new Cube();
    cube->setShaderProgramm(shaderProgramID);
    cube->scale(1,1,1);
    addDrawable(sky);
    addDrawable(cube);

}







