#include "${class_name}.h"

namespace Domain
{
	${class_name}::${class_name}(QObject* parent /*= nullptr*/) : Entity(parent)
	{

	}

	Identifier ${class_name}::getId() const
	{
		return id;
	}

	void ${class_name}::setId(Identifier const& id)
	{
		this->id = id;
	}
}