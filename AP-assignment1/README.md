# AP---assignment1

Project: Netflix

Made by:

Itay hoban, ID 211547153
Matan, ID 211458484
Oren, ID 209188689

Assignment 1 of Advanced Programming course. This part contains interface for watching movies and recommendation system.
CLI software

Link to GitHub repository:
https://github.com/matan211/AP-assignment1

Execution in Docker:
Compile: docker build -t my_project .
Run CLI: docker run -it my_project ./my_project
Unit test: docker run --rm my_project

Exexcution instructions:

1. Download MinGW to your PC. As following link: https://www.youtube.com/watch?v=oC69vlWofJQ
2. Open terminal in AP-assignment1/src folder
3. Compile by the command: g++ -o ConsoleMenu ConsoleMenu.cpp App.cpp HelpCommand.cpp AddMovieCommand.cpp Utils.cpp DisplayRecommendedMoviesCommand.cpp
4. Execute by the command: ./ConsoleMenu
