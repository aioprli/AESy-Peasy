#include "key.hpp"

bool Key::key_create(string name, string path) {
    const string chars =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // generate key
    string key = "";
    for (int i = 0; i < this->_maxlength; ++i) {
        key += chars[std::rand() % chars.length()];
    }

    // check whether the path is available
    std::filesystem::path dir_path(path);
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        std::cerr << "Error: Path " << path << " is not valid or accessible."
                  << std::endl;
        return false;
    }

    // if name is empty, set the default file name
    if (name.empty()) {
        name = "key";
    }

    // generate the file path and name
    std::filesystem::path file_path = dir_path / (name + ".key");
    int counter = 1;
    while (std::filesystem::exists(file_path)) {
        file_path = dir_path / (name + "_" + std::to_string(counter) + ".key");
        counter++;
    }

    // save the key to a file
    std::ofstream outFile(file_path);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << file_path
                  << " for writing." << std::endl;
        return false;
    }
    outFile << key;
    outFile.close();

    std::cout << "Key successfully generated and saved to: " << file_path
              << std::endl;
    return true;
}


bool Key::get_encrypted_array(string path) { return true; }

char Key::xor_char(char c) { return '1'; }
string Key::xor_string(string s) {
    std::string a;
    return a;
}

