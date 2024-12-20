<h1 align="center">Matrix Chain</h1>

## Description

 Implementation of algorithm for fast multiplication of matrix chain.

## How to run

1. Clone <br>
    <code>git clone https://github.com/baitim/MatrixChain.git</code>

2. Go to folder <br>
    <code>cd MatrixChain</code>

3. Prepare conan <br>
    <code>conan profile detect --force</code>

4. Init dependencies <br>
    <code>conan install . --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True -s compiler.cppstd=gnu20</code> <br>
    maybe you will need these flags for the conan <code>-s build_type=Debug</code>

5. Init submodules <br>
    <code>git submodule update --init --recursive</code>

6. Build <br>
    <code>cmake . -B build -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake; cmake --build build</code>

7. Run <br>
    <code>./build/src/matrix_chain</code>

## How to test

* Testing
    - End to end & Unit<br>
        <code>ctest --test-dir build --output-on-failure</code>

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