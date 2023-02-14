#pragma once
#include "../swagger_global.h"
#include "Information/Info.h"
#include "Information/Server.h"
#include "Components.h"
#include "Path/Paths.h"


namespace Swagger
{
	class SWAGGER_EXPORT OpenApi
	{
	public:
		OpenApi(
			Info const& info,
			List<Server> const& servers,
			std::shared_ptr<Components> components,
			std::shared_ptr<Paths> const& paths);

		virtual std::shared_ptr<Path> getPath(QStringList const& directoryFragments) const;

		const QJsonValue getJson() const;

		const std::shared_ptr<Components>& getComponents() const;

	private:
		QJsonArray createServerArray() const;

		const Info info;
		const  List<Server> servers;
		const std::shared_ptr<Components> components;
		const std::shared_ptr<Paths> paths;

	};
}