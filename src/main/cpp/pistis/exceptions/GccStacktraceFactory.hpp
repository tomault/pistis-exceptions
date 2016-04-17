#ifndef __PISTIS__EXCEPTIONS__GCCSTACKTRACEFACTORY_HPP__
#define __PISTIS__EXCEPTIONS__GCCSTACKTRACEFACTORY_HPP__

#include <pistis/exceptions/StackFrame.hpp>
#include <regex>
#include <string>
#include <vector>

namespace pistis {
  namespace exceptions {

    class GccStacktraceFactory {
    public:
      GccStacktraceFactory(size_t maxFrames);

      std::vector<StackFrame> operator()(size_t skip=0) const;

    private:
      size_t _maxFrames;

      struct FrameInfo {
	std::string signature;
	const void* address;
	std::string module;
	const void* start;

	FrameInfo(const void* address_);
      };

      void _parseFrameDescription(const char* text, FrameInfo& info) const;
      std::string _demangle(const char* text, const char* end) const;

      static const std::regex& frameInfoRegex();
    };

  }
}
#endif
