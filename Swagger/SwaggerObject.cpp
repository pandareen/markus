#include "SwaggerObject.h"

namespace Swagger
{
	SwaggerObject::SwaggerObject(QString const& name) : m_name(name)
	{

	}


	QString const& SwaggerObject::getName() const
	{
		return m_name;
	}

}