#include "Response.h"

Swagger::Response::Response(QString const& description, Map<MediaType> const& content /*= { {} }*/, Map<Parameter> const& headerMap /*= { {} } */) :
	header(headerMap),
	content(content),
	description(description)
{

}

const QJsonValue Swagger::Response::getJson() const
{
	auto retn = QJsonObject{
		{"headers", header.getJson() },
		{"description", description}
	};

	if (!content.isEmpty())
		retn["content"] = content.getJson();

	return retn;
}

Swagger::Response::Response(QString const& description, Map<Parameter> const& headerMap) :
	Response(description, { {} }, headerMap)
{

}
