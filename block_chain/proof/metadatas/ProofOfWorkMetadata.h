//
// Created by default on 17/4/2561.
//

#ifndef BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
#define BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H


#include "Metadata.h"

class ProofOfWorkMetadata: public Metadata {
    friend class ProofOfWork;
public:
    ProofOfWorkMetadata();
    ProofOfWorkMetadata(long long int, long long int, std::string str);
    bool operator==(Metadata& m) const override {
        auto pwm = dynamic_cast<ProofOfWorkMetadata*>(&m);
        return pwm->first == first && pwm->second == second && pwm->winner == winner;
    }
    Element* toElement() const override;
    Hash* hash() override;
    void update_database(Database *pDatabase) override;
protected:
    void fromElement(ElementObject* e, const Serializer* s, const char* encoding) override;
private:
    long long int first;
    long long int second;
    std::string winner;
};


#endif //BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
