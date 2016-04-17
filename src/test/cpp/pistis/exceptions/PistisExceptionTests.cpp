/** @file PistisExceptionTests.cpp
 *
 *  Unit tests for pistis::exceptions::PistisException
 */

#include <pistis/exceptions/PistisException.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace pistis::exceptions;

TEST(PistisExceptionTests, DefaultConstruction) {
  PistisException e;

  EXPECT_EQ(e.details(), "Exception occurred");
  EXPECT_TRUE(e.origin().empty());
  EXPECT_TRUE(e.cause() == nullptr);
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
#endif
}

TEST(PistisExceptionTests, ConstructWithDetails) {
  const std::string DETAILS("This is an exception");
  PistisException e(DETAILS);

  EXPECT_EQ(e.details(), DETAILS);
  EXPECT_TRUE(e.origin().empty());
  EXPECT_TRUE(e.cause() == nullptr);
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
#endif
}

TEST(PistisExceptionTests, ConstructWithOrigin) {
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  PistisException e(ORIGIN);

  EXPECT_EQ(e.details(), "Exception occurred");
  EXPECT_EQ(e.origin(), ORIGIN);
  EXPECT_TRUE(e.cause() == nullptr);
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
#endif
}

TEST(PistisExceptionTests, ConstructWithOriginAndDetails) {
  const std::string DETAILS("This is an exception");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  PistisException e(DETAILS, ORIGIN);

  EXPECT_EQ(e.details(), DETAILS);
  EXPECT_EQ(e.origin(), ORIGIN);
  EXPECT_TRUE(e.cause() == nullptr);
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
#endif
}

TEST(PistisExceptionTests, ConstructWithCauseAndDetails) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause);

  EXPECT_EQ(e.details(), DETAILS);
  EXPECT_TRUE(e.origin().empty());
  ASSERT_TRUE(e.cause());
  EXPECT_EQ(e.cause()->details(), cause.details());
  EXPECT_EQ(e.cause()->origin(), cause.origin());
  EXPECT_EQ(e.cause()->cause(), cause.cause());
  EXPECT_NE(e.cause(), &cause);  // e.cause() is a copy of cause, not cause itself
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
  EXPECT_TRUE(e.cause()->backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
  EXPECT_FALSE(e.cause()->backtrace().empty());
#endif
}

TEST(PistisExceptionTests, ConstructWithCauseOriginAndDetails) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);

  EXPECT_EQ(e.details(), DETAILS);
  EXPECT_EQ(e.origin(), ORIGIN);
  ASSERT_TRUE(e.cause());
  EXPECT_EQ(e.cause()->details(), cause.details());
  EXPECT_EQ(e.cause()->origin(), cause.origin());
  EXPECT_EQ(e.cause()->cause(), cause.cause());
  EXPECT_NE(e.cause(), &cause);  // e.cause() is a copy of cause, not cause itself
#ifdef PISTIS_NO_BACKTRACE
  EXPECT_TRUE(e.backtrace().empty());
  EXPECT_TRUE(e.cause()->backtrace().empty());
#else
  EXPECT_FALSE(e.backtrace().empty());
  EXPECT_FALSE(e.cause()->backtrace().empty());
#endif
}

TEST(PistisExceptionTests, Copy) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  PistisException copy(e);

  EXPECT_EQ(e.details(), copy.details());
  EXPECT_EQ(e.origin(), copy.origin());
  ASSERT_TRUE(e.cause());
  ASSERT_TRUE(copy.cause());
  EXPECT_NE(e.cause(), copy.cause()); // copy.cause() is a copy of e.cause()
  EXPECT_EQ(e.cause()->details(), copy.cause()->details());
  EXPECT_EQ(e.cause()->origin(), copy.cause()->origin());
  EXPECT_FALSE(copy.cause()->cause());
  EXPECT_TRUE(e.backtrace() == copy.backtrace());
  EXPECT_TRUE(e.cause()->backtrace() == copy.cause()->backtrace());
}

TEST(PistisExceptionTests, Move) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  const PistisException* causePtr= e.cause();
  std::vector<StackFrame> backtrace= e.backtrace();
  PistisException copy(std::move(e));

  EXPECT_EQ(copy.details(), DETAILS);
  EXPECT_EQ(copy.origin(), ORIGIN);
  EXPECT_EQ(copy.cause(), causePtr);
  EXPECT_TRUE(copy.backtrace() == backtrace);

  EXPECT_TRUE(e.details().empty());
  EXPECT_TRUE(e.origin().empty());
  EXPECT_FALSE(e.cause());
  EXPECT_TRUE(e.backtrace().empty());
}

