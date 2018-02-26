/*
** DLLoaderManager.hpp for cpp_arcade in /home/anthony/repository/cpp_arcade/DLLoaderManager.hpp
**
** Made by Anthony LECLERC
** Login   <anthony.leclerc@epitech.eu>
**
** Started on  sam. mars 11 12:52:53 2017 Anthony LECLERC
// Last update Fri Mar 17 21:34:49 2017 Sylvain Chaugny
*/

#ifndef CPP_ARCADE_DLLOADERMANAGER_HPP
# define CPP_ARCADE_DLLOADERMANAGER_HPP

# include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include "DLInstanceLoader.hpp"
#include "DLLoaderFactory.hpp"
#include "FileSystem.hpp"
#include "path.hpp"

#ifdef UNIX
#	include <dirent.h>
#endif

namespace module {
  template <typename TInterface>
  class DLLoaderManager {
  public:

    using loader_type = DLInstanceLoader<TInterface>;

    typedef typename std::unordered_set<std::unique_ptr<loader_type> > Loaders;

    typedef typename Loaders::iterator       iterator;
    typedef typename Loaders::const_iterator const_iterator;

  private:
    Loaders _libs;

  public:
    DLLoaderManager() :
        _libs()
    {}

    DLLoaderManager(DLLoaderManager&&) = default;
    DLLoaderManager(DLLoaderManager const&) = default;

    ~DLLoaderManager() = default;

    /*
     * \brief iterator for Libraries -> from std::vector
     */
    iterator
    begin()
    { return _libs.begin(); }

    const_iterator
    begin() const
    { return _libs.begin(); }

    iterator
    end()
    { return _libs.end(); }

    const_iterator
    end() const
    { return _libs.end(); }

    loader_type *
    loadLibrary(fs::Path const& file)
    {
      auto loader = module::make::newFunctionLoader<TInterface>(file.path());
      if (!loader->isLoaded()) {
        return nullptr;
      }
      auto ret = _libs.insert(std::move(loader));
      return ret.second ? ret.first->get() : nullptr;
    }

    /*
     * \brief Unload the library pointed by the iterator and remove it from _libs
     * \param library	iterator to the library to be removed
     */
    void
    unloadLibrary(iterator library)
    {
      _libs.erase(library);
    }

    void unloadLibrary(const loader_type *l) {
      unloadLibrary(std::find_if(std::begin(_libs), std::end(_libs), [&](auto&& ptr) {
        return ptr.get() == l;
      }));
    }

    void
    unloadLibraries()
    {
      _libs.erase(_libs.begin(), _libs.end());
    }

    void
    unloadLibraries(iterator begin, iterator end)
    {
      _libs.erase(begin, end);
    }

    /*
     * if size == 0, then no library have been loaded
     */
    size_t
    size() const
    {
      return _libs.size();
    }
  };
}

#endif /* !CPP_ARCADE_DLLOADERMANAGER_HPP */
