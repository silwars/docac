#include "json.h"

const QString json::kFileName = "D:/encoded.json";

json::json(const QString key)
{
    this->key = key;
    this->Json = readJson(key);
}


QJsonArray json::readJson(QString key) {
  auto decodedFile = crypto::decrypt(readFile(), key, key);

  auto start = decodedFile.indexOf("\n");
  auto jsonStr = decodedFile.sliced(start, decodedFile.length() - start);

  QJsonDocument d = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonArray json = d.QJsonDocument::array();
  return json;

}


QByteArray json::readFile() {
  QFile file(json::kFileName);

  file.open(QIODevice::ReadWrite | QIODevice::Text);
  auto readedFile = file.readAll();

  file.close();
  return readedFile;
}

void json::writeFile() {
    QJsonDocument doc(this->Json);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    QFile file(json::kFileName);
    file.open(QIODevice::WriteOnly| QIODevice::Text);

    auto encodedText = crypto::encrypt((this->key + "\n" + strJson).toUtf8(), this->key, this->key);
    file.write(encodedText);
    file.close();
}


void json::writetojson( QJsonObject obj) {

  this->Json.append(obj);
  this->writeFile();
}

void json::deletefromjson(int row){
    this->Json.removeAt(row);
    writeFile();

}



QJsonObject json::encodeobj(QJsonObject obj){
    QString elogin = crypto::encrypt((obj["login"].toString().toUtf8()), this->key, this->key);
    obj["login"] = elogin;
    QString epass = crypto::encrypt((obj["pass"].toString().toUtf8()), this->key, this->key);
    obj["pass"] = epass;
    return obj;
}
