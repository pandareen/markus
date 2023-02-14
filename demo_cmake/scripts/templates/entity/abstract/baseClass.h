#pragma once
#include "../Entity.h"

namespace Domain
{
	class ${project_name}_EXPORT ${class_name} : public Entity
	{
		Q_OBJECT
		Q_CLASSINFO("abstract", "true")
		${class_info}
		Q_PROPERTY(Identifier id MEMBER id READ getId WRITE setId REQUIRED)
		Q_PROPERTY(ClassTypes classType MEMBER classType)
		${value_object_properties}

		
	public:
		enum class ClassTypes
		{
			${class_types}
		};
		Q_ENUM(ClassTypes)

		Q_INVOKABLE	${class_name}(QObject* parent = nullptr);

		Identifier getId() const;

		void setId(Identifier const& id);
		

		Identifier id;
		ClassTypes classType;
		${value_objects}
	}; 
}
Q_DECLARE_METATYPE(Domain::${class_name}*)