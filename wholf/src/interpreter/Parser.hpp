#ifndef WHOLF_PARSER_HPP
#define WHOLF_PARSER_HPP

#include "Node.hpp"
#include "Token.hpp"
#include <vector>
#include <memory>

namespace Wholf {
    // Parser sınıfı
    class Parser {
    private:
        std::vector<Token> tokens;
        size_t current;
        
    public:
        Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}
        
        std::unique_ptr<Node> parse();
        
    private:
        // Yardımcı fonksiyonlar
        bool isAtEnd() const { return current >= tokens.size(); }
        
        Token peek() const { return tokens[current]; }
        
        Token advance() {
            if (!isAtEnd()) current++;
            return tokens[current - 1];
        }
        
        bool check(TokenType type) const {
            if (isAtEnd()) return false;
            return tokens[current].type == type;
        }
        
        bool match(TokenType type) {
            if (!check(type)) return false;
            advance();
            return true;
        }
        
        Token consume(TokenType type, const std::string& message) {
            if (check(type)) return advance();
            throw std::runtime_error(message);
        }
        
        // Parse fonksiyonları
        std::unique_ptr<Node> expression();
        std::unique_ptr<Node> assignment();
        std::unique_ptr<Node> equality();
        std::unique_ptr<Node> comparison();
        std::unique_ptr<Node> term();
        std::unique_ptr<Node> factor();
        std::unique_ptr<Node> unary();
        std::unique_ptr<Node> primary();
        
        // Statü fonksiyonları
        std::unique_ptr<Node> statement();
        std::unique_ptr<Node> declaration();
        std::unique_ptr<Node> variableDeclaration();
        std::unique_ptr<Node> functionDeclaration();
        std::unique_ptr<Node> classDeclaration();
        std::unique_ptr<Node> ifStatement();
        std::unique_ptr<Node> whileStatement();
        std::unique_ptr<Node> forStatement();
        std::unique_ptr<Node> foreachStatement();
        std::unique_ptr<Node> block();
    };
}

#endif // WHOLF_PARSER_HPP
