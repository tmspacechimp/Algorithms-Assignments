// https://www.spoj.com/problems/CMEXPR/
#include <iostream>
#include <stack>
#include <set>
using namespace std;

bool includesPlusOrMinus(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '-' || s[i] == '+')
        {
            return true;
        }
    }
    return false;
}

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int priority(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string infix)
{
    stack<char> s;
    string postfix;
    for (int i = 0; i < infix.length(); i++)
    {
        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
        {
            postfix += infix[i];
        }
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                char temp = s.top();
                postfix += temp;
                s.pop();
            }
            if (s.top() == '(')
            {
                s.pop();
            }
        }
        else if (isOperator(infix[i]))
        {
            if (s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                if (priority(infix[i]) > priority(s.top()))
                {
                    s.push(infix[i]);
                }
                else
                {
                    while ((!s.empty()) && (priority(infix[i]) <= priority(s.top())))
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

string postfixToInfix(string postfix)
{

    stack<string> s;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (!isOperator(postfix[i]))
        {
            string op(1, postfix[i]);
            s.push(op);
        }
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            if (postfix[i] == '+')
            {
                s.push(op2 + postfix[i] + op1);
            }
            if (postfix[i] == '-')
            {
                set<char> ops;
                int k = 0;
                for (int j = 0; j < op1.size(); j++)
                {
                    if (op1[j] == '(')
                        k++;
                    if (op1[j] == ')')
                        k--;
                    if (k == 0 && (op1[j] == '+' || op1[j] == '-' || op1[j] == '*' || op1[j] == '/'))
                    {
                        ops.insert(op1[j]);
                    }
                }
                if (ops.find('+') != ops.end() || ops.find('-') != ops.end() )
                {
                    op1 = "(" + op1 + ")";
                }
                s.push(op2 + postfix[i] + op1);
            }
            if (postfix[i] == '*')
            {
                set<char> ops;
                int k = 0;
                for (int j = 0; j < op1.size(); j++)
                {
                    if (op1[j] == '(')
                        k++;
                    if (op1[j] == ')')
                        k--;
                    if (k == 0 && (op1[j] == '+' || op1[j] == '-' || op1[j] == '*' || op1[j] == '/'))
                    {
                        ops.insert(op1[j]);
                    }
                }
                if (ops.find('+') != ops.end() || ops.find('-') != ops.end())
                {
                    op1 = "(" + op1 + ")";
                }
                ops.clear();
                k = 0;
                for (int j = 0; j < op2.size(); j++)
                {
                    if (op2[j] == '(')
                        k++;
                    if (op2[j] == ')')
                        k--;
                    if (k == 0 && (op2[j] == '+' || op2[j] == '-' || op2[j] == '*' || op2[j] == '/'))
                    {
                        ops.insert(op2[j]);
                    }
                }
                if (ops.find('+') != ops.end() || ops.find('-') != ops.end())
                {
                    op2 = "(" + op2 + ")";
                }
                s.push(op2 + postfix[i] + op1);
            }
            if (postfix[i] == '/')
            {
                set<char> ops;
                int k = 0;
                for (int j = 0; j < op2.size(); j++)
                {
                    if (op2[j] == '(')
                        k++;
                    if (op2[j] == ')')
                        k--;
                    if (k == 0 && (op2[j] == '+' || op2[j] == '-' || op2[j] == '*' || op2[j] == '/'))
                    {
                        ops.insert(op2[j]);
                    }
                }
                if (ops.find('+') != ops.end() || ops.find('-') != ops.end())
                {
                    op2 = "(" + op2 + ")";
                }
                if (op1.size() == 1)
                {
                    s.push(op2 + postfix[i] + op1);
                }
                else
                {
                    s.push(op2 + postfix[i] + "(" + op1 + ")");
                }
            }
        }
    }
    return s.top();
}
int main()
{

    string infix, postfix, ans;
    int n;
    cin>>n;
    for (int i = 0; i < n; i++)
    {

    cin >> infix;
   // infix = "((((((l)/n))*b))/n-(((w*((o))-((((m-((s))))))))/c*((((((m/(((((n))-((((((i/(((((((e)*n))/(i-k))-a-((t)))/w+(((u))))*(((((x-b)-(f))*(e)))*k)+n/((w*(((y))))))))*((y))+(v+r*n))/(o)-(m)*r))))))))))))))";
    //ans = "l/n*b/n-(w*o-(m-s))/c*m/(n-((i/(((e*n/(i-k)-a-t)/w+u)*(x-b-f)*e*k+n/(w*y))*y+v+r*n)/o-m*r))";
    postfix = infixToPostfix(infix);
    //cout << postfix << endl;
    infix = postfixToInfix(postfix);
    cout << infix << endl;
   // if (ans == infix)
    //    cout << 1 << endl;
    }
    return 0;
}
