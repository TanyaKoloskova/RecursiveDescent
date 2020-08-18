#include <iostream>
#include <string>
#include <utility>
#include <vector>


struct Expression {
    Expression()= default;
    Expression(int value) : value(value), type("VALUE"){}
    Expression(std::string operation) : operation(std::move(operation)), type("OPERATION") {}
    Expression(std::string unary_operation, Expression expr) : operation(std::move(unary_operation)), operands{std::move(expr)} , type("UNARY"){}
    Expression(std::string binary_operation, Expression left, Expression right) : operation(std::move(binary_operation)), operands{std::move(left), std::move(right)}, type("BINARY") {}
    std::string type;
    int value{};
    std::string operation;
    std::vector<Expression> operands;
};

class parser_expression{
public:
    parser_expression(): input(nullptr) {}
    parser_expression(std::istream* input): input(input) {}
    Expression parse(){
        return parse_binary_expr(0);
    }
private:
    std::istream* input;

    std::string get_token(){
        char symbol;
        // clearing before token
        for(;;){
            if (!input->get(symbol))
                return "END";
            if (symbol=='\n')
                return "END";
            if (std::isspace(symbol))
                continue;
            if (std::isalpha(symbol))
                return "ERROR: EXPRESSION INCLUDE NOT INTEGER SYMBOLS";
            break;
        }
        if (std::isdigit(symbol)) {
            std::string number;
            do {
                number.push_back(symbol);
                if (!input->get(symbol))
                    return number;
            }while(std::isdigit(symbol));
            input->putback(symbol);
            return number;
        }
        if (symbol=='+'||symbol=='-'||symbol=='*'||symbol=='/'){
            std::string result{symbol};
            return result;
        }
        return "ERROR: UNKNOWN TOKEN";

    }
    Expression parse_unary_expr(int current_priority) {
        std::string token = get_token();
        if (token.substr(0, 5) == "ERROR") throw std::logic_error(token);
        if (token.substr(0, 3) == "END") throw std::logic_error("ERROR: UNEXPECTED END OF EXPRESSION");
        if (std::isdigit(token[0]))
            return Expression(std::stoi(token));
        if (current_priority<=1) {
            if (token == "-")
                return Expression(-parse_unary_expr(current_priority).value);
            if (token == "+")
                return Expression(parse_unary_expr(current_priority).value);
            if ((token == "*") || (token == "/"))
                throw std::logic_error("ERROR: UNSOLVABLE SEQUENCE OF OPERATIONS");
        }
        else
            throw std::logic_error("ERROR: UNSOLVABLE SEQUENCE OF OPERATIONS");


    }
    Expression parse_binary_expr(int current_priority){
        Expression left_part = parse_unary_expr(current_priority);
        std::string operation = get_token();
        while((operation.substr(0, 3) != "END")) {
            if ((operation != "+") && (operation != "-") && (operation != "*") && (operation != "/"))
                throw std::logic_error("ERROR: UNKNOWN TOKEN UNSTEAD OPERATION");
            int priority = get_priority(operation);
            if (priority <= current_priority) {
                input->putback(operation[0]);
                return left_part;
            }
            Expression right_part = parse_binary_expr(priority);
            left_part =  Expression(operation, left_part, right_part);
            operation = get_token();
        }
        //bad code. In last time, when full expression parse, It func push \n.
        input->putback('\n');
        return left_part;
    }

    int get_priority(const std::string& operation){
        if (operation == "+") return 1;
        if (operation == "-") return 1;
        if (operation == "*") return 2;
        if (operation == "/") return 2;
        throw std::logic_error("ERROR: UNKNOWN OPERATION");
    }
};

int calculate_tree_expression(const Expression& expr)
{
    if (expr.type == "BINARY")
    {
        int left = calculate_tree_expression(expr.operands[0]);
        int right = calculate_tree_expression(expr.operands[1]);
        if (expr.operation =="+") return (left+right);
        if (expr.operation =="-") return (left-right);
        if (expr.operation =="*") return (left*right);
        if (expr.operation =="/") {
            if (right==0)
                throw std::logic_error("ERROR: DIVISION BY ZERO");
            return (left / right);
        };
        throw std::logic_error("ERROR: UNKNOWN OPERATION");
    }
    if (expr.type == "VALUE")
        return expr.value;
    throw std::logic_error("ERROR: UNKNOWN TYPE SUBEXPRESSION");
}


int calculator(std::istream& input, int& result) {
    parser_expression parser(&input);
    try {
        Expression tree_expression = parser.parse();
        result = calculate_tree_expression(tree_expression);
        return 0;
    }
    catch (std::logic_error& er){
        std::cerr<<er.what()<<std::endl;
        return 2;
    }
    catch (...){
        std::cerr<<"Unknown error"<<std::endl;
        return 10;
    }
}