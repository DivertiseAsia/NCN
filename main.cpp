#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
#include "validator/CustomSerializer.h"
#include "block_chain/utils/serialization/json/JsonCreator.hpp"
#include "block_chain/utils/serialization/json/JsonParser.hpp"
#include "block_chain/TransactionManager.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */

int main() {
    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);
    Serializer* serial = new CustomSerializer();
    serial->set_serializer("json", new JsonCreator());
    serial->set_unserializer("json", new JsonParser());
    Node client(serial, 3000);
    //Transaction* t = new StatusTransaction("I lost");
    Transaction* t = nullptr;
    usleep(1000000);
    do{
        t = manager.run();
        client.request_transaction(t);
    }while(t != nullptr);

    std::cout << "Wait" << std::endl;
    //usleep(3000000);
    while(1);//{std::cout<<"t";client.request_transaction(t);std::cout<<"t"<<std::endl;}
    return 0;
}


/*
 * Object Database
 * --> List de Row (abstract)
 *      --> Contient une version to_string (Hash a mit son statut a jour :X)
 *      --> Contient une action (Mettre le statut a jour, poster un nouveau message)
 *      --> Contient un resultat (nouveau statut ou message)
 *      --> Contient un checker de si c'est possible (Est ce qu'il y a un statut pour pouvoir poster un message?)
 *
 * --> List de Row uniques
 *      --> Mis a jour quand un nouveau arrive, pas de supperposition
 * --> List de Row multiple
 *      --> Ajoutes a la suite
 */
