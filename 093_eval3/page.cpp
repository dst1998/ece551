#include "page.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Page::Page() : choiceNum(0), win(false), lose(false) {
}

Page::~Page() {
}
//Read input file into a vector
void Page::ReadIn(const char * filename) {
  //check if filename is valid ("page"+int+".txt")
  const char * p = filename;
  if (*p++ != 'p') {
    std::cerr << "Invalid filename! no p" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 'a') {
    std::cerr << "Invalid filename! no a" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 'g') {
    std::cerr << "Invalid filename! no g" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 'e') {
    std::cerr << "Invalid filename! no e" << std::endl;
    exit(EXIT_FAILURE);
  }
  //the first char after 'e' should be 1-9
  if (*p < '1' || *p > '9') {
    std::cerr << "Invalid filename! no 1-9" << std::endl;
    exit(EXIT_FAILURE);
  }
  p++;
  while (*p != '\0') {
    if (*p >= '0' && *p <= '9') {
      p++;
    }
    else {
      break;
    }
  }
  if (*p++ != '.') {
    std::cerr << "Invalid filename! no ." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 't') {
    std::cerr << "Invalid filename! no t" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 'x') {
    std::cerr << "Invalid filename! no x" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (*p++ != 't') {
    std::cerr << "Invalid filename! no t" << std::endl;
    exit(EXIT_FAILURE);
  }
  //check if file is valid
  std::ifstream infile(filename);
  if (infile.fail()) {
    std::cerr << "Can't open file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  //get the content into vec is chechking is successfully done above
  std::string str;
  while (!infile.eof()) {
    std::getline(infile, str);
    vec.push_back(str);
  }
}

//Parsing the text before and behind '#'
void Page::ParsePage() {
  size_t TextStartNum = 0;  //the row index that text starts.
  //get Textstartnum
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i][0] == '#') {
      break;
    }
    else {
      TextStartNum += 1;
    }
  }
  TextStartNum += 1;
  //if first line is WIN
  if (vec[0].compare("WIN") == 0) {
    win = true;
    if (TextStartNum != 2) {
      std::cerr << "Wrong: More than one navigation sentence!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //if first line is LOSE
  else if (vec[0].compare("LOSE") == 0) {
    lose = true;
    if (TextStartNum != 2) {
      std::cerr << "Wrong: More than one navigation sentence!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //else: first line is a choice in the page
  else {
    //get the number of choices if choices exist on the page.
    choiceNum = TextStartNum - 1;
    //get the choices vector
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices.push_back(vec[i]);
    }
    //reformat the choice vector
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices[i] = RewriteChoice(vecChoices[i], i);
    }
  }
  //get the text part of the page
  for (size_t i = TextStartNum; i < vec.size(); i++) {
    vecText.push_back(vec[i]);
  }
}

//reformat the choice line
std::string Page::RewriteChoice(std::string str, size_t i) {
  std::string::size_type pos;  //the position (index) of ":"
  //exit if can't find ':' in the choice line
  if ((pos = str.find(':')) == str.npos) {
    std::cerr << "Can't find ':' in the choice line." << std::endl;
    exit(EXIT_FAILURE);
  }
  //exit if nothing in front of ':' in the choice line
  if (pos == 0) {
    std::cerr << "Nothing in front of ':' in the choice line." << std::endl;
    exit(EXIT_FAILURE);
  }
  for (size_t j = 0; j < pos; j++) {
    if (str[j] < '0' || str[j] > '9' || str[0] == '0') {
      std::cerr << "Not a valid integer!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //substr(a,b):index a included, index b not included.
  size_t index;
  std::stringstream ssnum;
  ssnum << str.substr(0, pos);  //put string into sstream
  ssnum >> index;
  vecRefer.push_back(index);  //add pages index being referred by this page into vecRefer.
  std::stringstream ssout;
  ssout << " " << i + 1 << ". " << str.substr(pos + 1);
  return ssout.str();
}

//print the text of the page.
void Page::TextPrint() {
  for (size_t i = 0; i < vecText.size(); i++) {
    std::cout << vecText[i] << std::endl;
  }
}

//print if win
void Page::WinPrint() {
  std::cout << "Congratulations! You have won. Hooray!\n";
}

//print if lose
void Page::LosePrint() {
  std::cout << "Sorry, you have lost. Better luck next time!\n";
}

//print choices
void Page::ChoicesPrint() {
  std::cout << "What would you like to do?\n"
            << "\n";
  for (size_t i = 0; i < vecChoices.size(); i++) {
    std::cout << vecChoices[i] << std::endl;
  }
}

//integrate the functions above, to make test program clear
void Page::ReadOnePage(const char * filename) {
  ReadIn(filename);
  ParsePage();
  TextPrint();
  //if no choices,and first line is WIN
  if (win == true) {
    WinPrint();
  }
  //if no choices,and first line is LOSE
  else if (lose == true) {
    LosePrint();
  }
  //else:have choices in the page
  else {
    ChoicesPrint();
  }
}
//get the value of win(private).
bool Page::GetWin() {
  return win;
}
//get the value of lose(private).
bool Page::GetLose() {
  return lose;
}
//get the value of vecRefer(private).
const std::vector<size_t> Page::GetVecRefer() {
  return vecRefer;
}
//get the value of vecChoices(private).
const std::vector<std::string> Page::GetVecChoices() {
  return vecChoices;
}
