#include "PathFactory.h"
#include <QCryptographicHash>

namespace Swagger
{
	PathFactory::PathFactory(
		std::shared_ptr<RequestBodyFactory> const& bodyFactory, 
		std::shared_ptr<ResponsesFactory> const& responsesFactory) : 
		bodyFactory(bodyFactory),
		responsesFactory(responsesFactory)
	{

	}


	std::shared_ptr<Swagger::Path> PathFactory::callbackPath(
		QString const& eventName,
		QString const& callbackVariableName,
		std::shared_ptr<::Swagger::Schema> const& callbackResponseObject) const
	{
		const auto route = std::make_shared<PathRoute>(
			FragmentList{
				std::make_shared<PathFragment>("{$request.body#"),
				std::make_shared<PathFragment>(QString("%1}").arg(callbackVariableName))
			}
		);

		const auto callbackId = createCallbackId(eventName);
		const auto operation = createOperation(eventName, callbackResponseObject);

		return std::make_shared<Path>(route, QMap<Path::Method, std::shared_ptr<Operation>> { {Path::Method::POST, operation} });
	}

	std::shared_ptr<Swagger::Operation> PathFactory::createOperation(QString const& callbackId, std::shared_ptr<::Swagger::Schema> const& schema) const
	{
		return std::make_shared<Operation>(
			callbackId, ParameterList{},
			responsesFactory->callbackResponses(),
			QStringList{}, "", "", bodyFactory->createJsonRequestBody(schema));
	}

	QString PathFactory::createCallbackId(QString const& uniqueString) const
	{
		return QString(QCryptographicHash::hash(uniqueString.toUtf8(), QCryptographicHash::Keccak_256).toHex()).left(30);
	}

}