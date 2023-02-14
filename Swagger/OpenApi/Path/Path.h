#pragma once
#include "../../swagger_global.h"
#include "../../IJson.h"
#include "../Operation.h"
#include "PathRoute.h"
#include <memory>


namespace Swagger
{
	class SWAGGER_EXPORT Path : protected QObject, public IJson
	{
		Q_OBJECT
	public:
		enum class Method { GET = 1, PUT = 4, POST = 3, DELETE = 0, OPTIONS = 6, HEAD = 2, PATCH = 28, TRACE = 7 };
		Q_ENUM(Method)

		Path(std::shared_ptr<PathRoute> const& route,
			 QMap<Method, std::shared_ptr<Operation>> const& operation,
			 ParameterList const& parameters = {});

		static QString getMethodString(const Method method);
		static Method convertStringToMethodEnum(QString const& method);

		const QJsonValue getJson() const;

		bool isPath(QStringList const& path) const;

		std::shared_ptr<Operation> getOperation(const Method path) const;
		std::shared_ptr<Operation> getOperation(QString const& method) const;

		virtual bool hasOperation(const Method path) const;
		bool hasOperation(QString const& method) const;

	private:
		std::shared_ptr<PathRoute> route;
		QMap<Method, std::shared_ptr<Operation>> operation;
		ParameterList parameters;
	};
}