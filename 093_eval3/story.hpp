#include <vector>

#include "page.hpp"
class Story {
 private:
  int win;
  int lose;
  size_t pageNum;
  std::vector<int> BeReferencedVec;
  std::vector<Page> vecPages;
  std::vector<int> vecDepth;
  std::vector<std::string> vecPath;
  std::vector<std::vector<std::string> > vecAllPaths;
  std::vector<size_t> vecVisit;

 public:
  //default constructor
  Story();
  // get the number of total pages and initialize the BeReferencedVec.
  void GetPageNum(char * directory);
  //check errors of one page, exit if have any error.
  void CheckOnePage(const char * filename);
  //check all pages of the story.
  void CheckPages(char * directory);
  //read whole story after checking.
  void ReadStory();
  //get the depth of each page.
  void GetDepth();
  //depth helper function, used in GetDepth.
  void DepthHelper(size_t index, int depth);
  //get all the non-cycle paths of the story.
  void GetPath();
  void GetPathHelper(size_t index);
};
