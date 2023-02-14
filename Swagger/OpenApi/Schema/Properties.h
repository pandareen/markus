#pragma once
#include "SwaggerJson.h"
#include "Schema.h"
namespace Sw
{

// 	class Properties
// 	{
// 	public:
// 		Properties(QVector<const Schema*> const& required, QVector<const Schema*> const& optional) :
// 			m_required(requiredLst(required)),
// 			m_requiredStr(requiredLstStr(required)),
// 			m_properties(required + optional)
// 		{
// 
// 		}
// 
// 		const bool isRequired(QString const& required) const {
// 			return m_requiredStr.contains(required);
// 		}
// 
// 
// 		const QJsonObject getJson() const
// 		{
// 			QJsonObject retn;
// 			const QVector<const Schema *> & props = properties();
// 
// 			for (auto item : props)	
// 				retn[*item] = item->getJson();
// 
// 			return retn;
// 		}		
// 		
// 		const QJsonArray getRequierdLst() const {
// 			return QJsonArray::fromStringList(m_requiredStr.toList());
// 		}
// 
// 		const QVector<const Schema *> & properties() const { return m_properties; }
// 
// 	protected:
// 
// 		const QVector<QString> requiredLstStr(QVector<const Schema*> const& properties) const {
// 			QVector<QString> retn;
// 
// 			for (auto scheme : properties)
// 				retn << scheme->getName();
// 
// 			return retn;
// 		}
// 
// 		const QVector<const Schema*> requiredLst(QVector<const Schema*> const& properties) const {
// 			QVector<const Schema*> retn;
// 
// 			for (auto scheme : properties)
// 				retn << scheme;
// 
// 			return retn;
// 		}
// 
// 		const ushort size() const {
// 			return m_properties.size();
// 		}
// 
// 		const QVector <const Schema*> getList(QVector<const Schema*> const& list, const bool readOnly = true, const bool writeOnly = false) const
// 		{
// 			QVector <const Schema*> retn;
// 
// 			for (auto child : list) {
// 				if (readOnly   && child->isReadOnly() ||
// 					writeOnly && child->isWriteOnly() ) {
// 					retn.append(child);
// 				}
// 			}
// 			return retn;
// 		}
// 
// 		const Schema *const operator[](const ushort idx) const {
// 			return m_properties[idx];
// 		}
// 
// 	private:
// 		const QVector <QString > m_requiredStr;
// 		const QVector <const Schema*> m_required;
// 
// 		const QVector <const Schema*> m_properties;
// 	};

}