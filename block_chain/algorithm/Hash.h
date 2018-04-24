//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_H
#define BLOCK_CHAIN_HASH_H

#include <string>
#include <openssl/md5.h>
#include "../kernel/components/Component.h"
#include "../utils/Encoding.h"
#include <iostream>

class Serializer;

/**
 *  @class Hash "block_chain/algorithm/Hash.h"
 *  A class for md5 based hash, based on OpenSLL
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Hash{
public:

    /**
     *  A default constructor
     */
    Hash();

    /**
     *  A Constructor that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     */
    Hash(Hash* hash1, Hash* value);

    /**
     *  A Constructor that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     */
    Hash(Hash* hash1, double value);

    /**
     *  A Constructor that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     */
    Hash(Hash* hash1, int value);

    /**
     *  A Constructor that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     */
    Hash(Hash* hash1, long long int value);

    /**
     *  A Constructor that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     */
    Hash(Hash* hash1, std::string value);

    /**
     *  A Constructor that hash a string value
     *
     *  @param value Element to Hash
     */
    Hash(std::string value);

    /**
     *  Constructor that Hash a component object
     *
     *  @param component The component to hash
     *  @param serializer The serializer to serialize the component
     *  @param encoding The encoding to serialize the component
     */
    Hash(const Component* component, const Serializer* serializer, const char* encoding);

    /**
     *  Get a string representation of the hash
     *
     *  @return The string representation of the hash
     */
    std::string to_string() const;

    /**
     *  Compare two different Hashes
     *
     *  @param h The Hash to compare to
     *  @return true if both Hashes are the same, false otherwise
     */
    bool operator==(Hash const& h) const{
        return hash == h.hash;
    }

    /**
     *  The method used by the serializer to transform
     *  an object into an Element representation.
     *  @see Element
     *
     *  @return The Element representation of the object
     */
    Element* toElement();

    /**
     *  The function used to build the object from
     *  its element representation.
     *  the object if it is empty
     *  @see ElementObject
     *  @see Serializer
     *
     *  @param element The Element representation of the object
     *  @param serializer The serializer (Can be used if serialization of some elements is needed)
     *  @param encoding The encoding that has been used to create the Element representation of the object (Can be used if serialization of some elements is needed)
     */
    void fromElement(ElementObject* element, const Serializer* serializer, const char* encoding);
private:

    /**
     *  The hash itself
     */
    std::string hash;
};

#endif //BLOCK_CHAIN_HASH_H
