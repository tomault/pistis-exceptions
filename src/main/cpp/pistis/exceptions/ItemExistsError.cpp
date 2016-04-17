#include "ItemExistsError.hpp"
#include <sstream>

using namespace pistis::exceptions;

ItemExistsError::ItemExistsError(const ExceptionOrigin& origin):
    PistisException("Item exists", origin) {
  // Intentionally left blank
}

ItemExistsError::ItemExistsError(const std::string& what,
				 const ExceptionOrigin& origin):
    PistisException(_createMessage(what, ""), origin) {
  // Intentionally left blank
}

ItemExistsError::ItemExistsError(const std::string& what,
				 const std::string& container,
				 const ExceptionOrigin& origin):
    PistisException(_createMessage(what, container), origin) {
  // Intentionally left blank
}

ItemExistsError* ItemExistsError::duplicate() const {
  return new ItemExistsError(*this);
}

std::string ItemExistsError::_createMessage(const std::string& what,
					    const std::string& container) {
  std::ostringstream msg;
  if (what.empty()) {
    msg << "Item";
  } else {
    msg << what;
  }
  msg << " exists";
  if (!container.empty()) {
    msg << " in " << container;
  }
  return msg.str();
}
