#include <stdio.h>
#include <tgbot/tgbot.h>
#include <unordered_map>
#pragma execution_character_set("utf-8")
using namespace TgBot;
using namespace std;

bool inRunning = true;
const int64_t adminid = 869613280; // id администратора

//Хранение данных которые вводит пользователь

enum class State {
	START,
	FIRST_NAME,
	LAST_NAME,
	SUPPORT,
	CONSULTATION
};

struct UserInfo
{
	string firstname;
	string lastname;
	string time;
	string day;
};

unordered_map<int64_t, State> userStates;
unordered_map<int64_t, UserInfo> userInfo;
unordered_map<int64_t, bool> isHandlingState;

//Клавиатура с кнопками с днями неделями

InlineKeyboardMarkup::Ptr keybortglav() {
	InlineKeyboardMarkup::Ptr keybort(new InlineKeyboardMarkup);
	InlineKeyboardButton::Ptr btn1(new InlineKeyboardButton);
	InlineKeyboardButton::Ptr btn2(new InlineKeyboardButton);
	InlineKeyboardButton::Ptr btn3(new InlineKeyboardButton);
	InlineKeyboardButton::Ptr btn4(new InlineKeyboardButton);
	InlineKeyboardButton::Ptr btn5(new InlineKeyboardButton);
	btn1->text = "Понедельник";
	btn1->callbackData = "monday";
	keybort->inlineKeyboard.push_back({ btn1 });
	btn2->text = "Вторник";
	btn2->callbackData = "tuesday";
	keybort->inlineKeyboard.push_back({ btn2 });
	btn3->text = "Среда";
	btn3->callbackData = "wednesday";
	keybort->inlineKeyboard.push_back({ btn3 });
	btn4->text = "Четверг";
	btn4->callbackData = "thursday";
	keybort->inlineKeyboard.push_back({ btn4 });
	btn5->text = "Пятница";
	btn5->callbackData = "friday";
	keybort->inlineKeyboard.push_back({ btn5 });

	return keybort;
}


//Клавиатура с кнопками отмены и подтверждения


InlineKeyboardMarkup::Ptr cancelkeyboard() {
	InlineKeyboardMarkup::Ptr keybort(new InlineKeyboardMarkup);
	InlineKeyboardButton::Ptr btn1(new InlineKeyboardButton);
	InlineKeyboardButton::Ptr btn2(new InlineKeyboardButton);
	btn1->text = "Потдвердить прием";
	btn1->callbackData = "confirm";
	keybort->inlineKeyboard.push_back({ btn1 });
	btn2->text = "Отменить прием";
	btn2->callbackData = "cancelall";
	keybort->inlineKeyboard.push_back({ btn2 });
	return keybort;
}


// сохранение данных файл

void saveUserDataToFile(const UserInfo& userInfo) {
	ofstream outFile("userdata.txt", ios::app);
	if (outFile.is_open()) {
		outFile << "First Name: " << userInfo.firstname << "\n";
		outFile << "Last Name: " << userInfo.lastname << "\n";
		outFile << "Time: " << userInfo.time << "\n";
		outFile << "Week Day: " << userInfo.day << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR!" << endl;
	}
}


string messageText; // отправляемое сообщение

