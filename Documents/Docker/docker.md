# Docker Tutorial for Beginners

`cat /etc/*release*`

```shell
cat /etc/*release*
CentOS Linux release 7.6.1810 (Core)
Derived from Red Hat Enterprise Linux 7.6 (Source)
NAME="CentOS Linux"
VERSION="7 (Core)"
ID="centos"
ID_LIKE="rhel fedora"
VERSION_ID="7"
PRETTY_NAME="CentOS Linux 7 (Core)"
ANSI_COLOR="0;31"
CPE_NAME="cpe:/o:centos:centos:7"
HOME_URL="https://www.centos.org/"
BUG_REPORT_URL="https://bugs.centos.org/"

CENTOS_MANTISBT_PROJECT="CentOS-7"
CENTOS_MANTISBT_PROJECT_VERSION="7"
REDHAT_SUPPORT_PRODUCT="centos"
REDHAT_SUPPORT_PRODUCT_VERSION="7"

CentOS Linux release 7.6.1810 (Core)
CentOS Linux release 7.6.1810 (Core)
cpe:/o:centos:centos:7
```

```shell
docker --version
Docker version 19.03.8, build afacb8b
```

# docker exec

## Description

Run a command in a running container

## Usage

```dockerfile
docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
```

# docker run

## Description

Run a command in a new container

## Usage

```none
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```

## Options

