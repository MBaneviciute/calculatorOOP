#ifndef _CAL_
#define _CAL_

//includes
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <stack>
#include<bits/stdc++.h>
namespace shutingYard
{
    /*     the names    */

    typedef std :: vector<std :: string> RPN; 

    /*     typedef functions   */

    //1 argument function
    //typedef function returnType(pointer to the function)(argument type + name);
    typedef double(*unaryFunEval)(double num);//

    //2 argument function
    typedef double(*binaryFunEval)(double num, double num2);//

    //tokenTypes
    enum class tokeTypes
    {
        OPERATOR,
        CONSTANT,
        FUNCTION,
        LPARENTASYS,
        RPARENTASYS,
        ELSE
    };

    /* util functions */

    //search if expression has that elements
    template <typename T>
    bool contains(std :: vector<T> vec, T elem);
    
    //get key list
    template <typename T>
    std :: vector<std :: string> keys(std :: map<std :: string, T> map);
    
    //is it a number 
    bool is_num(char c, bool accepD = true, bool acceptNeg = true);
   
    //if entire string in number
    bool is_num(const char * str);
    

    //find element from list in the expression starting at index i
    std :: string findElement(int i, const char * exp, std :: vector<std :: string> list);
    
    
    // determine if string only contains numerical characters
	bool containsNumbers(const char* str);

    //determine if string mathes a function
    bool isFunc(std :: string str);
    

    //get numeric calue of string
    double getNumericalVal(const char* str);

    //determine if function is left associatyve
    bool isLeAss(std :: string str);

    //get precendence
    short getPrece(std :: string str);
   

    /*    function class   */
    class func
    {
        public:
        //default constructor
        func() : type(tokeTypes :: OPERATOR), prec(0), unary(true), left(true), U_eval(nullptr), B_eval(nullptr) {}
        //for unary functions
        func(unaryFunEval eval, tokeTypes type = tokeTypes :: FUNCTION, short pre = 0, bool left = true)
        : func(type, prec, left, true) 
        {
            U_eval = eval;
        }
        //for binary functions
        func(binaryFunEval eval, tokeTypes type = tokeTypes :: FUNCTION, short prec = 0, bool leaft = true)
        : func(type, prec, left, false)
        {
            B_eval = eval;
        }

        //we are defaulting the function that evaluates
        //the unary or bianry function and desides which is which 
        //by the amount of arguments

        double eval(double in_num, double in_num2 = 0)
        {
            //if unary is true we do the unary fun. if its false we do a binary function
            return this->unary ? U_eval(in_num) : B_eval(in_num, in_num2);
        }


        unaryFunEval U_eval; //unary evaluation
        binaryFunEval B_eval; //binary evaluation
        tokeTypes type;
        short prec; //precedence
        bool unary; //is it unary(or is it not, thats the question?)
        bool left; //left assiociative

        private:
        //private part of the constructor
        func(tokeTypes type, short prec, bool left, bool unary)
        : type(type), prec(prec), left(left), unary(unary), U_eval(nullptr), B_eval(B_eval) {}
    };

    /* help */
    //TO DO :
    /* 
        implement unary functions like sin, cos etc:
    */
    //binary functions
    std :: map<std :: string, func> binary_fun = 
    {//we pre fill the map of binary operators, and we use lambda 
        //
        { "+" , func([](double x, double y) -> double {return x + y;}, tokeTypes :: OPERATOR, 2) },
        { "-" , func([](double x, double y) -> double {return x - y;}, tokeTypes :: OPERATOR, 2) },
        { "*" , func([](double x, double y) -> double {return x * y;}, tokeTypes :: OPERATOR, 3) },
        { "/" , func([](double x, double y) -> double {return x / y;}, tokeTypes :: OPERATOR, 3) },
        //{ "+" , func([](double x, double y) -> double {return x + y;}, tokeTypes :: OPERATOR, 2) },
    };
    /////////////////////////////////////////////helpers/////////////////////////////
    //function names
    std :: vector<std :: string> funcName = keys<func>(binary_fun);
    
    //map of variables
    std :: map<std :: string, double> variables;

    //operators
    std :: vector<char> operators = {'+','-','*','/'};

    //left brakets :: (MAY BE ADDED VARIATIONS)
    std :: vector<char> Lbrac = {'('};
    
    //right brakets :: (MAY BE ADDED VARIATIONS)
    std :: vector<char> Rbrac = {')'};
    
    ////////////////////////////////////end helpers///////////////////////////////////

    /*
        Nodes
    */
   //the base node
    class Node
    {   
        public:
        std :: string name;
        bool isFunc;

