#ifndef WHOLF_FEGN_HPP
#define WHOLF_FEGN_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace Wholf {
    namespace Fegn {
        // API entegrasyonu
        class Api {
        public:
            std::string baseUrl;
            std::map<std::string, std::string> headers;
            
            Api(const std::string& baseUrl) : baseUrl(baseUrl) {}
            
            std::string get(const std::string& endpoint);
            std::string post(const std::string& endpoint, const std::string& data);
            std::string put(const std::string& endpoint, const std::string& data);
            std::string deleteRequest(const std::string& endpoint);
        };
        
        // Veri yönetimi
        class DataStore {
        private:
            std::map<std::string, std::string> data;
            
        public:
            void set(const std::string& key, const std::string& value) {
                data[key] = value;
            }
            
            std::string get(const std::string& key) {
                return data[key];
            }
            
            void remove(const std::string& key) {
                data.erase(key);
            }
        };
        
        // Olay yönetimi
        class Event {
        public:
            std::string name;
            std::function<void()> callback;
            
            Event(const std::string& name, const std::function<void()>& callback)
                : name(name), callback(callback) {}
        };
        
        // Entegrasyon yöneticisi
        class Integration {
        private:
            std::vector<std::shared_ptr<Event>> events;
            std::map<std::string, std::shared_ptr<Api>> apis;
            
        public:
            void addApi(const std::string& name, const std::shared_ptr<Api>& api) {
                apis[name] = api;
            }
            
            void addEvent(const std::string& name, const std::function<void()>& callback) {
                events.push_back(std::make_shared<Event>(name, callback));
            }
            
            void triggerEvent(const std::string& name) {
                for (const auto& event : events) {
                    if (event->name == name) {
                        event->callback();
                    }
                }
            }
        };
        
        // Veri akışı yönetimi
        class Stream {
        public:
            std::string source;
            std::function<void(std::string)> transform;
            std::function<void(std::string)> sink;
            
            void pipe(const std::function<void(std::string)>& sink) {
                this->sink = sink;
            }
        };
    }
}

#endif // WHOLF_FEGN_HPP
