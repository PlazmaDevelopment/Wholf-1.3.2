#ifndef WHOLF_STDLIB_HPP
#define WHOLF_STDLIB_HPP

#include <string>
#include <vector>
#include <memory>

namespace Wholf {
    namespace StdLib {
        // Temel veri tipleri
        class String {
        public:
            std::string value;
            
            String(const std::string& value) : value(value) {}
            
            // Metotlar
            int length() const;
            String* substring(int start, int end);
            std::vector<String*> split(const String& delimiter);
            String* toUpperCase();
            String* toLowerCase();
        };
        
        class Number {
        public:
            double value;
            
            Number(double value) : value(value) {}
            
            // Matematiksel operasyonlar
            Number* add(const Number& other);
            Number* subtract(const Number& other);
            Number* multiply(const Number& other);
            Number* divide(const Number& other);
        };
        
        // Koleksiyonlar
        template<typename T>
        class List {
        private:
            std::vector<T> elements;
            
        public:
            void add(T element);
            T get(int index);
            void set(int index, T element);
            int size();
            void remove(int index);
        };
        
        // Dosya işlemleri
        class File {
        public:
            static String* read(const String& path);
            static void write(const String& path, const String& content);
        };
        
        // Girdi/Çıktı
        class Console {
        public:
            static void writeLine(const String& message);
            static String* readLine();
        };
    }
}

#endif // WHOLF_STDLIB_HPP
