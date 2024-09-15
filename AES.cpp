#include "AES.hpp"
AES::AES(const std::string &inputPath, const std::string &keyFilePath,
         const std::string &outputPath)
    : inputPath(fs::absolute(inputPath)), // Handle absolute paths
      keyFilePath(fs::absolute(keyFilePath)),
      outputPath(fs::absolute(outputPath)) {

    validatePaths(); // Validate the paths
    readKeyFile();
    getallFile(this->inputPath, this->outputPath);
}

void AES::getallFile(fs::path inputPath, fs::path outputPath) {
    oldFiles.push_back(inputPath);
    newFiles.push_back(outputPath);
    if (fs::is_directory(inputPath)) {
        for (auto &entry : fs::directory_iterator(inputPath)) {
            // Construct corresponding output path
            fs::path relativePath = fs::relative(entry.path(), inputPath);
            fs::path newOutputPath = outputPath / relativePath;

            // Recursively handle directories
            getallFile(entry.path(), newOutputPath);
        }
    }
}
void AES::validatePaths() {
    // Check if all three paths exist
    if (!fs::exists(inputPath)) {
        throw std::runtime_error("Input path does not exist: " +
                                 inputPath.string());
    }
    if (!fs::exists(outputPath)) {
        throw std::runtime_error("Output path does not exist: " +
                                 inputPath.string());
    }
    if (!fs::exists(keyFilePath) || !fs::is_regular_file(keyFilePath)) {
        throw std::runtime_error("Key file path is invalid: " +
                                 keyFilePath.string());
    }
    // Check if the input and output types match
    if (fs::is_directory(inputPath)) {
        if (!fs::is_directory(outputPath)) {
            throw std::runtime_error("Output path must be a directory when "
                                     "input is a directory: " +
                                     outputPath.string());
        }
    } else if (fs::is_regular_file(inputPath)) {
        if (fs::is_directory(outputPath)) {
            this->outputPath /= inputPath.filename();
        }
    }
}

void AES::readKeyFile() {
    std::ifstream keyFile(keyFilePath, std::ios::binary);
    if (!keyFile) {
        throw std::runtime_error("Unable to open key file.");
    }
    // Read the file content, only read the first 8 unsigned int values
    keyFile.read(reinterpret_cast<char *>(key.data()), key.size());
    // Check if the actual read size matches the expected size
    if (keyFile.gcount() != keySize * sizeof(unsigned int)) {
        throw std::runtime_error(
            "Read size mismatch or not enough data in file.");
    }
    keyFile.close();
}

void AES::encoder() {
    AESECB worker;
    worker.KeyExpansion(key);
    for (size_t i = 0; i < oldFiles.size(); ++i) {
        if (fs::is_directory(oldFiles[i])) {
            if (!fs::exists(newFiles[i])) {
                fs::create_directory(newFiles[i]);
            }
        } else if (fs::is_regular_file(oldFiles[i])) {
            fs::path newFilePath = newFiles[i];
            if (!fs::exists(newFilePath.parent_path())) {
                fs::create_directories(newFilePath.parent_path());
            }
            std::vector<Byte> inputfile;
            if (readFile(oldFiles[i], inputfile)) {
                auto re = worker.encode(inputfile);
                writeFile(newFiles[i], re);
            } else {
                std::cerr << "Unable to read the file: " << oldFiles[i]
                          << std::endl;
            }
        } else {
            std::cerr << "Unrecognized file type: " << oldFiles[i] << std::endl;
        }
    }
}
void AES::decoder() {
    AESECB worker;
    worker.KeyExpansion(key);

    for (size_t i = 0; i < oldFiles.size(); ++i) {
        if (fs::is_directory(oldFiles[i])) {
            if (!fs::exists(newFiles[i])) {
                fs::create_directory(newFiles[i]);
            }
        } else if (fs::is_regular_file(oldFiles[i])) {
            fs::path newFilePath = newFiles[i];
            if (!fs::exists(newFilePath.parent_path())) {
                fs::create_directories(newFilePath.parent_path());
            }
            std::vector<Byte> inputfile;
            if (readFile(oldFiles[i], inputfile)) {
                auto re = worker.decode(inputfile);
                writeFile(newFiles[i], re);
            } else {
                std::cerr << "Unable to read the file: " << oldFiles[i]
                          << std::endl;
            }
        } else {
            std::cerr << "Unrecognized file type: " << oldFiles[i] << std::endl;
        }
    }
}

bool AES::readFile(const fs::path &filePath, std::vector<Byte> &buffer) {
    // Open the file
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }
    // Get file size
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    // Resize the vector
    buffer.resize(static_cast<size_t>(fileSize));
    // Read the file content into the vector
    if (!file.read(reinterpret_cast<char *>(buffer.data()), fileSize)) {
        std::cerr << "Failed to read the file: " << filePath << std::endl;
        return false;
    }
    return true;
}

bool AES::writeFile(const fs::path &filePath, const std::vector<Byte> &buffer) {
    // Open the file
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }
    // Write the vector content to the file
    if (!file.write(reinterpret_cast<const char *>(buffer.data()),
                    buffer.size())) {
        std::cerr << "Failed to read the file: " << filePath << std::endl;
        return false;
    }
    return true;
}