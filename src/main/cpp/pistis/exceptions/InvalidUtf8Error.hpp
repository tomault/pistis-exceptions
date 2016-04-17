#ifndef __PISTIS__EXCEPTIONS__INVALIDUTF8ERROR_HPP__
#define __PISTIS__EXCEPTIONS__INVALIDUTF8ERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include <type_traits>

namespace pistis {
  namespace exceptions {

    class InvalidUtf8Error : public PistisException {
    public:
      static constexpr const uint32_t UNKNOWN_OFFSET = (uint32_t)-1;

    public:
      InvalidUtf8Error(uint32_t charOffset, uint32_t byteOffset,
		       const std::string& details,
		       const ExceptionOrigin& origin);
      InvalidUtf8Error(const InvalidUtf8Error&) = default;
      InvalidUtf8Error(InvalidUtf8Error&&) = default;

      uint32_t offset() const { return charOffset_ + byteOffset_; }
      uint32_t charOffset() const { return charOffset_; }
      uint32_t byteOffset() const { return byteOffset_; }

      void setCharOffset(uint32_t offset) { charOffset_ = offset; }
      void increaseCharOffset(uint32_t delta) { charOffset_ += delta; }

      template <typename Ptr>
      InvalidUtf8Error& setContext(Ptr startOfData, Ptr endOfData,
				   Ptr offendingByte, uint32_t bytesBefore,
				   uint32_t bytesAfter) {
	std::ostringstream ctx;
	Ptr p = 
	  writeSegment_(ctx, goBack_(offendingByte, bytesBefore, startOfData),
			offendingByte);
	writeByte_(ctx, *p);
	writeSegment_(ctx, p, goForward(p, bytesAfter, endOfData));
	context_ = ctx.str();
	return *this;
      }

      virtual InvalidUtf8Error* duplicate() const;

      InvalidUtf8Error& operator=(const InvalidUtf8Error&) = default;
      InvalidUtf8Error& operator=(InvalidUtf8Error&&) = default;

      static InvalidUtf8Error invalidStartByte(uint32_t startByte,
					       const ExceptionOrigin& origin) {
	return invalidStartByte(UNKNOWN_OFFSET, startByte, origin);
      }

      static InvalidUtf8Error invalidStartByte(uint32_t charOffset,
					       uint32_t startByte,
					       const ExceptionOrigin& origin);

      static InvalidUtf8Error invalidTrailingByte(
          uint32_t offset, uint32_t trailingByte,
	  const ExceptionOrigin& origin
      ) {
	return invalidTrailingByte(UNKNOWN_OFFSET, offset, trailingByte,
				   origin);
      }

      static InvalidUtf8Error invalidTrailingByte(
          uint32_t charOffset, uint32_t byteOffset, uint32_t trailingByte,
	  const ExceptionOrigin& origin
      );

      static InvalidUtf8Error notUnicodeChar(uint32_t startByte,
					     const ExceptionOrigin& origin) {
	return notUnicodeChar(UNKNOWN_OFFSET, startByte, origin);
      }

      static InvalidUtf8Error notUnicodeChar(uint32_t charOffset,
					     uint32_t startByte,
					     const ExceptionOrigin& origin);

    private:
      uint32_t charOffset_;
      uint32_t byteOffset_;
      std::string context_;

      template <typename Ptr,
		typename Tag =
		  typename std::iterator_traits<Ptr>::iterator_category>
      Ptr goBack_(Ptr p, uint32_t n, Ptr limit,
		  typename std::enable_if<
		      std::is_same<Tag, std::random_access_iterator_tag>::value,
		      int
		  >::type = 0) {
	Ptr q = p - n;
	return (q < limit) ? limit : q;
      }

      template <typename Ptr,
		typename Tag =
		  typename std::iterator_traits<Ptr>::iterator_category>
      Ptr goBack_(Ptr p, uint32_t n, Ptr limit,
		  std::enable_if<
		      std::is_same<
		          Tag, std::bidirectional_iterator_tag
		      >::value,
		      int
		  > = 0) {
	Ptr q = p;
	while ((q != limit) && n) {
	  --q;
	  --n;
	}
	return q;
      }

      template <typename Ptr,
		typename Tag =
		  typename std::iterator_traits<Ptr>::iterator_category>
      Ptr goForward_(Ptr p, uint32_t n, Ptr limit,
		     std::enable_if<
		         std::is_same<Tag,
		         std::random_access_iterator_tag>::value, int
		     > = 0) {
	Ptr q = p + n;
	return (q < limit) ? q : limit;
      }

      template <typename Ptr,
		typename Tag =
		  typename std::iterator_traits<Ptr>::iterator_category>
      Ptr goForward_(
          Ptr p, uint32_t n, Ptr limit,
	  std::enable_if<
	      std::is_same<Tag, std::bidirectional_iterator_tag>::value,
	      int
	  > = 0
      ) {
	Ptr q = p;
	while ((q != limit) && n) {
	  ++q;
	  --n;
	}
	return q;
      }

      template <typename Ptr>
      Ptr writeSegment_(std::ostringstream& ctx, Ptr start, Ptr end) {
	Ptr p = start;
	if (p != end) {
	  ctx << "[";
	  while (p != end) {
	    if (p != start) {
	      ctx << " ";
	    }
	    ctx << writeByte_(ctx, *p);
	    ++p;
	  }
	  ctx << "]";
	}
	return p;
      }

      void writeByte_(std::ostringstream& ctx, uint32_t b) {
	if (((b >= 0x20) && (b < 0x80)) || (b >= 0xA0)) {
	  ctx << (char)b;
	} else {
	  ctx << "0x" << std::hex << std::setw(2) << std::setfill('0') << b;
	}
      }

      virtual void printDetails_(std::ostream& out) const;

      void setContext_(const std::string& context) { context_ = context; }
    };

  }
}
#endif
