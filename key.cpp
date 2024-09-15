#include "key.hpp"


bool Key::key_create(string name, string path) {
    vector<unsigned int> key = get_key();

    // Check whether the path is available
    std::filesystem::path dir_path(path);
    if (!std::filesystem::exists(dir_path) ||
        !std::filesystem::is_directory(dir_path)) {
        std::cerr << "Error: Path " << path << " is not valid or accessible."
                  << std::endl;
        return false;
    }

    // If name is empty, set the default file name
    if (name.empty()) {
        name = "key";
    }

    // Generate the file path and name
    std::filesystem::path file_path = dir_path / (name + ".key");
    int counter = 1;
    while (std::filesystem::exists(file_path)) {
        file_path = dir_path / (name + "_" + std::to_string(counter) + ".key");
        counter++;
    }

    // Save the key to a file
    std::ofstream outFile(file_path, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << file_path
                  << " for writing." << std::endl;
        return false;
    }
    outFile.write(reinterpret_cast<const char *>(key.data()),
                  key.size() * sizeof(unsigned int));
    outFile.close();

    std::cout << "Key successfully generated and saved to: " << file_path
              << std::endl;
    return true;
}

string Key::get_time_ms() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return std::to_string(millis);
}

vector<unsigned int> Key::get_key() {
    SHA256 sha256;
    std::string current_time = get_time_ms();
    sha256.calculateH(current_time);
    vector<unsigned int> key = sha256.getH();
    return key;
}

void SHA256::calculateH(const string &input) {
    init();
    std::vector<unsigned int> M = prepareMessage(input.c_str());
    Hash(M, H);
}

vector<unsigned int> SHA256::getH() {
    return vector<unsigned int>(H, H + sizeof(H) / sizeof(unsigned int));
}

void SHA256::init() { std::memcpy(H, H_init, sizeof(H)); };

std::vector<unsigned int> SHA256::prepareMessage(const std::string &input) {
    size_t size = input.size();
    size_t len = size + 1; // Including one byte of 0x80
    len = len + ((len % M_LEN < 56) ? (56 - len % M_LEN)
                                    : (120 - len % M_LEN)); // Pad to proper length

    std::vector<unsigned int> M(len / 4 + 2, 0);
    for (size_t i = 0; i < size; ++i)
        M[i / 4] |= (unsigned int)(input[i] & 0xFF) << ((3 - i % 4) * 8);
    M[size / 4] |= 0x80 << ((3 - size % 4) * 8); // Add 0x80

    size_t bit_len = size * 8;
    M[M.size() - 2] = (bit_len >> 32) & 0xFFFFFFFF; // Higher 32 bits
    M[M.size() - 1] = bit_len & 0xFFFFFFFF;         // Lower 32 bits

    return M;
}

void SHA256::Hash(std::vector<unsigned int> &M, unsigned int *H) {
    unsigned int W[64];
    unsigned int a, b, c, d, e, f, g, h, T1, T2;
    unsigned int H0 = H[0], H1 = H[1], H2 = H[2], H3 = H[3], H4 = H[4],
                 H5 = H[5], H6 = H[6], H7 = H[7];

    for (size_t i = 0; i < M.size(); i += 16) {
        // Prepare message schedule array W
        for (int t = 0; t < 16; ++t)
            W[t] = M[i + t];
        for (int t = 16; t < 64; ++t)
            W[t] =
                Sigma_o1(W[t - 2]) + W[t - 7] + Sigma_o0(W[t - 15]) + W[t - 16];

        // Initialize working variables
        a = H0; b = H1; c = H2; d = H3;
        e = H4; f = H5; g = H6; h = H7;

        // Main loop
        for (int t = 0; t < 64; ++t) {
            T1 = h + Sigma_E1(e) + Ch(e, f, g) + K[t] + W[t];
            T2 = Sigma_E0(a) + Maj(a, b, c);
            h = g;  g = f;  f = e;  e = d + T1;
            d = c;  c = b;  b = a;  a = T1 + T2;
        }
        // Compression
        H0 += a;    H1 += b;    H2 += c;    H3 += d;
        H4 += e;    H5 += f;    H6 += g;    H7 += h;
    }

    // Store the results in the H array
    H[0] = H0;  H[1] = H1;  H[2] = H2;  H[3] = H3;
    H[4] = H4;  H[5] = H5;  H[6] = H6;  H[7] = H7;
}