| Name, shorthand           | Default   | Description                                                  |
| ------------------------- | --------- | :----------------------------------------------------------- |
| `--add-host`              |           | Add a custom host-to-IP mapping (host:ip)                    |
| `--attach , -a`           |           | Attach to STDIN, STDOUT or STDERR                            |
| `--blkio-weight`          |           | Block IO (relative weight), between 10 and 1000, or 0 to disable (default 0) |
| `--blkio-weight-device`   |           | Block IO weight (relative device weight)                     |
| `--cap-add`               |           | Add Linux capabilities                                       |
| `--cap-drop`              |           | Drop Linux capabilities                                      |
| `--cgroup-parent`         |           | Optional parent cgroup for the container                     |
| `--cidfile`               |           | Write the container ID to the file                           |
| `--cpu-count`             |           | CPU count (Windows only)                                     |
| `--cpu-percent`           |           | CPU percent (Windows only)                                   |
| `--cpu-period`            |           | Limit CPU CFS (Completely Fair Scheduler) period             |
| `--cpu-quota`             |           | Limit CPU CFS (Completely Fair Scheduler) quota              |
| `--cpu-rt-period`         |           | [**API 1.25+**](https://docs.docker.com/engine/api/v1.25/) Limit CPU real-time period in microseconds |
| `--cpu-rt-runtime`        |           | [**API 1.25+**](https://docs.docker.com/engine/api/v1.25/) Limit CPU real-time runtime in microseconds |
| `--cpu-shares , -c`       |           | CPU shares (relative weight)                                 |
| `--cpus`                  |           | [**API 1.25+**](https://docs.docker.com/engine/api/v1.25/) Number of CPUs |
| `--cpuset-cpus`           |           | CPUs in which to allow execution (0-3, 0,1)                  |
| `--cpuset-mems`           |           | MEMs in which to allow execution (0-3, 0,1)                  |
| `--detach , -d`           |           | Run container in background and print container ID           |
| `--detach-keys`           |           | Override the key sequence for detaching a container          |
| `--device`                |           | Add a host device to the container                           |
| `--device-cgroup-rule`    |           | Add a rule to the cgroup allowed devices list                |
| `--device-read-bps`       |           | Limit read rate (bytes per second) from a device             |
| `--device-read-iops`      |           | Limit read rate (IO per second) from a device                |
| `--device-write-bps`      |           | Limit write rate (bytes per second) to a device              |
| `--device-write-iops`     |           | Limit write rate (IO per second) to a device                 |
| `--disable-content-trust` | `true`    | Skip image verification                                      |
| `--dns`                   |           | Set custom DNS servers                                       |
| `--dns-opt`               |           | Set DNS options                                              |
| `--dns-option`            |           | Set DNS options                                              |
| `--dns-search`            |           | Set custom DNS search domains                                |
| `--domainname`            |           | Container NIS domain name                                    |
| `--entrypoint`            |           | Overwrite the default ENTRYPOINT of the image                |
| `--env , -e`              |           | Set environment variables                                    |
| `--env-file`              |           | Read in a file of environment variables                      |
| `--expose`                |           | Expose a port or a range of ports                            |
| `--gpus`                  |           | [**API 1.40+**](https://docs.docker.com/engine/api/v1.40/) GPU devices to add to the container (‘all’ to pass all GPUs) |
| `--group-add`             |           | Add additional groups to join                                |
| `--health-cmd`            |           | Command to run to check health                               |
| `--health-interval`       |           | Time between running the check (ms\|s\|m\|h) (default 0s)    |
| `--health-retries`        |           | Consecutive failures needed to report unhealthy              |
| `--health-start-period`   |           | [**API 1.29+**](https://docs.docker.com/engine/api/v1.29/) Start period for the container to initialize before starting health-retries countdown (ms\|s\|m\|h) (default 0s) |
| `--health-timeout`        |           | Maximum time to allow one check to run (ms\|s\|m\|h) (default 0s) |
| `--help`                  |           | Print usage                                                  |
| `--hostname , -h`         |           | Container host name                                          |
| `--init`                  |           | [**API 1.25+**](https://docs.docker.com/engine/api/v1.25/) Run an init inside the container that forwards signals and reaps processes |
| `--interactive , -i`      |           | Keep STDIN open even if not attached                         |
| `--io-maxbandwidth`       |           | Maximum IO bandwidth limit for the system drive (Windows only) |
| `--io-maxiops`            |           | Maximum IOps limit for the system drive (Windows only)       |
| `--ip`                    |           | IPv4 address (e.g., 172.30.100.104)                          |
| `--ip6`                   |           | IPv6 address (e.g., 2001:db8::33)                            |
| `--ipc`                   |           | IPC mode to use                                              |
| `--isolation`             |           | Container isolation technology                               |
| `--kernel-memory`         |           | Kernel memory limit                                          |
| `--label , -l`            |           | Set meta data on a container                                 |
| `--label-file`            |           | Read in a line delimited file of labels                      |
| `--link`                  |           | Add link to another container                                |
| `--link-local-ip`         |           | Container IPv4/IPv6 link-local addresses                     |
| `--log-driver`            |           | Logging driver for the container                             |
| `--log-opt`               |           | Log driver options                                           |
| `--mac-address`           |           | Container MAC address (e.g., 92:d0:c6:0a:29:33)              |
| `--memory , -m`           |           | Memory limit                                                 |
| `--memory-reservation`    |           | Memory soft limit                                            |
| `--memory-swap`           |           | Swap limit equal to memory plus swap: ‘-1’ to enable unlimited swap |
| `--memory-swappiness`     | `-1`      | Tune container memory swappiness (0 to 100)                  |
| `--mount`                 |           | Attach a filesystem mount to the container                   |
| `--name`                  |           | Assign a name to the container                               |
| `--net`                   |           | Connect a container to a network                             |
| `--net-alias`             |           | Add network-scoped alias for the container                   |
| `--network`               |           | Connect a container to a network                             |
| `--network-alias`         |           | Add network-scoped alias for the container                   |
| `--no-healthcheck`        |           | Disable any container-specified HEALTHCHECK                  |
| `--oom-kill-disable`      |           | Disable OOM Killer                                           |
| `--oom-score-adj`         |           | Tune host’s OOM preferences (-1000 to 1000)                  |
| `--pid`                   |           | PID namespace to use                                         |
| `--pids-limit`            |           | Tune container pids limit (set -1 for unlimited)             |
| `--platform`              |           | [**experimental (daemon)**](https://docs.docker.com/engine/reference/commandline/dockerd/#daemon-configuration-file)[**API 1.32+**](https://docs.docker.com/engine/api/v1.32/) Set platform if server is multi-platform capable |
| `--privileged`            |           | Give extended privileges to this container                   |
| `--publish , -p`          |           | Publish a container’s port(s) to the host                    |
| `--publish-all , -P`      |           | Publish all exposed ports to random ports                    |
| `--read-only`             |           | Mount the container’s root filesystem as read only           |
| `--restart`               | `no`      | Restart policy to apply when a container exits               |
| `--rm`                    |           | Automatically remove the container when it exits             |
| `--runtime`               |           | Runtime to use for this container                            |
| `--security-opt`          |           | Security Options                                             |
| `--shm-size`              |           | Size of /dev/shm                                             |
| `--sig-proxy`             | `true`    | Proxy received signals to the process                        |
| `--stop-signal`           | `SIGTERM` | Signal to stop a container                                   |
| `--stop-timeout`          |           | [**API 1.25+**](https://docs.docker.com/engine/api/v1.25/) Timeout (in seconds) to stop a container |
| `--storage-opt`           |           | Storage driver options for the container                     |
| `--sysctl`                |           | Sysctl options                                               |
| `--tmpfs`                 |           | Mount a tmpfs directory                                      |
| `--tty , -t`              |           | Allocate a pseudo-TTY                                        |
| `--ulimit`                |           | Ulimit options                                               |
| `--user , -u`             |           | Username or UID (format: <name\|uid>[:<group\|gid>])         |
| `--userns`                |           | User namespace to use                                        |
| `--uts`                   |           | UTS namespace to use                                         |
| `--volume , -v`           |           | Bind mount a volume                                          |
| `--volume-driver`         |           | Optional volume driver for the container                     |
| `--volumes-from`          |           | Mount volumes from the specified container(s)                |
| `--workdir , -w`          |           | Working directory inside the container                       |



## Examples[🔗](https://docs.docker.com/engine/reference/commandline/run/#examples)

### Full container capabilities (--privileged)

```shell
$ docker run -t -i --privileged ubuntu bash
root@50e3f57e16e6:/# mount -t tmpfs none /mnt
root@50e3f57e16e6:/# df -h
Filesystem      Size  Used Avail Use% Mounted on
overlay          59G  4.9G   51G   9% /
tmpfs            64M     0   64M   0% /dev
tmpfs           995M     0  995M   0% /sys/fs/cgroup
shm              64M     0   64M   0% /dev/shm
/dev/sda1        59G  4.9G   51G   9% /etc/hosts
root@6769cf1846d1:/#
```



### Mount volume (-v, --read-only)

```shell
docker run -v ~/docker:/docker -w /docker -it ubuntu bash
root@665fba966d6d:/docker# pwd
```

When the host directory of a bind-mounted volume doesn’t exist, Docker will automatically create this directory on the host for you. In the example above, Docker will create the `/docker` folder before starting your container.

### Publish or expose port (-p, --expose)

```shell
$ docker run -p 127.0.0.1:80:8080/tcp ubuntu bash
```

This binds port `8080` of the container to TCP port `80` on `127.0.0.1` of the host machine. You can also specify `udp` and `sctp` ports. The [Docker User Guide](https://docs.docker.com/engine/userguide/networking/default_network/dockerlinks/) explains in detail how to manipulate ports in Docker.

Note that ports which are not bound to the host (i.e., `-p 80:80` instead of `-p 127.0.0.1:80:80`) will be accessible from the outside. This also applies if you configured UFW to block this specific port, as Docker manages his own iptables rules. [Read more](https://docs.docker.com/network/iptables/)

```
$ docker run --expose 80 ubuntu bash
```

This exposes port `80` of the container without publishing the port to the host system’s interfaces.



# File system sharing (osxfs)

### Namespaces

Much of the macOS file system that is accessible to the user is also available to containers using the `-v` bind mount syntax. The following command runs a container from an image called `r-base` and shares the macOS user’s `~/Desktop/` directory as `/Desktop` in the container.

```shell
docker run -it -v ~/Desktop:/Desktop r-base bash	
```

```shell
docker run -t -i -v /var/run/docker.sock:/var/run/docker.sock -v  /usr/local/bin:/usr/bin/docker busybox sh
/ # ls
bin   dev   etc   home  proc  root  sys   tmp   usr   var
```

All other paths used in `-v` bind mounts are sourced from the Moby Linux VM running the Docker containers, so arguments such as `-v /var/run/docker.sock:/var/run/docker.sock` should work as expected.



# Docker and iptables

On Linux, Docker manipulates `iptables` rules to provide network isolation. While this is an implementation detail and you should not modify the rules Docker inserts into your `iptables` policies, it does have some implications on what you need to do if you want to have your own policies in addition to those managed by Docker.

If you’re running Docker on a host that is exposed to the Internet, you will probably want to have iptables policies in place that prevent unauthorized access to containers or other services running on your host. This page describes how to achieve that, and what caveats you need to be aware of.



# Iptables Tutorial – Securing Ubuntu VPS with Linux Firewall

## What is Iptables, and How Does It Work?

Simply put, iptables is a firewall program for [Linux](https://www.linux.org/). It will monitor traffic from and to your server using **tables**. These tables contain **sets of rules**, called **chains**, that will filter incoming and outgoing data packets.

When a **packet** matches a **rule**, it is given a **target**, which can be another chain or one of these special values:

- **ACCEPT** – will allow the packet to pass through.
- **DROP** – will not let the packet pass through.
- **RETURN** – stops the packet from traversing through a chain and tell it to go back to the previous chain.

In this iptables tutorial, we are going to work with one of the default tables, called **filter**. It consists of three chains:

- **INPUT** – controls incoming packets to the server.
- **FORWARD** – filters incoming packets that will be forwarded somewhere else.
- **OUTPUT** – filter packets that are going out from your server.

iptables rules only apply to **ipv4**. If you want to set up a firewall for the **ipv6** protocol, you will need to use **ip6tables** instead.



#### Enabling Traffic on Localhost

To allow traffic on localhost, type this command:

```shell
root@e5406ed7ef1d:/docker# iptables -A INPUT -i lo -j ACCEPT
root@e5406ed7ef1d:/docker# iptables -L -v
Chain INPUT (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination
    0     0 ACCEPT     all  --  lo     any     anywhere             anywhere

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain OUTPUT (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination
```

#### Enabling Connections on HTTP, SSH, and SSL Port

Next, we want **http** (port **80**), **https** (port **443**), and **ssh** (port **22**) connections to work as usual. To do this, we need to specify the protocol (**-p**) and the corresponding port (**–dport**). You can execute these commands one by one:

```shell
root@e5406ed7ef1d:/docker# iptables -A INPUT -p tcp --dport 22 -j ACCEPT
root@e5406ed7ef1d:/docker# iptables -A INPUT -p tcp --dport 80 -j ACCEPT
root@e5406ed7ef1d:/docker# iptables -A INPUT -p tcp --dport 443 -j ACCEPT
root@e5406ed7ef1d:/docker# iptables -L -v
Chain INPUT (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination
    0     0 ACCEPT     all  --  lo     any     anywhere             anywhere
    0     0 ACCEPT     tcp  --  any    any     anywhere             anywhere             tcp dpt:22
    0     0 ACCEPT     tcp  --  any    any     anywhere             anywhere             tcp dpt:80
    0     0 ACCEPT     tcp  --  any    any     anywhere             anywhere             tcp dpt:443

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain OUTPUT (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination
```

#### Refrence : 

[Iptables Tutorial](https://www.hostinger.com/tutorials/iptables-tutorial/#comment-116684)

# How to Install Redis on Ubuntu

## Step 1 – Prerequsities	

```shell
sudo apt-get update
sudo apt-get upgrade
```

## Step 2 – Installing Redis

```shell
sudo apt-get install redis-server
```

Next is to enable Redis to start on system boot. Also restart Redis service once.

```
sudo systemctl enable redis-server.service
```

if bash: systemctl: command not found

```
root@e5406ed7ef1d:/docker# apt-get install systemd
```

## Step 3 – Configure Redis	

```
sudo vim /etc/redis/redis.conf
```

```
whereis redis-server
redis-server: /usr/bin/redis-server
```

## Step 4 – Install Redis PHP Extension

```shell
sudo apt-get install php-redis
```

## Step 5 – Test Connection to Redis Server

```
redis-cli
```

Few more examples of redis-cli command line tool. You can find more details about redis-cli [here](https://redis.io/commands/INFO).

```
redis-cli info
redis-cli info stats
redis-cli info server
```

