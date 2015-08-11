/*
 * tree_table.h
 * definitions to manage tree information
 * Author: Brian Gravelle Caes Lab University of Oregon
 * Date Started: 10 August 2015
 * Last Update:  11 August 2015
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


union TreeNode {
  LeafNode leaf_node;
  MiddleNode middle_node;
}

struct LeafNode {
  int id;
  EVP_PKEY *public_key;
  TreeNode *parent_node;
};

struct MiddleNode {
  unsigned char* key;
  string bin_code, dec_code;
  TreeNode *left_child, *right_child, *parent_node;
};

typedef vector<LeafNode> LeafPair;
typedef map < string, LeafPair > Table;

#endif
