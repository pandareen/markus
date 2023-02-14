#include "OperationFactory.h"

namespace Swagger
{
	std::shared_ptr<Operation> OperationFactory::create(QString const& id, ParameterList const& parameters,
		std::shared_ptr<Responses> const& responses, QStringList const& tags /*= {}*/, QString const& summary /*= ""*/,
		QString const& description /*= ""*/, std::shared_ptr<RequestBody> const& body /*= nullptr*/) const
	{
		return 	std::make_shared<::Swagger::Operation>(
			id, parameters, responses,
			tags, summary, description, body
			);
	}
}