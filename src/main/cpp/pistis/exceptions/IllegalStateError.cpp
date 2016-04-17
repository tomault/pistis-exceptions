#include "IllegalStateError.hpp"

using namespace pistis::exceptions;

IllegalStateError::IllegalStateError(const std::string& details,
				     const ExceptionOrigin& origin):
    PistisException("Illegal state: " + details, origin) {
  // Intentionally left blank
}

IllegalStateError::IllegalStateError(const std::string& details,
				     const PistisException& cause,
				     const ExceptionOrigin& origin):
    PistisException("Illegal state: " + details, cause, origin) {
  // Intentionally left blank  
}

IllegalStateError* IllegalStateError::duplicate() const {
  return new IllegalStateError(*this);
}
