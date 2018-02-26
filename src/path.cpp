//
// Path.cpp for cpp_zia in /home/anthony/repository/cpp_zia/Path.cpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  lun. févr. 19 04:48:33 2018 Anthony LECLERC
// Last update lun. févr. 19 04:48:33 2018 Anthony LECLERC
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include "path.hpp"

fs::Path::Path(std::string const& path, std::string const& separator) :
    _complete(path),
    _separator(separator)
{
  auto sep_path = std::find_end(path.begin(), path.end(),
                                separator.begin(), separator.end());

  setPath( { path.begin(), sep_path });
  if (sep_path != path.end())
    ++sep_path;
  if (sep_path != path.end())
	  setFile({ sep_path, path.end() });
  else
	  setFile("");
}

fs::Path::Path(char const *s, std::string const& separator) : Path(std::string(s), separator)
{}

fs::Path& fs::Path::setExtension(std::string const& string)
{
  _extension = string;
  if (_extension[0] != '.')
    _extension = '.' + _extension;
  updateFile();
  return *this;
}

fs::Path::Path(Path const&) = default;

fs::Path::Path(Path&&) = default;

fs::Path::~Path() = default;

fs::Path& fs::Path::setPath(std::string const& path)
{
  std::vector<std::string>().swap(_path);
  std::string::size_type b = 0;

  while ((b = path.find_first_not_of(_separator, b)) != std::string::npos) {
	  auto e = path.find_first_of(_separator, b);
	  _path.push_back(path.substr(b, e - b));
	  b = e;
  }
  _fullpath = path + _separator;
  updateComplete();
  return *this;
}

fs::Path& fs::Path::setStem(std::string const& stem)
{
  _stem = stem;
  updateFile();
  return *this;
}

fs::Path& fs::Path::setSeparator(std::string const& string)
{
  _separator = string;
  return *this;
}

fs::Path& fs::Path::setFile(std::string const& file)
{
  _extension = {};
  auto ext = file.find_last_of('.');
  if (ext != 0)
  {
    _stem = std::string (&file[0], &file[ext == file.npos ? file.size() : ext]);
    if (ext != file.npos)
    {
      _extension = std::string (&file[ext], &file[file.size()]);
    }
  }
  else
  {
    _stem = file;
  }
  updateFile();
  return *this;
}

fs::Path& fs::Path::appendPath(std::string const& last_path)
{
  _path.emplace_back(last_path);
  updatePath();
  return *this;
}

fs::Path& fs::Path::operator/=(std::string const& string)
{
  return (this->appendPath(string));
}

std::string const& fs::Path::extension() const
{
  return _extension;
}

std::string const& fs::Path::fullPath() const
{
  return _fullpath;
}

std::string const& fs::Path::stem() const
{
  return _stem;
}

std::string const& fs::Path::file() const
{
  return _file;
}

bool fs::Path::hasExtension() const
{
  return _extension.size() > 0;
}

fs::Path& fs::Path::removeLastPath()
{
  _path.pop_back();
  updatePath();
  return *this;
}

std::string const& fs::Path::operator[](std::size_t index) const
{
  return _path.at(index);
}

std::string& fs::Path::operator[](std::size_t index)
{
  return _path.at(index);
}

void fs::Path::updateFile()
{
  _file = _stem + _extension;
  updateComplete();
}

void fs::Path::updateComplete()
{
  _complete = _fullpath + _file;
}

std::string const& fs::Path::path() const
{
  return _complete;
}

void fs::Path::updatePath()
{
  std::stringstream ss;
  std::copy(_path.begin(), _path.end(), std::ostream_iterator<std::string>(ss, _separator.c_str()));
  _fullpath = ss.str();
  updateComplete();
}

bool fs::Path::operator==(fs::Path const& rhs) const
{
  return _complete == rhs._complete;
}

bool fs::Path::operator!=(fs::Path const& rhs) const
{
  return !(rhs == *this);
}

std::ostream& fs::operator<<(std::ostream& os, fs::Path const& p)
{
  os << p.path();
  return os;
}
