#include "OpenApi.h"

namespace Swagger
{
	class NullPath : public Path
	{
	public:
		NullPath() : Path(nullptr, { { Path::Method::GET, nullptr} })
		{

		}

		bool hasOperation(const Method path) const final
		{
			return false;
		}
	};


	OpenApi::OpenApi(Info const& info, List<Server> const& servers, std::shared_ptr<Components> components, std::shared_ptr<Paths> const& paths) : paths(paths), info(info), servers(servers), components(components)
	{

	}

	std::shared_ptr<Path> OpenApi::getPath(QStringList const& directoryFragments) const
	{
		for (auto const& path : paths->getList())
			if (path->isPath(directoryFragments)) return path;
		
		//Q_ASSERT(true, "should have path");

		return std::make_shared<NullPath>();
	}

	const QJsonValue OpenApi::getJson() const
	{
		return QJsonObject{
		 { "openapi", "3.0.2"},
		 { "info", info },
		 {"servers", createServerArray()},
		  paths->getPair(),
		  components->getPair()
		};
	}

	const std::shared_ptr<Swagger::Components>& OpenApi::getComponents() const
	{
		return components;
	}

	QJsonArray OpenApi::createServerArray() const
	{
		QJsonArray arr;

		for (const auto& server : servers)
			arr.append(server);

		return arr;
	}
}