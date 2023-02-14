#pragma once
#include "../../swagger_global.h"
#include "PathFactory.h"


namespace Swagger
{
	class SWAGGER_EXPORT EventFactory
	{
	public:
		EventFactory(
			std::shared_ptr<PathFactory> const& pathFactory
		);	
		
		std::shared_ptr<Event> createEvent(
			QString const& eventName,
			QString const& callbackVariableName,
			std::shared_ptr<Schema> const& callbackResponseObject
		) const;


	private:
		const std::shared_ptr<PathFactory> pathFactory;
	};
}