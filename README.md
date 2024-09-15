# AES-256 Encryption Tool
This repository provides an AES-256 encryption tool that supports key generation, encryption, and decryption. Currently, only the **ECB** (Electronic Codebook) mode is implemented, but the framework is prepared to support other modes as well as GPU acceleration in future updates.

## Features
- Key Generation: Automatically generates a 256-bit key for AES encryption using the SHA256 algorithm.
- Encryption: Encrypts plaintext using AES-256 in ECB mode.
- Decryption: Decrypts ciphertext using AES-256 in ECB mode.
## Requirements
- C++17 or later
- Cmake 3.10 or later
## Build
~~~bash
mkdir build
cd build
cmake ..
cmake --build .
~~~
## Parameters

### 1. Operation Modes (One of the following must be selected)

- **`--generate-key` / `-g`**
  Generates a new encryption key using SHA-256.
  No other mode (encryption or decryption) can be selected with this option.
- **`--encrypt` / `-e`**
  Performs encryption of a file or folder. Requires the `--input-file`,`--output-path`,`--key-file` and `--key-mode` parameters.
- **`--decrypt` / `-d`**
  Performs decryption of a file or folder. Requires the `--input-file`,`--output-path`,`--key-file` and `--key-mode` parameters.

### 2. File Paths and Key Parameters

- **`--key-path` / `-p`** (Optional)
  Specifies the directory path to save the generated key. Defaults to the current directory.
- **`--key-filename` / `-f`** (Optional)
  Specifies the filename for the generated key. If not provided, the default filename is `"key"`.
- **`--input-file` / `-i`** (Required for encryption/decryption)
  Specifies the path to the input file or folder to be encrypted or decrypted.
  This parameter is **mandatory** for both encryption and decryption modes.
- **`--key-file` / `-k`** (Required for encryption/decryption)
  Specifies the path to the key file used for encryption or decryption.
  This parameter is **mandatory** for both encryption and decryption modes.
- **`--output-path` / `-o`** (Required for encryption/decryption)
  Specifies the directory where the output (encrypted or decrypted) file(s) should be saved.
  This parameter is **mandatory** for both encryption and decryption modes.

### 3. Key Mode

- `--key-mode` / `-m`

   (Optional)

  Specifies the encryption mode.

  Available options:

  - `EBC` (default): Electronic Codebook mode.

### 4. General Parameter Rules

- Only one operation mode can be selected at a time.
  The following are **mutually exclusive**:
  - `--generate-key`
  - `--encrypt`
  - `--decrypt`
- When performing **encryption** or **decryption**, both `--input-file` and `--key-file` are required.
  Failing to provide these will result in an error.
- When generating a key (`--generate-key`), you may optionally specify `--key-path` and `--key-filename` to control where and how the key is saved.

## Example Usage

### Key Generation

```
./aes_tool --generate-key -p /path/to/save/key -f my_key
```

Generates a new encryption key and saves it to `/path/to/save/key/my_key`.

### Encryption

```
./aes_tool --encrypt -i /path/to/input/file -k /path/to/key -o /path/to/output -m ECB
```

Encrypts the input file using the specified key and saves the output to the provided output path using the ECB mode.

### Decryption

```
./aes_tool --decrypt -i /path/to/encrypted/file -k /path/to/key -o /path/to/output -m ecb
```

Decrypts the input file using the specified key and saves the output, using the ECB mode.


## Supported Modes
At present, the tool only supports ECB mode. More modes like CBC, CFB, OFB, and GCM will be added in future releases.



## Open-Source License and Disclaimer

This program is released as open-source for the purpose of learning and technical exchange. The following sections outline the terms of the open-source license and the related disclaimer.

### Open-Source License

This program is distributed under the [MIT License](https://opensource.org/licenses/MIT). You are free to copy, modify, distribute, and use the source code, provided that you retain the original license notice and copyright information.

### Disclaimer

1. **Educational Purposes Only**
   This program is provided solely for educational and technical exchange purposes. **No security or reliability guarantees** are made. The developers make no warranties regarding the accuracy, completeness, performance, or fitness of the program for any particular purpose.
2. **No Security Guarantees**
   The encryption functionality of this program is intended only for learning purposes and **does not guarantee the security of encrypted data**. It is not recommended for use in any production environment or scenarios involving sensitive data. Users are solely responsible for any security risks, including data breaches, when using this program.
3. **Use at Your Own Risk**
   The developers shall not be liable for any damage caused to users' computer files, systems, or other data as a result of using or modifying this program. **Users assume full responsibility for all consequences of using this program**.
4. **Modifications and Redistribution**
   Users are permitted to modify and redistribute this program. However, any issues arising from such modifications, including but not limited to data loss, system damage, or information leakage, are the sole responsibility of the user. The developers are not liable for any risks introduced by modified versions of the program.



**Notice: By using this program, you acknowledge that you have read and agreed to this disclaimer, and that you understand and accept the responsibilities and risks outlined herein.**
