#include "Paths.h"
#include <QJsonObject>

namespace Swagger
{
	Paths::Paths(PathList const& item) : IJson("paths"), paths(item)
	{

	}

	Paths::Paths(QList<PathList> paths) : Paths(create(paths))
	{

	}

	Paths::PathList Paths::create(QList<PathList> const& paths)
	{
		PathList retn;

		for (const auto& items : paths) {
			for (const auto& path : items) {
				retn.append(path);
			}
		}

		return retn;
	}

	const QJsonValue Paths::getJson() const
	{
		QJsonObject retn;

		for (auto const& e : paths) {
			retn.insert(e->getName(), e->getJson());
		}

		return retn;
	}

	const Swagger::Paths& Paths::append(std::shared_ptr<Path> const& item) const
	{
		paths << item;
		return *this;
	}

	const Swagger::Paths& Paths::append(PathList const& item) const
	{
		paths << item;
		return *this;
	}

	Paths::PathList const& Paths::getList() const
	{
		return paths;
	}
}