/**
 * @file LogSettingsTest.cc
 * @brief Implementation of unit test for LogSettings data class.
 * @copyright Copyright (c) 2020 Yasuaki Miyoshi.
 *
 * This software is released under the MIT License.
 * see http://opensource.org/licenses/mit-license.php
 */
#include <fstream>

#include <cereal/archives/json.hpp>
#include <gtest/gtest.h>

#include "logger/LogSettings.h"

namespace {
/**
 * @brief This class derives a class from testing::Test
 *        for using the same data configuration for multiple tests.
 */
class LogSettingsTest : public testing::Test {
protected:
    /**
     * @brief Constructor
     */
    LogSettingsTest() = default;

    /**
     * @brief Destructor
     */
    virtual ~LogSettingsTest() noexcept = default;

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
}

TEST_F(LogSettingsTest, WriteAndReadJsonCorrectly)
{
    const std::string jsonFilePath = "result.json";
    CppDevelopTemplate::LogSettings expect {
        "AppName", "logs/DILib.log", 1048576 * 5, 3
    };
    expect.serializeJson(jsonFilePath);

    CppDevelopTemplate::LogSettings actual;
    actual.deserializeJson(jsonFilePath);

    ASSERT_EQ(expect.loggerName, actual.loggerName);
    ASSERT_EQ(expect.logOutputPath, actual.logOutputPath);
    ASSERT_EQ(expect.maxFileSize, actual.maxFileSize);
    ASSERT_EQ(expect.maxFiles, actual.maxFiles);
}
