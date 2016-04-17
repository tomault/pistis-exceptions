#ifndef __PISTIS__EXCEPTIONS__ITEMEXISTSERROR_HPP__
#define __PISTIS__EXCEPTIONS__ITEMEXISTSERROR_HPP__

#include <pistis/exceptions/PistisException.hpp>

namespace pistis {
  namespace exceptions {

    class ItemExistsError : public PistisException {
    public:
      ItemExistsError(const ExceptionOrigin& origin);
      ItemExistsError(const std::string& what,
		      const ExceptionOrigin& origin);
      ItemExistsError(const std::string& what,
		      const std::string& container,
		      const ExceptionOrigin& origin);

      virtual ItemExistsError* duplicate() const;
      
    private:
      static std::string _createMessage(const std::string& what,
					  const std::string& container);
    };
    
  }
}
#endif
