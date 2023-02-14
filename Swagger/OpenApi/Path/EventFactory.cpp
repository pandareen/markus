#include "EventFactory.h"

namespace Swagger
{
	EventFactory::EventFactory(std::shared_ptr<PathFactory> const& pathFactory) : pathFactory(pathFactory)
	{

	}


	std::shared_ptr<Event> EventFactory::createEvent(QString const& eventName, 
		QString const& callbackVariableName, std::shared_ptr<Schema> const& callbackResponseObject) const
	{
		const auto jsonPath = pathFactory->callbackPath(eventName, callbackVariableName, callbackResponseObject)->getPair();

		return std::make_shared<Event>(eventName, QJsonObject{	jsonPath});
	}

}