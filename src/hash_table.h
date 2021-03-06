//------------------------------------------------------------------------------
//! Contains declaration of the HashTable as well as functions related to it.
//! In order to work with the HashTable you have to specify a hash function and
//! a cmp function that will be called each time a collision occurres in a 
//! bucket. 
//! 
//! @file   hash_table.h
//! @author tralf-strues 
//! @date   2021-04-02
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#pragma once

#include <stdint.h>

#include "language.h"
#include "bucket.h"

struct HashTable
{
    size_t   size;
    Bucket*  buckets;
    int      (*cmp)     (const ht_key_t first, const ht_key_t second);
    uint32_t (*getHash) (ht_key_t key);
};

//------------------------------------------------------------------------------
//! Constructs the hashTable.
//! 
//! @param hashTable
//! @param size
//! @param cmp     function comparing keys in case a collision occurres.
//! @param getHash hash function.
//------------------------------------------------------------------------------
void construct(HashTable* hashTable, size_t size, 
               int (*cmp)(const ht_key_t first, const ht_key_t second),
               uint32_t (*getHash)(ht_key_t key));

//------------------------------------------------------------------------------
//! Destroys the hashTable. 
//! 
//! @param hashTable
//!
//! @note If construct() function hasn't been called prior to destroy(), the 
//!       latter doesn't free memory (due to no memory allocation having
//!       been called).
//------------------------------------------------------------------------------
void destroy(HashTable* hashTable);

//------------------------------------------------------------------------------
//! Insert a pair (key, value) to hashTable.
//! 
//! @param hashTable
//! @param key
//! @param value
//!
//! @note If there is an element with the same key in hashTable already, then 
//!       does nothing. 
//------------------------------------------------------------------------------
void insert(HashTable* hashTable, ht_key_t key, ht_value_t value);

//------------------------------------------------------------------------------
//! Finds an element associated with key in hashTable.
//! 
//! @param hashTable
//! @param key
//! 
//! @return pointer to a value from pair (key, value).
//------------------------------------------------------------------------------
#ifndef OPTIMIZED_FIND
const ht_value_t* find(const HashTable* hashTable, ht_key_t key);
#else
extern const ht_value_t* find(const HashTable* hashTable, ht_key_t key);
#endif