//This is the source file for step2
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }

  std::string directory_name(argv[1]);
  std::string prefix = directory_name;
  std::string page1_name = prefix += "/page1.txt";
  std::set<size_t> pages_set;
  Page page;
  //  std::cout << "current page name:" << page1_name.c_str() << std::endl;
  int contain_win = 0;
  int contain_lose = 0;
  int flag_valid_page = ParsePage(page, page1_name.c_str(), pages_set);
  if (flag_valid_page == 2) {
    contain_win++;
  }
  if (flag_valid_page == 3) {
    contain_lose++;
  }
  if (flag_valid_page == -1) {  //error handling
    std::cerr << "Page1 not found!!\n";
    exit(EXIT_FAILURE);
  }
  size_t num_page = 2;

  while (flag_valid_page != -1) {
    Page page;
    std::string prefix = directory_name;
    std::string cur_page_name = prefix += "/page";  //"story1/page"
    std::stringstream cur_pagenum;
    cur_pagenum << num_page;
    cur_page_name += cur_pagenum.str();  //"storyt1/page3"
    cur_page_name += ".txt";             //"story1/page3.txt"

    flag_valid_page = ParsePage(page, cur_page_name.c_str(), pages_set);
    if (flag_valid_page == 2) {
      contain_win++;
    }
    if (flag_valid_page == 3) {
      contain_lose++;
    }
    num_page++;
  }
  std::set<size_t>::const_iterator it;
  for (it = pages_set.begin(); it != pages_set.end(); ++it) {
    //   std::cout << "we have page" << *it << "in our pages set!" << std::endl;
  }
  std::set<size_t>::reverse_iterator rever_it = pages_set.rbegin();
  if (*rever_it >= num_page) {  //error handling
    std::cerr << "Page choice went out of valid range!!\n";
    exit(EXIT_FAILURE);
  }
  if (pages_set.count(1) > 0) {  //set contains page number "1"
    if (pages_set.size() != num_page - 2) {
      std::cerr << "At least one page is unreachable!\n";
      exit(EXIT_FAILURE);
    }
  }
  else {  //page 1 is not in our set
    //   std::cout << "The set size is :" << pages_set.size() << std::endl;
    if (pages_set.size() != num_page - 3) {
      std::cerr << "At least one page is unreachable!\n";
      exit(EXIT_FAILURE);
    }
  }
  if (contain_win == 0 || contain_lose == 0) {
    std::cerr << "Missing win or lose page!\n";
    exit(EXIT_SUCCESS);
  }
  //////NOW we begin the story

  std::string nextpage;
  std::string users_choice;
  nextpage = "1";
  size_t users_num = 0;
  //int cur_page=1;
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
