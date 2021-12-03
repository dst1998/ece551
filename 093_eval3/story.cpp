
#include "story.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
//default constructor
Story::Story() : win(0), lose(0), pageNum(0) {
}
// get the number of total pages and initialize the BeReferencedVec.
void Story::GetPageNum(char * directory) {
  int i = 1;  //i:page number
  while (true) {
    //create directory+filename
    std::stringstream ss, ssfile;
    ss.str(directory);  //std::string
    ssfile << ss.str() << "/page" << i << ".txt";
    char * filename = NULL;
    std::string tem = ssfile.str();
    filename = (char *)tem.c_str();
    //open each file,fail if page1 not exists.
    //stop while loop if a page(except page1) cannot be found.
    std::ifstream infile(filename);
    if (infile.fail()) {
      if (i == 1) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
      }
      else {
        break;
      }
    }
    i++;
  }
  //get the number of pages in whole story.
  pageNum = i - 1;
  //initialize every page's referenced mark to 0 (no page is referered now)
  for (size_t i = 0; i < pageNum; i++) {
    BeReferencedVec.push_back(0);
  }
}
//check errors of one page, exit if have any error.
void Story::CheckOnePage(const char * filename) {
  Page p;
  p.ReadIn(filename);
  p.ParsePage();
  //check if any error exists in this page.
  for (size_t i = 0; i < p.GetVecRefer().size(); i++) {
    //check if this page refers a page that not exists.
    if (p.GetVecRefer()[i] > BeReferencedVec.size()) {
      std::cerr << filename << ": This page refered at least one page that not exists! "
                << std::endl;
      exit(EXIT_FAILURE);
    }
    //if this page referred other pages, FLAG the page index referred to 1.
    BeReferencedVec[p.GetVecRefer()[i] - 1] = 1;
  }
  //add 1 to the number of win in story if win appears on this page.
  if (p.GetWin() == true) {
    win++;
  }
  //add 1 to the number of lose in story if win appears on this page.
  if (p.GetLose() == true) {
    lose++;
  }
  //pushback this page to make up the story.
  vecPages.push_back(p);
}
//check all pages of the story.
void Story::CheckPages(char * directory) {
  for (size_t i = 1; i <= pageNum; i++) {
    //create directory+filename
    std::stringstream ss, ssfile;
    ss.str(directory);  //std::string
    ssfile << ss.str() << "/page" << i << ".txt";
    const char * filename = NULL;
    std::string tem = ssfile.str();
    filename = tem.c_str();
    //check each page
    CheckOnePage(filename);
  }
  //check if every page is referred by other pages, no checking on page1,so i start from 1.
  for (size_t i = 1; i < pageNum; i++) {
    if (BeReferencedVec[i] == 0) {
      std::cerr << "At least one page is not referred by other pages in story! "
                << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //exit if no win in story.
  if (win < 1) {
    std::cerr << "There should be at least one WIN in story! " << std::endl;
    exit(EXIT_FAILURE);
  }
  //exit if no lose in story.
  if (lose < 1) {
    std::cerr << "There should be at least one LOSE in story! " << std::endl;
    exit(EXIT_FAILURE);
  }
}
//read whole story after checking.
void Story::ReadStory() {
  size_t i = 0;
  while (i < pageNum) {
    //first: show the page.
    vecPages[i].TextPrint();
    //if no choices,and first line is WIN,exit
    if (vecPages[i].GetWin() == true) {
      vecPages[i].WinPrint();
      break;
    }
    //if no choices,and first line is LOSE,exit
    else if (vecPages[i].GetLose() == true) {
      vecPages[i].LosePrint();
      break;
    }
    //else:have choices in the page
    else {
      vecPages[i].ChoicesPrint();
      size_t num;  //page number of a page
      //get the correct page number of next step
      while (true) {
        std::cin >> num;
        if (!std::cin.good()) {
          std::cin.clear();
          std::string badinput;
          std::cin >> badinput;
          std::cout << "That is not a valid choice, please try again\n";
        }
        else {
          //num = atoi(c);
          //std::cout << "num=" << num << std::endl;  //
          //check if it is a int or a valid int for choices
          if (num < 1 || num > vecPages[i].GetVecChoices().size()) {
            std::cout << "That is not a valid choice, please try again\n";
          }
          else {
            break;
          }
        }
      }
      //jump to the page according to the choices given by audience
      i = vecPages[i].GetVecRefer()[num - 1] - 1;
    }
  }
}

void Story::GetDepth() {
  //initialize every page's depth to 0
  for (size_t i = 0; i < pageNum; i++) {
    vecDepth.push_back(0);
  }
  Story::DepthHelper(0, 0);
  for (size_t i = 0; i < pageNum; i++) {
    if (vecDepth[i] == 0 && i > 0) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << ":" << vecDepth[i] << std::endl;
    }
  }
}

void Story::DepthHelper(size_t index, int depth) {
  // if this page is a leaf node, we can know its depth.
  if (vecPages[index].GetVecRefer().size() == 0) {
    if (vecDepth[index] == 0 || vecDepth[index] > depth) {
      vecDepth[index] = depth;
    }
    return;
  }
  //else: recursion, get the depth when return.
  for (size_t i = 0; i < vecPages[index].GetVecRefer().size(); i++) {
    DepthHelper(vecPages[index].GetVecRefer()[i] - 1, depth + 1);
  }
  if (vecDepth[index] == 0 || vecDepth[index] > depth) {
    vecDepth[index] = depth;
  }
}

void Story::GetPath() {
  Story::GetPathHelper(0);
  //print
  if (vecAllPaths.size() == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  else {
    for (size_t i = 0; i < vecAllPaths.size(); i++) {
      for (size_t j = 0; j < vecAllPaths[i].size(); j++) {
        std::cout << vecAllPaths[i][j];
      }
      std::cout << std::endl;
    }
  }
}

void Story::GetPathHelper(size_t index) {
  // if this page is a leaf node.
  if (vecPages[index].GetVecRefer().size() == 0) {
    if (vecPages[index].GetWin()) {
      std::stringstream ss;
      ss << index + 1 << "(win)";
      vecPath.push_back(ss.str());
      vecAllPaths.push_back(vecPath);
      vecPath.erase(vecPath.begin() + vecPath.size() - 1);
      return;
    }
    else {
      return;
    }
  }
  //else: recursion, get the depth when return.
  std::stringstream ss;
  for (size_t i = 0; i < vecPages[index].GetVecRefer().size(); i++) {
    if (std::find(vecVisit.begin(), vecVisit.end(), vecPages[index].GetVecRefer()[i]) !=
        vecVisit.end()) {
      continue;
    }  //This returns a bool (true if present, false otherwise).
    std::stringstream ss;
    ss << index + 1 << "(" << i + 1 << "),";
    vecPath.push_back(ss.str());
    vecVisit.push_back(vecPages[index].GetVecRefer()[i]);
    GetPathHelper(vecPages[index].GetVecRefer()[i] - 1);

    vecPath.erase(vecPath.begin() + vecPath.size() - 1);
    vecVisit.erase(vecVisit.begin() + vecVisit.size() - 1);
  }
}
