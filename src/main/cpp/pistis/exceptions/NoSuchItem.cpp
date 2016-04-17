#include "NoSuchItem.hpp"
#include <sstream>

using namespace pistis::exceptions;

NoSuchItem::NoSuchItem(const std::string& itemName,
		       const ExceptionOrigin& origin):
    PistisException(_createDetails(itemName, std::string()), origin) {
  // Intentionally left blank
}

NoSuchItem::NoSuchItem(const std::string& itemName,
		       const std::string& container,
		       const ExceptionOrigin& origin):
    PistisException(_createDetails(itemName, container), origin) {
  // Intentionally left blank
}

NoSuchItem::NoSuchItem(NoSuchItem&& other):
    PistisException(other) {
  // Intentionally left blank
}

NoSuchItem* NoSuchItem::duplicate() const {
  return new NoSuchItem(*this);
}

NoSuchItem& NoSuchItem::operator=(NoSuchItem&& other) {
  PistisException::operator=(std::move(other));
  return *this;
}

std::string NoSuchItem::_createDetails(const std::string& itemName,
				       const std::string& container) {
  std::ostringstream msg;
  msg << "No such item";
  if (!itemName.empty()) {
    msg << " \"" << itemName << "\"";
  }
  if (!container.empty()) {
    msg << " in \"" << container << "\"";
  }
  return msg.str();
}
