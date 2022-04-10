#include <bits/stdc++.h>
#include "lexer.cpp"
using namespace std;

int main()
{
    tokenNumberSet();
    ifstream InputFile("input.txt");
    string str;
    while (getline(InputFile, str))
    {
        scanner(str, ln);
        ln++;
    }
    cout << "\nEnd of Lexer Output\n";
}
