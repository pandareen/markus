#include "PathRoute.h"

namespace Swagger
{

	PathRoute::PathRoute(FragmentList const& list) : parameterList(list)
	{

	}

	PathRoute::operator QString() const {
		QString retn;

		for (auto const& item : parameterList)
			retn.append("/" + item->getString());

		return retn;
	}

	ConvertError PathRoute::compare(QStringList const& path) const
	{
		bool retn = (path.size() == parameterList.size());

		for (int i = 0; i < parameterList.size() && retn; i++)
			retn &= parameterList[i]->isFragmentCorrect(path[i]);
	
		return retn;
	}

	//QString PathRoute::getParameter(const QStringList& path, const std::shared_ptr<PathParameter>& param) const
	//{
	//	QString retn;
	//
	//	for (int i = 0; i < parameterList.size() && retn.isEmpty(); i++) {
	//		if (param == parameterList[i].first)
	//			retn = path[i];
	//	}
	//
	//	return retn;
	//}
}