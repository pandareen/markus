#pragma once
#include "../container/Reference.h"
#include "../OperationFactory.h"
#include "Schema/Factory/SchemaFactory.h"
#include "Parameter/ParameterFactory.h"
#include "Path/PathFactory.h"

namespace Swagger
{

	class SWAGGER_EXPORT Components : public IJson
	{
	public:
		Components();

		const QJsonValue getJson() const {
			return QJsonObject{
				{"schemas", schemaFactory->getJson() },
				//{"responses", factory->getJson() },
				//{"parameters", factory->getJson() },
				//{"requestBodies", factory->getJson() },
			};
		}

		virtual std::shared_ptr<SchemaFactory> const& schema() const;
		virtual std::shared_ptr<OperationFactory> const& operation() const;
		virtual std::shared_ptr<ResponseFactory> const&  response() const;
		virtual std::shared_ptr<ResponsesFactory> const&  responses() const;
		virtual std::shared_ptr<ParameterFactory> const& parameter() const;
		virtual std::shared_ptr<RequestBodyFactory> const& requestBody() const;
		virtual std::shared_ptr<PathFactory> const& path() const;

	protected:
		const std::shared_ptr<SchemaFactory> schemaFactory = std::make_shared<SchemaFactory>();
		const std::shared_ptr<ResponseFactory> responseFactory = std::make_shared<ResponseFactory>(schemaFactory);
		const std::shared_ptr<ResponsesFactory> responsesFactory = std::make_shared<ResponsesFactory>(responseFactory);
		const std::shared_ptr<OperationFactory> operationFactory = std::make_shared<OperationFactory>(schemaFactory, responsesFactory);
		const std::shared_ptr<RequestBodyFactory> requestBodyFactory = std::make_shared<RequestBodyFactory>(schemaFactory);
		const std::shared_ptr<ParameterFactory> parameterFactory = std::make_shared<ParameterFactory>(schemaFactory);
		const std::shared_ptr<PathFactory> pathFactory = std::make_shared<PathFactory>(requestBodyFactory, responsesFactory);

	private:
	};

}