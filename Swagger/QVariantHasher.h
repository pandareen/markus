#pragma once
#include <QCryptographicHash>
#include <QBuffer>
#include <QDataStream>


class QVariantHasher : public QDataStream
{
public:
	QVariantHasher() : buff(&bb), QDataStream(&buff) {
		bb.reserve(1000);
		buff.open(QIODevice::WriteOnly);
	}

	const QByteArray hash() const {
		return QCryptographicHash::hash(bb, QCryptographicHash::Sha256);
	}

private:
	QByteArray bb;
	QBuffer buff;
};