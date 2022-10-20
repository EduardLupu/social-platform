#pragma once

#include "Domain.h"

class Repository {
private:
	vector<User> users;
	vector<Topic> topics;
	vector<Post> posts;
	string file_users;
	string file_topics;
	string file_posts;
public:
	Repository(const std::string& file_users, const std::string& file_topics, const std::string& file_posts) {
		this->file_users = file_users;
		this->file_topics = file_topics;
		this->file_posts = file_posts;
		load_users();
		load_topics();
		load_posts();
	}
	~Repository() {
		save_users();
		save_topics();
		save_posts();
	}
	vector<User> get_users() {
		return this->users;
	}
	vector<Topic> get_topics() {
		return this->topics;
	}
	vector<Post> get_posts() {
		return this->posts;
	}
	void load_users() {
		std::ifstream f{ this->file_users };
		if (!f.is_open())
			return;

		User p;
		while (f >> p)
		{
			this->users.push_back(p);
		}
		f.close();
	}
	void load_topics() {
		std::ifstream f{ this->file_topics };
		if (!f.is_open())
			return;

		Topic p;
		while (f >> p)
		{
			this->topics.push_back(p);
		}
		f.close();
	}
	void load_posts() {
		std::ifstream f{ this->file_posts };
		if (!f.is_open())
			return;
	
		Post p;
		while (f >> p)
		{
			this->posts.push_back(p);
		}
		f.close();
	}


	void save_users() {
		std::ofstream f{ this->file_users };
		if (!f.is_open())
			return;

		for (auto g : this->users)
			f << g;
		f.close();
	}

	void save_topics() {
		std::ofstream f{ this->file_topics };
		if (!f.is_open())
			return;

		for (auto g : this->topics)
			f << g;
		f.close();
	}

	void save_posts() {
		std::ofstream f{ this->file_posts };
		if (!f.is_open())
			return;

		for (auto g : this->posts)
			f << g;
		f.close();
	}
	void addToTopicTheUser(string t, string u)
	{
		for (auto topic : this->get_topics())
		{
			if (topic.getTopic().find(t) != std::string::npos)
				topic.setTopicUsers(topic.getTopicUsers() + "_" + u);
		}
	}
	void addPost(Post t)
	{
		this->posts.push_back(t);
	}
	void updatePost(Post rr, Post p)
	{
		for (auto& post : this->posts)
		{
			if (post.getId() == rr.getId())
			{
				post = p;
				return;
			}
		}
	}
};