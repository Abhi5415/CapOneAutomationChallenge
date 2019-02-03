#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

bool isMultiline = false;

struct Data
{
  int totalLines;
  int singleLines;
  int multiLines;
  int blocks;
  int todo;
};

struct Lang
{
  string singleLine;
  string openMulti;
  string closeMulti;
  int type;
  // 1 - for different commenting
  // 2 - for same commenting
};

bool hasPreceeding(string line, int index)
{
  // cout << line;
  if (index == 0)
    return false;
  index--;
  while (index != 0)
  {
    if (line[index] != ' ')
      // cout << " - true" << endl;
      return true;

    index--;
  }
  // cout << " - false" << endl;
  return false;
}

int checkValidIndex(string line, string commentType)
{
  vector<int> quotes;
  int occurence = 0;

  while (line.find("\"", occurence) != string::npos)
  {
    int val = (line.find("\"", occurence));
    quotes.push_back(val);
    occurence = line.find("\"", occurence);
    occurence++;
  }
  occurence = 0;
  int openQuote = 0;

  if (quotes.size() > 0)
  {
    while (line.find(commentType, occurence) != string::npos)
    {
      if (line.find(commentType, occurence) < quotes.at(openQuote) || line.find(commentType, occurence) > quotes.at(openQuote + 1))
      {
        return occurence;
      }
      openQuote += 2;
      if (quotes.size() < openQuote + 2)
        break;

      occurence = line.find(commentType, occurence);
      occurence++;
    }
    return INT_MAX;
  }
  if (line.find(commentType) != string::npos)
  {
    return line.find(commentType);
  }
  else
  {
    return INT_MAX;
  }
}

void countCommentDif(string line, Data &info, stack<int> &comments, Lang lang)
{
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  int indexOfMulti = checkValidIndex(line, lang.openMulti);
  int indexOfSingle = checkValidIndex(line, lang.singleLine);
  int indexOfCloseMulti = checkValidIndex(line, lang.closeMulti);

  if (indexOfMulti < indexOfSingle)
  {
    if (comments.top() != 1)
    {
      comments.push(1);
      info.blocks++;
      cout << line << endl;
      if (checkValidIndex(line, "TODO") < INT_MAX)
        info.todo++;
    }
    info.multiLines++;
  }

  else if (indexOfCloseMulti < indexOfSingle)
  {
    if (comments.top() == 1)
    {
      comments.pop();
      info.multiLines++;
    }
  }

  else if (comments.top() == 1)
  {
    info.multiLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }
  //
  else if (indexOfSingle < indexOfMulti && indexOfSingle < indexOfCloseMulti)
  {
    info.singleLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }

  else
  {
    return;
  }
}

void countCommentSame(string line, Data &info, stack<int> &comments, Lang lang)
{
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  int index = checkValidIndex(line, lang.singleLine);

  if (index < INT_MAX)
  {
    if (comments.top() == 1)
    {
      comments.push(1);
      info.multiLines++;
      return;
    }
    else
    {
      if (!hasPreceeding(line, index))
      {
        comments.push(1);
      }
      info.singleLines++;
    }
  }
  else if (comments.top() == 1)
  {
    comments.pop();
    if (comments.top() == 1)
    {
      info.multiLines++;
      info.singleLines--;
      info.blocks++;
    }
    comments.push(0);
  }
}

void printResults(Data &info)
{
  cout << "Total # of lines: " << info.totalLines << endl;
  cout << "Total # of comment lines: " << info.singleLines + info.multiLines << endl;
  cout << "Total # of single line comments: " << info.singleLines << endl;
  cout << "Total # of comment lines within block comments: " << info.multiLines << endl;
  cout << "Total # of block line comments:" << info.blocks << endl;
  cout << "Total # of TODO’s: " << info.todo << endl;
}

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

int main(int argc, char *argv[])
{

  cout << "Please specify the file to check in: ";
  string inputFile;
  cin >> inputFile;

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
