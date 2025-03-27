from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.scm import Version
from conan.errors import ConanInvalidConfiguration

class FastDDSQMLAppConan(ConanFile):
    name = "fastdds_qml_app"
    version = "1.0.0"
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True
    }
    
    # Sources are in the same folder as this recipe
    exports_sources = "CMakeLists.txt", "src/*", "resources.qrc"
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def configure(self):
        # Dynamically set Qt options
        self.options["qt/*"].shared = True
        self.options["qt/*"].qtquickcontrols = True
        self.options["qt/*"].qtquickcontrols2 = True
        self.options["qt/*"].qtdeclarative = True
        self.options["qt/*"].qttools = True
        self.options["qt/*"].with_vulkan = False
    
    def layout(self):
        cmake_layout(self)
    
    def requirements(self):
        self.requires("fast-dds/2.14.3")
        self.requires("qt/5.15.16")

    def validate(self):
        # Validate compiler supports C++20
        if self.settings.compiler == "gcc" and Version(self.settings.compiler.version) < Version("10"):
            raise ConanInvalidConfiguration("GCC >= 10 is required for C++20 support")
        if self.settings.compiler == "clang" and Version(self.settings.compiler.version) < Version("10"):
            raise ConanInvalidConfiguration("Clang >= 10 is required for C++20 support")
        if self.settings.compiler == "msvc" and Version(self.settings.compiler.version) < Version("16"):
            raise ConanInvalidConfiguration("Visual Studio 2019 or higher is required for C++20 support")
    
    def generate(self):
        # Generate CMake toolchain file
        tc = CMakeToolchain(self)
        tc.generator = "Ninja"  # Use Ninja as the generator
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = self.options.get_safe("fPIC", True)
        tc.variables["CMAKE_CXX_STANDARD"] = "20"  # Set C++20 in toolchain
        tc.generate()
        
        # Generate CMake dependency files
        deps = CMakeDeps(self)
        deps.generate()
    
    def build(self):
        from conan.tools.cmake import CMake
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        from conan.tools.cmake import CMake
        cmake = CMake(self)
        cmake.install()
    
    def imports(self):
        # Copy shared libraries to the bin folder for Windows
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dll", dst="bin", src="lib")
        
        # For MacOS
        self.copy("*.dylib*", dst="bin", src="lib")