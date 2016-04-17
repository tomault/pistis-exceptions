#ifndef __PISTIS__EXCEPTIONS__NOSUCHITEM_HPP__
#define __PISTIS__EXCEPTIONS__NOSUCHITEM_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    /** @brief Indicates an item does not exist in some collection */
    class NoSuchItem : public PistisException {
    public:
      NoSuchItem(const std::string& itemName, const ExceptionOrigin& origin);
      NoSuchItem(const std::string& itemName, const std::string& container,
		 const ExceptionOrigin& origin);
      NoSuchItem(const NoSuchItem& other) = default;
      NoSuchItem(NoSuchItem&& other);

      virtual NoSuchItem* duplicate() const;
      
      NoSuchItem& operator=(const NoSuchItem& other)= default;
      NoSuchItem& operator=(NoSuchItem&& other);

    private:
      static std::string _createDetails(const std::string& itemName,
					const std::string& container);

    };

  }
}
#endif

