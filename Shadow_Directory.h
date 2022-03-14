
#ifndef _SHADOW_DIRECTORY_H_
#define _SHADOW_DIRECTORY_H_

#include<list>
#include "File.h"

using namespace std;

class Shadow_Directory
{
 private:
 public:
  std::string host_url;
  Shadow_Directory(std::string);
  virtual std::list<File> searchFileByTag(std::string);
  virtual File createFile(std::string, std::string, std::string, std::string);
  virtual File getFile(std::string);
  virtual File updateFile(std::string, std::string, std::string, std::string);
};

#endif // _SHADOW_DIRECTORY_H_
