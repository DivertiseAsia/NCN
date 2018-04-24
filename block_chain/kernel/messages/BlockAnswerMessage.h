//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
#define BLOCK_CHAIN_BLOCKANSWERMESSAGE_H


#include "Message.h"

/**
 *  @class BlockAnswerMessage "block_chain/kernel/messages/BlockAnswerMessage.h"
 *  An answer containing the required block
 *  @see Message
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockAnswerMessage: public Message
{
    friend class BlockAnswerParser;
public:
    BlockAnswerMessage();

    /**
     *  Creates an answer to a block request
     *  Calls the super constructor with the type value
     *  @see Message::ANSWER_BLOCK
     *
     *  @param p The serialized block
     *  @param k The key of the creator
     */
    BlockAnswerMessage(std::string p, std::string k);
    ~BlockAnswerMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject* element, const Serializer* serializer, const char* encoding) override;

private:

    /**
     * The serialized required block
     */
    std::string block;

    /**
     * The key of the creator
     */
    std::string key;
};



#endif //BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
