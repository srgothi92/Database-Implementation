
#include "iostream"
#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <fstream>


DBFile::DBFile() : oDBFileInterface(NULL)
{
}

void DBFile::setFileType(fType f_type, const char *f_path)
{
    string metafileName;
    metafileName.append(f_path);
    metafileName.append(".meta");
    ofstream metafile;
    metafile.open(metafileName.c_str());
    metafile << f_type << endl;
    metafile.close();
    cout << "file type is " << f_type << endl;
}

fType DBFile::getFileType(const char *f_path)
{
    int t;
    string metafileName;
    metafileName.append(f_path);
    metafileName.append(".meta");
    ifstream metafile;
    metafile.open(metafileName.c_str());
    metafile >> t;
    fType dbfileType = (fType)t;
    metafile.close();
    return dbfileType;
}

int DBFile::setDBFileInstance(fType f_type)
{
    switch (f_type)
    {
    case heap:
        cout << "Created Instance of DBFileHeap \n";
        oDBFileInterface = new DBFileHeap();
        return 1;
    case sorted:
    case tree:
        cout << "Not yet Implemented, Please use heap \n";
    default:
        cout << "Unknown option.\n";
    }
    return 0;
}

int DBFile::Create(const char *f_path, fType f_type, void *startup)
{
    setFileType(f_type, f_path);
    int isCreated  = setDBFileInstance(f_type);
    if(isCreated == 0) {
        return 0;
    }
    return oDBFileInterface->Create(f_path, f_type, startup);
}

void DBFile::Load(Schema &f_schema, const char *loadpath)
{
    oDBFileInterface->Load(f_schema, loadpath);
}

int DBFile::Open(const char *f_path)
{
    fType f_type = getFileType(f_path);
    setDBFileInstance(f_type);
    return oDBFileInterface->Open(f_path);
}

void DBFile::MoveFirst()
{
    oDBFileInterface->MoveFirst();
}

int DBFile::Close()
{
    if (oDBFileInterface != NULL)
    {
        int closeStatus = oDBFileInterface->Close();
        delete oDBFileInterface;
        return closeStatus;
    }
    return 0;
}

void DBFile::Add(Record &rec)
{
    oDBFileInterface->Add(rec);
}

int DBFile::GetNext(Record &fetchme)
{
    return oDBFileInterface->GetNext(fetchme);
}

int DBFile::GetNext(Record &fetchme, CNF &cnf, Record &literal)
{
    return oDBFileInterface->GetNext(fetchme, cnf, literal);
}
