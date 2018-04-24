//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKMESSAGE_H
#define BLOCK_CHAIN_BLOCKMESSAGE_H


#include "Message.h"

/**
 *  @class BlockMessage "block_chain/kernel/messages/BlockMessage.h"
 *  An block message contains everything about a block:
 *  - the serialized block
 *  - the key of the creator
 *  - the MerkleTree of that transaction
 *  @see Message
 *  @see MerkleTree
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockMessage: public Message
{
    friend class BlockParser;
public:
    BlockMessage();

    /**
     *  Creates a block message
     *  Calls the super constructor with the type value
     *  @see Message::BLOCK
     *
     *  @param b The serialized block
     *  @param k The creator's key
     *  @param t The Merkle tree for that transaction.
     */
    BlockMessage(std::string b, std::string k, MerkleTree* t);
    ~BlockMessage() override;
    Element* toElement() const override;

    /**
     *  Get the key of the creator
     *
     *  @return The key of the creator
     */
    const std::string get_key() const;
protected:
    void fromElement(ElementObject* element, const Serializer* serializer, const char* encoding) override;

private:

    /**
     *  The serialized block
     */
    std::string block;

    /**
     *  The creator's key
     */
    std::string key;

    /**
     *  The Merkle tree containing the hash of the
     *  block's transactions
     */
    MerkleTree* tree;
};


#endif //BLOCK_CHAIN_BLOCKMESSAGE_H
