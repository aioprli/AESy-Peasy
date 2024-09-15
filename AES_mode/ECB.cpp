#include "ECB.hpp"
std::vector<Byte> AESECB::encode(const std::vector<Byte> &plaintext) {
    std::vector<Byte> ciphertext;
    for (size_t i = 0; i < plaintext.size(); i += 16) {
        Block currentBlock = {};
        size_t blockSize =
            std::min(plaintext.size() - i, static_cast<size_t>(16));
        std::memcpy(currentBlock.data(), plaintext.data() + i, blockSize);

        // If the block is smaller than 16 bytes, pad the remaining part
        if (blockSize < 16) {
            std::memset(currentBlock.data() + blockSize, 16 - blockSize,
                        16 - blockSize);
        }
        EncryptBlock(currentBlock);
        ciphertext.insert(ciphertext.end(), currentBlock.begin(),
                          currentBlock.end());
    }

    // If the plaintext length is a multiple of 16 bytes, add a full padding
    // block
    if (plaintext.size() % 16 == 0) {
        Block paddingBlock = {};
        std::memset(paddingBlock.data(), 16, 16);
        EncryptBlock(paddingBlock);
        ciphertext.insert(ciphertext.end(), paddingBlock.begin(),
                          paddingBlock.end());
    }

    return ciphertext;
}

std::vector<Byte> AESECB::decode(const std::vector<Byte> &ciphertext) {
    if (ciphertext.size() % 16 != 0) {
        throw std::invalid_argument("Ciphertext size is not a multiple of 16. "
                                    "Possible invalid encrypted file.");
    }

    std::vector<Byte> plaintext;
    for (size_t i = 0; i < ciphertext.size(); i += 16) {
        Block currentBlock = {};
        std::memcpy(currentBlock.data(), ciphertext.data() + i, 16);
        DecryptBlock(currentBlock);
        plaintext.insert(plaintext.end(), currentBlock.begin(),
                         currentBlock.end());
    }

    // Remove padding
    if (!plaintext.empty()) {
        Byte paddingValue = plaintext.back();
        if (paddingValue > 0 && paddingValue <= 16) {
            plaintext.resize(plaintext.size() - paddingValue);
        } else {
            throw std::runtime_error(
                "Invalid padding value detected. Decryption failed.");
        }
    }

    return plaintext;
}