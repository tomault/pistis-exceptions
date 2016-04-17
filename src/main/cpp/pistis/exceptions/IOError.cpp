#include "IOError.hpp"
#include <sstream>
#include <string.h>


using namespace pistis::exceptions;

IOError::IOError(const std::string& details, const ExceptionOrigin& origin):
    PistisException(details, origin) {
  // Intentionally left blank
}

IOError::IOError(const std::string& details, const PistisException& cause,
		 const ExceptionOrigin& origin):
    PistisException(details, cause, origin) {
  // Intentionally left blank  
}

IOError* IOError::duplicate() const {
  return new IOError(*this);
}

std::string IOError::detailsFromSystemError(const std::string& msg,
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

std::string IOError::detailsFromSystemError(const std::string& msg) {
  return detailsFromSystemError(msg, errno);
}

IOError IOError::fromSystemError(const std::string& msg, int errorCode,
				 const ExceptionOrigin& origin) {
  return IOError(detailsFromSystemError(msg, errorCode), origin);
}

IOError IOError::fromSystemError(const std::string& msg, int errorCode,
				 const PistisException& cause,
				 const ExceptionOrigin& origin) {
  return IOError(detailsFromSystemError(msg, errorCode), cause, origin);
}

IOError IOError::fromSystemError(const std::string& msg,
				 const ExceptionOrigin& origin) {
  return IOError(detailsFromSystemError(msg), origin);
}

IOError IOError::fromSystemError(const std::string& msg,
				 const PistisException& cause,
				 const ExceptionOrigin& origin) {
  return IOError(detailsFromSystemError(msg), cause, origin);
}
