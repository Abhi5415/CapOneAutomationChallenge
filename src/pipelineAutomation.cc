#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include "proccessing.h"

using namespace std;

int main(int argc, char *argv[])
{

  string inputFile = argv[1];
  ifstream file;
  file.open(inputFile);
  if (!file)
  {
    cerr << "Unable to open file " << inputFile << endl;
    exit(1);
  }

  // setup
  Lang lang;
  identifyLanguage(lang, inputFile);
  stack<int> comments;
  comments.push(0);
  Data info;
  string line;

  if (lang.type == 1)
  {
    while (getline(file, line))
    {
      info.totalLines++;
      countCommentDif(line, info, comments, lang);
    }
  }
  else
  {
    while (getline(file, line))
    {
      info.totalLines++;
      countCommentSame(line, info, comments, lang);
    }
  }

  printResults(info);
  file.close();
}
