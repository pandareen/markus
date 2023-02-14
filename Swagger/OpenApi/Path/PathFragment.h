#pragma once
#include "../Schema/ConvertError.h"
#include "../Parameter/PathParameter.h"
#include <QVariant>

namespace Swagger
{
	class SWAGGER_EXPORT PathFragment
	{

	public:
		PathFragment(QString const& fragment);
		PathFragment(std::shared_ptr<PathParameter> const& parameter);

		bool isFragmentCorrect(QString const& fragment) const;

		QString const& getString() const;

	private:
		PathFragment(QString const& fragmentString, std::shared_ptr<PathParameter> const& fragmentParamter);

		bool isStaticFragment() const;
		bool isParameterCorrectFormatted(QString const& fragment) const;

		const QString fragmentString;
		const std::shared_ptr<PathParameter> fragmentParamter;
	};

	using FragmentList = QList<std::shared_ptr<PathFragment>>;
}

