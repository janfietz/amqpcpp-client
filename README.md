# AMQP-CPP Client 

[![Build Status](https://travis-ci.org/janfietz/amqpcpp-client.svg?branch=master)](https://travis-ci.org/janfietz/amqpcpp-client)

Simple C++14 project to test [AMQP-CPP](https://github.com/CopernicaMarketingSoftware/AMQP-CPP) functionality.

## Build using cmake
## Requirements

- `git`
- `cmake` version `3.5.1` or higher.
- `gcc` or `clang` that supports `std=c++14`.

## Start rabbitmq

### Requirements
- `docker`
- `docker-compose`

```
cd rabbitmq
docker-compose uo
```

### Managment plugin

Open [http://localhost:15672/]

Use the following login
```
username: guest
password: guest
```