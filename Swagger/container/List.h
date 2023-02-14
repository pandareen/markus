#pragma once
#include <QList>
#include <QJsonValue>
#include <QJsonArray>

namespace Swagger
{
	template< typename T>
	class List : public QList<T>
	{
	public:
		using QList<T>::QList;

		const QJsonValue getJson() const
		{
			QJsonArray retn;

			for (auto item : *this)
				retn.append(item->getJson());

			return retn;
		}
	};
}
