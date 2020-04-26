
#include <iostream>
#include<fstream>
#include<string>
#include<vector>

char operators[] = "#+-*/%&|!=><[](){},.;:'\"?^~\\";
std::string s_operators[] = {"#","+","-","*","/","%","&","|","!","=",">","<","[","]","(",")","{","}",",",".",";",":","'","\"","?","^","~","\\"};
std::string Keywords[] = { "asm","auto","bool","break","case",
"catch","char","class","const_cast","continue",
"default","delete","double","do","dynamic_cast",
"else","enum","explicit","extern","false","float",
"for","friend","gotot","if","inline","int","long",
"mutable","namespace","new","operator","private",
"protected","public","register","reinterpret_cast",
"return","short","signed","sizeof","static_cast","static",
"struct","switch","template","this",
"throw","true","try","typedef","typeid","typename",
"union","unsigned","using","virtual","void",
"volatile","wchar_t","while" };
char constants[] = "0123456789";


class Token
{
private:
    std::string m_token;
    std::string m_type;
    int m_line;
public:
    Token(std::string token, std::string type, int line);
    Token(char token, std::string type, int line);
    ~Token();
public:
    bool operator==(std::string str);
    bool operator==(char str);
public:
    void Log();
    void Push_back(char ch);
    void Push_back(std::string str);
    std::string token();
    void Type(std::string type);
    
};

Token::Token(std::string token, std::string type, int line) :
    m_token(token), m_type(type), m_line(line)
{

}

Token::Token(char token, std::string type, int line) :
    m_token(1, token), m_type(type), m_line(line)
{

}

Token::~Token()
{

}

bool Token::operator==(std::string str)
{
    if (m_token == str)
    {
        return true;
    }
    return false;
}

bool Token::operator==(char str)
{
    std::string t_str(str, 1);
    if (m_token == t_str)
    {
        return true;
    }
    return false;
}

void Token::Log()
{
    std::cout.width(4);
    std::cout <<std::left<< m_line << " | "; 
    std::cout.width(10); 
    std::cout << std::left << m_type << " | " << m_token << std::endl;
}

void Token::Push_back(char ch)
{
    m_token.push_back(ch);
}

void Token::Push_back(std::string str)
{
    for (unsigned int i = 0; i < str.size(); i++)
    {
        m_token.push_back(str[i]);
    }
}
std::string Token::token()
{
    return m_token;
}

void Token::Type(std::string type)
{
    m_type = type;
}

bool IsKeyword(std::string& buffer)
{
    for (int i = 0; i < 61; i++)
    {
        if (buffer == Keywords[i] )
        {
            return true;
        }
    }
    return false;
}
bool IsKeyword(Token kwd)
{
    for (int i = 0; i < 61; i++)
    {
        if (kwd == Keywords[i])
        {
            return true;
        }
    }
    return false;
}

bool IsOperator(char ch)
{
    for (int i = 0; i < 29; i++)
    {
        if (ch == operators[i])
        {
           
            return true;
        }
    }
    return false;
}

bool IsOperator(Token ch)
{
    for (int i = 0; i < 29; i++)
    {
        if (ch == s_operators[i])
        {

            return true;
        }
    }
    return false;
}

bool IsAlnum(std::string buffer)
{
    for(unsigned int i=0;i<buffer.size();i++)
    {
        if (isalnum(buffer[i]) == false)
        {     
            if (buffer[i] == '.')
            {

            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool IsAlnum(Token tkn)
{
    for (unsigned int i = 0; i <tkn.token().size(); i++)
    {
        if (isalnum(tkn.token()[i]) == false)
        {
            if (tkn.token()[i] == '.')
            {

            }
            else
            {
                return false;
            }
        }
    }
    return true;
}



int main()
{
    /*First Pass*/
    std::ifstream fin;
    fin.open("comment.txt", std::ios::in);
    if (!fin)
    {
        std::cout << "No such file exists" << std::endl;
    }
    std::vector<Token> source;
    std::string buffer;
    char ch;
    bool flag = false;
    int line = 1;
    while (fin)
    {
        flag = false;
        fin.get(ch);
        if (fin.eof())
        {
            break;
        }
        else if ( ch == '\n')
        {
            line += 1;
            continue;
        }
        else if (ch == ' ')
        {
            continue;
        }
        /*else if (ch == '/')
        {
            buffer.push_back(ch);
            fin.get(ch);
            if (ch == '/')
            {
                fin.get(ch);
                while (ch != '\n')
                {
                    buffer.push_back(ch);
                }
                source.push_back(Token(buffer, "Comment", line));
                buffer.clear();
                line += 1;
                flag = true;
            }
            else
            {
                source.push_back(Token(buffer, "Operator", line));
                buffer.pop_back();
                buffer.push_back(ch);
            }
        }
        */
        else if (ch == '\"')
        {
            buffer.push_back(ch);
            fin.get(ch);
            while (ch != '\"')
            {
                buffer.push_back(ch);
                fin.get(ch);
            }
            buffer.push_back(ch);
            source.push_back(Token(buffer, "String", line));
            buffer.clear();
            continue;
        }
        else if (IsOperator(ch) == true)
        {            
            source.push_back(Token(ch, "Operator", line));
            continue;
        }
        /*else if (isalnum(ch))
        {
            while (true)
            {
                buffer.push_back(ch);
                fin.get(ch);
                if (ch == ' ')
                {
                    source.push_back(Token(buffer, "Constant", line));
                    buffer.clear();
                    flag = true;
                    break;
                }
                else if(ch == '\n')
                {
                    source.push_back(Token(buffer, "Constant", line));
                    buffer.clear();
                    flag = true;
                    break;
                }
                else if (isalpha(ch))
                {
                    source.push_back(Token(buffer, "Constant", line));
                    buffer.clear();
                    buffer.push_back(ch);
                    break;
                }
                else if (IsOperator(ch))
                {
                    if (ch == '.')
                    {

                    }
                    else
                    {
                        source.push_back(Token(buffer, "Constant", line));
                        source.push_back(Token(ch, "Operator", line));
                        buffer.clear();
                        flag = true;
                        break;
                    }
                }
            }  
        }
        if (flag == true)
        {
            continue;
        }*/
        while(!flag)
        {
            buffer.push_back(ch);
            if (fin.eof())
            {   
                buffer.pop_back();
                source.push_back(Token(buffer, "Identifier", line));
                flag = true;
                break;
            }
            if (ch == '\n')
            {
            line += 1;
            buffer.pop_back();
            break;
            }
            else if (ch == ' ')
            {
            break;
            }
            else if (IsOperator(ch))
            {
                buffer.pop_back();
                source.push_back(Token(buffer, "Identifier", line));
                source.push_back(Token(ch, "Operator", line));
                buffer.clear();
                flag = true;
                break;      
            }
            else if (IsKeyword(buffer) == true)
            {
                source.push_back(Token(buffer,"Keyword",line));
                buffer.clear();
                flag = true;
                break;
            }
            fin.get(ch);
        }
        if (flag == false)
        {     
             source.push_back(Token(buffer, "Identifier", line-1 ));
             buffer.clear();
        }
    }
    fin.close();
    source.pop_back();
    for (unsigned int i = 0; i < source.size(); i++)
    {
        source[i].Log();
    }
    std::cin.get();
    return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               