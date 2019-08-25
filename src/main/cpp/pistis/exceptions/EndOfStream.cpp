#include "EndOfStream.hpp"

using namespace pistis::exceptions;

EndOfStream::EndOfStream(const ExceptionOrigin& origin):
    PistisException("End of stream reached", origin) {
}

EndOfStream::EndOfStream(const std::string& details,
			 const ExceptionOrigin& origin):
    PistisException(details, origin) {
}
