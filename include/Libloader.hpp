//
// Libloader.hpp for cpp_zia in /home/anthony/repository/cpp_zia/Libloader.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  mar. févr. 20 05:18:42 2018 Anthony LECLERC
// Last update mar. févr. 20 05:18:42 2018 Anthony LECLERC
//

#pragma once

#include "DLLoaderManager.hpp"
#include "SearchLoad.hpp"
#include "DirectoryLoader.hpp"

namespace module {

  template <typename TInterface>
  using SearchLoaderManager = detail::SearchLoader<TInterface>;

  template <typename TInterface>
  using DirectoryLoaderManager = detail::DirectoryLoader<TInterface>;

}
