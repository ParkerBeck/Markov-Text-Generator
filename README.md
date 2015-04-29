# BECK_CSCI2270_FinalProject
Markov Chain text generation

Markov Chain
A Markov chain is a stochastic model describing a sequence of possible events in which the probability of each event depends only on the state attained in the previous event.
This is shown in the program by having a large amount of text put into the program initially. The program then takes all of the words from that file and makes a 
graph of them with connections being made between words that are next to each other at any point in the text file. The program is started when a seed word is given to it. The seed word is the first word used to generate the graph.  The seed word is then 
found in the list. Then instead of following the original path of the story the program will then select, at random, a possible word that came after the seed word
at any point in the story. This continues on as the next word then has a random word come after it. An example would be if the text file had the phrases; "cat ran",
"cat jumped", and "cat moved". If the seed word was cat then the possible following words could be ran, jumped, or moved. This process continues on until a complete story by having an equal number of sentences to the original text
is made.

System Requirements:

C++ version 11 used
Libraries used: map, vector, string, iostream, queue, fstream, sstream, random, time.h, algorithm

Instructions:

The first decision is to choose a document to create the chain from by entering the number next to the choice and pressing enter.
The second decision is to choose a seed word to start the graph from by typing in a word that appears in the chosen document.  Make sure that the word is spelled correctly before pressing enter to start the chain.

If a word is chosen that does not apppear in the chosen document, please follow the on screen instructions to be able to pick a new word.

Once the program has ran, there is a choice to rerun the program with a new word by following the on screen instructions.


The program will create a text file with the complete chain that can be found in the program file.