#ifndef WHOLF_PARSER_HPP
#define WHOLF_PARSER_HPP

#include "lexer.hpp"
#include <memory>
#include <vector>

namespace Wholf {
    class Parser {
    private:
        std::vector<std::shared_ptr<Token>> tokens;
        int current;
        
    public:
        Parser(std::vector<std::shared_ptr<Token>> tokens)
            : tokens(tokens), current(0) {}
        
        std::shared_ptr<Expr> parse();
        
    private:
        bool isAtEnd();
        std::shared_ptr<Token> peek();
        std::shared_ptr<Token> previous();
        std::shared_ptr<Token> advance();
        bool check(TokenType type);
        bool match(std::vector<TokenType> types);
        void consume(TokenType type, const std::string& message);
        void synchronize();
        
        // Expression parsing
        std::shared_ptr<Expr> expression();
        std::shared_ptr<Expr> equality();
        std::shared_ptr<Expr> comparison();
        std::shared_ptr<Expr> term();
        std::shared_ptr<Expr> factor();
        std::shared_ptr<Expr> unary();
        std::shared_ptr<Expr> primary();
        
        // Statement parsing
        std::shared_ptr<Stmt> statement();
        std::shared_ptr<Stmt> declaration();
        std::shared_ptr<Stmt> classDeclaration();
        std::shared_ptr<Stmt> functionDeclaration();
        std::shared_ptr<Stmt> variableDeclaration();
        std::shared_ptr<Stmt> expressionStatement();
        std::shared_ptr<Stmt> ifStatement();
        std::shared_ptr<Stmt> whileStatement();
        std::shared_ptr<Stmt> forStatement();
        std::shared_ptr<Stmt> block();
    };
}

#endif // WHOLF_PARSER_HPP
