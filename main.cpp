#include <iostream>

#include "block_chain/Node.h"
#include "block_chain/TransactionManager.h"
#include "block_chain/chain/block/proof/Proof.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
#include "reward/RewardTransaction.h"
#include "block_chain/kernel/components/Config.h"
#include "block_chain/Framework.h"
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */
/*rand() % 1000+3000*/

int main() {


    //Possible transactions
    Framework block_chain;
    block_chain.add_transaction(new StatusTransaction);
    block_chain.add_transaction(new MoneyTransaction);
    block_chain.add_transaction(new MessagesTransaction);

    //Get the manager
    auto manager = block_chain.generate_manager();

    //Get the serializer
    auto serial = block_chain.generate_serializer();

    //Reward object
    Reward* reward = new RewardTransaction();

    //Block chain initialization
    Config config("./config.json", serial, Proof::WORK, reward);
    Node client(config);

    //launching the loop
    client.start(manager);
    return 0;
}
