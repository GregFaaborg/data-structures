/*
Greg Faaborg
Homework #4
This program implements heapsort from a given vector as well as supporting inserting elements into the max heap one by one. 
*/
#include "maxheap.hpp"
#include <stdio.h>
#include <iostream>

MaxHeap::MaxHeap() {}
MaxHeap::~MaxHeap() {}

int MaxHeap::size() { 
  return arr.size();
}

int MaxHeap::left(int parent) {
  // left = 2*i + 1
  return (2 * parent) + 1;
}

int MaxHeap::right(int parent) {
  // right = 2*i + 2
  return (2 * parent) + 2;
}

int MaxHeap::parent(int child) {
  // parent = i - 1/2
  return (child - 1)/2;
}

void MaxHeap::insert(int element) {
  //inserts element into vector
  arr.push_back(element);

  //so percolate up starting at the end of the vector
  percolateUp(size() - 1);
}


//EXTRA CREDIT 
/*
void MaxHeap::increase_key(int index, int element)
{
  cout << "Increasing element at index: " <<  index << " which is " << arr[index] << " to be " << element << "." << endl;
  if(element < arr[index])
    cout << "Error unable to increase: Current element is already larger." << endl;
  arr[index] = element;
  while(index > 0 && arr[parent(index)] < arr[index])
  {
    int temp = arr[index];
    arr[index] = arr[parent(index)];
    arr[parent(index)] = temp;
    index = parent(index);
  }
}
*/

int MaxHeap::deleteMax() {
  
  
  //largest is first element in vector
  int largest = arr[0];
  //swap root with last element
  arr[0] = arr.back;

  //remove back element from vector
  arr.pop_back();
  //then percolate down from root
  percolateDown(0);
  return largest;  
}

void MaxHeap::display() {
  vector<int>::iterator it;
  cout << "MaxHeap:- ";
  for(it=arr.begin(); it!=arr.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void MaxHeap::percolateUp(int index) {
  //largest element is last item in vector so percolate it up 
  //so that it does not violate max heap property 
  //of the parent being larger than the children

  //arr[parent(index)] to (child - 1)/2
  if(index && arr[(index - 1)/2] < arr[index])
  {
    //parent is smaller than child so swap
    int temp = arr[index];
    
    //TODO arr[parent(index)] to (child - 1)/2
    arr[index] = arr[(index - 1)/2];
    arr[(index - 1)/2] = temp;

    percolateUp((index - 1)/2);
  } 
}

void MaxHeap::percolateDown(int index) {
 
  //percolate down used for deleting elements in the heap
  //as well as the actual building of the heap 

  //TODO left()index to 
  while((2 * index) + 1 < size())
  {
    //get left and right child indices
    int left_child = (2 * index) + 1;//left(index);
    int right_child = (2 * index) + 2;//right(index);
    int largest = left_child;
    //comparing right and left children 
    if(right_child < size() && arr[right_child] > arr[left_child])
      largest = right_child;  
    //comparing parent to child and if child is bigger swap parent
    if(arr[largest] > arr[index])
    {
      int temp = arr[index];
      arr[index] = arr[largest];
      arr[largest] = temp;
      index = largest;
    }
    else
      index = size();
  }
}

void MaxHeap::buildHeap(vector<int> A,int n) {
  
  //call percolate down starting from internal node
  int i = (n-2)/2;
  while(i >= 0)
  {
    percolateDown(i--);
    
  }
}

void MaxHeap::heapsort(vector<int>& A,int n) {

  //copy A to arr
  arr.clear();
  arr = A;
  int size = n; 

  buildHeap(arr,n);
  while(n > 0)
  {
    //setting the end of the array to contain the largest element in the current heap
    arr[n - 1] = deleteMax();
    n--;
  }

  //arr contains sorted vector so copy elements over to A
  A = arr;
  for(int i = 0; i < size; i++)
  {
    A.push_back(arr[i]);
  }
}
