/**
 * @brief Acts as a factory class to create DBFile based on type heap, sorted
 * and tree provided. * 
 */
#ifndef DBFILE_H
#define DBFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "DBFileInterface.h"
#include "ComparisonEngine.h"
#include "Defs.h"
#include "DBFileHeap.h"

// stub DBFile header..replace it with your own DBFile.h 

class DBFile {
private:
    DBFileInterface * oDBFileInterface;
	void setFileType(fType f_type, const char *f_path);
	fType getFileType(const char *f_path);
	int setDBFileInstance(fType f_type);

public:
	DBFile (); 

	int Create (const char *fpath, fType file_type, void *startup);
	int Open (const char *fpath);
	int Close ();

	void Load (Schema &myschema, const char *loadpath);

	void MoveFirst ();
	void Add (Record &addme);
	int GetNext (Record &fetchme);
	int GetNext (Record &fetchme, CNF &cnf, Record &literal);

};
#endif
