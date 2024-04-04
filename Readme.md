### Описание 
Программа для вывод информации о
 * кодеке, 
 * контейнере, 
 * ширине/высоте, 
 * количестве кадров, 
 * так же информацию об аудио дорожке

### Компиляция 
`g++ main.cpp -o main -lavformat -lavcodec -lavutil`

### Использование
`./main .\<filename>`

### Использовал 
* g++.exe (Rev5, Built by MSYS2 project) 13.2.0
* mingw-w64-x86_64-ffmpeg 6.1.1-9
* Инструкция по настройке MSYS2 https://habr.com/ru/articles/599243/
