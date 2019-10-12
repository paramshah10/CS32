#include <stack>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

///////////// MAKE SURE YOU CHANGE BACK THE FUNCTION NAMES TO THE ORIGINAL THINGS

string removeSpaces(string infix);
bool evenBrackets(string infix);

int evaluate(string infix, string& postfix, bool& result)
{
	postfix = "";
	infix = removeSpaces(infix);
	if (!evenBrackets(infix))
		return 1;
	stack<char> operatorStack;
	for (int i = 0; i < infix.size(); i++) 
	{
		if (isalpha(infix[i])) 
		{
			if (infix.size() == 1) 
			{
				postfix += infix[i];
				break;
			}
			else 
			{
				if (i == infix.size() - 1) 
				{
					if (infix[i - 1] == '(') 
					{
						return 1;
					}
				}
				else if (i != 0) 
				{

					if (!(infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '(')) 
					{
						return 1;
					}
				}
				else 
				{
					if (!(infix[i + 1] == '!' || infix[i + 1] == '&' || infix[i + 1] == '^' || infix[i + 1] == ')')) 
					{
						return 1;
					}
				}

				postfix += infix[i];
			}
		}
		else if (infix[i] == '(') 
		{
			if (infix.size() == 1) 
			{
				return 1;
			}
			else if (i == infix.size() - 1) 
			{
				return 1;
			}
			else if (i!= 0 && (isalpha(infix[i - 1]))) 
			{
				return 1;
			} 
			else if ( i!= 0 && infix[i - 1] == ')') 
			{
				return 1;
			}
			else if ( i != infix.size()-1 && infix[i+1]==')') 
			{
			
				return 1;
			}
			operatorStack.push(infix[i]);
		}

		else if (infix[i] == ')') 
		{
			if (i == 0) 
			{
				return 1;
			}
			else if (i != infix.size() - 1 && isalpha(infix[i + 1])) 
			{
				return 1;
			}
			while (!operatorStack.empty() && operatorStack.top() != '(') 
			{
		
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			if (!operatorStack.empty()) 
			{
				operatorStack.pop();
			}
		}
		else if (infix[i] == '!') 
		{
			if (i == infix.size() - 1) 
			{
				return 1;
			}
			else if ( i != 0 && isalpha( infix[i - 1])) 
			{
				return 1;
			}
			else if ( i!=0 && infix[i - 1] == ')') 
			{
				return 1;
			}
			operatorStack.push(infix[i]);
		}
		else if (infix[i] == '&') 
		{
			if (i == infix.size() - 1 || i == 0) 
			{
				return 1;
			}
			else if (!(isalpha(infix[i - 1])|| infix[i-1] == ')')) 
			{
				return 1;
			}
			while (!operatorStack.empty() && operatorStack.top() == '!') 
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
		}
		else if (infix[i] == '^') 
		{
			if (i == infix.size() - 1 || i == 0) 
			{
				return 1;
			}
			else if (!(isalpha(infix[i - 1]) || infix[i-1] == ')')) 
			{
				
				return 1;
			}
			while (!operatorStack.empty() && (operatorStack.top() == '&' || operatorStack.top() == '!')) 
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
		}
		else 
		{
			return 1;
		}
	}

	while (!operatorStack.empty()) 
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	stack<bool> operandStack;
	for (int i = 0; i < postfix.size(); i++) 
	{
		if (postfix[i] == 'T')
			operandStack.push(true);

		else if (postfix[i] == 'F')
			operandStack.push(false);

		else 
		{
			if (postfix[i] == '!') 
			{
				bool operand = operandStack.top();
				operandStack.pop();
				operandStack.push(!operand);
			}
			else if (postfix[i] == '^') 
			{
				bool operand2 = operandStack.top();
				operandStack.pop();
				bool operand1 = operandStack.top();
				operandStack.pop();
				if (operand1)
				{
					if (!operand2)
						operandStack.push(true);
					else
						operandStack.push(false);
				}
				else
				{
					if (operand2)
						operandStack.push(true);
					else
						operandStack.push(false);
				}
			}
			else 
			{
				bool operand2 = operandStack.top();
				operandStack.pop();
				bool operand1 = operandStack.top();
				operandStack.pop();
				operandStack.push(operand1 && operand2);
			}
		}
	}
	if (!operandStack.empty()) 
	{
		result = operandStack.top();
		operandStack.pop();
		return 0;
	}
	return	1;
}

string removeSpaces(string infix) 
{
	string res = "";
	for (int i = 0; i < infix.size(); i++) 
	{
		if (infix[i] != ' ') 
		{
			res += infix[i];
		}
	}
	return res;
}

bool evenBrackets(string infix) 
{
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < infix.size(); i++) 
	{
		if (infix[i] == '(') 
			count1++;
		else if (infix[i] == ')') 
			count2++;
	}
	return count1 == count2;
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate("TTF()!", pf, answer) == 1);
	cout << "Passed all tests" << endl;
}