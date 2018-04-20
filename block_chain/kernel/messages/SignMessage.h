//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNMESSAGE_H
#define BLOCK_CHAIN_SIGNMESSAGE_H


#include "Message.h"

/**
 *  An basic message for simple communication.
 *  @see Message
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class SignMessage: public Message
{
    friend class SignInParser;
    friend class SignOutParser;
    friend class PeersAskParser;
    friend class PeersAnswerParser;
public:
    SignMessage();

    /**
     *  Creates a simple message with a text and
     *  a message type
     *  Calls the super constructor with the type value
     *
     *  @param p The given text. Used as a peer text
     *  @param t The type of the message
     */
    SignMessage(std::string p, int t);
    ~SignMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:

    /**
     *  The text contained in the basic message
     */
    std::string peer;
};


#endif //BLOCK_CHAIN_SIGNMESSAGE_H
