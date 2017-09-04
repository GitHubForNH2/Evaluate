#ifndef EVALUATE_H
#define EVALUATE_H

#include <string>
#include <stack>
#include <stdlib.h>

using namespace std;

char Precede(char t1,char t2){
    char ret;

    switch (t1)
    {
    case '+':
    case '-':
        if (t2 == '*' || t2 == '/' || t2 == '(')
            ret = '<';
        else ret = '>';
        break;
    case '*':
    case '/':
        if (t2 == '(') ret = '<';
        else ret = '>';
        break;
    case '(':
       switch (t2)
           {  case '#':
                       cout << "Need a bracket!!!" << endl;
                       exit(1);
              case ')':
                ret = '=';
                break;
              default : ret = '<';
           }
           break;
    case ')':
        if(t2 == '(')
        {
           cout << "Need a bracket!!!" << endl;
           exit(1);
        }
        else ret = '>';
        break;
    case '#':
       switch (t2)
           {
              case '#':
                ret = '=';
                break;
              case ')':
                cout << "Need a bracket!!!" << endl;
                exit(1);
              default : ret = '<';
           }
    }
    return ret;
}

bool In(char t)
{
    switch(t)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '#':return true;
    default : return false;
    }
}

double operate(double op1,double op2,char t)
{
    switch (t)
    {
    case '+': return op1+op2; break;
    case '-': return op1-op2; break;
    case '*': return op1*op2; break;
    case '/': return op1/op2; break;
    }
}

double Calculate(string &s)
{
    int i=0;
    double ret;//return value
    char cc_tmp;
    stack<char> C_stack;
    stack<double> N_stack;

    C_stack.push('#');
    s = s + '#';

    while (s[i] != '#' || cc_tmp != '#')
    {
        if (In(s[i]))
        {
                char c_tmp = C_stack.top();
                char sign = Precede(c_tmp,s[i]);

                if (sign == '>')
                {
                    if (N_stack.empty())
                    {
                        cout << "Input Expression error!!!" << endl;
                        exit(1);
                    }
                    else
                    {
                        double num2;
                        num2 = N_stack.top();
                        N_stack.pop();
                        double num1;
                        num1 = N_stack.top();
                        N_stack.pop();

                        c_tmp = C_stack.top();
                        C_stack.pop();
                        double ret = operate(num1,num2,c_tmp);

                        N_stack.push(ret);

                    }
                }
                else if(sign == '<')
                {
                    C_stack.push(s[i]);
                    i++;//当前字符判断完成，序号加一，指向下一个字符
                }
                else // '='
                {
                    char c_tmp2;
                    if(s[i] == '#') break;
                    else
                    {
                        c_tmp2 = C_stack.top();
                        C_stack.pop();
                        //cout << "c_tmp2: " << c_tmp2 <<endl;
                    }
                    i++;//当前字符判断完成，序号加一，指向下一个字符
                }
            }

        else//数字
        {
            double n_tmp = 0;

            while(s[i] >= '0' && s[i] <= '9')//该数字是连续数字
            {
                if (s[i] >= '0' && s[i] <= '9')//处理整数
                {
                    int j = 0;
                    double k[10];
                    while (s[i] >= '0' && s[i] <= '9')
                    {
                       k[j] = (double)(s[i]-'0');//最高位开始存
                       j++;
                       i++;
                    }
                    j--;
                    double n = 1;
                    for (;j>=0;j--)
                    {
                        n_tmp += k[j] * n;
                        n *= 10;
                    }
                }
                if (s[i] == '.')//开始处理小数点后面的数
                {
                    i++;//不理会小数点，直接指向下一个数字
                    int n = 10;
                    while (s[i] >= '0' && s[i] <= '9') //小数点后是连续数字
                    {
                        n_tmp = n_tmp + ((double)(s[i] - '0'))/n;
                        n *= 10;
                        i++;
                    }

                 }
            }
            N_stack.push(n_tmp);
        }
        cc_tmp = C_stack.top();
    }//while 结束
    ret = N_stack.top();
    N_stack.pop();
    return ret;
}

#endif // EVALUATE_H
