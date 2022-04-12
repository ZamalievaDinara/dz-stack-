using namespace std;

#include <iostream>
#include <string>

template <typename T>
struct elem
{
    T value;
    elem* prior = nullptr; 
};

template <typename T>
void push(elem<T>*& stack, T value)
{
    auto* newel = new elem<T>();
    newel->value = value; 
    newel->prior = stack; 
    stack = newel; 
}

template <typename T>
bool pop(elem<T>*& stack, T& value) 
{
    if (!stack) 
        return false;
    auto* topElem = stack;
    value = stack->value; 
    stack = stack->prior; 
    delete topElem;
    return true;
}
 
template <typename T>
void clearStack(elem<T>*& stack)
{
    while (stack)
    {
        auto* topElem = stack->prior;
        delete stack;
        stack = topElem;
    }
}

int checkBrackets(const string& str)
{
    elem<char>* bracketStack = nullptr;
    elem<int>* posStack = nullptr;
    
    for (int i = 0; i < str.size(); ++i)
    {
        const char ch = str[i];
        
        switch (ch)
        {
        case '(': push(bracketStack, ')'); push(posStack, i); break;
        case '[': push(bracketStack, ']'); push(posStack, i); break;
        case '{': push(bracketStack, '}'); push(posStack, i); break;
        case '<': push(bracketStack, '>'); push(posStack, i); break;
  
        case ')':
        case ']':
        case '}':
        case '>':
            char lastBracket;
            int lastPos;
            pop(posStack, lastPos);
            if (!pop(bracketStack, lastBracket) || lastBracket != ch)
                return i;
            break;
        }

    }
    if (posStack)
    {
        int lastPos;
        pop(posStack, lastPos);
        clearStack(posStack);
        clearStack(bracketStack);
        return lastPos;
    }
    return -1;

}

int main()
{
    setlocale(LC_ALL, "Rus");
    string str;
    cout << "Введите математическое выражение: ";
    cin >> str;
    cout << endl;
    int errorPos = checkBrackets(str);
    if (errorPos < 0)
        cout << "OK" << endl;
    else
        cout << "Ошибка в позиции: " << errorPos + 1;
    
}

