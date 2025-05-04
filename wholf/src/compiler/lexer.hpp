#ifndef WHOLF_LEXER_HPP
#define WHOLF_LEXER_HPP

#include <string>
#include <vector>
#include <memory>

namespace Wholf {
    enum class TokenType {
        // Anahtar kelimeler
        KeywordClass,
        KeywordUsing,
        KeywordStatic,
        KeywordVoid,
        
        // Operatörler
        Plus,
        Minus,
        Star,
        Slash,
        
        // Ayraçlar
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        
        // Diğer token'ler
        Identifier,
        StringLiteral,
        NumberLiteral,
        EOF
    };

    class Token {
    public:
        TokenType type;
        std::string lexeme;
        int line;
        
        Token(TokenType type, std::string lexeme, int line)
            : type(type), lexeme(lexeme), line(line) {}
    };

    class Lexer {
    private:
        std::string source;
        int current;
        int line;
        
    public:
        Lexer(const std::string& source)
            : source(source), current(0), line(1) {}
        
        std::vector<std::shared_ptr<Token>> scanTokens();
        
    private:
        char advance();
        bool isAtEnd();
        char peek();
        char peekNext();
        bool match(char expected);
        std::shared_ptr<Token> makeToken(TokenType type);
        std::shared_ptr<Token> errorToken(const std::string& message);
        void skipWhitespace();
        std::shared_ptr<Token> string();
        std::shared_ptr<Token> number();
        std::shared_ptr<Token> identifier();
    };
}

#endif // WHOLF_LEXER_HPP
