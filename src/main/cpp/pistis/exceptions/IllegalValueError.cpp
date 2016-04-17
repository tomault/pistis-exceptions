#include "IllegalValueError.hpp"
#include <sstream>

using namespace pistis::exceptions;

IllegalValueError::IllegalValueError(const std::string& details,
				     const ExceptionOrigin& origin):
    PistisException(details, origin) {
  // Intentionally left blank
}

IllegalValueError::IllegalValueError(const std::string& what,
				     const std::string& details,
				     const ExceptionOrigin& origin):
    PistisException(_createMessage(what, "", details), origin) {
  // Intentionally left blank
}

IllegalValueError::IllegalValueError(const std::string& what,
				     const std::string& value,
				     const std::string& details,
				     const ExceptionOrigin& origin):
    PistisException(_createMessage(what, value, details), origin) {
  // Intentionally left blank
}

IllegalValueError* IllegalValueError::duplicate() const {
  return new IllegalValueError(*this);
}

std::string IllegalValueError::_createMessage(const std::string& what,
					      const std::string& value,
					      const std::string& details) {
  std::ostringstream msg;
  msg << "Illegal value";
  if (!value.empty()) {
    msg << "\"" << value << "\"";
  }
  if (!what.empty()) {
    msg << " for " << what;
  }
  if (!details.empty()) {
    msg << " (" << details << ")";
  }
  return msg.str();
}
