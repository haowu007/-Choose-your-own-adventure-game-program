#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
#include <map>       //for std::map
#include <set>       //for std::set
#include <sstream>   //for std::stringstream
#include <stack>     //for std::stack
#include <string>    //for std::string
#include <vector>    //for std::vector
class Page {
 public:
  std::vector<std::string>
      navi_PageNum_vec;  //Each element in our vector stores exactly one NAVIGATION line(before the colon) on the given page
  std::vector<std::string>
      navi_choice_vec;  //Each elemnet in this vector stores the content after the colon in a navigation line
  std::vector<std::string> actual_text_vec;  //The text of this given page
  int result_flag;                           //1 for Win, 2 for lose, 3 for continue

  void print_page();
};

bool isPositiveNum(std::string & s);
bool parseOneChoice(Page & page,
                    std::string & cur,
                    std::map<size_t, std::vector<size_t> > & adj_map,
                    size_t page_num,
                    size_t & max_choice_page);
int ParsePage(Page & page,
              const char * filename,
              std::map<size_t, std::vector<size_t> > & adj_map,
              size_t page_num,
              size_t & max_choice_page);
int examine_whole_story(char * directory,
                        std::map<size_t, std::vector<size_t> > & adj_map,
                        std::set<size_t> & win_pages_set);
void ReadaStory(char * directory_name, size_t num_page);
void printStoryDepth(size_t num_page, std::map<size_t, std::vector<size_t> > & adj_map);
void printPath(std::vector<std::pair<size_t, size_t> > & vec);
void FindAllWin(char * directory);
