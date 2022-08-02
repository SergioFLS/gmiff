# gmiff
This project aims to be an FLOSS and portable clone of the GameMaker runtime, targetting Studio versions that work with a data file (on Windows, it's `data.win`).

I want it to work kind of like ScummVM and EasyRPG, which replace the original runtime and allow the games run on platforms where this project can, including unsupported platforms by GameMaker (such as FreeBSD).

## Current status
I just started working on the project. Right now I was able to read the GEN8 chunk, which means that you can't actually use it to run games (yet) :(

I also did this while learning some of the features of C, so sorry if my code is bad...

## Origin of the idea
Some years ago, I wanted to play Undertale on an Android phone as my laptop was broken a long time ago. Eventually I found the [Droidtale](https://mrpowergamerbr.com/us/projects/droidtale/) project which involved slapping Undertale's `data.win` file into an Android runner.

Various years later, Deltarune Chapter 1 was released, and I wanted to play it natively on Linux. While it did run on Wine, there was a bug on Wine that made the game play too fast.

I then found [a Reddit post](https://www.reddit.com/r/Deltarune/comments/9wizh3/deltarune_running_on_linux_natively/) which had similar procedures to Droidtale. This made me wonder if any GameMaker game would run with just a compatible runtime...

I tried another Windows-only game with a different runner, and yes, it ran!

Later then, I found the Underminers community, which dedicates itself to datamine secrets in Undertale, which had their own tool, UndertaleModTool. You gave it a GameMaker data file, and it would let you edit most of the data inside.

And while messing around with it, I noticed that the code was stored in a propietary bytecode format. And there goes the idea for this project! (omg i didn't realise i was writing this too long)
## Thank you
* [Luna](https://github.com/nommiin/Luna) - Another somewhat working(!) recreation of the GameMaker runtime in C#. Also the inspiration of this project.
* [UndertaleModTool](https://github.com/krzys-h/UndertaleModTool) and [DogScepter](https://github.com/colinator27/DogScepter) - Modding tools primarily for Undertale and Deltarune. Parsing code was used for reference.