        Node * R;//pointer to the right node value
        Node * L;//pointer to the left node value
        //constructor
        Node(std :: string name, bool isFunc)
        : name(name), isFunc(isFunc) {}

        //defaulting and overloading the eval function from before
        double eval(double num1 = 0, double num2 = 0);
    };
    //the function node
    //inheritance of classes 
    class FunNode : public Node
    {
        public:

        bool isUnary;
        func function;

        //constructor
        FunNode(std :: string name) : Node(name, true) {}
        
        //is binary or is it not
        void setUnary(bool isU)
        {
            this->isUnary = isU;
            this->function = binary_fun[name];
        }
        //evaluate 
        double eval(double x, double y = 0)
        {
            return this->function.eval(x, y);
        }
    };
    //number node class
    class NumNode : public Node
    {
        public:
        //constructor
        NumNode(std :: string name) : Node(name, false) {}

        //return numeric value
        double eval(double x = 0 , double y = 0)
        {
            return getNumericalVal(name.c_str());
        }
    };

    /*     functions    */
    //parse infix into reverse polish notation 
    RPN reversePolishNotation(const char * exp)
    {
        std :: vector<std :: string> quene;
        std :: stack<std :: string> stack;

        std :: string obj = "";
        tokeTypes type = tokeTypes :: ELSE;
        tokeTypes prevType = tokeTypes :: ELSE; //negative sign detection

        bool acceptDec = true;
        bool acceptNeg = true;

        //the main loop for RPN, reading tokens and detecting 
        for(int i = 0, len = (int)strlen(exp); i < len; ++i)
        {
            char to = exp[i];
            
            //skip spaces and commas
            if(to == ' ' || to == ',')
            {
                continue;
            }
            //token classification
            if(is_num(to))
            {
                type = tokeTypes :: CONSTANT;
                if(to == '.')
                {
                    acceptDec = false;
                }
                else if (to == '-')
                {
                   acceptNeg = false;
                }
                
                int startI = i; //start iteartor
                if(i < len - 1)
                {
                    while(is_num(exp[i + 1], acceptDec, acceptNeg))
                    {
                        i++;
                        if(i >= len - 1)
                        {
                            break;
                        }
                    }
                }
                obj = std :: string(exp).substr(startI, i - startI + 1);
                //subtraction sign detection
                if(obj == "-")
                {
                    type = tokeTypes :: OPERATOR;
                } 
            }
            else
            {
                obj = findElement(i, exp, funcName);
                if(obj != "")
                {
                    //find valid operation
                    type = contains<char>(operators, obj[0]) ? tokeTypes :: OPERATOR : tokeTypes :: FUNCTION;
                } 
                else
                {
                    obj = findElement(i, exp, keys<double>(variables));
                    if(obj != "")
                    {
                        type = tokeTypes :: CONSTANT;
                    }
                    else if(contains<char>(Lbrac, to))
                    {
                        type = tokeTypes :: LPARENTASYS;
                        obj = "(";
                    }
                    else if(contains<char>(Rbrac, to))
                    {
                        type = tokeTypes :: RPARENTASYS;
                        obj = ")";
                    }
                    else
                    {
                        type = tokeTypes :: ELSE;
                    }
                
            }
            i += obj.size() - 1;
        }
        //do something with operations
        const char * last_stack = (stack.size() > 0)? stack.top().c_str() : "";
        switch(type)
        {
            case tokeTypes :: CONSTANT:
                quene.push_back(obj);
                break;
            case tokeTypes :: FUNCTION:
                stack.push(obj);
                break;
            case tokeTypes :: OPERATOR:
                if(stack.size() != 0)
                {
                    while (
                        (
                            (contains<std :: string>(funcName, last_stack) &&
                            !contains<char>(operators, last_stack[0])) ||
                            getPrece(last_stack) > getPrece(obj) ||
                            ((getPrece(last_stack) == getPrece(obj)) &&
                            isLeAss(last_stack)) 
                        ) && 
                        !contains<char>(Lbrac, last_stack[0])
                    )
                    {
                        //pop from stack to the quene
                        quene.push_back(stack.top());
                        stack.pop();
                        if(stack.size() == 0)
                        {
                            break;
                        }
                        last_stack = stack.top().c_str();
                        }
                    }
                    stack.push(obj);
                    break;
                case tokeTypes :: LPARENTASYS:
                    stack.push(obj);
                    break;
                case tokeTypes :: RPARENTASYS:
                    while(last_stack[0] != '(')
                    {
                        //pop from stack to the quenue
                        quene.push_back(stack.top());
                        stack.pop();
                        last_stack = stack.top().c_str();
                    }
                    stack.pop();
                    break;
                default:
                    return quene;
                }
                //reset type
                prevType = type;
        }
        while(stack.size() > 0)
        {
            //pop from the stack to the quene
            quene.push_back(stack.top());
            stack.pop();
        }

        return quene;
    }
    //RPN to tree
    Node * parse(RPN rpn)
    {
        std :: stack<Node*> stack;

        for(std :: string item : rpn)
        {
            if(is_num(item.c_str()))
            {
                //push number node
                stack.push(new NumNode(item));
            }
            else
            {
                //function
                FunNode * f = new FunNode(item);
                if(contains<std :: string>(keys(binary_fun), item))
                {
                    f->setUnary(false);
                    //set children of node

                    //right child is second argument
                    f->R = stack.top();
                    stack.pop();

                    //left child is first argument
                    f->L = stack.top();
                    stack.pop();
                }
                stack.push(f);
            }
        }
        if(stack.size() == 0)
        {
            return nullptr;
        }
        return stack.top();
    }

