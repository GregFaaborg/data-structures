#include "stack.hpp"
#include <cstring>

using namespace std;

// Auxiliary method, you probably find it useful
// Operands are all lower case and upper case characters
bool isOperand(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    else 
        return false;
}

// Auxiliary method, you probably find it useful
int precedence(char c)
{
    if(c == '+' || c == '-')
    {
        return 0;
    }
    if(c == '*' || c == '/')
    {
        return 1;
    }
    if(c == '^')
    {
        return 2;
    }
    return -1;
}


int main()
{
    freopen("input_infix2postfix.txt", "r", stdin);
    string input;
    string solution;
    int line_counter = 0;
    int topcheck;
    int infixcheck;
    while(cin >> solution)
    {
        cin >> input;
        cout<<input<<endl;
        Stack<char> stack;
        string result;
        //The input file is in the format "expected_solution infix_expression", where expected_solution is the infix_expression in postfix format

            
        for(int i=0; i<input.length(); ++i)
        {
            //stack.display();
            topcheck=precedence(stack.top());
            infixcheck=precedence(input[i]);
            // WRITE CODE HERE to store in 'result' the postfix transformation of 'input'
            if(isOperand(input[i]))    
            {
                result+=input[i];
                /*
                if(input[i]=='(')
                {
                    //cout<<stack.top()<<endl;
                    
                    stack.push(input[i]);                    
                }
                else if(input[i]==')')
                {
                    //cout<<stack.top()<<" ";
                    while(stack.top()!='(')
                    {
                        result+=stack.top();
                        stack.pop();
                    
                    }
                    if(stack.top()=='(')
                    {
                        stack.pop();
                    }
                    

                }
                */
            }
                else if(input[i] == '(')
                {
                    stack.push(input[i]);
                }
                else if(input[i] == ')')
                {
                    while(stack.top() != '(')
                    {
                        result+=stack.top();
                        stack.pop();
                    }
                    stack.pop();
                }
                //*,+,-,/
                else
                {
                    while(stack.size() > 0 && stack.top() != '(' && infixcheck <= topcheck)
                    {
                        result+=stack.top();
                        stack.pop();
                    }
                    stack.push(input[i]);
                }
                /*
                else if(stack.size()==-1)
                {
                    stack.push(input[i]);
                }
                */
                /*
                else if(infixcheck>=topcheck)
                {
                    stack.push(input[i]);
                }
                */
                /*
                else 
                {
                    if(stack.top()!='(')
                    {    
                        result+=stack.top();
                        stack.pop();
                        stack.push(input[i]);
                        //cout<<stack.top()<<endl;
                    }
                    *else
                    {
                        stack.pop();
                    }*/
                //}
                /*
            */
            //}
           /// else //operands
            //{
            //    result+=input[i];
            //}    
        }
            
        // You need to do some extra stuff here to store in 'result' the postfix transformation of 'input'
        while(stack.size() > 0)
        {
            
            if(stack.top()!='(')
            {
                result+=stack.top();
                stack.pop();
            }
            
           /* else
            {
                stack.pop();
            }
            */
            //result+=stack.top();
            //stack.pop();        
        }
        // Checking whether the result you got is correct
        if(solution == result)
        {
            cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
        }
        else
        {
            cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
        }
        line_counter++;
    }
}

