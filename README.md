# 427-cpp-async

Задания "Знакомство с асинхронным вводом/выводом на C++" (LEARNING_CENTER-427)

## Requirements
- [Boost](https://www.boost.org/users/download/)

## Buildings
```shell
cd boost_X_XX_X
./bootstrap.sh
./b2 install --with-system --with-thread --with-date_time --with-regex --with-serialization --prefix=/dir/to/install/lib
```

## Uninstall
```shell
sudo rm -rf /usr/local/lib/libboost* cmake
sudo rm -rf /usr/local/include/boost
```