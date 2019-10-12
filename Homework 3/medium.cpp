#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
using namespace std;

enum CallType {
	VOICE, TEXT
};

class Medium
{
public:
	Medium(string medium);
	virtual ~Medium();
	virtual string connect() const = 0;
	virtual string id() const;
	virtual string transmit(string msg) const = 0;

private:
	string ID;
};

Medium::Medium(string medium) : ID(medium)
{}

Medium::~Medium()
{}

string Medium::id() const
{
	return "" + ID;
}

class TwitterAccount : public Medium
{
public:
	TwitterAccount(string account);
	virtual ~TwitterAccount();
	virtual string connect() const;
	virtual string transmit(string msg) const;
};

TwitterAccount::TwitterAccount(string account) : Medium(account)
{
	
}

TwitterAccount::~TwitterAccount()
{
	cout << "Destroying the Twitter Account " << id() << endl;
}

string TwitterAccount::connect() const
{
	return "Tweet";
}

string TwitterAccount::transmit(string msg) const
{
	return "sending text: " + msg;
}


class Phone : public Medium
{
public:
	Phone(string phone, CallType text);
	virtual ~Phone();
	virtual string connect() const;
	virtual string transmit(string msg) const;

private:
	CallType CT;
};

Phone::Phone(string phone, CallType text) : Medium(phone), CT(text)
{}

Phone::~Phone()
{
	cout << "Destroying the phone " << id() << endl;
}

string Phone::connect() const
{
	return "Call";
}

string Phone::transmit(string msg) const
{
	if (CT == VOICE)
		return "sending voice: " + msg;
	else
		return "sending text: " + msg;
}


class EmailAccount : public Medium
{
public:
	EmailAccount(string email);
	virtual ~EmailAccount();
	virtual string connect() const;
	virtual string transmit(string msg) const;

};

EmailAccount::EmailAccount(string email) : Medium(email)
{}

EmailAccount::~EmailAccount()
{
	cout << "Destroying the email account " << id() << endl;
}

string EmailAccount::connect() const
{
	return "Email";
}

string EmailAccount::transmit(string msg) const
{
	return "sending text: " + msg;
}

void send(const Medium* m, string msg)
{
	cout << m->connect() << " using id " << m->id()
		<< ", sending " << m->transmit(msg) << endl;
}

int main()
{
	Medium* media[4];
	media[0] = new TwitterAccount("UCLABruinAlert");
	// Phone users may prefer messages to be left as voice or text.
	media[1] = new Phone("(310) 825 3894", VOICE);
	media[2] = new Phone("(213) 389 9060", TEXT);
	media[3] = new EmailAccount("jbroon@ucla.edu");

	cout << "Send the message." << endl;
	for (int k = 0; k < 4; k++)
		send(media[k], "Major power outage in West L.A.");

	// Clean up the media before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete media[k];

	cout << endl << "Number of memory leaks are: " << _CrtDumpMemoryLeaks() << endl;
}

/*
Output produced:

Send the message.
Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
Call using id (213) 389 9060, sending text: Major power outage in West L.A.
Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
Cleaning up.
Destroying the Twitter account UCLABruinAlert.
Destroying the phone (310) 825 3894.
Destroying the phone (213) 389 9060.
Destroying the email account jbroon@ucla.edu.

*/