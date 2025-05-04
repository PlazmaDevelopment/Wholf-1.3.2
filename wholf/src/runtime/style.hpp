#ifndef WHOLF_STYLE_HPP
#define WHOLF_STYLE_HPP

#include <string>
#include <map>
#include <memory>

namespace Wholf {
    namespace Style {
        // CSS özelliklerini temsil eden sınıf
        class Property {
        public:
            std::string name;
            std::string value;
            
            Property(const std::string& name, const std::string& value)
                : name(name), value(value) {}
        };
        
        // CSS seçicilerini temsil eden sınıf
        class Selector {
        public:
            std::string value;
            
            Selector(const std::string& value) : value(value) {}
        };
        
        // CSS kurallarını temsil eden sınıf
        class Rule {
        public:
            std::shared_ptr<Selector> selector;
            std::map<std::string, std::string> properties;
            
            void addProperty(const std::string& name, const std::string& value) {
                properties[name] = value;
            }
        };
        
        // Stil yöneticisi
        class StyleSheet {
        private:
            std::vector<std::shared_ptr<Rule>> rules;
            
        public:
            void addRule(const std::string& selector, const std::map<std::string, std::string>& properties) {
                auto rule = std::make_shared<Rule>();
                rule->selector = std::make_shared<Selector>(selector);
                for (const auto& prop : properties) {
                    rule->addProperty(prop.first, prop.second);
                }
                rules.push_back(rule);
            }
            
            std::string generateCSS() {
                std::string css;
                for (const auto& rule : rules) {
                    css += rule->selector->value + " {\n";
                    for (const auto& prop : rule->properties) {
                        css += "    " + prop.first + ": " + prop.second + ";\n";
                    }
                    css += "}\n\n";
                }
                return css;
            }
        };
        
        // Animasyon yönetimi
        class Animation {
        public:
            std::string name;
            std::string duration;
            std::string timingFunction;
            std::string delay;
            std::string iterationCount;
            std::string direction;
            
            Animation(const std::string& name)
                : name(name) {}
            
            void setDuration(int seconds) {
                duration = std::to_string(seconds) + "s";
            }
            
            void setTimingFunction(const std::string& function) {
                timingFunction = function;
            }
        };
        
        // Tema yönetimi
        class Theme {
        private:
            std::map<std::string, std::string> variables;
            
        public:
            void setVariable(const std::string& name, const std::string& value) {
                variables[name] = value;
            }
            
            std::string getVariable(const std::string& name) {
                return variables[name];
            }
        };
    }
}

#endif // WHOLF_STYLE_HPP
