#pragma once
#include "../../swagger_global.h"
#include "../../IJson.h"
#include "Path.h"


namespace Swagger
{
	class SWAGGER_EXPORT Paths : public IJson
	{
	public:
		using PathList = QList<std::shared_ptr<Path>>;


		Paths(PathList const& item = {});
		Paths(QList<PathList> paths);

		const QJsonValue getJson() const;

		const Paths& append(std::shared_ptr<Path> const& item) const;
		const Paths& append(PathList const& item) const;

		PathList const& getList() const;

	private:
		static PathList create(QList<PathList> const& paths);

		mutable PathList paths;
	};
}