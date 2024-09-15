#ifndef AESEBC_HPP
#define AESEBC_HPP
#include "AES_base.hpp"

class AESECB : public AESBase {
  public:
    AESECB() = default;
    ~AESECB() = default;
    std::vector<Byte> encode(const std::vector<Byte> &plaintext) override;
    std::vector<Byte> decode(const std::vector<Byte> &ciphertext) override;
};
#endif