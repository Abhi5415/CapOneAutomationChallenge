#include <string>
#include "proccessing.h"

void identifyLanguage(Lang &lang, string inputFile)
{
  string extension = inputFile.substr(inputFile.find_last_of(".") + 1);

  if (extension == "py")
  {
    lang.singleLine = "#";
    lang.type = 2;
  }

  if (extension == "java")
  {
    lang.singleLine = "//";
    lang.openMulti = "/*";
    lang.closeMulti = "*/";
    lang.type = 1;
  }

  if (extension == "js")
  {
    lang.singleLine = "//";
    lang.openMulti = "/*";
    lang.closeMulti = "*/";
    lang.type = 1;
  }
}