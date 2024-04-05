#include "in2pos.h"

arithmetic::arithmetic(){

}

arithmetic::arithmetic(string equation){
    istringstream ss(equation);
    string token;
    vector<string> infix;
    string output;
    // Read all the tokens in the input
    while(ss >> token){
        infix.push_back(token);
    }

    vector<string> stack;
    while(!infix.empty()){
        // Parse the first token to a string and remove it from the vector
        string val = infix[0];
        // cout << "val: " << val << endl;
        infix.erase(infix.begin());
        // If the current token is an integer
        if(!isOperator(val) && val != "(" && val != ")"){
            output += val + " ";
        }
        else if(val == "("){
            stack.push_back(val);
        }
        // If the value is an operator
        else if(isOperator(val)){
        //     push the operator onto the stack
        //     pop and write to the output string all consecutive operators that are either operators of higher precedence, or left-associative operators of equal precedence
            while(!stack.empty() && ((stack.back() != "(" && getPresidence(stack.back()) > getPresidence(val)) ||
                (getPresidence(stack.back()) == getPresidence(val) && val != "^"))){
                string temp = stack.back();
                stack.pop_back();
                output += temp + " ";
            }
            stack.push_back(val);
        }
        else if(val == ")"){
        //     pop and write to the output string all operators until a left parenthesis is popped off the stack
            while(!stack.empty() && stack.back() != "("){
                output += stack.back() + " ";
                stack.pop_back();
            }
            stack.pop_back();
        }
        // cout << output << endl;
    }
    // if end of the string
    //     pop and write to the output string all operators until the stack is empty
    while(!stack.empty()){
        output += stack.back() + " ";
        stack.pop_back();
    }
    cout << output;
}

int arithmetic::getPresidence(string operation){
    if(operation == "-" || operation == "+"){
        return 1;
    }
    else if(operation == "*" || operation == "/"){
        return 2;
    }
    else if(operation == "^"){
        return 3;
    }
    return 0;
}

bool arithmetic::isOperator(string token){
    if(token == "+" || token == "-" || token == "*" 
        || token == "/" || token == "^"){
        return true;
    }
    return false;
}


int main(int argc, char* argv[]){
    string equation = argv[1];

    arithmetic myEquation(equation);
}
