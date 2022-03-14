#include "Shadow_Directory.h"

// JSON RPC part
#include <stdlib.h>
#include "tagging_client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include "File.h"
using namespace jsonrpc;
using namespace std;

Shadow_Directory::Shadow_Directory(std::string host_url) {
    this->host_url = host_url;
}

std::list<File> Shadow_Directory::searchFileByTag(std::string tag) {
    HttpClient httpclient((this->host_url).c_str());
    tagging_Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    try {
        myv = myClient.searchFileByTag(tag.c_str());
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    std::cout << "Calling Shadow_Directory.searchFileByTag with status " << myv["status"].asCString() << std::endl;
    std::list<File> res;

    if (myv["status"].asString() == "success") {
        for (Json::Value& jv : myv["tagged"]) {
            res.push_back(File::jsonToFile(jv));
        }
    }
    return res;
}

File Shadow_Directory::createFile(std::string filename, std::string content, std::string collaborators, std::string ownerId)
{
    HttpClient httpclient((this->host_url).c_str());
    tagging_Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    try {
        myv = myClient.createFile(collaborators, content, filename, ownerId);
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    std::cout << "Calling Shadow_Directory.createFile with status " << myv["status"].asCString() << std::endl;
    
    File res;
    if (myv["status"].asString() == "success") {
        res = File::jsonToFile(myv);
    }
    return res;
}

File Shadow_Directory::getFile(std::string fhandle)
{
    HttpClient httpclient((this->host_url).c_str());
    tagging_Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    try {
        myv = myClient.getFile(fhandle);
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    std::cout << "Calling Shadow_Directory.getFile with status " << myv["status"].asCString() << std::endl;
    
    File res;
    if (myv["status"].asString() == "success") {
        res = File::jsonToFile(myv);
    }
    return res;
}

File Shadow_Directory::updateFile(std::string fhandle, std::string content, std::string collaborators, std::string tag)
{
    HttpClient httpclient((this->host_url).c_str());
    tagging_Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;
    try {
        myv = myClient.updateFile(collaborators, content, fhandle, tag);
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    std::cout << "Calling Shadow_Directory.updateFile with status " << myv["status"].asCString() << std::endl;
    
    File res;
    if (myv["status"].asString() == "success") {
        res = File::jsonToFile(myv);
    }
    return res;
}

std::string join(const std::list<std::string>& v) {

   std::string res;
   for (const std::string& s : v) {
       res.append(s);
   }
   return res;
}