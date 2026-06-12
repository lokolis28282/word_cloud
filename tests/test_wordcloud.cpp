#include <gtest/gtest.h>

#include <QByteArray>
#include <QGuiApplication>
#include <cstdio>
#include <string>
#include <vector>

#include "wordcloud.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM")) {
        qputenv("QT_QPA_PLATFORM", QByteArray("offscreen"));
    }

    QGuiApplication app(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(t1, a1) {
    EXPECT_EQ(aa("HELLO"), "hello");
    EXPECT_EQ(aa(" a b "), "ab");
}

TEST(t1, a2) {
    vector<string> x;
    x.push_back("cat");
    x.push_back("Cat");
    x.push_back("dog");

    vector<ww> r = bb(x);

    ASSERT_EQ((int)r.size(), 2);
    EXPECT_EQ(r[0].s, "cat");
    EXPECT_EQ(r[0].n, 2);
}

TEST(t1, a3) {
    vector<string> x;
    x.push_back("one");
    x.push_back("one");
    x.push_back("two");

    string f = "test_bad_cloud.jpg";
    EXPECT_TRUE(dd(x, f));
    remove(f.c_str());
}
