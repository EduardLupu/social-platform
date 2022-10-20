#pragma once

#include "Repository.h"
#include "Observer.h"

class Service : public Observable {
private:
	Repository& r;
public:
	Service(Repository& r) : r(r) {}
	vector<User> get_users() { return this->r.get_users(); }
	vector<Topic> get_topics() { return this->r.get_topics(); }
	vector<Post> get_posts() { return this->r.get_posts(); }
	void addToTopicTheUser(string t, string u) {
		this->r.addToTopicTheUser(t, u);
		this->notify();
	}
	void addPost(string id, string text, string date, string time, string user) {
		this->r.addPost(Post(id, text, date, time, user));
		this->notify();
	}
	void updatePost(string selectedvalue, string id, string text, string date, string time, string user) {
		for (auto e : this->get_posts())
		{
			if (selectedvalue.find(e.getId()) != std::string::npos)
			{
				this->r.updatePost(e, Post(id, text, date, time, user));
			}
		}
		this->notify();
	}
};