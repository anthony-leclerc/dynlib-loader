//
// DirectoryLoader.hpp for cpp_zia in /home/anthony/repository/cpp_zia/DirectoryLoader.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  mar. févr. 20 12:37:00 2018 Anthony LECLERC
// Last update mar. févr. 20 12:37:00 2018 Anthony LECLERC
//

#pragma once

#include <unordered_set>
#include <iostream>
#include "path.hpp"
#include "FileSystem.hpp"

namespace module {
  namespace detail {

    template<typename TInterface>
    class DirectoryLoader : public DLLoaderManager<TInterface> {
    public:

      using Base = DLLoaderManager<TInterface>;

      DirectoryLoader() = default;

      DirectoryLoader(fs::Path const& directory) :
          Base(),
          _directory(directory)
      {}

      std::size_t loadLibraries()
      {
          fs::FolderDescriptor directory_view(_directory.path());

          if (!directory_view) {
            return 0;
          }

          std::size_t count{0};
          while (directory_view.hasNext()) {
            auto file = directory_view.next();
            if (file.isFile()) {
              fs::Path filepath(_directory);
              // Add folder path to the file name
              filepath.setFile(file.name());
              std::cout << filepath.path() << std::endl;
              if (loadLibrary(filepath)) {
                ++count;
              }
            }
          }
          return count;
      }

      bool loadLibrary(fs::Path const& path) {
        return Base::loadLibrary(path) != nullptr;
      }

    private:
      fs::Path _directory;
    };

  }
}