# red-black-tree-cpp

![language](https://img.shields.io/badge/language-C%2B%2B-blue) ![platform](https://img.shields.io/badge/platform-cross--platform-lightgrey)
<!-- ![CI](https://github.com/arikthehacker/red-black-tree-cpp/actions/workflows/ci.yml/badge.svg) -->

A red-black tree I wrote by hand (rotations, recoloring, and the full insert fix-up
cases), storing an abstract `Race` base class with three derived race types.

## quickstart

```
git clone https://github.com/arikthehacker/red-black-tree-cpp.git
cd red-black-tree-cpp
sudo apt-get install -y build-essential
make run
```

`make run` feeds `sample-input.txt` (create the tree, insert four races, display it). The
in-order display shows the node colors:

```
[BLACK] Alpha Walk: ...
[BLACK] Beta Marathon: ...
[BLACK] Fun Run: ...
[RED] Gamma Run: ...
```

## menu

On start the program prints:

```
================== shamrock run 2025 =====================
 1. create kidsRun
 2. create raceWalk
 3. create halfMarathon
 4. registerRace
 5. startRace
 6. stopRace
 7. test kidsRun unique method (snackBreak)
 8. test raceWalk unique methods (penalty + dq)
 9. test halfMarathon unique methods
10. create redBlackTree
11. insert new race into rbTree
12. display rbTree
13. remove all from rbTree
14. destroy rbTree
15. exit
============================================================
enter choice: 
```

## how it works

Insertion is an ordinary BST insert, then `fixInsertion` walks up restoring the
red-black properties. If the uncle is red it recolors and recurses on the grandparent; if
the uncle is black it rotates and recolors:

```c
// case 1: uncle is red => recolor
if (uncle && uncle->color == Color::RED)
{
    parent->color = Color::BLACK;
    uncle->color = Color::BLACK;
    grandparent->color = Color::RED;
    fixInsertion(grandparent);
    return;
}
// case 2 & 3: uncle is black => rotate then recolor
if (parent == grandparent->left)
{
    if (node == parent->right) { rotateLeft(parent); ... }
    parent->color = Color::BLACK;
    grandparent->color = Color::RED;
    rotateRight(grandparent);
}
```

`rotateLeft` and `rotateRight` re-link the nodes and their parents, and removal is
recursive. The tree stores `Race` objects through a `shared_ptr`, so the three derived
types (`kidsRun`, `raceWalk`, `halfMarathon`) all live in the same tree with their own
behavior.

The program is menu-driven and reads choices from standard input; `sample-input.txt` is
one scripted session and `expected-output.txt` is what it prints.
