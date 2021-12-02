#include <algorithm>
#include <cstdlib>
#include <map>
#include <vector>
//ECE590 hw8 Greedy Ferries pseudo code

int DP(std::map<int, int> & lanes,
       //key = 1 for L1, 2 for L2, 3 for L3 ; value = remaining space
       std::vector<int> & cars,
       //this vector stores the length of the cars
       size_t index
       //labels which car is the next in the car sequence
) {
  int current_car_length = cars[index];
  //Find possible choices

  int choose_l1, choose_l2, choose_l3 = -1;
  if (index >= cars.size()) {
    return 0;
  }
  if (lanes[1] >= current_car_length) {
    std::map<int, int> new_map = lanes;
    // make a local copy here because we don't want to change 'lanes':
    // it might be used by the following two if clauses !
    new_map[1] -= current_car_length;
    choose_l1 = DP(lanes, cars, index + 1);
  }
  if (lanes[2] >= current_car_length && lanes[2] != lanes[1]) {
    std::map<int, int> new_map = lanes;
    new_map[2] -= current_car_length;
    choose_l2 = DP(lanes, cars, index + 1);
  }
  if (lanes[3] >= current_car_length && lanes[3] != lanes[2] && lanes[3] != lanes[1]) {
    std::map<int, int> new_map = lanes;
    new_map[3] -= current_car_length;
    choose_l3 = DP(lanes, cars, index + 1);
  }
  return 1 + std::max(std::max(choose_l1, choose_l2), choose_l3);
  //we have our base case incorporated in the above code:
  //if none of the lanes can fit the car, we should return 0
  //and 1+ (-1) is exactly zero.
}
