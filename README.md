# Сервер для отдачи статический файлов

Разработал Надточий Алексей в рамка курса highload.
 
### Build
```
git clone https://github.com/AleksMVP/static-server.git
cd static-server
mkdir build
cd build
cmake ..
make
```

### Docker build
```
git clone https://github.com/AleksMVP/static-server.git
cd static-server
docker build -t bobernginx .
docker run -p 7888:7888 bobernginx
```
