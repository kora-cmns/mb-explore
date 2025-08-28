#include <gtest/gtest.h>
#include <string>
#include "url_utils.h"

class UrlConstructionTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(UrlConstructionTest, SimpleArtistTitle) {
    std::string result = BuildSearchUrl("Beatles", "Hey Jude");
    std::string expected = "https://musicbrainz.org/ws/2/recording?query=artist:%22Beatles%22%20AND%20recording:%22Hey%20Jude%22&fmt=json&limit=10";
    EXPECT_EQ(result, expected);
}

TEST_F(UrlConstructionTest, SpecialCharacters) {
    std::string result = BuildSearchUrl("Guns N' Roses", "Sweet Child O' Mine");
    std::string expected = "https://musicbrainz.org/ws/2/recording?query=artist:%22Guns%20N%27%20Roses%22%20AND%20recording:%22Sweet%20Child%20O%27%20Mine%22&fmt=json&limit=10";
    EXPECT_EQ(result, expected);
}

TEST_F(UrlConstructionTest, CustomLimit) {
    std::string result = BuildSearchUrl("Twenty One Pilots", "Heathens", 25);
    std::string expected = "https://musicbrainz.org/ws/2/recording?query=artist:%22Twenty%20One%20Pilots%22%20AND%20recording:%22Heathens%22&fmt=json&limit=25";
    EXPECT_EQ(result, expected);
}

TEST_F(UrlConstructionTest, UrlEncodeBasic) {
    EXPECT_EQ(UrlEncode("Hello World"), "Hello%20World");
    EXPECT_EQ(UrlEncode("AC/DC"), "AC%2FDC");
    EXPECT_EQ(UrlEncode("Don't Stop"), "Don%27t%20Stop");
    EXPECT_EQ(UrlEncode("100% Pure"), "100%25%20Pure");
    EXPECT_EQ(UrlEncode("A&B"), "A%26B");
}

TEST_F(UrlConstructionTest, EdgeCases) {
    // Empty strings
    std::string result1 = BuildSearchUrl("", "Title");
    std::string expected1 = "https://musicbrainz.org/ws/2/recording?query=artist:%22%22%20AND%20recording:%22Title%22&fmt=json&limit=10";
    EXPECT_EQ(result1, expected1);
    
    // Special characters that need encoding
    std::string result2 = BuildSearchUrl("M&M's", "Song#1");
    std::string expected2 = "https://musicbrainz.org/ws/2/recording?query=artist:%22M%26M%27s%22%20AND%20recording:%22Song%231%22&fmt=json&limit=10";
    EXPECT_EQ(result2, expected2);
}