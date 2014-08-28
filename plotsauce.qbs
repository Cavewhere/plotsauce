import qbs 1.0

CppApplication {
    name: "plotsauce"

    type: "application"
    consoleApplication: true

    Depends { name: "Qt"; submodules: ["core", "xml", "gui"] }
    Depends { name: "cavern-3dReader" }

    cpp.includePaths: ["src"]
    cpp.dynamicLibraries: ["z"]

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
