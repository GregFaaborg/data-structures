/*
infix2postfix.cpp 
Greg Faaborg
This program transforms infix expressions to postfix expressions using a stack data structure
*/
#include "stack.hpp"

using namespace std;

// Operands are all lower case and upper case characters
//checks whether the currenrt character is a letter
bool isOperand(char c){

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    else 
        return false;

}

//setting the precedence of each operation + and - being the lowest 
//followed by * and / followed by ^.
int precedence(char c)
{
  if(c == '+' || c == '-'){
    return 0;
  }
  if(c == '*' || c == '/'){
    return 1;
  }
  if(c == '^'){
    return 2;
  }
  return -1;
}


int main(){
  freopen("input_infix2postfix.txt", "r", stdin);
  string input;
  string solution;
  int line_counter = 0;
  while(cin >> solution){
    cin >> input;
    Stack<char> stack;
    string result;
    //The input file is in the format "expected_solution infix_expression", where expected_solution is the infix_expression in postfix format

    
    for(unsigned int i=0; i<input.length(); ++i)
    {
        //if is a-zA-Z
        if(isOperand(input[i]))
        {
            //append it to the result string
            result = result + input[i];
        }
        //if opening parenthesis
        else if(input[i] == '(')
        {
            //push ( onto stack
            stack.push(input[i]);
        }
        //if closing parentheis
        else if(input[i] == ')')
        {
            //while we havent reached the (
            while(stack.top() != '(')
            {
                //add the top of the stack to the result string and pop the top of the stack 
                result = result + stack.returnPop();
            }           
            //remove (    
            stack.pop();  
        }
        //is operator (+,-,*,/,^)
        else if(!isOperand(input[i])) 
        {
            /*while the stack is not empty and the top is not ( and the precedence
            of the current character is less than or equal to the precedence of the top of the stack 
            */
            while(stack.size() > 0 && stack.top() != '(' && precedence(input[i]) <= precedence(stack.top()))
            {
                //add the top of the stack to the result string and pop the top 
                result = result + stack.returnPop();
            }
            //push the current character to the stack
            stack.push(input[i]);
        }
    }
   
    //pop everything from the stack and and add it the result string 
    while(stack.size() > 0)
    {
        result = result + stack.returnPop();
    }
     

    // Checking whether the result you got is correct
    if(solution == result){
      cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
    }
    line_counter++;
  }
}
