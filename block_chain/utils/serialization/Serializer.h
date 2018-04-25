//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_SERIALIZER_H
#define BLOCK_CHAIN_SERIALIZER_H

#include "../../chain/block/Block.h"
#include "../../chain/block/transaction/Transaction.h"
#include "../Factory.h"
#include "Parser.h"
#include "../../kernel/messages/Message.h"
#include <cstdlib>
#include "json/JsonCreator.h"
#include "json/JsonParser.h"
#include <utility>
#include "../../chain/block/proof/metadata/ProofOfWorkMetadata.h"

/**
 *  @class Serializer "block_chain/utils/serialization/Serializer.h"
 *  A basic serializer.
 *  The class Serializer implements all of the
 *  serialization and unserialization methods.
 *  @see ContentCreator
 *  @see ContentParser
 *  @see Element
 *  @see ElementObject
 *  @see Component
 *  @see Transaction
 *  @see Block
 *  @see Message
 *  @see Metadata
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Serializer
{
public:

    /**
     *  Initialize the Serializer with default readers:
     *  - json creator
     *  - json parser
     *  They can be used as encoding
     *  @see JsonCreator
     *  @see JsonParser
     */
    Serializer();

    /**
     * Default destructor that clears the factories
     */
     virtual ~Serializer();

    /**
     *  Serialize a Component object
     *  @see Component
     *  @see ContentCreator
     *
     * 	@param component the component to be serialized
     * 	@param encoding the key to choose the creator
     * 	@return the serialized string
     */
    virtual char* serialize(const Component* component, const char* encoding) const;

    /**
     *  Serialize an Element object
     *  @see Element
     *  @see ContentCreator
     *
     * 	@param element the element to be serialized
     * 	@param encoding the key to choose the creator
     * 	@return the serialized string
     */
    virtual char* serialize(Element* element, const char* encoding) const;

    /**
     *  Unserialize an given string to obtain a Transaction
     *  @see ContentParser
     *  @see Transaction
     *
     * 	@param transaction the string to be unserialized
     * 	@param encoding the key to choose the parser
     * 	@return The Transaction object
     */
    virtual Transaction* unserializeTransaction(std::string transaction, const char* encoding) const;

    /**
     *  Unserialize an given string to obtain a Block
     *  @see ContentParser
     *  @see Block
     *
     * 	@param block the string to be unserialized
     * 	@param encoding the key to choose the parser
     * 	@return The Block object
     */
    virtual Block* unserializeBlock(std::string block, const char* encoding) const;

    /**
     *  Unserialize an given string to obtain a Message
     *  @see ContentParser
     *  @see Message
     *
     * 	@param message the string to be unserialized
     * 	@param encoding the key to choose the parser
     * 	@return The Message object
     */
    virtual Message* unserializeMessage(std::string message, const char* encoding) const;

    /**
     *  Unserialize an given string to obtain a Metadata
     *  @see ContentParser
     *  @see Metadata
     *
     * 	@param message the string to be unserialized
     * 	@param encoding the key to choose the parser
    * 	@return The Metadata object
    */
    virtual Metadata* unserializeMetadata(std::string message, const char* encoding) const;

    /**
     *  Unserialize a given string to obtain an ElementObject
     *  @see ContentParser
     *  @see ElementObject
     *
     * 	@param str the string to be unserialized
     * 	@param encoding the key to choose the parser
    * 	@return The Element representation of the string
    */
    ElementObject* getElement(std::string str, const char* encoding) const;

    /**
     *  Add a custom creator to the list
     *  @see ContentCreator
     *
     * 	@param creator the creator object to use
    */
    void set_serializer(ContentCreator* creator);

    /**
     *  Add a custom parser to the list
     *  @see ContentParser
     *
     * 	@param parser the parser object
    */
    void set_unserializer(ContentParser* parser);

    /**
     *  Add a new possible metadata
     *  @see Metadata
     *
     * 	@param id The type of the metadata
     * 	@param metadata The lambda expression generating the metadata
    */
    void add_metadata(int id, std::function<Metadata*()> metadata);

    /**
     *  Add a new possible transaction
     *  @see Transaction
     *
     * 	@param id The type of the metadata
     * 	@param transaction The lambda expression generating the transaction
    */
    void add_transaction(int id, std::function<Transaction*()> transaction);
protected:

    /**
     * The factory of different creators
     * @see Factory
     * @see ContentCreator
     */
    Factory<ContentCreator*> creators;

    /**
     * The factory of different parsers
     * @see Factory
     * @see ContentParser
     */
    Factory<ContentParser*> parsers;

    /**
     *  The list of all possible unserializable metadata
     */
    std::map<int, std::function<Metadata*()>> metadata_index;

    /**
     *  The list of all possible unserializable transactions
     */
    std::map<int, std::function<Transaction*()>> transactions_index;
};


#endif //BLOCK_CHAIN_SERIALIZER_H
