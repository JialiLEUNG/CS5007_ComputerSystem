/*
 * dictionary.c
 *
 * This file implements a dictionary of words and definitions.
 * There there can be multiple definitions for a word. A word
 * is limited to a length of MAX_WORD characters including the
 * terminating '\0' character, and a definition is limited to
 * MAX_DEF characters including the terminating '\0' character.
 * The dictionary is limited to MAX_ENTRIES entries.
 *
 *  @since 2019-05-09
 *  @author Philip Gust
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dictionary.h"

/** Dictionary entry with word and definition */
struct DictionaryEntry {
	/** word string */
	char word[MAX_WORD];

	/** def string */
	char def[MAX_DEF];
};

/** Dictionary array of entries */
struct Dictionary {
	/** Number of dictionary entries */
	int n_entries;

	/** Dictionary entries */
	struct DictionaryEntry entries[MAX_ENTRIES];
};

/** The dictionary */
static struct Dictionary dictionary;

/**
 * Return the number of entries in the dictionary.
 * @return the number of dictionary entries
 */
int getDictionarySize() {
	return dictionary.n_entries;
}

/**
 * Get dictionary word.
 *
 * @param entry the index of the entry
 * @param word word for the entry
 * @return true if entry found
 */
bool getDictionaryWord(int entry, char word[]) {
	if (entry < 0 || entry >= dictionary.n_entries) {
		return false;
	}
	strcpy(word, dictionary.entries[entry].word);
	return true;
}

/**
 * Get dictionary definition.
 *
 * @param entry the index of the entry
 * @param def the definition for the entry
 * @return true if entry found
 */
bool getDictionaryDefinition(int entry, char def[]) {
	if (entry < 0 || entry >= dictionary.n_entries) {
		return false;
	}

	strcpy(def, dictionary.entries[entry].def);
	return true;
}

/**
 * Find dictionary entry for a word. If word ends
 * with wildcard (*), finds any matching word.
 *
 * @param word the word to match
 * @param start_entry the starting entry
 * @return entry index or -1 if not found
 */
int getDictionaryEntry(const char word[], int start_entry) {
	int wordlen = strlen(word);
	if (wordlen > 0 && start_entry >= 0) {
		for (int entry = start_entry; entry < dictionary.n_entries; entry++) {
			if (word[wordlen-1] == '*') {  // wildcard match
				if (strncmp(word, dictionary.entries[entry].word, wordlen-1) == 0) {
					return entry;
				}
			} else if (strcmp(word, dictionary.entries[entry].word) == 0) {
				return entry;
			}
		}
	}
	return -1;
}

/**
 * Put definition entry for name. Assumes unique entry name.
 *
 * @param word the entry word
 * @param def the entry definition
 * @return index of new entry or -1 if dictionary is full
 */
int putDictionaryEntry(const char word[], const char def[]) {
	assert(strlen(word) < MAX_WORD);
	assert(strlen(def) < MAX_DEF);

	if (dictionary.n_entries >= MAX_ENTRIES) {
		return -1;
	}

	strcpy(dictionary.entries[dictionary.n_entries].word, word);
	strcpy(dictionary.entries[dictionary.n_entries].def, def);

	return dictionary.n_entries++;
}
