# Feistel Cipher over GF(2^8)

A small C++17 command-line tool that encrypts and decrypts files with a Feistel cipher on 16-bit blocks. The round function multiplies bytes in GF(2^8), reduced by the AES polynomial `x^8 + x^4 + x^3 + x + 1` (`0x11B`).

## Build

```sh
make          # builds ./program
make clean    # removes object files and the binary
```

Needs `clang++` (set in the Makefile as `CXX`).

## Usage

```sh
./program <input_file> <output_file> <key> <e|d>
```

- `e` encrypts, `d` decrypts.
- Each character of the key is one round key, so **the key length is the number of rounds**.

Example:

```sh
./program testfile.txt cipher.bin mysecret e
./program cipher.bin plain.txt mysecret d
```

## How it works

- The file is read as bytes and split into 2-byte blocks `(L, R)`.
- Each round does `L, R = R, L XOR gf_mul(R, k_i)`, where `k_i` is the i-th key byte.
- After the last round, the two halves are swapped.
- Decryption runs the same steps with the key bytes in reverse order.
- If the file has an odd number of bytes, the last byte is copied through **unencrypted**.

## Files

| File | Purpose |
|------|---------|
| `main.cpp` | Parses arguments and calls the cipher |
| `feistel.h/.cpp` | File I/O and the Feistel rounds (`feistel_16::process`) |
| `poly.h/.cpp` | GF(2^8) polynomial helpers: degree, division, multiplication |
| `my_file.h/.cpp` | File-size helper (not used by the current build) |
| `test.cpp` | Earlier prototype of the cipher (not built by the Makefile) |
| `testfile.txt` | Sample plaintext |

## Caveats

This is a course project and is not secure. The block size is 16 bits, there is no key schedule, and the key byte `0` makes its round function return 0.
