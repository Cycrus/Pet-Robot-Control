/**********************************************************************
 * logger.cpp
 * 
 * Implementation of the default logger.
 * 
 * Author: Cyril Marx
 * Created: September 2024
 **********************************************************************/

#include "logger.hpp"

#include <iomanip>
#include <sstream>
#include <chrono>

Logger::Logger(std::string interface_name) :
interface_name_(interface_name),
datetime_format_("%Y-%m-%d %H:%M:%S")
{ }

void Logger::debug(std::string message)
{
  loggerPrint_(message, "DEBUG", CYAN);
}

void Logger::success(std::string message)
{
  loggerPrint_(message, "SUCCESS", GREEN);
}

void Logger::info(std::string message)
{
  loggerPrint_(message, "INFO", WHITE);
}

void Logger::warning(std::string message)
{
  loggerPrint_(message, "WARNING", YELLOW);
}

void Logger::error(std::string message)
{
  loggerPrint_(message, "ERROR", RED);
}

void Logger::loggerPrint_(std::string message, std::string level, std::string color)
{
  std::string curr_time = getCurrentTimeString_();
  std::cout << interface_name_ << " | " << curr_time << " " << color << "[" << level << "] " << message << WHITE << std::endl;
}

std::string Logger::getCurrentTimeString_() {
  auto now = std::chrono::system_clock::now();
  std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
  std::ostringstream oss;
  oss << std::put_time(std::localtime(&time_t_now), datetime_format_.c_str());

  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
  oss << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();

  return oss.str();
}
