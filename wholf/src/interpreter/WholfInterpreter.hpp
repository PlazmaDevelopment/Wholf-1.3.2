#ifndef WHOLF_INTERPRETER_HPP
#define WHOLF_INTERPRETER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <stack>
#include <variant>
#include <any>

namespace Wholf {
    // Veri tipleri
    enum class DataType {
        INTEGER,
        FLOAT,
        STRING,
        BOOLEAN,
        NULL_TYPE,
        UNDEFINED,
        ARRAY,
        OBJECT,
        FUNCTION,
        CLASS
    };
    
    // Değer sınıfı
    class Value {
    public:
        std::variant<int, float, std::string, bool, std::nullptr_t, std::vector<Value>, std::map<std::string, Value>, std::function<Value()>, std::shared_ptr<void>> data;
        DataType type;
        
        Value(int value) : type(DataType::INTEGER) { data = value; }
        Value(float value) : type(DataType::FLOAT) { data = value; }
        Value(const std::string& value) : type(DataType::STRING) { data = value; }
        Value(bool value) : type(DataType::BOOLEAN) { data = value; }
        Value(std::nullptr_t value) : type(DataType::NULL_TYPE) { data = value; }
        Value(const std::vector<Value>& value) : type(DataType::ARRAY) { data = value; }
        Value(const std::map<std::string, Value>& value) : type(DataType::OBJECT) { data = value; }
        Value(const std::function<Value()>& value) : type(DataType::FUNCTION) { data = value; }
        Value(const std::shared_ptr<void>& value) : type(DataType::CLASS) { data = value; }
        
        operator int() const { return std::get<int>(data); }
        operator float() const { return std::get<float>(data); }
        operator std::string() const { return std::get<std::string>(data); }
        operator bool() const { return std::get<bool>(data); }
        operator std::nullptr_t() const { return std::get<std::nullptr_t>(data); }
        operator std::vector<Value>() const { return std::get<std::vector<Value>>(data); }
        operator std::map<std::string, Value>() const { return std::get<std::map<std::string, Value>>(data); }
        operator std::function<Value()>() const { return std::get<std::function<Value()>>(data); }
        operator std::shared_ptr<void>() const { return std::get<std::shared_ptr<void>>(data); }
    };
    
    // Yorumlayıcı sınıfı
    class Interpreter {
    private:
        // Çevre değişkenleri
        std::map<std::string, Value> variables;
        
        // Fonksiyonlar
        std::map<std::string, std::function<Value()>> functions;
        
        // Sınıflar
        std::map<std::string, std::shared_ptr<void>> classes;
        
        // Stack
        std::stack<Value> stack;
        
        // İşlem önceliği
        std::map<std::string, int> operatorPrecedence;
        
    public:
        // Yorumlayıcı başlatma
        Interpreter() {
            // İşlem öncelikleri
            operatorPrecedence["+"] = 1;
            operatorPrecedence["-"] = 1;
            operatorPrecedence["*"] = 2;
            operatorPrecedence["/"] = 2;
            operatorPrecedence["%"] = 2;
            operatorPrecedence["^"] = 3;
            operatorPrecedence["&&"] = 4;
            operatorPrecedence["||"] = 4;
            operatorPrecedence["!"] = 5;
            operatorPrecedence["=="] = 6;
            operatorPrecedence["!="] = 6;
            operatorPrecedence[">"] = 6;
            operatorPrecedence["<"] = 6;
            operatorPrecedence[">="] = 6;
            operatorPrecedence["<="] = 6;
        }
        
        // Kod yorumlama
        Value interpret(const std::string& code) {
            // Tokenize
            std::vector<std::string> tokens = tokenize(code);
            
            // Parse
            std::vector<std::unique_ptr<Node>> ast = parse(tokens);
            
            // Evaluate
            return evaluate(ast);
        }
        
    private:
        // Tokenize
        std::vector<std::string> tokenize(const std::string& code) {
            std::vector<std::string> tokens;
            std::string currentToken;
            
            for (char c : code) {
                if (c == ' ' || c == '\n' || c == '\t') {
                    if (!currentToken.empty()) {
                        tokens.push_back(currentToken);
                        currentToken.clear();
                    }
                } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' ||
                          c == '=' || c == '!' || c == '>' || c == '<' || c == '&' || c == '|' ||
                          c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
                          c == ',' || c == ';') {
                    if (!currentToken.empty()) {
                        tokens.push_back(currentToken);
                        currentToken.clear();
                    }
                    tokens.push_back(std::string(1, c));
                } else {
                    currentToken += c;
                }
            }
            
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
            }
            
