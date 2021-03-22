# Сервер для отдачи статический файлов

Разработал Надточий Алексей в рамка курса highload.
 
## Build

```
git clone https://github.com/AleksMVP/static-server.git
cd static-server
mkdir build
cd build
cmake ..
make
```

## Docker build
```
git clone https://github.com/AleksMVP/static-server.git
cd static-server
docker build -t static-server .
docker run -p 7888:7888 static-server
```

## Benchmarks

### Nginx
```
12 threads and 400 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   137.94ms  267.55ms   1.97s    90.64%
    Req/Sec   337.91     80.57     0.93k    77.70%
```

### static-server
```
12 threads and 400 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     6.56ms    2.00ms  63.21ms   95.51%
    Req/Sec   213.45    176.23     0.88k    62.26%
```
