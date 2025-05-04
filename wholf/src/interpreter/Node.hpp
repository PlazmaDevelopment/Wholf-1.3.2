#ifndef WHOLF_NODE_HPP
#define WHOLF_NODE_HPP

#include <string>
#include <memory>

namespace Wholf {
    // Temel node sınıfı
    class Node {
    public:
        virtual ~Node() = default;
        virtual std::string toString() const = 0;
    };
    
    // Sayı node
    class NumberNode : public Node {
    public:
        double value;
        
        NumberNode(double value) : value(value) {}
        
        std::string toString() const override {
            return std::to_string(value);
        }
    };
    
    // Identifier node
    class IdentifierNode : public Node {
    public:
        std::string name;
        
        IdentifierNode(const std::string& name) : name(name) {}
        
        std::string toString() const override {
            return name;
        }
    };
    
    // Binary işlem node
    class BinaryOperationNode : public Node {
    public:
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        std::string operatorType;
        
        BinaryOperationNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right, const std::string& operatorType)
            : left(std::move(left)), right(std::move(right)), operatorType(operatorType) {}
        
        std::string toString() const override {
            return "(" + left->toString() + " " + operatorType + " " + right->toString() + ")";
        }
    };
    
    // Fonksiyon çağırma node
    class FunctionCallNode : public Node {
    public:
        std::string functionName;
        std::vector<std::unique_ptr<Node>> arguments;
        
        FunctionCallNode(const std::string& functionName, std::vector<std::unique_ptr<Node>> arguments)
            : functionName(functionName), arguments(std::move(arguments)) {}
        
        std::string toString() const override {
            std::string result = functionName + "(";
            for (size_t i = 0; i < arguments.size(); ++i) {
                if (i > 0) result += ", ";
                result += arguments[i]->toString();
            }
            result += ")";
            return result;
        }
    };
    
    // Fonksiyon tanımlama node
    class FunctionDefinitionNode : public Node {
    public:
        std::string functionName;
        std::vector<std::string> parameters;
        std::unique_ptr<Node> body;
        
        FunctionDefinitionNode(const std::string& functionName, std::vector<std::string> parameters, std::unique_ptr<Node> body)
            : functionName(functionName), parameters(std::move(parameters)), body(std::move(body)) {}
        
        std::string toString() const override {
            std::string result = "function " + functionName + "(";
            for (size_t i = 0; i < parameters.size(); ++i) {
                if (i > 0) result += ", ";
                result += parameters[i];
            }
            result += ") {\n" + body->toString() + "\n}";
            return result;
        }
    };
    
    // Sınıf tanımlama node
    class ClassDefinitionNode : public Node {
    public:
        std::string className;
        std::vector<std::unique_ptr<Node>> methods;
        
        ClassDefinitionNode(const std::string& className, std::vector<std::unique_ptr<Node>> methods)
            : className(className), methods(std::move(methods)) {}
        
        std::string toString() const override {
            std::string result = "class " + className + " {\n";
            for (const auto& method : methods) {
                result += method->toString() + "\n";
            }
            result += "}";
            return result;
        }
    };
    
    // İf koşulu node
    class IfNode : public Node {
    public:
        std::unique_ptr<Node> condition;
        std::unique_ptr<Node> thenBranch;
        std::unique_ptr<Node> elseBranch;
        
        IfNode(std::unique_ptr<Node> condition, std::unique_ptr<Node> thenBranch, std::unique_ptr<Node> elseBranch = nullptr)
            : condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch)) {}
        
        std::string toString() const override {
            std::string result = "if (" + condition->toString() + ") {\n" + thenBranch->toString() + "\n}";
            if (elseBranch) {
                result += " else {\n" + elseBranch->toString() + "\n}";
            }
            return result;
        }
    };
    
    // Döngü node
    class LoopNode : public Node {
    public:
        std::string type;  // while, for, foreach
        std::unique_ptr<Node> condition;
        std::unique_ptr<Node> body;
        
        LoopNode(const std::string& type, std::unique_ptr<Node> condition, std::unique_ptr<Node> body)
            : type(type), condition(std::move(condition)), body(std::move(body)) {}
        
        std::string toString() const override {
            return type + " (" + condition->toString() + ") {\n" + body->toString() + "\n}";
        }
    };
}

#endif // WHOLF_NODE_HPP
