#ifndef WHOLF_SCANNER_HPP
#define WHOLF_SCANNER_HPP

#include "Token.hpp"
#include <string>
#include <vector>

namespace Wholf {
    // Scanner sınıfı
    class Scanner {
    private:
        std::string source;
        int start;
        int current;
        int line;
        int column;
        
    public:
        Scanner(const std::string& source) : source(source), start(0), current(0), line(1), column(1) {}
        
        std::vector<Token> scanTokens();
        
    private:
        // Token oluşturma
        Token makeToken(TokenType type) {
            return Token(type, source.substr(start, current - start), line, column);
        }
        
        Token errorToken(const std::string& message) {
            return Token(TokenType::EOF_TOKEN, message, line, column);
        }
        
        // Yardımcı fonksiyonlar
        bool isAtEnd() const { return current >= source.length(); }
        
        char advance() {
            column++;
            return source[current++];
        }
        
        void addToken(TokenType type) {
            tokens.push_back(makeToken(type));
        }
        
        void addToken(TokenType type, const std::variant<int, float, std::string, Keyword, Operator, Punctuation>& literal) {
            tokens.push_back(Token(type, literal, line, column));
        }
        
        char peek() const {
            if (isAtEnd()) return '\0';
            return source[current];
        }
        
        char peekNext() const {
            if (current + 1 >= source.length()) return '\0';
            return source[current + 1];
        }
        
        bool match(char expected) {
            if (isAtEnd()) return false;
            if (source[current] != expected) return false;
            current++;
            column++;
            return true;
        }
        
        void skipWhitespace() {
            while (true) {
                char c = peek();
                switch (c) {
                    case ' ':
                    case '\r':
                    case '\t':
                        advance();
                        break;
                    case '\n':
                        line++;
                        column = 1;
                        advance();
                        break;
                    case '/':
                        if (peekNext() == '/') {
                            // Tek satır yorum
                            while (peek() != '\n' && !isAtEnd()) advance();
                        } else if (peekNext() == '*') {
                            // Çoklu satır yorum
                            while (peek() != '*' && peekNext() != '/' && !isAtEnd()) {
                                if (peek() == '\n') {
                                    line++;
                                    column = 1;
                                }
                                advance();
                            }
                            if (!isAtEnd()) {
                                advance(); // '*' karakterini atla
                                advance(); // '/' karakterini atla
                            }
                        } else {
                            return;
                        }
                        break;
                    default:
                        return;
                }
            }
        }
        
        std::string string() {
            while (peek() != '"' && !isAtEnd()) {
                if (peek() == '\n') {
                    line++;
                    column = 1;
                }
                advance();
            }
            
            if (isAtEnd()) {
                tokens.push_back(errorToken("Unterminated string."));
                return "";
            }
            
            // Kapalı tırnak işaretini atla
            advance();
            return source.substr(start + 1, current - 2 - start);
        }
        
        double number() {
            while (std::isdigit(peek())) advance();
            
            if (peek() == '.' && std::isdigit(peekNext())) {
                advance();
                while (std::isdigit(peek())) advance();
            }
            
            return std::stod(source.substr(start, current - start));
        }
        
        std::string identifier() {
            while (std::isalnum(peek())) advance();
            return source.substr(start, current - start);
        }
        
        // Anahtar kelimeleri kontrol et
        Keyword checkKeyword(const std::string& text) {
            if (text == "let") return Keyword::LET;
            if (text == "const") return Keyword::CONST;
            if (text == "function") return Keyword::FUNCTION;
            if (text == "class") return Keyword::CLASS;
            if (text == "if") return Keyword::IF;
            if (text == "else") return Keyword::ELSE;
            if (text == "while") return Keyword::WHILE;
            if (text == "for") return Keyword::FOR;
            if (text == "foreach") return Keyword::FOREACH;
            if (text == "return") return Keyword::RETURN;
            if (text == "break") return Keyword::BREAK;
            if (text == "continue") return Keyword::CONTINUE;
            if (text == "true") return Keyword::TRUE;
            if (text == "false") return Keyword::FALSE;
            if (text == "null") return Keyword::NULL_TOKEN;
            if (text == "undefined") return Keyword::UNDEFINED;
            return Keyword::IDENTIFIER;
        }
    };
}

#endif // WHOLF_SCANNER_HPP