//обработка состояний в диалоге (STATE)
void handleState(const Bot& bot, int64_t userId, Message::Ptr message) {
	switch (userStates[userId]) {
	case State::START:
		bot.getApi().sendMessage(userId, "Введите имя:");
		userStates[userId] = State::FIRST_NAME;
		isHandlingState[userId] = true;
		break;
	case State::FIRST_NAME:
		userInfo[userId].firstname = message->text;
		bot.getApi().sendMessage(userId, "Введите фамилию:");
		userStates[userId] = State::LAST_NAME;
		break;
	case State::LAST_NAME:
		userInfo[userId].lastname = message->text;
		saveUserDataToFile(userInfo[userId]);
		bot.getApi().sendMessage(userId, "Ваши данные сохранены.");
		userStates[userId] = State::START;
		isHandlingState[userId] = false;
		break;
	case State::SUPPORT:
		bot.getApi().sendMessage(adminid, "Проблема от пользователя " + userInfo[userId].firstname + ", " + userInfo[userId].lastname + ": " + message->text);
		bot.getApi().sendMessage(userId, "Ваше сообщение отправлено в поддержку.");
		userStates[userId] = State::START;
		isHandlingState[userId] = false;
		break;
	case State::CONSULTATION:
		bot.getApi().sendMessage(adminid, "Проблема от пользователя " + userInfo[userId].firstname + ", " + userInfo[userId].lastname + ": " + message->text);
		bot.getApi().sendMessage(userId, "Ваше сообщение отправлено медику.");
		userStates[userId] = State::START;
		isHandlingState[userId] = false;
		break;
	}
}

