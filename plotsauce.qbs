import qbs 1.0

CppApplication {
    name: "plotsauce"

    type: "application"
    consoleApplication: true

    Depends { name: "Qt"; submodules: ["core", "xml", "gui"] }
    Depends { name: "cavern-3dReader" }
    Depends { name: "z" }

    cpp.cxxLanguageVersion: (Qt.core.versionMajor >= 5 && Qt.core.versionMinor >= 7 ? "c++11" : "c++98");
    cpp.includePaths: ["src"]

    Group {
        fileTagsFilter: ["application"]
        qbs.install: true
        qbs.installDir: project.installDir
    }

    files: [
        "main.cpp",
        "src/*.cpp",
        "src/*.h"
        //"src/survex/*.c",
        //"src/survex/*.h"
    ]
}
