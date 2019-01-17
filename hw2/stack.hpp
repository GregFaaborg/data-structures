/*
Header file for stack.cpp
Greg Faaborg
*/
#include<iostream>
#include<string>
//#include<cmath>
#include<cctype>
#include<cstdio>

// Ideally this would not be a huge number, you could also use a vector
#define MAXSIZE 100000

using namespace std;

template<class T>
class Stack{

private:
    T arr[MAXSIZE]; // the actual stack
    int topIndex;   // index of the top element
  
public:
    Stack(){
        topIndex = -1; // constructor
    };
    ~Stack(){};     // destructor

    void push(T c); // push c to the stack
    T top();        // return the top element in the stack
    void pop();     // removes the top element in the stack;
    T returnPop();  // remove the top element in the stack and returns it 
    int size();     // returns the size of the stack
    void display(); // display the stack to stdout
};
