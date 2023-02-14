#pragma once
#include "../../swagger_global.h"
#include <QStringList>

namespace Swagger
{
	class SWAGGER_EXPORT ConvertError
	{
	public:
		ConvertError() = default;

		ConvertError(const bool errorOccured, QStringList const& messages = {});
		ConvertError(const bool errorOccured, QString const& message);

		operator QString() const;
		operator bool() const;

		ConvertError& operator<<(ConvertError const& otherError);

		bool occured() const;
		bool noError() const;

		QString message() const;

		QStringList list() const;


		void eraseError(int idx);

	private:
		bool hasError = false;
		QStringList error;
	};
}

