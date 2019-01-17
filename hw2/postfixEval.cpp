/*
postfixEval.cpp
Greg Faaborg
evaluates postfix expressions
*/
#include "stack.hpp"

using namespace std;

//function the calculates the last two operand on the stack with the current operator
int calculate(int operand1, char operater, int operand2)
{
    if(operater == '+')
        return operand1 + operand2;
    else if(operater == '-')
        return operand1 - operand2;
    else if(operater == '*')
        return operand1 * operand2;
    else if(operater == '/')
        return operand1 / operand2;
}

int main(){
  freopen("input_postfixEval.txt", "r", stdin);
  string post;
  int solution;
  int line_counter = 0;
  while(cin>>solution){
    cin>>post;
    Stack<int> stack;
    // The input file is in the format "expected_solution postfix_expression"

    for(unsigned int i=0; i<post.length();i++)
    {
        //if the current character is a digit the push it onto the stack
        if(isdigit(post[i]))
        {
            //subtracting '0' to get the actual value of the current chracter
            //ex. '2' - '0' = 2
            //    50 - 48 = 2  
            int operand = post[i] - '0';
            stack.push(operand);
        }
        else if(post[i] == ' ')
        ;
    
        //the charcater is an operator 
        else
        {   
            //pop the top of the stack 
            int operand2 = stack.returnPop();

            //pop the new top of the stack 
            int operand1 = stack.returnPop();
            
            //perform the operation of the current character between the opearnds 
            //in the stack
            int num = calculate(operand1, post[i], operand2);
            //push the calculated value onto the stack
            stack.push(num);
        }      
    }

    // Checking whether the value you calculated is correct ...
    int value = stack.top();

    if(solution == value){
      cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
    }
    line_counter++;
  }
}
