#include "ExceptionOrigin.hpp"

using namespace pistis::exceptions;

ExceptionOrigin::ExceptionOrigin():
    _sig(), _filename(), _line() {
  // Intentionally left blank
}

ExceptionOrigin::ExceptionOrigin(const std::string& sig,
				 const std::string& filename, int line):
    _sig(sig), _filename(filename), _line(line) {
  // Intentionally left blank
}

ExceptionOrigin::ExceptionOrigin(std::string&& sig, std::string&& filename,
				 int line):
    _sig(sig), _filename(filename), _line(line) {
  // Intentionally left blank
}

bool ExceptionOrigin::operator==(const ExceptionOrigin& other) const {
  return (sig() == other.sig()) &&
         (filename() == other.filename()) &&
         (line() == other.line());
}

bool ExceptionOrigin::operator!=(const ExceptionOrigin& other) const {
  return (sig() != other.sig()) ||
         (filename() != other.filename()) ||
         (line() != other.line());
}

std::ostream& pistis::exceptions::operator<<(std::ostream& out,
					     const ExceptionOrigin& o) {
  if (!o.sig().empty()) {
    out << o.sig();
    if (!o.filename().empty()) {
      out << " [" << o.filename() << ":" << o.line() << "]";
    }
  } else if (!o.filename().empty()) {
    out << o.filename() << ":" << o.line();
  }
  return out;
}
