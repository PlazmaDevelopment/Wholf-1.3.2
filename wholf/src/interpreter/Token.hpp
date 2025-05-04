#ifndef WHOLF_TOKEN_HPP
#define WHOLF_TOKEN_HPP

#include <string>
#include <variant>

namespace Wholf {
    // Token türleri
    enum class TokenType {
        NUMBER,
        STRING,
        IDENTIFIER,
        KEYWORD,
        OPERATOR,
        PUNCTUATION,
        EOF_TOKEN
    };
    
    // Anahtar kelimeler
    enum class Keyword {
        LET,
        CONST,
        FUNCTION,
        CLASS,
        IF,
        ELSE,
        WHILE,
        FOR,
        FOREACH,
        RETURN,
        BREAK,
        CONTINUE,
        TRUE,
        FALSE,
        NULL_TOKEN,
        UNDEFINED
    };
    
    // Operatörler
    enum class Operator {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        POWER,
        AND,
        OR,
        NOT,
        EQUAL,
        NOT_EQUAL,
        GREATER,
        LESS,
        GREATER_EQUAL,
        LESS_EQUAL
    };
    
    // Noktalama işaretleri
    enum class Punctuation {
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        COMMA,
        SEMICOLON,
        DOT,
        COLON,
        ARROW
    };
    
    // Token sınıfı
    class Token {
    public:
        TokenType type;
        std::variant<int, float, std::string, Keyword, Operator, Punctuation> value;
        int line;
        int column;
        
        Token(TokenType type, const std::variant<int, float, std::string, Keyword, Operator, Punctuation>& value, int line, int column)
            : type(type), value(value), line(line), column(column) {}
        
        std::string toString() const {
            switch (type) {
                case TokenType::NUMBER:
                    return std::to_string(std::get<int>(value));
                case TokenType::STRING:
                    return std::get<std::string>(value);
                case TokenType::IDENTIFIER:
                    return std::get<std::string>(value);
                case TokenType::KEYWORD:
                    return keywordToString(std::get<Keyword>(value));
                case TokenType::OPERATOR:
                    return operatorToString(std::get<Operator>(value));
                case TokenType::PUNCTUATION:
                    return punctuationToString(std::get<Punctuation>(value));
                case TokenType::EOF_TOKEN:
                    return "EOF";
                default:
                    return "";
            }
        }
        
    private:
        std::string keywordToString(Keyword keyword) const {
            switch (keyword) {
                case Keyword::LET: return "let";
                case Keyword::CONST: return "const";
                case Keyword::FUNCTION: return "function";
                case Keyword::CLASS: return "class";
                case Keyword::IF: return "if";
                case Keyword::ELSE: return "else";
                case Keyword::WHILE: return "while";
                case Keyword::FOR: return "for";
                case Keyword::FOREACH: return "foreach";
                case Keyword::RETURN: return "return";
                case Keyword::BREAK: return "break";
                case Keyword::CONTINUE: return "continue";
                case Keyword::TRUE: return "true";
                case Keyword::FALSE: return "false";
                case Keyword::NULL_TOKEN: return "null";
                case Keyword::UNDEFINED: return "undefined";
                default: return "";
            }
        }
        
        std::string operatorToString(Operator op) const {
            switch (op) {
                case Operator::PLUS: return "+";
                case Operator::MINUS: return "-";
                case Operator::MULTIPLY: return "*";
                case Operator::DIVIDE: return "/";
                case Operator::MODULO: return "%";
                case Operator::POWER: return "^";
                case Operator::AND: return "&&";
                case Operator::OR: return "||";
                case Operator::NOT: return "!";
                case Operator::EQUAL: return "==";
                case Operator::NOT_EQUAL: return "!=";
                case Operator::GREATER: return ">";
                case Operator::LESS: return "<";
                case Operator::GREATER_EQUAL: return ">=";
                case Operator::LESS_EQUAL: return "<=";
                default: return "";
            }
        }
        
        std::string punctuationToString(Punctuation punc) const {
            switch (punc) {
                case Punctuation::LEFT_PAREN: return "(";
                case Punctuation::RIGHT_PAREN: return ")";
                case Punctuation::LEFT_BRACE: return "{";
                case Punctuation::RIGHT_BRACE: return "}";
                case Punctuation::LEFT_BRACKET: return "[";
                case Punctuation::RIGHT_BRACKET: return "]";
                case Punctuation::COMMA: return ",";
                case Punctuation::SEMICOLON: return ";";
                case Punctuation::DOT: return ".";
                case Punctuation::COLON: return ":";
                case Punctuation::ARROW: return "=>";
                default: return "";
            }
        }
    };
}

#endif // WHOLF_TOKEN_HPP
