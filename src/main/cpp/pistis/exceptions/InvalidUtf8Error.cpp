#include "InvalidUtf8Error.hpp"

using namespace pistis::exceptions;

InvalidUtf8Error::InvalidUtf8Error(uint32_t charOffset, uint32_t byteOffset,
				   const std::string& details,
				   const ExceptionOrigin& origin):
    PistisException(details, origin), charOffset_(charOffset),
    byteOffset_(byteOffset_), context_() {
  // Intentionally left blank
}

InvalidUtf8Error* InvalidUtf8Error::duplicate() const {
  InvalidUtf8Error* dup=
    new InvalidUtf8Error(charOffset_, byteOffset_, details(), origin());
  dup->setContext_(context_);
  return dup;
}

InvalidUtf8Error InvalidUtf8Error::invalidStartByte(
    uint32_t charOffset, uint32_t startByte, const ExceptionOrigin& origin
) {
  std::ostringstream details;
  details << "Lead byte 0x" << std::hex << std::setw(2) << std::setfill('0')
	  << startByte << " is invalid";
  return InvalidUtf8Error(charOffset, 0, details.str(), origin);
}

InvalidUtf8Error InvalidUtf8Error::invalidTrailingByte(
    uint32_t charOffset, uint32_t byteOffset, uint32_t trailingByte,
    const ExceptionOrigin& origin
) {
  std::ostringstream details;
  details << "Trailing byte #" << byteOffset << " (0x"
	  << std::hex << std::setw(2) << std::setfill('0') << trailingByte
	  << " is invalid";
  return InvalidUtf8Error(charOffset, byteOffset, details.str(), origin);
}

InvalidUtf8Error InvalidUtf8Error::notUnicodeChar(
    uint32_t charOffset, uint32_t startByte, const ExceptionOrigin& origin
) {
  std::ostringstream details;
  details << "Character with lead byte 0x" << std::hex << std::setw('0')
	  << std::setfill('0') << startByte
	  << " is not a legal unicode character";
  return InvalidUtf8Error(charOffset, 0, details.str(), origin);
}

void InvalidUtf8Error::printDetails_(std::ostream& out) const {
  out << "Invalid UTF-8 character";
  if (charOffset_ != UNKNOWN_OFFSET) {
    out << " at offset " << charOffset();
  }
  out << " (" << details();
  if (!context_.empty()) {
    out << " - Context is " << context_;
  }
  out << ")";
}
