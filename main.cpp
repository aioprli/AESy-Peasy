#include <cmdline.hpp>
#include <iostream>
using namespace std;

void getparsers(int argc, char *argv[], cmdline::parser &parser) {
    // 生成选择密钥 (bool) - 是否生成新的密钥
    parser.add("generate-key", 'g', "Generate a new encryption key");
    // 加密 (bool) - 是否执行加密操作
    parser.add("encrypt", 'e', "Perform encryption operation");
    // 解密 (bool) - 是否执行解密操作
    parser.add("decrypt", 'd', "Perform decryption operation");

    // 生成密钥路径 (string) - 保存生成的密钥的路径
    parser.add<string>("key-path", 'p',
                       "Path to save the generated key, default current path",
                       false, "");
    // 密钥文件名 (string) - 生成密钥的文件名
    parser.add<string>("key-filename", 'f',
                       "Filename for the generated key, default named\"key\"",
                       false);

    // 输入文件 (string) - 需要加密或解密的输入文件/文件夹路径
    parser.add<string>("input-file", 'i', "Path to the input file", false);
    // 密钥文件 (string) - 用于加密或解密的密钥文件路径
    parser.add<string>("key-file", 'k', "Path to the encryption key file",
                       false);
    // 输出路径 (string) - 加密或解密后的文件保存路径
    parser.add<string>("output-path", 'o',
                       "Path to save the output file(s), default same as root "
                       "directory of input file(s)",
                       false);
    // 密钥模式 (oneof) - 密钥模式选择，如 'AES' 或 'RSA'
    parser.add<string>("key-mode", 'm', "Key mode for encryption [AES, RSA]",
                       false, "AES", cmdline::oneof<string>("AES", "RSA"));

    // 解析命令行参数
    parser.parse_check(argc, argv);
}

int checkargs(cmdline::parser &parser) {
    // 检查是否只有一种模式
    if (parser.exist("generate-key") + parser.exist("encrypt") +
            parser.exist("decrypt") !=
        1) {
        cerr << "Multiple modes are selected. Please check whether the input "
                "parameters are correct"
             << endl;
        return -1;
    }

    // 生成密钥参数检查
    if (parser.exist("generate-key")) {
        return 1;
    }
    // 加密参数检查
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
        if (!parser.exist("key-mode")) {
            cerr << "The current selection is encryption, but no key-mode is "
                    "selected"
                 << endl;
            return -1;
        }
        return 2;
    }
    // 解密参数检查
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
    // 解析参数
    cmdline::parser cmd;
    getparsers(argc, argv, cmd);

    // 检查参数
    int mode = checkargs(cmd);
    // 生成密钥
    if (mode == 1) {

    }
    // 加密
    else if (mode == 2) {

    }
    // 解密
    else if (mode == 3) {
    }
    return mode;
}
