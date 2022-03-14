
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "tagging_server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

#include <list>
#include "File.h"

using namespace std;
using namespace jsonrpc;

class MyServer : public tagging_Server 
{
public:
    MyServer(jsonrpc::AbstractServerConnector &connector, jsonrpc::serverVersion_t type);
    virtual Json::Value createFile(const std::string& collaborators, const std::string& content, const std::string& filename, const std::string& owner);
    virtual Json::Value updateFile(const std::string& collaborators, const std::string& content, const std::string& fhandle, const std::string& tag);
    virtual Json::Value getFile(const std::string& fhandle);
    virtual Json::Value searchFileByTag(const std::string& tag);
};

MyServer::MyServer(jsonrpc::AbstractServerConnector &connector, jsonrpc::serverVersion_t type) 
    : tagging_Server(connector, type)
{
    std::cout << "MyServer Object created" << std::endl;
}

std::list<File> files;

Json::Value MyServer::searchFileByTag(const std::string& tag)
{
    std::cout << "Receive remote searchFileByTag call with " << tag << std::endl;
    Json::Value tagged;
    int i = 0;
    for(File& fi : files){
        for(const std::string& t : fi.tags){
            if(t == tag){
                Json::Value ff = fi.dumpToJson();
                tagged[i++] = ff;
                break;
            }
        }
    }
    Json::Value res;
    res["tagged"] = tagged;
    res["status"] = "success";
    return res;
}

std::list<string> splitString(string s, char delimeter){
    std::list<string> res;
	string temp = "";
	for(int i=0;i<s.length();++i){
		if(s[i]==delimeter){
			res.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}		
	}
	res.push_back(temp);
	return res;
}

void tagFileWithML(File& f)
{
    std::cout << "Running DeepLearning Model to classify files" << std::endl;
    std::cout << "File " << f.fhandle << " is classified as ucdavis" << std::endl;
    f.tags.push_back("ucdavis");
}

Json::Value MyServer::createFile
(const std::string& collaborators, const std::string& content, 
 const std::string& filename, const std::string& owner)
{
    std::cout << "Receive remote createFile call" << std::endl;
    File f {};
    f.collaborators = splitString(collaborators, ',');
    f.content = content;
    f.filename = filename;
    f.ownerId = owner;
    Json::Value res = f.dumpToJson();
    tagFileWithML(f);
    files.push_back(f);
    res["status"] = "success";
    return res;
}

Json::Value MyServer::updateFile
(const std::string& collaborators, const std::string& content, 
 const std::string& fhandle, const std::string& tag)
{
    std::cout << "Receive remote updateFile call" << std::endl;
    Json::Value res;
    for(File& fi : files){
        if(fi.fhandle == fhandle){
            fi.collaborators = splitString(collaborators, ',');
            fi.content = content;
            fi.tags.push_back(tag);
            res = fi.dumpToJson();
            break;
        }
    }
    res["status"] = "success";
    return res;
}

Json::Value MyServer::getFile(const std::string& fhandle)
{
    std::cout << "Receive remote getFile call with " << fhandle << std::endl;
    Json::Value res;
    for(File& fi : files){
        if(fi.fhandle == fhandle){
            res = fi.dumpToJson();
            break;
        }
    }
    res["status"] = "success";
    return res;
}

int main() 
{
    std::list<std::string> f1tags;
    f1tags.push_back("ucdavis");
    std::list<std::string> f1cols;
    f1cols.push_back("user1");
    File file1 {"ecs251_hw1", "This is hw1", "user1", f1tags, f1cols};
    files.push_back(file1);

    HttpServer httpserver(8384);
    MyServer s(httpserver, JSONRPC_SERVER_V1V2);
    s.StartListening();
    std::cout << "Hit enter to stop the server" << endl;
    getchar();

    s.StopListening();
    return 0;
}