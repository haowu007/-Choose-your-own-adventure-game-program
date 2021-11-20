#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
#include <set>       //for std::set
#include <sstream>   //for std::stringstream
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

  void print_page() {
    std::vector<std::string>::const_iterator it;
    for (it = actual_text_vec.begin(); it != actual_text_vec.end(); ++it) {
      std::cout << *it << std::endl;
    }
    std::cout << std::endl;  //print a blank line
    if (result_flag == 1) {  //The output corresponding to "Win"
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (result_flag == 2) {  //The output corresponding to "Lose"
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {  //The output corresponding to "Continue reading"
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;  //print another blank line
      int i = 1;
      for (it = navi_choice_vec.begin(); it != navi_choice_vec.end(); ++it) {
        std::cout << " " << i++ << ". " << *it << std::endl;
      }
    }
  }
};
