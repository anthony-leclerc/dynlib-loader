 //
// ImplDllLoader.hpp for cpp_rtype in /home/anthony/repository/cpp_rtype/ImplDllLoader.hpp
//
// Made by Anthony LECLERC
// Login   <anthony.leclerc@epitech.eu>
//
// Started on  mer. janv. 17 16:44:24 2018 Anthony LECLERC
// Last update mer. janv. 17 16:44:24 2018 Anthony LECLERC
//

#ifndef CPP_RTYPE_IMPLDLLLOADER_HPP
#define CPP_RTYPE_IMPLDLLLOADER_HPP

#include <memory>
#include "types.hpp"
//#include "Export.hpp"

#ifdef WIN32

# ifdef dlloader_EXPORTS
#  define EXPORT __declspec(dllexport)
# else
#  define EXPORT __declspec(dllimport)
# endif
#else
# define EXPORT
#endif

 namespace module {

   namespace detail {

	 EXPORT extern const Handle InvalidHandle;
	 EXPORT extern const Handle InvalidSym;

	 class EXPORT ImplDllLoader {
	 public:

	   Handle loadLibrary(std::string const& name);

	   detail::Sym loadSymbol(Handle, std::string const& name);

	   void closeLibrary(detail::Handle );
	 };
   }
 }

#endif /* CPP_RTYPE_IMPLDLLLOADER_HPP */
