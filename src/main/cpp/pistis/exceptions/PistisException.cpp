#include "PistisException.hpp"
#include <algorithm>
#include <cstring>
#include <sstream>

#ifdef PISTIS_NO_BACKTRACE
#define BT
#else
#define BT StackFrame::trace(1)
#endif

using namespace pistis::exceptions;


PistisException::PistisException():
    _details(defaultDetails()), _origin(), _cause(), _backtrace(BT), _msg() {
  // Intentionally left blank
}

PistisException::PistisException(const std::string& details):
    _details(details), _origin(), _cause(), _backtrace(BT), _msg() {
  // Intentionally left blank
}

PistisException::PistisException(const ExceptionOrigin& origin):
    _details(defaultDetails()), _origin(origin), _cause(), _backtrace(BT),
    _msg() {
  // Intentionally left blank
}

PistisException::PistisException(const std::string& details,
				 const ExceptionOrigin& origin):
    _details(details), _origin(origin), _cause(), _backtrace(BT), _msg() {
  // Intentionally left blank
}

PistisException::PistisException(const std::string& details,
				 const PistisException& cause):
    _details(details), _origin(), _cause(cause.duplicate()), _backtrace(BT),
    _msg() {
  // Intentionally left blank
}

PistisException::PistisException(const std::string& details,
				 const PistisException& cause,
				 const ExceptionOrigin& origin):
    _details(details), _origin(origin), _cause(cause.duplicate()),
    _backtrace(BT), _msg() {
  // Intentionally left blank
}
	
PistisException::PistisException(const PistisException& ex):
    _details(ex.details()), _origin(ex.origin()),
    _cause(ex.cause() ? ex.cause()->duplicate() : nullptr),
    _backtrace(ex.backtrace()), _msg() {
  // Intentionally left blank
}

PistisException::PistisException(PistisException&& other) noexcept:
    _details(std::move(other._details)), _origin(std::move(other._origin)),
    _cause(other._cause.release()), _backtrace(std::move(other._backtrace)),
    _msg(other._msg.release()) {
  // Intentionally left blank
}

PistisException::~PistisException() noexcept = default;

std::ostream& PistisException::print(std::ostream& out, bool brief) const {
  printDetails_(out);
  if (!origin().empty()) {
    out << "\n  at " << origin();
  }
  if (!brief && !backtrace().empty()) {
    std::for_each(backtrace().begin(), backtrace().end(),
		  [&out](const StackFrame& f) { out << "\n    " << f; });
  }
  if (cause()) {
    out << "\nCaused by: ";
    cause()->print(out, brief);
  }
  return out;
}

std::string PistisException::toString(bool brief) const {
  std::ostringstream tmp;
  print(tmp, brief);
  return tmp.str();
}

PistisException* PistisException::duplicate() const {
  return new PistisException(*this);
}

const char* PistisException::what() const noexcept {
  if (!_msg) {
    std::string tmp= toString();
    _msg.reset(new char[tmp.length() + 1]);
    strcpy(_msg.get(), tmp.c_str());
  }
  return _msg.get();
}

PistisException& PistisException::operator=(const PistisException& other) {
  if (this != &other) {
    _details = other.details();
    _origin = other.origin();
    _cause.reset(other.cause() ? other.cause()->duplicate() : nullptr);
    _backtrace = other.backtrace();
    _msg.reset(nullptr);
  }
  return *this;
}

PistisException& PistisException::operator=(PistisException&& other) noexcept {
  if (this != &other) {
    _details = std::move(other._details);
    _origin = std::move(other._origin);
    _cause.reset(other._cause.release());
    _backtrace = std::move(other._backtrace);
    _msg.reset(other._msg.release());
  }
  return *this;
}

void PistisException::printDetails_(std::ostream& out) const {
  out << details();
}

const std::string& PistisException::defaultDetails() {
  static const std::string DEFAULT_DETAILS = "Exception occurred";
  return DEFAULT_DETAILS;
}
