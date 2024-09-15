/**********************************************************************
 * logger.hpp
 * 
 * The default logger of the interfaces.
 * 
 * Author: Cyril Marx
 * Created: September 2024
 **********************************************************************/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#define WHITE "\033[00m"
#define RED "\033[91m"
#define YELLOW "\033[93m"
#define GREEN "\033[92m"
#define CYAN "\033[96m"

class Logger
{
  public:
  /* Constructor. Sets the interface name and the time format.
   * @param interface_name The name of the interface to show in each logging call.
   */
  Logger(std::string interface_name);

  /* Logging interface methods.
   * @param message The message to log.
   */
  void debug(std::string message);
  void success(std::string message);
  void info(std::string message);
  void warning(std::string message);
  void error(std::string message);

  private:
  std::string interface_name_;
  std::string datetime_format_;

  /* The internal printing method each logging method uses.
   * @param message The message to log.
   * @param level A string describint the logging level.
   * @param color The ANSI color code to use for the log message.
   */
  void loggerPrint_(std::string message, std::string level, std::string color);

  /* Returns the current time with a millisecond precision as a string.
   * @return The current time as a string.
   */
  std::string getCurrentTimeString_();
};

#endif // LOGGER_HPP