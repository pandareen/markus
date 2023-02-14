#include "IJson.h"

Swagger::IJson::IJson(QString const& name /*= ""*/) : m_name(name)
{

}

const Swagger::IJson::JsonPair Swagger::IJson::getPair() const
{
	return {
		getName(),
		getJson()
	};
}

QString const& Swagger::IJson::getName() const
{
	return m_name;
}

Swagger::IJson::operator QString const& () const {
	return m_name;
}


Swagger::IJson::operator const JsonPair() const {
	return getPair();
}
