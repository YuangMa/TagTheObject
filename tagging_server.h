/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_TAGGING_SERVER_H_
#define JSONRPC_CPP_STUB_TAGGING_SERVER_H_

#include <jsonrpccpp/server.h>

class tagging_Server : public jsonrpc::AbstractServer<tagging_Server>
{
    public:
        tagging_Server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<tagging_Server>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("createFile", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "collaborators",jsonrpc::JSON_STRING,"content",jsonrpc::JSON_STRING,"filename",jsonrpc::JSON_STRING,"owner",jsonrpc::JSON_STRING, NULL), &tagging_Server::createFileI);
            this->bindAndAddMethod(jsonrpc::Procedure("updateFile", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "collaborators",jsonrpc::JSON_STRING,"content",jsonrpc::JSON_STRING,"fhandle",jsonrpc::JSON_STRING,"tag",jsonrpc::JSON_STRING, NULL), &tagging_Server::updateFileI);
            this->bindAndAddMethod(jsonrpc::Procedure("getFile", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "fhandle",jsonrpc::JSON_STRING, NULL), &tagging_Server::getFileI);
            this->bindAndAddMethod(jsonrpc::Procedure("searchFileByTag", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "tag",jsonrpc::JSON_STRING, NULL), &tagging_Server::searchFileByTagI);
        }

        inline virtual void createFileI(const Json::Value &request, Json::Value &response)
        {
            response = this->createFile(request["collaborators"].asString(), request["content"].asString(), request["filename"].asString(), request["owner"].asString());
        }
        inline virtual void updateFileI(const Json::Value &request, Json::Value &response)
        {
            response = this->updateFile(request["collaborators"].asString(), request["content"].asString(), request["fhandle"].asString(), request["tag"].asString());
        }
        inline virtual void getFileI(const Json::Value &request, Json::Value &response)
        {
            response = this->getFile(request["fhandle"].asString());
        }
        inline virtual void searchFileByTagI(const Json::Value &request, Json::Value &response)
        {
            response = this->searchFileByTag(request["tag"].asString());
        }
        virtual Json::Value createFile(const std::string& collaborators, const std::string& content, const std::string& filename, const std::string& owner) = 0;
        virtual Json::Value updateFile(const std::string& collaborators, const std::string& content, const std::string& fhandle, const std::string& tag) = 0;
        virtual Json::Value getFile(const std::string& fhandle) = 0;
        virtual Json::Value searchFileByTag(const std::string& tag) = 0;
};

#endif //JSONRPC_CPP_STUB_TAGGING_SERVER_H_
