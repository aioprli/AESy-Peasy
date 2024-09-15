#include "AES.hpp"
#include "key.hpp"
#include <cmdline.hpp>
#include <iostream>
using namespace std;

void getparsers(int argc, char *argv[], cmdline::parser &parser) {
    // Option to generate a key (bool) - Whether to generate a new key
    parser.add("generate-key", 'g', "Generate a new encryption key");
    // Encryption (bool) - Whether to perform encryption
    parser.add("encrypt", 'e', "Perform encryption operation");
    // Decryption (bool) - Whether to perform decryption
    parser.add("decrypt", 'd', "Perform decryption operation");

    // Key path (string) - Path to save the generated key
    parser.add<string>("key-path", 'p',
                       "Path to save the generated key, default current path",
                       false, "");
    // Key filename (string) - Filename for the generated key
    parser.add<string>("key-filename", 'f',
                       "Filename for the generated key, default named\"key\"",
                       false);

    // Input file (string) - Path to the input file/folder to be encrypted or
    // decrypted
    parser.add<string>("input-file", 'i', "Path to the input file", false);
    // Key file (string) - Path to the key file used for encryption or
    // decryption
    parser.add<string>("key-file", 'k', "Path to the encryption key file",
                       false);
    // Output path (string) - Path to save the encrypted or decrypted file(s)
    parser.add<string>(
        "output-path", 'o',
        "Path to save the output file(s) directory of input file(s)", false);
    // Key mode (oneof) - Key mode selection, such as 'AES' or 'RSA'
    parser.add<string>("key-mode", 'm', "Key mode for encryption [CBC, EBC]",
                       false, "AES", cmdline::oneof<string>("EBC", "CBC"));

    // Parse command-line arguments
    parser.parse_check(argc, argv);
}

int checkargs(cmdline::parser &parser) {
    // Check if only one mode is selected
    if (parser.exist("generate-key") + parser.exist("encrypt") +
            parser.exist("decrypt") !=
        1) {
        cerr << "Zero or multiple modes are selected. Please check whether the "
                "input parameters are correct"
             << endl;
        return -1;
    }

    // Check parameters for generating a key
    if (parser.exist("generate-key")) {
        return 1;
    }
    // Check parameters for encryption
    else if (parser.exist("encrypt")) {
        if (!parser.exist("input-file")) {
            cerr << "The current selection is encryption, but the input-file "
                    "path is missing"
                 << endl;
            return -1;
        }
        if (!parser.exist("key-file")) {
            cerr
                << "The current selection is encryption, but the key-file path "
                   "is missing"
                << endl;
            return -1;
        }
        if (!parser.exist("output-path")) {
            cerr << "The current selection is encryption, but the output-path "
                    "path is missing"
                 << endl;
            return -1;
        }
        if (!parser.exist("key-mode")) {
            cerr << "The current selection is encryption, but no key-mode is "
                    "selected"
                 << endl;
            return -1;
        }
        return 2;
    }
    // Check parameters for decryption
    else if (parser.exist("decrypt")) {
        if (!parser.exist("input-file")) {
            cerr << "The current selection is decryption, but the input-file "
                    "path is missing"
                 << endl;
            return -1;
        }
        if (!parser.exist("key-file")) {
            cerr
                << "The current selection is decryption, but the key-file path "
                   "is missing"
                << endl;
            return -1;
        }
        if (!parser.exist("output-path")) {
            cerr << "The current selection is decryption, but the output-path "
                    "path is missing"
                 << endl;
            return -1;
        }
        if (!parser.exist("key-mode")) {
            cerr << "The current selection is decryption, but no key-mode is "
                    "selected"
                 << endl;
            return -1;
        }
        return 3;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    // Parse the arguments
    cmdline::parser cmd;
    getparsers(argc, argv, cmd);

    // Check the arguments
    int mode = checkargs(cmd);
    // Generate key
    if (mode == 1) {
        Key key;
        cout << cmd.get<string>("key-path") << endl;
        bool result = key.key_create(cmd.get<string>("key-filename"),
                                     cmd.get<string>("key-path"));
        if (result == false) {
            return -1;
        }
    }
    // Encryption
    else if (mode == 2) {
        AES encoder(cmd.get<string>("input-file"), cmd.get<string>("key-file"),
                    cmd.get<string>("output-path"));
        encoder.encoder();
        cout << "Encryption completed: " << cmd.get<string>("output-path")
             << std::endl;
    }
    // Decryption
    else if (mode == 3) {
        AES decoder(cmd.get<string>("input-file"), cmd.get<string>("key-file"),
                    cmd.get<string>("output-path"));
        decoder.decoder();
        cout << "Decryption completed: " << cmd.get<string>("output-path")
             << std::endl;
    }
    return mode;
}
