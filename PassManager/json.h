#ifndef JSON_H
#define JSON_H
#include "QDebug"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QString"
#include "crypto.h"


class json
{
public:
    explicit json(const QString key);
    QString key;
    QByteArray file;
    QJsonArray Json;
    QJsonArray readJson(QString key);
    QJsonObject encodeobj(QJsonObject obj);
    static QByteArray readFile();
    void writeFile();

    void writetojson(QJsonObject obj);
    void deletefromjson(int row);

    static const QString kFileName;

};

#endif // JSON_H
