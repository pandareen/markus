#pragma once
#include "../../IJson.h"
#include "../../MediaType.h"
#include "../../container/Map.h"
#include "../Parameter/Parameter.h"

namespace Swagger
{

	class SWAGGER_EXPORT Response : public IJson
	{
	public:
		Response(QString const& description,
			Map<MediaType> const& content = { {} },
			Map<Parameter> const& headerMap = { {} }
		);

		Response(QString const& description, Map<Parameter> const& headerMap	);

		const QJsonValue getJson() const;

	private:
		const QString description;
		const Map<Parameter> header;
		const Map<MediaType> content;
	};

}