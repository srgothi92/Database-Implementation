#include "DBFileHeap.h"
#include "iostream"
#include "fstream"
#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"
#include <string>

DBFileHeap::DBFileHeap() : oFile(), oPage(), pageNumber(0)
{
}
/**
 * @brief Erases an existing file and creates a new File with Heap type record storage.
 * @param f_path path of file that needs to be created.
 * @return 1 on success and 0 on failure.
 */
int DBFileHeap::Create(const char *f_path, fType f_type, void *startup)
{
  try
  {
    oFile.Open(0, f_path);
    cout << "File created \n";
  }
  catch (...)
  {
    cerr << "DBFileHeap create error. \n";
    return 0;
  }
  return 1;
}
/** 
 * @brief Loads all record from .tbl file to Heap file.
 * @param f_schema schema of file to be loaded.
 * @param loadpath path of file to be loaded.
*/
void DBFileHeap::Load(Schema &f_schema, const char *loadpath)
{
  // Open file in read mode
  FILE *loadFile = fopen(loadpath, "r");
  try
  {
    if (loadFile == NULL)
    {
      throw("File:" + std::string(loadpath) + " error");
    }
    Record record;
    Page tempPage;
    int counter = 0;
    while (record.SuckNextRecord(&f_schema, loadFile) == 1)
    {
      int pageFull = tempPage.Append(&record);
      if (pageFull == 0)
      {
        oFile.AddPage(&tempPage, pageNumber++);
        tempPage.EmptyItOut();
        tempPage.Append(&record);
      }

      counter++;
      if (counter % 10000 == 0)
      {
        cerr << "Record Counter: " << counter << "\n";
      }
    }
    // add last page to the file.
    oFile.AddPage(&tempPage, pageNumber++);
    cout << "Records " + std::to_string(counter) + "added to file \n";
  }
  catch (exception e)
  {
    cerr << e.what();
    fclose(loadFile);
  }
}
/**
 * @brief Open the existing heap file.
 * @param f_path Path of file to open.
 * @return 1 on success and 0 on failure.
 */
int DBFileHeap::Open(const char *f_path)
{
  try
  {
    oFile.Open(1, f_path);
    cout << "File: " << std::string(f_path) << " opened. \n";
  }
  catch (...)
  {
    cerr << "File " << std::string(f_path) << " open error. \n";
    return 0;
  }
  return 1;
}
/** 
 * @brief Move to the first record in file.
*/
void DBFileHeap::MoveFirst()
{
  pageNumber = 0;
  if (oFile.GetLength() != 0)
  {
    oFile.GetPage(&oPage, pageNumber);
    cout << "Moved to first Page \n";
  }
  else
  {
    cout << "No Pages available to MoveFirst \n";
  }
}
/**
 * @brief Close the open heap file.
 * @return 1 on success and 0 on failure.
 */
int DBFileHeap::Close()
{
  try
  {
    int fileLength = oFile.Close();
    return 1;
  }
  catch (...)
  {
    cout << "Close error, file does not exist \n";
    return 0;
  }
}
/**
 * @brief Adds a new record to the end of file.
 * @param rec record that needs to be inserted.
 */
void DBFileHeap::Add(Record &rec)
{
  Page tempPage;
  off_t fileSize = oFile.GetLength();
  if (fileSize != 0)
  {
    oFile.GetPage(&tempPage, oFile.GetLength() - 2);
  }
  else
  {
    fileSize = 2;
  }
  int pageFull = tempPage.Append(&rec);
  if (pageFull == 0)
  {
    tempPage.EmptyItOut();
    tempPage.Append(&rec);
    oFile.AddPage(&tempPage, fileSize - 1);
  }
  else
  {
    oFile.AddPage(&tempPage, fileSize - 2);
  }
}
/**
 * @brief Gets next record from the file and returns to user, where "next" is defined
 * relative to the current pointer. After return pointer in file is increment to next record.
 * @param fetchme Pointer to which record needs to returned.
 * @return 1 on success and 0 on failure.
 */
int DBFileHeap::GetNext(Record &fetchme)
{
  if (0 == oPage.GetFirst(&fetchme))
  {
    ++pageNumber;
    if (pageNumber >= oFile.GetLength() - 1)
    {
      return 0;
    }
    oFile.GetPage(&oPage, pageNumber);
    oPage.GetFirst(&fetchme);
  }
  return 1;
}
/**
 * @brief Gets next record from the file based on selection predicate (a conjuctive normal form expression),
 * where "next" is defined relative to the current pointer in selection predicate. After return pointer in file is increment to next record.
 * @param fetchme Pointer to which record needs to returned.
 * @param cnf Conjuctive normal form expression to filter the records.
 * @param literal 
 * @return 1 on success and 0 on failure.
 */
int DBFileHeap::GetNext(Record &fetchme, CNF &cnf, Record &literal)
{
  ComparisonEngine comp;
  while (GetNext(fetchme) == 1)
  {
    if (comp.Compare(&fetchme, &literal, &cnf) == 1)
    {
      return 1;
    }
  }
  return 0;
}
