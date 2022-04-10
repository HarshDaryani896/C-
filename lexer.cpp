/*
Group Member Details

Group #21
2018B3A70992H	Rohan Sachan
2018B1A70645H	Harsh Daryani
2018B1A70775H	Aaryan Gupta
2018B3A70984H	Jui Pradhan
Language name: c+

*/

//Lexer Program

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

#define varTokenNum 100
#define intTokenVal 200
#define floatTokenVal 300
#define stringTokenVal 400

//Structure to contain Token name, type of lexeme, token number and linenumber in the input file
struct Token{
    string name;
    string lexeme;
    int tno;
    int lno;
};


//Vector containing lexer output
vector<Token> tokenInfo;

//Map storing lexical errors
map<int,string> er; 
unordered_map<string, int> operators, keywords, datatypes;
int ln = 1;

//Functions for Inserting tokens according to type
void insert_datatype(string token,int i)
{
    datatypes.insert({token,i++});
}

void insert_keyword(string token,int i)
{
    keywords.insert({token,i++});
}
void insert_operator(string token,int i)
{
    operators.insert({token,i++});
}

//Giving unique values to each token for datatype, keyword and operator
void tokenNumberSet()
{
    int i = 0;
    insert_datatype("cint",i++);            //i=0
    insert_datatype("cfloat",i++);          //i=1
    insert_datatype("cstring",i++);         //i=2
    insert_datatype("cbool",i++);           //i=3
    
    insert_keyword("cin", i++);             //i=4
    insert_keyword("cout", i++);            //i=5
    insert_keyword("cfor", i++);            //i=6
    insert_keyword("cif", i++);             //i=7
    insert_keyword("celse", i++);           //i=8
    insert_keyword("celse cif", i++);       //i=9
    insert_keyword("cbreak", i++);          //i=10
    insert_keyword("creturn", i++);         //i=11
    insert_keyword("true", i++);            //i=12
    insert_keyword("false", i++);           //i=13
    insert_keyword("cendl", i++);           //i=14
    insert_keyword("call", i++);            //i=15

    insert_operator("+",i++);               //i=16
    insert_operator("-",i++);               //i=17
    insert_operator("*",i++);               //i=18
    insert_operator("/",i++);               //i=19
    insert_operator("%",i++);               //i=20
    insert_operator("==",i++);              //i=21
    insert_operator("!=",i++);              //i=22
    insert_operator("(",i++);               //i=23
    insert_operator(")",i++);               //i=24
    insert_operator("[",i++);               //i=25
    insert_operator("]",i++);               //i=26
    insert_operator("{",i++);               //i=27
    insert_operator("}",i++);               //i=28
    insert_operator("\"",i++);              //i=29
    insert_operator("<=",i++);              //i=30
    insert_operator(">=",i++);              //i=31
    insert_operator("<",i++);               //i=32
    insert_operator(">",i++);               //i=33
    insert_operator("&&",i++);              //i=34
    insert_operator("||",i++);              //i=35
    insert_operator("++",i++);              //i=36
    insert_operator("--",i++);              //i=37
    insert_operator(";",i++);               //i=38
    insert_operator("#",i++);               //i=39
    insert_operator("<<",i++);              //i=40
    insert_operator(">>",i++);              //i=41
    insert_operator("=",i++);              //i=42

}

 
// Boolean function that identifies keyword 
bool checkKeyword(string str)
{
    if (keywords.find(str) != keywords.end())
        return true;
    return false;
}
// Boolean function that identifies data type
bool checkDataType(string str)
{
    if (datatypes.find(str) != datatypes.end())
        return true;
    return false;
}


//DFA function that checks string, int, float and boolean and tells the type of token
bool DFA(string str, int linenumber)
{
    //flag as in state of combined DFA
    int flag = 0; //initial state

    //DFA for identifiers (String)
    if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
    {
        flag = 1;
        for(int i = 1; i < str.length(); i++){
            if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
            {
                flag = 6;//error state
                return false; 
            }
            
        }
        if(flag == 1)//final state for identifier
        {
            struct Token tempToken = {str,"id",varTokenNum,linenumber};
            tokenInfo.push_back(tempToken);
            cout << "Token " << varTokenNum << ", string " << str << " identifier," << " line number " << linenumber << "\n";
            return true;
        }
    }

    //DFA for int, float (Data types)
    else if (str == "0" || (str[0] >= '0' && str[0] <= '9') || ((str[0] == '+' || str[0] == '-') && (str[1] >= '0' && str[1] <= '9')) || ((str[0] >= '0' && str[0] <= '9') && str[1] == '.') || ((str[0] == '+' || str[0] == '-') && (str[1] >= '0' && str[1] <= '9') && str[2] == '.'))
    {
        if (str == "0")
        {
            flag=3;
        }
        if(str[0] >= '0' && str[0] <= '9')
        {
            flag = 3;
        }
        else if(str[0] == '+' || str[0] == '-')
        {
            flag = 2;
            if(str[1] == '+' || str[1] == '-')
            {
                flag=3;
            }
            else
            {
                flag = 6;
            }
        }
        else
        {
            flag = 6; //error state
        }
        bool floatFlag = false;
        if (str == "0")
        {
            if(flag==3)//final state for integer
            {
                struct Token tempToken = {str,"literal",intTokenVal,linenumber};
                tokenInfo.push_back(tempToken);
                cout << "Token " << intTokenVal << ", string " << str << " integer," << " line number " << linenumber << endl;
                return true;
            }
        }
        int count = 0;
        for(int i = 1; i < str.length(); )
        {
            if (str[i] == '.')
            {
                flag=4;
                count++;
                i++;
                continue;
            }
            if (!(str[i] >= '0' && str[i] <= '9'))
            {
                flag=6;//error state
                return false;
            }
                
            if (count)
            {
                flag=5; //final state for float
                floatFlag = true;
            }
            i++;        
        }

        if (floatFlag && count < 2 && flag==5)
        {
            struct Token tempToken = {str,"literal",floatTokenVal,linenumber};
            tokenInfo.push_back(tempToken);
           cout << "Token " << floatTokenVal << ", string " << str << " floating point integer," << " line number " << linenumber << endl;
        }
        else if (!floatFlag && !count)
        {
            struct Token tempToken = {str,"literal",intTokenVal,linenumber};
            tokenInfo.push_back(tempToken);
            cout << "Token " << intTokenVal << ", string " << str << " integer," << " line number " << linenumber << endl;
        }
        else
        {
            return false;
        }

        return true;
    }
    return false;
}

