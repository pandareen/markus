#include "Responses.h"
namespace Swagger
{
	Responses::Responses(Map<Response> const& responses, std::shared_ptr<Response> const& defaultResponse /*= nullptr*/) :
		IJson("responses"),
		responses(responses),
		defaultResponse(defaultResponse)
	{

	}



	const QJsonValue Responses::getJson() const
	{
		auto retn = responses.getJson().toObject();

		if (defaultResponse)
			retn.insert("default", defaultResponse->getJson());

		return retn;
	}

}