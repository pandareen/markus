#pragma once
#include "../swagger_global.h"
#include "Parameter/Parameter.h"

#include "Response/Responses.h"
#include "RequestBody/RequestBody.h"
#include "Path/Callbacks.h"


namespace Swagger
{
	class SWAGGER_EXPORT Operation
	{
	public:
		Operation(
			QString const& id,
			ParameterList const& parameters,
			std::shared_ptr<Responses> const& responses,
			QStringList const& tags = {},
			QString const& summary = "",
			QString const& description = "",
			std::shared_ptr<RequestBody> const& body = nullptr,
			std::shared_ptr<Callbacks>  const& callbacks = nullptr);

		QString const& getId() const;
		const QJsonValue getJson() const;
		bool hasRequestBody() const;
		std::shared_ptr<RequestBody> const& getRequestBody() const;

		void setCallbacks(std::shared_ptr<Callbacks> const& callbacks) const;

	private:
		QJsonValue getParametersFromList() const;

		const QString id;
		const ParameterList parameters;
		const std::shared_ptr<Responses> responses;
		const QStringList tags;
		const QString summary;
		const QString description;
		const std::shared_ptr<RequestBody> body;
		mutable std::shared_ptr<Callbacks> callbacks;
	};

}