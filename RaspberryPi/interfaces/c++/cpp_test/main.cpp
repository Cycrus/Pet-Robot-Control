
#include <iostream>
#include <unistd.h>
#include "MQTTClient.h"
#include "logger.hpp"
#include <json.hpp>

using json = nlohmann::json;

int main(void) 
{
  std::string dstring = "dynamic hewwo";
  json j;
  j["test_int"] = 5;
  j["test_cstring"] = "hewwo";
  j["test_dstring"] = dstring;

  Logger logger("TestInterface");
  int i = 0;
  while(true)
  {
    logger.info("Hello World.");
    logger.debug(std::to_string(j["test_int"].get<int>()));
    logger.warning(j["test_cstring"].get<std::string>());
    logger.error(j["test_dstring"].get<std::string>());
    logger.success("Oh, this is a value " + std::to_string(i));
    sleep(1);
    i++;
  }
  return 0;
}
