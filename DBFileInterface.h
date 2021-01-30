/**
 * @brief A Interface of DBFIle. Provides signature of methods that represents a DBFile. Three
 * types of DBFile heap, sorted and tree are implemented based on this interface. Requires 3 variables,
 * 1. oFile, A file to store pages of records.
 * 2. oPage, Pages which stores limited number of records. When Page is full its stored
 * to file and a new page is created.
 * 3. pageNumber, An offest representing current page Number in file.
 */
#ifndef DBFileInterface_H
#define DBFileInterface_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"

class DBFileInterface
{
    File oFile;
    Page oPage;
    off_t pageNumber;

public:
    DBFileInterface();
    virtual ~DBFileInterface() = 0;
    /**
     * Used to create a file. The first parameter to this function is a text string
     * that tells you where the binary data is physically to be located – you should
     * store the actual database data using the File class from File.h. 
     * The second parameter to the Create function tells you the type of the file.
     * Finally, the last parameter to Create is a dummy parameter that you won’t use
     * for this assignment, but you will use for assignment two.
     * The return value from Create is a 1 on success and a zero on failure.
     */
    virtual int Create(const char *fpath, fType file_type, void *startup) = 0;
    /**
     * This function assumes that the DBFile already exists and has previously 
     * been created and then closed. The one parameter to this function is simply 
     * the physical location of the file. If your DBFile needs to know anything else 
     * about itself, it should have written this to an auxiliary text file that it will
     * also open at startup. The return value is a 1 on success and a zero on failure.
     */
    virtual int Open(const char *fpath) = 0;
    /**
     * Close simply closes the file. The return value is a 1 on success and a zero on failure.
     */
    virtual int Close() = 0;
    /**
     * Load function bulk loads the DBFile instance from a text file, appending new data
     * to it using the SuckNextRecord function from Record.h. The character string passed
     * to Load is the name of the data file to bulk load.
     */
    virtual void Load(Schema &myschema, const char *loadpath) = 0;
    /**
     * Each DBFile instance has a “pointer” to the current record in the file.
     * By default, this pointer is at the first record in the file, 
     * but it can move in response to record retrievals. The following function forces 
     * the pointer to correspond to the first record in the file.
     */
    virtual void MoveFirst() = 0;
    /**
     * In order to add records to the file, the function Add is used. In the case of the 
     * unordered heap file that you are implementing in this assignment, this function 
     * simply adds the new record to the end of the file.
     */
    virtual void Add(Record &addme) = 0;
    /**
     * GetNext simply gets the next record from the file and returns it to the user,
     * where “next” is defined to be relative to the current l ocation of the pointer.
     * After the function call returns, the pointer into the file is incremented,
     * so a subsequent call to GetNext won’t return the same record twice.
     * The return value is an integer whose value is zero if and only if there is not a valid record returned from the function call (which will be the case, for example, if the last record in the file has already been returned).
     */
    virtual int GetNext(Record &fetchme) = 0;
    /**
     * GetNext also accepts a selection predicate (this is a conjunctive normal form expression).
     * It returns the next record in the file that is accepted by the selection predicate.
     * The literal record is used to check the selection predicate, and is created when the
     * parse tree for the CNF is processed.
     */
    virtual int GetNext(Record &fetchme, CNF &cnf, Record &literal) = 0;
};
#endif
