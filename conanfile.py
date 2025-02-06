from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class matrixChainRecipe(ConanFile):
    name = "matrix_chain"
    version = "1.0"

    license = ""
    author = ""
    url = ""
    description = "matrix_chain"
    topics = ""

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    requires = "gtest/1.15.0", "matrix/1.0"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "tests/*", "compare/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "config")
        self.cpp_info.set_property("cmake_file_name", "MatrixChain")
        self.cpp_info.set_property("cmake_target_name", "MatrixChain::MatrixChain")
        self.cpp_info.libs = ["matrix_chain"]
        self.cpp_info.includedirs = ["include"]