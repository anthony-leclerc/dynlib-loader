#pragma once

#ifdef WIN32

#pragma warning(disable: 4251)
#ifdef dlloader_EXPORTS
#	define DLLOADER_API __declspec(dllexport)

#else
#	define DLLOADER_API __declspec(dllimport)
#endif
#else
#	define DLLOADER_API
#endif