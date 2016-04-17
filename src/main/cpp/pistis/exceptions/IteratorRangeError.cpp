#include "IteratorRangeError.hpp"

using namespace pistis::exceptions;

IteratorRangeError::IteratorRangeError(const ExceptionOrigin& origin):
    PistisException("Iterator out-of-bounds", origin) {
  // Intentionally left blank
}

IteratorRangeError::IteratorRangeError(const std::string& details,
				       const ExceptionOrigin& origin):
    PistisException(details, origin) {
  // Intentionally left blank
}

IteratorRangeError* IteratorRangeError::duplicate() const {
  return new IteratorRangeError(*this);
}
