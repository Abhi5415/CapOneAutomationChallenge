#include <string>
#include "proccessing.h"

void identifyLanguage(Lang &lang, string inputFile)
{
  string extension = inputFile.substr(inputFile.find_last_of(".") + 1);

  // To add a language that supports both multiline and single line comments, update the fields as shown below
  // if (extension == "{file-extension}")
  // {
  //   lang.singleLine = "{single-line-symbol}";
  //   lang.openMulti = "{start-multiline-symbol}";
  //   lang.closeMulti = "{close-multiline-symbol}";
  //   lang.type = 1;
  // }

  // To add a language that supports only single line comments, update the fields as shown below
  // if (extension == "{file-extension}")
  // {
  //   lang.singleLine = "{single-line-symbol}";
  //   lang.type = 2;
  // }

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