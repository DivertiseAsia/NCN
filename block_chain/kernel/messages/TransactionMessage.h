//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTIONMESSAGE_H
#define BLOCK_CHAIN_TRANSACTIONMESSAGE_H


#include "Message.h"

/**
 *  @class TransactionMessage "block_chain/kernel/messages/TransactionMessage.h"
 *  An transaction message contains everything about a transaction:
 *  - the public key of the creator
 *  - the serialized transaction
 *  - the ciphered serialized transaction
 *  - the MerkleTree of that transaction
 *  @see Message
 *  @see MerkleTree
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class TransactionMessage: public Message
{
    friend class TransactionParser;
public:
    TransactionMessage();

    /**
     *  Creates a transaction message
     *  Calls the super constructor with the type value
     *  @see Message::TRANSACTION
     *
     *  @param p The plain text.
     *  @param c The ciphered text.
     *  @param k The user's key.
     *  @param t The Merkle tree for that transaction.
     */
    TransactionMessage(std::string p, std::string c, std::string k, MerkleTree* t);
    ~TransactionMessage() override;
    Element* toElement() const override;

    /**
     *  Get the ciphered text
     *
     *  @return The ciphered text in ASCII form
     */
    std::string getCipher();
protected:
    void fromElement(ElementObject* element, const Serializer* serializer, const char* encoding) override;

private:

    /**
     *  The public key to decrypt the ciphered text
     */
    std::string public_key;

    /**
     *  The plain text representing the serialized
     *  transaction
     */
    std::string plain_text;

    /**
     *  The ciphered text representing the serialized
     *  transaction
     */
    std::string cipher;

    /**
     *  The Merkle tree containing the hash of the
     *  transaction
     */
    MerkleTree* tree;
};


#endif //BLOCK_CHAIN_TRANSACTIONMESSAGE_H
