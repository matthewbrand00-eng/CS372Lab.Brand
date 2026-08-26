#include <iostream>
#include <chrono>
#include <stack>
#include <cstdint>
using namespace std;

void moveDisks(int, stack<int> &, stack<int> &, stack<int>&);
void MoveDisksHelper(stack<int> &, stack<int> &);

int main() {
  for (auto numdisks : {5, 10, 15, 20, 25, 30, 35}) {
      stack<int> source;
      stack<int> dest;
      stack<int> aux;
      cout << "Numdisks: " << numdisks << endl;

      auto start = std::chrono::steady_clock::now();
      moveDisks(numdisks, source, aux, dest);
      auto end = std::chrono::steady_clock::now();

      std::chrono::duration<double> elapsed_seconds = end - start;
      cout << "Elapsed time: " << elapsed_seconds.count()
           << " seconds" << endl;
      cout << "Moved " << numdisks << " disks" << endl;
    }
    return 0;
}

void moveDisks(int num, stack<int> &fromPeg, stack<int> &tempPeg, stack<int> &toPeg) {
  stack<int> *source = &fromPeg;
  stack<int> *auxiliary = &tempPeg;
  stack<int> *destination = &toPeg;
  if (num % 2 == 0) { // Swap in num disks is even.
    swap(destination, auxiliary);
  }
  std::uint64_t numberOfMoves = (std::uint64_t{1} << num) - 1;
  for (int i = num; i >= 1; i--) {
    source->push(i);
  }
  // now do moves:
  for (std::uint64_t i = 1; i <= numberOfMoves; i++) {
    if (i % 3 == 0) {
      MoveDisksHelper(*auxiliary, *destination);
    }
    else if (i % 3 == 2) {
      MoveDisksHelper(*source, *auxiliary);
    }
    else if (i % 3 ==  1) {
      MoveDisksHelper(*source, *destination);
    }
  }
}

void MoveDisksHelper(stack<int> &source, stack<int> &dest) {
  int top1;
  int top2;
  if (source.empty()) {
    top2 = dest.top();
    dest.pop();
    source.push(top2);
  }
  else if (dest.empty()) {
    top1 = source.top();
    source.pop();
    dest.push(top1);
  }
  else if (source.top() > dest.top()) {
    top1 = source.top();
    source.pop();
    top2 = dest.top();
    dest.pop();
    source.push(top1);
    source.push(top2);
  }
  else {
    top2 = dest.top();
    dest.pop();
    top1 = source.top();
    source.pop();
    dest.push(top2);
    dest.push(top1);
  }
}


