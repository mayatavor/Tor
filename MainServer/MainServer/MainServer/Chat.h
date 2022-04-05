#pragma once
class Chat
{
public:
	Chat();
	Chat(int firstUserId, int secondUserId);
	~Chat() = default;

	//getters
	int getChatId() const;
	int getFirstuserId() const;
	int getSecondUserId() const;

	//setters
	void setChatId(int chatId);
	void setFirstuser(int id);
	void setSecondUser(int id);

private:
	int _chatId;
	int _firstUser;
	int _secondUser;
};

