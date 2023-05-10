* * *
## 유니티에 MongoDB Driver 설치하는 방법
> Assets 안에 Plugins 폴더를 하나 만들고
> bin/Debug/netstandard2.0/publish 안에 있는 모든 dll 파일을 옮기면 완료
* * *
## 드라이버 생성 (Windows 터미널)
> dotnet new classlib --framework "netstandard2.0" -o MongoDBUnity<br>
> cd MongoDBUnity<br>
> dotnet add package MongoDB.Driver<br>
> dotnet publish
* * *
