#include <iostream>
#include <tgbot/tgbot.h>

int main() {
    // Create a bot object with your bot token
    TgBot::Bot bot("YOUR_BOT_TOKEN");

    // Register a command handler for /start command
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hello, I'm your Telegram bot!");
    });

    // Register a command handler for /echo command
    bot.getEvents().onCommand("echo", [&bot](TgBot::Message::Ptr message) {
        std::string text = message->text;
        text.erase(0, 6); // Remove the "/echo " part from the message

        bot.getApi().sendMessage(message->chat->id, text);
    });

    // Run the bot
    try {
        std::cout << "Bot is running..." << std::endl;
        bot.getApi().deleteWebhook();

        // Uncomment the following line if you want to use long polling
        // bot.getApi().waitForUpdates();

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (const TgBot::TgException& e) {
        std::cerr << "Telegram Bot Error: " << e.what() << std::endl;
    }

    return 0;
}
