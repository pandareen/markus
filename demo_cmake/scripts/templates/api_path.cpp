#include "${class_name}.h"

namespace Service
{
	${class_name}::${class_name}(std::shared_ptr<RepositoryFactory> const& repositoryFactory) :
		BaseResourcePath(::Domain::${class_name}::staticMetaObject, repositoryFactory)
	{
		connectBaseResourceSignals(
			[this](::Domain::Entity* entity) {
				emit inserted(static_cast<::Domain::${class_name}*>(entity));
			},
			[this](::Domain::Entity* entity) {
				emit updated(static_cast<::Domain::${class_name}*>(entity));
			},
			[this](::Domain::Entity* entity ) {
				emit erased(static_cast<::Domain::${class_name}*>(entity));
			}
		);
	}

	QList<::Domain::${class_name}*> ${class_name}::getPage(QString const& filername, QStringList const& values, QString const& sortBy, QString const& orderBy, int pageIndex) const
	{
		return  BaseResourcePath::getPage<::Domain::${class_name}>(filername, values, sortBy, orderBy, pageIndex);
	}

	Domain::${class_name}* ${class_name}::get(::Domain::Identifier const& id) const
	{
		return static_cast<::Domain::${class_name}*>(getById(id));
	}


	bool ${class_name}::update(::Domain::${class_name}* entity) const
	{
		return BaseResourcePath::update(entity);
	}


	bool ${class_name}::insert(::Domain::${class_name}* entity) const
	{
		return BaseResourcePath::insert(entity);
	}


	bool ${class_name}::erase(::Domain::Identifier const& id) const
	{
		return BaseResourcePath::erase(id);
	}
}
