// Improvement upon the initial version of the stack class.
// Author: Jack Collins, 13382796
//   Date: 08 Feb 2016

// The syntax checker loops through the characters of a file individually
// It pushes (, { and [ characters to a stack.
// If it comes across a ], } or ) character, it pops a character from the stack and compares it with it

//This works adequately for most files but in exceptional cases such as brackets in quotes,
//we need to employ additional checks before pushing to the stack. To do this, I introduced a
//inCommas boolean variable which simply toggles on/off each time it encounters a quote character

// There is a further corner case, however, if one considers an escaped quotation like so '\''
// In order to not toggle the inCommas variable in this case, we need to introudce an escapeChar boolean variable
// to simple track whether or not we are escaping the next character in the loop.

// Note: the original code contained a further corner case. Namely, the following cout -
// "You can't put more items into a stack than there is room for"
// the ' character here is within quotation marks and would throw off the validity of our inCommas boolean as a result
// A further inQuotationMarks boolean variable could be introduced but for the sake of this lab I have merely
// changed "can't" to "can not", emitting the '

// Comments are a further area to consider since they should be entirely ignored by a syntax checker. A simple 
// inComment boolean variable could be set to true on the finding of any "//" string and set to false on
// the next line break. As with the previous boolean variable, the use of this would be to ignore all characters while 
// inComment is true and hence allow the synatax checker to ignore all comments. I have not implemented this as
// I did have time to properly do so.

// This current syntax checker successfully parses itself.


#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

#define MAX_STACK 10000
int LineNumber=1;

class stack
{
private:
    char *contents;
    int top;
public:
    stack (void);
    stack (unsigned int StackSize);
    ~stack(void);
    void init(void );
    void push(char c);
    char pop(void );
    bool isEmpty(void);
    bool isFull(void);
};

stack::stack(void)
{
    top=0;
    contents = new char[MAX_STACK];
}

stack::stack(unsigned int StackSize)
{
    top=0;
    contents = new char[StackSize];
}
stack::~stack()
{
    delete [] contents;
}

void stack::push(char c)
{
    if(!isFull())
    {
        contents[top]=c;
        top++;
    }
    else
    {
        cerr << "You can not put more items into a stack than there is room for." << endl;
    }

}

char stack::pop(void)
{
    if(!isEmpty())
    {
        top--;
        return(contents[top]);
    }
    else
    {
        cerr << "Warning!: You tried to pop an empty stack" << endl;
        return((char)NULL);
    }
}

bool stack::isEmpty(void)
{
    return top == 0;
}
bool stack::isFull(void)
{
    return top == MAX_STACK;
}


int main(void )
{
    bool isError = false;
    bool inCommas = false;
    bool escapeChar = false;

    stack charStack(10000);
    string fileName;
    ifstream inFileStream;
    char c;
    cout << "Please enter the name of a C++ file: " << endl;
    cin >> fileName;
    inFileStream.open(fileName.c_str());
    while(inFileStream.get(c))
    {
        if (c == '\n')
            {
                LineNumber++;
                continue;
            }
        if(inCommas && !escapeChar)
        {
            if (c == '\\')
            {
                escapeChar = true;
                continue;
            }
            else if (c == '\'')
            {
                inCommas = false;
                continue;
            }
            else
                continue;

        }
        else if(inCommas && escapeChar)
        {
            escapeChar = false;
            continue;
        }
        else
        {
            if(c == '\''){
                inCommas = true;
                continue;
            }
            else if(c ==  '(' || c == '{' || c == '[')
            {
                charStack.push(c);
                continue;
            }
            else if(c == ')')
            {
                if(charStack.pop() == '(')
                    continue;
                else
                {
                    cout << "symbols do not match on line " <<  LineNumber << endl;
                    isError = true;
                    break;
                }
            }
            else if(c == '}')
            {
                if(charStack.pop() == '{')
                    continue;
                else
                {
                    cout << "symbols do not match on line " <<  LineNumber << endl;
                    isError = true;
                    break;
                }
            }
            else if(c == ']')
            {
                if(charStack.pop() == '[')
                    continue;
                else
                {
                    cout << "symbols do not match on line " <<  LineNumber << endl;
                    isError = true;
                    break;
                }
            }
            else
            {
                continue;
            } // Finshed reading the file
        }
    }
    if(!charStack.isEmpty())
        cout << "syntax error: stack is not empty after parsing the entire file...";
    else if (isError)
        cout << "Parsing finished with some errors...";
    else
        cout << "Successfully parsed " << LineNumber << " lines in the file without any problems...";
    return(0);
}