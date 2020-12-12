from conans import CMake, ConanFile

class AdventOfCodeConan(ConanFile):
    name = 'advent-of-code'
    version = '2020.12.12'
    author = 'svanveen'

    default_user = 'svanveen'
    default_channel = 'stable'

    scm = {
        'type': 'git',
        'url': 'auto',
        'revision': 'auto',
    }

    generators = 'cmake'
    settings = 'os', 'compiler', 'build_type', 'arch'

    default_options = {
        'cmake:with_openssl': False
    }

    build_requires = [
        'cmake/[>=3.16]'
    ]

    requires = [
        'docopt.cpp/0.6.3',
        'gtest/1.10.0',
        'range-v3/0.11.0'
    ]

    no_copy_sources = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def deploy(self):
        self.copy('*')
