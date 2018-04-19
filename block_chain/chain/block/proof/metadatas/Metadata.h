//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_METADATA_H
#define BLOCK_CHAIN_METADATA_H


#include "../../../../utils/serialization/Element.h"
#include "../../../../kernel/components/Component.h"
#include "../../../../algorithm/Hash.h"
#include "../../../state/Database.h"

class Metadata:public Component{
public:
    virtual ~Metadata();
    virtual bool operator==(Metadata& m) const{
        return false;
    }
    //virtual Element* toElement() const;
    //virtual void fromElement(ElementObject* e, const Serializer* serializer, const char* encoding);
    virtual void update_database(Database *pDatabase) = 0;
    virtual Hash* hash() = 0;
};
#endif //BLOCK_CHAIN_METADATA_H
