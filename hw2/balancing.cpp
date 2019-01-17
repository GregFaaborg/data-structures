/*
balancing.cpp
Greg Faaborg
Determines whether an expresion has balanced parentheses, square brackets, or curly brackets.
*/
#include "stack.hpp"

using namespace std;

//function to determine if the current character is ),],}
bool closer(char closing)
{
    if(closing == ')' || closing == ']' || closing == '}')
        return true;
    else
        return false;
}

//function to determine if current charcter is (,[,{
bool opener(char opening)
{
    if(opening == '(' || opening == '[' || opening == '{')
        return true;
    else 
        return false;
}

//function to determine whether the top of the stack an opening charcater and the current charcater is the matching closing character
bool match(char opening, char closing)
{   
    if(opening == '[' && closing == ']')
        return true;
    else if(opening == '(' && closing == ')')
        return true;
    else if(opening == '{' && closing == '}')
        return true;
    //no match found
    else
        return false;
}

int main(){
  freopen("input_balanced.txt", "r", stdin);
  string expression,result;
  int line_counter;
  while(cin >> result){
    cin >> expression;
    Stack<char> stack;
    bool isBalanced = true;
    bool solution;
    if(result[0] == 'Y' || result[0] == 'y'){
      solution = true;
    }else{
      solution = false;
    }

    for(unsigned int i=0; i<expression.length(); ++i)
    {
        //if (,[, or { then push onto the stack
        if(opener(expression[i]))
            stack.push(expression[i]);
        //if is ),], or } 
        else if(closer(expression[i]))
        {
            //if there is nothing else in the stack or if there is something in the stack and the stack top does not match with the closing character then set isBalanced = fasle and break out of loop
            if(stack.size() == 0 || !match(stack.top(),expression[i]))
            {
                isBalanced = false;
                break;
            }
            //top does match with the closing charcter and stack is not empty then pop the top off of the stack
            else
                stack.pop();
        }
    }
    //if there is nothing in the stack and isBalanced is already true (because it could be empty which would make isBalanced false from the if condition above) then the expression is balanced
    if(stack.size() == 0 && isBalanced == true)
        isBalanced = true;
    //the expression is not balanced
    else 
        isBalanced = false;


    // checking isBalanced for the correct value
    if(isBalanced == solution){
      cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
    }
    line_counter++;
  }
}
