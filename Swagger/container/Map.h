#pragma once
#include "../swagger_global.h"

#include <QMap>
#include <QString>
#include <QJsonValue>
#include <QJsonObject>

namespace Swagger
{
	template<  typename T2>
	class SWAGGER_EXPORT Map : public QMap<QString, std::shared_ptr<T2>>
	{
	public:
		using QMap<QString, std::shared_ptr<T2>>::QMap;

		virtual const QJsonValue getJson() const
		{
			QJsonObject retn;

			for (auto e : (*this).keys())
				if ((*this).value(e))
					retn[e] = (*this).value(e)->getJson();


			return retn;
		}

	};
}