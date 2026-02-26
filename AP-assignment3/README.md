# AP-assignment3

Part 3 of Netflix project



Link to GitHub repository:
https://github.com/matan211/AP-assignment3

for the newtwork server:
one terminal:
go to server folder and then type npm start

second terminal:
for the commands like curl -i http://localhost:3000/api/categories

Server(on cpp_server folder):
g++ -c src/ConsoleMenu.cpp -o ConsoleMenu.o
g++ -c src/DisplayRecommendedMoviesCommand.cpp -o DisplayRecommendedMoviesCommand.o
g++ -c src/AddMovieCommand.cpp -o AddMovieCommand.o
g++ -c src/HelpCommand.cpp -o HelpCommand.o
g++ -c src/DeleteCommand.cpp -o DeleteCommand.o
g++ -c src/Utils.cpp -o Utils.o
g++ ConsoleMenu.o DisplayRecommendedMoviesCommand.o AddMovieCommand.o HelpCommand.o DeleteCommand.o Utils.o -o output.exe -lws2_32
./output.exe

Run NodeJS:
1. On server folder: npm init -y
2. Install requirements: npm i express cors body-parser custom-env jsonwebtoken mongoose uuid axios
3. Add to package.json: "scripts": {
    "start": "SET NODE_ENV=local && node app.js"
  }
4. Create config on 'server' folder.
5. Create .env.local file in 'config' file.
6. Write in .env.local: CONNECTION_STRING="mongodb://localhost:27017/Netflix_database"
PORT=8080 
7. Run server on 'server' folder: npm start
8. Run user in new terminal with '\' before ' " ', e.g., curl.exe -i -X POST http://localhost:8080/movies/ -H "Content-Type: application/json" -d '{\"name\":\"The Dark knight\", \"genre\":\"Action\"}' 

Run on Docker:
on root folder: docker-compose up --build
Run Client on seperate Terminal.