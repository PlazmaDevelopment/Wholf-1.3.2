#ifndef WHOLF_FRONTEND_HPP
#define WHOLF_FRONTEND_HPP

#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace Wholf {
    namespace Frontend {
        // Temel UI bileşenleri
        class Element {
        public:
            std::string tag;
            std::string id;
            std::string className;
            std::string text;
            std::vector<std::shared_ptr<Element>> children;
            
            Element(const std::string& tag) : tag(tag) {}
            
            // Özellikler
            void setAttribute(const std::string& name, const std::string& value);
            void setStyle(const std::string& property, const std::string& value);
            void addClass(const std::string& className);
            void removeClass(const std::string& className);
            
            // Olay yönetimi
            void addEventListener(const std::string& event, const std::function<void()>& callback);
            void removeEventListener(const std::string& event, const std::function<void()>& callback);
        };
        
        // Özel UI bileşenleri
        class Button : public Element {
        public:
            Button() : Element("button") {}
            
            void onClick(const std::function<void()>& callback) {
                addEventListener("click", callback);
            }
            
            void setText(const std::string& text) {
                this->text = text;
            }
            
            std::string getText() const {
                return text;
            }
        };
        
        class Text : public Element {
        public:
            Text() : Element("div") {}
            
            void setText(const std::string& text) {
                this->text = text;
            }
            
            std::string getText() const {
                return text;
            }
            
            void setFontSize(int size) {
                setStyle("font-size", std::to_string(size) + "px");
            }
            
            void setFontColor(const std::string& color) {
                setStyle("color", color);
            }
        };
        
        // Sayfa yönetimi
        class Page {
        public:
            std::vector<std::shared_ptr<Element>> elements;
            
            void addElement(std::shared_ptr<Element> element) {
                elements.push_back(element);
            }
            
            void removeElement(std::shared_ptr<Element> element) {
                elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
            }
            
            void setTitle(const std::string& title) {
                // Sayfa başlığı ayarla
            }
            
            void setTheme(const std::string& theme) {
                // Tema ayarla
            }
        };
        
        // CSS yönetimi
        class Style {
        public:
            void addRule(const std::string& selector, const std::string& properties) {
                // CSS kuralı ekle
            }
            
            void removeRule(const std::string& selector) {
                // CSS kuralı kaldır
            }
        };
    }
}

#endif // WHOLF_FRONTEND_HPP
