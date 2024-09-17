# File Signature Generator

This is a simple C++ console program that generates a signature for a specified file. The program divides the input file into fixed-size blocks, computes a hash for each block, and writes the hashes to an output signature file.

## Features
- Split a file into blocks of equal length.
- Compute a hash for each block.
- Save the computed signature (hashes of all blocks) to an output file.
- Handle different block sizes (default is 1 MB).
- Command-line interface for flexibility.

## Installation

1. Clone the repository:
```bash
git clone git@github.com:i-gap4uk/FileSignatureGenerator.git
cd FileSignatureGenerator
```

2. Build the project by bash script:
```bash
./build.sh
```

## Usage

Run the program from the command line using the following syntax:
```bash
cd build/
./file_signature_generator -i <input_file> -o <output_file> -bs <block_size>
```
- **-i <input_file>**: Path to the input file for which the signature will be generated **[Mandatory]**.
- **-o <output_file>**: Path to the output file where the signature (hashes) will be saved **[Optional]**.
- **-bs <block_size>**: Size of the blocks in megabytes. The default block size is 1 MB (1048576 bytes) **[Optional]**.

## Example
```bash
./file_signature_generator -i input.txt -o signature.txt -bs 1
```

**In this example:**

**input.txt** - is the file to be processed.
**signature.txt** - is the file where the generated signature will be saved.
**1** - (1 MB) is the block size.

## Implementation Details
- The program divides the input file into blocks of equal size.
- If the file size is not a multiple of the block size, the last block is padded with zeros to match the block size.
- A hash is computed for each block and stored in the output signature file.