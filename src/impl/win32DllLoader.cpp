//
// win32DllLoader.hpp for cpp_rtype in /home/anthony/repository/cpp_rtype/win32DllLoader.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  mer. janv. 17 15:51:50 2018 Anthony LECLERC
// Last update mer. janv. 17 15:51:50 2018 Anthony LECLERC
//

/// Windows specific header for Dll loader.

#include <windows.h>
#include <string>
#include <iostream>
#include "impl/types.hpp"
#include "impl/ImplDllLoader.hpp"

namespace module {

  /// Set theses values with Win API correct values.
  namespace detail {

	const Handle InvalidHandle{ nullptr };
	const Sym    InvalidSym{ nullptr };


    Handle ImplDllLoader::loadLibrary(std::string const& name)
    {
      /// DLOpen equivalent for windows
      auto handler = LoadLibrary(name.c_str());
      if (handler == detail::InvalidHandle) {
        std::cout << "Error during the loading of : " << name << std::endl;
      }
      return (handler);
    }

    Sym ImplDllLoader::loadSymbol(Handle h, std::string const& name)
    {
      /// DLSym equivalent for windows
      if (h == detail::InvalidHandle) {
        return (detail::InvalidSym);
      }
      auto func = GetProcAddress(static_cast<HMODULE>(h), name.c_str());
      if (func == detail::InvalidSym) {
        std::cout << "Error during the loading of the function : " << name
            << std::endl;
      }
      return (func);
    }

    void ImplDllLoader::closeLibrary(detail::Handle h)
    {
      /// DlClose equivalent for windows
      if (h != detail::InvalidHandle) {
        FreeLibrary(static_cast<HMODULE>(h));
      }
    }
  }
}