//Function that checks for valid token
bool checkToken(string str, int linenumber)
{
    if (checkKeyword(str))
    {
        if(str!="false" && str!="true")
        {
            struct Token tempToken = {str,str,keywords[str],linenumber};
            tokenInfo.push_back(tempToken);
        }
        else
        {
            struct Token tempToken = {str,"literal",001,linenumber};
            tokenInfo.push_back(tempToken);
        }
        cout << "Token " << keywords[str] << ", string " << str << " keyword, "<< " line number " << linenumber << "\n";
    }
    else if (checkDataType(str))
    {
        struct Token tempToken = {str,str,datatypes[str],linenumber};
        tokenInfo.push_back(tempToken);
        cout << "Token " << datatypes[str] << ", string " << str << " data type, " << " line number " << linenumber << "\n";
    }
    else if (DFA(str, linenumber))
    {
        //other checks in DFA
    }
    else if (str != "")
    {
        if(er.find(linenumber)==er.end())
        er.insert(make_pair(linenumber,"Token not found "+str));
        cout << "ERROR " << str << " Token not found!, "
                 << " line number " << linenumber << endl;
        return false;
    }
    return true;
}


//Scanner function to check tha validity of tokens and identification of errors 
void scanner(string s, int linenumber)
{

    //Ignores white spaces and single line comments 
    string str = "";
    for (int i = 0; i < s.length(); i++)
    {
        //comment
        if (s[i] == '#')
            break;
        //string literal
        if (s[i] == '\"')
        {
            int start = i;
            i++;
            while (i < s.length() && s[i] != '\"')
            {
                i++;
            }
            if (i == s.length())
            {
                if(er.find(linenumber)==er.end())
                er.insert(make_pair(linenumber,"String not terminated"));
                cout << "ERROR string not terminated, "<< " line number " << linenumber << endl;
            }
            else
            {
                struct Token tempToken = {s.substr(start, i-start+1),"literal",stringTokenVal,linenumber};
                tokenInfo.push_back(tempToken);
                cout << "Token " << stringTokenVal << ", string " << s.substr(start, i-start+1) << " string," << " line number " << linenumber << endl;
            }
        }
        else if (string(1, s[i]) == "+" || string(1, s[i]) == "-")
        {
            if (str == "" && !(i + 1 >= s.length() || s[i + 1] == ' '))
                str.push_back(s[i]);  
            else
            {
                if (!checkToken(str, linenumber))
                {
                //check recovery condition
                //return;
                }
                if ((i < s.length() - 1) && operators.find(s.substr(i, 2)) != operators.end())
                {
                    struct Token tempToken = {s.substr(i, 2),s.substr(i, 2),operators[s.substr(i, 2)],linenumber};
                    tokenInfo.push_back(tempToken);
                    cout << "Token " << operators[s.substr(i, 2)] << ", string " << s.substr(i, 2) << " operator," << " line number " << linenumber << "\n";
                    i++;
                }
                else
                {
                    struct Token tempToken = {string(1, s[i]),string(1, s[i]),operators[string(1, s[i])],linenumber};
                    tokenInfo.push_back(tempToken);
                   cout << "Token " << operators[string(1, s[i])] << ", string " << s[i] << " operator,"  << " line number " << linenumber << "\n";
                }
                str = "";
                continue;
            }
        }
        else if (operators.find(string(1, s[i])) != operators.end() || string(1, s[i]) == " ")
        {
            if (!checkToken(str, linenumber))
            {
                //check recovery condition
                //return;
            }
            if (s[i] == ' ')
            {
                str = "";
                continue;
            }
            else if ((i < s.length() - 1) && operators.find(s.substr(i, 2)) != operators.end())
            {
                struct Token tempToken = {s.substr(i, 2),s.substr(i, 2),operators[s.substr(i, 2)],linenumber};
                tokenInfo.push_back(tempToken);
                cout << "Token " << operators[s.substr(i, 2)] << ", string " << s.substr(i, 2) << " operator," <<  " line number " << linenumber << "\n";
                i++;
            }
            else
            {
                struct Token tempToken = {string(1, s[i]),string(1, s[i]),operators[string(1, s[i])],linenumber};
                tokenInfo.push_back(tempToken);
                cout << "Token " << operators[string(1, s[i])] << ", string " << s[i] << " operator," <<  " line number " << linenumber << "\n";
            }
            str = "";
            continue;
        }
        else
            str.push_back(s[i]);
    }
    if (str.length())
    {
        checkToken(str, linenumber);
    }
    return;
}
