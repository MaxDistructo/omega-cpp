#include "mdcore/listener.h"
#include "mdcore/logger.h"

class EventListener
{
    public:
        EventListener(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user)
        {
            this->channel = channel;
            this->user = user;
        };
        ~EventListener();
        virtual void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message);
        SleepyDiscord::Snowflake<SleepyDiscord::Channel> getChannel()
        {
            return this->channel;
        }
        SleepyDiscord::Snowflake<SleepyDiscord::User> getUser()
        {
            return this->user;
        }
    private:
        SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel;
        SleepyDiscord::Snowflake<SleepyDiscord::User> user;
};

class EventDispatcher: public mdcore::Listener
{

    public:
        EventDispatcher(){};
        ~EventDispatcher(){};
        void onMessage(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override
        {
            for(auto const& [key, val] : listeners)
            {
                if(val->getUser() == message.author.ID && val->getChannel() == message.channelID)
                {
                    logger.info("Executing " + key);
                    val->execute(client, message);
                    break;
                }
            }
        }
        /**
         * @brief Register a new listener
         * This function will both register and take over managing the alocated memory. 
         * 
         * @param name The name to assign to this listener. Suggest to use the ID/Name of the user
         * @param listener A pointer to an allocated listener
         */
        void registerListener(std::string name, EventListener* listener)
        {
            listeners[name] = listener;
        }
        /**
         * @brief Delete a registered EventListener
         * 
         * @param name The name of the listener to delete
         */
        void deregisterListener(std::string name)
        {
            auto listener = listeners[name];
            delete listener;
            listeners[name] = nullptr;
        }
    private:
        std::map<std::string, EventListener*> listeners;
        mdcore::Logger logger = mdcore::Logger("EventDispatcher");
};