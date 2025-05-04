#ifndef WHOLF_FILE_HPP
#define WHOLF_FILE_HPP

#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>

namespace Wholf {
    namespace File {
        // Dosya işlemleri
        class FileOperations {
        public:
            void createFile(const std::string& path) {
                std::ofstream file(path);
                file.close();
            }
            
            void deleteFile(const std::string& path) {
                std::filesystem::remove(path);
            }
            
            void readFile(const std::string& path, std::string& content) {
                std::ifstream file(path);
                std::stringstream buffer;
                buffer << file.rdbuf();
                content = buffer.str();
            }
            
            void writeFile(const std::string& path, const std::string& content) {
                std::ofstream file(path);
                file << content;
            }
        };
        
        // Klasör işlemleri
        class DirectoryOperations {
        public:
            void createDirectory(const std::string& path) {
                std::filesystem::create_directory(path);
            }
            
            void deleteDirectory(const std::string& path) {
                std::filesystem::remove_all(path);
            }
            
            std::vector<std::string> listDirectory(const std::string& path) {
                std::vector<std::string> files;
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    files.push_back(entry.path().string());
                }
                return files;
            }
        };
        
        // Dosya sistemi yönetimi
        class FileSystem {
        private:
            std::string currentPath;
            
        public:
            void setCurrentPath(const std::string& path) {
                currentPath = path;
            }
            
            std::string getCurrentPath() const {
                return currentPath;
            }
            
            bool exists(const std::string& path) {
                return std::filesystem::exists(path);
            }
            
            bool isDirectory(const std::string& path) {
                return std::filesystem::is_directory(path);
            }
        };
        
        // Dosya izleme
        class FileWatcher {
        public:
            void watch(const std::string& path, const std::function<void()>& callback) {
                // Dosya değişikliklerini izle
            }
            
            void stopWatching(const std::string& path) {
                // İzlemeyi durdur
            }
        };
    }
}

#endif // WHOLF_FILE_HPP
