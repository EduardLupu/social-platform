#include "SocialPlatform.h"
#include <qmessagebox.h>

SocialPlatform::SocialPlatform(Service& service, User user, QWidget* parent)
    : service{ service }, user{ user }, QWidget(parent)
{
    ui.setupUi(this);
    this->service.addObserver(this);
    this->setWindowTitle(QString::fromStdString(user.getName()));
    this->update();
    this->ui.label_2->setText(QString::fromStdString(user.getName() + "'s posts"));
    this->connectSlots();
}

SocialPlatform::~SocialPlatform()
{
    this->service.removeObserver(this);
}

void SocialPlatform::populateFeed() {
    vector<Post> posts = service.get_posts();
    this->ui.feed->clear();
    for (auto& element : posts)
    {
        string post = element.getId() + " | " + element.getText() + " | " + element.getDate() + " | " + element.getTime() + " | " + element.getUser() + '\n';
        this->ui.feed->addItem(QString::fromStdString(post));
    }
}

void SocialPlatform::populatePosts() {
    vector<Post> posts = service.get_posts();
    std::sort(posts.begin(), posts.end(), [](Post a, Post b) {return a.getDate() > b.getDate(); });
    this->ui.posts->clear();
    for (auto& element : posts)
    {
        if (element.getUser() == user.getName())
        {
            string post = element.getId() + " | " + element.getText() + " | " + element.getDate() + " | " + element.getTime() + '\n';
            this->ui.posts->addItem(QString::fromStdString(post));
        }
    }
}

void SocialPlatform::populateSubscriptions()
{
    vector<Topic> topics = service.get_topics();
    this->ui.subscriptions->clear();
    for (auto element : topics)
    {
        if (element.getTopicUsers().find(user.getName()) != std::string::npos) {
            this->ui.subscriptions->addItem(QString::fromStdString(element.getTopic()));
        }
    }
}

void SocialPlatform::filtering() {

    string filtered = this->ui.filterTopics->text().toStdString();
    vector<Topic>topics = this->service.get_topics();
    this->ui.topicsList->clear();
    for (auto element : topics) {
        string TopicName = element.getTopic();
        if (TopicName.find(filtered) != std::string::npos) {
            this->ui.topicsList->addItem(QString::fromStdString(TopicName));
        }
    }
}

void SocialPlatform::subscribe() {
    string selectedvalue = this->ui.topicsList->currentItem()->text().toStdString();
    this->service.addToTopicTheUser(selectedvalue, user.getName());
    this->ui.subscriptions->addItem(QString::fromStdString(selectedvalue));
}

void SocialPlatform::connectSlots() {
    QObject::connect(this->ui.filterTopics, &QLineEdit::textChanged, this, &SocialPlatform::filtering);
    QObject::connect(this->ui.subscribe, &QPushButton::clicked, this, &SocialPlatform::subscribe);
    QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &SocialPlatform::addPost);
    QObject::connect(this->ui.update, &QPushButton::clicked, this, &SocialPlatform::updatePost);
}

void SocialPlatform::addPost() {
    string id = this->ui.id->text().toStdString();
    string text = this->ui.text->text().toStdString();
    string date = this->ui.date->text().toStdString();
    string time = this->ui.time->text().toStdString();
    if (text.size() < 3)
    {
        QMessageBox::critical(this, "Error", "Too small text!!");
        return;
    }
    this->service.addPost(id, text, date, time, user.getName());
}

void SocialPlatform::updatePost() {
    string selectedvalue = this->ui.feed->currentItem()->text().toStdString();
    string id = this->ui.id->text().toStdString();
    string text = this->ui.text->text().toStdString();
    string date = this->ui.date->text().toStdString();
    string time = this->ui.time->text().toStdString();
    if (text.size() < 3)
    {
        QMessageBox::critical(this, "Error", "Too small text!!");
        return;
    }
    this->service.updatePost(selectedvalue, id, text, date, time, user.getName());
    this->update();
}

void SocialPlatform::update()
{
    this->populateFeed();
    this->populatePosts();
    this->populateSubscriptions();
}
