#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Drawable.h"

/************************************************************************/
/* methods                                                              */
/************************************************************************/
void parseCommandLine(int argc, char **argv);

//camera
static bool sWireframe = false;
static double sLastUpdate = 0; //calculate time between each frame
char * ReadShaderFile(std::string const & file) {

    FILE *fp = nullptr;
    char *content = nullptr;

    size_t count = 0;

    if (file.c_str() != nullptr) {
        fp = fopen(file.c_str(), "r");

        if (fp != nullptr) {

            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);

            if (count > 0) {
                content = (char *)malloc(sizeof(char)* (count + 1));
                if (content != 0) {
                    count = fread(content, sizeof(char), count, fp);
                    content[count] = '\0';
                }
            }
            fclose(fp);
        }
    }
    return content;
}


//debugs shader
std::string PrintShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    std::string result;

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        std::string s(infoLog);
        result = std::string(s.begin(), s.end());
        printf("%s\n", infoLog);
        free(infoLog);
    }

    return result;
}

void PrintProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}



bool CheckQuery(int const & query, int const & id, std::string const & topic)
{
    //query status
    if (query == GL_FALSE) {
        std::cout << "----------" << topic << "------------------- " << std::endl;
        std::string result = PrintShaderInfoLog(id);

        std::string caption = "Error in " + std::string(topic.begin(), topic.end()) + ":";

        result = "Error in " + std::string(topic.begin(), topic.end()) + ":\n" + result + "\n" + "Application is closed.";

        //this is a windows method. If compiled with a different operating system, comment/replace this method
        //MessageBox(NULL, result.c_str(), caption.c_str(), MB_ICONEXCLAMATION | MB_ICONWARNING);
        //
        // tom: wstrings are bad with stdout. Quickest fix is to to use std::string
        printf("%s", result.c_str());

        assert(false); //shader could not be compiled- look at console for more infos
        return false;
    }

    return true;
}





/************************************************************************/
/* glut callbacks                                                       */
/************************************************************************/
//release all allocated resources
static void FinalizeApplication(void)
{
    //normally, shader and shader files have to be deleted
    //however, to simplify this program, we leave releasing resources to the operating system
}

// render loop
static void Display();

// size of window changed
static void Reshape(int w, int h);

//create geometry
static void createGeometry(void);

void addCubeVertices(std::vector<vec3> &vertexArray);

void addDrawable(Drawable* drawable);

void draw();