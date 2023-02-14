#include "ConvertError.h"

namespace Swagger
{
	ConvertError::ConvertError(const bool errorOccured, QStringList const& messages)
		: hasError(errorOccured), error((errorOccured ? messages : QStringList{} ))
	{

	}

	ConvertError::ConvertError(const bool errorOccured, QString const& message) :
		ConvertError(errorOccured, QStringList{ message })
	{

	}

	ConvertError::operator QString() const {
		return message();
	}

	ConvertError::operator bool() const {
		return occured();
	}

	ConvertError& ConvertError::operator<<(ConvertError const& otherError) {

		if (otherError.occured()) {
			hasError = true;
			error << otherError.message();
		}

		return *this;
	}

	bool ConvertError::occured() const {
		return hasError;
	}

	bool ConvertError::noError() const
	{
		return !hasError;
	}

	QString ConvertError::message() const {
		return error.join("\n\t");
	}

	QStringList ConvertError::list() const {
		return error;
	}

	void ConvertError::eraseError(int idx)
	{
		error.remove(idx);

		if (error.size() == 0)
			hasError = false;
	}

}