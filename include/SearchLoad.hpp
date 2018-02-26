//
// SearchLoad.hpp for cpp_zia in /home/anthony/repository/cpp_zia/SearchLoad.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  mar. févr. 20 04:53:02 2018 Anthony LECLERC
// Last update mar. févr. 20 04:53:02 2018 Anthony LECLERC
//

#ifndef CPP_ZIA_SEARCHLOAD_HPP
#define CPP_ZIA_SEARCHLOAD_HPP

#include <unordered_set>
#include <unordered_map>
#include "DLLoaderManager.hpp"

namespace module {

  namespace detail {

    template <typename TInterface>
    class SearchLoader : public DLLoaderManager<TInterface> {
    public:

      using Base = DLLoaderManager<TInterface>;
      using loader_type = typename Base::loader_type;
      using LibrarySet = std::unordered_map<std::string, loader_type *>;

      SearchLoader() = default;

      template<typename TString>
      SearchLoader(std::initializer_list<TString> l) :
          Base(), _libnames(l.begin(), l.end()), _libpaths{ fs::Path("./") }, _loadedLibraries()
      {}

      template<typename TContainer>
      SearchLoader(TContainer&& libnames) : Base(),
        _libnames(libnames), _libpaths{ fs::Path("./") }, _loadedLibraries()
      {}

      template <typename TContainer, typename UContainer>
      SearchLoader(
          TContainer&& libnames,
          UContainer&& folders)
          : Base()
		  , _loadedLibraries()
          , _libnames(libnames.begin(), libnames.end())
          , _libpaths(folders.begin(), folders.end())
      {
        loadLibraries();
      }

      /// @brief Load all libraries by searching directory path and library names.
      /// Will deload previous loaded library that have been removed by name.
      /// Unmodified libraries will stay loaded.
      /// @return Number of libraries loaded (with previously loaded libraries).
      std::size_t
      loadLibraries()
      {
        /// On Added lib
        for (auto&& name : _libnames)
        {
          if (_loadedLibraries.find(name) == _loadedLibraries.end())
          {
            loadLibrary(name);
          }
        }
        return _loadedLibraries.size();
      }
      
      bool loadLibrary(std::string const& s) {

        for (auto path : _libpaths) {

          #if WIN32
          path.setStem(s).setExtension(".dll");
          #else
          path.setStem("lib" + s)
              .setExtension(".so");
          #endif

          auto loader = Base::loadLibrary(path);
          if (loader)
          {
            std::cout << "Loaded: " << s << std::endl;
            _loadedLibraries.emplace(s, loader);
            return true;
          }
        }
        return false;
      }

      void addLibrary(std::string const& name) {
        _libnames.insert(name).second;
      };

      bool removeLibrary(std::string const& name) {
        return _libnames.erase(name) > 0;
      }

      void removeLibraries() {
        std::unordered_set<std::string>().swap(_libnames);
      }

      void addHintFolder(fs::Path const& path) {
		  std::cout << "Insert: " << path << std::endl;
		  _libpaths.insert(path);
      }

      bool removeHintFolder(fs::Path const& path) {
        return _libpaths.erase(path) > 0;
      }

      void removeHints() {
        std::unordered_set<fs::Path>().swap(_libpaths);
      }

      void unloadLibraries() {
        /// On Deleted lib
        for (auto it = std::begin(_loadedLibraries); it != std::end(_loadedLibraries); ) {
          if (_libnames.find(it->first) == std::end(_libnames))
          {
            Base::unloadLibrary(it->second);
            it = _loadedLibraries.erase(it);
          }
          else
            ++it;
        }
      }

      inline loader_type& operator[](std::string const& s) {
        return *_loadedLibraries.at(s);
      }
      inline loader_type const& operator[](std::string const& s) const {
        return *_loadedLibraries.at(s);
      }

    private:
      
      std::unordered_set<fs::Path>    _libpaths;
      std::unordered_set<std::string> _libnames;

      LibrarySet _loadedLibraries;
    };

  }
}

#endif /* CPP_ZIA_SEARCHLOAD_HPP */
