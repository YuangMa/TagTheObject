#include "File.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include<list>

using namespace std;
unsigned int File::fcount { };

File::File()
{
    this->collaborators = std::list<std::string>{};
    this->tags = std::list<std::string>{};
    this->fhandle = "fhandle-" + std::to_string(fcount++);
}

File::File(std::string filename, std::string content, std::string ownerId, std::list<std::string> tags, std::list<std::string> collaborators)
{
    this->filename = filename;
    this->content = content;
    this->ownerId = ownerId;
    this->collaborators = collaborators;
    this->tags = tags;
    this->fhandle = "fhandle-" + std::to_string(fcount++);
}

const Json::Value File::dumpToJson()
{
    Json::Value res;
    res["filename"] = this->filename;
    res["content"] = this->content;
    res["ownerId"] = this->ownerId;
    res["fhandle"] = this->fhandle;
    Json::Value tag = Json::arrayValue;
    int i = 0;
    for (const std::string& t: this->tags) {
        tag[i++] = t;
    }
    res["tags"] = tag;
    Json::Value cols = Json::arrayValue;
    i = 0;
    for (const std::string& t: this->collaborators) {
        cols[i++] = t;
    }
    res["collaborators"] = cols;
    return res;
}

File File::jsonToFile(Json::Value j)
{
    File f {};
    if (!j["content"].isNull()) {
        f.content = j["content"].asCString();
    }
    if (!j["filename"].isNull()) {
        f.filename = j["filename"].asCString();
    }
    if (!j["ownerId"].isNull()) {
        f.ownerId = j["ownerId"].asCString();
    }
    if (!j["fhandle"].isNull()) {
        f.fhandle = j["fhandle"].asCString();
    }
    if (!j["collaborators"].isNull()) {
        f.collaborators = std::list<std::string>{};
        for (Json::Value::ArrayIndex i = 0; i != j["collaborators"].size(); i++) {
            f.collaborators.push_back(j["collaborators"][i].asString());
        }
    }
    if (!j["tags"].isNull()) {
        f.tags = std::list<std::string>{};
        for (Json::Value::ArrayIndex i = 0; i != j["tags"].size(); i++) {
            f.tags.push_back(j["tags"][i].asString());
        }
    }
    return f;
}