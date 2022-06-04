#pragma once
#include "mdcore/listener.h"
#include "mdcore/logger.h"

/**
 * @brief The event listener object. This is only used by the event dispatcher.
 * 
 */
class EventListener
{
    public:
        EventListener(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user)
        {
            this->channel = channel;
            this->user = user;
        };
        virtual ~EventListener(){};
        virtual void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message){};
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
        virtual ~EventDispatcher()
        {
            //We took over the memory handing from whoever created this. Delete all EventListeners in queue before we die.
            for(auto const& [key,val] : listeners)
            {
                delete val;
            }
        };
        void onMessage(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override
        {
            std::string matching_key = "";
            for(auto const& [key, val] : listeners)
            {
                if(val != nullptr){
                    if(val->getUser() == message.author.ID && val->getChannel() == message.channelID)
                    {
                        logger.info("Executing " + key);
                        val->execute(client, message);
                        //Queue up a delete of the listener after the loop ends.
                        matching_key = key;
                        break;
                    }
                }
            }
            if(matching_key != "")
            {
                EventListener* val = listeners[matching_key];
                delete val;
                listeners[matching_key] = nullptr;
                matching_key = "";
            }
            //This allows listeners to queue up new listeners.
            if(!queue.empty())
            {
                for(auto const& [key, val] : queue)
                {
                    listeners[key] = val;
                }
                queue.clear();
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
         * @brief Threadsafe version of registerListener
         * 
         * @param name 
         * @param listener 
         */
        void enqueueListener(std::string name, EventListener* listener)
        {
            queue[name] = listener;
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
        std::map<std::string, EventListener*> queue;
        mdcore::Logger logger = mdcore::Logger("EventDispatcher");
};