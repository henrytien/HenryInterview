# Redis

[TOC]

## Redis简介
Redis：开源、免费、高性能、K-V数据库、内存数据库、非关系型数据库，支持持久化、集群和事务

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
127.0.0.1:6379>
```







