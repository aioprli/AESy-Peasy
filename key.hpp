
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Key {
  public:
    // crate a key based on time now
    bool key_create(string name = "", string path = "");

    // get the encrypted array based on the key
    bool get_encrypted_array(string path = "");

    // get the encryption/decryption char/string based on encrypted array
    char xor_char(char c);
    string xor_string(string s);

  private:
    // encrypted array
    vector<char> _key;

    // parameters
    int _flag = 0;
    int _step = 1;
    int _length = 4;
    int _maxlength = 1200;
};
