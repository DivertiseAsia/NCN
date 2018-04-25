//
// Created by default on 17/4/2561.
//

#ifndef BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
#define BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H


#include "Metadata.h"

/**
 *  @class ProofOfWorkMetadata "block_chain/chain/block/proof/metadata/ProofOfWorkMetadata.h"
 *  A metadata class for the proof of work.
 *  @see Metadata
 *  @see Block
 *  @see ProofOfWork
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfWorkMetadata: public Metadata {
    friend class ProofOfWork;
public:

    /**
     *  The type of the particular metadata
     */
    static const int TYPE;
    ProofOfWorkMetadata();

    /**
     *  Generated the metadata with the given parameters
     *
     *  @param i1 The first hash parameter
     *  @param i2 The second hash parameter
     *  @param str The winner's public key
     */
    ProofOfWorkMetadata(long long int i1, long long int i2, std::string str);
    bool operator==(Metadata& m) const override {
        auto pwm = dynamic_cast<ProofOfWorkMetadata*>(&m);
        return pwm->first == first && pwm->second == second && pwm->creator == creator;
    }
    Element* toElement() const override;
    std::string hash() override;
    void update_database(Database *pDatabase) override;
protected:
    void fromElement(ElementObject* e, const Serializer* s, const char* encoding) override;
private:

    /**
     *  The first hash parameter
     */
    long long int first;

    /**
     *  The first second parameter
     */
    long long int second;
};


#endif //BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
