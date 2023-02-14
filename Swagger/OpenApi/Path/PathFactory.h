#pragma once
#include "../../swagger_global.h"
#include "Path.h"
#include "../RequestBody/RequestBodyFactory.h"
#include "../Response/ResponsesFactory.h"

namespace Swagger
{
	class SWAGGER_EXPORT PathFactory
	{
	public:
		PathFactory(
			std::shared_ptr<RequestBodyFactory> const& bodyFactory,
			std::shared_ptr<ResponsesFactory> const& responsesFactory
		);

		std::shared_ptr<Path> callbackPath(
			QString const& eventName,
			QString const& callbackVariableName,
			std::shared_ptr<::Swagger::Schema> const& callbackResponseObject) const;


	private:
		std::shared_ptr<Operation> createOperation(
			QString const& callbackId, std::shared_ptr<Schema> const& schema) const;

		QString createCallbackId(QString const& uniqueString) const;


		const std::shared_ptr<::Swagger::RequestBodyFactory> bodyFactory;
		const std::shared_ptr<::Swagger::ResponsesFactory> responsesFactory;
	};
}