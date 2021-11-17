
#include "story.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Story::Story() : win(0), lose(0), pageNum(0) {
}
void Story::GetPageNum(char * directory) {
  int i = 1;
  while (true) {
    std::stringstream ss, ssfile;
    ss.str(directory);
    std::string str = ss.str();
    ssfile << "." << ss.str() << "/page" << i << ".txt";
    //const char * filename = ssfile.str().c_str();
    char * filename = NULL;  //
    std::string tem = ssfile.str();
    filename = (char *)tem.c_str();  //
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
  pageNum = i - 1;
  for (size_t i = 0; i < pageNum; i++) {
    BeReferencedVec.push_back(0);
  }
}

void Story::CheckOnePage(const char * filename) {
  Page p;
  p.ReadIn(filename);
  p.ParsePage();
  for (size_t i = 0; i < p.GetVecRefer().size(); i++) {
    if (p.GetVecRefer()[i] > BeReferencedVec.size()) {
      std::cerr << filename << ": This page refered at least one page that not exists! "
                << std::endl;
      exit(EXIT_FAILURE);
    }
    // if this page referred other pages, FLAG the page index referred to 1.
    BeReferencedVec[p.GetVecRefer()[i] - 1] = 1;
  }
  if (p.GetWin() == true) {
    win++;
  }
  if (p.GetLose() == true) {
    lose++;
  }
  vecPages.push_back(p);
}

void Story::CheckPages(char * directory) {
  for (size_t i = 1; i <= pageNum; i++) {
    std::stringstream ss, ssfile;
    ss.str(directory);
    std::string str = ss.str();
    ssfile << "." << ss.str() << "/page" << i << ".txt";
    const char * filename = NULL;
    std::string tem = ssfile.str();
    filename = tem.c_str();
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
  if (win < 1) {
    std::cerr << "There should be at least one WIN in story! " << std::endl;
    exit(EXIT_FAILURE);
  }
  if (lose < 1) {
    std::cerr << "There should be at least one LOSE in story! " << std::endl;
    exit(EXIT_FAILURE);
  }
}

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
      while (true) {
        //int cin_error = 0;
        //size_t num;  //page number of a page
        std::cin >> num;
        //should check if it is a int (by.good()??)
        if (num < 1 || num > vecPages[i].GetVecChoices().size()) {
          //cin_error = 1;  ///
          std::cout << "That is not a valid choice, please try again\n";
        }
        else {
          break;
        }
      }
      i = vecPages[i].GetVecRefer()[num - 1] - 1;
    }
  }
}