TEST(PistisExceptionTests, CopyAssign) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  PistisException copy;

  copy= e;

  EXPECT_EQ(e.details(), copy.details());
  EXPECT_EQ(e.origin(), copy.origin());
  ASSERT_TRUE(e.cause());
  ASSERT_TRUE(copy.cause());
  EXPECT_NE(e.cause(), copy.cause()); // copy.cause() is a copy of e.cause()
  EXPECT_EQ(e.cause()->details(), copy.cause()->details());
  EXPECT_EQ(e.cause()->origin(), copy.cause()->origin());
  EXPECT_FALSE(copy.cause()->cause());
  EXPECT_TRUE(e.backtrace() == copy.backtrace());
  EXPECT_TRUE(e.cause()->backtrace() == copy.cause()->backtrace());
}

TEST(PistisExceptionTests, MoveAssign) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  const PistisException* causePtr= e.cause();
  std::vector<StackFrame> backtrace= e.backtrace();
  PistisException copy;

  copy= std::move(e);

  EXPECT_EQ(copy.details(), DETAILS);
  EXPECT_EQ(copy.origin(), ORIGIN);
  EXPECT_EQ(copy.cause(), causePtr);
  EXPECT_TRUE(copy.backtrace() == backtrace);

  EXPECT_FALSE(e.cause());
}

TEST(PistisExceptionTests, Duplicate) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  std::unique_ptr<PistisException> copy(e.duplicate());

  EXPECT_EQ(e.details(), copy->details());
  EXPECT_EQ(e.origin(), copy->origin());
  ASSERT_TRUE(e.cause());
  ASSERT_TRUE(copy->cause());
  EXPECT_NE(e.cause(), copy->cause()); // copy.cause() is a copy of e.cause()
  EXPECT_EQ(e.cause()->details(), copy->cause()->details());
  EXPECT_EQ(e.cause()->origin(), copy->cause()->origin());
  EXPECT_FALSE(copy->cause()->cause());
  EXPECT_TRUE(e.backtrace() == copy->backtrace());
  EXPECT_TRUE(e.cause()->backtrace() == copy->cause()->backtrace());
}

TEST(PistisExceptionTests, Print) {
  std::string EX_PRINTED("This is an exception\n  at void f() [somefile:10]\n");
  std::string CAUSE_PRINTED("Caused by: This is its cause\n  at void g() [someotherfile:1]");
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  std::ostringstream msg;
  std::string printed;
  
  e.print(msg, true);
  EXPECT_EQ(msg.str(), EX_PRINTED + CAUSE_PRINTED);

  msg.str(std::string());
  e.print(msg, false);  // May have a stack trace in it
  printed= msg.str();
  EXPECT_EQ(printed.find(EX_PRINTED), 0);
  EXPECT_NE(printed.find(CAUSE_PRINTED), std::string::npos);
}

TEST(PistisExceptionTests, ToString) {
  std::string EX_PRINTED("This is an exception\n  at void f() [somefile:10]\n");
  std::string CAUSE_PRINTED("Caused by: This is its cause\n  at void g() [someotherfile:1]");
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  std::string printed;
  
  printed= e.toString(true);
  EXPECT_EQ(printed, EX_PRINTED + CAUSE_PRINTED);

  printed= e.toString(false); // May have a stack trace in it
  EXPECT_EQ(printed.find(EX_PRINTED), 0);
  EXPECT_NE(printed.find(CAUSE_PRINTED), std::string::npos);
}

TEST(PistisExceptionTests, What) {
  const std::string DETAILS("This is an exception");
  const std::string CAUSE_DETAILS("This is its cause");
  const ExceptionOrigin ORIGIN("void f()", "somefile", 10);
  const ExceptionOrigin CAUSE_ORIGIN("void g()", "someotherfile", 1);
  PistisException cause(CAUSE_DETAILS, CAUSE_ORIGIN);
  PistisException e(DETAILS, cause, ORIGIN);
  std::string printed= e.toString();
  const char* whatMsg= e.what();

  EXPECT_EQ(printed, whatMsg);

  // Calling what() a second time does not recreate the message, but
  // uses the stored message
  EXPECT_EQ(e.what(), whatMsg);
}

