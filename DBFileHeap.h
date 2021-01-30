/**
 * @brief A Heap Implmentation of DBFIle. Creates an unordered file of records,
 * where new records simply go to the end of file. 
 * 
 * 
 */
#ifndef DBFileHeap_H
#define DBFileHeap_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "DBFileInterface.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"

class DBFileHeap : public DBFileInterface
{
    File oFile;
    Page oPage;
    off_t pageNumber;

public:
    DBFileHeap();

    int Create(const char *fpath, fType file_type, void *startup);
    int Open(const char *fpath);
    int Close();

    void Load(Schema &myschema, const char *loadpath);

    void MoveFirst();
    void Add(Record &addme);
    int GetNext(Record &fetchme);
    int GetNext(Record &fetchme, CNF &cnf, Record &literal);
};
#endif
