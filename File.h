
#ifndef _FILE_H_
#define _FILE_H_


// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <list>
#include <iostream>

class File
{
 private:
 public:
  static unsigned int fcount;
  std::string filename;
  std::string fhandle;
  std::string content;
  std::string ownerId;
  std::list<std::string> tags;
  std::list<std::string> collaborators;
  File();
  File(std::string, std::string, std::string, std::list<std::string>, std::list<std::string>);
  const Json::Value dumpToJson();
  static File jsonToFile(Json::Value);
};

#endif  /* _FILE_H_ */