    //evaluate the tree
    double eval(Node * tree)
    {
        if(tree->isFunc)
        {
            FunNode * ftree = (FunNode*)tree;
            if(ftree->isUnary)
            {
                /*for unary functions*/
                return ftree->eval(eval(tree->L));
            }
            else
            {
                //eval each child with recursion and then evaluate with return value
                return ftree->eval(eval(tree->L), eval(tree->R));
            }
        }
        else
        {
            //the number node 
            return ((NumNode*)tree)->eval();
        }
    }

    /* util functions */

    //search if expression has that elements
    template <typename T>
    bool contains(std :: vector<T> vec, T elem)
    {
        return find(vec.begin(), vec.end(), elem) != vec.end();
    }
    //get key list
    template <typename T>
    std :: vector<std :: string> keys(std :: map<std :: string, T> map)
    {
        std :: vector<std :: string> ret;

        //push each key from each pair
        for(auto const& element : map)
        {
            ret.push_back(element.first);
        }
        return ret;
    }
     //is it a number 
    bool is_num(char c, bool accepD, bool acceptNeg)
    {
        //digits
        if(c >= '0' && c <= '9')
        {
            return true;
        }
        //decimal
        else if(accepD && c == '.')
        {
            return true;
        }
        //negative sign
        else if(acceptNeg && c == '-')
        {
            return true;
        }
        return false;
    }
    bool is_num(const char * str)
    {
        //its a constatnt, variable, or a numeric string
        return contains<std :: string>(keys<double>(variables), str) ||
        containsNumbers(str);
    }


    

    //find element from list in the expression starting at index i
    std :: string findElement(int i, const char * exp, std :: vector<std :: string> list)
    {
        for(std :: string item : list)
        {
            int n = (int)item.size();
            if(std :: string(exp).substr(i, n) == item)
            {
                return item;
            }
        }
        return "";
    }
    
    // determine if string only contains numerical characters
	bool containsNumbers(const char* str) {
		// cannot be a single decimal point or negative sign
		if (strcmp(str, ".") == 0 || strcmp(str, "-") == 0) {
			return false;
		}

		std::string obj = std::string(str);

		// try to prove wrong
		bool acceptDecimal = true;
		if (is_num(obj[0], true, true)) {
			// check first character for negative sign
			if (obj[0] == '.') {
				// cannot be any more decimal points
				acceptDecimal = false;
			}
		}
		else {
			return false;
		}
		
		for (unsigned int i = 1, len = obj.size(); i < len; i++) {
			// do not accept anymore negative signs
			if (!is_num(obj[i], acceptDecimal, false)) {
				return false;
			}

			if (obj[i] == '.') {
				// cannot be any more decimal points
				acceptDecimal = false;
			}
		}

		return true;
	}
    //get numeric calue of string
    double getNumericalVal(const char* str)
    {
       if(contains<std :: string>(keys<double>(variables), str))
       {
           return variables[str];
       }
       else
       {
           return std :: atof(str);
       }
    }

    //determine if string mathes a function
    bool isFunc(std :: string str)
    {
        return contains<std :: string>(funcName, str);
    }


    //determine if function is left associatyve
    bool isLeAss(std :: string str)
    {
        return binary_fun[str].left;
    }

    //get precendence
    short getPrece(std :: string str)
    {
        if(contains<std :: string>(keys(binary_fun), str))
        {
            return binary_fun[str].prec;
        }

        return 0;
    }

}
#endif