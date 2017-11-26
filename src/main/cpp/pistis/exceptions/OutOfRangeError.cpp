#include "OutOfRangeError.hpp"
#include <sstream>

using namespace pistis::exceptions;

OutOfRangeError::OutOfRangeError(const std::string& details):
    PistisException(details) {
}

OutOfRangeError::OutOfRangeError(const std::string& details,
				 const ExceptionOrigin& origin):
    PistisException(details, origin) {
}

OutOfRangeError::~OutOfRangeError() noexcept { }

OutOfRangeError* OutOfRangeError::duplicate() const {
  return new OutOfRangeError(*this);
}

OutOfRangeError OutOfRangeError::of(const std::string& what) {
  std::ostringstream msg;
  msg << "\"" << what << "\" is out-of-range";
  return OutOfRangeError(msg.str());
}

OutOfRangeError OutOfRangeError::of(const std::string& what,
				    const ExceptionOrigin& origin) {
  std::ostringstream msg;
  msg << "\"" << what << "\" is out-of-range";
  return OutOfRangeError(msg.str(), origin);
}

OutOfRangeError OutOfRangeError::of(const std::string& what,
				    const std::string& details) {
  std::ostringstream msg;
  msg << "\"" << what << "\" is out-of-range (" << details << ")";
  return OutOfRangeError(msg.str());
}

OutOfRangeError OutOfRangeError::of(const std::string& what,
				    const std::string& details,
				    const ExceptionOrigin& origin) {
  std::ostringstream msg;
  msg << "\"" << what << "\" is out-of-range (" << origin << ")";
  return OutOfRangeError(msg.str());
}


