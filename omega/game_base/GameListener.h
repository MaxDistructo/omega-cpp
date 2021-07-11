#include "mdcore/listener.h"



class Sublistener
{
    public:
        Sublistener();
        ~Sublistener();
        virtual void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message);
    private:
        std::string registeredFor;
        SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel;
        SleepyDiscord::Snowflake<SleepyDiscord::User> user;
};

class GameListener: public mdcore::Listener
{
    public:
        void onMessage(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override;
        void registerListener(std::string name, Sublistener& listener)
        {
            listeners[name] = new (std::nothrow) Sublistener(listener);
        }
        void deregisterListener(std::string name)
        {
            auto listener = listeners[name];
            delete listener;
            listeners[name] = nullptr;
        }
    private:
        std::map<std::string, Sublistener*> listeners;
};