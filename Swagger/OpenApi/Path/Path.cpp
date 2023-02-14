#include "Path.h"

#include <QMetaEnum>

namespace Swagger
{

	Path::Path(
		std::shared_ptr<PathRoute> const& route,
		QMap<Method, std::shared_ptr<Operation>> const& operation,
		ParameterList const& parameters) :
		IJson(route ? QString(*route) : ""),
		operation(operation),
		parameters(parameters),
		route(route)
	{

	}

	QString Path::getMethodString(const Path::Method method)
	{
		return QMetaEnum::fromType<Swagger::Path::Method>().valueToKey(static_cast<int>(method));
	}

	Swagger::Path::Method Path::convertStringToMethodEnum(QString const& method)
	{
		bool couldConvert = false;
		const auto metaObject = ::Swagger::Path::staticMetaObject;
		const auto enumIndex = metaObject.indexOfEnumerator("Method");
		const auto enumValue = metaObject.enumerator(enumIndex);
		const auto value = enumValue.keyToValue(qPrintable(method), &couldConvert);

		Q_ASSERT_X(couldConvert, "Path", "Couldn't convert method string to an value");

		return static_cast<Method>(value);
	}

    const QJsonValue Path::getJson() const
    {
		QJsonObject retn;

		for (auto const& methodCode : operation.keys())
			if (operation.contains(methodCode))
				retn[getMethodString(methodCode).toLower()] = operation.value(methodCode)->getJson();
		
        return retn;
    }

	bool Path::isPath(QStringList const& path) const
	{
		return route->compare(path);
	}

	std::shared_ptr<Operation> Path::getOperation(const Method path) const
	{
		return operation[path];
	}

	std::shared_ptr<Operation> Path::getOperation(QString const& method) const
	{
		return operation[convertStringToMethodEnum(method)];
	}

	bool Path::hasOperation(const Method path) const
	{
		return operation.contains(path);
	}

	bool Path::hasOperation(QString const& method) const
	{
		return hasOperation(convertStringToMethodEnum(method));
	}
}