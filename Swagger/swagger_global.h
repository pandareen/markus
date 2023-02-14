#pragma once

#include <QtCore/qglobal.h>

#ifndef Swagger_STATIC
# if defined(Swagger_EXPORTS)
#  define SWAGGER_EXPORT Q_DECL_EXPORT
# else
#  define SWAGGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SWAGGER_EXPORT
#endif
