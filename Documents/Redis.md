## Redis

[Documentation](https://redis.io/documentation) 

[TOC]

# What is Redis?

1. Redis is an **in-memory,** **key-value** **store**.

- **In-memory store**: Redis keeps the data in the cache and it does not write to the disk. This makes reading/writing data very fast. (However, Redis has an option to write data to the disk)
- **Key-value store**: Redis can store data as key-value pairs.

2. It is a [No-SQL](https://en.wikipedia.org/wiki/NoSQL) database.

3. Uses [data structures](https://redis.io/topics/data-types-intro) to store data.

4. Interaction with data is command-based.

> Redis is an open source (BSD licensed), in-memory data structure store, used as a database, cache and message broker. It supports data structures such as **strings, hashes, lists, sets, sorted sets** with range queries, bitmaps, hyperloglogs, geospatial indexes with radius queries and streams. Redis has built-in replication, Lua scripting, LRU eviction, transactions and different levels of on-disk persistence, and provides high availability via Redis Sentinel and automatic partitioning with Redis Cluster.

> You can run atomic operations on these types, like appending to a string; incrementing the value in a hash; pushing an element to a list; computing set intersection, union and difference; or getting the member with highest ranking in a sorted set.

> In order to achieve its outstanding performance, Redis works with an in-memory dataset. Depending on your use case, you can persist it either by dumping the dataset to disk every once in a while, or by appending each command to a log. Persistence can be optionally disabled, if you just need a feature-rich, networked, in-memory cache.

> Redis also supports trivial-to-setup master-slave asynchronous replication, with very fast non-blocking first synchronization, auto-reconnection with partial resynchronization on net split.

>Other features include:

    Transactions
    Pub/Sub
    Lua scripting
    Keys with a limited time-to-live
    LRU eviction of keys
    Automatic failover
    You can use Redis from most programming languages out there.

> Redis is written in ANSI C and works in most POSIX systems like Linux, *BSD, OS X without external dependencies. Linux and OS X are the two operating systems where Redis is developed and tested the most, and we recommend using Linux for deploying. Redis may work in Solaris-derived systems like SmartOS, but the support is best effort. There is no official support for Windows builds.


## Redis安装及配置

------

1. 用docker运行Redis

    > `docker pull redis`
    > `docker run -d --name redis -p 6379:6379 redis`  
    > `docker exec -it redis redis-cli`

2. Linux安装

    > 1. 确保Linux已经[安装gcc](https://blog.csdn.net/qq_33571814/article/details/82380215)
    > 2. 下载Redis
    >    `wget http://download.redis.io/releases/redis-4.0.1.tar.gz`
    > 3. 解压
    >    `tar -zxvf redis-4.0.1.tar.gz`
    > 4. 进入目录后编译
    >    `cd redis-4.0.1`
    >    `make MALLOC=libc`
    > 5. 安装
    >    `make PREFIX=/usr/local/redis install` #指定安装目录为/usr/local/redis
    > 6. 启动
    >    `/usr/local/redis/bin/redis-server`

3. Redis配置
    > 1. 进入解压的Redis目录，将redis.conf复制到安装文件的目录下
    >    `cp redis.conf /usr/local/redis`
    > 2. 启动自定义配置的Redis
    >    `/usr/local/redis/bin/redis-server /usr/local/redis/redis.conf`

4. 配置详解

    > - daemonize ： 默认为no，修改为yes启用守护线程
    > - port ：设定端口号，默认为6379
    > - bind ：绑定IP地址
    > - databases ：数据库数量，默认16
    > - save <second> <changes> ：指定多少时间、有多少次更新操作，就将数据同步到数据文件
    >   `#redis默认配置有三个条件，满足一个即进行持久化`
    >   `save 900 1` #900s有1个更改
    >   `save 300 10` #300s有10个更改
    >   `save 60 10000` #60s有10000更改
    > - dbfilename ：指定本地数据库的文件名，默认为dump.rdb
    > - dir ：指定本地数据库的存放目录，默认为./当前文件夹
    > - requirepass ：设置密码，默认关闭
    >   `redis -cli -h host -p port -a password`

5. Redis关闭

    > - 使用kill命令 (非正常关闭，数据易丢失)
    >   `ps -ef|grep -i redis`
    >   `kill -9 PID`
    > - 正常关闭
    >   `redis-cli shutdown`

## Redis常用命令

------

> Redis五种数据类型：string、hash、list、set、zset

### 公用命令

> - DEL key
> - DUMP key：序列化给定key，返回被序列化的值
> - EXISTS key：检查key是否存在
> - EXPIRE key second：为key设定过期时间
> - TTL key：返回key剩余时间
> - PERSIST key：移除key的过期时间，key将持久保存
> - KEY pattern：查询所有符号给定模式的key
> - RANDOM key：随机返回一个key
> - RANAME key newkey：修改key的名称
> - MOVE key db：移动key至指定数据库中
> - TYPE key：返回key所储存的值的类型

### EXPIRE key second的使用场景： 

1. 限时的优惠活动 

2. 网站数据缓存 

3. 手机验证码 

4. 限制网站访客频率

## key的命名规范

1. key不要太长，尽量不要超过1024字节。不仅消耗内存，也会降低查找的效率

2. key不要太短，太短可读性会降低

3. 在一个项目中，key最好使用统一的命名模式，如user:123:password

4. key区分大小写

## String 

### String特点：

string类型是二进制安全的，redis的string可以包含任何数据，如图像、序列化对象。一个键最多能存储512MB。

二进制安全是指，在传输数据的时候，能保证二进制数据的信息安全，也就是不会被篡改、破译；如果被攻击，能够及时检测出来 。

### String 的常见命令

- **set** **key_name value**：命令不区分大小写，但是key_name区分大小写
- **SETNX key value**：当key不存在时设置key的值。（SET if Not eXists）
- **get key_name**
- GETRANGE key start end：获取key中字符串的子字符串，从start开始，end结束
- MGET key1 [key2 …]：获取多个key
- GETSET KEY_NAME VALUE：设定key的值，并返回key的旧值。当key不存在，返回nil
- STRLEN key：返回key所存储的字符串的长度
- **INCR KEY_NAME** ：INCR命令key中存储的值+1,如果不存在key，则key中的值话先被初始化为0再加1
- **INCRBY KEY_NAME** 增量
- **DECR KEY_NAME VALUE**：key中的值自减一
- **DECRBY KEY_NAME VALUE**
- append key_name value：字符串拼接，追加至末尾，如果不存在，为其赋值

### **String应用场景：**

1. String通常用于保存单个字符串或JSON字符串数据 
2. String是二进制安全的，所以可以把保密要求高的图片文件内容作为字符串来存储 
3. 计数器：常规Key-Value缓存应用，如微博数、粉丝数。INCR本身就具有原子性特性，所以不会有线程安全问题

## Hashes

Hashes, which are maps composed of fields associated with values. Both the field and the value are strings. This is very similar to Ruby or Python hashes.

### Hash commands

#### HGETALL key

Returns all fields and values of the hash stored at `key`. In the returned value, every field name is followed by its value, so the length of the reply is twice the size of the hash.                  

#### HSETNX key field value

Sets `field` in the hash stored at `key` to `value`, only if `field` does not yet exist. If `key` does not exist, a new key holding a hash is created. If `field` already exists, this operation has no effect.

#### HVALS key

> **Time complexity:** O(N) where N is the size of the hash.

Returns all values in the hash stored at `key`.

## List

### List commands

#### LPUSH key element [element ...]

Insert all the specified values at the head of the list stored at `key`. If `key` does not exist, it is created as empty list before performing the push operations. When `key` holds a value that is not a list, an error is returned.

It is possible to push multiple elements using a single command call just specifying multiple arguments at the end of the command. Elements are inserted one after the other to the head of the list, from the leftmost element to the rightmost element. So for instance the command `LPUSH mylist a b c` will result into a list containing `c` as first element, `b` as second element and `a` as third element.

```sql
127.0.0.1:6379> lpush mj1 "I love you"
(integer) 1
127.0.0.1:6379> lpop mj1
"I love you"
```

#### LRANGE key start stop

Returns the specified elements of the list stored at `key`. The offsets `start` and `stop` are zero-based indexes, with `0` being the first element of the list (the head of the list), `1` being the next element and so on.

These offsets can also be negative numbers indicating offsets starting at the end of the list. For example, `-1` is the last element of the list, `-2` the penultimate, and so on.

```sql
127.0.0.1:6379> rpush mj1 "I love you forver"
(integer) 1
127.0.0.1:6379> lrange mj1 0 -1
1) "I love you forver"
127.0.0.1:6379> lrange mj1 0 -1
1) "I love you forver"
127.0.0.1:6379> lrange mj1 0 -1
1) "I love you forver"
127.0.0.1:6379> lindex mj1 0
"I love you forver"
```

#### BLPOP key [key ...] timeout

[BLPOP](https://redis.io/commands/blpop) is a blocking list pop primitive. It is the blocking version of [LPOP](https://redis.io/commands/lpop) because it blocks the connection when there are no elements to pop from any of the given lists. An element is popped from the head of the first list that is non-empty, with the given keys being checked in the order that they are given.

```sql
blpop l1 200
1) "l1"
2) "3"
(11.28s)

lpush l1 3
(integer) 1
```

#### LTRIM key start stop

```
LPUSH mylist someelement
LTRIM mylist 0 99
```

This pair of commands will push a new element on the list, while making sure that the list will not grow larger than 100 elements. **This is very useful when using Redis to store logs** for example. It is important to note that when used in this way [LTRIM](https://redis.io/commands/ltrim) is an O(1) operation because in the average case just one element is removed from the tail of the list.

```sql
127.0.0.1:6379> RPUSH mylist "one"
(integer) 2
127.0.0.1:6379> rpush mylist "two"
(integer) 3
127.0.0.1:6379> RPUSH mylist "three"
(integer) 4
127.0.0.1:6379> LTRIM mylist 1 -1
OK
127.0.0.1:6379> LRANGE mylist 0 -1
1) "one"
2) "two"
3) "three"
127.0.0.1:6379> LRANGE mylist 0 -1
1) "one"
2) "two"
3) "three"
127.0.0.1:6379> LTRIM mylist 1 -1
OK
127.0.0.1:6379> LRANGE mylist 0 -1
1) "two"
2) "three"
```

#### LSET key index element

Sets the list element at `index` to `element`. For more information on the `index` argument, see [LINDEX](https://redis.io/commands/lindex).

An error is returned for out of range indexes.

```sql
127.0.0.1:6379> RPUSH mylist "one"
(integer) 3
127.0.0.1:6379> RPUSH mylist "two"
(integer) 4
127.0.0.1:6379> lset mylist -2 "five"
OK
127.0.0.1:6379> lrange mylist 0 -1
1) "two"
2) "three"
3) "five"
4) "two"
```

#### LINSERT key BEFORE|AFTER pivot element

Inserts `element` in the list stored at `key` either before or after the reference value `pivot`.

When `key` does not exist, it is considered an empty list and no operation is performed.

An error is returned when `key` exists but does not hold a list value.

```sql
linsert mylist BEFORE "two" "six"
(integer) 5
127.0.0.1:6379> lrange mylist 0 -1
1) "six"
2) "two"
3) "three"
4) "five"
5) "two"
```

#### RPOPLPUSH source destination

Atomically returns and removes the last element (tail) of the list stored at `source`, and pushes the element at the first element (head) of the list stored at `destination`.

For example: consider `source` holding the list `a,b,c`, and `destination` holding the list `x,y,z`. Executing [RPOPLPUSH](https://redis.io/commands/rpoplpush) results in `source` holding `a,b` and `destination` holding `c,x,y,z`.

If `source` does not exist, the value `nil` is returned and no operation is performed. If `source` and `destination` are the same, the operation is equivalent to removing the last element from the list and pushing it as first element of the list, so it can be considered as a list rotation command.

#####  Pattern: Reliable queue

Redis is often used as a messaging server to implement processing of background jobs or other kinds of messaging tasks. A simple form of queue is often obtained pushing values into a list in the producer side, and waiting for this values in the consumer side using [RPOP](https://redis.io/commands/rpop) (using polling), or [BRPOP](https://redis.io/commands/brpop) if the client is better served by a blocking operation.

#####  Pattern: Circular list

Using [RPOPLPUSH](https://redis.io/commands/rpoplpush) with the same source and destination key, a client can visit all the elements of an N-elements list, one after the other, in O(N) without transferring the full list from the server to the client using a single [LRANGE](https://redis.io/commands/lrange) operation.

The above pattern works even if the following two conditions:

- There are multiple clients rotating the list: they'll fetch different elements, until all the elements of the list are visited, and the process restarts.

- Even if other clients are actively pushing new items at the end of the list. 

  An example is a monitoring system that must check that a set of web sites are reachable, with the smallest delay possible, using a number of parallel workers.

```sql
127.0.0.1:6379> RPUSH mylist "one"
(integer) 6
127.0.0.1:6379> RPUSH mylist "two"
(integer) 7
127.0.0.1:6379> RPUSH mylist "three"
(integer) 8
127.0.0.1:6379> RPOPLPUSH mylist myotherlist
"three"
127.0.0.1:6379> LRANGE mylist 0 -1
1) "six"
2) "two"
3) "three"
4) "five"
5) "two"
6) "one"
7) "two"
127.0.0.1:6379> lrange myotherlist 0 -1
1) "three"
127.0.0.1:6379>
```

## Set 

#### SET key value [EX seconds|PX milliseconds] [NX|XX] [KEEPTTL]

```shell
127.0.0.1:6379> SET mykey "Hello"
OK
127.0.0.1:6379> get mykey
"Hello"
127.0.0.1:6379>  SET anotherkey "will expire in a minute" EX 60
OK
127.0.0.1:6379> keys *
```

#### SCARD key

Returns the set cardinality (number of elements) of the set stored at `key`.

```
127.0.0.1:6379> type myset
set
127.0.0.1:6379> scard myset
(integer) 2
127.0.0.1:6379> scard mj
(error) WRONGTYPE Operation against a key holding the wrong kind of value
```

#### SISMEMBER key member

```
sismember myset "one"
(integer) 1
127.0.0.1:6379> sismember myset "two"
(integer) 0
127.0.0.1:6379> SISMEMBER myset "one"
(integer) 1
```

#### SRANDMEMBER key [count]

```
127.0.0.1:6379> srandmember myset 2
1) "Hello"
2) "one"
127.0.0.1:6379>
```

#####  Distribution of returned elements

The distribution of the returned elements is far from perfect when the number of elements in the set is small, this is due to the fact that we used an approximated random element function that does not really guarantees good distribution.

The algorithm used, that is implemented inside dict.c, samples the hash table buckets to find a non-empty one. **Once a non empty bucket is found, since we use chaining in our hash table implementation, the number of elements inside the bucket is checked and a random element is selected.**

This means that if you have two non-empty buckets in the entire hash table, and one has three elements while one has just one, the element that is alone in its bucket will be returned with much higher probability.

#### SREM key member [member ...]

```shell
127.0.0.1:6379> SMEMBERS myset
1) "Hello"
2) "World"
3) "two"
4) "one"
5) "three"
127.0.0.1:6379> SREM myset one
(integer) 1
127.0.0.1:6379> SMEMBERS myset
1) "Hello"
2) "World"
3) "two"
4) "three"
```

#### SCAN cursor [MATCH pattern] [COUNT count] [TYPE type]	

Since these commands allow for incremental iteration, returning only a small number of elements per call, they can be used in production without the downside of commands like [KEYS](https://redis.io/commands/keys) or [SMEMBERS](https://redis.io/commands/smembers) that may block the server for a long time (even several seconds) when called against big collections of keys or elements.

However while blocking commands like [SMEMBERS](https://redis.io/commands/smembers) are able to provide all the elements that are part of a Set in a given moment, The SCAN family of commands only offer limited guarantees about the returned elements since the collection that we incrementally iterate can change during the iteration process.

```shell
127.0.0.1:6379> sadd myset 1 2 3 foo foobar feelsgood
(integer) 6
127.0.0.1:6379> sscan myset 0 match f*
1) "0"
2) 1) "foobar"
   2) "foo"
   3) "feelsgood"
127.0.0.1:6379> scan 0 MATCH *mj*
1) "9"
2) 1) "mj1"
   2) "list_mj"
   3) "mj"
   4) "mj520"
   5) "zset-mj"
   
127.0.0.1:6379> scan 0 MATCH *mj* count 4
1) "10"
2) 1) "mj1"
   2) "list_mj"
   3) "mj"
   4) "mj520"
```

#  [Redis debugging guide](https://redis.io/topics/debugging#attaching-gdb-to-a-running-process)

## Attaching GDB to a running process

```
$ redis-cli info | grep process_id
process_id:58414
```

In the above example the process ID is **58414**.

- Login into your Redis server.

- (Optional but recommended) Start **screen** or **tmux** or any other program that will make sure that your GDB session will not be closed if your ssh connection will timeout. If you don't know what screen is do yourself a favor and [Read this article](http://www.linuxjournal.com/article/6340)

- Attach GDB to the running Redis server typing:

  gdb `` ``

  For example: gdb /usr/local/bin/redis-server 58414

GDB will start and will attach to the running server printing something like the following:

## Obtaining the core file

The next step is to generate the core dump, that is the image of the memory of the running Redis process. This is performed using the `gcore` command:

```
(gdb) gcore
Saved corefile core.58414
```



## [VSCode, MacOS Catalina - doesn't stop on breakpoints on C/C++ debug](https://stackoverflow.com/questions/58329611/vscode-macos-catalina-doesnt-stop-on-breakpoints-on-c-c-debug)

