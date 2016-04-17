/** @file ExceptionOriginTests.cpp
 *
 *  Unit tests for pistis::exceptions::ExceptionOrigin
 */

#include <pistis/exceptions/ExceptionOrigin.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace pistis::exceptions;

TEST(ExceptionOriginTests, DefaultConstruction) {
  ExceptionOrigin origin;
  std::ostringstream msg;

  EXPECT_TRUE(origin.empty());
  EXPECT_TRUE(origin.sig().empty());
  EXPECT_TRUE(origin.filename().empty());
  // origin.line() not specified when origin is default-constructed

  msg << origin;
  EXPECT_EQ(msg.str(), "");
}

TEST(ExceptionOriginTests, ConstructWithSignature) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  std::ostringstream msg;
  std::ostringstream truth;
  
  EXPECT_FALSE(origin.empty());
  EXPECT_EQ(origin.sig(), SIGNATURE);
  EXPECT_EQ(origin.filename(), FILENAME);
  EXPECT_EQ(origin.line(), LINE);
  
  msg << origin;
  truth << SIGNATURE << " [" << FILENAME << ":" << LINE << "]";
  EXPECT_EQ(msg.str(), truth.str());
}

TEST(ExceptionOriginTests, ConstructWithoutSignature) {
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin("", FILENAME, LINE);
  std::ostringstream msg;
  std::ostringstream truth;
  
  EXPECT_FALSE(origin.empty());
  EXPECT_EQ(origin.sig(), "");
  EXPECT_EQ(origin.filename(), FILENAME);
  EXPECT_EQ(origin.line(), LINE);
  
  msg << origin;
  truth << FILENAME << ":" << LINE;
  EXPECT_EQ(msg.str(), truth.str());
}

TEST(ExceptionOriginTests, ConstructWithMoveableArguments) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  std::string signature(SIGNATURE);
  std::string filename(FILENAME);
  int line= 10;
  ExceptionOrigin origin(std::move(signature), std::move(filename), line);
  std::ostringstream msg;
  std::ostringstream truth;
  
  EXPECT_FALSE(origin.empty());
  EXPECT_EQ(origin.sig(), SIGNATURE);
  EXPECT_EQ(origin.filename(), FILENAME);
  EXPECT_EQ(origin.line(), LINE);
  
  msg << origin;
  truth << SIGNATURE << " [" << FILENAME << ":" << LINE << "]";
  EXPECT_EQ(msg.str(), truth.str());

  // Commented out, pending verification that moving a string leaves it empty
  // EXPECT_EQ(signature, "");
  // EXPECT_EQ(filename, "");
  EXPECT_EQ(line, LINE);
}

TEST(ExceptionOriginTests, Copy) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin copy(origin);
  
  EXPECT_FALSE(origin.empty());
  EXPECT_EQ(origin.sig(), SIGNATURE);
  EXPECT_EQ(origin.filename(), FILENAME);
  EXPECT_EQ(origin.line(), LINE);

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.sig(), SIGNATURE);
  EXPECT_EQ(copy.filename(), FILENAME);
  EXPECT_EQ(copy.line(), LINE);
}

TEST(ExceptionOriginTests, Move) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin copy(std::move(origin));
  
  // Commented out, pending verification that moving a string leaves it empty
  //EXPECT_TRUE(origin.empty());
  //EXPECT_EQ(origin.sig(), "");
  //EXPECT_EQ(origin.filename(), "");
  //origin.line() unspecified after a move

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.sig(), SIGNATURE);
  EXPECT_EQ(copy.filename(), FILENAME);
  EXPECT_EQ(copy.line(), LINE);
}

TEST(ExceptionOriginTests, CopyAssign) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin copy;

  copy= origin;
  
  EXPECT_FALSE(origin.empty());
  EXPECT_EQ(origin.sig(), SIGNATURE);
  EXPECT_EQ(origin.filename(), FILENAME);
  EXPECT_EQ(origin.line(), LINE);

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.sig(), SIGNATURE);
  EXPECT_EQ(copy.filename(), FILENAME);
  EXPECT_EQ(copy.line(), LINE);
}

TEST(ExceptionOriginTests, MoveAssign) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin copy;

  copy= std::move(origin);
  
  // Commented out, pending verification that moving a string leaves it empty
  //EXPECT_TRUE(origin.empty());
  //EXPECT_EQ(origin.sig(), "");
  //EXPECT_EQ(origin.filename(), "");
  //origin.line() unspecified after a move

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.sig(), SIGNATURE);
  EXPECT_EQ(copy.filename(), FILENAME);
  EXPECT_EQ(copy.line(), LINE);
}

TEST(ExceptionOriginTests, Equality) {
  const std::string SIGNATURE("void f()");
  const std::string FILENAME("somefile");
  const int LINE= 10;
  const std::string OTHER_SIGNATURE("void g()");
  const std::string OTHER_FILENAME("someotherfile");
  const int OTHER_LINE= 15;
  ExceptionOrigin origin(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin same(SIGNATURE, FILENAME, LINE);
  ExceptionOrigin different1(OTHER_SIGNATURE, FILENAME, LINE);
  ExceptionOrigin different2(SIGNATURE, OTHER_FILENAME, LINE);
  ExceptionOrigin different3(SIGNATURE, FILENAME, OTHER_LINE);

  EXPECT_TRUE(origin == same);
  EXPECT_FALSE(origin != same);
  
  EXPECT_TRUE(origin != different1);
  EXPECT_TRUE(origin != different2);
  EXPECT_TRUE(origin != different3);
  EXPECT_FALSE(origin == different1);
  EXPECT_FALSE(origin == different2);
  EXPECT_FALSE(origin == different3);
}

