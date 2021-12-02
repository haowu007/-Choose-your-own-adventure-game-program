#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
#include <map>       //for std::map
#include <set>       //for std::set
#include <sstream>   //for std::stringstream
#include <stack>     //for std::stack
#include <string>    //for std::string
#include <vector>    //for std::vector
/***This class stores the information we read in from a given pageX.txt file ***/
class Page {
 public:
  std::vector<std::string>
      navi_PageNum_vec;  //Each element in our vector stores exactly one NAVIGATION line(before the colon) on the given page
  std::vector<std::string>
      navi_choice_vec;  //Each elemnet in this vector stores the content after the colon in a navigation line
  std::vector<std::string> actual_text_vec;  //The text of this given page
  int result_flag;                           //1 for Win, 2 for lose, 3 for continue

  void print_page();  //print out the content of a page in the format that step1 asked
};

/***This class stores the information that is of further use in step2/3/4 ***/
class Useful_infor {
 public:
  std::map<size_t, std::vector<size_t> >
      adj_map;  //adjacent map ,key = page number, value = page numbers of its neighbours
  std::set<size_t> win_pages_set;  // the page number of all the "WIN" pages
  size_t page_num;
  size_t max_choice_page;  //The maximum page number that appeared in a 'choice' section
  Useful_infor() {
    page_num = 0;
    max_choice_page = 0;
  }
};

bool isPositiveNum(std::string & s);  //returns true if s reprensents a positive integer
bool parseOneChoice(
    Page & page,
    std::string & cur,
    Useful_infor & UI);  //parse one single line corresponding to one choice
int ParsePage(Page & page,
              const char * filename,
              Useful_infor & UI);  //parse a whole page according to the required format
int examine_whole_story(
    char * directory,
    Useful_infor & UI);  //check the format for a directory containing a story
void ReadaStory(
    char * directory_name,
    size_t num_page);  //let user play the story by selecting different chioces
void printStoryDepth(
    char * directory);  //calculate can print the 'story depth' as required in cyoa-step3
void printPath(std::vector<std::pair<size_t, size_t> > & vec);  //print one single path
void FindAllWin(
    char * directory);  //find and print out all paths to the 'WIN' page(s) in a story
