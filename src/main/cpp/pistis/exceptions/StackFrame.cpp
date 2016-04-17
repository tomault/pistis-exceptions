#include "StackFrame.hpp"
#include <cstddef>
#include <iomanip>

#ifdef __GNUC__
#include "GccStacktraceFactory.hpp"
#endif

using namespace pistis::exceptions;

StackFrame::StackFrame(const std::string& functionSignature,
		       const void* address, const std::string& module,
		       const void* functionStart, const void* functionEnd):
    _sig(functionSignature), _address(address), _module(module),
    _fnStart(functionStart), _fnEnd(functionEnd) {
  // Intentionally left blank
}

std::vector<StackFrame> StackFrame::trace(size_t skip, size_t maxFrames) {
#ifdef __GNUC__
  GccStacktraceFactory getBacktrace(maxFrames);
  return getBacktrace(skip+1);
#else
  static const std::vector<StackFrame> _EMPTY_BACKTRACE;
  return _EMPTY_BACKTRACE;
#endif
}

bool StackFrame::operator==(const StackFrame& other) const {
  return (signature() == other.signature()) &&
         (address() == other.address()) &&
         (module() == other.module()) &&
         (functionStart() == other.functionStart()) &&
         (functionEnd() == other.functionEnd());
}

bool StackFrame::operator!=(const StackFrame& other) const {
  return (signature() != other.signature()) ||
         (address() != other.address()) ||
         (module() != other.module()) ||
         (functionStart() != other.functionStart()) ||
         (functionEnd() != other.functionEnd());
}

std::ostream& pistis::exceptions::operator<<(
    std::ostream& out, const StackFrame& frame
) {
  out << frame.address();
  if (frame.hasSignature()) {
    out << " " << frame.signature();
  }
  if (frame.hasFunctionStart()) {
    ptrdiff_t offset=
      (const unsigned char*)frame.address() -
      (const unsigned char*)frame.functionStart();
    out << "+0x" << std::hex << offset;
  }
  if (frame.hasModule()) {
    out << " [" << frame.module() << "]";
  }
  return out;
}

