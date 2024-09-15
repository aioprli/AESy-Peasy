#ifndef AES_HPP
#define AES_HPP
#include "AES.hpp"
#include "CBC.hpp"
#include "ECB.hpp"
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
namespace fs = std::filesystem;
enum class AES_MODE { CBC, ECB };
class AES {
  public:
    AES(const std::string &inputPath, const std::string &keyFilePath,
        const std::string &outputPath);
    void encoder();
    void decoder();

  private:
    fs::path inputPath;
    fs::path keyFilePath;
    fs::path outputPath;
    size_t keySize = 8;
    std::array<Byte, 32> key;
    std::vector<fs::path> oldFiles;
    std::vector<fs::path> newFiles;
    // Recursive function to map input paths to output paths
    void getallFile(fs::path inputPath, fs::path outputPath);
    void validatePaths();
    void readKeyFile();
    bool readFile(const fs::path &filePath, std::vector<uint8_t> &buffer);
    bool writeFile(const fs::path &filePath,
                   const std::vector<uint8_t> &buffer);
};
#endif