#include "Precompiled.h"
#include "Helper.h"


#include <GL/glew.h>

namespace GLUtils {




//----------------------------------------------------------------------------



bool CHelper::CheckForError(void)
{
  GLenum errCode;
  std::string errString;

  if ((errCode = glGetError()) != GL_NO_ERROR) {
    errString = std::string((const char *)(gluErrorString(errCode)));
    //assert(false);
    std::cout << "OpenGL Error: " <<  errString << std::endl;
    return true;
  }
  return false;
}







}