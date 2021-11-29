#include <map>
#include <set>
#include <vector>

#include "cyoa.cpp"

void printstoryDepth(char * directory) {
  std::map<size_t, std::vector<size_t> > adj_map;
  std::set<size_t> win_pages_set;
  size_t num_page = examine_whole_story(directory, adj_map, win_pages_set);

  std::vector<size_t> depth_vector(
      num_page - 1, 0);  //because the returned num_page is 2+the real pages number
  std::vector<size_t> visited_vector(num_page - 1, 0);
  std::stack<std::pair<size_t, size_t> > page_stack;  //first=page second=depth
  //Now we are ready to do DFS for the given adj_map
  std::pair<size_t, size_t> p(1, 0);
  page_stack.push(p);
  while (!page_stack.empty()) {
    size_t cur_page = page_stack.top().first;
    size_t cur_depth = page_stack.top().second;
    page_stack.pop();

    std::vector<size_t> cur_neighbour = adj_map[cur_page];
    for (std::vector<size_t>::iterator it = cur_neighbour.begin();
         it != cur_neighbour.end();
         it++) {
      if (depth_vector[*it] == 0 || depth_vector[*it] > 1 + cur_depth) {
        depth_vector[*it] = cur_depth + 1;  //renew the current depth
      }
      if (visited_vector[*it] == 0) {
        std::pair<size_t, size_t> pp(*it, 1 + cur_depth);
        page_stack.push(pp);
        visited_vector[*it] = 1;
      }
    }
  }

  for (size_t i = 1; i < depth_vector.size(); i++) {
    std::cout << "Page " << i;
    if (depth_vector[i] == 0 && i != 1) {
      std::cout << " is not reachable" << std::endl;
    }
    else {
      std::cout << ":" << depth_vector[i] << std::endl;
    }
  }
}
