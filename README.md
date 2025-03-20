<h1 align="center">Matrix Chain</h1>

## Description

 Implementation of algorithm for fast multiplication of matrix chain.

## How to integrate
 
 use [storage](https://github.com/baitim/ConanPackages), project = "matrix_chain", version = "1.0", user = "baitim"

## Requirements

* Cmake >= 3.30.8 <br>
    ### How to install Cmake 3.30.8 Linux/macOS:
1. **Download** the archive with the required CMake version from the official website: [Download CMake](https://cmake.org/download/).
2. **Unpack** the archive<br>
    <code>sudo tar -xzvf cmake-3.30.8-linux-x86_64.tar.gz -C /opt/</code>
3. **Set PATH** <br>
    <code>echo 'export PATH=/opt/cmake-3.30.8-linux-x86_64/bin:$PATH' >> ~/.bashrc</code><br>
    <code>source ~/.bashrc</code><br>
    or a similar one for your shell
4. **Check** the CMake version <br>
    <code>cmake --version</code>

## How to run

1. Clone <br>
    <code>git clone https://github.com/baitim/MatrixChain.git</code>

2. Go to folder <br>
    <code>cd MatrixChain</code>

3. Prepare conan <br>
    conan installation: <code>uv sync --group dev; source .venv/bin/activate</code><br>
    <code>conan profile detect --force</code>

4. Add conan required packages from [storage](https://github.com/baitim/ConanPackages)<br>
    <code>conan remote add conan_packages http://188.225.84.75:9300</code>

5. Init dependencies <br>
    <code>conan install . --build=missing</code><br>
    maybe you will need these flags for the conan <code>-s build_type=Debug</code>

6. Build <br>
    <code>cmake --preset release; cmake --build build/Release</code>

7. Run <br>
    <code>./build/Release/src/matrix_chain</code>

## How to test

* Testing
    - End to end & Unit<br>
        <code>ctest --test-dir build/Release --output-on-failure</code>

## How to compare

* Preparing
    write <code>cd compare</code> in terminal <br>
    write <code>python3 generate.py</code> in terminal <br>

* Comparing
    write <code>python3 compare.py</code> in terminal <br>
    The result of the comparison will be in the "compare.out" and "ratios.png" file

<p align="center"><img src="https://github.com/baitim/MatrixChain/blob/main/compare/ratios.png" width="80%"></p>

<p align="center"><img src="https://github.com/baitim/MatrixChain/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**