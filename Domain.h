#pragma once

using namespace std;

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

class User {
private:
	string name;
public:
	User() {}
	User(string name) : name(name) {}
	string getName() { return this->name; }
	friend std::ostream& operator<<(std::ostream& os, User& p)
	{
		os << p.name << '\n';
		return os;
	}
	friend std::istream& operator>>(std::istream& os, User& p)
	{
		os >> p.name;
		return os;
	}
};

class Topic {
private:
	string topic;
	string users;
public:
	Topic(string topic, string users) : topic(topic), users(users) {}
	Topic() {}
	string getTopic() { return this->topic; }
	string getTopicUsers() { return this->users; }
	friend std::ostream& operator<<(std::ostream& os, Topic& p)
	{
		os << p.topic << " " << p.users;
		os << '\n';
		return os;
	}
	friend std::istream& operator>>(std::istream& os, Topic& p)
	{
		os >> p.topic >> p.users;
		return os;
	}
	void setTopicUsers(string users) {
		this->users = users;
	}
};

class Post {
private:
	string id;
	string text;
	string date;
	string time;
	string user;
public:
	Post(string id, string text, string date, string time, string user) : id(id), text(text), date(date), time(time), user(user) {}
	Post() {}
	string getId() { return this->id; }
	string getText() { return this->text; }
	string getDate() { return this->date; }
	string getTime() { return this->time; }
	string getUser() { return this->user; }
	friend std::ostream& operator<<(std::ostream& os, Post & p)
	{
		os << p.id << " " << p.text << " " << p.date << " " << p.time << " " << p.user << '\n';
		return os;
	}
	friend std::istream& operator>>(std::istream& os, Post& p)
	{
		os >> p.id >> p.text >> p.date >> p.time >> p.user;
		return os;
	}
};