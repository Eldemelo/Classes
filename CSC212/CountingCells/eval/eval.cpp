#include "eval.h"

arithmetic::arithmetic(){

}

arithmetic::arithmetic(string equation){
    istringstream ss(equation);
    string output;
    vector<string> stack;
    string value;
    // Read all the tokens in the input
    while(ss >> value){
        // cout << "CurrVal: " << value << endl;
        // If the value is an integer
        if(!isOperator(value)){
        //    push it onto the stack
            stack.push_back(value);
        }
        // If it's an operation
        else if(isOperator(value)){
        //    pop two numbers (operands) from the stack, evaluate the operator on those numbers and push the result back to the stack
            string second = stack.back();
            stack.pop_back();
            string first = stack.back();
            stack.pop_back();
            stack.push_back(std::to_string(performCalc(value, first, second)));
            // cout << stack.back() << endl;
        }
    }
    // End of the string
    cout << stack.back();
}

int arithmetic::performCalc(string operation, string firstVal, string secondVal){
    // cout << "Performing operation " << firstVal << " " << operation << " " << secondVal << endl;
    if(operation == "-"){
        return (stoi(firstVal) - stoi(secondVal));
    }
    else if(operation == "+"){
        return (stoi(firstVal) + stoi(secondVal));
    }
    else if(operation == "*"){
        return (stoi(firstVal) * stoi(secondVal));
    }
    else if(operation == "/"){
        return floor((stod(firstVal) / stod(secondVal)));
    }
    else if(operation == "^"){
        return pow(stoi(firstVal),stoi(secondVal));
    }
    return -1;
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
