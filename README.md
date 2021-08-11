# fluxchess
Chess game and artifical intelligence algorithm written from scratch.

Language: **c++**

## AI
Algorithms used:
- [Minimax](https://en.wikipedia.org/wiki/Minimax)
- [Alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)
- [Quiescence search algorithm](https://en.wikipedia.org/wiki/Quiescence_search)

## GUI
Made with [*qt5*](https://github.com/qt/qt5).

## License
**This project** is licensed under the terms of the MIT License.

## Building
You can use [*qmake*](https://doc.qt.io/qt-5/qmake-manual.html) to build this project.

```sh
cd fluxchess

mkdir build && cd build
cp -r ../res .

qmake .. && make
```

## Status
Currently **in development**.
