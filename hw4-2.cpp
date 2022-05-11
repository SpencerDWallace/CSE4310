// g++ -o clique hw4-2.cpp
#include <cstdio>
#include <vector>
using namespace std;

int graph[]={//1   2   3   4   5   6   7   8   9  10
               1,  0,  0,  1,  1,  0,  0,  1,  1,  1, //1
               0,  1,  1,  0,  1,  0,  1,  0,  1,  0, //2
               0,  1,  1,  0,  1,  0,  1,  0,  1,  0, //3
               1,  0,  0,  1,  1,  0,  0,  1,  0,  0, //4
               1,  1,  1,  1,  1,  0,  1,  0,  1,  1, //5
               0,  0,  0,  0,  0,  1,  0,  0,  1,  0, //6
               0,  1,  1,  0,  1,  0,  1,  0,  1,  1, //7
               1,  0,  0,  1,  0,  0,  0,  1,  0,  1, //8
               1,  1,  1,  0,  1,  1,  1,  0,  1,  0, //9
               1,  0,  0,  0,  1,  0,  1,  1,  0,  1 //10
};

const int num_v = 10;
vector<int> sol;

void print_graph()
{
  printf("\n");
  for(int i = 0; i < num_v; i++)
    {
      for(int j = 0; j < num_v; j++)
        {
          (graph[i*num_v + j] == -1)
            ? printf("%d ", 0)
            : printf("%d ", graph[i*num_v + j] );
        }
      printf("\n");
    }
  printf("\n");

};

int calc_bound()
{
  int tallies[num_v] = {0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < num_v; i++)
    {
      int cur_tally = 0;
      for(int j = 0; j < num_v; j++)
      {
        int cur_index = i*num_v + j;
        if(graph[cur_index] == 1)
          cur_tally++;
      }
      for(int s = 0; s <= cur_tally; s++)
        tallies[s]++;
    }
  int largest_com = 0;
  for(int i = 0; i < num_v; i++)
    {
      if(tallies[i] >= i)
        largest_com = i;
    }
  printf("bound is: %d\n", largest_com);
  return largest_com;

};

void eliminate(int index)
{
  for(int i = index; i < num_v*num_v; i+=num_v)
    graph[i] = -1;
  for(int i = index*num_v; i < (index*num_v) + num_v; i++)
    graph[i] = -1;
};

void swap_and_remove(int index)
{
  int temp = sol[sol.size() - 1];
  sol[sol.size() - 1] = sol[index];
  sol[index] = temp;
  sol.pop_back();
};

int calc_bound_of_index(int index)
{
  int bound_of_index = 0;
  for(int i = index*num_v; i < (index*num_v)+num_v; i++){
    if(graph[i] == 1)
      bound_of_index++;
  }
  return bound_of_index;
};

bool check_clique()
{
  for(int i = 0; i < sol.size(); i++)
    {
      int vertex = sol[i] - 1;
      for(int j = 0; j < sol.size(); j++)
        {
          int offset = sol[j] - 1;
          if(i != j)
            if(graph[i*num_v + offset] == 0)
              return false;
        }
    }
  return true;
}

void clique(int bound)
{
  for(int i = 0; i < num_v; i++)
    {
      int low_bound = num_v;
      int low_bound_index = 0;
      for(int j = 0; j <  num_v; j++)
        {
          if(graph[j*num_v + j] == -1)
            continue;

          if(calc_bound_of_index(j) < low_bound){
            low_bound = calc_bound_of_index(j);
            low_bound_index = j;
          }
        }

      if(!check_clique()){
        printf("solution with %d has bound %d, checking solutions without %d\n", low_bound_index+1, low_bound, low_bound_index+1);
        eliminate(low_bound_index);
        swap_and_remove(low_bound_index);
      }
      else{
        printf("click found with bound %d\n", low_bound);
        print_graph();
        return;
      }
    }
};


int main(){
  for(int i = 0; i < 10; i++)
    sol.push_back(i+1);

  clique(calc_bound());

  printf("Vertices in solution are\n");
  for(int i = 0; i < sol.size(); i++)
    printf("%d ", sol[i]);
  printf("\n");

  return 0;
}
