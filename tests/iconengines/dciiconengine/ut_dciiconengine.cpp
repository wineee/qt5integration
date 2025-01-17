// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include <DDciIcon>
#include <DGuiApplicationHelper>
#include <QIcon>
#include <QPainter>

#include "dciiconengine.h"

DGUI_USE_NAMESPACE

class ut_DDciIconEngine : public testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    DDciIconEngine *mIconEngine = nullptr;
};

void ut_DDciIconEngine::SetUp()
{
    mIconEngine = new DDciIconEngine("test_selected_indicator");
}

void ut_DDciIconEngine::TearDown()
{
    delete mIconEngine;
}

TEST_F(ut_DDciIconEngine, actualSize)
{
    QSize size(32, 32);

    QSize iconSize = mIconEngine->actualSize(size, QIcon::Normal, QIcon::On);
    ASSERT_FALSE(iconSize.isEmpty());
    ASSERT_EQ(iconSize, QSize(16, 16)); // 该图标只有16这个大小。。
}

TEST_F(ut_DDciIconEngine, pixmap)
{
    QPixmap iconenginePixmap = mIconEngine->pixmap(QSize(32, 32), QIcon::Normal, QIcon::On);

    ASSERT_FALSE(iconenginePixmap.isNull());
}

TEST_F(ut_DDciIconEngine, paint)
{
    QImage iconImage(QSize(32, 32), QImage::Format_ARGB32);
    QPainter iconPainter(&iconImage);

    mIconEngine->paint(&iconPainter, QRect({0, 0}, iconImage.size()), QIcon::Normal, QIcon::On);
    ASSERT_FALSE(iconImage.isNull());
}

TEST_F(ut_DDciIconEngine, key)
{
    ASSERT_EQ(mIconEngine->key(), "DDciIconEngine");
    ASSERT_EQ(QIcon::fromTheme("test_selected_indicator").data_ptr()->engine->key(), "DDciIconEngine");
}

TEST_F(ut_DDciIconEngine, clone)
{
    auto clone = mIconEngine->clone();
    ASSERT_FALSE(!clone);
    delete clone;
}

TEST_F(ut_DDciIconEngine, read)
{
    QByteArray data;
    QString iconName = "test_selected_indicator";
    QDataStream out(&data, QIODevice::WriteOnly);
    out << iconName;

    QDataStream in(&data, QIODevice::ReadOnly);
    mIconEngine->read(in);

    ASSERT_EQ(mIconEngine->iconName(), iconName);
}

TEST_F(ut_DDciIconEngine, write)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    mIconEngine->write(out);
    QString iconName;

    QDataStream in(&data, QIODevice::ReadOnly);
    in >> iconName ;

    ASSERT_EQ(mIconEngine->iconName(), iconName);
}

TEST_F(ut_DDciIconEngine, iconName)
{
    ASSERT_EQ(mIconEngine->iconName(), "test_selected_indicator");
}
