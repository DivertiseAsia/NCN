//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <algorithm>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <iostream>
#include "chain/NodeState.h"
#include "utils/socket/SocketServer.h"
#include "utils/socket/Peer.h"
#include "algorithm/RSA.h"
#include "kernel/messages/Message.h"
#include "chain/block/proof/Proof.h"
#include "TransactionManager.h"
#include "kernel/parsers/MessageParser.h"
#include "kernel/parsers/BlockAskParser.h"
#include "kernel/parsers/BlockAnswerParser.h"
#include "kernel/parsers/BlockParser.h"
#include "kernel/parsers/SignInParser.h"
#include "kernel/parsers/SignOutParser.h"
#include "kernel/parsers/TransactionParser.h"
#include "kernel/parsers/PeersAnswerParser.h"
#include "kernel/parsers/PeersAskParser.h"
#include "kernel/messages/TransactionMessage.h"
#include "kernel/messages/BlockAskMessage.h"
#include "kernel/messages/SignOutMessage.h"
#include "kernel/messages/AskPeersMessage.h"

/**
 *  The node is the main entry point of the framework.
 *  It needs to be called to initialize the peer.
 *  Its work is to connect with peers, to exchange with
 *  peers and to ask the user to send its own transactions
 *  @see Transaction
 *  @see TransactionManager
 *  @see Proof
 *  @see MessageParser
 *  @see Serializer
 *  @see SocketServer
 *  @see NodeState
 *  @see RSA_Cryptography
 *  @see Message_action
 *  @see Block
 *
 *  @author Mathieu Lochet
 *  @version 6
 */
class Node{
    friend class Parser;
    friend class PeersAnswerParser;
    friend class PeersAskParser;
    friend class SignInParser;
    friend class SignOutParser;
    friend class TransactionParser;
    friend class BlockParser;
    friend class BlockAskParser;
    friend class BlockAnswerParser;
public:
	/**
	 *  Initialize the Node with all of its parameters
	 *  @see serializer
	 *  @see Proof
	 *  @see Reward
	 *
	 *  @param serializer The serializer used everywhere in the app
	 *  @param p The port the client will listen to
	 *  @param e The encoding to use with the serializer
	 *  @param pr The ID of the Proof to be used
	 *  @param d Is the app runs in debug more
	 *  @param r The reward transaction object
	 */
    Node(Serializer* serializer, int p = 3000, const char* e = "json", int pr = Proof::WORK, bool d = false, Reward* r = nullptr);

	/**
	 *  A destructor to delete all of the objects and signing out
	 *  from all of the peers
	 */
    ~Node();

	/**
	 *  Close the connection and sign out from all of the peers
	 */
    void close();

	/**
	 *  Process a transaction and send it to all of the peers
	 *  @see Transaction
	 *
	 *  @param transaction The newly created transaction to process and to send to the peers
	 */
    void request_transaction(Transaction* transaction);

	/**
	 *  The callback each socket connection will run.
	 *  Its goal is to generate messages and to root them to the
	 *  correct parser.
	 *  @see MessageParser
	 *  @see Socket
	 *  @see Serializer
	 *
	 *  @param socket The socket in charge of the connection
	 *  @param serializer The serializer to serialize and unserialize the packets
	 *  @param node The node to compute the requests
	 *  @return true once it's done
	 */
    bool static defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node);

	/**
	 *  Starts to run the manager and loop on its request, until
	 *  the manager replies nullptr.
	 *  @see TransactionManager
	 *
	 *  @param manager The manager containing the different transactions.
	 */
    void start(TransactionManager manager);

private:

	/**
	 *  The serializer
	 */
    Serializer* serializer;

	/**
	 *  Add all of the different parsers into the index of parsers
	 */
    void init_parsers();

	/**
	 *  Add a new parser in the list of parsers
	 *  @see MessageParser
	 *
	 *  @param p The new MessageParser to add to the list
	 */
	void add_parser(MessageParser* p);

	/**
	 *  The index of MessageParser to parse the packets
	 */
    std::map<int, MessageParser*> parsers;


	/**
	 *  Encoding for serialization
	 */
    std::string encoding;

	/**
	 *  The used proof for block validation
	 */
    Proof* proof;

	/**
	 *  Read the network file and ask for the list of peers
	 */
    void store();

	/**
	 *  The socket server listening on the port.
	 *  It accepts connections from other peers.
	 */
	SocketServer server;

	/**
	 *  The actual state of the block chain
	 */
    NodeState block_chain;

	/**
	 *  The peer describing itself
	 */
    Peer self;

	/**
	 *  The list of the other peers
	 */
    std::vector<Peer> peers;

	/**
	 *  The thread that will run the socket server and listen to the port
	 */
    std::thread running;

	/**
	 *  The cryptography object to use to encrypt the messages and objects
	 */
    RSA_Cryptography rsa;

	/**
	 * Counter to see if it received a block before it sends its own
	 */
    int queue;
    //typedef void(Node::* Message_action)(Message* message);

	/**
	 *  The main action of the callback
	 *  @see Message
	 *  @see MessageParser
	 *
	 *  @param message The parsed message
	 *  @param node The node to compute the requests
	 *  @return true once it's done
	 */
    void static async(Message* message, Node* node);

	/**
	 *  All of the blocks waiting for a missing parent.
	 *  They will be added to the block_chain once a
	 *  block's parent fingerprint is known in the blockchain
	 */
    std::vector<Block*> waiting;

	/**
	 *  Check if the block's parent is known.
	 *  If it is not, it is asked to another peer,
	 *  in a recursive way, and the block is added
	 *  to the waiting list.
	 *  @see Block
	 *
	 *  @param pBlock The block to check
	 *  @return 1 if the block's parent fingerprint is known, 0 otherwise
	 */
    int load(Block *pBlock);

	/**
	 *  If the Node runs in a debug mode
	 */
    bool debug;
};

#endif //BLOCK_CHAIN_CLIENT_H
