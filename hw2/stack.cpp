#include "stack.hpp"

using namespace std;


//pushes values onto the stack
template<class T>
void Stack<T>::push(T c){

    //if maxsize is reached output error
    if(topIndex > MAXSIZE)
        cout << "MAXSIZE reached unable to push to stack." << endl;
    else
    {
        //add 1 to topIndex and assign value of c to be array element
        arr[++topIndex] = c;
    }
}

//returns the top value of the stack
template<class T>
T Stack<T>::top()
{
    //if the stack is not empty return current array value
    if(topIndex >= 0)
        return arr[topIndex];
    else
    {
        cout << "STACK IS EMPTY NOTHING" << endl;
        return -1;
    }
}

//removes the top element of the stack
template<class T>
void Stack<T>::pop()
{
        //if stack is not empty subtract 1 from top index 
        if(topIndex < 0)
            cout << "STACK IS EMPTY NOTHING TO POP" << endl;
        else
            arr[--topIndex];
}

//returns the current value of the top of the stack and decrements the topIndex value by 1
template<class T>
T Stack<T>::returnPop(){

    //if the stack is not empty set the return value to be the top of the stack then decrement by 1
    if(topIndex >= 0)
    {
        T stackTop = arr[topIndex];
        --topIndex;
        return stackTop;
    }
    else
    {
        cout << "NOTHING TO POP STACK IS EMPTY" << endl;
        return -1;
    }
}

//returns the size of the stack
template<class T>
int Stack<T>::size(){

    //if there is something in the stack add 1 to topIndex value and return it otherwise return 0
    if(topIndex >= 0)
        return topIndex + 1;
    else
        return 0;
}

//displays the values of the stack
template<class T>
void Stack<T>::display(){

    if (topIndex < 0)
        cout << "STACK IS EMPTY, NOTHING TO DISPLAY";
    else
    {
        for(int i = 0; i <= topIndex; i++)
        {
            cout << arr[i] << endl;
        }
    }

}

template class Stack<char>;
template class Stack<int>;
