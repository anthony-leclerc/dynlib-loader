CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
project(cpp_zia CXX)

set (LIBLOADER_HEADERS
        include/DLLoaderManager.hpp
        include/DLLoaderFactory.hpp
        include/DLInstanceLoader.hpp
        include/FileSystem.hpp
        include/SearchLoad.hpp
        include/Libloader.hpp
        include/DirectoryLoader.hpp)

set(LIBLOADER_IMPL
        include/impl/ImplDllLoader.hpp
        include/impl/types.hpp
        src/path.cpp)

include_directories(include)

if (WIN32)
    set(WINDOWS_EXPORT_ALL_SYMBOLS true)
    set (LIBLOADER_IMPL ${LIBLOADER_IMPL}
            src/impl/win32DllLoader.cpp
            src/impl/win32FileSystem.cpp)
else()
    set (LIBLOADER_IMPL ${LIBLOADER_IMPL}
            src/impl/unixFileSystem.cpp
            src/impl/unixDllLoader.cpp)
endif()

#add_subdirectory(test)

add_library(dlloader SHARED ${LIBLOADER_IMPL} ${LIBLOADER_HEADERS})

if (UNIX)
    target_link_libraries(dlloader dl)
endif()