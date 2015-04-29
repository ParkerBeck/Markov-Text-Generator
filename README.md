# BECK_CSCI2270_FinalProject
Markov Chain text generation

Markov Chain
A Markov chain is a stochastic model describing a sequence of possible events in which the probability of each event depends only on the state attained in the previous event.
This is shown in the program by having a large amount of text put into the program initially. The program then takes all of the words from that file and makes a 
graph of them, with connections being made between words that are next to each other at any point in the text file. The program is started when a seed word is given to it. The seed word is then 
found in the list. Then instead of following the original path of the story the program will then select, at random, a possible word that came after the seed word
at any point in the story. This continues on as the next word then has a random word come after it. An example would be if the text file had the phrases; "cat ran",
"cat jumped", and "cat moved". If the seed word was cat then the possible following words could be ran, jumped, or moved. This process continues on until a complete story
is made.

C++ version 11 used
Libraries used: map, vector, string, iostream, queue, fstream, sstream, random, time.h, algorithm

