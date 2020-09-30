/**
 * @file DiLibTest.cc
 * @brief This is sample unit test.
 * @copyright Copyright (c) 2020 Yasuaki Miyoshi
 */
#include "Lib.h"
#include "StdoutWriter.h"
#include <gtest/gtest.h>

namespace {
class StdoutWriter : public CppDevelopTemplate::IWriter {
public:
    /**
     * @brief Construct a new StdoutWriter object
     *
     */
    INJECT(StdoutWriter()) = default;

    /**
     * @brief 内部インターフェースのメソッドの実装
     *
     * @param s
     */
    void write(std::string s) override
    {
        (void)s;
        std::cout << "hogehogeohge" << std::endl;
    }
};

fruit::Component<CppDevelopTemplate::IWriter> getMockWriter() {
  return fruit::createComponent()
      .bind<CppDevelopTemplate::IWriter, StdoutWriter>();
}

fruit::Component<CppDevelopTemplate::ILib> getMainComponent() {
  return fruit::createComponent()
      .replace(CppDevelopTemplate::getStdoutWriter).with(getMockWriter)
      .install(CppDevelopTemplate::getLib);
}

fruit::Injector<CppDevelopTemplate::ILib> createInjector() {
    return fruit::Injector<CppDevelopTemplate::ILib>(getMainComponent);
}

/**
 * @brief This class derives a class from testing::Test
 *        for using the same data configuration for multiple tests.
 */
class DiLibTest : public testing::Test {
protected:
    /**
     * @brief Constructor
     */
    DiLibTest() = default;

    /**
     * @brief Destructor
     */
    virtual ~DiLibTest() noexcept = default;

protected:
    /**
     * @brief Prepares the objects for each test.
     */
    virtual void SetUp() override
    {
    }

    /**
     * @brief Releases any resources allocated in SetUp().
     */
    virtual void TearDown() override
    {
    }
};
} /* unnamed namespace */

TEST_F(DiLibTest, ExecutesCorrectly)
{
    fruit::Injector<CppDevelopTemplate::ILib> injector = createInjector();
    auto target = injector.get<CppDevelopTemplate::ILib*>();
    target->execute();
    auto expect = 0;
    auto actual = 0;
    ASSERT_EQ(expect, actual);
}