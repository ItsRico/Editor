#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void insert(vector<string>& source, ifstream& coms);
void replace(vector<string>& source, ifstream& coms);
void find(vector<string>& source, ifstream& coms);
void deleteLine(vector<string>& source, ifstream& coms);
void erase( vector<string>& source, ifstream& coms);
void copyPaste( vector<string>& source, ifstream& coms);
void move(vector<string>& source, ifstream& coms);


int main(int argc, char** argv)
{
  string line;

  vector <string> edits;
  vector <string> source;
  vector <string> comV;

  ifstream com(argv[2]);
  ifstream src(argv[1]);
  ifstream com2(argv[2]); 

  while ( getline(src, line ) )
  {
     source.push_back(line);
  }//

  while ( getline(com2, line ) )
  {
     comV.push_back(line);
  }//

 int count = comV.size();
 
 while(count != 0)
 {
 
    switch (com.peek())
    {
      case 'I':
        insert(source, com);
        break;
      case 'R':
        replace(source, com);
        break;
      case 'F':
        find(source, com);
        break;
      case 'D':
        deleteLine(source, com);
        break;
      case 'E':
        erase(source, com);
        break;
      case 'C':
        copyPaste(source, com);
        break;
      case 'M':
        move(source, com);
        break; 
    }//

    count--;
 }//

    ofstream res(argv[3]);
    //source.erase(source.begin() + source.size() );

 for(vector<string>::iterator itr = source.begin(); itr != source.end(); itr++) 
     res << *itr << endl; 
  
}//

void move(vector<string>& source, ifstream& coms)
{
  int startLine;
  int endLine;
  int destLine;
  int lineNum = 0;
  vector<string> lines;
  vector<string> deepCopy;
  string line; 
  getline(coms, line, ' ') >> startLine;
  getline(coms, line, ' ') >> endLine; 
  getline(coms, line, ' ') >> destLine;
  
  vector<string>::iterator itr;

  for(itr = source.begin(); itr != source.end(); itr++) 
  {
    if( lineNum >= startLine && lineNum <= endLine)
    {
      lines.push_back(*itr);
    }//

      lineNum++;
  }//
  
  source.erase(source.begin() + startLine, source.begin() + endLine + 1);
 
  if(destLine < startLine) 
    source.insert(source.begin() + destLine  , lines.begin(), lines.end());
  else //
  {
    source.insert(source.begin() + destLine - 1  , lines.begin(), lines.end());
  }//
}//

void copyPaste( vector<string>& source, ifstream& coms)
{
  int startL;
  int endL;
  int destL;
  string line;
  vector<string> linesToCopy;
  int lineNum = 0;

  getline(coms, line, ' ') >> startL;
  getline(coms, line, ' ') >> endL; 
  getline(coms, line, ' ') >> destL;

  vector<string>::iterator itr;

  for(itr = source.begin(); itr != source.end(); itr++) 
  {
    if( lineNum >= startL && lineNum <= endL)
    {
      linesToCopy.push_back(*itr);
    }//

      lineNum++;
  }//

 source.insert(source.begin() + destL, linesToCopy.begin(), linesToCopy.end() );

}//
  


void erase( vector<string>& source, ifstream& coms)
{
  int lineCount = 0;
  string line;
  getline(coms, line, ' ');
  getline(coms, line, '\n');
  size_t pos;
  bool flag = false;
  vector<string>::iterator itr = source.begin();
  size_t size = line.size();
  
  for(itr = source.begin(); itr!= source.end(); itr++)
  {
    pos  = (*itr).find(line);

    while(pos != (*itr).npos)
    {
      
      (*itr).erase((*itr).begin() + pos, ((*itr).begin() + size + pos));
      pos  = (*itr).find(line);
      flag = true;
    }//
  
    if(flag && (*itr).find_first_not_of(' ') == string::npos)
    {
      source.erase(itr);
      itr--;
      flag = false;
    }//

    flag = false;
    lineCount++;
  }//
}//


void deleteLine(vector<string>& source, ifstream& coms)
{
  int lineStart;
  int lineEnd;
  string line2;
  
  getline(coms, line2, ' ') >> lineStart;
  getline(coms, line2, ' ') >> lineEnd;
  getline(coms, line2, '\n');
  
  
  vector<string>::iterator itr = source.begin();

  if(lineStart == lineEnd)
  {
    source.erase(source.begin() + lineStart , source.begin() + lineEnd + 1);
 
    return;
  }//

  source.erase(source.begin() + lineStart, source.begin() + lineEnd + 1);

}//

void insert(vector<string>& source, ifstream& coms)
{
  int lineNum;
  int colNum;
  int lineCount = 0;
  string line2;
  string space;
  getline(coms, line2, ' ') >> lineNum;
  getline(coms, line2, ' ') >> colNum;
  getline(coms, space, ' ');
  getline(coms, line2, '\n');
 
  vector<string>::iterator itr = source.begin();

  for(itr = source.begin(); itr!= source.end(); itr++)
  {

    if(lineCount == lineNum)
    {

      (*itr).insert(colNum, line2);
      break;
    }//

  lineCount++;
 }//
   
}//

void replace(vector<string>& source, ifstream& coms)
{
  int lineNum;
  int colStart;
  int colEnd;
  int lineCount = 0;
  string line;
  string space;
  getline(coms, line, ' ') >> lineNum;
  getline(coms, line, ' ') >> colStart;
  getline(coms, line, ' ') >> colEnd;
  getline(coms, space, ' ');
  getline(coms, line, '\n');

  vector<string>::iterator itr = source.begin();

  for(itr = source.begin(); itr!= source.end(); itr++)
  {

    if(lineCount == lineNum)
    {
      (*itr).replace((*itr).begin() + colStart , (*itr).begin() + colEnd, line);
      break;
    }//

  lineCount++;
 }//

}//


void find(vector<string>& source, ifstream& coms)
{
  int lineNum = 0;
  size_t found;

  string line; 
  getline(coms, line, ' ');
  getline(coms, line, '\n');
  cout << line << ' ';
  vector<string>::iterator itr = source.begin();
  
  for(itr = source.begin(); itr != source.end(); itr++)
  { 
    found = (*itr).find(line);

    if( found != (*itr).npos)
    {  
      cout << lineNum << " ";
    }//

    lineNum++;
  }//

 cout << endl; 
}//