int main() {


	bool mteno = false;
	bool mtenh = false;
	bool meleveno = false;
	bool melevenh = false;
	bool mtwelveo = false;
	bool mtwelveh = false;
	bool mthirtyo = false;

	bool tteno = false;
	bool ttenh = false;
	bool televeno = false;
	bool televenh = false;
	bool ttwelveo = false;
	bool ttwelveh = false;
	bool tthirtyo = false;

	bool wteno = false;
	bool wtenh = false;
	bool weleveno = false;
	bool welevenh = false;
	bool wtwelveo = false;
	bool wtwelveh = false;
	bool wthirtyo = false;

	bool thteno = false;
	bool thtenh = false;
	bool theleveno = false;
	bool thelevenh = false;
	bool thtwelveo = false;
	bool thtwelveh = false;
	bool ththirtyo = false;

	bool fteno = false;
	bool ftenh = false;
	bool feleveno = false;
	bool felevenh = false;
	bool ftwelveo = false;
	bool ftwelveh = false;
	bool fthirtyo = false;

	string cleanTime = " ";
	int i = 1;

	Bot bot("6836708566:AAFWzOaS9MCneoH6WJN9BcOiE-ma8UBaE38"); // Токен телеграм бота
	bot.getEvents().onCommand("start", [&bot](Message::Ptr message) { // Обработка команды start
		InlineKeyboardMarkup::Ptr keybort = keybortglav();
		bot.getApi().sendMessage(message->chat->id, "Здравствуйте, пожалуйста не забудьте написать ваше Ф.И перед выбором дня \nВыберите день", false, 0, keybort);
		int64_t userId = message->from->id;
		userStates[userId] = State::START;
		handleState(bot, userId, message);
		});
	bot.getEvents().onCommand("поддержка", [&bot](TgBot::Message::Ptr message) {
		int64_t userId = message->from->id;
		bot.getApi().sendMessage(userId, "Пожалуйста оставьте свой номер телефона или имя пользователя в телеграме для дальнейшей связи \nПожалуйста, опишите вашу проблему:");
		userStates[userId] = State::SUPPORT;
		isHandlingState[userId] = true;
		});

	bot.getEvents().onCommand("консультация", [&bot](TgBot::Message::Ptr message) {
		int64_t userId = message->from->id;
		bot.getApi().sendMessage(userId, "Пожалуйста оставьте свой номер телефона или имя пользователя в телеграме для дальнейшей связи \nПожалуйста, опишите вашу проблему:");
		userStates[userId] = State::CONSULTATION;
		isHandlingState[userId] = true;
		});
	int64_t lastUpdateId = 0;
	bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
		int64_t userId = message->from->id;
		if (isHandlingState.find(userId) != isHandlingState.end() && isHandlingState[userId]) {
			handleState(bot, userId, message);
		}
		});
	// Получаем последнее обновление перед запуском основного цикла
	auto updates = bot.getApi().getUpdates();
	if (!updates.empty()) {
		lastUpdateId = updates.back()->updateId;
	}




	bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
		InlineKeyboardMarkup::Ptr kb(new InlineKeyboardMarkup);
		InlineKeyboardButton::Ptr btn1(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn2(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn3(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn4(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn5(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn6(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn7(new InlineKeyboardButton);
		InlineKeyboardButton::Ptr btn8(new InlineKeyboardButton);
		if (query->data == "monday")
		{
			int64_t userId = query->from->id;
			string day = "Понедельник";
			userInfo[userId].day = day;
			saveUserDataToFile(userInfo[userId]);
			btn1->text = "10:00";
			btn1->callbackData = "mnineo";
			kb->inlineKeyboard.push_back({ btn1 });
			btn2->text = "10:30";
			btn2->callbackData = "mninehalf";
			kb->inlineKeyboard.push_back({ btn2 });
			btn3->text = "11:00";
			btn3->callbackData = "mteno";
			kb->inlineKeyboard.push_back({ btn3 });
			btn4->text = "11:30";
			btn4->callbackData = "mtenhalf";
			kb->inlineKeyboard.push_back({ btn4 });
			btn5->text = "12:00";
			btn5->callbackData = "meleveno";
			kb->inlineKeyboard.push_back({ btn5 });
			btn6->text = "12:30";
			btn6->callbackData = "melevenhalf";
			kb->inlineKeyboard.push_back({ btn6 });
			btn7->text = "13:00";
			btn7->callbackData = "mtwelfo";
			kb->inlineKeyboard.push_back({ btn7 });
			btn8->text = "Назад 🔙";
			btn8->callbackData = "BACK";
			kb->inlineKeyboard.push_back({ btn8 });
		}

		if (query->data == "tuesday") {
			int64_t userId = query->from->id;
			string day = "Вторник";
			userInfo[userId].day = day;
			saveUserDataToFile(userInfo[userId]);
			btn1->text = "10:00";
			btn1->callbackData = "tnineo";
			kb->inlineKeyboard.push_back({ btn1 });
			btn2->text = "10:30";
			btn2->callbackData = "tninehalf";
			kb->inlineKeyboard.push_back({ btn2 });
			btn3->text = "11:00";
			btn3->callbackData = "tteno";
			kb->inlineKeyboard.push_back({ btn3 });
			btn4->text = "11:30";
			btn4->callbackData = "ttenhalf";
			kb->inlineKeyboard.push_back({ btn4 });
			btn5->text = "12:00";
			btn5->callbackData = "televeno";
			kb->inlineKeyboard.push_back({ btn5 });
			btn6->text = "12:30";
			btn6->callbackData = "televenhalf";
			kb->inlineKeyboard.push_back({ btn6 });
			btn7->text = "13:00";
			btn7->callbackData = "ttwelfo";
			kb->inlineKeyboard.push_back({ btn7 });
			btn8->text = "Назад 🔙";
			btn8->callbackData = "BACK";
			kb->inlineKeyboard.push_back({ btn8 });
		}

		if (query->data == "wednesday") {
			int64_t userId = query->from->id;
			string day = "Среда";
			userInfo[userId].day = day;
			saveUserDataToFile(userInfo[userId]);
			btn1->text = "10:00";
			btn1->callbackData = "wnineo";
			kb->inlineKeyboard.push_back({ btn1 });
			btn2->text = "10:30";
			btn2->callbackData = "wninehalf";
			kb->inlineKeyboard.push_back({ btn2 });
			btn3->text = "11:00";
			btn3->callbackData = "wteno";
			kb->inlineKeyboard.push_back({ btn3 });
			btn4->text = "11:30";
			btn4->callbackData = "wtenhalf";
			kb->inlineKeyboard.push_back({ btn4 });
			btn5->text = "12:00";
			btn5->callbackData = "weleveno";
			kb->inlineKeyboard.push_back({ btn5 });
			btn6->text = "12:30";
			btn6->callbackData = "welevenhalf";
			kb->inlineKeyboard.push_back({ btn6 });
			btn7->text = "13:00";
			btn7->callbackData = "wtwelfo";
			kb->inlineKeyboard.push_back({ btn7 });
			btn8->text = "Назад 🔙";
			btn8->callbackData = "BACK";
			kb->inlineKeyboard.push_back({ btn8 });
		}

		if (query->data == "thursday") {
			int64_t userId = query->from->id;
			string day = "Четверг";
			userInfo[userId].day = day;
			saveUserDataToFile(userInfo[userId]);
			btn1->text = "10:00";
			btn1->callbackData = "thnineo";
			kb->inlineKeyboard.push_back({ btn1 });
			btn2->text = "10:30";
			btn2->callbackData = "thninehalf";
			kb->inlineKeyboard.push_back({ btn2 });
			btn3->text = "11:00";
			btn3->callbackData = "thteno";
			kb->inlineKeyboard.push_back({ btn3 });
			btn4->text = "11:30";
			btn4->callbackData = "thtenhalf";
			kb->inlineKeyboard.push_back({ btn4 });
			btn5->text = "12:00";
			btn5->callbackData = "theleveno";
			kb->inlineKeyboard.push_back({ btn5 });
			btn6->text = "12:30";
			btn6->callbackData = "thelevenhalf";
			kb->inlineKeyboard.push_back({ btn6 });
			btn7->text = "13:00";
			btn7->callbackData = "thtwelfo";
			kb->inlineKeyboard.push_back({ btn7 });;
			btn8->text = "Назад 🔙";
			btn8->callbackData = "BACK";
			kb->inlineKeyboard.push_back({ btn8 });
		}

		if (query->data == "friday") {
			int64_t userId = query->from->id;
			string day = "Пятница";
			userInfo[userId].day = day;
			saveUserDataToFile(userInfo[userId]);
			btn1->text = "10:00";
			btn1->callbackData = "fnineo";
			kb->inlineKeyboard.push_back({ btn1 });
			btn2->text = "10:30";
			btn2->callbackData = "fninehalf";
			kb->inlineKeyboard.push_back({ btn2 });
			btn3->text = "11:00";
			btn3->callbackData = "fteno";
			kb->inlineKeyboard.push_back({ btn3 });
			btn4->text = "11:30";
			btn4->callbackData = "ftenhalf";
			kb->inlineKeyboard.push_back({ btn4 });
			btn5->text = "12:00";
			btn5->callbackData = "feleveno";
			kb->inlineKeyboard.push_back({ btn5 });
			btn6->text = "12:30";
			btn6->callbackData = "felevenhalf";
			kb->inlineKeyboard.push_back({ btn6 });
			btn7->text = "13:00";
			btn7->callbackData = "ftwelfo";
			kb->inlineKeyboard.push_back({ btn7 });
			btn8->text = "Назад 🔙";
			btn8->callbackData = "BACK";
			kb->inlineKeyboard.push_back({ btn8 });
		}
		bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, kb);
		});

	bot.getEvents().onCallbackQuery([&bot, &cleanTime, &mteno, &mtenh, &meleveno, &melevenh, &mtwelveo, &mtwelveh, &mthirtyo, &tteno, &ttenh, &televeno, &televenh, &ttwelveo, &ttwelveh, &tthirtyo, &wteno, &wtenh, &weleveno, &welevenh, &wtwelveo, &wtwelveh, &wthirtyo, &thteno, &thtenh, &theleveno, &thelevenh, &thtwelveo, &thtwelveh, &ththirtyo, &fteno, &ftenh, &feleveno, &felevenh, &ftwelveo, &ftwelveh, &fthirtyo](CallbackQuery::Ptr query) {
		//Понедельник
		int64_t userId = query->from->id;
		if (query->data == "mnineo")
		{
			if (!mteno) {
				mteno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "mninehalf")
		{
			if (!mtenh) {
				mtenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "mteno")
		{
			if (!meleveno) {
				meleveno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "mtenhalf")
		{
			if (!melevenh) {
				melevenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "meleveno")
		{
			if (!mtwelveo) {
				mtwelveo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "melevenhalf")
		{
			if (!mtwelveh) {
				mtwelveh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "mtwelfo")
		{
			if (!mthirtyo) {
				mthirtyo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "13:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		//Вторник

		if (query->data == "tnineo")
		{
			if (!tteno) {
				tteno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "tninehalf")
		{
			if (!ttenh) {
				ttenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "tteno")
		{
			if (!televeno) {
				televeno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "ttenhalf")
		{
			if (!televenh) {
				televenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "televeno")
		{
			if (!ttwelveo) {
				ttwelveo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "televenhal")
		{
			if (!ttwelveh) {
				ttwelveh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "ttwelfo")
		{
			if (!tthirtyo) {
				tthirtyo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "13:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		//Среда
		if (query->data == "wnineo")
		{
			if (!wteno) {
				wteno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "wninehalf")
		{
			if (!wtenh) {
				wtenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "wteno")
		{
			if (!weleveno) {
				weleveno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "wtenhalf")
		{
			if (!welevenh) {
				welevenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "weleveno")
		{
			if (!wtwelveo) {
				wtwelveo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "welevenhalf")
		{
			if (!wtwelveh) {
				wtwelveh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "wtwelfo")
		{
			if (!wthirtyo) {
				wthirtyo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "13:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		//Четверг
		if (query->data == "thnineo")
		{
			if (!thteno) {
				thteno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "thninehalf")
		{
			if (!thtenh) {
				thtenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "thteno")
		{
			if (!theleveno) {
				theleveno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "thtenhalf")
		{
			if (!thelevenh) {
				thelevenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "theleveno")
		{
			if (!thtwelveo) {
				thtwelveo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "thelevenhalf")
		{
			if (!thtwelveh) {
				thtwelveh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");

				cleanTime = "12:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "thtwelfo")
		{
			if (!ththirtyo) {
				ththirtyo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "13:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		//Пятница
		if (query->data == "fnineo")
		{
			if (!fteno) {
				fteno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "fninehalf")
		{
			if (!ftenh) {
				ftenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "10:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "fteno")
		{
			if (!feleveno) {
				feleveno = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "ftenhalf")
		{
			if (!felevenh) {
				felevenh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "11:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "feleveno")
		{
			if (!ftwelveo) {
				ftwelveo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "felevenhalf")
		{
			if (!ftwelveh) {
				ftwelveh = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "12:30";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		if (query->data == "ftwelfo")
		{
			if (!fthirtyo) {
				fthirtyo = true;
				bot.getApi().sendMessage(query->message->chat->id, "Вы заняли слот.");
				cleanTime = "13:00";
				userInfo[userId].time = cleanTime;
				saveUserDataToFile(userInfo[userId]);
				InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
				bot.getApi().sendMessage(query->message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, "Слот уже занят.");
			}
		}
		});

	bot.getEvents().onCallbackQuery([&bot, &cleanTime, &mteno, &mtenh, &meleveno, &melevenh, &mtwelveo, &mtwelveh, &mthirtyo, &tteno, &ttenh, &televeno, &televenh, &ttwelveo, &ttwelveh, &tthirtyo, &wteno, &wtenh, &weleveno, &welevenh, &wtwelveo, &wtwelveh, &wthirtyo, &thteno, &thtenh, &theleveno, &thelevenh, &thtwelveo, &thtwelveh, &ththirtyo, &fteno, &ftenh, &feleveno, &felevenh, &ftwelveo, &ftwelveh, &fthirtyo](CallbackQuery::Ptr query) {
		int64_t userId = query->from->id;
		if (query->data == "cancelall") {
			UserInfo user = userInfo[userId];

			string weekday = user.day;
			string timee = user.time;

			if ((weekday == "Понедельник") && (timee == "10:00"))
			{
				mteno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "10:30"))
			{
				mtenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "11:00"))
			{
				meleveno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "11:30"))
			{
				melevenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "12:00"))
			{
				mtwelveo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "12:30"))
			{
				mtwelveh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Понедельник") && (timee == "13:00"))
			{
				mthirtyo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}

			if ((weekday == "Вторник") && (timee == "10:00"))
			{
				tteno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "10:30"))
			{
				ttenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "11:00"))
			{
				televeno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "11:30"))
			{
				televenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "12:00"))
			{
				ttwelveo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "12:30"))
			{
				ttwelveh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Вторник") && (timee == "13:00"))
			{
				tthirtyo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}

			if ((weekday == "Среда") && (timee == "10:00"))
			{
				wteno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "10:30"))
			{
				wtenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "11:00"))
			{
				weleveno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "11:30"))
			{
				welevenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "12:00"))
			{
				wtwelveo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "12:30"))
			{
				wtwelveh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Среда") && (timee == "13:00"))
			{
				wthirtyo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}

			if ((weekday == "Четверг") && (timee == "10:00"))
			{
				thteno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "10:30"))
			{
				thtenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "11:00"))
			{
				theleveno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "11:30"))
			{
				thelevenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "12:00"))
			{
				thtwelveo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "12:30"))
			{
				thtwelveh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Четверг") && (timee == "13:00"))
			{
				ththirtyo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}

			if ((weekday == "Пятница") && (timee == "10:00"))
			{
				fteno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "10:30"))
			{
				ftenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "11:00"))
			{
				feleveno = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "11:30"))
			{
				felevenh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "12:00"))
			{
				ftwelveo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "12:30"))
			{
				ftwelveh = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
			if ((weekday == "Пятница") && (timee == "13:00"))
			{
				fthirtyo = false;
				InlineKeyboardMarkup::Ptr keybort = keybortglav();
				bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
			}
		}
		if (query->data == "confirm")
		{
			bot.getApi().sendMessage(query->message->chat->id, "Вы потдтвердили запись на прием");
			messageText = "Данные для отправки:\n";
			messageText += "Имя: " + userInfo[userId].firstname + "\n";
			messageText += "Фамилия: " + userInfo[userId].lastname + "\n";
			messageText += "День недели: " + userInfo[userId].day + "\n";
			messageText += "Время: " + userInfo[userId].time;
			bot.getApi().sendMessage(adminid, messageText);
		}
		});

	bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
		if (query->data == "BACK") {
			InlineKeyboardMarkup::Ptr keybort = keybortglav();
			bot.getApi().editMessageText("Выберите время", query->message->chat->id, query->message->messageId, "", "Markdown", false, keybort);
		}
		});

	bot.getEvents().onCommand("stop", [&bot, &i](Message::Ptr message) {
		if (message->from->id == adminid) {
			bot.getApi().sendMessage(message->chat->id, "Программа приостановила свою работу...!");
			system("exit");
			i = 2;
		}
		else {
			bot.getApi().sendMessage(message->chat->id, "У вас недостаточно прав для совершения данной операции");
		}
		});

	bot.getEvents().onCommand("отменить", [&bot](Message::Ptr message) {
		InlineKeyboardMarkup::Ptr keybort = cancelkeyboard();
		bot.getApi().sendMessage(message->chat->id, "Вы подтверждаете прием или хотите выбрать другую дату?", false, 0, keybort);
		});

	bot.getEvents().onCommand("info", [&bot](Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Данная программа создана для Октябрьской сельской больницы \nПрограмма помогает записаться дистационно на прием к врачу! \n ТТехническая поддержка: \n Номер телефона: +77066652654 \n Телеграмм: @Kykikyk \n E-mail: oversg@bk.ru ");
		});

	try {
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
		TgLongPoll longPoll(bot, 60, lastUpdateId + 1);
		while (inRunning) {
			auto updates = bot.getApi().getUpdates(lastUpdateId + 1);
			for (auto& update : updates) {
				lastUpdateId = update->updateId;
			}
			if (i == 2) {
				break;
			}
			printf("Long poll started\n");
			longPoll.start();
		}
	}
	catch (TgException& e) {
		printf("error: %s\n", e.what());
	}
	return 0;
}