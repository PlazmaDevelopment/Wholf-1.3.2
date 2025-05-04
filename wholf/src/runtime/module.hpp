#ifndef WHOLF_MODULE_HPP
#define WHOLF_MODULE_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <functional>

namespace Wholf {
    namespace Module {
        // Modül tanımı
        class Module {
        public:
            std::string name;
            std::string path;
            std::map<std::string, std::function<void()>> exports;
            
            Module(const std::string& name, const std::string& path)
                : name(name), path(path) {}
            
            void exportFunction(const std::string& name, const std::function<void()>& func) {
                exports[name] = func;
            }
        };
        
        // Modül yöneticisi
        class ModuleManager {
        private:
            std::map<std::string, std::shared_ptr<Module>> modules;
            
        public:
            // Modül yükleme
            std::shared_ptr<Module> loadModule(const std::string& name, const std::string& path) {
                auto module = std::make_shared<Module>(name, path);
                modules[name] = module;
                return module;
            }
            
            // Modül içe aktarma
            std::shared_ptr<Module> importModule(const std::string& name) {
                return modules[name];
            }
            
            // Fonksiyon çağırma
            void callFunction(const std::string& moduleName, const std::string& functionName) {
                auto module = modules[moduleName];
                if (module && module->exports.find(functionName) != module->exports.end()) {
                    module->exports[functionName]();
                }
            }
        };
        
        // Paket yönetimi
        class Package {
        public:
            std::string name;
            std::string version;
            std::vector<std::string> dependencies;
            
            Package(const std::string& name, const std::string& version)
                : name(name), version(version) {}
            
            void addDependency(const std::string& dependency) {
                dependencies.push_back(dependency);
            }
        };
        
        // Paket yöneticisi
        class PackageManager {
        private:
            std::map<std::string, std::shared_ptr<Package>> packages;
            
        public:
            void installPackage(const std::string& name, const std::string& version) {
                auto package = std::make_shared<Package>(name, version);
                packages[name] = package;
            }
            
            void uninstallPackage(const std::string& name) {
                packages.erase(name);
            }
            
            void updatePackage(const std::string& name, const std::string& version) {
                if (packages.find(name) != packages.end()) {
                    packages[name]->version = version;
                }
            }
        };
        
        // Veri yapısı yönetimi
        class DataStructure {
        public:
            std::string name;
            std::vector<std::string> fields;
            
            DataStructure(const std::string& name) : name(name) {}
            
            void addField(const std::string& field) {
                fields.push_back(field);
            }
        };
    }
}

#endif // WHOLF_MODULE_HPP
