#include "Operation.h"

namespace Swagger
{
	Operation::Operation(
		QString const& id,
		ParameterList const& parameters,
		std::shared_ptr<Responses> const& responses, 
		QStringList const& tags /*= {}*/,
		QString const& summary /*= ""*/, 
		QString const& description /*= ""*/, 
		std::shared_ptr<RequestBody> const& body /*= nullptr*/,
		std::shared_ptr<Callbacks>  const& callbacks) :
		id(id),
		parameters(parameters),
		responses(responses),
		tags(tags),
		summary(summary),
		description(description),
		body(body),
		callbacks(callbacks)
	{

	}

	const QJsonValue Operation::getJson() const
	{
		QJsonObject retn = QJsonObject{
			responses->getPair(),
			{"tags", QJsonArray::fromStringList(tags) },
			{"parameters", getParametersFromList()},
			{"operationId", id}
		};

		if (callbacks)				retn["callbacks"]	= callbacks->getJson();
		if (body)					retn["requestBody"] = body->getJson();
		if (!summary.isEmpty())		retn["summary"]		= summary;
		if (!description.isEmpty())	retn["description"] = description;

		return retn;
	}

	QString const& Operation::getId() const
	{
		return id;
	}

	bool Operation::hasRequestBody() const
	{
		return body != nullptr;
	}

	std::shared_ptr<Swagger::RequestBody> const& Operation::getRequestBody() const
	{
		return body;
	}

	void Operation::setCallbacks(std::shared_ptr<Callbacks>  const& callbacks) const
	{
		this->callbacks = callbacks;
	}

	QJsonValue Operation::getParametersFromList() const
	{
		QJsonArray retn;

		for (auto const& item : parameters)
			retn.append(item->getJson());

		return retn;
	}

}

