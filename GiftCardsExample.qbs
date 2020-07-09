import qbs

Application {
    Depends { name: "Qt.quick" }

    property pathList qmlImportPaths: ["qml"]

    cpp.cxxLanguageVersion: "c++17"

    cpp.includePaths: "Source"

    files: [
        "Source/GiftCard.cpp",
        "Source/GiftCard.h",
        "Source/GiftCardModel.cpp",
        "Source/GiftCardModel.h",
        "Source/Main.cpp",
        "Qml/Qml.qrc",
        "Source/Provider.cpp",
        "Source/Provider.h",
        "Source/Providers.cpp",
        "Source/Providers.h",
        "Source/ProvidersModel.cpp",
        "Source/ProvidersModel.h",
    ]

    Group {
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
