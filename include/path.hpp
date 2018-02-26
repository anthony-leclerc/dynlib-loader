//
// PathBuilder.hpp for cpp_zia in /home/anthony/repository/cpp_zia/PathBuilder.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  lun. févr. 19 03:58:49 2018 Anthony LECLERC
// Last update lun. févr. 19 03:58:49 2018 Anthony LECLERC
//

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "Export.hpp"

namespace fs {

  class Path {
  public:
    Path() = default;
	
    Path(char const *s, std::string const& separator = "/");
    Path(std::string const& path, std::string const& separator = "/");

	Path(Path const&);
	Path(Path&&);

	~Path();

    Path&
    setExtension(std::string const& string);

    Path&
    setPath(std::string const& string);

    Path&
    setFile(std::string const& string);

    Path&
    setStem(std::string const& string);

    Path&
    setSeparator(std::string const& string);

    Path&
    appendPath(std::string const& string);

    Path&
    operator/=(std::string const& string);

    Path&
    removeLastPath();

    std::string const&
    path() const;

    std::string const&
    extension() const;

    std::string const&
    fullPath() const;

    std::string const&
    stem() const;

    std::string const&
    file() const;

    bool
    hasExtension() const;

    inline auto
    begin()
    { return _path.begin(); }

    inline auto
    end()
    { return _path.end(); }

    std::string const&
    operator[](std::size_t index) const;

    std::string&
    operator[](std::size_t index);

    bool
    operator==(Path const& rhs) const;

    bool
    operator!=(Path const& rhs) const;

  private:

    std::string _complete;

    /// File part
    std::string _stem{};
    std::string _extension{};
    std::string _file{};

    /// Path part
    std::vector<std::string> _path{};
    std::string              _fullpath{};
    std::string              _separator{"/"};

    auto
    nextSeparator(
        std::string::const_iterator begin,
        std::string::const_iterator end) const
    {
      return std::search(begin, end, _separator.cbegin(), _separator.cend());
    }

    void
    updateComplete();

    void
    updateFile();

    void
    updatePath();
  };

	std::ostream& operator<<(std::ostream& os, Path const& p);
}

namespace std {

  template <>
  struct hash<fs::Path> {

    inline std::size_t
    operator()(fs::Path const& p) const
    {
      return std::hash<std::string>()(p.path());
    }
  };

}
