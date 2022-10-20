#pragma once

#include <QtWidgets/QWidget>
#include "ui_SocialPlatform.h"
#include "Observer.h"
#include "Service.h"

class SocialPlatform : public QWidget, public Observer
{
    Q_OBJECT

public:
    SocialPlatform(Service& service, User user, QWidget* parent = nullptr);
    ~SocialPlatform();
    void update() override;
    void populateFeed();
    void populatePosts();
    void populateSubscriptions();
    void filtering();

    void subscribe();

    void connectSlots();

    void addPost();

    void updatePost();

private:
    Ui::SocialPlatformClass ui;
    Service& service;
    User user;
};
