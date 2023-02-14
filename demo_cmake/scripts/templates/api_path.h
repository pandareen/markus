#pragma once
#include "ServiceCore/ApiPath/Base/BaseResourcePath.h"
#include "DomainCore/Types/Entity/${include_path}"

namespace Service
{
	class ${project_name}_EXPORT ${class_name} : public BaseResourcePath
	{
		Q_OBJECT

	public:
		Q_INVOKABLE ${class_name}(std::shared_ptr<RepositoryFactory> const& repository);

	public slots:
		QList<::Domain::${class_name}*> getPage(
			QString const& filername, 
			QStringList const& values,
			QString const& sortBy,
			QString const& orderBy, 
			int pageIndex) const;

		::Domain::${class_name}* get(::Domain::Identifier const& id) const;
 
		bool update(::Domain::${class_name}* entity) const;
		bool insert(::Domain::${class_name}* entity) const;
		bool erase(::Domain::Identifier const& id) const;

	signals:
		void updated(::Domain::${class_name}* entity) const;
		void inserted(::Domain::${class_name}* entity) const;
		void erased(::Domain::${class_name}* entity) const;
	};
}