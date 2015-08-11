/*
 * tree_table.h
 * definitions to manage tree information
 * Author: Brian Gravelle Caes Lab University of Oregon
 * Date Started: 10 August 2015
 * Last Update:  10 August 2015
 *
 *
*/

#ifndef TREE_TABLE
#define TREE_TABLE

#include <openssl/evp.h>
#include <openssl/dh.h>
#include <string>
#include <vector>
#include <map>

using namespace std;


struct LeafNode {
  int id;
  EVP_PKEY *public_key;
};

typedef vector<LeafNode> LeafPair;
typedef map < string, LeafPair > Table;

#endif
