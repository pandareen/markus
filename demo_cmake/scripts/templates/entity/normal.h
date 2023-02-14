#pragma once
#include "../Entity.h"

namespace Domain
{
	class ${project_name}_EXPORT ${class_name} : public Entity
	{
		Q_OBJECT
		${class_info}
		Q_PROPERTY(Identifier id MEMBER id READ getId WRITE setId REQUIRED)
		${value_object_properties}
		Q_PROPERTY(QDateTime created MEMBER created)

	public:
		Q_INVOKABLE ${class_name}(QObject* parent = nullptr);

		Identifier getId() const;
		void setId(Identifier const& id);

		Identifier id;
		${value_objects}
		QDateTime created;
	};
}
Q_DECLARE_METATYPE(Domain::${class_name}*)