            return tokens;
        }
        
        // Parse
        std::vector<std::unique_ptr<Node>> parse(const std::vector<std::string>& tokens) {
            std::vector<std::unique_ptr<Node>> ast;
            std::stack<std::string> operators;
            std::stack<std::unique_ptr<Node>> operands;
            
            for (const auto& token : tokens) {
                if (isNumber(token)) {
                    operands.push(std::make_unique<NumberNode>(std::stod(token)));
                } else if (isIdentifier(token)) {
                    operands.push(std::make_unique<IdentifierNode>(token));
                } else if (isOperator(token)) {
                    while (!operators.empty() && 
                           operatorPrecedence[operators.top()] >= operatorPrecedence[token]) {
                        auto right = operands.top(); operands.pop();
                        auto left = operands.top(); operands.pop();
                        operands.push(std::make_unique<BinaryOperationNode>(
                            std::move(left), std::move(right), operators.top()
                        ));
                        operators.pop();
                    }
                    operators.push(token);
                } else if (token == "(") {
                    operators.push(token);
                } else if (token == ")") {
                    while (operators.top() != "(") {
                        auto right = operands.top(); operands.pop();
                        auto left = operands.top(); operands.pop();
                        operands.push(std::make_unique<BinaryOperationNode>(
                            std::move(left), std::move(right), operators.top()
                        ));
                        operators.pop();
                    }
                    operators.pop();
                }
            }
            
            while (!operators.empty()) {
                auto right = operands.top(); operands.pop();
                auto left = operands.top(); operands.pop();
                operands.push(std::make_unique<BinaryOperationNode>(
                    std::move(left), std::move(right), operators.top()
                ));
                operators.pop();
            }
            
            ast.push_back(std::move(operands.top()));
            return ast;
        }
        
        // Evaluate
        Value evaluate(const std::vector<std::unique_ptr<Node>>& ast) {
            for (const auto& node : ast) {
                return evaluateNode(node);
            }
            return Value(nullptr);
        }
        
        // Node evaluation
        Value evaluateNode(const std::unique_ptr<Node>& node) {
            if (auto number = dynamic_cast<NumberNode*>(node.get())) {
                return Value(number->value);
            } else if (auto identifier = dynamic_cast<IdentifierNode*>(node.get())) {
                return variables[identifier->name];
            } else if (auto binary = dynamic_cast<BinaryOperationNode*>(node.get())) {
                Value left = evaluateNode(binary->left);
                Value right = evaluateNode(binary->right);
                return evaluateBinaryOperation(left, right, binary->operatorType);
            }
            return Value(nullptr);
        }
        
        // Binary operation evaluation
        Value evaluateBinaryOperation(const Value& left, const Value& right, const std::string& operatorType) {
            if (operatorType == "+") return left + right;
            if (operatorType == "-") return left - right;
            if (operatorType == "*") return left * right;
            if (operatorType == "/") return left / right;
            if (operatorType == "%") return left % right;
            if (operatorType == "^") return std::pow(left, right);
            if (operatorType == "&&") return left && right;
            if (operatorType == "||") return left || right;
            if (operatorType == "!") return !left;
            if (operatorType == "==") return left == right;
            if (operatorType == "!=") return left != right;
            if (operatorType == ">") return left > right;
            if (operatorType == "<") return left < right;
            if (operatorType == ">=") return left >= right;
            if (operatorType == "<=") return left <= right;
            return Value(nullptr);
        }
        
        // Helper functions
        bool isNumber(const std::string& str) {
            return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
        }
        
        bool isIdentifier(const std::string& str) {
            return !str.empty() && std::isalpha(str[0]);
        }
        
        bool isOperator(const std::string& str) {
            return str == "+" || str == "-" || str == "*" || str == "/" || str == "%" ||
                   str == "^" || str == "&&" || str == "||" || str == "!" ||
                   str == "==" || str == "!=" || str == ">" || str == "<" ||
                   str == ">=" || str == "<=";
        }
    };
}

#endif // WHOLF_INTERPRETER_HPP
