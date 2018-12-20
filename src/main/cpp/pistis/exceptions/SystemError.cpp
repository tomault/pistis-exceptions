#include "SystemError.hpp"
#include <sstream>
#include <string.h>


using namespace pistis::exceptions;

SystemError::SystemError(const std::string& details,
			 const ExceptionOrigin& origin):
    PistisException(details, origin) {
  // Intentionally left blank
}

SystemError::SystemError(const std::string& details,
			 const PistisException& cause,
			 const ExceptionOrigin& origin):
    PistisException(details, cause, origin) {
  // Intentionally left blank  
}

SystemError* SystemError::duplicate() const {
  return new SystemError(*this);
}

std::string SystemError::detailsFromSystemCode(const std::string& msg,
					       int errorCode) {
  std::ostringstream result;
  size_t i= msg.find("#ERR#");

  if (i == std::string::npos) {
    result << msg << " (" << strerror(errorCode) << ")";
  } else {
    size_t last= 0;
    while (i != std::string::npos) {
      result << msg.substr(last, i) << strerror(errorCode);
      last= i+5;
      i= msg.find("#ERR#", last);
    }
    if (last < msg.size()) {
      result << msg.substr(last, msg.size());
    }
  }
  return result.str();
}

std::string SystemError::detailsFromSystemCode(const std::string& msg) {
  return detailsFromSystemCode(msg, errno);
}

SystemError SystemError::fromSystemCode(const std::string& msg, int errorCode,
					const ExceptionOrigin& origin) {
  return SystemError(detailsFromSystemCode(msg, errorCode), origin);
}

SystemError SystemError::fromSystemCode(const std::string& msg, int errorCode,
					const PistisException& cause,
					const ExceptionOrigin& origin) {
  return SystemError(detailsFromSystemCode(msg, errorCode), cause, origin);
}

SystemError SystemError::fromSystemCode(const std::string& msg,
					const ExceptionOrigin& origin) {
  return SystemError(detailsFromSystemCode(msg), origin);
}

SystemError SystemError::fromSystemCode(const std::string& msg,
					const PistisException& cause,
					const ExceptionOrigin& origin) {
  return SystemError(detailsFromSystemCode(msg), cause, origin);
}
