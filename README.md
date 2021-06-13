# directory-db
db of directory semantics

# Data Model

data outline:
```
: db meta info
key1: value1
key1,key2: value2
key1,key2,key3: value3
key1,key2,key4: value4
```

modify:
```
get/put/scan/delete
```

prefix semantics
* for every key in db, there exists a parent key

> delete key1,key2 will delete three record(key1,key2/key1,key2,key3/key1,key2,key4)


# TodoList

 * [ ] TableBuilder: used to flush memtable into table
 * [ ] Table: ordered readonly key value set, associated to the table
 * [ ] Iterator: Iterate memtable and Table
 * [ ] VersionEdit: flush tables to create a version edit
 * [ ] Version: compact VersionEdit into a VersionSet