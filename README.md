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

# How to Start

1. [install bazel](https://docs.bazel.build/versions/main/install-ubuntu.html)

```
sudo apt install apt-transport-https curl gnupg
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
```

```
sudo apt update && sudo apt install bazel
```

2. build & test

* Run vscode task: build bazel target / test bazel target
* Select Target 