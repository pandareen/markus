#pragma once
#include "Response.h"

namespace Swagger
{
	class SWAGGER_EXPORT Responses : public IJson
	{
	public:
		Responses(
			Map<Response> const& responses,
			std::shared_ptr<Response> const& defaultResponse = nullptr);

		const QJsonValue getJson() const;

	private:
		const Map<Response> responses;
		const std::shared_ptr<Response> defaultResponse;
	};
}