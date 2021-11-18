//This is the source file for step2
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  std::string directory_name(argv[1]);
  size_t num_page = examine_whole_story(argv[1]);
  //////NOW we begin the story

  std::string nextpage;
  std::string users_choice;
  nextpage = "1";
  size_t users_num = 0;
  //int cur_page=1;
  int flag_valid_page = 0;
  std::set<size_t> pages_set;
  while (1) {
    Page page;
    std::string prefix = directory_name;
    std::string cur_page_name = prefix += "/page";  //"story1/page"
    cur_page_name += nextpage;                      //"storyt1/page3"
    cur_page_name += ".txt";                        //"story1/page3.txt"
    flag_valid_page = ParsePage(page, cur_page_name.c_str(), pages_set);
    print_page(page);
    //   std::cout << "********************************" << std::endl;
    if (flag_valid_page == 2 || flag_valid_page == 3) {
      return EXIT_SUCCESS;
    }
    else {
      int validflag = 0;
      while (validflag == 0) {
        std::cin >> users_choice;
        users_num = (size_t)atoi(users_choice.c_str());
        if (!isPositiveNum(users_choice) || users_num > num_page - 2) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
        else {  //if the choice is in current page's permitted choice?
          size_t valid_size = page.navi_PageNum_vec.size();
          if (users_num <= valid_size) {
            validflag = 1;
          }
          if (validflag == 0) {
            std::cout << "That is not a valid choice, please try again" << std::endl;
          }
        }
      }
    }
    nextpage = page.navi_PageNum_vec[users_num - 1];
  }

  return EXIT_SUCCESS;
}
