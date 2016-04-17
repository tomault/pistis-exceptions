#include "GccStacktraceFactory.hpp"
#include <execinfo.h>
#include <cxxabi.h>
#include <cstdlib>

using namespace pistis::exceptions;

GccStacktraceFactory::GccStacktraceFactory(size_t maxFrames):
    _maxFrames(maxFrames) {
  // Intentionally left blank
}

std::vector<StackFrame> GccStacktraceFactory::operator()(size_t skip) const {
  void** addresses= new void*[_maxFrames];
  int n= backtrace(addresses, _maxFrames);
  std::vector<StackFrame> frames;

  if (n > (skip+1)) {
    char** symbols= backtrace_symbols(addresses, n);
    char** sym= symbols ? symbols+skip+1 : NULL;
    void** address= addresses+skip+1;
    void** end= addresses+n;
    
    frames.reserve(n-skip-1);
    while (address < end) {
      FrameInfo info(*address);
      if (symbols) {
	_parseFrameDescription(*sym, info);
	++sym;
      }
      frames.push_back(StackFrame(info.signature, *address, info.module,
				  info.start, NULL));
      ++address;
    }

    free(symbols);
  }
  delete[] addresses;
  return frames;
}

void GccStacktraceFactory::_parseFrameDescription(const char* text,
						  FrameInfo& info) const {
  std::cmatch m;
  if (!text || !*text) {
    // Do nothing with empty or non-existent entries
  } else if (std::regex_search(text, m, frameInfoRegex())) {
    if (m[1].matched) {
      info.module.assign(m[1].first, m[1].second);
    }
    info.signature= _demangle(m[2].first, m[2].second);
    if (m[3].matched) {
      std::string tmp(m[3].first, m[3].second);
      unsigned long int offset= strtoul(tmp.c_str(), NULL, 16);
      info.start= (unsigned char*)info.address - offset;
    }
  } else {
    info.signature= text;
  }
}

std::string GccStacktraceFactory::_demangle(const char* text,
					    const char* end) const {
  if (text && *text) {
    std::string tmp(text, end);
    int status= 0;
    char* demangled= abi::__cxa_demangle(tmp.c_str(), 0, 0, &status);
    if (demangled) {
      if (*demangled) {
	tmp.assign(demangled);
      }
      free(demangled);
    }
    return tmp;
  }
  return std::string();
}

const std::regex& GccStacktraceFactory::frameInfoRegex() {
  static const std::regex FRAME_INFO_REX(
      "^\\s*([^\\(]*)\\(([^\\)\\+]+)(\\+([^\\)]+))?\\)"
  );
  return FRAME_INFO_REX;
}

GccStacktraceFactory::FrameInfo::FrameInfo(const void* address_):
    signature(), address(address_), module(), start(nullptr) {
  // Intentionally left blank
}
