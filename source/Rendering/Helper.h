#pragma once

#include "Defines.h"

namespace GLUtils {


  class CHelper
  {
  public:    
    
    //Error Handling - returns true, if an error occurred
    GLUTILS_API static bool CheckForError(void);
  private:
    CHelper() {}  //static class - forbidden
    ~CHelper(){}  //static class - forbidden
  };
  


  //exception class for shader collection errors
  class CFailure : public std::runtime_error {
  public:
    GLUTILS_API CFailure(std::string const & msg) :std::runtime_error(msg) {}
  };
} //namespace Utils