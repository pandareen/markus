#include "PathFragment.h"
namespace Swagger
{
	PathFragment::PathFragment(QString const& fragment) :
		PathFragment(fragment.toLower(), nullptr)
	{

	}


	PathFragment::PathFragment(std::shared_ptr<PathParameter> const& parameter) :
		PathFragment("{" + QString(*parameter).toLower() + "}", parameter)
	{

	}

	PathFragment::PathFragment(QString const& fragmentString, std::shared_ptr<PathParameter> const& fragmentParamter) :
		fragmentString(fragmentString),
		fragmentParamter(fragmentParamter)
	{

	}

	bool PathFragment::isStaticFragment() const
	{
		return fragmentParamter == nullptr;
	}

	bool PathFragment::isParameterCorrectFormatted(QString const& fragment) const
	{
		QVariant value(fragment);
		return fragmentParamter->scheme()->convert(value).noError();
	}

	bool PathFragment::isFragmentCorrect(QString const& fragment) const
	{
		if (isStaticFragment())
			return fragmentString == fragment.toLower();

		return isParameterCorrectFormatted(fragment);
	}

	QString const& PathFragment::getString() const
	{
		return fragmentString;
	}

}