#include "AES_base.hpp"

void AESBase::KeyExpansion(const Key256 &key) {
    expandedKey.resize(15, Block{});
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 16; ++j) {
            expandedKey[i][j] = key[16 * i + j];
        }
    }
    for (size_t i = 2; i < 15; ++i) {
        size_t last = i - 2;
        if (i % 2 == 0) {
            std::vector<Byte> mid(4);
            for (size_t j = 0; j < 4; ++j) {
                mid[j] = expandedKey[last][j];
            }
            std::rotate(mid.begin(), mid.begin() + 1, mid.end());
            for (size_t j = 0; j < 4; ++j) {
                expandedKey[i][j] = S_Box[mid[j] >> 4][mid[j] & 0x0F] ^
                                    Rcon[i - 1] ^
                                    expandedKey[last][(j + 16 - 4) % 16];
            }
        } else {
            for (size_t j = 0; j < 4; ++j) {
                expandedKey[i][j] = expandedKey[last - 1][(j + 16 - 4) % 16] ^
                                    expandedKey[last][j];
            }
        }
        for (size_t j = 4; j < 16; ++j) {
            expandedKey[i][j] = expandedKey[last][j - 4] ^ expandedKey[last][j];
        }
    }
}
void AESBase::EncryptBlock(Block &block) {
    AddRoundKey(block, expandedKey[0]);
    for (size_t i = 1; i < 14; ++i) {
        SubBytes(block);
        ShiftRows(block);
        MixColumns(block);
        AddRoundKey(block, expandedKey[i]);
    }
    SubBytes(block);
    ShiftRows(block);
    AddRoundKey(block, expandedKey[14]);
}
void AESBase::DecryptBlock(Block &block) {
    InvAddRoundKey(block, expandedKey[14]);
    InvShiftRows(block);
    InvSubBytes(block);
    for (size_t i = 13; i > 0; --i) {

        InvAddRoundKey(block, expandedKey[i]);
        InvMixColumns(block);
        InvShiftRows(block);
        InvSubBytes(block);
    }
    InvAddRoundKey(block, expandedKey[0]);
}

void AESBase::SubBytes(Block &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = S_Box[data[i] >> 4][data[i] & 0x0F];
    }
}

void AESBase::InvSubBytes(Block &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = Inv_S_Box[data[i] >> 4][data[i] & 0x0F];
    }
}

void AESBase::ShiftRows(Block &data) {
    for (size_t i = 0; i < 4; ++i) {
        std::rotate(data.begin() + i * 4, data.begin() + i * 4 + i,
                    data.begin() + i * 4 + 4);
    }
}
void AESBase::InvShiftRows(Block &data) {
    for (size_t i = 0; i < 4; ++i) {
        std::rotate(data.begin() + i * 4, data.begin() + i * 4 + (4 - i),
                    data.begin() + i * 4 + 4);
    }
}

void AESBase::MixColumns(Block &data) {
    std::array<Byte, 4> temp;
    for (size_t x = 0; x < 4; ++x) {
        temp[0] = GF_mul(data[0 + x], MixArray[0][0]) ^
                  GF_mul(data[4 + x], MixArray[0][1]) ^
                  GF_mul(data[8 + x], MixArray[0][2]) ^
                  GF_mul(data[12 + x], MixArray[0][3]);
        temp[1] = GF_mul(data[0 + x], MixArray[1][0]) ^
                  GF_mul(data[4 + x], MixArray[1][1]) ^
                  GF_mul(data[8 + x], MixArray[1][2]) ^
                  GF_mul(data[12 + x], MixArray[1][3]);
        temp[2] = GF_mul(data[0 + x], MixArray[2][0]) ^
                  GF_mul(data[4 + x], MixArray[2][1]) ^
                  GF_mul(data[8 + x], MixArray[2][2]) ^
                  GF_mul(data[12 + x], MixArray[2][3]);
        temp[3] = GF_mul(data[0 + x], MixArray[3][0]) ^
                  GF_mul(data[4 + x], MixArray[3][1]) ^
                  GF_mul(data[8 + x], MixArray[3][2]) ^
                  GF_mul(data[12 + x], MixArray[3][3]);
        for (size_t y = 0; y < 4; ++y) {
            data[y * 4 + x] = temp[y];
        }
    }
}
void AESBase::InvMixColumns(Block &data) {
    std::array<Byte, 4> temp;
    for (size_t x = 0; x < 4; ++x) {
        temp[0] = GF_mul(data[0 + x], InvMixArray[0][0]) ^
                  GF_mul(data[4 + x], InvMixArray[0][1]) ^
                  GF_mul(data[8 + x], InvMixArray[0][2]) ^
                  GF_mul(data[12 + x], InvMixArray[0][3]);
        temp[1] = GF_mul(data[0 + x], InvMixArray[1][0]) ^
                  GF_mul(data[4 + x], InvMixArray[1][1]) ^
                  GF_mul(data[8 + x], InvMixArray[1][2]) ^
                  GF_mul(data[12 + x], InvMixArray[1][3]);
        temp[2] = GF_mul(data[0 + x], InvMixArray[2][0]) ^
                  GF_mul(data[4 + x], InvMixArray[2][1]) ^
                  GF_mul(data[8 + x], InvMixArray[2][2]) ^
                  GF_mul(data[12 + x], InvMixArray[2][3]);
        temp[3] = GF_mul(data[0 + x], InvMixArray[3][0]) ^
                  GF_mul(data[4 + x], InvMixArray[3][1]) ^
                  GF_mul(data[8 + x], InvMixArray[3][2]) ^
                  GF_mul(data[12 + x], InvMixArray[3][3]);
        for (size_t y = 0; y < 4; ++y) {
            data[y * 4 + x] = temp[y];
        }
    }
}

void AESBase::AddRoundKey(Block &data, const Block &key) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key[i];
    }
}
void AESBase::InvAddRoundKey(Block &data, const Block &key) {
    AddRoundKey(data, key);
}

Byte AESBase::GF_mul(Byte a, Byte b) {
    Byte result = 0;
    Byte p = 0x1B;
    Byte carry;
    for (size_t i = 0; i < 8; ++i) {
        if (b & 1)
            result ^= a;
        carry = a & 0x80;
        a <<= 1;
        if (carry)
            a ^= p;
        b >>= 1;
    }
    return result;
}