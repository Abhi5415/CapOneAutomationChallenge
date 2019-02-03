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

struct language
{
  string singleLine;
  string openMulti;
  string closeMulti;
};

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

void countComment(string line, Data &info, stack<int> &comments)
{
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  // 1 - open multiline comment
  int indexOfMulti = checkValidIndex(line, "/*");
  int indexOfSingle = checkValidIndex(line, "//");
  int indexOfCloseMulti = checkValidIndex(line, "*/");

  // cout << line << endl;
  // cout << "Multi: " << indexOfMulti << " || Close Multi: " << indexOfCloseMulti << " || Single: " << indexOfSingle << endl
  //      << endl;

  if (indexOfMulti < indexOfSingle)
  {
    if (comments.top() != 1)
    {
      comments.push(1);
      info.blocks++;
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

void printResults(Data &info)
{
  cout << "Total # of lines: " << info.totalLines << endl;
  cout << "Total # of comment lines: " << info.singleLines + info.multiLines << endl;
  cout << "Total # of single line comments: " << info.singleLines << endl;
  cout << "Total # of comment lines within block comments: " << info.multiLines << endl;
  cout << "Total # of block line comments:" << info.blocks << endl;
  cout << "Total # of TODO’s: " << info.todo << endl;
}

int main(int argc, char *argv[])
{

  cout << "Please specify the file to check in: ";
  string inputFile;
  cin >> inputFile;

  ifstream file;
  file.open(inputFile);

  stack<int> comments;
  comments.push(0);
  Data info;
  info.totalLines = 0;
  info.singleLines = 0;

  string line;
  while (getline(file, line))
  {
    info.totalLines++;
    countComment(line, info, comments);
  }
  printResults(info);
  file.close();
}
