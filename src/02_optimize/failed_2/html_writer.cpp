#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html_writer.h"

const size_t MAX_WORD_LENGTH = 128;

const char* getWordStart (const char* pos, bool* newLineFound);
const char* getWordEnd   (const char* pos);

void defineDoc(const Dictionary* dictionary, const char* doc, FILE* output)
{
    assert(dictionary);
    assert(doc);
    assert(output);

    const char* pos = doc;
    char curWord[MAX_WORD_LENGTH] = {};

    while (*pos != '\0')
    {
        bool newLineFound = false;

        const char* wordStart = getWordStart(pos, &newLineFound);
        if (wordStart == nullptr) { fprintf(output, pos); break; }

        const char* wordEnd = getWordEnd(wordStart);
        memcpy(curWord, wordStart, wordEnd - wordStart);

        curWord[wordEnd - wordStart] = '\0';

        if (wordStart > pos)
        {
            // fprintf(output, "%.*s", wordStart - pos, pos);
        }

        if (newLineFound)
        {
            // fprintf(output, "</p>\n<p>\n");
        }

        const DictEntry* curDictEntry = getDictionaryEntry(dictionary, curWord);
        if (curDictEntry != nullptr)
        {
            // fprintf(output, "<text class=\"tooltip\" title=\"");
            // printDictEntry(output, curDictEntry);
            // fprintf(output, "\">%s</text>", curWord);
        }
        else
        {
            // fprintf(output, "%s", curWord);
        }

        pos = wordEnd;
    }

    // fprintf(output, "</p>\n</body>\n</html>");
}

const char* getWordStart(const char* pos, bool* newLineFound)
{
    assert(pos);
    assert(newLineFound);
    
    while (*pos != '\0' && !isalpha(*pos)) 
    {
        if (*pos == '\n') { *newLineFound = true; } 
        pos++; 
    }

    return *pos == '\0' ? nullptr : pos;
}

const char* getWordEnd(const char* pos)
{
    assert(pos);

    while (*pos != '\0' && isalpha(*pos)) { pos++; }

    return pos;
}